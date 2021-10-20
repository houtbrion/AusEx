#include "AusExDigitalSwitch.h"

/*
 * 
 */
AUSEX_GROVE_DIGITAL_SWITCH_CLASS::AUSEX_GROVE_DIGITAL_SWITCH_CLASS(int pinNumber, int32_t sensorID ){
  _pin=pinNumber;
  _sensorID=sensorID;
}

bool AUSEX_GROVE_DIGITAL_SWITCH_CLASS::begin(bool pullUp){
  if (pullUp) {
    pinMode(_pin, INPUT_PULLUP);
  } else {
    pinMode(_pin, INPUT);
  }
  return true;
}

bool AUSEX_GROVE_DIGITAL_SWITCH_CLASS::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->size   = sizeof(sensors_event_t);
  event->sensor_id = _sensorID;
  event->type      = AUSEX_GROVE_DIGITAL_SWITCH_TYPE;
  event->timestamp = millis();

  /* Calculate the actual lux value */
  event->AUSEX_GROVE_DIGITAL_SWITCH_RETURN_VALUE = calcValue(digitalRead(_pin));
  return true;
}

void AUSEX_GROVE_DIGITAL_SWITCH_CLASS::getSensor(sensor_t* sensor){
  /* Clear the sensor_t object */
  memset(sensor, 0, sizeof(sensor_t));

  /* Insert the sensor name in the fixed length char array */
  strncpy (sensor->name, AUSEX_GROVE_DIGITAL_SWITCH_NAME , sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  sensor->version     = AUSEX_GROVE_DIGITAL_SWITCH_LIBRARY_VERSION;
  sensor->sensor_id   = _sensorID;
  sensor->type        = AUSEX_GROVE_DIGITAL_SWITCH_TYPE;
  sensor->min_value   = AUSEX_GROVE_DIGITAL_SWITCH_MIN_VALUE;
  sensor->max_value   = AUSEX_GROVE_DIGITAL_SWITCH_MAX_VALUE;
  sensor->resolution  = AUSEX_GROVE_DIGITAL_SWITCH_RESOLUTION;
  sensor->min_delay   = AUSEX_GROVE_DIGITAL_SWITCH_MIN_DELAY;
  sensor->init_delay  = AUSEX_GROVE_DIGITAL_SWITCH_INIT_DELAY;
}


bool AUSEX_GROVE_DIGITAL_SWITCH_CLASS::enableAutoRange(bool enabled) {
  _autoRange=enabled;
  return true;
}

AUSEX_GROVE_DIGITAL_SWITCH_VALUE_TYPE AUSEX_GROVE_DIGITAL_SWITCH_CLASS::calcValue(int val){
  return val;
}


int AUSEX_GROVE_DIGITAL_SWITCH_CLASS::setMode(int mode){
  _mode = mode;
  return -1;
}

int AUSEX_GROVE_DIGITAL_SWITCH_CLASS::getMode(void){
  return -1;
}
