#include "AusExSerialTemplate.h"

/*
 * 
 */

AUSEX_SERIAL_TEMPLATE_CLASS::AUSEX_SERIAL_TEMPLATE_CLASS(int32_t sensorID = -1){
  _h_port = &Serial;
  mode=0;
  _sensorID=sensorID;
  _multi = false;
}


AUSEX_SERIAL_TEMPLATE_CLASS::AUSEX_SERIAL_TEMPLATE_CLASS(HardwareSerial *port, int32_t sensorID = -1){
  _h_port = port;
  mode=0;
  _sensorID=sensorID;
  _multi=false;
}


AUSEX_SERIAL_TEMPLATE_CLASS::AUSEX_SERIAL_TEMPLATE_CLASS(SoftwareSerial *port, int32_t sensorID = -1){
  _port = port;
  mode=1;
  _sensorID=sensorID;
  _multi = false;
}

AUSEX_SERIAL_TEMPLATE_CLASS::AUSEX_SERIAL_TEMPLATE_CLASS(SoftwareSerial *port, bool multi, int32_t sensorID = -1){
  _port = port;
  _sensorID=sensorID;
  _multi = multi;
  if (multi) {
    mode=2;
  } else {
    mode=1;
  }
}


bool AUSEX_SERIAL_TEMPLATE_CLASS::begin(long baud){
  if (mode != 0) {
    _port->begin(baud);
  } else {
    _h_port->begin(baud);
  }
  return true;
}


bool AUSEX_SERIAL_TEMPLATE_CLASS::begin(long baud, byte s_config){
  if (mode!=0) {
    return false;
  } else {
    _h_port->begin(baud,s_config);
    return true;
  }
}


String AUSEX_SERIAL_TEMPLATE_CLASS::readHard(void){
  int count=0;
  char buffer[AUSEX_SERIAL_TEMPLATE_MAX_DATA_STRING];
  memset(buffer,0,AUSEX_SERIAL_TEMPLATE_MAX_DATA_STRING);
  if (_h_port->available()){
    while(_h_port->available()) {
      buffer[count++]=_h_port->read();
      if(count == AUSEX_SERIAL_TEMPLATE_MAX_DATA_STRING) break;
    }
    return String(buffer);
  }
  return "";
}

String AUSEX_SERIAL_TEMPLATE_CLASS::read(void){
  int count=0;
  char buffer[AUSEX_SERIAL_TEMPLATE_MAX_DATA_STRING];
  memset(buffer,0,AUSEX_SERIAL_TEMPLATE_MAX_DATA_STRING);
  if (_port->available()){
    while(_port->available()) {
      buffer[count++]=_port->read();
      if(count == AUSEX_SERIAL_TEMPLATE_MAX_DATA_STRING) break;
    }
    return String(buffer);
  }
  return "";
}

bool AUSEX_SERIAL_TEMPLATE_CLASS::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->version   = sizeof(sensors_event_t);
  event->sensor_id = _sensorID;
  event->type      = AUSEX_SERIAL_TEMPLATE_SENSOR_TYPE;
  event->timestamp = millis();

  /* Calculate the actual lux value */
  if (mode != 0) {
    event->AUSEX_SERIAL_TEMPLATE_SENSOR_RETURN_VALUE = calcValue(read());
  } else {
    event->AUSEX_SERIAL_TEMPLATE_SENSOR_RETURN_VALUE = calcValue(readHard());
  }
  return true;
}

void AUSEX_SERIAL_TEMPLATE_CLASS::getSensor(sensor_t* sensor){
  /* Clear the sensor_t object */
  memset(sensor, 0, sizeof(sensor_t));

  /* Insert the sensor name in the fixed length char array */
  strncpy (sensor->name, AUSEX_SERIAL_TEMPLATE_SENSOR_NAME , sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  sensor->version     = AUSEX_SERIAL_TEMPLATE_SENSOR_LIBRARY_VERSION;
  sensor->sensor_id   = _sensorID;
  sensor->type        = AUSEX_SERIAL_TEMPLATE_SENSOR_TYPE;
  sensor->min_value   = AUSEX_SERIAL_TEMPLATE_SENSOR_MIN_VALUE;
  sensor->max_value   = AUSEX_SERIAL_TEMPLATE_SENSOR_MAX_VALUE;
  sensor->resolution  = AUSEX_SERIAL_TEMPLATE_SENSOR_RESOLUTION;
  sensor->min_delay   = AUSEX_SERIAL_TEMPLATE_SENSOR_MIN_DELAY;
  sensor->init_delay   = AUSEX_SERIAL_TEMPLATE_SENSOR_INIT_DELAY;
}


bool AUSEX_SERIAL_TEMPLATE_CLASS::enableAutoRange(bool enabled) {
  return false;
}

int AUSEX_SERIAL_TEMPLATE_CLASS::setMode(int mode) {
  return -1;
}

int AUSEX_SERIAL_TEMPLATE_CLASS::getMode() {
  return -1;
}

AUSEX_SERIAL_TEMPLATE_SENSOR_VALUE_TYPE AUSEX_SERIAL_TEMPLATE_CLASS::calcValue(String val){
  return 0;
}
