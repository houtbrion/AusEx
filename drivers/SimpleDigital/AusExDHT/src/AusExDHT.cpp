#include "AusExDHT.h"

/*
 * 
 */
AusExDHT::AusExDHT(int pinNumber, uint8_t dhtType, int32_t tempSensorId, int32_t humiditySensorId):
  _pin(pinNumber),
  _type(dhtType),
  _temp(this,tempSensorId),
  _humidity(this,humiditySensorId)
{}



AusExDHT::Temperature::Temperature(AUSEX_DHT_CLASS * parent, int32_t id):
  _parent(parent),
  _id(id)
{}

AusExDHT::Humidity::Humidity(AUSEX_DHT_CLASS * parent, int32_t id):
  _parent(parent),
  _id(id)
{}

bool AusExDHT::begin(bool pullUp){
  lastTime=0;
  oldTemperature=NO_MEASURE;
  oldHumidity=NO_MEASURE;
  measure_delay=(getMinDelay(_type))/1000;
  #ifdef __AVR
    _bit = digitalPinToBitMask(_pin);
    _port = digitalPinToPort(_pin);
  #endif
  _maxcycles = microsecondsToClockCycles(1000);  // 1 millisecond timeout for
                                                 // reading pulses from DHT sensor.
  // Note that count is now ignored as the DHT reading algorithm adjusts itself
  // based on the speed of the processor.
  pullTime=55; // usec
  if (pullUp) {
    pinMode(_pin, INPUT_PULLUP);
  } else {
    pinMode(_pin, INPUT);
  }
  return true;
}


// Expect the signal line to be at the specified level for a period of time and
// return a count of loop cycles spent at that level (this cycle count can be
// used to compare the relative time of two pulses).  If more than a millisecond
// ellapses without the level changing then the call fails with a 0 response.
// This is adapted from Arduino's pulseInLong function (which is only available
// in the very latest IDE versions):
//   https://github.com/arduino/Arduino/blob/master/hardware/arduino/avr/cores/arduino/wiring_pulse.c
uint32_t AusExDHT::expectPulse(bool level) {
#if (F_CPU > 16000000L)
  uint32_t count = 0;
#else
  uint16_t count = 0; // To work fast enough on slower AVR boards
#endif
  // On AVR platforms use direct GPIO port access as it's much faster and better
  // for catching pulses that are 10's of microseconds in length:
  #ifdef __AVR
    uint8_t portState = level ? _bit : 0;
    while ((*portInputRegister(_port) & _bit) == portState) {
      if (count++ >= _maxcycles) {
        return DHT_TIMEOUT; // Exceeded timeout, fail.
      }
    }
  // Otherwise fall back to using digitalRead (this seems to be necessary on ESP8266
  // right now, perhaps bugs in direct port access functions?).
  #else
    while (digitalRead(_pin) == level) {
      if (count++ >= _maxcycles) {
        return DHT_TIMEOUT; // Exceeded timeout, fail.
      }
    }
  #endif

  return count;
}

bool AusExDHT::readDHT(void) {
  // Reset 40 bits of received data to zero.
  data[0] = data[1] = data[2] = data[3] = data[4] = 0;

#if defined(ESP8266)
    yield(); // Handle WiFi / reset software watchdog
#endif

  // Send start signal.  See DHT datasheet for full signal diagram:
  //   http://www.adafruit.com/datasheets/Digital%20humidity%20and%20temperature%20sensor%20AM2302.pdf

  // Go into high impedence state to let pull-up raise data line level and
  // start the reading process.
  pinMode(_pin, INPUT_PULLUP);
  delay(1);

  // First set data line low for a period according to sensor type
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
  switch(_type) {
    case DHT22:
    case DHT21:
      delayMicroseconds(1100); // data sheet says "at least 1ms"
      break;
    case DHT11:
    default:
      delay(20); //data sheet says at least 18ms, 20ms just to be safe
      break;
  }

  uint32_t cycles[80];
  {
    // End the start signal by setting data line high for 40 microseconds.
    pinMode(_pin, INPUT_PULLUP);

    // Delay a moment to let sensor pull data line low.
    delayMicroseconds(pullTime);

    // Now start reading the data line to get the value from the DHT sensor.

    // Turn off interrupts temporarily because the next sections
    // are timing critical and we don't want any interruptions.
    AusExDhtInterruptLock lock;

    // First expect a low signal for ~80 microseconds followed by a high signal
    // for ~80 microseconds again.
    if (expectPulse(LOW) == DHT_TIMEOUT) {
      return false;
    }
    if (expectPulse(HIGH) == DHT_TIMEOUT) {
      return false;
    }

    // Now read the 40 bits sent by the sensor.  Each bit is sent as a 50
    // microsecond low pulse followed by a variable length high pulse.  If the
    // high pulse is ~28 microseconds then it's a 0 and if it's ~70 microseconds
    // then it's a 1.  We measure the cycle count of the initial 50us low pulse
    // and use that to compare to the cycle count of the high pulse to determine
    // if the bit is a 0 (high state cycle count < low state cycle count), or a
    // 1 (high state cycle count > low state cycle count). Note that for speed all
    // the pulses are read into a array and then examined in a later step.
    for (int i=0; i<80; i+=2) {
      cycles[i]   = expectPulse(LOW);
      cycles[i+1] = expectPulse(HIGH);
    }
  } // Timing critical code is now complete.

  // Inspect pulses and determine which ones are 0 (high state cycle count < low
  // state cycle count), or 1 (high state cycle count > low state cycle count).
  for (int i=0; i<40; ++i) {
    uint32_t lowCycles  = cycles[2*i];
    uint32_t highCycles = cycles[2*i+1];
    if ((lowCycles == DHT_TIMEOUT) || (highCycles == DHT_TIMEOUT)) {
      return false;
    }
    data[i/8] <<= 1;
    // Now compare the low and high cycle times to see if the bit is a 0 or 1.
    if (highCycles > lowCycles) {
      // High cycles are greater than 50us low cycle count, must be a 1.
      data[i/8] |= 1;
    }
    // Else high cycles are less than (or equal to, a weird case) the 50us low
    // cycle count so this must be a zero.  Nothing needs to be changed in the
    // stored data.
  }

  // Check we read 40 bits and that the checksum matches.
  if (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) {
    return true;
  } else {
    return false;
  }
}

