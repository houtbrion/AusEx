#ifndef __AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_H__
#define __AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_H__

#define AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_CLASS AusExGrove3AxisDigitalAccelerometer1_5g
#define AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_SENSOR_NAME "AusExGrove3AxisAccelerometer1_5g"
#define AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_SENSOR_TYPE SENSOR_TYPE_ACCELEROMETER
#define AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_SENSOR_LIBRARY_VERSION 1
#define AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_SENSOR_RETURN_VALUE acceleration
#define AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_SENSOR_VALUE_TYPE sensors_vec_t
#define AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_SENSOR_MIN_VALUE -14.709975
#define AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_SENSOR_MAX_VALUE 14.709975
#define AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_SENSOR_RESOLUTION 0.0476
#define AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_SENSOR_MIN_DELAY 0
#define AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_SENSOR_INIT_DELAY 0

#define AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_SENSOR_DEFAULT_I2C_ADDR 0x4c


#include "AusEx.h"
#include <Wire.h>


#define MMA7660TIMEOUT  500         // us
#define MMA7660_SR    0x08      //sample rate register
#define MMA7660_MODE  0x07
#define MMA7660_STAND_BY 0x00
#define MMA7660_ACTIVE   0x01

#define MMA7660_AUTO_SLEEP_120  0X00//120 sample per second (default)
#define MMA7660_AUTO_SLEEP_64 0X01
#define MMA7660_AUTO_SLEEP_32 0X02
#define MMA7660_AUTO_SLEEP_16 0X03
#define MMA7660_AUTO_SLEEP_8  0X04
#define MMA7660_AUTO_SLEEP_4  0X05
#define MMA7660_AUTO_SLEEP_2  0X06
#define MMA7660_AUTO_SLEEP_1  0X07

struct MMA7660_LOOKUP {
  float g;
  float xyAngle;
  float zAngle;
};

class AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_CLASS : public Adafruit_SensorEx {
public:
  AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_CLASS(TwoWire *theWire,int32_t sensorID = -1);
  bool begin(uint32_t addr=AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_SENSOR_DEFAULT_I2C_ADDR);
  bool getEvent(sensors_event_t*);
  void getSensor(sensor_t*);
  bool enableAutoRange(bool enabled);
  int setMode(int mode);
  int getMode(void);

private:
  MMA7660_LOOKUP accLookup[64];
  TwoWire *_i2c_if;
  int _i2c_addr;
  uint8_t _mode;
  uint32_t _sensorID;
  bool _autoRange;
  void write(uint8_t _register, uint8_t _data);
  int8_t read(uint8_t _register);
  void initAccelTable();
  bool getXYZ(int8_t *x,int8_t *y,int8_t *z);
  void setState(uint8_t mode);
  void setSampleRate(uint8_t rate);
  bool getAcceleration(float *ax,float *ay,float *az);
};



#endif /* __AUSEX_GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_H__ */
