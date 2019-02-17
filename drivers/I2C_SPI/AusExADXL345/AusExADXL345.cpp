
#include <limits.h>

#include "AusExADXL345.h"

/**************************************************************************/
/*!
    @brief  Abstract away platform differences in Arduino Wire library
*/
/**************************************************************************/
inline uint8_t ADXL345_AusEx::i2cread(void) {
  return _i2c_if->read();
}

/**************************************************************************/
/*!
    @brief  Abstract away platform differences in Arduino Wire library
*/
/**************************************************************************/
inline void ADXL345_AusEx::i2cwrite(uint8_t x) {
  _i2c_if->write((uint8_t)x);
}

/**************************************************************************/
/*!
    @brief  Abstract away SPI receiver & transmitter
*/
/**************************************************************************/
uint8_t spixfer(uint8_t clock, uint8_t miso, uint8_t mosi, uint8_t data) {
  // hardware SPI
  if ( clock == 0xFF ) {
    return SPI.transfer(data);
  }
  // software SPI
  uint8_t reply = 0;
  for (int i=7; i>=0; i--) {
    reply <<= 1;
    digitalWrite(clock, LOW);
    digitalWrite(mosi, data & (1<<i));
    digitalWrite(clock, HIGH);
    if (digitalRead(miso)) 
      reply |= 1;
  }
  return reply;
}

/**************************************************************************/
/*!
    @brief  Writes 8-bits to the specified destination register
*/
/**************************************************************************/
void ADXL345_AusEx::writeRegister(uint8_t reg, uint8_t value) {
  if (_i2c) {
    _i2c_if->begin();
    _i2c_if->beginTransmission((uint8_t)_i2caddr);
    i2cwrite((uint8_t)reg);
    i2cwrite((uint8_t)(value));
    _i2c_if->endTransmission();
  } else {
    if ( _clk == 0xFF ) SPI.beginTransaction(SPISettings(500000, MSBFIRST, SPI_MODE3));
    digitalWrite(_cs, LOW);
    spixfer(_clk, _di, _do, reg);
    spixfer(_clk, _di, _do, value);
    digitalWrite(_cs, HIGH);
    if ( _clk == 0xFF ) SPI.endTransaction();
  }
}

/**************************************************************************/
/*!
    @brief  Reads 8-bits from the specified register
*/
/**************************************************************************/
uint8_t ADXL345_AusEx::readRegister(uint8_t reg) {
  if (_i2c) {
    _i2c_if->begin();
    _i2c_if->beginTransmission((uint8_t)_i2caddr);
    i2cwrite(reg);
    _i2c_if->endTransmission();
    _i2c_if->requestFrom((uint8_t)_i2caddr, 1);
    return (i2cread());
  } else {
    if ( _clk == 0xFF ) SPI.beginTransaction(SPISettings(500000, MSBFIRST, SPI_MODE3));
    reg |= 0x80; // read byte
    digitalWrite(_cs, LOW);
    spixfer(_clk, _di, _do, reg);
    uint8_t reply = spixfer(_clk, _di, _do, 0xFF);
    digitalWrite(_cs, HIGH);
    if ( _clk == 0xFF ) SPI.endTransaction();
    return reply;
  }
}

/**************************************************************************/
/*!
    @brief  Reads 16-bits from the specified register
*/
/**************************************************************************/
int16_t ADXL345_AusEx::read16(uint8_t reg) {
  if (_i2c) {
    _i2c_if->begin();
    _i2c_if->beginTransmission((uint8_t)_i2caddr);
    i2cwrite(reg);
    _i2c_if->endTransmission();
    _i2c_if->requestFrom((uint8_t)_i2caddr, 2);
    return (uint16_t)(i2cread() | (i2cread() << 8));  
  } else {
    if ( _clk == 0xFF ) SPI.beginTransaction(SPISettings(500000, MSBFIRST, SPI_MODE3));
    reg |= 0x80 | 0x40; // read byte | multibyte
    digitalWrite(_cs, LOW);
    spixfer(_clk, _di, _do, reg);
    uint16_t reply = spixfer(_clk, _di, _do, 0xFF)  | (spixfer(_clk, _di, _do, 0xFF) << 8);
    digitalWrite(_cs, HIGH);
    if ( _clk == 0xFF ) SPI.endTransaction();
    return reply;
  }
}

