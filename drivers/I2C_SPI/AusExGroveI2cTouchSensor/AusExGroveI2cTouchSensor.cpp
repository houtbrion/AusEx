#include "AusExGroveI2cTouchSensor.h"

/*
 * 
 */
_TEMPLATE_CLASS::_TEMPLATE_CLASS(int32_t sensorID ){
  _i2c_addr=_SENSOR_DEFAULT_I2C_ADDR;
  _sensorID=sensorID;
}

bool _TEMPLATE_CLASS::begin(TwoWire *theWire){
  _i2c_if=theWire;
  _i2c_if->begin();
  mpr121Setup();
}

void _TEMPLATE_CLASS::mpr121Setup() {
  // Section A - Controls filtering when data is > baseline.
  write(MHD_R, 0x01);
  write(NHD_R, 0x01);
  write(NCL_R, 0x00);
  write(FDL_R, 0x00);
  // Section B - Controls filtering when data is < baseline.
  write(MHD_F, 0x01);
  write(NHD_F, 0x01);
  write(NCL_F, 0xFF);
  write(FDL_F, 0x02);
  // Section C - Sets touch and release thresholds for each electrode
  write(ELE0_T, TOU_THRESH);
  write(ELE0_R, REL_THRESH);
  write(ELE1_T, TOU_THRESH);
  write(ELE1_R, REL_THRESH);
  write(ELE2_T, TOU_THRESH);
  write(ELE2_R, REL_THRESH);
  write(ELE3_T, TOU_THRESH);
  write(ELE3_R, REL_THRESH);  
  write(ELE4_T, TOU_THRESH);
  write(ELE4_R, REL_THRESH);
  write(ELE5_T, TOU_THRESH);
  write(ELE5_R, REL_THRESH);
  write(ELE6_T, TOU_THRESH);
  write(ELE6_R, REL_THRESH);
  write(ELE7_T, TOU_THRESH);
  write(ELE7_R, REL_THRESH);
  write(ELE8_T, TOU_THRESH);
  write(ELE8_R, REL_THRESH);
  write(ELE9_T, TOU_THRESH);
  write(ELE9_R, REL_THRESH);
  write(ELE10_T, TOU_THRESH);
  write(ELE10_R, REL_THRESH);
  write(ELE11_T, TOU_THRESH);
  write(ELE11_R, REL_THRESH);
  // Section D
  // Set the Filter Configuration
  // Set ESI2
  write(FIL_CFG, 0x04);
  //set_register(0x5A,ATO_CFGU, 0xC9);  // USL = (Vdd-0.7)/vdd*256 = 0xC9 @3.3V   mpr121Write(ATO_CFGL, 0x82);  // LSL = 0.65*USL = 0x82 @3.3V
  //set_register(0x5A,ATO_CFGL, 0x82);  // Target = 0.9*USL = 0xB5 @3.3V
  //set_register(0x5A,ATO_CFGT,0xb5);
  //set_register(0x5A,ATO_CFG0, 0x1B);
  // Section E
  // Electrode Configuration
  // Set ELE_CFG to 0x00 to return to standby mode
  write(ELE_CFG, 0x0C);  // Enables all 12 Electrodes
  // Section F
  // Enable Auto Config and auto Reconfig
  //write(ATO_CFG0, 0x0B);
  //write(ATO_CFGU, 0xC9);  // USL = (Vdd-0.7)/vdd*256 = 0xC9 @3.3V
  //write(ATO_CFGL, 0x82);  // LSL = 0.65*USL = 0x82 @3.3V
  //write(ATO_CFGT, 0xB5);  // Target = 0.9*USL = 0xB5 @3.3V
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

int16_t _TEMPLATE_CLASS::readLong()
{
  uint8_t l,h;
  _i2c_if->requestFrom(_i2c_addr, 2);
  l = _i2c_if->read();
  h = _i2c_if->read();
  return (h << 8) | l;
}

bool _TEMPLATE_CLASS::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->version   = sizeof(sensors_event_t);
  event->sensor_id = _sensorID;
  event->type      = _SENSOR_TYPE;
  event->timestamp = millis();

  /* Calculate the actual lux value */
  event->_SENSOR_RETURN_VALUE = readLong();
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

bool _TEMPLATE_CLASS::getTouchState(_SENSOR_VALUE_TYPE val, uint8_t num){
  if(val & (1<<num)) return true;
  return false;
}

