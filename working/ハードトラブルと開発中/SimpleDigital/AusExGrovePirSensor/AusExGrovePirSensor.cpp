#include "AusExGrovePirSensor.h"

/*
 * 
 */
_TEMPLATE_CLASS::_TEMPLATE_CLASS(int pinNumber, uint32_t sensorID = -1){
  _pin=pinNumber;
  _sensorID=sensorID;
  _pullUp=false;
}
_TEMPLATE_CLASS::_TEMPLATE_CLASS(int pinNumber,bool pullUp, uint32_t sensorID = -1){
  _pin=pinNumber;
  _sensorID=sensorID;
  _pullUp=pullUp;
}

bool _TEMPLATE_CLASS::begin(void){
  if (_pullUp) {
    pinMode(_pin, INPUT_PULLUP);
  } else {
    pinMode(_pin, INPUT);
  }

}

bool _TEMPLATE_CLASS::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->version   = sizeof(sensors_event_t);
  event->sensor_id = _sensorID;
  event->type      = _SENSOR_TYPE;
  event->timestamp = millis();

  /* Calculate the actual lux value */
  event->_SENSOR_RETURN_VALUE = calcValue(digitalRead(_pin));
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

_SENSOR_VALUE_TYPE _TEMPLATE_CLASS::calcValue(int val){
  return val;
}
