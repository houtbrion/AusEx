#include "AusExBmp180.h"

/*
 * 
 */
AUSEX_BMP180_CLASS::AUSEX_BMP180_CLASS(TwoWire *theWire, int32_t sensorID){
  _i2c_if=theWire;
  _sensorID=sensorID;
}

bool AUSEX_BMP180_CLASS::begin(uint32_t addr){
  _i2c_addr=addr;
  _i2c_if->begin();

  /* Make sure we have the right device */
  uint8_t id;
  read8(BMP085_REGISTER_CHIPID, &id);
  if(id != 0x55)
  {
    return false;
  }

  /* Set the mode indicator */
  _bmp085Mode = BMP085_MODE_ULTRAHIGHRES;

  /* Coefficients need to be read once */
  readCoefficients();
  return true;
}

/**************************************************************************/
/*!
    @brief  Writes an 8 bit value over I2C
*/
/**************************************************************************/
void AUSEX_BMP180_CLASS::writeCommand(byte reg, byte value)
{
  _i2c_if->beginTransmission((uint8_t)AUSEX_BMP180_SENSOR_DEFAULT_I2C_ADDR);
  #if ARDUINO >= 100
    _i2c_if->write((uint8_t)reg);
    _i2c_if->write((uint8_t)value);
  #else
    _i2c_if->send(reg);
    _i2c_if->send(value);
  #endif
  _i2c_if->endTransmission();
}

/**************************************************************************/
/*!
    @brief  Reads an 8 bit value over I2C
*/
/**************************************************************************/
void AUSEX_BMP180_CLASS::read8(byte reg, uint8_t *value)
{
  _i2c_if->beginTransmission((uint8_t)AUSEX_BMP180_SENSOR_DEFAULT_I2C_ADDR);
  #if ARDUINO >= 100
    _i2c_if->write((uint8_t)reg);
  #else
    _i2c_if->send(reg);
  #endif
  _i2c_if->endTransmission();
  _i2c_if->requestFrom((uint8_t)AUSEX_BMP180_SENSOR_DEFAULT_I2C_ADDR, (byte)1);
  #if ARDUINO >= 100
    *value = _i2c_if->read();
  #else
    *value = _i2c_if->receive();
  #endif  
  _i2c_if->endTransmission();
}

/**************************************************************************/
/*!
    @brief  Reads a 16 bit value over I2C
*/
/**************************************************************************/
void AUSEX_BMP180_CLASS::read16(byte reg, uint16_t *value)
{
  _i2c_if->beginTransmission((uint8_t)AUSEX_BMP180_SENSOR_DEFAULT_I2C_ADDR);
  #if ARDUINO >= 100
    _i2c_if->write((uint8_t)reg);
  #else
    _i2c_if->send(reg);
  #endif
  _i2c_if->endTransmission();
  _i2c_if->requestFrom((uint8_t)AUSEX_BMP180_SENSOR_DEFAULT_I2C_ADDR, (byte)2);
  #if ARDUINO >= 100
    *value = (_i2c_if->read() << 8) | _i2c_if->read();
  #else
    *value = (_i2c_if->receive() << 8) | _i2c_if->receive();
  #endif  
  _i2c_if->endTransmission();
}

/**************************************************************************/
/*!
    @brief  Reads a signed 16 bit value over I2C
*/
/**************************************************************************/
void AUSEX_BMP180_CLASS::readS16(byte reg, int16_t *value)
{
  uint16_t i;
  read16(reg, &i);
  *value = (int16_t)i;
}
/**************************************************************************/
/*!
    @brief  Reads the factory-set coefficients
*/
/**************************************************************************/
void AUSEX_BMP180_CLASS::readCoefficients(void)
{
  readS16(BMP085_REGISTER_CAL_AC1, &_bmp085_coeffs.ac1);
  readS16(BMP085_REGISTER_CAL_AC2, &_bmp085_coeffs.ac2);
  readS16(BMP085_REGISTER_CAL_AC3, &_bmp085_coeffs.ac3);
  read16(BMP085_REGISTER_CAL_AC4, &_bmp085_coeffs.ac4);
  read16(BMP085_REGISTER_CAL_AC5, &_bmp085_coeffs.ac5);
  read16(BMP085_REGISTER_CAL_AC6, &_bmp085_coeffs.ac6);
  readS16(BMP085_REGISTER_CAL_B1, &_bmp085_coeffs.b1);
  readS16(BMP085_REGISTER_CAL_B2, &_bmp085_coeffs.b2);
  readS16(BMP085_REGISTER_CAL_MB, &_bmp085_coeffs.mb);
  readS16(BMP085_REGISTER_CAL_MC, &_bmp085_coeffs.mc);
  readS16(BMP085_REGISTER_CAL_MD, &_bmp085_coeffs.md);
}
/**************************************************************************/
/*!
*/
/**************************************************************************/
void AUSEX_BMP180_CLASS::readRawTemperature(int32_t *temperature)
{
  uint16_t t;
  writeCommand(BMP085_REGISTER_CONTROL, BMP085_REGISTER_READTEMPCMD);
  delay(5);
  read16(BMP085_REGISTER_TEMPDATA, &t);
  *temperature = t;
}

