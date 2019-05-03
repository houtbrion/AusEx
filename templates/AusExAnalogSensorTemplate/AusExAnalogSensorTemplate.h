#ifndef __AUSEX_ANALOG_SENSOR_TEMPLATE_H__
#define __AUSEX_ANALOG_SENSOR_TEMPLATE_H__

#include "AusEx.h"

#define AUSEX_ANALOG_TEMPLATE_CLASS AusExAnalogTemplate
#define AUSEX_ANALOG_TEMPLATE_SENSOR_NAME "AusExAnalogTemplate"
#define AUSEX_ANALOG_TEMPLATE_SENSOR_TYPE SENSOR_TYPE_SIMPLE
#define AUSEX_ANALOG_TEMPLATE_SENSOR_LIBRARY_VERSION 1
#define AUSEX_ANALOG_TEMPLATE_SENSOR_RETURN_VALUE value
#define AUSEX_ANALOG_TEMPLATE_SENSOR_VALUE_TYPE uint32_t
#define AUSEX_ANALOG_TEMPLATE_DEFAULT_VDD 5
#define AUSEX_ANALOG_TEMPLATE_SENSOR_MIN_VALUE 0
#define AUSEX_ANALOG_TEMPLATE_SENSOR_MAX_VALUE 1023
#define AUSEX_ANALOG_TEMPLATE_SENSOR_RESOLUTION 1
#define AUSEX_ANALOG_TEMPLATE_SENSOR_MIN_DELAY 0




class AUSEX_ANALOG_TEMPLATE_CLASS : public Adafruit_SensorEx {
public:
  AUSEX_ANALOG_TEMPLATE_CLASS(int, float vdd=AUSEX_ANALOG_TEMPLATE_DEFAULT_VDD, int32_t sensorID = -1);
  bool begin(void);
  bool getEvent(sensors_event_t*);
  void getSensor(sensor_t*);
  bool enableAutoRange(bool);
  int setMode(int);
  int getMode();

private:
  int _pin;
  float _vdd;
  int32_t _sensorID;
  AUSEX_ANALOG_TEMPLATE_SENSOR_VALUE_TYPE calcValue(int);
  bool _autoRange;
};



#endif /* __AUSEX_ANALOG_SENSOR_TEMPLATE_H__ */
