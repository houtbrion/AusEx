#include "AusExAM232X.h"

/*
 * 
 */

AusExAM232X::AusExAM232X(TwoWire * theWire ,uint8_t am232xType,  int32_t tempSensorId, int32_t humiditySensorId):
  _i2c_if(theWire),
  _type(am232xType),
  _temp(this,tempSensorId),
  _humidity(this,humiditySensorId)
{}



AusExAM232X::Temperature::Temperature(AUSEX_AM232X_CLASS * parent, int32_t id):
  _parent(parent),
  _id(id)
{}

AusExAM232X::Humidity::Humidity(AUSEX_AM232X_CLASS * parent, int32_t id):
  _parent(parent),
  _id(id)
{}

bool AusExAM232X::begin(uint32_t addr){
  if ((_type != 0 ) && (_type != 1)) return false;
  lastTime=millis();
  oldTemperature=NO_MEASURE;
  oldHumidity=NO_MEASURE;
  _i2c_addr=addr;
  _i2c_if->begin();
  return true;
}

void AusExAM232X::Temperature::getSensor(sensor_t* sensor) {
  // Clear sensor definition.
  memset(sensor, 0, sizeof(sensor_t));
  // Set sensor name.
  switch(_parent->_type){
    case 0:strncpy (sensor->name, "AM2321" , sizeof(sensor->name) - 1);break;
    case 1:strncpy (sensor->name, "AM2322" , sizeof(sensor->name) - 1);break;
  }
  sensor->name[sizeof(sensor->name)- 1] = 0;
  // Set version and ID
  sensor->version         = AUSEX_AM232X_SENSOR_LIBRARY_VERSION;
  sensor->sensor_id       = _id;
  // Set type and characteristics.
  sensor->type            = SENSOR_TYPE_AMBIENT_TEMPERATURE;
  sensor->min_delay       = AUSEX_AM232X_SENSOR_TEMPERATURE_MIN_DELAY;
  sensor->max_value       = AUSEX_AM232X_SENSOR_TEMPERATURE_MAX_VALUE;
  sensor->min_value       = AUSEX_AM232X_SENSOR_TEMPERATURE_MIN_VALUE;
  sensor->resolution      = AUSEX_AM232X_SENSOR_TEMPERATURE_RESOLUTION;
  sensor->init_delay      = AUSEX_AM232X_SENSOR_INIT_DELAY;
}

void AusExAM232X::Humidity::getSensor(sensor_t* sensor) {
  // Clear sensor definition.
  memset(sensor, 0, sizeof(sensor_t));
  // Set sensor name.
  switch(_parent->_type){
    case 0:strncpy (sensor->name, "AM2321" , sizeof(sensor->name) - 1);break;
    case 1:strncpy (sensor->name, "AM2322" , sizeof(sensor->name) - 1);break;
  }
  sensor->name[sizeof(sensor->name)- 1] = 0;
  // Set version and ID
  sensor->version         = AUSEX_AM232X_SENSOR_LIBRARY_VERSION;
  sensor->sensor_id       = _id;
  // Set type and characteristics.
  sensor->type            = SENSOR_TYPE_RELATIVE_HUMIDITY;
  sensor->min_delay       = AUSEX_AM232X_SENSOR_HUMIDITY_MIN_DELAY;
  sensor->max_value       = AUSEX_AM232X_SENSOR_HUMIDITY_MAX_VALUE;
  sensor->min_value       = AUSEX_AM232X_SENSOR_HUMIDITY_MIN_VALUE;
  sensor->resolution      = AUSEX_AM232X_SENSOR_HUMIDITY_RESOLUTION;
  sensor->init_delay      = AUSEX_AM232X_SENSOR_INIT_DELAY;
}

void AusExAM232X::readAM232X(byte *rdptr, byte length) {
  lastTime=millis();
  //step1
  _i2c_if->beginTransmission(_i2c_addr);
  _i2c_if->write(0x00);
  _i2c_if->endTransmission();
  delay(AM2321_I2C_WAIT1);
  //step2
  _i2c_if->beginTransmission(_i2c_addr);
  _i2c_if->write(0x03);
  _i2c_if->write(0x00);
  _i2c_if->write(0x04);
  _i2c_if->endTransmission();
  delay(AM2321_I2C_WAIT2);
  //step3
  _i2c_if->requestFrom((byte)_i2c_addr,length);
  delayMicroseconds(AM2321_I2C_WAIT_MICRO);
  if(length <= _i2c_if->available()) {
    for(int i=0;i<length;i++) {
      rdptr[i] = _i2c_if->read();
    }
  }
}

bool AusExAM232X::getTemperature(sensors_event_t* event){
  float timeDiff = millis()- lastTime;
  if (AUSEX_AM232X_SENSOR_TEMPERATURE_MIN_DELAY > timeDiff*1000) {
    event->timestamp = lastTime;
    event->temperature = oldTemperature;
    return true;
  }
  readAM232X(rdptr,8);
  oldTemperature=(float) (rdptr[4]*256+rdptr[5])/10.0;
  event->timestamp = lastTime;
  event->temperature = oldTemperature;
  if (AUSEX_AM232X_SENSOR_HUMIDITY_MIN_DELAY <= timeDiff*1000) {
    oldHumidity=(float) (rdptr[2]*256+rdptr[3])/10.0;
  }
  return true;
}

bool AusExAM232X::getHumidity(sensors_event_t* event){
  float timeDiff = millis()- lastTime;
  if (AUSEX_AM232X_SENSOR_HUMIDITY_MIN_DELAY > timeDiff*1000) {
    event->timestamp = lastTime;
    event->relative_humidity = oldHumidity;
    return true;
  }
  readAM232X(rdptr,8);
  oldHumidity=(float) (rdptr[2]*256+rdptr[3])/10.0;
  event->timestamp = lastTime;
  event->relative_humidity = oldHumidity;
  if (AUSEX_AM232X_SENSOR_TEMPERATURE_MIN_DELAY <= timeDiff*1000) {
    oldTemperature=(float) (rdptr[4]*256+rdptr[5])/10.0;
  }
  return true;
}

bool AusExAM232X::Temperature::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->version   = sizeof(sensors_event_t);
  event->sensor_id = _id;
  event->type      = SENSOR_TYPE_AMBIENT_TEMPERATURE;
  bool flag=_parent->getTemperature(event);
  return flag;
}

bool AusExAM232X::Humidity::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->version   = sizeof(sensors_event_t);
  event->sensor_id = _id;
  event->type      = SENSOR_TYPE_RELATIVE_HUMIDITY;
  bool flag=_parent->getHumidity(event);
  return flag;
}

bool AusExAM232X::enableAutoRange(bool enabled) {
  return false;
}

bool AusExAM232X::Temperature::enableAutoRange(bool enabled) {
  return _parent->enableAutoRange(enabled);
}

bool AusExAM232X::Humidity::enableAutoRange(bool enabled) {
  return _parent->enableAutoRange(enabled);
}

int AusExAM232X::setMode(int mode){
  return -1;
}

int AusExAM232X::Temperature::setMode(int mode){
  return _parent->setMode(mode);
}

int AusExAM232X::Humidity::setMode(int mode){
  return _parent->setMode(mode);
}

int AusExAM232X::getMode(void){
  return -1;
}

int AusExAM232X::Temperature::getMode(void){
  return _parent->getMode();
}

int AusExAM232X::Humidity::getMode(void){
  return _parent->getMode();
}
