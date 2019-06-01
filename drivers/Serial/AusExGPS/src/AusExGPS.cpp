#include "AusExGPS.h"

/*
 * 
 */

AUSEX_GPS_CLASS::AUSEX_GPS_CLASS(SoftwareSerial *port, int32_t positionID , int32_t dateID , int32_t orientationID , int32_t speedID ) :
  _port(port),
  _position(this,positionID),
  _dateTime(this,dateID),
  _orientation(this,orientationID),
  _speed(this,speedID)
{}

AUSEX_GPS_CLASS::Position::Position(AusExGPS * parent, int32_t id) :
  _parent(parent),
  _id(id)
{}

AUSEX_GPS_CLASS::Date::Date(AusExGPS * parent, int32_t id) :
  _parent(parent),
  _id(id)
{}

AUSEX_GPS_CLASS::Orientation::Orientation(AusExGPS * parent, int32_t id) :
  _parent(parent),
  _id(id)
{}

AUSEX_GPS_CLASS::Speed::Speed(AusExGPS * parent, int32_t id) :
  _parent(parent),
  _id(id)
{}

bool AUSEX_GPS_CLASS::begin(uint32_t bps, byte conf){
  //_port->begin(bps,conf);
  _port->begin(bps);
  duration = (uint16_t) AUSEX_GPS_DURATION;
  return true;
}

void AUSEX_GPS_CLASS::Position::getSensor(sensor_t* sensor){
  /* Clear the sensor_t object */
  memset(sensor, 0, sizeof(sensor_t));

  /* Insert the sensor name in the fixed length char array */
  strncpy (sensor->name, AUSEX_GPS_NAME , sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  sensor->version     = AUSEX_GPS_LIBRARY_VERSION;
  sensor->sensor_id   = _id;
  sensor->type        = SENSOR_TYPE_POSITION;
  sensor->min_value   = AUSEX_GPS_MIN_VALUE;
  sensor->max_value   = AUSEX_GPS_MAX_VALUE;
  sensor->resolution  = AUSEX_GPS_RESOLUTION;
  sensor->min_delay   = AUSEX_GPS_MIN_DELAY;
  sensor->init_delay   = AUSEX_GPS_INIT_DELAY;
}

void AUSEX_GPS_CLASS::Date::getSensor(sensor_t* sensor){
  /* Clear the sensor_t object */
  memset(sensor, 0, sizeof(sensor_t));

  /* Insert the sensor name in the fixed length char array */
  strncpy (sensor->name, AUSEX_GPS_NAME , sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  sensor->version     = AUSEX_GPS_LIBRARY_VERSION;
  sensor->sensor_id   = _id;
  sensor->type        = SENSOR_TYPE_DATE;
  sensor->min_value   = AUSEX_GPS_MIN_VALUE;
  sensor->max_value   = AUSEX_GPS_MAX_VALUE;
  sensor->resolution  = AUSEX_GPS_RESOLUTION;
  sensor->min_delay   = AUSEX_GPS_MIN_DELAY;
  sensor->init_delay   = AUSEX_GPS_INIT_DELAY;
}

void AUSEX_GPS_CLASS::Orientation::getSensor(sensor_t* sensor){
  /* Clear the sensor_t object */
  memset(sensor, 0, sizeof(sensor_t));

  /* Insert the sensor name in the fixed length char array */
  strncpy (sensor->name, AUSEX_GPS_NAME , sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  sensor->version     = AUSEX_GPS_LIBRARY_VERSION;
  sensor->sensor_id   = _id;
  sensor->type        = SENSOR_TYPE_ORIENTATION;
  sensor->min_value   = AUSEX_GPS_MIN_VALUE;
  sensor->max_value   = AUSEX_GPS_MAX_VALUE;
  sensor->resolution  = AUSEX_GPS_RESOLUTION;
  sensor->min_delay   = AUSEX_GPS_MIN_DELAY;
  sensor->init_delay   = AUSEX_GPS_INIT_DELAY;
}

void AUSEX_GPS_CLASS::Speed::getSensor(sensor_t* sensor){
  /* Clear the sensor_t object */
  memset(sensor, 0, sizeof(sensor_t));

  /* Insert the sensor name in the fixed length char array */
  strncpy (sensor->name, AUSEX_GPS_NAME , sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  sensor->version     = AUSEX_GPS_LIBRARY_VERSION;
  sensor->sensor_id   = _id;
  sensor->type        = SENSOR_TYPE_SPEED;
  sensor->min_value   = AUSEX_GPS_MIN_VALUE;
  sensor->max_value   = AUSEX_GPS_MAX_VALUE;
  sensor->resolution  = AUSEX_GPS_RESOLUTION;
  sensor->min_delay   = AUSEX_GPS_MIN_DELAY;
  sensor->init_delay   = AUSEX_GPS_INIT_DELAY;
}

bool AUSEX_GPS_CLASS::readGPS(int8_t type){
  unsigned long start = millis();
  do {
    while (_port->available()) gps.encode(_port->read());
  } while (millis() - start < (unsigned long) duration);
  //
  if (gps.hdop.isValid()) _pos.dop=gps.hdop.hdop();
  if (gps.location.isValid()) {
    _pos.longtitude=gps.location.lng();
    _pos.latitude=gps.location.lat();
  }
  if (gps.altitude.isValid()) _pos.altitude=gps.altitude.meters();
  if (gps.date.isValid()) {
    _date.year=gps.date.year();
    _date.month=gps.date.month();
    _date.day=gps.date.day();
  }
  if (gps.time.isValid()) {
    _date.hour=gps.time.hour();
    _date.minute=gps.time.minute();
    _date.second=gps.time.second();
  }
  _date.millisecond=-1;
  if (gps.course.isValid()) {
    _orient.heading=gps.course.deg();
  }
  if (gps.speed.isValid()) _spd=gps.speed.knots();
  switch(type) {
    case SENSOR_TYPE_POSITION    : if ((gps.hdop.isValid()) && (gps.location.isValid()) && (gps.altitude.isValid())) return true; else return false;
    case SENSOR_TYPE_DATE        : if ((gps.date.isValid()) && (gps.time.isValid()) ) return true; else return false;
    case SENSOR_TYPE_ORIENTATION : if (gps.course.isValid()) return true; else return false;
    case SENSOR_TYPE_SPEED       : if (gps.speed.isValid()) return true; else return false;
  }
  if (gps.satellites.isValid()) {
    _sat = gps.satellites.value();
    return true;
  }
  _sat = 0;
  return false;
}

bool AUSEX_GPS_CLASS::Position::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));
  event->version   = sizeof(sensors_event_t);
  event->sensor_id = _id;
  event->type      = SENSOR_TYPE_POSITION;
  event->timestamp = millis();
  bool flag = _parent->readGPS(SENSOR_TYPE_POSITION);
  event->position.longtitude = _parent->_pos.longtitude;
  event->position.latitude = _parent->_pos.latitude;
  event->position.altitude = _parent->_pos.altitude;
  event->position.dop = _parent->_pos.dop;
  return flag;
}

bool AUSEX_GPS_CLASS::Date::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));
  event->version   = sizeof(sensors_event_t);
  event->sensor_id = _id;
  event->type      = SENSOR_TYPE_DATE;
  event->timestamp = millis();
  bool flag = _parent->readGPS(SENSOR_TYPE_DATE);
  event->date.year=_parent->_date.year;
  event->date.month=_parent->_date.month;
  event->date.day=_parent->_date.day;
  event->date.hour=_parent->_date.hour;
  event->date.minute=_parent->_date.minute;
  event->date.second=_parent->_date.second;
  event->date.millisecond=_parent->_date.millisecond;
  return flag;
}

