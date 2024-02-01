#ifndef __AUSEX_HTS221_H__
#define __AUSEX_HTS221_H__

#define NO_MEASURE NAN

#define AUSEX_HTS221_CLASS AusExHTS221
#define AUSEX_HTS221_SENSOR_NAME "AusExHTS221"
#define AUSEX_HTS221_SENSOR_LIBRARY_VERSION 1
#define AUSEX_HTS221_SENSOR_TEMPERATURE_MIN_VALUE -40
#define AUSEX_HTS221_SENSOR_TEMPERATURE_MAX_VALUE 120
#define AUSEX_HTS221_SENSOR_TEMPERATURE_RESOLUTION 0.5
#define AUSEX_HTS221_SENSOR_HUMIDITY_MIN_VALUE 0
#define AUSEX_HTS221_SENSOR_HUMIDITY_MAX_VALUE 100
#define AUSEX_HTS221_SENSOR_HUMIDITY_RESOLUTION 0.004
#define AUSEX_HTS221_SENSOR_TEMPERATURE_MIN_DELAY 0
#define AUSEX_HTS221_SENSOR_HUMIDITY_MIN_DELAY 0
#define AUSEX_HTS221_SENSOR_INIT_DELAY 0
#define AUSEX_HTS221_SENSOR_DEFAULT_I2C_ADDR 0x5F

#define HTS221_HELLO_REG            0x0f
#define HTS221_CTRL1_REG            0x20
#define HTS221_CTRL2_REG            0x21
#define HTS221_CTRL3_REG            0x22
#define HTS221_STATUS_REG           0x27
#define HTS221_HUMIDITY_OUT_L_REG   0x28
#define HTS221_TEMP_OUT_L_REG       0x2a
#define HTS221_H0_rH_x2_REG         0x30
#define HTS221_H1_rH_x2_REG         0x31
#define HTS221_T0_degC_x8_REG       0x32
#define HTS221_T1_degC_x8_REG       0x33
#define HTS221_T1_T0_MSB_REG        0x35
#define HTS221_H0_T0_OUT_REG        0x36
#define HTS221_H1_T0_OUT_REG        0x3a
#define HTS221_T0_OUT_REG           0x3c
#define HTS221_T1_OUT_REG           0x3e

#include "AusEx.h"
#include "Wire.h"
//#if defined(__AVR__)
//  #include <util/delay.h>
//#endif

class AusExHTS221 {
public:
  AusExHTS221(TwoWire *theWire, uint32_t tempSensorId=-1, int32_t humiditySensorId=-1);
  bool begin(uint32_t addr=AUSEX_HTS221_SENSOR_DEFAULT_I2C_ADDR);


  class Temperature : public Adafruit_SensorEx {
  public:
    Temperature(AusExHTS221* parent, int32_t id);
    bool getEvent(sensors_event_t* event);
    void getSensor(sensor_t* sensor);
    bool enableAutoRange(bool);
    int setMode(int);
    int getMode();
  private:
    AusExHTS221* _parent;
    int32_t _id;
  };
  class Humidity : public Adafruit_SensorEx {
  public:
    Humidity(AusExHTS221* parent, int32_t id);
    bool getEvent(sensors_event_t* event);
    void getSensor(sensor_t* sensor);
    bool enableAutoRange(bool);
    int setMode(int);
    int getMode();
  private:
    AusExHTS221* _parent;
    int32_t _id;
  };
  Temperature temperature() {
    return _temp;
  };

  Humidity humidity() {
    return _humidity;
  };
  int setMode(int);
  int getMode();
  bool enableAutoRange(bool);


private:
  TwoWire *_i2c_if;
  uint8_t _i2c_addr;
  //
  float _humiditySlope;
  float _humidityZero;
  float _temperatureSlope;
  float _temperatureZero;
  //byte rdptr[8];
  //unsigned long lastTime;
  //float oldTemperature;
  //float oldHumidity;
  Temperature _temp;
  Humidity _humidity;
  void writeCommand(uint16_t );
  bool getTemperature(sensors_event_t*);
  bool getHumidity(sensors_event_t*);
  //void readHTS221(byte *rdptr, byte length);
  int read8(uint8_t);
  int read16(uint8_t);
  bool write(uint8_t, uint8_t);
  bool calibration(void);
};


#endif /* __AUSEX_HTS221_H__ */
