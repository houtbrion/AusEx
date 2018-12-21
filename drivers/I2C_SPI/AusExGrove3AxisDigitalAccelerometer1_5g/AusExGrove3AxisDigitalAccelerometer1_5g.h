#ifndef __GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_AUSEX_H__
#define __GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_AUSEX_H__

#define _TEMPLATE_CLASS Grove3AxisDigitalAccelerometer1_5gAusEx
#define _SENSOR_NAME "Grove3AxisAccelerometer1_5gAusEx"
#define _SENSOR_TYPE SENSOR_TYPE_ACCELEROMETER
#define _SENSOR_LIBRARY_VERSION 1
#define _SENSOR_RETURN_VALUE acceleration
#define _SENSOR_VALUE_TYPE sensors_vec_t
#define _SENSOR_MIN_VALUE -14.709975
#define _SENSOR_MAX_VALUE 14.709975
#define _SENSOR_RESOLUTION 0.0476
#define _SENSOR_MIN_DELAY 0

#define _SENSOR_DEFAULT_I2C_ADDR 0x4c


#include "AusEx.h"
#include <Wire.h>


#define MMA7660TIMEOUT  500         // us
#define MMA7660_SR    0x08      //sample rate register
#define MMA7660_MODE  0x07
#define MMA7660_STAND_BY 0x00
#define MMA7660_ACTIVE   0x01
#define AUTO_SLEEP_32   0X02

struct MMA7660_LOOKUP {
  float g;
  float xyAngle;
  float zAngle;
};

class _TEMPLATE_CLASS : public Adafruit_SensorEx {
public:
  _TEMPLATE_CLASS(int32_t sensorID = -1);
  bool begin(TwoWire *theWire=&Wire);
  bool getEvent(sensors_event_t*);
  void getSensor(sensor_t*);
  bool enableAutoRange(bool enabled);
  int setMode(int mode);

private:
  MMA7660_LOOKUP accLookup[64];
  TwoWire *_i2c_if;
  int _i2c_addr;
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



#endif /* __GROVE_3AXIS_DIGITAL_ACCELEROMETER_1_5G_AUSEX_H__ */
