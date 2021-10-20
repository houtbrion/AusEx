#include "AusExSHT31.h"



/*
 * 
 */

AusExSHT31::AusExSHT31(TwoWire * theWire , int32_t tempSensorId, int32_t humiditySensorId):
  _i2c_if(theWire),
  _temp(this,tempSensorId),
  _humidity(this,humiditySensorId)
{}

AusExSHT31::Temperature::Temperature(AUSEX_SHT31_CLASS * parent, int32_t id):
  _parent(parent),
  _id(id)
{}

AusExSHT31::Humidity::Humidity(AUSEX_SHT31_CLASS * parent, int32_t id):
  _parent(parent),
  _id(id)
{}

bool AusExSHT31::begin(uint32_t addr){
  _mode=0;
  lastTime=millis();
  oldTemperature=NO_MEASURE;
  oldHumidity=NO_MEASURE;
  _i2c_addr=addr;
  _i2c_if->begin();
  reset();
  return true;
}

void AusExSHT31::reset(void) {
  writeCommand(SHT31_SOFTRESET);
  delay(10);
}


void AusExSHT31::writeCommand(uint16_t cmd) {
  _i2c_if->beginTransmission(_i2c_addr);
  _i2c_if->write(cmd >> 8);
  _i2c_if->write(cmd & 0xFF);
  _i2c_if->endTransmission();
}

uint8_t AusExSHT31::crc8(const uint8_t *data, int len) {
  /*
   *
   * CRC-8 formula from page 14 of SHT spec pdf
   *
   * Test data 0xBE, 0xEF should yield 0x92
   *
   * Initialization data 0xFF
   * Polynomial 0x31 (x8 + x5 +x4 +1)
   * Final XOR 0x00
   */

  const uint8_t POLYNOMIAL(0x31);
  uint8_t crc(0xFF);

  for (int j = len; j; --j) {
    crc ^= *data++;

    for (int i = 8; i; --i) {
      crc = (crc & 0x80) ? (crc << 1) ^ POLYNOMIAL : (crc << 1);
    }
  }
  return crc;
}

