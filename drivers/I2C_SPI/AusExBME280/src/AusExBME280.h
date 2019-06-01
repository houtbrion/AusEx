#ifndef __AUSEX_BME280_H__
#define __AUSEX_BME280_H__

#define NO_MEASURE NAN

#define AUSEX_BME280_CLASS AusExBME280
#define AUSEX_BME280_SENSOR_NAME "BME280"
#define AUSEX_BME280_SENSOR_LIBRARY_VERSION 1
#define AUSEX_BME280_SENSOR_TEMPERATURE_MIN_VALUE -40
#define AUSEX_BME280_SENSOR_TEMPERATURE_MAX_VALUE 125
#define AUSEX_BME280_SENSOR_TEMPERATURE_RESOLUTION 1
#define AUSEX_BME280_SENSOR_TEMPERATURE_MIN_DELAY 2000000
#define AUSEX_BME280_SENSOR_HUMIDITY_MIN_VALUE 0
#define AUSEX_BME280_SENSOR_HUMIDITY_MAX_VALUE 100
#define AUSEX_BME280_SENSOR_HUMIDITY_RESOLUTION 1
#define AUSEX_BME280_SENSOR_HUMIDITY_MIN_DELAY 8000000
#define AUSEX_BME280_SENSOR_PRESSURE_MIN_VALUE 0
#define AUSEX_BME280_SENSOR_PRESSURE_MAX_VALUE 100
#define AUSEX_BME280_SENSOR_PRESSURE_RESOLUTION 1
#define AUSEX_BME280_SENSOR_PRESSURE_MIN_DELAY 8000000
#define AUSEX_BME280_SENSOR_INIT_DELAY 2000
#define AUSEX_BME280_SENSOR_DEFAULT_I2C_ADDR 0x77

#include "AusEx.h"
#include "Wire.h"
#include "Adafruit_BME280.h"

/* 測定モード */
#define BME280_NORMAL_MODE  0b0000
#define BME280_FORCE_MODE   0b0001

/* サンプリング */
#define BME280_SAMPLING_NONE 0b0000
#define BME280_SAMPLING_X1   0b0001
#define BME280_SAMPLING_X2   0b0010
#define BME280_SAMPLING_X4   0b0011
#define BME280_SAMPLING_X8   0b0100
#define BME280_SAMPLING_X16  0b0101

/* フィルタ */
#define BME280_FILTER_OFF 0b0000
#define BME280_FILTER_X2  0b0001
#define BME280_FILTER_X4  0b0010
#define BME280_FILTER_X8  0b0011
#define BME280_FILTER_X16 0b0100

/* スタンバイ時間 */
#define BME280_STANDBY_MS_0_5  0b000
#define BME280_STANDBY_MS_10   0b110
#define BME280_STANDBY_MS_20   0b111
#define BME280_STANDBY_MS_62_5 0b001
#define BME280_STANDBY_MS_125  0b010
#define BME280_STANDBY_MS_250  0b011
#define BME280_STANDBY_MS_500  0b100
#define BME280_STANDBY_MS_1000 0b101

class AusExBME280 {
public:
  AusExBME280(TwoWire *theWire, int32_t tempSensorId=-1, int32_t humiditySensorId=-1, int32_t pressureSensorId=-1);
  AusExBME280(uint8_t clock, uint8_t mosi, uint8_t miso, uint8_t cs, int32_t tempSensorId=-1, int32_t humiditySensorId=-1, int32_t pressureSensorId=-1);
  bool begin(uint32_t addr=AUSEX_BME280_SENSOR_DEFAULT_I2C_ADDR);

  class Temperature : public Adafruit_SensorEx {
  public:
    Temperature(AusExBME280* parent, int32_t id);
    bool getEvent(sensors_event_t* event);
    void getSensor(sensor_t* sensor);
    bool enableAutoRange(bool);
    int setMode(int);
    int getMode();
    int generateMode(uint8_t state, uint8_t tempSample, uint8_t humSample , uint8_t pressSample, uint8_t filter, uint8_t standby);
    bool parseMode(int mode, uint8_t *state, uint8_t *tempSample, uint8_t *humSample , uint8_t *pressSample, uint8_t *filter, uint8_t *standby);
  private:
    AusExBME280* _parent;
    int32_t _id;
  };

  class Humidity : public Adafruit_SensorEx {
  public:
    Humidity(AusExBME280* parent, int32_t id);
    bool getEvent(sensors_event_t* event);
    void getSensor(sensor_t* sensor);
    bool enableAutoRange(bool);
    int setMode(int);
    int getMode();
    int generateMode(uint8_t state, uint8_t tempSample, uint8_t humSample , uint8_t pressSample, uint8_t filter, uint8_t standby);
    bool parseMode(int mode, uint8_t *state, uint8_t *tempSample, uint8_t *humSample , uint8_t *pressSample, uint8_t *filter, uint8_t *standby);
  private:
    AusExBME280* _parent;
    int32_t _id;
  };

  class Pressure : public Adafruit_SensorEx {
  public:
    Pressure(AusExBME280* parent, int32_t id);
    bool getEvent(sensors_event_t* event);
    void getSensor(sensor_t* sensor);
    bool enableAutoRange(bool);
    int setMode(int);
    int getMode();
    int generateMode(uint8_t state, uint8_t tempSample, uint8_t humSample , uint8_t pressSample, uint8_t filter, uint8_t standby);
    bool parseMode(int mode, uint8_t *state, uint8_t *tempSample, uint8_t *humSample , uint8_t *pressSample, uint8_t *filter, uint8_t *standby);
  private:
    AusExBME280* _parent;
    int32_t _id;
  };

  Temperature temperature() {
    return _temp;
  };

  Humidity humidity() {
    return _humidity;
  };

  Pressure pressure() {
    return _pressure;
  };

  int setMode(int);
  int getMode();
  bool enableAutoRange(bool);
  int generateMode(uint8_t state, uint8_t tempSample, uint8_t humSample , uint8_t pressSample, uint8_t filter, uint8_t standby);
  bool parseMode(int mode, uint8_t *state, uint8_t *tempSample, uint8_t *humSample , uint8_t *pressSample, uint8_t *filter, uint8_t *standby);

private:
  Adafruit_BME280         _bme280;
  bool                    _bme280Sleep;
  bool                    _i2c;
  TwoWire                 *_i2c_if;
  int                     _mode;
  int                     _clk, _mosi, _miso, _cs;

  Temperature             _temp;
  Humidity                _humidity;
  Pressure                _pressure;

  bool      getTemperature(sensors_event_t*);
  bool      getHumidity(sensors_event_t*);
  bool      getPressure(sensors_event_t*);

};

#endif /* __AUSEX_BME280_H__ */
