#ifndef __AUSEX_DALLAS_ONE_WIRE_TEMPERATURE_H__
#define __AUSEX_DALLAS_ONE_WIRE_TEMPERATURE_H__

#define AUSEX_DALLAS_TEMPERATURE_CLASS AusExDallasTemperature
#define AUSEX_DALLAS_TEMPERATURE_SENSOR_NAME "DallasTemperature"
#define AUSEX_DALLAS_TEMPERATURE_SENSOR_TYPE SENSOR_TYPE_AMBIENT_TEMPERATURE
#define AUSEX_DALLAS_TEMPERATURE_SENSOR_LIBRARY_VERSION 1
#define AUSEX_DALLAS_TEMPERATURE_SENSOR_RETURN_VALUE temperature
#define AUSEX_DALLAS_TEMPERATURE_SENSOR_VALUE_TYPE float
#define AUSEX_DALLAS_TEMPERATURE_SENSOR_MIN_VALUE -55
#define AUSEX_DALLAS_TEMPERATURE_SENSOR_MAX_VALUE 125
#define AUSEX_DALLAS_TEMPERATURE_SENSOR_RESOLUTION 0.07
#define AUSEX_DALLAS_TEMPERATURE_SENSOR_MIN_DELAY 0
#define AUSEX_DALLAS_TEMPERATURE_SENSOR_INIT_DELAY 3000

#include <OneWire.h>
#include <DallasTemperature.h>
#include <AusEx.h>

class AUSEX_DALLAS_TEMPERATURE_CLASS : public Adafruit_SensorEx {
public:
  AUSEX_DALLAS_TEMPERATURE_CLASS(int, int32_t sensorID = -1);
  bool begin(void);
  bool getEvent(sensors_event_t*);
  void getSensor(sensor_t*);
  bool enableAutoRange(bool);
  int setMode(int);
  int getMode();

private:
  DallasTemperature _sensor;
  OneWire _wire;
  uint8_t _mode;
  int32_t _sensorID;
};



#endif /* __AUSEX_DALLAS_ONE_WIRE_TEMPERATURE_H__ */
