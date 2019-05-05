#ifndef __AUSEX_GROVE_ULTRASONIC_RANGER_H__
#define __AUSEX_GROVE_ULTRASONIC_RANGER_H__

#define AUSEX_GROVE_ULTRASONIC_RANGER_CLASS AusExGroveUltrasonicRanger
#define AUSEX_GROVE_ULTRASONIC_RANGER_SENSOR_NAME "AusExGroveUltrasonicRanger"
#define AUSEX_GROVE_ULTRASONIC_RANGER_SENSOR_TYPE SENSOR_TYPE_DISTANCE
#define AUSEX_GROVE_ULTRASONIC_RANGER_SENSOR_LIBRARY_VERSION 1
#define AUSEX_GROVE_ULTRASONIC_RANGER_SENSOR_RETURN_VALUE distance
#define AUSEX_GROVE_ULTRASONIC_RANGER_SENSOR_VALUE_TYPE float
#define AUSEX_GROVE_ULTRASONIC_RANGER_SENSOR_MIN_VALUE 0
#define AUSEX_GROVE_ULTRASONIC_RANGER_SENSOR_MAX_VALUE 1
#define AUSEX_GROVE_ULTRASONIC_RANGER_SENSOR_RESOLUTION 1
#define AUSEX_GROVE_ULTRASONIC_RANGER_SENSOR_MIN_DELAY 0
#define AUSEX_GROVE_ULTRASONIC_RANGER_SENSOR_INIT_DELAY 0

#include "AusEx.h"


class AUSEX_GROVE_ULTRASONIC_RANGER_CLASS : public Adafruit_SensorEx {
public:
  AUSEX_GROVE_ULTRASONIC_RANGER_CLASS(int pinNumber, int32_t sensorID = -1);
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
  uint32_t _sensorID;
  AUSEX_GROVE_ULTRASONIC_RANGER_SENSOR_VALUE_TYPE calcValue(long);
  bool _autoRange;
};



#endif /* __AUSEX_GROVE_ULTRASONIC_RANGER_H__ */
