#ifndef __AUSEX_GROVE_I2C_TOUCH_SENSOR_H__
#define __AUSEX_GROVE_I2C_TOUCH_SENSOR_H__

#define AUSEX_GROVE_I2C_TOUCH_SENSOR_CLASS AusExGroveI2cTouchSensor
#define AUSEX_GROVE_I2C_TOUCH_SENSOR_NAME "AusExGroveI2cTouchSensor"
#define AUSEX_GROVE_I2C_TOUCH_SENSOR_TYPE SENSOR_TYPE_SIMPLE
#define AUSEX_GROVE_I2C_TOUCH_SENSOR_LIBRARY_VERSION 1
#define AUSEX_GROVE_I2C_TOUCH_SENSOR_RETURN_VALUE value
#define AUSEX_GROVE_I2C_TOUCH_SENSOR_VALUE_TYPE uint32_t
#define AUSEX_GROVE_I2C_TOUCH_SENSOR_MIN_VALUE 0
#define AUSEX_GROVE_I2C_TOUCH_SENSOR_MAX_VALUE 1
#define AUSEX_GROVE_I2C_TOUCH_SENSOR_RESOLUTION 1
#define AUSEX_GROVE_I2C_TOUCH_SENSOR_MIN_DELAY 0
#define AUSEX_GROVE_I2C_TOUCH_SENSOR_INIT_DELAY 0

#define AUSEX_GROVE_I2C_TOUCH_NUM_OF_SENSORS 12

#define AUSEX_GROVE_I2C_TOUCH_SENSOR_DEFAULT_I2C_ADDR 0x5A

// MPR121 Register Defines
#define MHD_R  0x2B
#define NHD_R 0x2C
#define NCL_R   0x2D
#define FDL_R 0x2E
#define MHD_F 0x2F
#define NHD_F 0x30
#define NCL_F 0x31
#define FDL_F 0x32
#define ELE0_T  0x41
#define ELE0_R  0x42
#define ELE1_T  0x43
#define ELE1_R  0x44
#define ELE2_T  0x45
#define ELE2_R  0x46
#define ELE3_T  0x47
#define ELE3_R  0x48
#define ELE4_T  0x49
#define ELE4_R  0x4A
#define ELE5_T  0x4B
#define ELE5_R  0x4C
#define ELE6_T  0x4D
#define ELE6_R  0x4E
#define ELE7_T  0x4F
#define ELE7_R  0x50
#define ELE8_T  0x51
#define ELE8_R  0x52
#define ELE9_T  0x53
#define ELE9_R  0x54
#define ELE10_T 0x55
#define ELE10_R 0x56
#define ELE11_T 0x57
#define ELE11_R 0x58
#define FIL_CFG 0x5D
#define ELE_CFG 0x5E
#define GPIO_CTRL0  0x73
#define GPIO_CTRL1  0x74
#define GPIO_DATA 0x75
#define GPIO_DIR  0x76
#define GPIO_EN   0x77
#define GPIO_SET  0x78
#define GPIO_CLEAR  0x79
#define GPIO_TOGGLE 0x7A
#define ATO_CFG0  0x7B
#define ATO_CFGU  0x7D
#define ATO_CFGL  0x7E
#define ATO_CFGT  0x7F

// Global Constants
#define TOU_THRESH  0x0F
#define REL_THRESH  0x0A

#include "AusEx.h"
#include <Wire.h>


class AUSEX_GROVE_I2C_TOUCH_SENSOR_CLASS : public Adafruit_SensorEx {
public:
  AUSEX_GROVE_I2C_TOUCH_SENSOR_CLASS(TwoWire *theWire, int32_t sensorID = -1);
  bool begin(uint32_t addr = AUSEX_GROVE_I2C_TOUCH_SENSOR_DEFAULT_I2C_ADDR);
  bool getEvent(sensors_event_t*);
  void getSensor(sensor_t*);
  bool enableAutoRange(bool enabled);
  int setMode(int mode);
  int getMode(void);
  bool getTouchState(AUSEX_GROVE_I2C_TOUCH_SENSOR_VALUE_TYPE val, uint8_t num);

private:
  TwoWire *_i2c_if;
  int _i2c_addr;
  uint32_t _sensorID;
  bool _autoRange;
  void write(uint8_t _register, uint8_t _data);
  int8_t read(uint8_t _register);
  int16_t readLong(void);
  void mpr121Setup(void);
};



#endif /* __AUSEX_GROVE_I2C_TOUCH_SENSOR_H__ */
