#include "AusExHTS221.h"

/*
 * 
 */

AusExHTS221::AusExHTS221(TwoWire * theWire,  uint32_t tempSensorId, int32_t humiditySensorId):
  _i2c_if(theWire),
  _temp(this,tempSensorId),
  _humidity(this,humiditySensorId)
{}

AusExHTS221::Temperature::Temperature(AUSEX_HTS221_CLASS * parent, int32_t id):
  _parent(parent),
  _id(id)
{}

AusExHTS221::Humidity::Humidity(AUSEX_HTS221_CLASS * parent, int32_t id):
  _parent(parent),
  _id(id)
{}

bool AusExHTS221::begin(uint32_t addr){
  _i2c_addr=addr;
  _i2c_if->begin();

  if (read8(HTS221_HELLO_REG) != 0xbc) {
    return false;
  }

  // turn on the HTS221 and enable Block Data Update
  if (!write(HTS221_CTRL1_REG, 0x84)) return false;

  // Disable HTS221_DRDY by default and make the output open drain
  if (!write(HTS221_CTRL3_REG, 0x40)) return false;

  if (!calibration()) return false;

  return true;
}

void AusExHTS221::Temperature::getSensor(sensor_t* sensor) {
  // Clear sensor definition.
  memset(sensor, 0, sizeof(sensor_t));
  // Set sensor name.
  strncpy (sensor->name, "HTS221" , sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  // Set version and ID
  sensor->version         = AUSEX_HTS221_SENSOR_LIBRARY_VERSION;
  sensor->sensor_id       = _id;
  // Set type and characteristics.
  sensor->type            = SENSOR_TYPE_AMBIENT_TEMPERATURE;
  sensor->min_delay       = AUSEX_HTS221_SENSOR_TEMPERATURE_MIN_DELAY;
  sensor->max_value       = AUSEX_HTS221_SENSOR_TEMPERATURE_MAX_VALUE;
  sensor->min_value       = AUSEX_HTS221_SENSOR_TEMPERATURE_MIN_VALUE;
  sensor->resolution      = AUSEX_HTS221_SENSOR_TEMPERATURE_RESOLUTION;
  sensor->init_delay      = AUSEX_HTS221_SENSOR_INIT_DELAY;
}

void AusExHTS221::Humidity::getSensor(sensor_t* sensor) {
  // Clear sensor definition.
  memset(sensor, 0, sizeof(sensor_t));
  // Set sensor name.
  strncpy (sensor->name, "HTS221" , sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  // Set version and ID
  sensor->version         = AUSEX_HTS221_SENSOR_LIBRARY_VERSION;
  sensor->sensor_id       = _id;
  // Set type and characteristics.
  sensor->type            = SENSOR_TYPE_RELATIVE_HUMIDITY;
  sensor->min_delay       = AUSEX_HTS221_SENSOR_HUMIDITY_MIN_DELAY;
  sensor->max_value       = AUSEX_HTS221_SENSOR_HUMIDITY_MAX_VALUE;
  sensor->min_value       = AUSEX_HTS221_SENSOR_HUMIDITY_MIN_VALUE;
  sensor->resolution      = AUSEX_HTS221_SENSOR_HUMIDITY_RESOLUTION;
  sensor->init_delay      = AUSEX_HTS221_SENSOR_INIT_DELAY;
}

bool AusExHTS221::getTemperature(sensors_event_t* event){

  // Wait for ONE_SHOT bit to be cleared by the hardware
  while (read8(HTS221_CTRL2_REG) & 0x01);

  // trigger one shot
  if (!write(HTS221_CTRL2_REG, 0x01)) return false;

  // wait for completion
  while ((read8(HTS221_STATUS_REG) & 0x01) == 0) {
    yield();
  }

  // read value and convert
  int val = read16(HTS221_TEMP_OUT_L_REG);
  if (val < 0) return false;

  event->temperature = (float) (val * _temperatureSlope + _temperatureZero);

  return true;
}

bool AusExHTS221::getHumidity(sensors_event_t* event){

  //Wait for ONE_SHOT bit to be cleared by the hardware
  while (read8(HTS221_CTRL2_REG) & 0x01);

  // trigger one shot
  if (!write(HTS221_CTRL2_REG, 0x01)) return false;

  // wait for completion
  while ((read8(HTS221_STATUS_REG) & 0x02) == 0) {
    yield();
  }

  // read value and convert
  int16_t val = (int16_t) read16(HTS221_HUMIDITY_OUT_L_REG);

  event->relative_humidity = (float) (val * _humiditySlope + _humidityZero);

  return true;
}

bool AusExHTS221::Temperature::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->size      = sizeof(sensors_event_t);
  event->sensor_id = _id;
  event->type      = SENSOR_TYPE_AMBIENT_TEMPERATURE;
  event->timestamp = millis();
  bool flag=_parent->getTemperature(event);
  return flag;
}

bool AusExHTS221::Humidity::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->size      = sizeof(sensors_event_t);
  event->sensor_id = _id;
  event->type      = SENSOR_TYPE_RELATIVE_HUMIDITY;
  event->timestamp = millis();
  bool flag=_parent->getHumidity(event);
  return flag;
}

