#include "AusExDallasTemperature.h"

/*
 * 
 */
AUSEX_DALLAS_TEMPERATURE_CLASS::AUSEX_DALLAS_TEMPERATURE_CLASS(int pinNumber, int32_t sensorID):
  _wire((uint8_t)pinNumber),
  _sensor(&_wire),
  _sensorID(sensorID)
{}

bool AUSEX_DALLAS_TEMPERATURE_CLASS::begin(void){
  _mode=0;
  _sensor.begin();
  return true;
}

bool AUSEX_DALLAS_TEMPERATURE_CLASS::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->size   = sizeof(sensors_event_t);
  event->sensor_id = _sensorID;
  event->type      = AUSEX_DALLAS_TEMPERATURE_SENSOR_TYPE;
  event->timestamp = millis();

  _sensor.requestTemperatures(); // Send the command to get temperatures
  
  event->AUSEX_DALLAS_TEMPERATURE_SENSOR_RETURN_VALUE = _sensor.getTempCByIndex(_mode);
  return true;
}

void AUSEX_DALLAS_TEMPERATURE_CLASS::getSensor(sensor_t* sensor){
  /* Clear the sensor_t object */
  memset(sensor, 0, sizeof(sensor_t));

  /* Insert the sensor name in the fixed length char array */
  strncpy (sensor->name, AUSEX_DALLAS_TEMPERATURE_SENSOR_NAME , sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  sensor->version     = AUSEX_DALLAS_TEMPERATURE_SENSOR_LIBRARY_VERSION;
  sensor->sensor_id   = _sensorID;
  sensor->type        = AUSEX_DALLAS_TEMPERATURE_SENSOR_TYPE;
  sensor->min_value   = AUSEX_DALLAS_TEMPERATURE_SENSOR_MIN_VALUE;
  sensor->max_value   = AUSEX_DALLAS_TEMPERATURE_SENSOR_MAX_VALUE;
  sensor->resolution  = AUSEX_DALLAS_TEMPERATURE_SENSOR_RESOLUTION;
  sensor->min_delay   = AUSEX_DALLAS_TEMPERATURE_SENSOR_MIN_DELAY;
  sensor->init_delay  = AUSEX_DALLAS_TEMPERATURE_SENSOR_INIT_DELAY;
}


bool AUSEX_DALLAS_TEMPERATURE_CLASS::enableAutoRange(bool enabled) {
  return true;
}

int AUSEX_DALLAS_TEMPERATURE_CLASS::setMode(int mode){
  _mode = (uint8_t)mode;
  return 1;
}

int AUSEX_DALLAS_TEMPERATURE_CLASS::getMode(){
  return _mode;
}