void AusExSHT31::Temperature::getSensor(sensor_t* sensor) {
  // Clear sensor definition.
  memset(sensor, 0, sizeof(sensor_t));
  // Set sensor name.
  strncpy (sensor->name, AUSEX_SHT31_SENSOR_NAME , sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  // Set version and ID
  sensor->version         = AUSEX_SHT31_SENSOR_LIBRARY_VERSION;
  sensor->sensor_id       = _id;
  // Set type and characteristics.
  sensor->type            = SENSOR_TYPE_AMBIENT_TEMPERATURE;
  sensor->min_delay       = AUSEX_SHT31_SENSOR_TEMPERATURE_MIN_DELAY;
  sensor->max_value       = AUSEX_SHT31_SENSOR_TEMPERATURE_MAX_VALUE;
  sensor->min_value       = AUSEX_SHT31_SENSOR_TEMPERATURE_MIN_VALUE;
  sensor->resolution      = AUSEX_SHT31_SENSOR_TEMPERATURE_RESOLUTION;
  sensor->init_delay = AUSEX_SHT31_SENSOR_INIT_DELAY;
}

void AusExSHT31::Humidity::getSensor(sensor_t* sensor) {
  // Clear sensor definition.
  memset(sensor, 0, sizeof(sensor_t));
  // Set sensor name.
  strncpy (sensor->name, AUSEX_SHT31_SENSOR_NAME , sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  // Set version and ID
  sensor->version         = AUSEX_SHT31_SENSOR_LIBRARY_VERSION;
  sensor->sensor_id       = _id;
  // Set type and characteristics.
  sensor->type            = SENSOR_TYPE_RELATIVE_HUMIDITY;
  sensor->min_delay       = AUSEX_SHT31_SENSOR_HUMIDITY_MIN_DELAY;
  sensor->max_value       = AUSEX_SHT31_SENSOR_HUMIDITY_MAX_VALUE;
  sensor->min_value       = AUSEX_SHT31_SENSOR_HUMIDITY_MIN_VALUE;
  sensor->resolution      = AUSEX_SHT31_SENSOR_HUMIDITY_RESOLUTION;
  sensor->init_delay = AUSEX_SHT31_SENSOR_INIT_DELAY;
}


boolean AusExSHT31::readSHT31(void) {
#ifdef DEBUG
  Serial.println("******** readSHT31 start *******");
#endif
  uint8_t readbuffer[6];
  unsigned long currentTime=millis();
  float timeDiff=currentTime - lastTime;
  if (0 > timeDiff) {
    timeDiff=0;
    lastTime=0;
  }
  if (( AUSEX_SHT31_SENSOR_TEMPERATURE_MIN_DELAY > (timeDiff*1000)) && (AUSEX_SHT31_SENSOR_HUMIDITY_MIN_DELAY > (timeDiff*1000))) {
#ifdef DEBUG
    Serial.println("interval time is not enough");
#endif
    return true;
  }
  lastTime=millis();

  writeCommand(SHT31_MEAS_HIGHREP);

  delay(20);
  _i2c_if->requestFrom(_i2c_addr, (uint8_t)6);
  int i2cState = _i2c_if->available();
#ifdef DEBUG
  Serial.print("++++++++++ I2C state = ");Serial.println(i2cState);
#endif
  if (i2cState != 6) {
#ifdef DEBUG
    Serial.println("++++++++++ I2C read error ++++++++++++++");
#endif
    return false;
  }
  for (uint8_t i = 0; i < 6; i++) {
    readbuffer[i] = _i2c_if->read();
    //  Serial.print("0x"); Serial.println(readbuffer[i], HEX);
  }

  uint16_t ST, SRH;
  ST = readbuffer[0];
  ST <<= 8;
  ST |= readbuffer[1];

  if (readbuffer[2] != crc8(readbuffer, 2)) {
#ifdef DEBUG
    Serial.println("********crc error  1*******");
#endif
    return false;
  }

  SRH = readbuffer[3];
  SRH <<= 8;
  SRH |= readbuffer[4];

  if (readbuffer[5] != crc8(readbuffer + 3, 2)) {
#ifdef DEBUG
    Serial.println("********crc error  2*******");
#endif
    return false;
  }
  // Serial.print("ST = "); Serial.println(ST);
  double stemp = ST;
  stemp *= 175;
  stemp /= 0xffff;
  stemp = -45 + stemp;

  //  Serial.print("SRH = "); Serial.println(SRH);
  double shum = SRH;
  shum *= 100;
  shum /= 0xFFFF;

  if ((float) AUSEX_SHT31_SENSOR_TEMPERATURE_MIN_DELAY < timeDiff*1000) {
    oldTemperature = stemp;
  }
  if ((float)AUSEX_SHT31_SENSOR_HUMIDITY_MIN_DELAY < timeDiff*1000) {
    oldHumidity = shum;
  }
#ifdef DEBUG
  Serial.print("Temperature = ");Serial.println(oldTemperature);
  Serial.print("Humidity    = ");Serial.println(oldHumidity);
#endif
  return true;
}

bool AusExSHT31::getTemperature(sensors_event_t* event){
  bool flag=readSHT31();
  event->timestamp = lastTime;
  event->temperature = oldTemperature;
  return flag;
}

bool AusExSHT31::getHumidity(sensors_event_t* event){
  bool flag=readSHT31();
  event->timestamp = lastTime;
  event->relative_humidity = oldHumidity;
  return flag;
}

bool AusExSHT31::Temperature::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->size      = sizeof(sensors_event_t);
  event->sensor_id = _id;
  event->type      = SENSOR_TYPE_AMBIENT_TEMPERATURE;
  bool flag=_parent->getTemperature(event);
  return flag;
}


bool AusExSHT31::Humidity::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->size      = sizeof(sensors_event_t);
  event->sensor_id = _id;
  event->type      = SENSOR_TYPE_RELATIVE_HUMIDITY;
  bool flag=_parent->getHumidity(event);
  return flag;
}

bool AusExSHT31::enableAutoRange(bool enabled) {
  return false;
}

bool AusExSHT31::Temperature::enableAutoRange(bool enabled) {
  return _parent->enableAutoRange(enabled);
}

bool AusExSHT31::Humidity::enableAutoRange(bool enabled) {
  return _parent->enableAutoRange(enabled);
}

int AusExSHT31::setMode(int mode){
  if ((0 > mode) || (1 < mode)) return 0;
  if (mode == 0) {
    writeCommand(SHT31_HEATERDIS);
  } else {
    writeCommand(SHT31_HEATEREN);
  }
  _mode = mode;
  return 1;
}

int AusExSHT31::Temperature::setMode(int mode){
  return _parent->setMode(mode);
}

int AusExSHT31::Humidity::setMode(int mode){
  return _parent->setMode(mode);
}

int AusExSHT31::getMode(void){
  return _mode;
}

int AusExSHT31::Temperature::getMode(void){
  return _parent->getMode();
}

int AusExSHT31::Humidity::getMode(void){
  return _parent->getMode();
}
