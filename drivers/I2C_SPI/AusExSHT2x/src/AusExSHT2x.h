#ifndef __AUSEX_SHT2X_H__
#define __AUSEX_SHT2X_H__

#define NO_MEASURE NAN

#define AUSEX_SHT2X_CLASS AusExSHT2x
#define AUSEX_SHT2X_SENSOR_NAME "SHT2x"
#define AUSEX_SHT2X_SENSOR_LIBRARY_VERSION 1
#define AUSEX_SHT2X_SENSOR_TEMPERATURE_MIN_VALUE -40
#define AUSEX_SHT2X_SENSOR_TEMPERATURE_MAX_VALUE 80
#define AUSEX_SHT2X_SENSOR_TEMPERATURE_RESOLUTION 0.1
#define AUSEX_SHT2X_SENSOR_HUMIDITY_MIN_VALUE 0
#define AUSEX_SHT2X_SENSOR_HUMIDITY_MAX_VALUE 100
#define AUSEX_SHT2X_SENSOR_HUMIDITY_RESOLUTION 0.1
#define AUSEX_SHT2X_SENSOR_TEMPERATURE_MIN_DELAY 5000000
#define AUSEX_SHT2X_SENSOR_HUMIDITY_MIN_DELAY 8000000
#define AUSEX_SHT2X_SENSOR_INIT_DELAY 15000
#define AUSEX_SHT2X_SENSOR_DEFAULT_I2C_ADDR 0x40

#define SHT2X_READ_TEMP 0xE3
#define SHT2X_READ_HUMI 0xE5
#define SHT2X_SOFT_RESET 0xFE

#define SH2X_POLYNOMIAL  0x131;  // P(x)=x^8+x^5+x^4+1 = 100110001

#define SHT21 0
#define SHT25 1  // 将来のための予約


#include "AusEx.h"
#include "Wire.h"


class AusExSHT2x {
public:
  AusExSHT2x(TwoWire *theWire, uint32_t type, int32_t tempSensorId=-1, int32_t humiditySensorId=-1);
  bool begin(uint32_t addr=AUSEX_SHT2X_SENSOR_DEFAULT_I2C_ADDR);

  class Temperature : public Adafruit_SensorEx {
  public:
    Temperature(AusExSHT2x * parent, int32_t id);
    bool getEvent(sensors_event_t* event);
    void getSensor(sensor_t* sensor);
    bool enableAutoRange(bool);
    int setMode(int);
    int getMode();
  private:
    AusExSHT2x* _parent;
    int32_t _id;
  };
  class Humidity : public Adafruit_SensorEx {
  public:
    Humidity(AusExSHT2x * parent, int32_t id);
    bool getEvent(sensors_event_t* event);
    void getSensor(sensor_t* sensor);
    bool enableAutoRange(bool);
    int setMode(int);
    int getMode();
  private:
    AusExSHT2x* _parent;
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
  unsigned long lastTime;
  float oldTemperature;
  float oldHumidity;
  Temperature _temp;
  Humidity _humidity;
  void writeCommand(uint16_t );
  bool getTemperature(sensors_event_t*);
  bool getHumidity(sensors_event_t*);
  bool readSHT2x(uint16_t * st, uint16_t * srh);
  void resetSHT2x(void);
};


#endif /* __AUSEX_SHT2X_H__ */
