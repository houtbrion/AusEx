#ifndef __GROVE_ANALOG_CURRENT_SENSOR_AUSEX_H__
#define __GROVE_ANALOG_CURRENT_SENSOR_AUSEX_H__

#define _TEMPLATE_CLASS GroveAnalogCurrentSensorAusEx
#define _SENSOR_NAME "GroveAnalogCurrentSensorAusEx"
#define _SENSOR_TYPE SENSOR_TYPE_CURRENT
#define _SENSOR_LIBRARY_VERSION 1
#define _SENSOR_RETURN_VALUE current
#define _SENSOR_VALUE_TYPE float
#define _DEFAULT_VDD_ 5
#define _SENSOR_MIN_VALUE 0
#define _SENSOR_MAX_VALUE 8840.1697312588401697312588401697
#define _SENSOR_RESOLUTION 8.6329561527581329561527581329562
#define _SENSOR_MIN_DELAY 1000000
#define _SENSOR_MIN_DELAY_MILLI 1000

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



#endif /* __GROVE_ANALOG_CURRENT_SENSOR_AUSEX_H__ */
