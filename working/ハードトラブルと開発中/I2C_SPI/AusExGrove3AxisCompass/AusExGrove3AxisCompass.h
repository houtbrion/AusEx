#ifndef __GROVE_3AXIS_COMPASS_AUSEX_H__
#define __GROVE_3AXIS_COMPASS_AUSEX_H__

#define _TEMPLATE_CLASS Grove3AxisCompassAusEx
#define _SENSOR_NAME "Grove3AxisCompassAusEx"
#define _SENSOR_TYPE SENSOR_TYPE_MAGNETIC_FIELD
#define _SENSOR_LIBRARY_VERSION 1
#define _SENSOR_RETURN_VALUE magnetic
#define _SENSOR_VALUE_TYPE sensors_vec_t
#define _SENSOR_MIN_VALUE -8.1
#define _SENSOR_MAX_VALUE 8.1
#define _SENSOR_RESOLUTION 0.00043
#define _SENSOR_MIN_DELAY 0

#define _SENSOR_DEFAULT_I2C_ADDR 0x1E
//#define HMC5883L_ADDRESS 0x1E

#define CONFIGURATION_REGISTERA 0x00
#define CONFIGURATION_REGISTERB 0x01
#define MODE_REGISTER 0x02
#define DATA_REGISTER_BEGIN 0x03

#define MEASUREMENT_CONTINUOUS 0x00
#define MEASUREMENT_SINGLE_SHOT 0x01
#define MEASUREMENT_IDLE 0x03

#define ERRORCODE_1_NUM 1
//#define ERRORCODE_1 "Entered scale was not valid, valid gauss values are: 0.88, 1.3, 1.9, 2.5, 4.0, 4.7, 5.6, 8.1"
#define SUCCESS 0

//#define CLOSEENOUGH(x,y) (fabs(x-y)<0.001)

#include "AusEx.h"
#include <Wire.h>

struct MagnetometerScaled
{
  float XAxis;
  float YAxis;
  float ZAxis;
};

struct MagnetometerRaw
{
  int XAxis;
  int YAxis;
  int ZAxis;
};



class _TEMPLATE_CLASS : public Adafruit_SensorEx {
public:
  _TEMPLATE_CLASS(uint32_t sensorID = -1);
  bool begin(TwoWire *theWire=&Wire);
  bool begin(float range, TwoWire *theWire=&Wire);
  bool getEvent(sensors_event_t*);
  void getSensor(sensor_t*);
  bool enableAutoRange(bool enabled);
  int setMode(int mode);

private:
  TwoWire *_i2c_if;
  int _i2c_addr;
  uint32_t _sensorID;
  bool _autoRange;
  float m_Scale;
  float _max_value;
  float _resolution;
  //_SENSOR_VALUE_TYPE calcValue(int);
  void write(int address, int data);
  //int8_t read(uint8_t _register);
  int16_t read(int address, int length);
  bool setScale(float gauss);
  //char *getErrorText(int errorCode);
  void setMeasurementMode(uint8_t mode);
  MagnetometerRaw readRawAxis();
  MagnetometerScaled readScaledAxis();
  float checkRange(float val);
};



#endif /* __GROVE_3AXIS_COMPASS_AUSEX_H__ */
