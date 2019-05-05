#include "AusExGroveTouchSensor.h"

/*
 * 
 */
AUSEX_GROVE_TOUCH_CLASS::AUSEX_GROVE_TOUCH_CLASS(int pinNumber, int32_t sensorID ){
  _pin=pinNumber;
  _sensorID=sensorID;
  //_pullUp=false;
}

/*
_TEMPLATE_CLASS::_TEMPLATE_CLASS(int pinNumber,bool pullUp, int32_t sensorID ){
  _pin=pinNumber;
  _sensorID=sensorID;
  _pullUp=pullUp;
}
*/

bool AUSEX_GROVE_TOUCH_CLASS::begin(bool pullUp){
  if (pullUp) {
    pinMode(_pin, INPUT_PULLUP);
  } else {
    pinMode(_pin, INPUT);
  }
  return true;
}

bool AUSEX_GROVE_TOUCH_CLASS::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->version   = sizeof(sensors_event_t);
  event->sensor_id = _sensorID;
  event->type      = AUSEX_GROVE_TOUCH_SENSOR_TYPE;
  event->timestamp = millis();

  /* Calculate the actual lux value */
  event->AUSEX_GROVE_TOUCH_SENSOR_RETURN_VALUE = calcValue(digitalRead(_pin));
  return true;
}

void AUSEX_GROVE_TOUCH_CLASS::getSensor(sensor_t* sensor){
  /* Clear the sensor_t object */
  memset(sensor, 0, sizeof(sensor_t));

  /* Insert the sensor name in the fixed length char array */
  strncpy (sensor->name, AUSEX_GROVE_TOUCH_SENSOR_NAME , sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  sensor->version     = AUSEX_GROVE_TOUCH_SENSOR_LIBRARY_VERSION;
  sensor->sensor_id   = _sensorID;
  sensor->type        = AUSEX_GROVE_TOUCH_SENSOR_TYPE;
  sensor->min_value   = AUSEX_GROVE_TOUCH_SENSOR_MIN_VALUE;
  sensor->max_value   = AUSEX_GROVE_TOUCH_SENSOR_MAX_VALUE;
  sensor->resolution  = AUSEX_GROVE_TOUCH_SENSOR_RESOLUTION;
  sensor->min_delay   = AUSEX_GROVE_TOUCH_SENSOR_MIN_DELAY;
  sensor->init_delay  = AUSEX_GROVE_TOUCH_SENSOR_INIT_DELAY;
}


bool AUSEX_GROVE_TOUCH_CLASS::enableAutoRange(bool enabled) {
  return false;
}

int AUSEX_GROVE_TOUCH_CLASS::setMode(int mode) {
  return -1;
}

int AUSEX_GROVE_TOUCH_CLASS::getMode(void) {
  return -1;
}

AUSEX_GROVE_TOUCH_SENSOR_VALUE_TYPE AUSEX_GROVE_TOUCH_CLASS::calcValue(int val){
  return val;
}
