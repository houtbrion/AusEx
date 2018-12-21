#ifndef __GENERAL_I2C_AUSEX_H__
#define __GENERAL_I2C_AUSEX_H__

#define _TEMPLATE_CLASS i2cAusExTemplate
#define _SENSOR_NAME "i2cAusExTemplate"
#define _SENSOR_TYPE SENSOR_TYPE_SIMPLE
#define _SENSOR_LIBRARY_VERSION 1
#define _SENSOR_RETURN_VALUE value
#define _SENSOR_VALUE_TYPE uint32_t
#define _SENSOR_MIN_VALUE 0
#define _SENSOR_MAX_VALUE 1
#define _SENSOR_RESOLUTION 1
#define _SENSOR_MIN_DELAY 0

#define _SENSOR_DEFAULT_I2C_ADDR 0


#include "AusEx.h"
#include <Wire.h>


class _TEMPLATE_CLASS : public Adafruit_SensorEx {
public:
  _TEMPLATE_CLASS(uint32_t sensorID = -1);
  bool begin(TwoWire *theWire=&Wire);
  bool getEvent(sensors_event_t*);
  void getSensor(sensor_t*);
  bool enableAutoRange(bool enabled);
  int setMode(int mode);

private:
  TwoWire *_i2c_if;
  int _i2c_addr;
  uint32_t _sensorID;
  _SENSOR_VALUE_TYPE calcValue(int);
  void write(uint8_t _register, uint8_t _data);
  int8_t read(uint8_t _register);
  int16_t read(uint8_t addressh, uint8_t addressl);
  bool _autoRange;
};



#endif /* __GENERAL_I2C_AUSEX_H__ */
