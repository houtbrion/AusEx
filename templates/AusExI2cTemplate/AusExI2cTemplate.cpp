#include "AusExI2cTemplate.h"

/*
 * 
 */
AUSEX_I2C_TEMPLATE_CLASS::AUSEX_I2C_TEMPLATE_CLASS(TwoWire *theWire, int32_t sensorID = -1){
  _i2c_if=theWire;
  //_i2c_addr=AUSEX_I2C_TEMPLATE_SENSOR_DEFAULT_I2C_ADDR;
  _sensorID=sensorID;
}

bool AUSEX_I2C_TEMPLATE_CLASS::begin(uint32_t addr){
  _i2c_addr=addr;
  _i2c_if->begin();
  return true;
}

void AUSEX_I2C_TEMPLATE_CLASS::write(uint8_t _register, uint8_t _data)
{
  //_i2c_addr->begin();
  _i2c_if->beginTransmission(_i2c_addr);
  _i2c_if->write(_register);   
  _i2c_if->write(_data);
  _i2c_if->endTransmission();
}

int8_t AUSEX_I2C_TEMPLATE_CLASS::read(uint8_t _register)
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

int16_t AUSEX_I2C_TEMPLATE_CLASS::read(uint8_t addressh, uint8_t addressl)
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


bool AUSEX_I2C_TEMPLATE_CLASS::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->version   = sizeof(sensors_event_t);
  event->sensor_id = _sensorID;
  event->type      = AUSEX_I2C_TEMPLATE_SENSOR_TYPE;
  event->timestamp = millis();

  /* Calculate the actual lux value */
  event->AUSEX_I2C_TEMPLATE_SENSOR_RETURN_VALUE = calcValue(0);
  return true;
}

void AUSEX_I2C_TEMPLATE_CLASS::getSensor(sensor_t* sensor){
  /* Clear the sensor_t object */
  memset(sensor, 0, sizeof(sensor_t));

  /* Insert the sensor name in the fixed length char array */
  strncpy (sensor->name, AUSEX_I2C_TEMPLATE_SENSOR_NAME , sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  sensor->version     = AUSEX_I2C_TEMPLATE_SENSOR_LIBRARY_VERSION;
  sensor->sensor_id   = _sensorID;
  sensor->type        = AUSEX_I2C_TEMPLATE_SENSOR_TYPE;
  sensor->min_value   = AUSEX_I2C_TEMPLATE_SENSOR_MIN_VALUE;
  sensor->max_value   = AUSEX_I2C_TEMPLATE_SENSOR_MAX_VALUE;
  sensor->resolution  = AUSEX_I2C_TEMPLATE_SENSOR_RESOLUTION;
  sensor->min_delay   = AUSEX_I2C_TEMPLATE_SENSOR_MIN_DELAY;
}


bool AUSEX_I2C_TEMPLATE_CLASS::enableAutoRange(bool enabled) {
  return false;
}

int AUSEX_I2C_TEMPLATE_CLASS::setMode(int mode) {
  return -1;
}

int AUSEX_I2C_TEMPLATE_CLASS::getMode() {
  return -1;
}

AUSEX_I2C_TEMPLATE_SENSOR_VALUE_TYPE AUSEX_I2C_TEMPLATE_CLASS::calcValue(int val){
  return val;
}