bool AUSEX_GPS_CLASS::Orientation::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));
  event->version   = sizeof(sensors_event_t);
  event->sensor_id = _id;
  event->type      = SENSOR_TYPE_ORIENTATION;
  event->timestamp = millis();
  bool flag = _parent->readGPS(SENSOR_TYPE_ORIENTATION);
  event->orientation.heading=_parent->_orient.heading;
  return flag;
}

bool AUSEX_GPS_CLASS::Speed::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));
  event->version   = sizeof(sensors_event_t);
  event->sensor_id = _id;
  event->type      = SENSOR_TYPE_SPEED;
  event->timestamp = millis();
  bool flag = _parent->readGPS(SENSOR_TYPE_SPEED);
  event->speed=_parent->_spd;
  return flag;
}

bool AUSEX_GPS_CLASS::enableAutoRange(bool enabled) {
  return false;
}
bool AUSEX_GPS_CLASS::Position::enableAutoRange(bool enabled) {
  return _parent->enableAutoRange(enabled);
}
bool AUSEX_GPS_CLASS::Date::enableAutoRange(bool enabled) {
  return _parent->enableAutoRange(enabled);
}
bool AUSEX_GPS_CLASS::Orientation::enableAutoRange(bool enabled) {
  return _parent->enableAutoRange(enabled);
}
bool AUSEX_GPS_CLASS::Speed::enableAutoRange(bool enabled) {
  return _parent->enableAutoRange(enabled);
}

int AUSEX_GPS_CLASS::setMode(int mode) {
  if ((AUSEX_GPS_DURATION_MIN > mode) || (AUSEX_GPS_DURATION_MAX < mode)) {
    return false;
  }
  duration=(uint16_t)mode;
  return true;
}
int AUSEX_GPS_CLASS::Position::setMode(int mode) {
  return _parent->setMode(mode);
}
int AUSEX_GPS_CLASS::Date::setMode(int mode) {
  return _parent->setMode(mode);
}
int AUSEX_GPS_CLASS::Orientation::setMode(int mode) {
  return _parent->setMode(mode);
}
int AUSEX_GPS_CLASS::Speed::setMode(int mode) {
  return _parent->setMode(mode);
}
int AUSEX_GPS_CLASS::getMode(void) {
  readGPS(0xFF);
  int mode = ((int) _sat << 16) | (int) duration;
  return mode;
}
int AUSEX_GPS_CLASS::Position::getMode(void) {
  return _parent->getMode();
}
int AUSEX_GPS_CLASS::Date::getMode(void) {
  return _parent->getMode();
}
int AUSEX_GPS_CLASS::Orientation::getMode(void) {
  return _parent->getMode();
}
int AUSEX_GPS_CLASS::Speed::getMode(void) {
  return _parent->getMode();
}
