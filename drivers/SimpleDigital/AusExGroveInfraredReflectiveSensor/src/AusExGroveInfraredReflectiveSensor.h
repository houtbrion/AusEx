#ifndef __AUSEX_GROVE_INFRARED_REFLECTIVE_H__
#define __AUSEX_GROVE_INFRARED_REFLECTIVE_H__

#define AUSEX_GROVE_INFRARED_REFLECTIVE_CLASS AusExGroveInfraredReflectiveSensor
#define AUSEX_GROVE_INFRARED_REFLECTIVE_SENSOR_NAME "AusExGroveInfraredReflectiveSensor"
#define AUSEX_GROVE_INFRARED_REFLECTIVE_SENSOR_TYPE SENSOR_TYPE_SIMPLE
#define AUSEX_GROVE_INFRARED_REFLECTIVE_SENSOR_LIBRARY_VERSION 1
#define AUSEX_GROVE_INFRARED_REFLECTIVE_SENSOR_RETURN_VALUE value
#define AUSEX_GROVE_INFRARED_REFLECTIVE_SENSOR_VALUE_TYPE uint32_t
#define AUSEX_GROVE_INFRARED_REFLECTIVE_SENSOR_MIN_VALUE 0
#define AUSEX_GROVE_INFRARED_REFLECTIVE_SENSOR_MAX_VALUE 1
#define AUSEX_GROVE_INFRARED_REFLECTIVE_SENSOR_RESOLUTION 1
#define AUSEX_GROVE_INFRARED_REFLECTIVE_SENSOR_MIN_DELAY 0
#define AUSEX_GROVE_INFRARED_REFLECTIVE_SENSOR_INIT_DELAY 0

#include "AusEx.h"


class AUSEX_GROVE_INFRARED_REFLECTIVE_CLASS : public Adafruit_SensorEx {
public:
  AUSEX_GROVE_INFRARED_REFLECTIVE_CLASS(int pinNumber, int32_t sensorID = -1);
  //_TEMPLATE_CLASS(int pinNumber,bool pullUp, int32_t sensorID = -1);
  //bool begin(void);
  bool begin(bool pullUp=false);
  bool getEvent(sensors_event_t*);
  void getSensor(sensor_t*);
  bool enableAutoRange(bool enabled);
  int setMode(int mode);
  int getMode(void);

private:
  int _pin;
  //int _pullUp;
  uint32_t _sensorID;
  AUSEX_GROVE_INFRARED_REFLECTIVE_SENSOR_VALUE_TYPE calcValue(int);
  bool _autoRange;
};



#endif /* __AUSEX_GROVE_INFRARED_REFLECTIVE_H__ */
