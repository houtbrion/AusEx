#include "AusExGrove3AxisDigitalAccelerometer1_5g.h"

/*
 * 
 */
AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_CLASS::AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_CLASS(TwoWire *theWire,int32_t sensorID ){
  _i2c_if=theWire;
  _sensorID=sensorID;
  _mode=-1;
}

void AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_CLASS::initAccelTable(){
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

void AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_CLASS::setState(uint8_t mode) {
  write(MMA7660_MODE,mode);
}
void AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_CLASS::setSampleRate(uint8_t rate) {
  write(MMA7660_SR,rate);
}

bool AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_CLASS::begin(uint32_t addr){
  _i2c_addr=addr;
  _mode=MMA7660_AUTO_SLEEP_120;
  initAccelTable();
  setState(MMA7660_STAND_BY);
  setSampleRate(MMA7660_AUTO_SLEEP_120);
  setState(MMA7660_ACTIVE);
  return true;
}

void AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_CLASS::write(uint8_t _register, uint8_t _data)
{
  _i2c_if->begin();
  _i2c_if->beginTransmission(_i2c_addr);
  _i2c_if->write(_register);   
  _i2c_if->write(_data);
  _i2c_if->endTransmission();
}

int8_t AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_CLASS::read(uint8_t _register)
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

bool AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_CLASS::getXYZ(int8_t *x,int8_t *y,int8_t *z)
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

bool AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_CLASS::getAcceleration(float *ax,float *ay,float *az)
{
  int8_t x,y,z;
  if(!getXYZ(&x,&y,&z))return false;
  *ax = x/21.00;
  *ay = y/21.00;
  *az = z/21.00;
  return true;
}

bool AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_CLASS::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->size      = sizeof(sensors_event_t);
  event->sensor_id = _sensorID;
  event->type      = AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_SENSOR_TYPE;
  event->timestamp = millis();
  float x, y, z;
  getAcceleration(&x, &y, &z);
  event->AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_SENSOR_RETURN_VALUE.x = x;
  event->AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_SENSOR_RETURN_VALUE.y = y;
  event->AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_SENSOR_RETURN_VALUE.z = z;
  return true;
}

void AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_CLASS::getSensor(sensor_t* sensor){
  /* Clear the sensor_t object */
  memset(sensor, 0, sizeof(sensor_t));

  /* Insert the sensor name in the fixed length char array */
  strncpy (sensor->name, AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_SENSOR_NAME , sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  sensor->version     = AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_SENSOR_LIBRARY_VERSION;
  sensor->sensor_id   = _sensorID;
  sensor->type        = AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_SENSOR_TYPE;
  sensor->min_value   = AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_SENSOR_MIN_VALUE;
  sensor->max_value   = AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_SENSOR_MAX_VALUE;
  sensor->resolution  = AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_SENSOR_RESOLUTION;
  sensor->min_delay   = AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_SENSOR_MIN_DELAY;
  sensor->init_delay  = AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_SENSOR_INIT_DELAY;
}

bool AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_CLASS::enableAutoRange(bool enabled) {
  return false;
}


int AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_CLASS::setMode(int mode) {
  if ((mode < MMA7660_AUTO_SLEEP_120 ) || (mode > MMA7660_AUTO_SLEEP_1)) return 1;
  setState(MMA7660_STAND_BY);
  setSampleRate(mode);
  setState(MMA7660_ACTIVE);
  _mode=mode;
  return 0;
}

int AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_CLASS::getMode() {
  return _mode;
}
