#ifndef __AUSEX_GPS_H__
#define __AUSEX_GPS_H__

#define AUSEX_GPS_CLASS AusExGPS
#define AUSEX_GPS_NAME "GPS"
#define AUSEX_GPS_TYPE SENSOR_TYPE_SIMPLE
#define AUSEX_GPS_LIBRARY_VERSION 1
#define AUSEX_GPS_RETURN_VALUE value
#define AUSEX_GPS_VALUE_TYPE uint32_t
#define AUSEX_GPS_MIN_VALUE 0
#define AUSEX_GPS_MAX_VALUE 1
#define AUSEX_GPS_RESOLUTION 1
#define AUSEX_GPS_MIN_DELAY 0
#define AUSEX_GPS_INIT_DELAY 0

#define AUSEX_MAX_DATA_STRING 512
#define AUSEX_GPS_DEFAULT_BPS 9600
#define AUSEX_GPS_DURATION     3000
#define AUSEX_GPS_DURATION_MIN 1000
#define AUSEX_GPS_DURATION_MAX 65535

#include "AusEx.h"
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

class AUSEX_GPS_CLASS {
public:
  //AUSEX_GPS_CLASS(serial_t *port, int32_t positionID = -1, int32_t dateID = -1, int32_t orientationID = -1, int32_t speedID = -1);
  AUSEX_GPS_CLASS(SoftwareSerial *port, int32_t positionID = -1, int32_t dateID = -1, int32_t orientationID = -1, int32_t speedID = -1);
  bool begin(uint32_t bps, byte conf = SERIAL_8N1 );
  bool enableAutoRange(bool enabled);
  int  setMode(int mode);
  int  getMode();

  class Position : Adafruit_SensorEx {
  public:
    Position(AusExGPS * parent, int32_t id);
    bool getEvent(sensors_event_t* event);
    void getSensor(sensor_t* sensor);
    bool enableAutoRange(bool);
    int  setMode(int);
    int  getMode();
  private:
    AusExGPS * _parent;
    int32_t    _id;
  };

  class Date : Adafruit_SensorEx {
  public:
    Date(AusExGPS * parent, int32_t id);
    bool getEvent(sensors_event_t* event);
    void getSensor(sensor_t* sensor);
    bool enableAutoRange(bool);
    int  setMode(int);
    int  getMode();
  private:
    AusExGPS * _parent;
    int32_t    _id;
  };

  class Orientation : Adafruit_SensorEx {
  public:
    Orientation(AusExGPS * parent, int32_t id);
    bool getEvent(sensors_event_t* event);
    void getSensor(sensor_t* sensor);
    bool enableAutoRange(bool);
    int  setMode(int);
    int  getMode();
  private:
    AusExGPS * _parent;
    int32_t    _id;
  };

  class Speed : Adafruit_SensorEx {
  public:
    Speed(AusExGPS * parent, int32_t id);
    bool getEvent(sensors_event_t* event);
    void getSensor(sensor_t* sensor);
    bool enableAutoRange(bool);
    int  setMode(int);
    int  getMode();
  private:
    AusExGPS * _parent;
    int32_t    _id;
  };

  Position position() {
    return _position;
  };

  Date date() {
    return _dateTime;
  };

  Orientation orientation() {
    return _orientation;
  };

  Speed speed() {
    return _speed;
  };
  sensors_position_t _pos;
  sensors_date_t     _date;
  sensors_vec_t      _orient;
  float             _spd;
  uint8_t           _sat;

private:
  TinyGPSPlus gps;
  SoftwareSerial * _port;
  uint16_t       duration;
  Position        _position;
  Date            _dateTime;
  Orientation     _orientation;
  Speed           _speed;
  //bool            _autoRange;

  bool              readGPS(int8_t);
};

#endif /* __AUSEX_GPS_H__ */
