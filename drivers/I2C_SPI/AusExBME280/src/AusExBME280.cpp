#include "AusExBME280.h"


/*
 * 
 */

AusExBME280::AusExBME280(TwoWire * theWire , int32_t tempSensorId, int32_t humiditySensorId, int32_t pressureSensorId):
  _i2c(true),
  _i2c_if(theWire),
  _temp(this,tempSensorId),
  _humidity(this,humiditySensorId),
  _pressure(this,pressureSensorId)
{}

AusExBME280::AusExBME280(uint8_t clock, uint8_t mosi, uint8_t miso, uint8_t cs, int32_t tempSensorId, int32_t humiditySensorId, int32_t pressureSensorId):
  _i2c(false),
  _clk(clock),
  _mosi(mosi),
  _miso(miso),
  _cs(cs),
  _temp(this,tempSensorId),
  _humidity(this,humiditySensorId),
  _pressure(this,pressureSensorId)
{}

AusExBME280::Temperature::Temperature(AUSEX_BME280_CLASS * parent, int32_t id):
  _parent(parent),
  _id(id)
{}

AusExBME280::Humidity::Humidity(AUSEX_BME280_CLASS * parent, int32_t id):
  _parent(parent),
  _id(id)
{}

AusExBME280::Pressure::Pressure(AUSEX_BME280_CLASS * parent, int32_t id):
  _parent(parent),
  _id(id)
{}

bool AusExBME280::begin(uint32_t addr){
  bool flag;
  if (_i2c) {
    // i2c接続の場合
    _bme280=Adafruit_BME280();
    flag=_bme280.begin((uint8_t) addr, _i2c_if);
  } else {
    if (_cs==0xFF) {
      // ハードSPI接続の場合
      _bme280=Adafruit_BME280((int8_t) _cs);
    } else {
      // ソフトSPI接続の場合
      _bme280=Adafruit_BME280( _cs,  _mosi, _miso,  _clk);
    }
    flag=_bme280.begin(0x77);
  }
  _bme280Sleep=false;
  _bme280.setSampling(Adafruit_BME280::MODE_NORMAL,Adafruit_BME280::SAMPLING_X16,Adafruit_BME280::SAMPLING_X16,Adafruit_BME280::SAMPLING_X16,Adafruit_BME280::FILTER_OFF,Adafruit_BME280::STANDBY_MS_0_5);
  _mode = generateMode(BME280_NORMAL_MODE,BME280_SAMPLING_X16,BME280_SAMPLING_X16,BME280_SAMPLING_X16,BME280_FILTER_OFF,BME280_STANDBY_MS_0_5);
  return flag;
}

