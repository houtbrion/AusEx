#ifndef __AUSEX_TEMT6000_H__
#define __AUSEX_TEMT6000_H__

#include "AusEx.h"

#define AUSEX_TEMT6000_CLASS AusExTEMT6000
#define AUSEX_TEMT6000_SENSOR_NAME "TEMT6000"
#define AUSEX_TEMT6000_SENSOR_TYPE SENSOR_TYPE_LIGHT
#define AUSEX_TEMT6000_SENSOR_LIBRARY_VERSION 1
#define AUSEX_TEMT6000_SENSOR_RETURN_VALUE light
#define AUSEX_TEMT6000_SENSOR_VALUE_TYPE float
#define AUSEX_TEMT6000_DEFAULT_VDD 3.3
#define AUSEX_TEMT6000_SENSOR_MIN_VALUE 0
#define AUSEX_TEMT6000_SENSOR_MAX_VALUE 1023
#define AUSEX_TEMT6000_SENSOR_RESOLUTION 1
#define AUSEX_TEMT6000_SENSOR_MIN_DELAY 0
#define AUSEX_TEMT6000_SENSOR_INIT_DELAY 0



class AUSEX_TEMT6000_CLASS : public Adafruit_SensorEx {
public:
  AUSEX_TEMT6000_CLASS(int, float vdd=AUSEX_TEMT6000_DEFAULT_VDD, int32_t sensorID = -1);
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
  AUSEX_TEMT6000_SENSOR_VALUE_TYPE calcValue(int);
  bool _autoRange;
};



#endif /* __AUSEX_TEMT6000_H__ */