/**************************************************************************/
/*!
*/
/**************************************************************************/
void AUSEX_BMP180_CLASS::readRawPressure(int32_t *pressure)
{
  uint8_t  p8;
  uint16_t p16;
  int32_t  p32;

  writeCommand(BMP085_REGISTER_CONTROL, BMP085_REGISTER_READPRESSURECMD + (_bmp085Mode << 6));
  switch(_bmp085Mode){
    case BMP085_MODE_ULTRALOWPOWER:
      delay(5);
      break;
    case BMP085_MODE_STANDARD:
      delay(8);
      break;
    case BMP085_MODE_HIGHRES:
      delay(14);
      break;
    case BMP085_MODE_ULTRAHIGHRES:
    default:
      delay(26);
      break;
  }

  read16(BMP085_REGISTER_PRESSUREDATA, &p16);
  p32 = (uint32_t)p16 << 8;
  read8(BMP085_REGISTER_PRESSUREDATA+2, &p8);
  p32 += p8;
  p32 >>= (8 - _bmp085Mode);
    
  *pressure = p32;
}

/**************************************************************************/
/*!
    @brief  Compute B5 coefficient used in temperature & pressure calcs.
*/
/**************************************************************************/
int32_t AUSEX_BMP180_CLASS::computeB5(int32_t ut) {
  int32_t X1 = (ut - (int32_t)_bmp085_coeffs.ac6) * ((int32_t)_bmp085_coeffs.ac5) >> 15;
  int32_t X2 = ((int32_t)_bmp085_coeffs.mc << 11) / (X1+(int32_t)_bmp085_coeffs.md);
  return X1 + X2;
}

/**************************************************************************/
/*!
    @brief  Gets the compensated pressure level in kPa
*/
/**************************************************************************/
void AUSEX_BMP180_CLASS::getPressure(float *pressure)
{
  int32_t  ut = 0, up = 0, compp = 0;
  int32_t  x1, x2, b5, b6, x3, b3, p;
  uint32_t b4, b7;

  /* Get the raw pressure and temperature values */
  readRawTemperature(&ut);
  readRawPressure(&up);

  /* Temperature compensation */
  b5 = computeB5(ut);

  /* Pressure compensation */
  b6 = b5 - 4000;
  x1 = (_bmp085_coeffs.b2 * ((b6 * b6) >> 12)) >> 11;
  x2 = (_bmp085_coeffs.ac2 * b6) >> 11;
  x3 = x1 + x2;
  b3 = (((((int32_t) _bmp085_coeffs.ac1) * 4 + x3) << _bmp085Mode) + 2) >> 2;
  x1 = (_bmp085_coeffs.ac3 * b6) >> 13;
  x2 = (_bmp085_coeffs.b1 * ((b6 * b6) >> 12)) >> 16;
  x3 = ((x1 + x2) + 2) >> 2;
  b4 = (_bmp085_coeffs.ac4 * (uint32_t) (x3 + 32768)) >> 15;
  b7 = ((uint32_t) (up - b3) * (50000 >> _bmp085Mode));

  if (b7 < 0x80000000)
  {
    p = (b7 << 1) / b4;
  }
  else
  {
    p = (b7 / b4) << 1;
  }

  x1 = (p >> 8) * (p >> 8);
  x1 = (x1 * 3038) >> 16;
  x2 = (-7357 * p) >> 16;
  compp = p + ((x1 + x2 + 3791) >> 4);

  /* Assign compensated pressure value */
  *pressure = compp;
}

/**************************************************************************/
/*!
    @brief  Reads the sensor and returns the data as a sensors_event_t
*/
/**************************************************************************/
bool AUSEX_BMP180_CLASS::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->size      = sizeof(sensors_event_t);
  event->sensor_id = _sensorID;
  event->type      = AUSEX_BMP180_SENSOR_TYPE;
  event->timestamp = millis();

  /*  */
  float pressure_kPa;
  getPressure(&pressure_kPa);
  event->AUSEX_BMP180_SENSOR_RETURN_VALUE = pressure_kPa / 100.0F;
  return true;
}

/**************************************************************************/
/*!
    @brief  Provides the sensor_t data for this sensor
*/
/**************************************************************************/

void AUSEX_BMP180_CLASS::getSensor(sensor_t* sensor){
  /* Clear the sensor_t object */
  memset(sensor, 0, sizeof(sensor_t));

  /* Insert the sensor name in the fixed length char array */
  strncpy (sensor->name, AUSEX_BMP180_SENSOR_NAME , sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  sensor->version     = AUSEX_BMP180_SENSOR_LIBRARY_VERSION;
  sensor->sensor_id   = _sensorID;
  sensor->type        = AUSEX_BMP180_SENSOR_TYPE;
  sensor->min_value   = AUSEX_BMP180_SENSOR_MIN_VALUE;
  sensor->max_value   = AUSEX_BMP180_SENSOR_MAX_VALUE;
  sensor->resolution  = AUSEX_BMP180_SENSOR_RESOLUTION;
  sensor->min_delay   = AUSEX_BMP180_SENSOR_MIN_DELAY;
  sensor->init_delay  = AUSEX_BMP180_SENSOR_INIT_DELAY;
}


bool AUSEX_BMP180_CLASS::enableAutoRange(bool enabled) {
  return false;
}

int AUSEX_BMP180_CLASS::setMode(int mode) {
  /* Mode boundary check */
  if ((mode > BMP085_MODE_ULTRAHIGHRES) || (mode < BMP085_MODE_ULTRALOWPOWER))
  {
    return 0;
  }
  _bmp085Mode = (uint8_t) mode;
  return 1;
}

int AUSEX_BMP180_CLASS::getMode() {
  return (int) _bmp085Mode;
}

AUSEX_BMP180_SENSOR_VALUE_TYPE AUSEX_BMP180_CLASS::calcValue(int val){
  return val;
}
