#ifndef __AUSEX_GROVE_SIMPLE_MOISTURE_H__
#define __AUSEX_GROVE_SIMPLE_MOISTURE_H__

#define AUSEX_GROVE_SIMPLE_MOISTURE_CLASS AusExGroveSimpleMoisture
#define AUSEX_GROVE_SIMPLE_MOISTURE_SENSOR_NAME "AusExGroveSimpleMoisture"
#define AUSEX_GROVE_SIMPLE_MOISTURE_SENSOR_TYPE SENSOR_TYPE_SIMPLE_ANALOG
#define AUSEX_GROVE_SIMPLE_MOISTURE_SENSOR_LIBRARY_VERSION 1
#define AUSEX_GROVE_SIMPLE_MOISTURE_SENSOR_RETURN_VALUE value
#define AUSEX_GROVE_SIMPLE_MOISTURE_SENSOR_VALUE_TYPE uint32_t
#define AUSEX_GROVE_SIMPLE_MOISTURE_DEFAULT_VDD 5
#define AUSEX_GROVE_SIMPLE_MOISTURE_SENSOR_MIN_VALUE 0
#define AUSEX_GROVE_SIMPLE_MOISTURE_SENSOR_MAX_VALUE 1023
#define AUSEX_GROVE_SIMPLE_MOISTURE_SENSOR_RESOLUTION 1
#define AUSEX_GROVE_SIMPLE_MOISTURE_SENSOR_MIN_DELAY 0
#define AUSEX_GROVE_SIMPLE_MOISTURE_SENSOR_INIT_DELAY 0

#include "AusEx.h"


class AUSEX_GROVE_SIMPLE_MOISTURE_CLASS : public Adafruit_SensorEx {
public:
  AUSEX_GROVE_SIMPLE_MOISTURE_CLASS(int pinNumber, int32_t sensorID = -1);
  AUSEX_GROVE_SIMPLE_MOISTURE_CLASS(int pinNumber,float vdd, int32_t sensorID = -1);
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
  AUSEX_GROVE_SIMPLE_MOISTURE_SENSOR_VALUE_TYPE calcValue(int);
  bool _autoRange;
};



#endif /* __AUSEX_GROVE_SIMPLE_MOISTURE_H__ */
