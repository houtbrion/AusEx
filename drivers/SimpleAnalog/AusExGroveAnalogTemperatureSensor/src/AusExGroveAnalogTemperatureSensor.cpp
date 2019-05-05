
#include "AusExGroveAnalogTemperatureSensor.h"

AUSEX_GROVE_ANALOG_TEMPERATURE_CLASS::AUSEX_GROVE_ANALOG_TEMPERATURE_CLASS(int analogPin, int32_t sensorID){
  _sensorID = sensorID;
  _pin_number = analogPin;
}


bool AUSEX_GROVE_ANALOG_TEMPERATURE_CLASS::begin(void){
  pinMode(_pin_number, INPUT);
  return true;
}

bool AUSEX_GROVE_ANALOG_TEMPERATURE_CLASS::getEvent(sensors_event_t *event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));
  event->version   = sizeof(sensors_event_t);
  event->sensor_id = _sensorID;
  event->type      = AUSEX_GROVE_ANALOG_TEMPERATURE_SENSOR_TYPE;
  event->timestamp = millis();
  int a = analogRead(_pin_number);
  float R = RESISTOR_R0*(1023.0/a-1.0);
  event->AUSEX_GROVE_ANALOG_TEMPERATURE_SENSOR_RETURN_VALUE = 1.0/(log(R/RESISTOR_R0)/THERMISTOR_B+1/298.15)-273.15; // convert to temperature via datasheet
  return true;
}

void AUSEX_GROVE_ANALOG_TEMPERATURE_CLASS::getSensor(sensor_t* sensor) {
  /* Clear the sensor_t object */
  memset(sensor, 0, sizeof(sensor_t));
  /* Insert the sensor name in the fixed length char array */
  strncpy (sensor->name, AUSEX_GROVE_ANALOG_TEMPERATURE_SENSOR_NAME, sizeof(sensor->name) - 1);
  sensor->version = AUSEX_GROVE_ANALOG_TEMPERATURE_SENSOR_LIBRARY_VERSION;
  sensor->sensor_id = _sensorID;
  sensor->type = AUSEX_GROVE_ANALOG_TEMPERATURE_SENSOR_TYPE;
  sensor->min_value   = AUSEX_GROVE_ANALOG_TEMPERATURE_SENSOR_MIN_VALUE;
  sensor->max_value   = AUSEX_GROVE_ANALOG_TEMPERATURE_SENSOR_MAX_VALUE;
  sensor->resolution  = AUSEX_GROVE_ANALOG_TEMPERATURE_SENSOR_RESOLUTION;
  sensor->min_delay   = AUSEX_GROVE_ANALOG_TEMPERATURE_SENSOR_MIN_DELAY;
  sensor->init_delay  = AUSEX_GROVE_ANALOG_TEMPERATURE_SENSOR_INIT_DELAY;
};

bool AUSEX_GROVE_ANALOG_TEMPERATURE_CLASS::enableAutoRange(bool enabled) {
  return false;
};

int AUSEX_GROVE_ANALOG_TEMPERATURE_CLASS::setMode(int mode) {
  return -1;
};

int AUSEX_GROVE_ANALOG_TEMPERATURE_CLASS::getMode(void) {
  return -1;
};