void AusExBME280::Temperature::getSensor(sensor_t* sensor) {
  // Clear sensor definition.
  memset(sensor, 0, sizeof(sensor_t));
  // Set sensor name.
  strncpy (sensor->name, AUSEX_BME280_SENSOR_NAME , sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  // Set version and ID
  sensor->version         = AUSEX_BME280_SENSOR_LIBRARY_VERSION;
  sensor->sensor_id       = _id;
  // Set type and characteristics.
  sensor->type            = SENSOR_TYPE_AMBIENT_TEMPERATURE;
  sensor->min_delay       = AUSEX_BME280_SENSOR_TEMPERATURE_MIN_DELAY;
  sensor->max_value       = AUSEX_BME280_SENSOR_TEMPERATURE_MAX_VALUE;
  sensor->min_value       = AUSEX_BME280_SENSOR_TEMPERATURE_MIN_VALUE;
  sensor->resolution      = AUSEX_BME280_SENSOR_TEMPERATURE_RESOLUTION;
  sensor->init_delay = AUSEX_BME280_SENSOR_INIT_DELAY;
}

void AusExBME280::Humidity::getSensor(sensor_t* sensor) {
  // Clear sensor definition.
  memset(sensor, 0, sizeof(sensor_t));
  // Set sensor name.
  strncpy (sensor->name, AUSEX_BME280_SENSOR_NAME , sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  // Set version and ID
  sensor->version         = AUSEX_BME280_SENSOR_LIBRARY_VERSION;
  sensor->sensor_id       = _id;
  // Set type and characteristics.
  sensor->type            = SENSOR_TYPE_RELATIVE_HUMIDITY;
  sensor->min_delay       = AUSEX_BME280_SENSOR_HUMIDITY_MIN_DELAY;
  sensor->max_value       = AUSEX_BME280_SENSOR_HUMIDITY_MAX_VALUE;
  sensor->min_value       = AUSEX_BME280_SENSOR_HUMIDITY_MIN_VALUE;
  sensor->resolution      = AUSEX_BME280_SENSOR_HUMIDITY_RESOLUTION;
  sensor->init_delay = AUSEX_BME280_SENSOR_INIT_DELAY;
}

void AusExBME280::Pressure::getSensor(sensor_t* sensor) {
  // Clear sensor definition.
  memset(sensor, 0, sizeof(sensor_t));
  // Set sensor name.
  strncpy (sensor->name, AUSEX_BME280_SENSOR_NAME , sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  // Set version and ID
  sensor->version         = AUSEX_BME280_SENSOR_LIBRARY_VERSION;
  sensor->sensor_id       = _id;
  // Set type and characteristics.
  sensor->type            = SENSOR_TYPE_PRESSURE;
  sensor->min_delay       = AUSEX_BME280_SENSOR_PRESSURE_MIN_DELAY;
  sensor->max_value       = AUSEX_BME280_SENSOR_PRESSURE_MAX_VALUE;
  sensor->min_value       = AUSEX_BME280_SENSOR_PRESSURE_MIN_VALUE;
  sensor->resolution      = AUSEX_BME280_SENSOR_PRESSURE_RESOLUTION;
  sensor->init_delay = AUSEX_BME280_SENSOR_INIT_DELAY;
}

bool AusExBME280::getTemperature(sensors_event_t* event){
  if (_bme280Sleep) _bme280.takeForcedMeasurement();
  event->timestamp = millis();
  event->temperature = _bme280.readTemperature();
  if (event->temperature == NO_MEASURE) return false;
  return true;
}

bool AusExBME280::getHumidity(sensors_event_t* event){
  if (_bme280Sleep) _bme280.takeForcedMeasurement();
  event->timestamp = millis();
  event->relative_humidity = _bme280.readHumidity();
  if (event->relative_humidity == NO_MEASURE) return false;
  return true;
}

bool AusExBME280::getPressure(sensors_event_t* event){
  if (_bme280Sleep) _bme280.takeForcedMeasurement();
  event->timestamp = millis();
  event->pressure = _bme280.readPressure();
  if (event->pressure == NO_MEASURE) return false;
  return true;
}

bool AusExBME280::Temperature::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->size      = sizeof(sensors_event_t);
  event->sensor_id = _id;
  event->type      = SENSOR_TYPE_AMBIENT_TEMPERATURE;
  bool flag=_parent->getTemperature(event);
  return flag;
}

bool AusExBME280::Humidity::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->size      = sizeof(sensors_event_t);
  event->sensor_id = _id;
  event->type      = SENSOR_TYPE_RELATIVE_HUMIDITY;
  bool flag=_parent->getHumidity(event);
  return flag;
}

bool AusExBME280::Pressure::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->size      = sizeof(sensors_event_t);
  event->sensor_id = _id;
  event->type      = SENSOR_TYPE_PRESSURE;
  bool flag=_parent->getPressure(event);
  return flag;
}

bool AusExBME280::enableAutoRange(bool enabled) {
  return false;
}

bool AusExBME280::Temperature::enableAutoRange(bool enabled) {
  return _parent->enableAutoRange(enabled);
}

bool AusExBME280::Humidity::enableAutoRange(bool enabled) {
  return _parent->enableAutoRange(enabled);
}

bool AusExBME280::Pressure::enableAutoRange(bool enabled) {
  return _parent->enableAutoRange(enabled);
}

