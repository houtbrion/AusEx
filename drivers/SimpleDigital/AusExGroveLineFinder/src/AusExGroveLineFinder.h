#ifndef __AUSEX_GROVE_LINE_FINDER_H__
#define __AUSEX_GROVE_LINE_FINDER_H__



#define AUSEX_GROVE_LINE_FINDER_CLASS AusExGroveLineFinder
#define AUSEX_GROVE_LINE_FINDER_NAME "AusExGroveLineFinder"
#define AUSEX_GROVE_LINE_FINDER_TYPE SENSOR_TYPE_SIMPLE
#define AUSEX_GROVE_LINE_FINDER_LIBRARY_VERSION 1
#define AUSEX_GROVE_LINE_FINDER_RETURN_VALUE value
#define AUSEX_GROVE_LINE_FINDER_VALUE_TYPE uint32_t
#define AUSEX_GROVE_LINE_FINDER_MIN_VALUE 0
#define AUSEX_GROVE_LINE_FINDER_MAX_VALUE 1
#define AUSEX_GROVE_LINE_FINDER_RESOLUTION 1
#define AUSEX_GROVE_LINE_FINDER_MIN_DELAY 0
#define AUSEX_GROVE_LINE_FINDER_INIT_DELAY 0

#include "AusEx.h"


class AUSEX_GROVE_LINE_FINDER_CLASS : public Adafruit_SensorEx {
public:
  AUSEX_GROVE_LINE_FINDER_CLASS(int, int32_t sensorID = -1);
  bool begin(bool pullUp=false);
  bool getEvent(sensors_event_t*);
  void getSensor(sensor_t*);
  bool enableAutoRange(bool);
  int setMode(int);
  int getMode();

private:
  int _pin;
  int32_t _sensorID;
  AUSEX_GROVE_LINE_FINDER_VALUE_TYPE calcValue(int);
};



#endif /* __AUSEX_GROVE_LINE_FINDER_H__ */
