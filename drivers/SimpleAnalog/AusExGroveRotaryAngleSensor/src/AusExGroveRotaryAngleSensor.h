#ifndef __AUSEX_GROVE_ROTARY_ANGLE_SENSOR_H__
#define __AUSEX_GROVE_ROTARY_ANGLE_SENSOR_H__

#define AUSEX_GROVE_ROTARY_ANGLE_CLASS AusExGroveRotaryAngleSensor
#define AUSEX_GROVE_ROTARY_ANGLE_SENSOR_NAME "AusExGroveRotaryAngleSensor"
#define AUSEX_GROVE_ROTARY_ANGLE_SENSOR_TYPE SENSOR_TYPE_ANGLE
#define AUSEX_GROVE_ROTARY_ANGLE_SENSOR_LIBRARY_VERSION 1
#define AUSEX_GROVE_ROTARY_ANGLE_SENSOR_RETURN_VALUE angle
#define AUSEX_GROVE_ROTARY_ANGLE_SENSOR_RETURN_VALUE_TYPE float
#define AUSEX_GROVE_ROTARY_ANGLE_DEFAULT_VDD 5
#define FULL_ANGLE 300
#define AUSEX_GROVE_ROTARY_ANGLE_SENSOR_MIN_VALUE 0
#define AUSEX_GROVE_ROTARY_ANGLE_SENSOR_MAX_VALUE FULL_ANGLE
#define AUSEX_GROVE_ROTARY_ANGLE_SENSOR_RESOLUTION 0.29296875
#define AUSEX_GROVE_ROTARY_ANGLE_SENSOR_MIN_DELAY 0
#define AUSEX_GROVE_ROTARY_ANGLE_SENSOR_INIT_DELAY 0

#include "AusEx.h"


class AUSEX_GROVE_ROTARY_ANGLE_CLASS : public Adafruit_SensorEx {
public:
  AUSEX_GROVE_ROTARY_ANGLE_CLASS(int pinNumber,int32_t sensorID = -1);
  AUSEX_GROVE_ROTARY_ANGLE_CLASS(int pinNumber,float vdd, int32_t sensorID = -1);
  bool begin(void);
  bool getEvent(sensors_event_t*);
  void getSensor(sensor_t*);
  bool enableAutoRange(bool enabled);
  int setMode(int mode);
  int getMode(void);

private:
  int _pin;
  float _vdd;
  uint32_t _sensorID;
  AUSEX_GROVE_ROTARY_ANGLE_SENSOR_RETURN_VALUE_TYPE calcValue(int);
  bool _autoRange;
};



#endif /* __AUSEX_GROVE_ROTARY_ANGLE_SENSOR_H__ */
