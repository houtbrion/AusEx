#include "AusExGrove3AxisDigitalGyro.h"

/*
 * 
 */
AUSEX_GROVE_3AXIS_DIGITAL_GYRO_CLASS::AUSEX_GROVE_3AXIS_DIGITAL_GYRO_CLASS(TwoWire *theWire, int32_t sensorID ){
  _i2c_if=theWire;
  _sensorID=sensorID;
  _x_offset=0;
  _y_offset=0;
  _z_offset=0;
  _times=0;
  _wait=0;
}
AUSEX_GROVE_3AXIS_DIGITAL_GYRO_CLASS::AUSEX_GROVE_3AXIS_DIGITAL_GYRO_CLASS(TwoWire *theWire, unsigned int samples,  unsigned int sampleDelayMS, int32_t sensorID ){
  _i2c_if=theWire;
  _sensorID=sensorID;
  _times=samples;
  _wait=sampleDelayMS;
  _x_offset=0;
  _y_offset=0;
  _z_offset=0;
}
int16_t AUSEX_GROVE_3AXIS_DIGITAL_GYRO_CLASS::read(uint8_t addressh, uint8_t addressl)
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



void AUSEX_GROVE_3AXIS_DIGITAL_GYRO_CLASS::zeroCalibrate(unsigned int samples, unsigned int sampleDelayMS) 
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


void AUSEX_GROVE_3AXIS_DIGITAL_GYRO_CLASS::write(uint8_t _register, uint8_t _data)
{
  //_i2c_addr->begin();
  _i2c_if->beginTransmission(_i2c_addr);
  _i2c_if->write(_register);   
  _i2c_if->write(_data);
  _i2c_if->endTransmission();
}

bool AUSEX_GROVE_3AXIS_DIGITAL_GYRO_CLASS::begin(uint32_t addr){
  _i2c_addr=addr;
  _i2c_if->begin();
  write(ITG3200_PWR_M,0x80);//send a reset to the device
  write(ITG3200_SMPL,0x00);//sample rate divider
  write(ITG3200_DLPF,0x18);//+/-2000 degrees/s (default value)
  if (_times >0 ) zeroCalibrate(_times, _wait);
  return true;
}


void AUSEX_GROVE_3AXIS_DIGITAL_GYRO_CLASS::getXYZ(int16_t *x,int16_t *y,int16_t *z)
{
  *x = read(ITG3200_GX_H,ITG3200_GX_L)+_x_offset;
  *y = read(ITG3200_GY_H,ITG3200_GY_L)+_y_offset;
  *z = read(ITG3200_GZ_H,ITG3200_GZ_L)+_z_offset;
}

/*Function: Get the angular velocity and its unit is degree per second.*/
void AUSEX_GROVE_3AXIS_DIGITAL_GYRO_CLASS::getAngularVelocity(float *ax,float *ay,float *az)
{
  int16_t x,y,z;
  getXYZ(&x,&y,&z);
  *ax = x/14.375;
  *ay = y/14.375;
  *az = z/14.375;
}

bool AUSEX_GROVE_3AXIS_DIGITAL_GYRO_CLASS::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->version   = sizeof(sensors_event_t);
  event->sensor_id = _sensorID;
  event->type      = AUSEX_GROVE_3AXIS_DIGITAL_GYRO_SENSOR_TYPE;
  event->timestamp = millis();
  float ax, ay, az;
  getAngularVelocity(&ax, &ay, &az);

  event->AUSEX_GROVE_3AXIS_DIGITAL_GYRO_SENSOR_RETURN_VALUE.x = ax;
  event->AUSEX_GROVE_3AXIS_DIGITAL_GYRO_SENSOR_RETURN_VALUE.y = ay;
  event->AUSEX_GROVE_3AXIS_DIGITAL_GYRO_SENSOR_RETURN_VALUE.z = az;
  return true;
}

void AUSEX_GROVE_3AXIS_DIGITAL_GYRO_CLASS::getSensor(sensor_t* sensor){
  /* Clear the sensor_t object */
  memset(sensor, 0, sizeof(sensor_t));

  /* Insert the sensor name in the fixed length char array */
  strncpy (sensor->name, AUSEX_GROVE_3AXIS_DIGITAL_GYRO_SENSOR_NAME , sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  sensor->version     = AUSEX_GROVE_3AXIS_DIGITAL_GYRO_SENSOR_LIBRARY_VERSION;
  sensor->sensor_id   = _sensorID;
  sensor->type        = AUSEX_GROVE_3AXIS_DIGITAL_GYRO_SENSOR_TYPE;
  sensor->min_value   = AUSEX_GROVE_3AXIS_DIGITAL_GYRO_SENSOR_MIN_VALUE;
  sensor->max_value   = AUSEX_GROVE_3AXIS_DIGITAL_GYRO_SENSOR_MAX_VALUE;
  sensor->resolution  = AUSEX_GROVE_3AXIS_DIGITAL_GYRO_SENSOR_RESOLUTION;
  sensor->min_delay   = AUSEX_GROVE_3AXIS_DIGITAL_GYRO_SENSOR_MIN_DELAY;
}


bool AUSEX_GROVE_3AXIS_DIGITAL_GYRO_CLASS::enableAutoRange(bool enabled) {
  return false;
}

int AUSEX_GROVE_3AXIS_DIGITAL_GYRO_CLASS::setMode(int mode) {
  return -1;
}

int AUSEX_GROVE_3AXIS_DIGITAL_GYRO_CLASS::getMode(void) {
  return -1;
}
