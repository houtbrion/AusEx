#include "AusExGroveDustSensor.h"

/*
 * 
 */
AUSEX_GROVE_DUST_SENSOR_CLASS::AUSEX_GROVE_DUST_SENSOR_CLASS(int pinNumber, int32_t sensorID ){
  _pin=pinNumber;
  _sensorID=sensorID;
}


bool AUSEX_GROVE_DUST_SENSOR_CLASS::begin(bool pullUp){
  if (pullUp) {
    pinMode(_pin, INPUT_PULLUP);
  } else {
    pinMode(_pin, INPUT);
  }
  return true;
}

float AUSEX_GROVE_DUST_SENSOR_CLASS::measure(void){
  //unsigned long duration;
  unsigned long starttime = millis();//get the current time;
  unsigned long lowpulseoccupancy = 0;
  float ratio = 0;
  float concentration = 0;
  while ((millis() - starttime) < AUSEX_GROVE_DUST_SENSOR_MIN_DELAY ) {
    lowpulseoccupancy+=pulseIn(_pin, LOW);
  }
  ratio = lowpulseoccupancy/(AUSEX_GROVE_DUST_SENSOR_MIN_DELAY*10.0);  // Integer percentage 0=>100
  concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
  return concentration;
}

bool AUSEX_GROVE_DUST_SENSOR_CLASS::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->version   = sizeof(sensors_event_t);
  event->sensor_id = _sensorID;
  event->type      = AUSEX_GROVE_DUST_SENSOR_TYPE;
  event->timestamp = millis();

  /* Calculate the actual lux value */
  event->AUSEX_GROVE_DUST_SENSOR_RETURN_VALUE = measure();
  return true;
}

void AUSEX_GROVE_DUST_SENSOR_CLASS::getSensor(sensor_t* sensor){
  /* Clear the sensor_t object */
  memset(sensor, 0, sizeof(sensor_t));

  /* Insert the sensor name in the fixed length char array */
  strncpy (sensor->name, AUSEX_GROVE_DUST_SENSOR_NAME , sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  sensor->version     = AUSEX_GROVE_DUST_SENSOR_LIBRARY_VERSION;
  sensor->sensor_id   = _sensorID;
  sensor->type        = AUSEX_GROVE_DUST_SENSOR_TYPE;
  sensor->min_value   = AUSEX_GROVE_DUST_SENSOR_MIN_VALUE;
  sensor->max_value   = AUSEX_GROVE_DUST_SENSOR_MAX_VALUE;
  sensor->resolution  = AUSEX_GROVE_DUST_SENSOR_RESOLUTION;
  sensor->min_delay   = AUSEX_GROVE_DUST_SENSOR_MIN_DELAY;
  sensor->init_delay  = AUSEX_GROVE_DUST_SENSOR_INIT_DELAY;
}


bool AUSEX_GROVE_DUST_SENSOR_CLASS::enableAutoRange(bool enabled) {
  return false;
}

int AUSEX_GROVE_DUST_SENSOR_CLASS::setMode(int mode) {
  return -1;
}

int AUSEX_GROVE_DUST_SENSOR_CLASS::getMode(void) {
  return -1;
}
