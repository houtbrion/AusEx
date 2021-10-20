#include "AusExSHT2x.h"

/*
 * 
 */

AusExSHT2x::AusExSHT2x(TwoWire * theWire ,uint32_t am232xType,  int32_t tempSensorId, int32_t humiditySensorId):
  _i2c_if(theWire),
  _type(am232xType),
  _temp(this,tempSensorId),
  _humidity(this,humiditySensorId)
{}



AusExSHT2x::Temperature::Temperature(AUSEX_SHT2X_CLASS * parent, int32_t id):
  _parent(parent),
  _id(id)
{}

AusExSHT2x::Humidity::Humidity(AUSEX_SHT2X_CLASS * parent, int32_t id):
  _parent(parent),
  _id(id)
{}

bool AusExSHT2x::begin(uint32_t addr){
  if ((_type != 0 ) && (_type != 1)) return false;
  lastTime=millis();
  oldTemperature=NO_MEASURE;
  oldHumidity=NO_MEASURE;
  _i2c_addr=addr;
  _i2c_if->begin();
  resetSHT2x();
  return true;
}

void AusExSHT2x::Temperature::getSensor(sensor_t* sensor) {
  // Clear sensor definition.
  memset(sensor, 0, sizeof(sensor_t));
  // Set sensor name.
  switch(_parent->_type){
    case 0:strncpy (sensor->name, "SHT21" , sizeof(sensor->name) - 1);break;
    default:strncpy (sensor->name, AUSEX_SHT2X_SENSOR_NAME , sizeof(sensor->name) - 1);break;
  }
  sensor->name[sizeof(sensor->name)- 1] = 0;
  // Set version and ID
  sensor->version         = AUSEX_SHT2X_SENSOR_LIBRARY_VERSION;
  sensor->sensor_id       = _id;
  // Set type and characteristics.
  sensor->type            = SENSOR_TYPE_AMBIENT_TEMPERATURE;
  sensor->min_delay       = AUSEX_SHT2X_SENSOR_TEMPERATURE_MIN_DELAY;
  sensor->max_value       = AUSEX_SHT2X_SENSOR_TEMPERATURE_MAX_VALUE;
  sensor->min_value       = AUSEX_SHT2X_SENSOR_TEMPERATURE_MIN_VALUE;
  sensor->resolution      = AUSEX_SHT2X_SENSOR_TEMPERATURE_RESOLUTION;
  sensor->init_delay      = AUSEX_SHT2X_SENSOR_INIT_DELAY;
}

void AusExSHT2x::Humidity::getSensor(sensor_t* sensor) {
  // Clear sensor definition.
  memset(sensor, 0, sizeof(sensor_t));
  // Set sensor name.
  switch(_parent->_type){
    case 0:strncpy (sensor->name, "SHT21" , sizeof(sensor->name) - 1);break;
    case 1:strncpy (sensor->name, AUSEX_SHT2X_SENSOR_NAME , sizeof(sensor->name) - 1);break;
  }
  sensor->name[sizeof(sensor->name)- 1] = 0;
  // Set version and ID
  sensor->version         = AUSEX_SHT2X_SENSOR_LIBRARY_VERSION;
  sensor->sensor_id       = _id;
  // Set type and characteristics.
  sensor->type            = SENSOR_TYPE_RELATIVE_HUMIDITY;
  sensor->min_delay       = AUSEX_SHT2X_SENSOR_HUMIDITY_MIN_DELAY;
  sensor->max_value       = AUSEX_SHT2X_SENSOR_HUMIDITY_MAX_VALUE;
  sensor->min_value       = AUSEX_SHT2X_SENSOR_HUMIDITY_MIN_VALUE;
  sensor->resolution      = AUSEX_SHT2X_SENSOR_HUMIDITY_RESOLUTION;
  sensor->init_delay      = AUSEX_SHT2X_SENSOR_INIT_DELAY;
}

