#include "AusExLPS22HB.h"

/*
 * 
 */
AUSEX_LPS22HB_CLASS::AUSEX_LPS22HB_CLASS(TwoWire *theWire, int32_t sensorID){
  _i2c_if=theWire;
  _sensorID=sensorID;
  _mode = AUSEX_LPS22HB_MODE_KPA;
}

bool AUSEX_LPS22HB_CLASS::begin(uint32_t addr){
  _i2c_addr=addr;
  _i2c_if->begin();
  if (read(AUSEX_LPS22HB_HELLO_REG) != 0xb1) {
    return false;
  }
  return true;
}

void AUSEX_LPS22HB_CLASS::write(uint8_t _register, uint8_t _data)
{
  //_i2c_addr->begin();
  _i2c_if->beginTransmission(_i2c_addr);
  _i2c_if->write(_register);   
  _i2c_if->write(_data);
  _i2c_if->endTransmission();
}

int8_t AUSEX_LPS22HB_CLASS::read(uint8_t _register)
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

int16_t AUSEX_LPS22HB_CLASS::read(uint8_t addressh, uint8_t addressl)
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


bool AUSEX_LPS22HB_CLASS::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->size   = sizeof(sensors_event_t);
  event->sensor_id = _sensorID;
  event->type      = AUSEX_LPS22HB_SENSOR_TYPE;
  event->timestamp = millis();

  write(AUSEX_LPS22HB_CTRL2_REG,0x01);
  while ((read(AUSEX_LPS22HB_CTRL2_REG) & 0x01) != 0) {
    yield();
  }

  uint8_t xl_reg = read(AUSEX_LPS22HB_PRESS_OUT_XL_REG);
  uint8_t  l_reg = read(AUSEX_LPS22HB_PRESS_OUT_L_REG);
  uint8_t  h_reg = read(AUSEX_LPS22HB_PRESS_OUT_H_REG);
  float val = (xl_reg | (l_reg << 8 ) | (h_reg <<16))/40960.0;
  /* Calculate the actual lux value */
  event->AUSEX_LPS22HB_SENSOR_RETURN_VALUE = calcValue(val);
  return true;
}

void AUSEX_LPS22HB_CLASS::getSensor(sensor_t* sensor){
  /* Clear the sensor_t object */
  memset(sensor, 0, sizeof(sensor_t));

  /* Insert the sensor name in the fixed length char array */
  strncpy (sensor->name, AUSEX_LPS22HB_SENSOR_NAME , sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  sensor->version     = AUSEX_LPS22HB_SENSOR_LIBRARY_VERSION;
  sensor->sensor_id   = _sensorID;
  sensor->type        = AUSEX_LPS22HB_SENSOR_TYPE;
  sensor->min_value   = AUSEX_LPS22HB_SENSOR_MIN_VALUE;
  sensor->max_value   = AUSEX_LPS22HB_SENSOR_MAX_VALUE;
  sensor->resolution  = AUSEX_LPS22HB_SENSOR_RESOLUTION;
  sensor->min_delay   = AUSEX_LPS22HB_SENSOR_MIN_DELAY;
  sensor->init_delay   = AUSEX_LPS22HB_SENSOR_INIT_DELAY;
}


bool AUSEX_LPS22HB_CLASS::enableAutoRange(bool enabled) {
  return false;
}

int AUSEX_LPS22HB_CLASS::setMode(int mode) {
  switch(mode) {
    case AUSEX_LPS22HB_MODE_KPA:
    case AUSEX_LPS22HB_MODE_HPA:
    case AUSEX_LPS22HB_MODE_PAI:
    case AUSEX_LPS22HB_MODE_MBAR:
      _mode = mode;
      return 0;
  }
  return -1;
}

int AUSEX_LPS22HB_CLASS::getMode() {
  return _mode;
}

AUSEX_LPS22HB_SENSOR_VALUE_TYPE AUSEX_LPS22HB_CLASS::calcValue(AUSEX_LPS22HB_SENSOR_VALUE_TYPE val){
  switch(_mode) {
    case AUSEX_LPS22HB_MODE_KPA: return val;
    case AUSEX_LPS22HB_MODE_HPA: return val*10;
    case AUSEX_LPS22HB_MODE_PAI: return val*0.145038;
    case AUSEX_LPS22HB_MODE_MBAR: return val*10;
  }
  return -1;
}
