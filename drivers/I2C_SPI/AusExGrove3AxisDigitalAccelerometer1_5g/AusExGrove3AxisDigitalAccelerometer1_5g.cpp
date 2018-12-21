#include "AusExGrove3AxisDigitalAccelerometer1_5g.h"

/*
 * 
 */
_TEMPLATE_CLASS::_TEMPLATE_CLASS(int32_t sensorID ){
  _i2c_addr=_SENSOR_DEFAULT_I2C_ADDR;
  _sensorID=sensorID;
}

void _TEMPLATE_CLASS::initAccelTable(){
  int i;
  float val, valZ;
  for (i = 0, val = 0; i < 32; i++) {
    accLookup[i].g = val;
    val += 0.047;
  }
  for (i = 63, val = -0.047; i > 31; i--) {
    accLookup[i].g = val;
    val -= 0.047;
  }
  for (i = 0, val = 0, valZ = 90; i < 22; i++) {
    accLookup[i].xyAngle = val;
    accLookup[i].zAngle = valZ;
    val += 2.69;
    valZ -= 2.69;
  }
  for (i = 63, val = -2.69, valZ = -87.31; i > 42; i--) {
    accLookup[i].xyAngle = val;
    accLookup[i].zAngle = valZ;
    val -= 2.69;
    valZ += 2.69;
  }
  for (i = 22; i < 43; i++) {
    accLookup[i].xyAngle = 255;
    accLookup[i].zAngle = 255;
  }
}

void _TEMPLATE_CLASS::setState(uint8_t mode) {
  write(MMA7660_MODE,mode);
}
void _TEMPLATE_CLASS::setSampleRate(uint8_t rate) {
  write(MMA7660_SR,rate);
}

bool _TEMPLATE_CLASS::begin(TwoWire *theWire){
  _i2c_if=theWire;
  initAccelTable();
  setState(MMA7660_STAND_BY);
  setSampleRate(AUTO_SLEEP_32);
  setState(MMA7660_ACTIVE);
}

void _TEMPLATE_CLASS::write(uint8_t _register, uint8_t _data)
{
  _i2c_if->begin();
  _i2c_if->beginTransmission(_i2c_addr);
  _i2c_if->write(_register);   
  _i2c_if->write(_data);
  _i2c_if->endTransmission();
}

int8_t _TEMPLATE_CLASS::read(uint8_t _register)
{
  int8_t data;
  _i2c_if->begin();
  _i2c_if->beginTransmission(_i2c_addr);
  _i2c_if->write(_register);
  _i2c_if->endTransmission();
  _i2c_if->beginTransmission(_i2c_addr);
  _i2c_if->requestFrom(_i2c_addr, 1);
  if(_i2c_if->available() > 0){
    data = _i2c_if->read();
  }
  _i2c_if->endTransmission();
  return data;
}

bool _TEMPLATE_CLASS::getXYZ(int8_t *x,int8_t *y,int8_t *z)
{
START:
  unsigned char val[3];
  int count = 0;
  val[0] = val[1] = val[2] = 64;
  while(_i2c_if->available() > 0)
  _i2c_if->read();
  _i2c_if->requestFrom(_i2c_addr,3);
  unsigned long timer_s = micros();
  while(_i2c_if->available()){
    if(count < 3) {
      while ( val[count] > 63 ) { // reload the damn thing it is bad
        val[count] = _i2c_if->read();
        if(micros()-timer_s > MMA7660TIMEOUT) {
          goto START;
        }
      }
    }
    count++;
  }
  *x = ((int8_t)(val[0]<<2))/4;
  *y = ((int8_t)(val[1]<<2))/4;
  *z = ((int8_t)(val[2]<<2))/4;
  return true;
}

bool _TEMPLATE_CLASS::getAcceleration(float *ax,float *ay,float *az)
{
  int8_t x,y,z;
  if(!getXYZ(&x,&y,&z))return false;
  *ax = x/21.00;
  *ay = y/21.00;
  *az = z/21.00;
  return true;
}

bool _TEMPLATE_CLASS::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->version   = sizeof(sensors_event_t);
  event->sensor_id = _sensorID;
  event->type      = _SENSOR_TYPE;
  event->timestamp = millis();
  float x, y, z;
  getAcceleration(&x, &y, &z);
  event->_SENSOR_RETURN_VALUE.x = x;
  event->_SENSOR_RETURN_VALUE.y = y;
  event->_SENSOR_RETURN_VALUE.z = z;
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
