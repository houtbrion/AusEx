#ifndef __AUSEX_AM232X_H__
#define __AUSEX_AM232X_H__

#define NO_MEASURE NAN

#define AUSEX_AM232X_CLASS AusExAM232X
#define AUSEX_AM232X_SENSOR_NAME "AusExAM232X"
#define AUSEX_AM232X_SENSOR_LIBRARY_VERSION 1
#define AUSEX_AM232X_SENSOR_TEMPERATURE_MIN_VALUE -40
#define AUSEX_AM232X_SENSOR_TEMPERATURE_MAX_VALUE 80
#define AUSEX_AM232X_SENSOR_TEMPERATURE_RESOLUTION 0.1
#define AUSEX_AM232X_SENSOR_HUMIDITY_MIN_VALUE 0
#define AUSEX_AM232X_SENSOR_HUMIDITY_MAX_VALUE 100
#define AUSEX_AM232X_SENSOR_HUMIDITY_RESOLUTION 0.1
#define AUSEX_AM232X_SENSOR_TEMPERATURE_MIN_DELAY 5000000
#define AUSEX_AM232X_SENSOR_HUMIDITY_MIN_DELAY 5000000
#define AUSEX_AM232X_SENSOR_INIT_DELAY 1000
#define AUSEX_AM232X_SENSOR_DEFAULT_I2C_ADDR 0x5C

#define AM2321_I2C_WAIT1 1
#define AM2321_I2C_WAIT2 2
#define AM2321_I2C_WAIT_MICRO 60

#define AM2321 0
#define AM2322 1

#include "AusEx.h"
#include "Wire.h"
#if defined(__AVR__)
  #include <util/delay.h>
#endif

class AusExAM232X {
public:
  AusExAM232X(TwoWire *theWire, int32_t type, uint32_t tempSensorId=-1, int32_t humiditySensorId=-1);
  bool begin(uint32_t addr=AUSEX_AM232X_SENSOR_DEFAULT_I2C_ADDR);


  class Temperature : public Adafruit_SensorEx {
  public:
    Temperature(AusExAM232X* parent, int32_t id);
    bool getEvent(sensors_event_t* event);
    void getSensor(sensor_t* sensor);
    bool enableAutoRange(bool);
    int setMode(int);
    int getMode();
  private:
    AusExAM232X* _parent;
    int32_t _id;
  };
  class Humidity : public Adafruit_SensorEx {
  public:
    Humidity(AusExAM232X* parent, int32_t id);
    bool getEvent(sensors_event_t* event);
    void getSensor(sensor_t* sensor);
    bool enableAutoRange(bool);
    int setMode(int);
    int getMode();
  private:
    AusExAM232X* _parent;
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
  uint32_t _type;
  TwoWire *_i2c_if;
  uint8_t _i2c_addr;
  byte rdptr[8];
  unsigned long lastTime;
  float oldTemperature;
  float oldHumidity;
  Temperature _temp;
  Humidity _humidity;
  void writeCommand(uint16_t );
  bool getTemperature(sensors_event_t*);
  bool getHumidity(sensors_event_t*);
  void readAM232X(byte *rdptr, byte length);
};


#endif /* __AUSEX_AM232X_H__ */
