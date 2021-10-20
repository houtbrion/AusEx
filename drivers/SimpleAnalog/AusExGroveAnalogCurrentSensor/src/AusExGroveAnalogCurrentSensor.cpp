#include "AusExGroveAnalogCurrentSensor.h"

/*
 * 
 */
AUSEX_GROVE_ANALOG_CURRENT_SENSOR_CLASS::AUSEX_GROVE_ANALOG_CURRENT_SENSOR_CLASS(int pinNumber, int32_t sensorID){
  _pin=pinNumber;
  _sensorID=sensorID;
  _vdd=AUSEX_GROVE_ANALOG_CURRENT_DEFAULT_VDD;
  _mode=0;
  sensorMaxValue=AUSEX_GROVE_ANALOG_CURRENT_SENSOR_AVE_MAX_VALUE;
}

AUSEX_GROVE_ANALOG_CURRENT_SENSOR_CLASS::AUSEX_GROVE_ANALOG_CURRENT_SENSOR_CLASS(int pinNumber,float vdd, int32_t sensorID){
  _pin=pinNumber;
  _sensorID=sensorID;
  _vdd=vdd;
  _mode=0;
  sensorMaxValue=AUSEX_GROVE_ANALOG_CURRENT_SENSOR_AVE_MAX_VALUE;
}

bool AUSEX_GROVE_ANALOG_CURRENT_SENSOR_CLASS::begin(void){
  return true;
}

bool AUSEX_GROVE_ANALOG_CURRENT_SENSOR_CLASS::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->size      = sizeof(sensors_event_t);
  event->sensor_id = _sensorID;
  event->type      = AUSEX_GROVE_ANALOG_CURRENT_SENSOR_TYPE;
  uint32_t start_time = millis();
  int sensorMax=0;
  int sensorValue=0;
  while((millis()-start_time) <AUSEX_GROVE_ANALOG_CURRENT_SENSOR_MIN_DELAY_MILLI) {
    sensorValue = analogRead(_pin);
    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }
  }
  event->timestamp = millis();
  /* Calculate the actual lux value */
  event->AUSEX_GROVE_ANALOG_CURRENT_SENSOR_RETURN_VALUE = calcValue(sensorMax);
  return true;
}

void AUSEX_GROVE_ANALOG_CURRENT_SENSOR_CLASS::getSensor(sensor_t* sensor){
  /* Clear the sensor_t object */
  memset(sensor, 0, sizeof(sensor_t));

  /* Insert the sensor name in the fixed length char array */
  strncpy (sensor->name, AUSEX_GROVE_ANALOG_CURRENT_SENSOR_NAME , sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  sensor->version     = AUSEX_GROVE_ANALOG_CURRENT_SENSOR_LIBRARY_VERSION;
  sensor->sensor_id   = _sensorID;
  sensor->type        = AUSEX_GROVE_ANALOG_CURRENT_SENSOR_TYPE;
  sensor->min_value   = AUSEX_GROVE_ANALOG_CURRENT_SENSOR_MIN_VALUE;
  sensor->max_value   = sensorMaxValue;
  sensor->resolution  = AUSEX_GROVE_ANALOG_CURRENT_SENSOR_RESOLUTION;
  sensor->min_delay   = AUSEX_GROVE_ANALOG_CURRENT_SENSOR_MIN_DELAY;
  sensor->init_delay  = AUSEX_GROVE_ANALOG_CURRENT_SENSOR_INIT_DELAY;
}


bool AUSEX_GROVE_ANALOG_CURRENT_SENSOR_CLASS::enableAutoRange(bool enabled) {
  return false;
}

int AUSEX_GROVE_ANALOG_CURRENT_SENSOR_CLASS::setMode(int mode) {
  if ((mode > 1) ||( mode < 0) ) return 0;
  if (mode == 0) {
    sensorMaxValue=AUSEX_GROVE_ANALOG_CURRENT_SENSOR_AVE_MAX_VALUE;
  } else {
    sensorMaxValue=AUSEX_GROVE_ANALOG_CURRENT_SENSOR_PEAK_MAX_VALUE;
  }
  _mode=mode;
  return 1;
}

int AUSEX_GROVE_ANALOG_CURRENT_SENSOR_CLASS::getMode(void) {
  return _mode;
}

AUSEX_GROVE_ANALOG_CURRENT_SENSOR_VALUE_TYPE AUSEX_GROVE_ANALOG_CURRENT_SENSOR_CLASS::calcValue(int val){
  if (_mode == 0 ) return (float)val/1024*_vdd/800*2000000/1.414;
  return (float)val/1024*_vdd/800*2000000;
}
