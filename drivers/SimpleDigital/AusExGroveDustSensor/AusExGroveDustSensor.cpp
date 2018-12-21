#include "AusExGroveDustSensor.h"

/*
 * 
 */
_TEMPLATE_CLASS::_TEMPLATE_CLASS(int pinNumber, int32_t sensorID ){
  _pin=pinNumber;
  _sensorID=sensorID;
}


bool _TEMPLATE_CLASS::begin(void){
  pinMode(_pin, INPUT);
}

float _TEMPLATE_CLASS::measure(void){
  //unsigned long duration;
  unsigned long starttime = millis();//get the current time;
  unsigned long lowpulseoccupancy = 0;
  float ratio = 0;
  float concentration = 0;
  while ((millis() - starttime) < SAMPLING_TIME ) {
    lowpulseoccupancy+=pulseIn(_pin, LOW);
  }
  ratio = lowpulseoccupancy/(SAMPLING_TIME*10.0);  // Integer percentage 0=>100
  concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
  return concentration;
}

bool _TEMPLATE_CLASS::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->version   = sizeof(sensors_event_t);
  event->sensor_id = _sensorID;
  event->type      = _SENSOR_TYPE;
  event->timestamp = millis();

  /* Calculate the actual lux value */
  event->_SENSOR_RETURN_VALUE = measure();
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