int AusExBME280::setMode(int mode){
  uint8_t state,tempSample,humSample,pressSample,filter,standby;
  parseMode(mode,&state,&tempSample,&humSample,&pressSample,&filter,&standby);
  if ((standby) > 7 ) return 0;
  if ((filter) > 4 ) return 0;
  if ((pressSample) > 5 ) return 0;
  if ((humSample) > 5 ) return 0;
  if ((tempSample) > 5 ) return 0;
  if ((state) > 1) return 0;
  Adafruit_BME280::sensor_mode _bme280Mode;
  Adafruit_BME280::sensor_sampling _tempSampling, _humSampling, _pressSampling;
  Adafruit_BME280::sensor_filter _filter;
  Adafruit_BME280::standby_duration _duration;
  if (state == BME280_NORMAL_MODE) {
    _bme280Mode=Adafruit_BME280::MODE_NORMAL;
    _bme280Sleep=false;
  } else {
    _bme280Mode=Adafruit_BME280::MODE_SLEEP;
    _bme280Sleep=true;
  }
  switch(tempSample) {
    case BME280_SAMPLING_NONE: _tempSampling = Adafruit_BME280::SAMPLING_NONE; break;
    case BME280_SAMPLING_X1: _tempSampling = Adafruit_BME280::SAMPLING_X1; break;
    case BME280_SAMPLING_X2: _tempSampling = Adafruit_BME280::SAMPLING_X2; break;
    case BME280_SAMPLING_X4: _tempSampling = Adafruit_BME280::SAMPLING_X4; break;
    case BME280_SAMPLING_X8: _tempSampling = Adafruit_BME280::SAMPLING_X8; break;
    case BME280_SAMPLING_X16: _tempSampling = Adafruit_BME280::SAMPLING_X16; break;
  }
  switch(humSample) {
    case BME280_SAMPLING_NONE: _humSampling = Adafruit_BME280::SAMPLING_NONE; break;
    case BME280_SAMPLING_X1: _humSampling = Adafruit_BME280::SAMPLING_X1; break;
    case BME280_SAMPLING_X2: _humSampling = Adafruit_BME280::SAMPLING_X2; break;
    case BME280_SAMPLING_X4: _humSampling = Adafruit_BME280::SAMPLING_X4; break;
    case BME280_SAMPLING_X8: _humSampling = Adafruit_BME280::SAMPLING_X8; break;
    case BME280_SAMPLING_X16: _humSampling = Adafruit_BME280::SAMPLING_X16; break;
  }
  switch(pressSample) {
    case BME280_SAMPLING_NONE: _pressSampling = Adafruit_BME280::SAMPLING_NONE; break;
    case BME280_SAMPLING_X1: _pressSampling = Adafruit_BME280::SAMPLING_X1; break;
    case BME280_SAMPLING_X2: _pressSampling = Adafruit_BME280::SAMPLING_X2; break;
    case BME280_SAMPLING_X4: _pressSampling = Adafruit_BME280::SAMPLING_X4; break;
    case BME280_SAMPLING_X8: _pressSampling = Adafruit_BME280::SAMPLING_X8; break;
    case BME280_SAMPLING_X16: _pressSampling = Adafruit_BME280::SAMPLING_X16; break;
  }
  switch(filter) {
    case BME280_FILTER_OFF: _filter = Adafruit_BME280::FILTER_OFF;break;
    case BME280_FILTER_X2: _filter = Adafruit_BME280::FILTER_X2;break;
    case BME280_FILTER_X4: _filter = Adafruit_BME280::FILTER_X4;break;
    case BME280_FILTER_X8: _filter = Adafruit_BME280::FILTER_X8;break;
    case BME280_FILTER_X16: _filter = Adafruit_BME280::FILTER_X16;break;
  }
  switch(standby) {
    case BME280_STANDBY_MS_0_5: _duration = Adafruit_BME280::STANDBY_MS_0_5; break;
    case BME280_STANDBY_MS_10: _duration = Adafruit_BME280::STANDBY_MS_10; break;
    case BME280_STANDBY_MS_20: _duration = Adafruit_BME280::STANDBY_MS_20; break;
    case BME280_STANDBY_MS_62_5: _duration = Adafruit_BME280::STANDBY_MS_62_5; break;
    case BME280_STANDBY_MS_125: _duration = Adafruit_BME280::STANDBY_MS_125; break;
    case BME280_STANDBY_MS_250: _duration = Adafruit_BME280::STANDBY_MS_250; break;
    case BME280_STANDBY_MS_500: _duration = Adafruit_BME280::STANDBY_MS_500; break;
    case BME280_STANDBY_MS_1000: _duration = Adafruit_BME280::STANDBY_MS_1000; break;
  }
  _bme280.setSampling(_bme280Mode,_tempSampling,_humSampling,_pressSampling,_filter,_duration);
  return 1;
}

