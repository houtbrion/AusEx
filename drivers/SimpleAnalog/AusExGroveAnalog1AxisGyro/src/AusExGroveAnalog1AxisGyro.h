#ifndef __AUSEX_GROVE_ANALOG_1AXIS_GYRO_H__
#define __AUSEX_GROVE_ANALOG_1AXIS_GYRO_H__

#define AUSEX_GROVE_ANALOG_1AXIS_GYRO_CLASS AusExGroveAnalog1AxisGyro
#define AUSEX_GROVE_ANALOG_1AXIS_GYRO_SENSOR_NAME "AusExGroveAnalog1AxisGyro"
#define AUSEX_GROVE_ANALOG_1AXIS_GYRO_SENSOR_TYPE SENSOR_TYPE_1AXIS_GYRO
#define AUSEX_GROVE_ANALOG_1AXIS_GYRO_SENSOR_LIBRARY_VERSION 1
#define AUSEX_GROVE_ANALOG_1AXIS_GYRO_SENSOR_RETURN_VALUE roll
#define AUSEX_GROVE_ANALOG_1AXIS_GYRO_SENSOR_VALUE_TYPE float
#define AUSEX_GROVE_ANALOG_1AXIS_GYRO_DEFAULT_VDD 5
#define AUSEX_GROVE_ANALOG_1AXIS_GYRO_SENSOR_MIN_VALUE 0
#define AUSEX_GROVE_ANALOG_1AXIS_GYRO_SENSOR_MAX_VALUE 7388.0597014925373134328358208955
#define AUSEX_GROVE_ANALOG_1AXIS_GYRO_SENSOR_RESOLUTION 7.2219547424169475204622051035147
#define AUSEX_GROVE_ANALOG_1AXIS_GYRO_SENSOR_MIN_DELAY 0
#define AUSEX_GROVE_ANALOG_1AXIS_GYRO_SENSOR_INIT_DELAY 0

#include "AusEx.h"


class AUSEX_GROVE_ANALOG_1AXIS_GYRO_CLASS : public Adafruit_SensorEx {
public:
  AUSEX_GROVE_ANALOG_1AXIS_GYRO_CLASS(int pinNumber, int32_t sensorID = -1);
  AUSEX_GROVE_ANALOG_1AXIS_GYRO_CLASS(int pinNumber,float vdd, int32_t sensorID = -1);
  bool begin(void);
  bool getEvent(sensors_event_t*);
  void getSensor(sensor_t*);
  bool enableAutoRange(bool enabled);
  int setMode(int mode);
  int getMode(void);

private:
  int _pin;
  float _vdd;
  int32_t _sensorID;
  AUSEX_GROVE_ANALOG_1AXIS_GYRO_SENSOR_VALUE_TYPE calcValue(int);
  bool _autoRange;
};



#endif /* __AUSEX_GROVE_ANALOG_1AXIS_GYRO_H__ */