bool AusExSHT2x::readSHT2x(uint16_t * st, uint16_t * srh) {
  lastTime=millis();
  uint8_t msb, lsb, chk;  // 生データ
  // 気温データ取得
  //step1
  _i2c_if->beginTransmission(_i2c_addr);
  _i2c_if->write(SHT2X_READ_TEMP);
  _i2c_if->endTransmission();
  //step2
  _i2c_if->requestFrom((uint8_t)_i2c_addr,(uint8_t) 3);
  while (!_i2c_if->available()){}
  msb = _i2c_if->read();
  lsb = _i2c_if->read();
  chk = _i2c_if->read();
  //*st = msb << 8 | lsb;
  *st = (msb)*256+lsb;
  // 湿度データ取得
  //step1
  _i2c_if->beginTransmission(_i2c_addr);
  _i2c_if->write(SHT2X_READ_HUMI);
  _i2c_if->endTransmission();
  //step2
  _i2c_if->requestFrom((uint8_t)_i2c_addr,(uint8_t)3);
  while (!_i2c_if->available()){}
  msb = _i2c_if->read();
  lsb = _i2c_if->read();
  chk = _i2c_if->read();
  *srh = (msb)*256+lsb;
  return true;
}

bool AusExSHT2x::getTemperature(sensors_event_t* event){
  float timeDiff = millis()- lastTime;
  if (AUSEX_SHT2X_SENSOR_TEMPERATURE_MIN_DELAY > timeDiff*1000) {
    event->timestamp = lastTime;
    event->temperature = oldTemperature;
    if (oldTemperature==NO_MEASURE) return false;
    return true;
  }
  uint16_t tmp,hum;
  if (!readSHT2x(&tmp,&hum)) return false;
  oldTemperature=(float) -46.85 + 175.72 * (float)tmp / (16.0 * 16.0 * 16.0 * 16.0);
  event->timestamp = lastTime;
  event->temperature = oldTemperature;
  if (AUSEX_SHT2X_SENSOR_HUMIDITY_MIN_DELAY <= timeDiff*1000) {
    oldHumidity=(float) -6.0 + 125.0 * (float)hum / (16.0 * 16.0 * 16.0 * 16.0);
  }
  return true;
}

bool AusExSHT2x::getHumidity(sensors_event_t* event){
  float timeDiff = millis()- lastTime;
  if (AUSEX_SHT2X_SENSOR_HUMIDITY_MIN_DELAY > timeDiff*1000) {
    event->timestamp = lastTime;
    event->relative_humidity = oldHumidity;
    if (oldHumidity==NO_MEASURE) return false;
    return true;
  }
  uint16_t tmp,hum;
  if (!readSHT2x(&tmp,&hum)) return false;
  oldHumidity=(float) (float) -6.0 + 125.0 * (float)hum / (16.0 * 16.0 * 16.0 * 16.0);
  event->timestamp = lastTime;
  event->relative_humidity = oldHumidity;
  if (AUSEX_SHT2X_SENSOR_TEMPERATURE_MIN_DELAY <= timeDiff*1000) {
    oldTemperature=(float) -46.85 + 175.72 * (float)tmp / (16.0 * 16.0 * 16.0 * 16.0);
  }
  return true;
}

bool AusExSHT2x::Temperature::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->size      = sizeof(sensors_event_t);
  event->sensor_id = _id;
  event->type      = SENSOR_TYPE_AMBIENT_TEMPERATURE;
  bool flag=_parent->getTemperature(event);
  return flag;
}

bool AusExSHT2x::Humidity::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->size      = sizeof(sensors_event_t);
  event->sensor_id = _id;
  event->type      = SENSOR_TYPE_RELATIVE_HUMIDITY;
  bool flag=_parent->getHumidity(event);
  return flag;
}

bool AusExSHT2x::enableAutoRange(bool enabled) {
  return false;
}

bool AusExSHT2x::Temperature::enableAutoRange(bool enabled) {
  return _parent->enableAutoRange(enabled);
}

bool AusExSHT2x::Humidity::enableAutoRange(bool enabled) {
  return _parent->enableAutoRange(enabled);
}

int AusExSHT2x::setMode(int mode){
  return -1;
}

int AusExSHT2x::Temperature::setMode(int mode){
  return _parent->setMode(mode);
}

int AusExSHT2x::Humidity::setMode(int mode){
  return _parent->setMode(mode);
}

int AusExSHT2x::getMode(void){
  return -1;
}

int AusExSHT2x::Temperature::getMode(void){
  return _parent->getMode();
}

int AusExSHT2x::Humidity::getMode(void){
  return _parent->getMode();
}

void AusExSHT2x::resetSHT2x(void){
  _i2c_if->beginTransmission(_i2c_addr);
  _i2c_if->write(SHT2X_SOFT_RESET);
  _i2c_if->endTransmission();
}
