#ifndef __GROVE_DIGITAL_LIGHT_SENSOR_V2_AUSEX_H__
#define __GROVE_DIGITAL_LIGHT_SENSOR_V2_AUSEX_H__

#define _TEMPLATE_CLASS GroveDigitalLightSensorV2AusEx
#define _SENSOR_NAME "GroveDigitalLightSensorV2AusEx"
#define _SENSOR_TYPE SENSOR_TYPE_SIMPLE
#define _SENSOR_LIBRARY_VERSION 1
#define _SENSOR_RETURN_VALUE light
#define _SENSOR_VALUE_TYPE float
#define _SENSOR_MIN_VALUE 0
#define _SENSOR_MAX_VALUE 1
#define _SENSOR_RESOLUTION 1
#define _SENSOR_MIN_DELAY 0

#define _SENSOR_DEFAULT_I2C_ADDR 0x44 

#define COMMAND_I               0x00
#define COMMAND_II              0x01
#define DATA_L                  0x02
#define DATA_H                  0x03
#define INT_LT_L                0x04
#define INT_LT_H                0x05
#define INT_HT_L                0x06
#define INT_HT_H                0x07
#define CHIP_ID                 0x0f

#define OPMODE_ALS_ONCE         ((0x1)<<5)
#define OPMODE_IR_ONCE          ((0x2)<<5)
#define OPMODE_ALS_CONTI        ((0x5)<<5)
#define OPMODE_IR_CONTI         ((0x6)<<5)


#define FULL_SCALE_LUX_RANGE0   1000
#define FULL_SCALE_LUX_RANGE1   4000
#define FULL_SCALE_LUX_RANGE2   16000
#define FULL_SCALE_LUX_RANGE3   64000
#define DEFAULT_LUX_RANGE_INDEX 1       //should be [0,3]

#define INTEGRATION_TIME3       0.0256  //ms, this also configure the ADC to 4bits
#define INTEGRATION_TIME2       0.41  //ms, this also configure the ADC to 8bits
#define INTEGRATION_TIME1       6.5  //ms, this also configure the ADC to 12bits
#define INTEGRATION_TIME0       105  //ms, this also configure the ADC to 16bits
#define DEFAULT_INTEGRATION_TIME_INDEX 1  //should be [0,3]

#define ADC_COUNT_MAX0 65536
#define ADC_COUNT_MAX1 4096
#define ADC_COUNT_MAX2 256
#define ADC_COUNT_MAX3 16

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
  bool _autoRange;
  int32_t _adc_count_max[4];
  float   _intg_time[4];
  uint32_t _ranges[4];
  uint8_t _range;
  uint8_t _integration_time;
  float _min_value;
  float _max_value;
  float _resolution;
  int32_t _min_delay;
  _SENSOR_VALUE_TYPE calcValue(uint16_t);
  void write(uint8_t _register, uint8_t _data);
  int8_t read(uint8_t _register);
  //int16_t read(uint8_t addressh, uint8_t addressl);
  int16_t readLong(uint8_t reg);
  uint16_t measure(uint8_t what);
  bool setRange(int range_index, int intg_time_index);
};



#endif /* __GROVE_DIGITAL_LIGHT_SENSOR_V2_AUSEX_H__ */