int AusExBME280::Temperature::setMode(int mode){
  return _parent->setMode(mode);
}

int AusExBME280::Humidity::setMode(int mode){
  return _parent->setMode(mode);
}

int AusExBME280::Pressure::setMode(int mode){
  return _parent->setMode(mode);
}

int AusExBME280::getMode(void){
  return _mode;
}

int AusExBME280::Temperature::getMode(void){
  return _parent->getMode();
}

int AusExBME280::Humidity::getMode(void){
  return _parent->getMode();
}

int AusExBME280::Pressure::getMode(void){
  return _parent->getMode();
}

int AusExBME280::generateMode(uint8_t state, uint8_t tempSample, uint8_t humSample , uint8_t pressSample, uint8_t filter, uint8_t standby) {
  if ((standby) > 7 ) return -1;
  if ((filter) > 4 ) return -1;
  if ((pressSample) > 5 ) return -1;
  if ((humSample) > 5 ) return -1;
  if ((tempSample) > 5 ) return -1;
  if ((state) > 1) return -1;
  int mode = (state << 20) | (tempSample << 16) | (humSample<<12) | (pressSample<<8) | (filter<<4) | standby;
  return mode;
}

int AusExBME280::Temperature::generateMode(uint8_t state, uint8_t tempSample, uint8_t humSample , uint8_t pressSample, uint8_t filter, uint8_t standby) {
  return _parent->generateMode(state, tempSample, humSample, pressSample, filter, standby);
}

int AusExBME280::Humidity::generateMode(uint8_t state, uint8_t tempSample, uint8_t humSample , uint8_t pressSample, uint8_t filter, uint8_t standby) {
  return _parent->generateMode(state, tempSample, humSample, pressSample, filter, standby);
}

int AusExBME280::Pressure::generateMode(uint8_t state, uint8_t tempSample, uint8_t humSample , uint8_t pressSample, uint8_t filter, uint8_t standby) {
  return _parent->generateMode(state, tempSample, humSample, pressSample, filter, standby);
}

bool AusExBME280::parseMode(int mode, uint8_t *state, uint8_t *tempSample, uint8_t *humSample , uint8_t *pressSample, uint8_t *filter, uint8_t *standby){
  *standby      = (uint8_t) (0x0000000F & mode);
  *filter       = (uint8_t) ((0x000000F0 & mode)>>4);
  *pressSample  = (uint8_t) ((0x00000F00 & mode)>>8);
  *humSample    = (uint8_t) ((0x0000F000 & mode)>>12);
  *tempSample   = (uint8_t) ((0x000F0000 & mode)>>16);
  *state        = (uint8_t) ((0x00F00000 & mode)>>20);
  if ((*standby) > 7 ) return false;
  if ((*filter) > 4 ) return false;
  if ((*pressSample) > 5 ) return false;
  if ((*humSample) > 5 ) return false;
  if ((*tempSample) > 5 ) return false;
  if ((*state) > 1) return false;
  return true;
}

bool AusExBME280::Temperature::parseMode(int mode, uint8_t *state, uint8_t *tempSample, uint8_t *humSample , uint8_t *pressSample, uint8_t *filter, uint8_t *standby){
  return  _parent->parseMode(mode,state,tempSample,humSample,pressSample,filter,standby);
}

bool AusExBME280::Humidity::parseMode(int mode, uint8_t *state, uint8_t *tempSample, uint8_t *humSample , uint8_t *pressSample, uint8_t *filter, uint8_t *standby){
  return  _parent->parseMode(mode,state,tempSample,humSample,pressSample,filter,standby);
}

bool AusExBME280::Pressure::parseMode(int mode, uint8_t *state, uint8_t *tempSample, uint8_t *humSample , uint8_t *pressSample, uint8_t *filter, uint8_t *standby){
  return  _parent->parseMode(mode,state,tempSample,humSample,pressSample,filter,standby);
}
