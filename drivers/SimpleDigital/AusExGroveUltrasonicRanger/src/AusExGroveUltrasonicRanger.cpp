#include "AusExGroveUltrasonicRanger.h"

/*
 * 
 */
AUSEX_GROVE_ULTRASONIC_RANGER_CLASS::AUSEX_GROVE_ULTRASONIC_RANGER_CLASS(int pinNumber, int32_t sensorID ){
  _pin=pinNumber;
  _sensorID=sensorID;
}


bool AUSEX_GROVE_ULTRASONIC_RANGER_CLASS::begin(bool pullUp){
  if (pullUp) {
    pinMode(_pin, INPUT_PULLUP);
  } else {
    pinMode(_pin, INPUT);
  }
  return true;
}


bool AUSEX_GROVE_ULTRASONIC_RANGER_CLASS::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->size      = sizeof(sensors_event_t);
  event->sensor_id = _sensorID;
  event->type      = AUSEX_GROVE_ULTRASONIC_RANGER_SENSOR_TYPE;
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
  
  
  event->AUSEX_GROVE_ULTRASONIC_RANGER_SENSOR_RETURN_VALUE = calcValue(duration);
  return true;
}

void AUSEX_GROVE_ULTRASONIC_RANGER_CLASS::getSensor(sensor_t* sensor){
  /* Clear the sensor_t object */
  memset(sensor, 0, sizeof(sensor_t));

  /* Insert the sensor name in the fixed length char array */
  strncpy (sensor->name, AUSEX_GROVE_ULTRASONIC_RANGER_SENSOR_NAME , sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  sensor->version     = AUSEX_GROVE_ULTRASONIC_RANGER_SENSOR_LIBRARY_VERSION;
  sensor->sensor_id   = _sensorID;
  sensor->type        = AUSEX_GROVE_ULTRASONIC_RANGER_SENSOR_TYPE;
  sensor->min_value   = AUSEX_GROVE_ULTRASONIC_RANGER_SENSOR_MIN_VALUE;
  sensor->max_value   = AUSEX_GROVE_ULTRASONIC_RANGER_SENSOR_MAX_VALUE;
  sensor->resolution  = AUSEX_GROVE_ULTRASONIC_RANGER_SENSOR_RESOLUTION;
  sensor->min_delay   = AUSEX_GROVE_ULTRASONIC_RANGER_SENSOR_MIN_DELAY;
  sensor->init_delay  = AUSEX_GROVE_ULTRASONIC_RANGER_SENSOR_INIT_DELAY;
}


bool AUSEX_GROVE_ULTRASONIC_RANGER_CLASS::enableAutoRange(bool enabled) {
  return false;
}

int AUSEX_GROVE_ULTRASONIC_RANGER_CLASS::setMode(int mode) {
  return -1;
}

int AUSEX_GROVE_ULTRASONIC_RANGER_CLASS::getMode(void) {
  return -1;
}

AUSEX_GROVE_ULTRASONIC_RANGER_SENSOR_VALUE_TYPE AUSEX_GROVE_ULTRASONIC_RANGER_CLASS::calcValue(long val){
  float RangeInCentimeters;
  RangeInCentimeters = val/29/2;
  return RangeInCentimeters;
}
