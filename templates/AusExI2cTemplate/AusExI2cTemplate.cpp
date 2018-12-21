#include "AusExI2cTemplate.h"

/*
 * 
 */
_TEMPLATE_CLASS::_TEMPLATE_CLASS(uint32_t sensorID = -1){
  _i2c_addr=_SENSOR_DEFAULT_I2C_ADDR;
  _sensorID=sensorID;
}

bool _TEMPLATE_CLASS::begin(TwoWire *theWire){
  _i2c_if=theWire;
  _i2c_if->begin();
}

void _TEMPLATE_CLASS::write(uint8_t _register, uint8_t _data)
{
  //_i2c_addr->begin();
  _i2c_if->beginTransmission(_i2c_addr);
  _i2c_if->write(_register);   
  _i2c_if->write(_data);
  _i2c_if->endTransmission();
}

int8_t _TEMPLATE_CLASS::read(uint8_t _register)
{
  int8_t data;
  _i2c_if->beginTransmission(_i2c_addr);
  _i2c_if->write(_register);
  _i2c_if->endTransmission();
  _i2c_if->requestFrom(_i2c_addr, 1);
  if(_i2c_if->available() > 0){
    data = _i2c_if->read();
  }
  _i2c_if->endTransmission();
  return data;
}

int16_t _TEMPLATE_CLASS::read(uint8_t addressh, uint8_t addressl)
{
  int data, t_data;
  _i2c_if->beginTransmission(_i2c_addr);
  _i2c_if->write(addressh);
  _i2c_if->endTransmission();
  _i2c_if->requestFrom(_i2c_addr, 1);
  if(_i2c_if->available() > 0){
    t_data = _i2c_if->read();
    data = t_data << 8;
  }
  _i2c_if->beginTransmission(_i2c_addr);
  _i2c_if->write(addressl);
  _i2c_if->endTransmission();
  _i2c_if->requestFrom(_i2c_addr, 1);
  if(_i2c_if->available() > 0){
    data |= _i2c_if->read();
  }
  return data;
}


bool _TEMPLATE_CLASS::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->version   = sizeof(sensors_event_t);
  event->sensor_id = _sensorID;
  event->type      = _SENSOR_TYPE;
  event->timestamp = millis();

  /* Calculate the actual lux value */
  event->_SENSOR_RETURN_VALUE = calcValue(0);
  return true;
}

void _TEMPLATE_CLASS::getSensor(sensor_t* sensor){
  /* Clear the sensor_t object */
  memset(sensor, 0, sizeof(sensor_t));

  /* Insert the sensor name in the fixed length char array */
  strncpy (sensor->name, _SENSOR_NAME , sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  sensor->version     = _SENSOR_LIBRARY_VERSION;
  sensor->sensor_id   = _sensorID;
  sensor->type        = _SENSOR_TYPE;
  sensor->min_value   = _SENSOR_MIN_VALUE;
  sensor->max_value   = _SENSOR_MAX_VALUE;
  sensor->resolution  = _SENSOR_RESOLUTION;
  sensor->min_delay   = _SENSOR_MIN_DELAY;
}


bool _TEMPLATE_CLASS::enableAutoRange(bool enabled) {
  return false;
}

int _TEMPLATE_CLASS::setMode(int mode) {
  return -1;
}

_SENSOR_VALUE_TYPE _TEMPLATE_CLASS::calcValue(int val){
  return val;
}
