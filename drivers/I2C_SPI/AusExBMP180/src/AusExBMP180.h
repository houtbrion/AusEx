#ifndef __AUSEX_BMP180_H__
#define __AUSEX_BMP180_H__

#define AUSEX_BMP180_CLASS AusExBmp180
#define AUSEX_BMP180_SENSOR_NAME "AusExBmp180"
#define AUSEX_BMP180_SENSOR_TYPE SENSOR_TYPE_PRESSURE
#define AUSEX_BMP180_SENSOR_LIBRARY_VERSION 1
//#define AUSEX_BMP180_SENSOR_RETURN_VALUE value
#define AUSEX_BMP180_SENSOR_RETURN_VALUE pressure
#define AUSEX_BMP180_SENSOR_VALUE_TYPE float
//#define AUSEX_BMP180_SENSOR_VALUE_TYPE uint32_t
#define AUSEX_BMP180_SENSOR_MIN_VALUE 300.0F
#define AUSEX_BMP180_SENSOR_MAX_VALUE 1100.0F
#define AUSEX_BMP180_SENSOR_RESOLUTION 0.01F
#define AUSEX_BMP180_SENSOR_MIN_DELAY 0
#define AUSEX_BMP180_SENSOR_INIT_DELAY 0

#define AUSEX_BMP180_SENSOR_DEFAULT_I2C_ADDR 0x77

#include "AusEx.h"
#include <Wire.h>



/*=========================================================================
    REGISTERS
    -----------------------------------------------------------------------*/
    enum
    {
      BMP085_REGISTER_CAL_AC1            = 0xAA,  // R   Calibration data (16 bits)
      BMP085_REGISTER_CAL_AC2            = 0xAC,  // R   Calibration data (16 bits)
      BMP085_REGISTER_CAL_AC3            = 0xAE,  // R   Calibration data (16 bits)
      BMP085_REGISTER_CAL_AC4            = 0xB0,  // R   Calibration data (16 bits)
      BMP085_REGISTER_CAL_AC5            = 0xB2,  // R   Calibration data (16 bits)
      BMP085_REGISTER_CAL_AC6            = 0xB4,  // R   Calibration data (16 bits)
      BMP085_REGISTER_CAL_B1             = 0xB6,  // R   Calibration data (16 bits)
      BMP085_REGISTER_CAL_B2             = 0xB8,  // R   Calibration data (16 bits)
      BMP085_REGISTER_CAL_MB             = 0xBA,  // R   Calibration data (16 bits)
      BMP085_REGISTER_CAL_MC             = 0xBC,  // R   Calibration data (16 bits)
      BMP085_REGISTER_CAL_MD             = 0xBE,  // R   Calibration data (16 bits)
      BMP085_REGISTER_CHIPID             = 0xD0,
      BMP085_REGISTER_VERSION            = 0xD1,
      BMP085_REGISTER_SOFTRESET          = 0xE0,
      BMP085_REGISTER_CONTROL            = 0xF4,
      BMP085_REGISTER_TEMPDATA           = 0xF6,
      BMP085_REGISTER_PRESSUREDATA       = 0xF6,
      BMP085_REGISTER_READTEMPCMD        = 0x2E,
      BMP085_REGISTER_READPRESSURECMD    = 0x34
    };
/*=========================================================================*/

/*=========================================================================
    MODE SETTINGS
    -----------------------------------------------------------------------*/
    typedef enum
    {
      BMP085_MODE_ULTRALOWPOWER          = 0,
      BMP085_MODE_STANDARD               = 1,
      BMP085_MODE_HIGHRES                = 2,
      BMP085_MODE_ULTRAHIGHRES           = 3
    } bmp085_mode_t;
/*=========================================================================*/

/*=========================================================================
    CALIBRATION DATA
    -----------------------------------------------------------------------*/
    typedef struct
    {
      int16_t  ac1;
      int16_t  ac2;
      int16_t  ac3;
      uint16_t ac4;
      uint16_t ac5;
      uint16_t ac6;
      int16_t  b1;
      int16_t  b2;
      int16_t  mb;
      int16_t  mc;
      int16_t  md;
    } bmp085_calib_data;
/*=========================================================================*/

class AUSEX_BMP180_CLASS : public Adafruit_SensorEx {
public:
  AUSEX_BMP180_CLASS(TwoWire *theWire, int32_t sensorID = -1);
  bool begin(uint32_t addr=AUSEX_BMP180_SENSOR_DEFAULT_I2C_ADDR);
  bool getEvent(sensors_event_t*);
  void getSensor(sensor_t*);
  bool enableAutoRange(bool enabled);
  int setMode(int mode);
  int getMode();

private:
  TwoWire *_i2c_if;
  int _i2c_addr;
  int32_t _sensorID;
  void writeCommand(byte, byte);
  void read8(byte , uint8_t *);
  void read16(byte , uint16_t *);
  void readS16(byte , int16_t *);
  void readCoefficients(void);
  void readRawTemperature(int32_t *);
  void readRawPressure(int32_t *);
  int32_t computeB5(int32_t );
  void getPressure(float *pressure);
  AUSEX_BMP180_SENSOR_VALUE_TYPE calcValue(int);
  bool _autoRange;
  bmp085_calib_data _bmp085_coeffs;
  uint8_t           _bmp085Mode;
};



#endif /* __AUSEX_BMP180_H__ */