float AusExDHT::dataToTemperature(void){
  float f = NAN;
  switch (_type) {
  case DHT11:
    f = data[2];
    if (data[3] & 0x80) {
      f = -1 - f ;
    }
    f += (data[3] & 0x0f) * 0.1;
    break;
  case DHT12:
    f = data[2];
    f += (data[3] & 0x0f) * 0.1;
    if (data[2] & 0x80) {
      f *= -1;
    }
    break;
  case DHT22:
  case DHT21:
    f = ((word)(data[2] & 0x7F)) << 8 | data[3];
    f *= 0.1;
    if (data[2] & 0x80) {
      f *= -1;
    }
    break;
  }
  return f;
}

float AusExDHT::dataToHumidity(void){
  float f = NAN;
  switch (_type) {
  case DHT11:
  case DHT12:
    f = data[0] + data[1] * 0.1;
    break;
  case DHT22:
  case DHT21:
    f = ((word)data[0]) << 8 | data[1];
    f *= 0.1;
    break;
  }
  return f;
}

bool AusExDHT::measure(){
  if (false==readDHT()){
    return false;
  }
  oldTemperature=dataToTemperature();
  oldHumidity=dataToHumidity();
  return true;
}

void AusExDHT::setName(sensor_t* sensor) {
  switch(_type) {
    case DHT11:
      strncpy(sensor->name, "DHT11", sizeof(sensor->name) - 1);
      break;
    case DHT12:
      strncpy(sensor->name, "DHT12", sizeof(sensor->name) - 1);
      break;
    case DHT21:
      strncpy(sensor->name, "DHT21", sizeof(sensor->name) - 1);
      break;
    case DHT22:
      strncpy(sensor->name, "DHT22", sizeof(sensor->name) - 1);
      break;
    default:
      // TODO: Perhaps this should be an error?  However main DHT library doesn't enforce
      // restrictions on the sensor type value.  Pick a generic name for now.
      strncpy(sensor->name, "DHT?", sizeof(sensor->name) - 1);
      break;
  }
  sensor->name[sizeof(sensor->name)- 1] = 0;
}
int32_t AusExDHT::getMinDelay(uint8_t type) {
  switch(type) {
    case DHT11:
      return 1000000L;  // 1 second (in microseconds)
    case DHT12:
      return 2000000L;  // 2 second (in microseconds)
    case DHT21:
      return 2000000L;  // 2 seconds (in microseconds)
    case DHT22:
      return 2000000L;  // 2 seconds (in microseconds)
    default:
      // Default to slowest sample rate in case of unknown type.
      return 2000000L;  // 2 seconds (in microseconds)
  }
}
void AusExDHT::Temperature::getSensor(sensor_t* sensor) {
  // Clear sensor definition.
  memset(sensor, 0, sizeof(sensor_t));
  // Set sensor name.
  _parent->setName(sensor);
  // Set version and ID
  sensor->version         = AUSEX_DHT_SENSOR_LIBRARY_VERSION;
  sensor->sensor_id       = _id;
  // Set type and characteristics.
  sensor->type            = SENSOR_TYPE_AMBIENT_TEMPERATURE;
  sensor->min_delay =_parent->getMinDelay(_parent->_type);
  
  switch (_parent->_type) {
    case DHT11:
      sensor->max_value   = 50.0F;
      sensor->min_value   = 0.0F;
      sensor->resolution  = 2.0F;
      break;
    case DHT12:
      sensor->max_value   = 60.0F;
      sensor->min_value   = -20.0F;
      sensor->resolution  = 0.5F;
      break;
    case DHT21:
      sensor->max_value   = 80.0F;
      sensor->min_value   = -40.0F;
      sensor->resolution  = 0.1F;
      break;
    case DHT22:
      sensor->max_value   = 125.0F;
      sensor->min_value   = -40.0F;
      sensor->resolution  = 0.1F;
      break;
    default:
      // Unknown type, default to 0.
      sensor->max_value   = 0.0F;
      sensor->min_value   = 0.0F;
      sensor->resolution  = 0.0F;
      break;
  }
  sensor->init_delay = sensor->min_delay;
}

