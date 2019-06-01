#ifndef __AUSEX_SHT31_H__
#define __AUSEX_SHT31_H__

#include "AusEx.h"
#include "Wire.h"


//#define DEBUG

#define NO_MEASURE NAN

#define AUSEX_SHT31_CLASS AusExSHT31
#define AUSEX_SHT31_SENSOR_NAME "SHT31"
#define AUSEX_SHT31_SENSOR_LIBRARY_VERSION 1
#define AUSEX_SHT31_SENSOR_TEMPERATURE_MIN_VALUE -40
#define AUSEX_SHT31_SENSOR_TEMPERATURE_MAX_VALUE 125
#define AUSEX_SHT31_SENSOR_TEMPERATURE_RESOLUTION 1
#define AUSEX_SHT31_SENSOR_HUMIDITY_MIN_VALUE 0
#define AUSEX_SHT31_SENSOR_HUMIDITY_MAX_VALUE 100
#define AUSEX_SHT31_SENSOR_HUMIDITY_RESOLUTION 1
#define AUSEX_SHT31_SENSOR_TEMPERATURE_MIN_DELAY 2000000
#define AUSEX_SHT31_SENSOR_HUMIDITY_MIN_DELAY 8000000
#define AUSEX_SHT31_SENSOR_INIT_DELAY 1000
#define AUSEX_SHT31_SENSOR_DEFAULT_I2C_ADDR 0x45

#define SHT31_MEAS_HIGHREP_STRETCH 0x2C06
#define SHT31_MEAS_MEDREP_STRETCH  0x2C0D
#define SHT31_MEAS_LOWREP_STRETCH  0x2C10
#define SHT31_MEAS_HIGHREP         0x2400
#define SHT31_MEAS_MEDREP          0x240B
#define SHT31_MEAS_LOWREP          0x2416
#define SHT31_READSTATUS           0xF32D
#define SHT31_CLEARSTATUS          0x3041
#define SHT31_SOFTRESET            0x30A2
#define SHT31_HEATEREN             0x306D
#define SHT31_HEATERDIS            0x3066

class AusExSHT31 {
public:
  AusExSHT31(TwoWire *theWire, int32_t tempSensorId=-1, int32_t humiditySensorId=-1);
  bool begin(uint32_t addr=AUSEX_SHT31_SENSOR_DEFAULT_I2C_ADDR);

  class Temperature : public Adafruit_SensorEx {
  public:
    Temperature(AusExSHT31* parent, int32_t id);
    bool getEvent(sensors_event_t* event);
    void getSensor(sensor_t* sensor);
    bool enableAutoRange(bool);
    int setMode(int);
    int getMode();
  private:
    AusExSHT31* _parent;
    int32_t _id;
  };
  class Humidity : public Adafruit_SensorEx {
  public:
    Humidity(AusExSHT31* parent, int32_t id);
    bool getEvent(sensors_event_t* event);
    void getSensor(sensor_t* sensor);
    bool enableAutoRange(bool);
    int setMode(int);
    int getMode();
  private:
    AusExSHT31* _parent;
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
  int _mode;
  TwoWire *_i2c_if;
  uint8_t _i2c_addr;
  int _pin;
  unsigned long lastTime;
  float oldTemperature;
  float oldHumidity;
  Temperature _temp;
  Humidity _humidity;
  void reset(void);
  void writeCommand(uint16_t );
  bool getTemperature(sensors_event_t*);
  bool getHumidity(sensors_event_t*);
  uint8_t crc8(const uint8_t *, int );
  bool readSHT31(void);
};


#endif /* __AUSEX_SHT31_H__ */
