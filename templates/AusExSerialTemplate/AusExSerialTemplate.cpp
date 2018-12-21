#include "AusExSerialTemplate.h"

/*
 * 
 */

_TEMPLATE_CLASS::_TEMPLATE_CLASS(uint32_t sensorID = -1){
  _h_port = &Serial;
  mode=0;
  _sensorID=sensorID;
  _multi = false;
}


_TEMPLATE_CLASS::_TEMPLATE_CLASS(HardwareSerial *port, uint32_t sensorID = -1){
  _h_port = port;
  mode=0;
  _sensorID=sensorID;
  _multi=false;
}


_TEMPLATE_CLASS::_TEMPLATE_CLASS(SoftwareSerial *port, uint32_t sensorID = -1){
  _port = port;
  mode=1;
  _sensorID=sensorID;
  _multi = false;
}

_TEMPLATE_CLASS::_TEMPLATE_CLASS(SoftwareSerial *port, bool multi, uint32_t sensorID = -1){
  _port = port;
  _sensorID=sensorID;
  _multi = multi;
  if (multi) {
    mode=2;
  } else {
    mode=1;
  }
}


bool _TEMPLATE_CLASS::begin(long baud){
  if (mode != 0) {
    _port->begin(baud);
  } else {
    _h_port->begin(baud);
  }
  return true;
}


bool _TEMPLATE_CLASS::begin(long baud, byte s_config){
  if (mode!=0) {
    return false;
  } else {
    _h_port->begin(baud,s_config);
    return true;
  }
}


String _TEMPLATE_CLASS::readHard(void){
  int count=0;
  char buffer[_MAX_DATA_STRING];
  memset(buffer,0,_MAX_DATA_STRING);
  if (_h_port->available()){
    while(_h_port->available()) {
      buffer[count++]=_h_port->read();
      if(count == _MAX_DATA_STRING) break;
    }
    return String(buffer);
  }
  return "";
}

String _TEMPLATE_CLASS::read(void){
  int count=0;
  char buffer[_MAX_DATA_STRING];
  memset(buffer,0,_MAX_DATA_STRING);
  if (_port->available()){
    while(_port->available()) {
      buffer[count++]=_port->read();
      if(count == _MAX_DATA_STRING) break;
    }
    return String(buffer);
  }
  return "";
}

bool _TEMPLATE_CLASS::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->version   = sizeof(sensors_event_t);
  event->sensor_id = _sensorID;
  event->type      = _SENSOR_TYPE;
  event->timestamp = millis();

  /* Calculate the actual lux value */
  if (mode != 0) {
    event->_SENSOR_RETURN_VALUE = calcValue(read());
  } else {
    event->_SENSOR_RETURN_VALUE = calcValue(readHard());
  }
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

_SENSOR_VALUE_TYPE _TEMPLATE_CLASS::calcValue(String val){
  return 0;
}
