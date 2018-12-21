#ifndef __GROVE_DUST_SENSOR_AUSEX_H__
#define __GROVE_DUST_SENSOR_AUSEX_H__

#define SAMPLING_TIME 30000

#define _TEMPLATE_CLASS GroveDustSensorAusEx
#define _SENSOR_NAME "GroveDustSensorAusEx"
#define _SENSOR_TYPE SENSOR_TYPE_DUST
#define _SENSOR_LIBRARY_VERSION 1
#define _SENSOR_RETURN_VALUE dust
#define _SENSOR_VALUE_TYPE float
#define _SENSOR_MIN_VALUE 0
#define _SENSOR_MAX_VALUE 28000 // 0~28,000 / 0 ~ 8000 pcs/liter / pcs/0.01cf
#define _SENSOR_RESOLUTION 1
#define _SENSOR_MIN_DELAY SAMPLING_TIME




#include "AusEx.h"


class _TEMPLATE_CLASS : public Adafruit_SensorEx {
public:
  _TEMPLATE_CLASS(int pinNumber, int32_t sensorID = -1);
  bool begin(void);
  bool getEvent(sensors_event_t*);
  void getSensor(sensor_t*);
  bool enableAutoRange(bool enabled);
  int setMode(int mode);
  float measure(void);

private:
  int _pin;
  uint32_t _sensorID;
  bool _autoRange;
};



#endif /* __GROVE_DUST_SENSOR_AUSEX_H__ */
