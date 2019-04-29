#ifndef __AUSEX_GROVE_3AXIS_DIGITAL_GYRO_H__
#define __AUSEX_GROVE_3AXIS_DIGITAL_GYRO_H__

#define AUSEX_GROVE_3AXIS_DIGITAL_GYRO_CLASS AusExGrove3AxisDigitalGyro
#define AUSEX_GROVE_3AXIS_DIGITAL_GYRO_SENSOR_NAME "AusExGrove3AxisDigitalGyro"
#define AUSEX_GROVE_3AXIS_DIGITAL_GYRO_SENSOR_TYPE SENSOR_TYPE_GYROSCOPE
#define AUSEX_GROVE_3AXIS_DIGITAL_GYRO_SENSOR_LIBRARY_VERSION 1
#define AUSEX_GROVE_3AXIS_DIGITAL_GYRO_SENSOR_RETURN_VALUE gyro
#define AUSEX_GROVE_3AXIS_DIGITAL_GYRO_SENSOR_VALUE_TYPE sensors_vec_t
#define AUSEX_GROVE_3AXIS_DIGITAL_GYRO_SENSOR_MIN_VALUE -4500
#define AUSEX_GROVE_3AXIS_DIGITAL_GYRO_SENSOR_MAX_VALUE 4500
#define AUSEX_GROVE_3AXIS_DIGITAL_GYRO_SENSOR_RESOLUTION 0.0696
#define AUSEX_GROVE_3AXIS_DIGITAL_GYRO_SENSOR_MIN_DELAY 0

#define AUSEX_GROVE_3AXIS_DIGITAL_GYRO_I2C_ADDRESS 0x68

#include "AusEx.h"
#include <Wire.h>

// ITG3200 Register
#define ITG3200_PWR_M  0x3E
#define ITG3200_SMPL  0x15
#define ITG3200_DLPF  0x16
#define ITG3200_GX_H  0x1D
#define ITG3200_GX_L  0x1E
#define ITG3200_GY_H  0x1F
#define ITG3200_GY_L  0x20
#define ITG3200_GZ_H  0x21
#define ITG3200_GZ_L  0x22



class AUSEX_GROVE_3AXIS_DIGITAL_GYRO_CLASS : public Adafruit_SensorEx {
public:
  AUSEX_GROVE_3AXIS_DIGITAL_GYRO_CLASS(TwoWire *theWire, int32_t sensorID = -1);
  AUSEX_GROVE_3AXIS_DIGITAL_GYRO_CLASS(TwoWire *theWire, unsigned int samples,  unsigned int sampleDelayMS, int32_t sensorID = -1);
  bool begin(uint32_t addr=AUSEX_GROVE_3AXIS_DIGITAL_GYRO_I2C_ADDRESS);
  bool getEvent(sensors_event_t*);
  void getSensor(sensor_t*);
  bool enableAutoRange(bool enabled);
  int setMode(int mode);
  int getMode(void);

private:
  int _i2c_addr;
  uint32_t _times;
  uint32_t _wait;
  TwoWire *_i2c_if;
  uint32_t _sensorID;
  //_SENSOR_VALUE_TYPE calcValue(int);
  void write(uint8_t _register, uint8_t _data);
  int16_t read(uint8_t addressh, uint8_t addressl);
  void getXYZ(int16_t *x,int16_t *y,int16_t *z);
  void zeroCalibrate(unsigned int samples, unsigned int sampleDelayMS);
  void getAngularVelocity(float *ax,float *ay,float *az);
  bool _autoRange;
  int16_t _x_offset;
  int16_t _y_offset;
  int16_t _z_offset;
};



#endif /* __AUSEX_GROVE_3AXIS_DIGITAL_GYRO_H__ */
