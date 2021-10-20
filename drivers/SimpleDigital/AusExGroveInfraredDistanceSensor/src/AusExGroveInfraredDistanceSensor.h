#ifndef __AUSEX_GROVE_IR_DISTANCE_H__
#define __AUSEX_GROVE_IR_DISTANCE_H__

#define AUSEX_GROVE_IR_DISTANCE_CLASS AusExGroveInfraredDistanceSensor
#define AUSEX_GROVE_IR_DISTANCE_SENSOR_NAME "AusExGroveInfraredDistanceSensor"
#define AUSEX_GROVE_IR_DISTANCE_SENSOR_TYPE SENSOR_TYPE_SIMPLE
#define AUSEX_GROVE_IR_DISTANCE_SENSOR_LIBRARY_VERSION 1
#define AUSEX_GROVE_IR_DISTANCE_SENSOR_RETURN_VALUE value
#define AUSEX_GROVE_IR_DISTANCE_SENSOR_VALUE_TYPE uint32_t
#define AUSEX_GROVE_IR_DISTANCE_SENSOR_MIN_VALUE 0
#define AUSEX_GROVE_IR_DISTANCE_SENSOR_MAX_VALUE 1
#define AUSEX_GROVE_IR_DISTANCE_SENSOR_RESOLUTION 1
#define AUSEX_GROVE_IR_DISTANCE_SENSOR_MIN_DELAY 0
#define AUSEX_GROVE_IR_DISTANCE_SENSOR_INIT_DELAY 0

#include "AusEx.h"


class AUSEX_GROVE_IR_DISTANCE_CLASS : public Adafruit_SensorEx {
public:
  AUSEX_GROVE_IR_DISTANCE_CLASS(int pinNumber, int32_t sensorID = -1);
  bool begin(bool pullUp=false);
  bool getEvent(sensors_event_t*);
  void getSensor(sensor_t*);
  bool enableAutoRange(bool enabled);
  int setMode(int mode);
  int getMode(void);

private:
  int _pin;
  uint32_t _sensorID;
  AUSEX_GROVE_IR_DISTANCE_SENSOR_VALUE_TYPE calcValue(int);
  bool _autoRange;
};



#endif /* __AUSEX_GROVE_IR_DISTANCE_H__ */
