#ifndef __AUSEX_DIGITAL_SENSOR_TEMPLATE_H__
#define __AUSEX_DIGITAL_SENSOR_TEMPLATE_H__



#define AUSEX_DIGITAL_TEMPLATE_CLASS AusExDigitalTemplate
#define AUSEX_DIGITAL_TEMPLATE_SENSOR_NAME "AusExDigitalTemplate"
#define AUSEX_DIGITAL_TEMPLATE_SENSOR_TYPE SENSOR_TYPE_SIMPLE
#define AUSEX_DIGITAL_TEMPLATE_SENSOR_LIBRARY_VERSION 1
#define AUSEX_DIGITAL_TEMPLATE_SENSOR_RETURN_VALUE value
#define AUSEX_DIGITAL_TEMPLATE_SENSOR_VALUE_TYPE uint32_t
#define AUSEX_DIGITAL_TEMPLATE_SENSOR_MIN_VALUE 0
#define AUSEX_DIGITAL_TEMPLATE_SENSOR_MAX_VALUE 1
#define AUSEX_DIGITAL_TEMPLATE_SENSOR_RESOLUTION 1
#define AUSEX_DIGITAL_TEMPLATE_SENSOR_MIN_DELAY 0

#include "AusEx.h"


class AUSEX_DIGITAL_TEMPLATE_CLASS : public Adafruit_SensorEx {
public:
  AUSEX_DIGITAL_TEMPLATE_CLASS(int, int32_t sensorID = -1);
  bool begin(bool pullUp=false);
  bool getEvent(sensors_event_t*);
  void getSensor(sensor_t*);
  bool enableAutoRange(bool);
  int setMode(int);
  int getMode();

private:
  int _pin;
  int _mode;
  uint32_t _sensorID;
  AUSEX_DIGITAL_TEMPLATE_SENSOR_VALUE_TYPE calcValue(int);
  bool _autoRange;
};



#endif /* __AUSEX_DIGITAL_SENSOR_TEMPLATE_H__ */
