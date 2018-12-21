#include "AusExGrove3AxisDigitalGyro.h"

/*
 * 
 */
_TEMPLATE_CLASS::_TEMPLATE_CLASS(int32_t sensorID ){
  _i2c_addr=GYRO_ADDRESS;
  _sensorID=sensorID;
  _x_offset=0;
  _y_offset=0;
  _z_offset=0;
  _times=0;
  _wait=0;
}
_TEMPLATE_CLASS::_TEMPLATE_CLASS(unsigned int samples,  unsigned int sampleDelayMS, int32_t sensorID ){
  _i2c_addr=GYRO_ADDRESS;
  _sensorID=sensorID;
  _times=samples;
  _wait=sampleDelayMS;
  _x_offset=0;
  _y_offset=0;
  _z_offset=0;
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



void _TEMPLATE_CLASS::zeroCalibrate(unsigned int samples, unsigned int sampleDelayMS) 
{
  int16_t x_offset_temp = 0;
  int16_t y_offset_temp = 0;
  int16_t z_offset_temp = 0;
  int16_t x,y,z;
  _x_offset = 0;
  _y_offset = 0;
  _z_offset = 0;
  getXYZ(&x,&y,&z);//
  for (int i = 0;i < samples;i++){
    delay(sampleDelayMS);
    getXYZ(&x,&y,&z);
    x_offset_temp += x;
    y_offset_temp += y;
    z_offset_temp += z;
  }

  _x_offset = abs(x_offset_temp)/samples;
  _y_offset = abs(y_offset_temp)/samples;
  _z_offset = abs(z_offset_temp)/samples;
  if(x_offset_temp > 0)_x_offset = -_x_offset;
  if(y_offset_temp > 0)_y_offset = -_y_offset;
  if(z_offset_temp > 0)_z_offset = -_z_offset;
}


void _TEMPLATE_CLASS::write(uint8_t _register, uint8_t _data)
{
  //_i2c_addr->begin();
  _i2c_if->beginTransmission(_i2c_addr);
  _i2c_if->write(_register);   
  _i2c_if->write(_data);
  _i2c_if->endTransmission();
}

bool _TEMPLATE_CLASS::begin(TwoWire *theWire){
  _i2c_if=theWire;
  _i2c_if->begin();
  write(ITG3200_PWR_M,0x80);//send a reset to the device
  write(ITG3200_SMPL,0x00);//sample rate divider
  write(ITG3200_DLPF,0x18);//+/-2000 degrees/s (default value)
  if (_times >0 ) zeroCalibrate(_times, _wait);
}


void _TEMPLATE_CLASS::getXYZ(int16_t *x,int16_t *y,int16_t *z)
{
  *x = read(ITG3200_GX_H,ITG3200_GX_L)+_x_offset;
  *y = read(ITG3200_GY_H,ITG3200_GY_L)+_y_offset;
  *z = read(ITG3200_GZ_H,ITG3200_GZ_L)+_z_offset;
}

/*Function: Get the angular velocity and its unit is degree per second.*/
void _TEMPLATE_CLASS::getAngularVelocity(float *ax,float *ay,float *az)
{
  int16_t x,y,z;
  getXYZ(&x,&y,&z);
  *ax = x/14.375;
  *ay = y/14.375;
  *az = z/14.375;
}

bool _TEMPLATE_CLASS::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->version   = sizeof(sensors_event_t);
  event->sensor_id = _sensorID;
  event->type      = _SENSOR_TYPE;
  event->timestamp = millis();
  float ax, ay, az;
  getAngularVelocity(&ax, &ay, &az);

  event->_SENSOR_RETURN_VALUE.x = ax;
  event->_SENSOR_RETURN_VALUE.y = ay;
  event->_SENSOR_RETURN_VALUE.z = az;
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
