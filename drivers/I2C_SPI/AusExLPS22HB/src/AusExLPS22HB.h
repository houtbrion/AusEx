#ifndef __AUSEX_LPS22HB_H__
#define __AUSEX_LPS22HB_H__

#define AUSEX_LPS22HB_CLASS AusExLPS22HB
#define AUSEX_LPS22HB_SENSOR_NAME "LPS22HB"
#define AUSEX_LPS22HB_SENSOR_TYPE SENSOR_TYPE_PRESSURE
#define AUSEX_LPS22HB_SENSOR_LIBRARY_VERSION 1
#define AUSEX_LPS22HB_SENSOR_RETURN_VALUE pressure
#define AUSEX_LPS22HB_SENSOR_VALUE_TYPE float
#define AUSEX_LPS22HB_SENSOR_MIN_VALUE 260  // ヘクトパスカル
#define AUSEX_LPS22HB_SENSOR_MAX_VALUE 1260 // ヘクトパスカル
#define AUSEX_LPS22HB_SENSOR_RESOLUTION 0.1 // ヘクトパスカル
#define AUSEX_LPS22HB_SENSOR_MIN_DELAY 0
#define AUSEX_LPS22HB_SENSOR_INIT_DELAY 0

#define AUSEX_LPS22HB_SENSOR_DEFAULT_I2C_ADDR 0x5C // 0x5C(Arduino MKR ENV) , 0x5D(回路次第)
#define AUSEX_LPS22HB_SENSOR_SECOND_I2C_ADDR  0x5D

#define AUSEX_LPS22HB_HELLO_REG           0x0f
#define AUSEX_LPS22HB_CTRL2_REG           0x11
#define AUSEX_LPS22HB_STATUS_REG          0x27
#define AUSEX_LPS22HB_PRESS_OUT_XL_REG    0x28
#define AUSEX_LPS22HB_PRESS_OUT_L_REG     0x29
#define AUSEX_LPS22HB_PRESS_OUT_H_REG     0x2a

#define AUSEX_LPS22HB_MODE_KPA  0
#define AUSEX_LPS22HB_MODE_HPA  1
#define AUSEX_LPS22HB_MODE_PAI  2
#define AUSEX_LPS22HB_MODE_MBAR 3

#include "AusEx.h"
#include <Wire.h>


class AUSEX_LPS22HB_CLASS : public Adafruit_SensorEx {
public:
  AUSEX_LPS22HB_CLASS(TwoWire *theWire, int32_t sensorID = -1);
  bool begin(uint32_t addr=AUSEX_LPS22HB_SENSOR_DEFAULT_I2C_ADDR);
  bool getEvent(sensors_event_t*);
  void getSensor(sensor_t*);
  bool enableAutoRange(bool enabled);
  int setMode(int mode);
  int getMode();

private:
  TwoWire *_i2c_if;
  int _i2c_addr;
  int32_t _sensorID;
  int _mode;
  AUSEX_LPS22HB_SENSOR_VALUE_TYPE calcValue(AUSEX_LPS22HB_SENSOR_VALUE_TYPE);
  void write(uint8_t _register, uint8_t _data);
  int8_t read(uint8_t _register);
  int16_t read(uint8_t addressh, uint8_t addressl);
  bool _autoRange;
};



#endif /* __AUSEX_LPS22HB_H__ */
