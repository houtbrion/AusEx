#ifndef __GROVE_ULTRASONIC_RANGER_AUSEX_H__
#define __GROVE_ULTRASONIC_RANGER_AUSEX_H__

#define _TEMPLATE_CLASS GroveUltrasonicRangerAusEx
#define _SENSOR_NAME "GroveUltrasonicRangerAusEx"
#define _SENSOR_TYPE SENSOR_TYPE_DISTANCE
#define _SENSOR_LIBRARY_VERSION 1
#define _SENSOR_RETURN_VALUE distance
#define _SENSOR_VALUE_TYPE float
#define _SENSOR_MIN_VALUE 0
#define _SENSOR_MAX_VALUE 1
#define _SENSOR_RESOLUTION 1
#define _SENSOR_MIN_DELAY 0

#include "AusEx.h"


class _TEMPLATE_CLASS : public Adafruit_SensorEx {
public:
  _TEMPLATE_CLASS(int pinNumber, int32_t sensorID = -1);
  //_TEMPLATE_CLASS(int pinNumber,bool pullUp, int32_t sensorID = -1);
  bool begin(void);
  bool getEvent(sensors_event_t*);
  void getSensor(sensor_t*);
  bool enableAutoRange(bool enabled);
  int setMode(int mode);

private:
  int _pin;
  uint32_t _sensorID;
  _SENSOR_VALUE_TYPE calcValue(long);
  bool _autoRange;
};



#endif /* __GROVE_ULTRASONIC_RANGER_AUSEX_H__ */