void AusExDHT::Humidity::getSensor(sensor_t* sensor) {
  // Clear sensor definition.
  memset(sensor, 0, sizeof(sensor_t));
  // Set sensor name.
  _parent->setName(sensor);
  // Set version and ID
  sensor->version         = AUSEX_DHT_SENSOR_LIBRARY_VERSION;
  sensor->sensor_id       = _id;
  // Set type and characteristics.
  sensor->type            = SENSOR_TYPE_RELATIVE_HUMIDITY;
  sensor->min_delay =_parent->getMinDelay(_parent->_type);
  switch (_parent->_type) {
    case DHT11:
      sensor->max_value   = 80.0F;
      sensor->min_value   = 20.0F;
      sensor->resolution  = 5.0F;
      break;
    case DHT12:
      sensor->max_value   = 95.0F;
      sensor->min_value   = 20.0F;
      sensor->resolution  = 5.0F;
      break;
    case DHT21:
      sensor->max_value   = 100.0F;
      sensor->min_value   = 0.0F;
      sensor->resolution  = 0.1F;
      break;
    case DHT22:
      sensor->max_value   = 100.0F;
      sensor->min_value   = 0.0F;
      sensor->resolution  = 0.1F;
      break;
    default:
      // Unknown type, default to 0.
      sensor->max_value   = 0.0F;
      sensor->min_value   = 0.0F;
      sensor->resolution  = 0.0F;
      break;
  }
  sensor->init_delay = sensor->min_delay;
}

bool AusExDHT::getTemperature(sensors_event_t* event){
  unsigned long currentTime=millis();
  float timeDiff=currentTime - lastTime;
  if (0 > timeDiff) {
    timeDiff=0;
    lastTime=0;
  }
  if ((float) measure_delay > timeDiff) {
    /* 時刻が経過していない場合は，古いデータを返す */
    event->timestamp = lastTime;
    event->temperature = oldTemperature;
    return true;
  } else {
    bool flag=measure();
    lastTime=millis();
    event->timestamp = lastTime;
    event->temperature = oldTemperature;
    return flag;
  }
}

bool AusExDHT::getHumidity(sensors_event_t* event){
  unsigned long currentTime=millis();
  float timeDiff=currentTime - lastTime;
  if (0 > timeDiff) {
    timeDiff=0;
    lastTime=0;
  }
  if ((float)measure_delay > timeDiff) {
    /* 時刻が経過していない場合は，古いデータを返す */
    event->timestamp = lastTime;
    event->relative_humidity = oldHumidity;
    return true;
  } else {
    bool flag=measure();
    lastTime=millis();
    event->timestamp = lastTime;
    event->relative_humidity = oldHumidity;
    return flag;
  }
}

bool AusExDHT::Temperature::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->size   = sizeof(sensors_event_t);
  event->sensor_id = _id;
  event->type      = SENSOR_TYPE_AMBIENT_TEMPERATURE;
  bool flag=_parent->getTemperature(event);
  return flag;
}


bool AusExDHT::Humidity::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->size   = sizeof(sensors_event_t);
  event->sensor_id = _id;
  event->type      = SENSOR_TYPE_RELATIVE_HUMIDITY;
  bool flag=_parent->getHumidity(event);
  return flag;
}

bool AusExDHT::enableAutoRange(bool enabled) {
  return false;
}

bool AusExDHT::Temperature::enableAutoRange(bool enabled) {
  return _parent->enableAutoRange(enabled);
}

bool AusExDHT::Humidity::enableAutoRange(bool enabled) {
  return _parent->enableAutoRange(enabled);
}


int AusExDHT::setMode(int mode){
  return -1;
}

int AusExDHT::Temperature::setMode(int mode){
  return _parent->setMode(mode);
}

int AusExDHT::Humidity::setMode(int mode){
  return _parent->setMode(mode);
}

int AusExDHT::getMode(void){
  return -1;
}

int AusExDHT::Temperature::getMode(void){
  return _parent->getMode();
}

int AusExDHT::Humidity::getMode(void){
  return _parent->getMode();
}
