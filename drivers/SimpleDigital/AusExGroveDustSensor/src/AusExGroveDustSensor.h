#ifndef __AUSEX_GROVE_DUST_SENSOR_H__
#define __AUSEX_GROVE_DUST_SENSOR_H__

#define SAMPLING_TIME 30000

#define AUSEX_GROVE_DUST_SENSOR_CLASS AusExGroveDustSensor
#define AUSEX_GROVE_DUST_SENSOR_NAME "AusExGroveDustSensor"
#define AUSEX_GROVE_DUST_SENSOR_TYPE SENSOR_TYPE_DUST
#define AUSEX_GROVE_DUST_SENSOR_LIBRARY_VERSION 1
#define AUSEX_GROVE_DUST_SENSOR_RETURN_VALUE dust
#define AUSEX_GROVE_DUST_SENSOR_VALUE_TYPE float
#define AUSEX_GROVE_DUST_SENSOR_MIN_VALUE 0
#define AUSEX_GROVE_DUST_SENSOR_MAX_VALUE 28000 // 0~28,000 / 0 ~ 8000 pcs/liter / pcs/0.01cf
#define AUSEX_GROVE_DUST_SENSOR_RESOLUTION 1
#define AUSEX_GROVE_DUST_SENSOR_MIN_DELAY SAMPLING_TIME




#include "AusEx.h"


class AUSEX_GROVE_DUST_SENSOR_CLASS : public Adafruit_SensorEx {
public:
  AUSEX_GROVE_DUST_SENSOR_CLASS(int pinNumber, int32_t sensorID = -1);
  bool begin(bool pullUp=false);
  bool getEvent(sensors_event_t*);
  void getSensor(sensor_t*);
  bool enableAutoRange(bool enabled);
  int setMode(int mode);
  int getMode(void);


private:
  int _pin;
  uint32_t _sensorID;
  bool _autoRange;
  float measure(void);
};



#endif /* __AUSEX_GROVE_DUST_SENSOR_H__ */