/**************************************************************************/
/*! 
    @brief  Reads the device ID (can be used to check connection)
*/
/**************************************************************************/
uint8_t ADXL345_AusEx::getDeviceID(void) {
  // Check device ID register
  return readRegister(ADXL345_REG_DEVID);
}

/**************************************************************************/
/*! 
    @brief  Gets the most recent X axis value
*/
/**************************************************************************/
int16_t ADXL345_AusEx::getX(void) {
  return read16(ADXL345_REG_DATAX0);
}

/**************************************************************************/
/*! 
    @brief  Gets the most recent Y axis value
*/
/**************************************************************************/
int16_t ADXL345_AusEx::getY(void) {
  return read16(ADXL345_REG_DATAY0);
}

/**************************************************************************/
/*! 
    @brief  Gets the most recent Z axis value
*/
/**************************************************************************/
int16_t ADXL345_AusEx::getZ(void) {
  return read16(ADXL345_REG_DATAZ0);
}

/**************************************************************************/
/*!
    @brief  Instantiates a new ADXL345 class
*/
/**************************************************************************/
ADXL345_AusEx::ADXL345_AusEx(int32_t sensorID) {
  _sensorID = sensorID;
  _range = ADXL345_RANGE_2_G;
  _i2c = true;
  _i2caddr = _SENSOR_DEFAULT_I2C_ADDR;
}

/**************************************************************************/
/*!
    @brief  Instantiates a new ADXL345 class in SPI mode
*/
/**************************************************************************/
ADXL345_AusEx::ADXL345_AusEx(uint8_t clock, uint8_t miso, uint8_t mosi, uint8_t cs, int32_t sensorID) {
  _sensorID = sensorID;
  _range = ADXL345_RANGE_2_G;
  _cs = cs;
  _clk = clock;
  _do = mosi;
  _di = miso;
  _i2c = false;
}

/**************************************************************************/
/*!
    @brief  Setups the HW (reads coefficients values, etc.)
*/
/**************************************************************************/
bool ADXL345_AusEx::begin(TwoWire *theWire) {
  _i2c_if=theWire;
  if (!_i2c) {
    digitalWrite(_cs, HIGH);
    pinMode(_cs, OUTPUT);
    if (_clk == 0xFF ) {
      SPI.begin();
    } else {
      pinMode(_clk, OUTPUT);
      digitalWrite(_clk, HIGH);
      pinMode(_do, OUTPUT);
      pinMode(_di, INPUT);
    }
  }

  /* Check connection */
  uint8_t deviceid = getDeviceID();
  if (deviceid != 0xE5)
  {
    /* No ADXL345 detected ... return false */
    //return false;
  }
  
  // Enable measurements
  writeRegister(ADXL345_REG_POWER_CTL, 0x08);  
    
  return true;
}

/**************************************************************************/
/*!
    @brief  Sets the g range for the accelerometer
*/
/**************************************************************************/
void _TEMPLATE_CLASS::setRange(uint8_t range)
{
  /* Read the data format register to preserve bits */
  uint8_t format = readRegister(ADXL345_REG_DATA_FORMAT);

  /* Update the data rate */
  format &= ~0x0F;
  format |= range;
  
  /* Make sure that the FULL-RES bit is enabled for range scaling */
  format |= 0x08;
  
  /* Write the register back to the IC */
  writeRegister(ADXL345_REG_DATA_FORMAT, format);
  
  /* Keep track of the current range (to avoid readbacks) */
  _range = range;
}

