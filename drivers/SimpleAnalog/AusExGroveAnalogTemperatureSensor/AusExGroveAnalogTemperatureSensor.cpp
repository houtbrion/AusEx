
#include "AusExGroveAnalogTemperatureSensor.h"


Grove_Analog_Temperature_Sensor_AusEx::Grove_Analog_Temperature_Sensor_AusEx(int32_t sensorID){
  _sensorID = sensorID;
  _pin_number = DEFAULT_PIN;
}

Grove_Analog_Temperature_Sensor_AusEx::Grove_Analog_Temperature_Sensor_AusEx(int analogPin, int32_t sensorID){
  _sensorID = sensorID;
  _pin_number = analogPin;
}


bool Grove_Analog_Temperature_Sensor_AusEx::begin(void){
  return true;
}


bool Grove_Analog_Temperature_Sensor_AusEx::getEvent(sensors_event_t *event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));
  event->version   = sizeof(sensors_event_t);
  event->sensor_id = _sensorID;
  event->type      = SENSOR_TYPE_AMBIENT_TEMPERATURE;
  event->timestamp = millis();
  int a = analogRead(_pin_number);
  float R = RESISTOR_R0*(1023.0/a-1.0);
  event->temperature = 1.0/(log(R/RESISTOR_R0)/THERMISTOR_B+1/298.15)-273.15; // convert to temperature via datasheet
  return true;
}

void Grove_Analog_Temperature_Sensor_AusEx::getSensor(sensor_t* sensor) {
  /* Clear the sensor_t object */
  memset(sensor, 0, sizeof(sensor_t));
  /* Insert the sensor name in the fixed length char array */
  strncpy (sensor->name, "GroveAnalogTemperatureSensor", sizeof(sensor->name) - 1);
  sensor->version = SENSOR_VERSION;
  sensor->sensor_id = _sensorID;
  sensor->type = SENSOR_TYPE_AMBIENT_TEMPERATURE;
  sensor->min_value   = _SENSOR_MIN_VALUE;
  sensor->max_value   = _SENSOR_MAX_VALUE;
  sensor->resolution  = _SENSOR_RESOLUTION;
  sensor->min_delay   = _SENSOR_MIN_DELAY;
};


bool Grove_Analog_Temperature_Sensor_AusEx::enableAutoRange(bool enabled) {
  return false;
};

int Grove_Analog_Temperature_Sensor_AusEx::setMode(int mode) {
  return -1;
};
