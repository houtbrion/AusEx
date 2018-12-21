#ifndef __GENERAL_ANALOG_1AXIS_GYRO_AUS_EX_H__
#define __GENERAL_ANALOG_1AXIS_GYRO_AUS_EX_H__

#define _TEMPLATE_CLASS GroveAnalog1AxisGyroAusEx
#define _SENSOR_NAME "GroveAnalog1AxisGyroAusEx"
#define _SENSOR_TYPE SENSOR_TYPE_1AXIS_GYRO
#define _SENSOR_LIBRARY_VERSION 1
#define _SENSOR_RETURN_VALUE roll
#define _SENSOR_VALUE_TYPE float
#define _DEFAULT_VDD_ 5
#define _SENSOR_MIN_VALUE 0
#define _SENSOR_MAX_VALUE 7388.0597014925373134328358208955
#define _SENSOR_RESOLUTION 7.2219547424169475204622051035147
#define _SENSOR_MIN_DELAY 0

#include "AusEx.h"


class _TEMPLATE_CLASS : public Adafruit_SensorEx {
public:
  _TEMPLATE_CLASS(int pinNumber, int32_t sensorID = -1);
  _TEMPLATE_CLASS(int pinNumber,float vdd, int32_t sensorID = -1);
  bool begin(void);
  bool getEvent(sensors_event_t*);
  void getSensor(sensor_t*);
  bool enableAutoRange(bool enabled);
  int setMode(int mode);

private:
  int _pin;
  float _vdd;
  int32_t _sensorID;
  _SENSOR_VALUE_TYPE calcValue(int);
  bool _autoRange;
};



#endif /* __GENERAL_ANALOG_1AXIS_GYRO_AUS_EX_H__ */