/**************************************************************************/
/*!
    @brief  Gets the g range for the accelerometer
*/
/**************************************************************************/
uint8_t _TEMPLATE_CLASS::getRange(void)
{
  _rate = (uint8_t)(readRegister(ADXL345_REG_DATA_FORMAT) & 0x03);
  return _rate;
}

/**************************************************************************/
/*!
    @brief  Sets the data rate for the ADXL345 (controls power consumption)
*/
/**************************************************************************/
void _TEMPLATE_CLASS::setDataRate(uint8_t dataRate)
{
  /* Note: The LOW_POWER bits are currently ignored and we always keep the device in 'normal' mode */
  _rate = dataRate;
  writeRegister(ADXL345_REG_BW_RATE, dataRate);
}

/**************************************************************************/
/*!
    @brief  Gets the data rate for the ADXL345 (controls power consumption)
*/
/**************************************************************************/
uint8_t _TEMPLATE_CLASS::getDataRate(void)
{
  _rate = (uint8_t)(readRegister(ADXL345_REG_BW_RATE) & 0x0F);
  return _rate;
}

/**************************************************************************/
/*! 
    @brief  Gets the most recent sensor event
*/
/**************************************************************************/
bool ADXL345_AusEx::getEvent(sensors_event_t *event) {
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));
  
  event->version   = sizeof(sensors_event_t);
  event->sensor_id = _sensorID;
  event->type      = _SENSOR_TYPE;
  event->timestamp = 0;
  event->acceleration.x = getX() * ADXL345_MG2G_MULTIPLIER * SENSORS_GRAVITY_STANDARD;
  event->acceleration.y = getY() * ADXL345_MG2G_MULTIPLIER * SENSORS_GRAVITY_STANDARD;
  event->acceleration.z = getZ() * ADXL345_MG2G_MULTIPLIER * SENSORS_GRAVITY_STANDARD;
  
  return true;
}

/**************************************************************************/
/*! 
    @brief  Gets the sensor_t data
*/
/**************************************************************************/
void ADXL345_AusEx::getSensor(sensor_t *sensor) {
  /* Clear the sensor_t object */
  memset(sensor, 0, sizeof(sensor_t));

  /* Insert the sensor name in the fixed length char array */
  strncpy (sensor->name, _SENSOR_NAME , sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  sensor->version     = 1;
  sensor->sensor_id   = _sensorID;
  sensor->type        = _SENSOR_TYPE;
  sensor->min_delay   = _SENSOR_MIN_DELAY;
  sensor->max_value   = _SENSOR_MAX_VALUE;  /* -16g = 156.9064 m/s^2  */
  sensor->min_value   = _SENSOR_MIN_VALUE;  /*  16g = 156.9064 m/s^2  */
  sensor->resolution  = _SENSOR_RESOLUTION; /*  4mg = 0.0392266 m/s^2 */ 
}
/**************************************************************************/
/*! 

*/
/**************************************************************************/
bool ADXL345_AusEx::enableAutoRange(bool flag) {
  return true;
}
/**************************************************************************/
/*! 

*/
/**************************************************************************/
int ADXL345_AusEx::setMode(int mode) {
  _range=getRangeParam(mode);
  _rate=getRateParam(mode);
  setDataRate(_rate);
  setRange(_range);
  return 0;
}
/**************************************************************************/
/*!

*/
/**************************************************************************/
int _TEMPLATE_CLASS::getMode() {
  return 256*getRange()+getDataRate();
}
/**************************************************************************/
/*!

*/
/**************************************************************************/
int getModeParam(uint8_t range, uint8_t rate) {
return range*256+rate;
}
/**************************************************************************/
/*!

*/
/**************************************************************************/
uint8_t getRangeParam(int mode) {
  return (uint8_t) ((mode >> 8) & 0xFF);
}
/**************************************************************************/
/*!

*/
/**************************************************************************/
uint8_t getRateParam(int mode) {
  return (uint8_t) (mode & 0xFF);
}
