#ifndef __AUSEX_I2C_TEMPLATE_H__
#define __AUSEX_I2C_TEMPLATE_H__

#define AUSEX_I2C_TEMPLATE_CLASS AusExI2cTemplate
#define AUSEX_I2C_TEMPLATE_SENSOR_NAME "AusExI2cTemplate"
#define AUSEX_I2C_TEMPLATE_SENSOR_TYPE SENSOR_TYPE_SIMPLE
#define AUSEX_I2C_TEMPLATE_SENSOR_LIBRARY_VERSION 1
#define AUSEX_I2C_TEMPLATE_SENSOR_RETURN_VALUE value
#define AUSEX_I2C_TEMPLATE_SENSOR_VALUE_TYPE uint32_t
#define AUSEX_I2C_TEMPLATE_SENSOR_MIN_VALUE 0
#define AUSEX_I2C_TEMPLATE_SENSOR_MAX_VALUE 1
#define AUSEX_I2C_TEMPLATE_SENSOR_RESOLUTION 1
#define AUSEX_I2C_TEMPLATE_SENSOR_MIN_DELAY 0

#define AUSEX_I2C_TEMPLATE_SENSOR_DEFAULT_I2C_ADDR 0


#include "AusEx.h"
#include <Wire.h>


class AUSEX_I2C_TEMPLATE_CLASS : public Adafruit_SensorEx {
public:
  AUSEX_I2C_TEMPLATE_CLASS(TwoWire *theWire, int32_t sensorID = -1);
  bool begin(uint32_t addr=AUSEX_I2C_TEMPLATE_SENSOR_DEFAULT_I2C_ADDR);
  bool getEvent(sensors_event_t*);
  void getSensor(sensor_t*);
  bool enableAutoRange(bool enabled);
  int setMode(int mode);
  int getMode();

private:
  TwoWire *_i2c_if;
  int _i2c_addr;
  int32_t _sensorID;
  AUSEX_I2C_TEMPLATE_SENSOR_VALUE_TYPE calcValue(int);
  void write(uint8_t _register, uint8_t _data);
  int8_t read(uint8_t _register);
  int16_t read(uint8_t addressh, uint8_t addressl);
  bool _autoRange;
};



#endif /* __AUSEX_I2C_TEMPLATE_H__ */
