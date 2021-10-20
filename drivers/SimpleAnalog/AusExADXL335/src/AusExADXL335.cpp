#include "AusExADXL335.h"

AUSEX_ADXL335_CLASS::AUSEX_ADXL335_CLASS(int pinX, int pinY, int pinZ, float vdd, float calX, float calY, float calZ, float sens, int32_t sensorID){
  _pinX=pinX;
  _pinY=pinY;
  _pinZ=pinZ;
  _sensorID=sensorID;
  _vdd=vdd;
  _sens=sens;
  _calX=calX;
  _calY=calY;
  _calZ=calZ;
}

bool AUSEX_ADXL335_CLASS::begin(void){
  pinMode(_pinX, INPUT);
  pinMode(_pinY, INPUT);
  pinMode(_pinZ, INPUT);
  return true;
}

void AUSEX_ADXL335_CLASS::getAcceleration(sensors_event_t* event){
  float volX, volY, volZ;
  volX=analogRead(_pinX)*_vdd/AUSEX_ADXL335_ADC_AMPLITUDE;
  volY=analogRead(_pinY)*_vdd/AUSEX_ADXL335_ADC_AMPLITUDE;
  volZ=analogRead(_pinZ)*_vdd/AUSEX_ADXL335_ADC_AMPLITUDE;
#ifdef DEBUG
  Serial.print("volX = ");Serial.println(volX);
  Serial.print("volY = ");Serial.println(volY);
  Serial.print("volZ = ");Serial.println(volZ);
#endif
  event->acceleration.x= (volX- _calX)/_sens;
  event->acceleration.y= (volY- _calY)/_sens;
  event->acceleration.z= (volZ- _calZ)/_sens;
}

bool AUSEX_ADXL335_CLASS::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->size      = sizeof(sensors_event_t);
  event->sensor_id = _sensorID;
  event->type      = AUSEX_ADXL335_SENSOR_TYPE;
  event->timestamp = millis();

  getAcceleration(event);
  return true;
}

void AUSEX_ADXL335_CLASS::getSensor(sensor_t* sensor){
  /* Clear the sensor_t object */
  memset(sensor, 0, sizeof(sensor_t));

  /* Insert the sensor name in the fixed length char array */
  strncpy (sensor->name, AUSEX_ADXL335_SENSOR_NAME , sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  sensor->version     = AUSEX_ADXL335_SENSOR_LIBRARY_VERSION;
  sensor->sensor_id   = _sensorID;
  sensor->type        = AUSEX_ADXL335_SENSOR_TYPE;
  sensor->min_value   = AUSEX_ADXL335_SENSOR_MIN_VALUE;
  sensor->max_value   = AUSEX_ADXL335_SENSOR_MAX_VALUE;
  sensor->resolution  = AUSEX_ADXL335_SENSOR_RESOLUTION;
  sensor->min_delay   = AUSEX_ADXL335_SENSOR_MIN_DELAY;
  sensor->init_delay  = AUSEX_ADXL335_SENSOR_INIT_DELAY;
}


bool AUSEX_ADXL335_CLASS::enableAutoRange(bool enabled) {
  return false;
}

int AUSEX_ADXL335_CLASS::setMode(int mode) {
  return -1;
}

int AUSEX_ADXL335_CLASS::getMode() {
  return -1;
}

