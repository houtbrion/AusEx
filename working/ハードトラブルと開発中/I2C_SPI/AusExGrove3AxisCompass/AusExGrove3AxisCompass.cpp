#include "AusExGrove3AxisCompass.h"

/*
 * 
 */
_TEMPLATE_CLASS::_TEMPLATE_CLASS(uint32_t sensorID = -1){
  _i2c_addr=_SENSOR_DEFAULT_I2C_ADDR;
  _sensorID=sensorID;
  m_Scale = 1;
  _autoRange=false;
}

bool _TEMPLATE_CLASS::begin(TwoWire *theWire){
  _i2c_if=theWire;
  _i2c_if->begin();
#if 0
  if (0!= setScale(0.88)) {
    return false;
  }
  return true;
#else /* 0 */
  if (!setScale(1.3)) return false;
  setMeasurementMode(MEASUREMENT_CONTINUOUS);
  return true;
#endif /* 0 */
}

bool _TEMPLATE_CLASS::begin(float range, TwoWire *theWire){
  _i2c_if=theWire;
  _i2c_if->begin();
#if 1
  if (!setScale(range)) return false;
  setMeasurementMode(MEASUREMENT_CONTINUOUS);
  return true;
#else /* 1 */
  if (0!= setScale(range)) {
    return false;
  }
  return true;
#endif /* 1 */
}

bool _TEMPLATE_CLASS::setScale(float gauss)
{
  uint8_t regValue = 0x00;
  if(gauss == 0.88){
    regValue = 0x00;
    m_Scale = 0.73;
    _resolution = _SENSOR_RESOLUTION;
    _max_value = 0.88;
  } else if(gauss == 1.3) {
    regValue = 0x01;
    m_Scale = 0.92;
    _resolution = _SENSOR_RESOLUTION;
    _max_value = 1.3;
  } else if(gauss == 1.9) {
    regValue = 0x02;
    m_Scale = 1.22;
    _resolution = _SENSOR_RESOLUTION;
    _max_value = 1.9;
  } else if(gauss == 2.5) {
    regValue = 0x03;
    m_Scale = 1.52;
    _resolution = _SENSOR_RESOLUTION;
    _max_value = 2.5;
  } else if(gauss == 4.0) {
    regValue = 0x04;
    m_Scale = 2.27;
    _resolution = _SENSOR_RESOLUTION;
    _max_value = 4.0;
  } else if(gauss == 4.7) {
    regValue = 0x05;
    m_Scale = 2.56;
    _resolution = _SENSOR_RESOLUTION;
    _max_value = 4.7;
  } else if(gauss == 5.6) {
    regValue = 0x06;
    m_Scale = 3.03;
    _resolution = _SENSOR_RESOLUTION;
    _max_value = 5.6;
  } else if(gauss == 8.1) {
    regValue = 0x07;
    m_Scale = 4.35;
    _resolution = _SENSOR_RESOLUTION;
    _max_value = 8.1;
  } else
    return false;
  
  // Setting is in the top 3 bits of the register.
  regValue = regValue << 5;
  write(CONFIGURATION_REGISTERB, regValue);
  return true;
}

void _TEMPLATE_CLASS::write(int address, int data)
{
  //_i2c_addr->begin();
  _i2c_if->beginTransmission(_i2c_addr);
  _i2c_if->write(address);   
  _i2c_if->write(data);
  _i2c_if->endTransmission();
}

#if 0
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
#endif /* 0 */

void _TEMPLATE_CLASS::setMeasurementMode(uint8_t mode)
{
  write(MODE_REGISTER, mode);
}

int16_t _TEMPLATE_CLASS::read(int address, int length)
{
  _i2c_if->beginTransmission(_i2c_addr);
  _i2c_if->write(address);
  _i2c_if->endTransmission();
  
  _i2c_if->beginTransmission(_i2c_addr);
  _i2c_if->requestFrom(_i2c_addr, length);

  uint8_t buffer[length];
  if(_i2c_if->available() == length) {
    for(uint8_t i = 0; i < length; i++) {
      buffer[i] = _i2c_if->read();
    }
  }
  _i2c_if->endTransmission();

  return buffer;

}

MagnetometerRaw _TEMPLATE_CLASS::readRawAxis()
{
  uint8_t* buffer = read(DATA_REGISTER_BEGIN, 6);
  MagnetometerRaw raw = MagnetometerRaw();
  raw.XAxis = (buffer[0] << 8) | buffer[1];
  raw.ZAxis = (buffer[2] << 8) | buffer[3];
  raw.YAxis = (buffer[4] << 8) | buffer[5];
  return raw;
}

MagnetometerScaled _TEMPLATE_CLASS::readScaledAxis()
{
  MagnetometerRaw raw = readRawAxis();
  MagnetometerScaled scaled = MagnetometerScaled();
  scaled.XAxis = raw.XAxis * m_Scale;
  scaled.ZAxis = raw.ZAxis * m_Scale;
  scaled.YAxis = raw.YAxis * m_Scale;
  return scaled;
}

float _TEMPLATE_CLASS::checkRange(float val){
  if ((m_Scale==0.73) && (val == 0.88)) {
    return 1.3;
  } else if ((m_Scale==0.92) && (val == 1.3)) {
    return 1.9;
  } else if ((m_Scale==1.22) && (val == 1.9)) {
    return 2.5;
  } else if ((m_Scale==1.52) && (val == 2.5)) {
    return 4.0;
  } else if ((m_Scale==2.27) && (val == 4.0)) {
    return 4.7;
  } else if ((m_Scale==2.56) && (val == 4.7)) {
    return 5.6;
  } else if ((m_Scale==3.03) && (val == 5.6)) {
    return 8.1;
  }
  return 0;
}

bool _TEMPLATE_CLASS::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->version   = sizeof(sensors_event_t);
  event->sensor_id = _sensorID;
  event->type      = _SENSOR_TYPE;
  event->timestamp = millis();
  MagnetometerScaled val;
  val = readScaledAxis();
  event->_SENSOR_RETURN_VALUE.x = val.XAxis;
  event->_SENSOR_RETURN_VALUE.y = val.YAxis;
  event->_SENSOR_RETURN_VALUE.z = val.ZAxis;
  if (_autoRange) {
    float range;
    range=checkRange(val.XAxis);
    if (0!=range) {
      setScale(range);
      return true;
    }
    range=checkRange(val.YAxis);
    if (0!=range) {
      setScale(range);
      return true;
    }
    range=checkRange(val.ZAxis);
    if (0!=range) {
      setScale(range);
      return true;
    }
  }
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
  sensor->min_value   = - _max_value;
  sensor->max_value   = _max_value;
  sensor->resolution  = _resolution;
  sensor->min_delay   = _SENSOR_MIN_DELAY;
}

bool _TEMPLATE_CLASS::enableAutoRange(bool enabled) {
  _autoRange=enabled;
  return true;
}


int _TEMPLATE_CLASS::setMode(int mode) {
  float modeTable[8] = {0.88, 1.3, 1.9, 2.5, 4.0, 4.7, 5.6, 8.1};
  if ((mode < 0) || (mode > 7)) return 0;
  if (SUCCESS != setScale(modeTable[mode])) return 0;
  return 1;
}

#if 0

char* _TEMPLATE_CLASS::getErrorText(int errorCode)
{
  if(ERRORCODE_1_NUM == 1) return ERRORCODE_1;
  return "Error not defined.";
}


_SENSOR_VALUE_TYPE _TEMPLATE_CLASS::calcValue(int val){
  return val;
}
#endif
