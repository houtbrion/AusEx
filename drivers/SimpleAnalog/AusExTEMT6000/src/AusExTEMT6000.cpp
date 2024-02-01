#include "AusExTEMT6000.h"

AUSEX_TEMT6000_CLASS::AUSEX_TEMT6000_CLASS(int pinNumber,float vdd, int32_t sensorID){
  _pin=pinNumber;
  _sensorID=sensorID;
  _vdd=vdd;
}

bool AUSEX_TEMT6000_CLASS::begin(void){
  pinMode(_pin, INPUT);
  return true;
}

bool AUSEX_TEMT6000_CLASS::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->size   = sizeof(sensors_event_t);
  event->sensor_id = _sensorID;
  event->type      = AUSEX_TEMT6000_SENSOR_TYPE;
  event->timestamp = millis();

  /* Calculate the actual lux value */
  event->AUSEX_TEMT6000_SENSOR_RETURN_VALUE = calcValue(analogRead(_pin));
  return true;
}

void AUSEX_TEMT6000_CLASS::getSensor(sensor_t* sensor){
  /* Clear the sensor_t object */
  memset(sensor, 0, sizeof(sensor_t));

  /* Insert the sensor name in the fixed length char array */
  strncpy (sensor->name, AUSEX_TEMT6000_SENSOR_NAME , sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  sensor->version     = AUSEX_TEMT6000_SENSOR_LIBRARY_VERSION;
  sensor->sensor_id   = _sensorID;
  sensor->type        = AUSEX_TEMT6000_SENSOR_TYPE;
  sensor->min_value   = AUSEX_TEMT6000_SENSOR_MIN_VALUE;
  sensor->max_value   = calcValue(AUSEX_TEMT6000_SENSOR_MAX_VALUE);
  sensor->resolution  = calcValue(AUSEX_TEMT6000_SENSOR_RESOLUTION);
  sensor->min_delay   = AUSEX_TEMT6000_SENSOR_MIN_DELAY;
  sensor->init_delay  = AUSEX_TEMT6000_SENSOR_INIT_DELAY;
}

bool AUSEX_TEMT6000_CLASS::enableAutoRange(bool enabled) {
  return false;
}

int AUSEX_TEMT6000_CLASS::setMode(int mode) {
  return -1;
}

int AUSEX_TEMT6000_CLASS::getMode() {
  return -1;
}

AUSEX_TEMT6000_SENSOR_VALUE_TYPE AUSEX_TEMT6000_CLASS::calcValue(int val){
  float mV = (val * _vdd * 1000) / AUSEX_TEMT6000_SENSOR_MAX_VALUE;
  return mV / 5.0;
}
