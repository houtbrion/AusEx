#include "AusExGroveDigitalLightSensorV2.h"

/*
 * 
 */
_TEMPLATE_CLASS::_TEMPLATE_CLASS(uint32_t sensorID = -1){
  _range=DEFAULT_LUX_RANGE_INDEX;
  _integration_time=DEFAULT_INTEGRATION_TIME_INDEX;
  _i2c_addr=_SENSOR_DEFAULT_I2C_ADDR;

  _sensorID=sensorID;
  _adc_count_max[0] = ADC_COUNT_MAX0;
  _adc_count_max[1] = ADC_COUNT_MAX1;
  _adc_count_max[2] = ADC_COUNT_MAX2;
  _adc_count_max[3] = ADC_COUNT_MAX3;

  _intg_time[0] = INTEGRATION_TIME0;
  _intg_time[1] = INTEGRATION_TIME1;
  _intg_time[2] = INTEGRATION_TIME2;
  _intg_time[4] = INTEGRATION_TIME3;

  _ranges[0] = FULL_SCALE_LUX_RANGE0;
  _ranges[1] = FULL_SCALE_LUX_RANGE1;
  _ranges[2] = FULL_SCALE_LUX_RANGE2;
  _ranges[3] = FULL_SCALE_LUX_RANGE3;

  _min_value=0;
  _max_value=_ranges[_range];
  _resolution=0;
  _min_delay=_intg_time[_integration_time];
}

bool _TEMPLATE_CLASS::begin(TwoWire *theWire){
  _i2c_if=theWire;
  _i2c_if->begin();
  int8_t reg=read(CHIP_ID);
  uint8_t chip_id = (reg >> 3) & 0x7;
  if (chip_id != 0x5) return false;
  write(CHIP_ID, reg & 0x7f); //clear the BOUT bit
  write(COMMAND_I, 0); //ensure the chip is under stop mode
  write(COMMAND_II,  _range|(_integration_time<<2)); //set the default full scale lux range, and the integration time
  return true;
}

bool _TEMPLATE_CLASS::setRange(int range_index, int intg_time_index)
{
  if(range_index < 0 || range_index > 3) return false;
  _range = range_index;
  if(intg_time_index < 0 || intg_time_index > 3) return false;
  _integration_time = intg_time_index;
  write(COMMAND_II, _range|(_integration_time<<2));
  _max_value=_ranges[_range];
  _min_delay=_intg_time[_integration_time];
  return true;
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

int16_t _TEMPLATE_CLASS::readLong(uint8_t reg)
{
  uint8_t l,h;
  _i2c_if->beginTransmission(_i2c_addr);
  _i2c_if->write(reg);
  _i2c_if->endTransmission(false);
  _i2c_if->requestFrom(_i2c_addr, 2);
  while(_i2c_if->available()<2);
  l = _i2c_if->read();
  h = _i2c_if->read();
  return (h << 8) | l;
}

uint16_t _TEMPLATE_CLASS::measure(uint8_t what)
{
  //start
  write( COMMAND_I, what);
  float how_long = _intg_time[_integration_time];
  if(how_long < 1.0f)
  {
    delayMicroseconds((int)(how_long * 1000));
  }else
  {
    delay((int)(how_long+1.5f));
  }
  uint16_t data = readLong(DATA_L);
  //stop
  write(COMMAND_I, 0);
  return data;
}

bool _TEMPLATE_CLASS::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->version   = sizeof(sensors_event_t);
  event->sensor_id = _sensorID;
  event->type      = _SENSOR_TYPE;
  event->timestamp = millis();

  event->_SENSOR_RETURN_VALUE = calcValue(measure(OPMODE_ALS_ONCE));
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
  sensor->min_value   = _min_value;
  sensor->max_value   = _max_value;
  sensor->resolution  = _resolution;
  sensor->min_delay   = _min_delay;
}


bool _TEMPLATE_CLASS::enableAutoRange(bool enabled) {
  return false;
}


int _TEMPLATE_CLASS::setMode(int mode) {
  /*
   * mode
   * 0～2 : range_index 0 , intg_time_index == mode
   * 3～5 : range_index 1 , intg_time_index == (mode-3)
   * 6～8 : range_index 2 , intg_time_index == (mode-6)
   */
  if ((mode > 8) || (mode < 0)) return 0;
  int range_index, intg_time_index;
  range_index=int(mode/3);
  intg_time_index=mode % 3;
  if (setRange(range_index, intg_time_index)) {
    return 1;
  } else {
    return 0;
  }
}

_SENSOR_VALUE_TYPE _TEMPLATE_CLASS::calcValue(uint16_t val){
  return _ranges[_range] * val / _adc_count_max[_integration_time];
}
