#ifndef __AUSEX_ADXL335_H__
#define __AUSEX_ADXL335_H__

#include "AusEx.h"


#define AUSEX_ADXL335_ADC_AMPLITUDE 1024//amplitude of the 10bit-ADC of Arduino is 1024LSB
#define AUSEX_ADXL335_ZERO_X  1.22 //accleration of X-AXIS is 0g, the voltage of X-AXIS is 1.22v
#define AUSEX_ADXL335_ZERO_Y  1.22 //
#define AUSEX_ADXL335_ZERO_Z  1.25 //
#define AUSEX_ADXL335_SENSITIVITY 0.25//sensitivity of X/Y/Z axis is 0.25v/g

#define AUSEX_ADXL335_CLASS AusExADXL335
#define AUSEX_ADXL335_SENSOR_NAME "ADXL335"
#define AUSEX_ADXL335_SENSOR_TYPE SENSOR_TYPE_LINEAR_ACCELERATION
#define AUSEX_ADXL335_SENSOR_LIBRARY_VERSION 1
#define AUSEX_ADXL335_SENSOR_RETURN_VALUE acceleration
#define AUSEX_ADXL335_SENSOR_VALUE_TYPE sensors_vec_t
#define AUSEX_ADXL335_SENSOR_MIN_VALUE 0
#define AUSEX_ADXL335_SENSOR_MAX_VALUE 1023
#define AUSEX_ADXL335_SENSOR_RESOLUTION 1
#define AUSEX_ADXL335_SENSOR_MIN_DELAY 0
#define AUSEX_ADXL335_SENSOR_INIT_DELAY 0



class AUSEX_ADXL335_CLASS : public Adafruit_SensorEx {
public:
  AUSEX_ADXL335_CLASS(int, int ,int ,float vdd, float calX, float calY, float calZ, float sens,  int32_t sensorID = -1);
  bool begin(void);
  bool getEvent(sensors_event_t*);
  void getSensor(sensor_t*);
  bool enableAutoRange(bool);
  int setMode(int);
  int getMode();

private:
  int _pinX;
  int _pinY;
  int _pinZ;
  float _calX;
  float _calY;
  float _calZ;
  float _vdd;
  int32_t _sensorID;
  float _sens;
  void getAcceleration(sensors_event_t* event);
};



#endif /* __AUSEX_ADXL335_H__ */