bool AusExHTS221::enableAutoRange(bool enabled) {
  return false;
}

bool AusExHTS221::Temperature::enableAutoRange(bool enabled) {
  return _parent->enableAutoRange(enabled);
}

bool AusExHTS221::Humidity::enableAutoRange(bool enabled) {
  return _parent->enableAutoRange(enabled);
}

int AusExHTS221::setMode(int mode){
  return -1;
}

int AusExHTS221::Temperature::setMode(int mode){
  return _parent->setMode(mode);
}

int AusExHTS221::Humidity::setMode(int mode){
  return _parent->setMode(mode);
}

int AusExHTS221::getMode(void){
  return -1;
}

int AusExHTS221::Temperature::getMode(void){
  return _parent->getMode();
}

int AusExHTS221::Humidity::getMode(void){
  return _parent->getMode();
}

int AusExHTS221::read8(uint8_t reg){
  uint8_t value;
  _i2c_if->beginTransmission(_i2c_addr);
  #if ARDUINO >= 100
    _i2c_if->write(reg);
  #else
    _i2c_if->send(reg);
  #endif
  if (_i2c_if->endTransmission(false) != 0) {
    return -1;
  }
  if (_i2c_if->requestFrom(_i2c_addr, (byte)1) != 1) {
    return -1;
  }
  #if ARDUINO >= 100
    value = _i2c_if->read();
  #else
    value = _i2c_if->receive();
  #endif  
  _i2c_if->endTransmission();
  return (int) value;
}

int AusExHTS221::read16(uint8_t reg){
  int first = read8(reg);
  if (first < 0 ) return first;
  int second = read8(reg + 1);
  if (second < 0 ) return second;

  return (first | (second << 8));
}

bool AusExHTS221::write(uint8_t reg, uint8_t val){
  _i2c_if->beginTransmission(_i2c_addr);
  #if ARDUINO >= 100
    _i2c_if->write(reg);
    _i2c_if->write(val);
  #else
    _i2c_if->send(reg);
    _i2c_if->send(val);
  #endif
  if (_i2c_if->endTransmission() != 0) {
    return false;
  }
  return true;
}

bool AusExHTS221::calibration(void) {
  int val = read8(HTS221_H0_rH_x2_REG);
  if (val < 0 ) return false;
  uint8_t h0rH = (uint8_t) val;

  val = read8(HTS221_H1_rH_x2_REG);
  if (val < 0 ) return false;
  uint8_t h1rH = (uint8_t) val;

  int val1 = read8(HTS221_T0_degC_x8_REG);
  int val2 = read8(HTS221_T1_T0_MSB_REG);
  if ((val1 < 0) || (val2 < 0)) return false;
  uint16_t t0degC = val1 | ((val2 & 0x03) << 8);

  val1 = read8(HTS221_T1_degC_x8_REG);
  val2 = read8(HTS221_T1_T0_MSB_REG);
  if ((val1 < 0) || (val2 < 0)) return false;
  uint16_t t1degC = val1 | ((val2 & 0x0c) << 6);

  val = read16(HTS221_H0_T0_OUT_REG);
  if (val < 0 ) return false;
  int16_t h0t0Out = (uint16_t) val;

  val = read16(HTS221_H1_T0_OUT_REG);
  if (val < 0 ) return false;
  int16_t h1t0Out = (uint16_t) val;

  val = read16(HTS221_T0_OUT_REG);
  if (val < 0 ) return false;
  int16_t t0Out = (uint16_t) val;

  val = read16(HTS221_T1_OUT_REG);
  if (val < 0 ) return false;
  int16_t t1Out = (uint16_t) val;

  _humiditySlope = (h1rH - h0rH) / (2.0 * (h1t0Out - h0t0Out));
  _humidityZero = (h0rH / 2.0) - _humiditySlope * h0t0Out;

  _temperatureSlope = (t1degC - t0degC) / (8.0 * (t1Out - t0Out));
  _temperatureZero = (t0degC / 8.0) - _temperatureSlope * t0Out;

  return true;
}