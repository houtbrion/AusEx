#include "AusExIRremote.h"

/*
 * 
 */
AUSEX_IRREMOTE_CLASS::AUSEX_IRREMOTE_CLASS(int pinNumber, int32_t sensorID):
  _irrecv(pinNumber),
  _sensorID(sensorID)
{}

bool AUSEX_IRREMOTE_CLASS::begin(void){
  _irrecv.enableIRIn();
}

bool AUSEX_IRREMOTE_CLASS::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->version   = sizeof(sensors_event_t);
  event->sensor_id = _sensorID;
  event->type      = AUSEX_IRREMOTE_TYPE;
  event->timestamp = millis();

  /* check ir receiver */
  decode_results  results;
  if (!_irrecv.decode(&results)) {
    return false;
  }
  _irrecv.resume();
  if (!convertValue(&results, event)) {
    return false;
  }
  return true;
}

void AUSEX_IRREMOTE_CLASS::getSensor(sensor_t* sensor){
  /* Clear the sensor_t object */
  memset(sensor, 0, sizeof(sensor_t));

  /* Insert the sensor name in the fixed length char array */
  strncpy (sensor->name, AUSEX_IRREMOTE_NAME , sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  sensor->version     = AUSEX_IRREMOTE_LIBRARY_VERSION;
  sensor->sensor_id   = _sensorID;
  sensor->type        = AUSEX_IRREMOTE_TYPE;
  sensor->min_value   = AUSEX_IRREMOTE_MIN_VALUE;
  sensor->max_value   = AUSEX_IRREMOTE_MAX_VALUE;
  sensor->resolution  = AUSEX_IRREMOTE_RESOLUTION;
  sensor->min_delay   = AUSEX_IRREMOTE_MIN_DELAY;
  sensor->init_delay  = AUSEX_IRREMOTE_INIT_DELAY;
}

bool AUSEX_IRREMOTE_CLASS::enableAutoRange(bool enabled) {
  return true;
}

bool AUSEX_IRREMOTE_CLASS::convertValue(decode_results * results, sensors_event_t * event) {
  if (results->overflow) {
    event->irremote.overflow  = 1;
  } else {
    event->irremote.overflow  = 0;
  }
  event->irremote.decode_type = results->decode_type;
  event->irremote.address     = results->address;
  event->irremote.value       = results->value;
  return true;
}

int AUSEX_IRREMOTE_CLASS::setMode(int mode){
  return -1;
}

int AUSEX_IRREMOTE_CLASS::getMode(){
  return -1;
}
