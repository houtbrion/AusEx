#include "AusExGroveUltrasonicRanger.h"

/*
 * 
 */
_TEMPLATE_CLASS::_TEMPLATE_CLASS(int pinNumber, int32_t sensorID ){
  _pin=pinNumber;
  _sensorID=sensorID;
}
bool _TEMPLATE_CLASS::begin(void){
  return true;
}

bool _TEMPLATE_CLASS::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->version   = sizeof(sensors_event_t);
  event->sensor_id = _sensorID;
  event->type      = _SENSOR_TYPE;
  event->timestamp = millis();

  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(_pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(_pin,LOW);
  pinMode(_pin,INPUT);
  long duration;
  duration = pulseIn(_pin,HIGH);
  
  
  event->_SENSOR_RETURN_VALUE = calcValue(duration);
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

_SENSOR_VALUE_TYPE _TEMPLATE_CLASS::calcValue(long val){
  float RangeInCentimeters;
  RangeInCentimeters = val/29/2;
  return RangeInCentimeters;
}
