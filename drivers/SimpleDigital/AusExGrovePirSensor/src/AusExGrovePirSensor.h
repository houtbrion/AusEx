#ifndef __GROVE_PIR_SENSOR_AUSEX_H__
#define __GROVE_PIR_SENSOR_AUSEX_H__

#define AUSEX_GROVE_PIR_SENSOR_CLASS AusExGrovePirSensor
#define AUSEX_GROVE_PIR_SENSOR_NAME "AusExGrovePirSensor"
#define AUSEX_GROVE_PIR_SENSOR_TYPE SENSOR_TYPE_SIMPLE
#define AUSEX_GROVE_PIR_SENSOR_LIBRARY_VERSION 1
#define AUSEX_GROVE_PIR_SENSOR_RETURN_VALUE value
#define AUSEX_GROVE_PIR_SENSOR_VALUE_TYPE uint32_t
#define AUSEX_GROVE_PIR_SENSOR_MIN_VALUE 0
#define AUSEX_GROVE_PIR_SENSOR_MAX_VALUE 1
#define AUSEX_GROVE_PIR_SENSOR_RESOLUTION 1
#define AUSEX_GROVE_PIR_SENSOR_MIN_DELAY 0
#define AUSEX_GROVE_PIR_SENSOR_INIT_DELAY 30000000

#include "AusEx.h"


class AUSEX_GROVE_PIR_SENSOR_CLASS : public Adafruit_SensorEx {
public:
  AUSEX_GROVE_PIR_SENSOR_CLASS(int pinNumber, uint32_t sensorID = -1);
  bool begin(bool pullUp=false);
  bool getEvent(sensors_event_t*);
  void getSensor(sensor_t*);
  bool enableAutoRange(bool enabled);
  int setMode(int mode);
  int getMode();

private:
  int _pin;
  int _pullUp;
  uint32_t _sensorID;
  AUSEX_GROVE_PIR_SENSOR_VALUE_TYPE calcValue(int);
  bool _autoRange;
};



#endif /* __GROVE_PIR_SENSOR_AUSEX_H__ */
