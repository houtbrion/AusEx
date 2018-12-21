#ifndef __GROVE_ROTARY_ANGLE_SENSOR_AUSEX_H__
#define __GROVE_ROTARY_ANGLE_SENSOR_AUSEX_H__

#define _TEMPLATE_CLASS GroveRotaryAngleSensorAusEx
#define _SENSOR_NAME "GroveRotaryAngleSensorAusEx"
#define _SENSOR_TYPE SENSOR_TYPE_ANGLE
#define _SENSOR_LIBRARY_VERSION 1
#define _SENSOR_RETURN_VALUE angle
#define _DEFAULT_VDD_ 5
#define FULL_ANGLE 300
#define _SENSOR_MIN_VALUE 0
#define _SENSOR_MAX_VALUE FULL_ANGLE
#define _SENSOR_RESOLUTION 0.29296875
#define _SENSOR_MIN_DELAY 0

#include "AusEx.h"


class _TEMPLATE_CLASS : public Adafruit_SensorEx {
public:
  _TEMPLATE_CLASS(int pinNumber,int32_t sensorID = -1);
  _TEMPLATE_CLASS(int pinNumber,float vdd, int32_t sensorID = -1);
  bool begin(void);
  bool getEvent(sensors_event_t*);
  void getSensor(sensor_t*);
  bool enableAutoRange(bool enabled);
  int setMode(int mode);

private:
  int _pin;
  float _vdd;
  uint32_t _sensorID;
  float calcValue(int);
  bool _autoRange;
};



#endif /* __GROVE_ROTARY_ANGLE_SENSOR_AUSEX_H__ */
