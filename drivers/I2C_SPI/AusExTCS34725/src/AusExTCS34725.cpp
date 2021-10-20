#include "AusExTCS34725.h"



void AUSEX_TCS34725_CLASS::write8(uint8_t reg, uint32_t value) {
  _wire->beginTransmission(_i2caddr);
  _wire->write(TCS34725_COMMAND_BIT | reg);
  _wire->write(value & 0xFF);
  _wire->endTransmission();
}

uint8_t AUSEX_TCS34725_CLASS::read8(uint8_t reg) {
  _wire->beginTransmission(_i2caddr);
  _wire->write(TCS34725_COMMAND_BIT | reg);
  _wire->endTransmission();

  _wire->requestFrom(_i2caddr, 1);
  return _wire->read();
}

uint16_t AUSEX_TCS34725_CLASS::read16(uint8_t reg) {
  uint16_t x;
  uint16_t t;

  _wire->beginTransmission(_i2caddr);
  _wire->write(TCS34725_COMMAND_BIT | reg);
  _wire->endTransmission();

  _wire->requestFrom(_i2caddr, 2);
  t = _wire->read();
  x = _wire->read();
  x <<= 8;
  x |= t;
  return x;
}

void AUSEX_TCS34725_CLASS::enable() {
  write8(TCS34725_ENABLE, TCS34725_ENABLE_PON);
  delay(3);
  write8(TCS34725_ENABLE, TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN);
  /* Set a delay for the integration time.
    This is only necessary in the case where enabling and then
    immediately trying to read values back. This is because setting
    AEN triggers an automatic integration, so if a read RGBC is
    performed too quickly, the data is not yet valid and all 0's are
    returned */
  switch (_tcs34725IntegrationTime) {
  case TCS34725_INTEGRATIONTIME_2_4MS:
    delay(3);
    break;
  case TCS34725_INTEGRATIONTIME_24MS:
    delay(24);
    break;
  case TCS34725_INTEGRATIONTIME_50MS:
    delay(50);
    break;
  case TCS34725_INTEGRATIONTIME_101MS:
    delay(101);
    break;
  case TCS34725_INTEGRATIONTIME_154MS:
    delay(154);
    break;
  case TCS34725_INTEGRATIONTIME_700MS:
    delay(700);
    break;
  }
}

void AUSEX_TCS34725_CLASS::disable() {
  /* Turn the device off to save power */
  uint8_t reg = 0;
  reg = read8(TCS34725_ENABLE);
  write8(TCS34725_ENABLE, reg & ~(TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN));
}

void AUSEX_TCS34725_CLASS::setIntegrationTime(tcs34725IntegrationTime_t it) {
  if (!_tcs34725Initialised)
    begin();

  /* Update the timing register */
  write8(TCS34725_ATIME, it);

  /* Update value placeholders */
  _tcs34725IntegrationTime = it;
}

void AUSEX_TCS34725_CLASS::setGain(tcs34725Gain_t gain) {
  if (!_tcs34725Initialised)
    begin();

  /* Update the timing register */
  write8(TCS34725_CONTROL, gain);

  /* Update value placeholders */
  _tcs34725Gain = gain;
}

void AUSEX_TCS34725_CLASS::getRawData(uint16_t *r, uint16_t *g, uint16_t *b,
                                   uint16_t *c) {
  if (!_tcs34725Initialised)
    begin();

  *c = read16(TCS34725_CDATAL);
  *r = read16(TCS34725_RDATAL);
  *g = read16(TCS34725_GDATAL);
  *b = read16(TCS34725_BDATAL);

  /* Set a delay for the integration time */
  switch (_tcs34725IntegrationTime) {
  case TCS34725_INTEGRATIONTIME_2_4MS:
    delay(3);
    break;
  case TCS34725_INTEGRATIONTIME_24MS:
    delay(24);
    break;
  case TCS34725_INTEGRATIONTIME_50MS:
    delay(50);
    break;
  case TCS34725_INTEGRATIONTIME_101MS:
    delay(101);
    break;
  case TCS34725_INTEGRATIONTIME_154MS:
    delay(154);
    break;
  case TCS34725_INTEGRATIONTIME_700MS:
    delay(700);
    break;
  }
}

void AUSEX_TCS34725_CLASS::getRawDataOneShot(uint16_t *r, uint16_t *g, uint16_t *b,
                                          uint16_t *c) {
  if (!_tcs34725Initialised)
    begin();

  enable();
  getRawData(r, g, b, c);
  disable();
}

float AUSEX_TCS34725_CLASS::calculateColorTemperature(void) {
  float X, Y, Z; /* RGB to XYZ correlation      */
  float xc, yc;  /* Chromaticity co-ordinates   */
  float n;       /* McCamy's formula            */
  float cct;

  /* 1. Map RGB values to their XYZ counterparts.    */
  /* Based on 6500K fluorescent, 3000K fluorescent   */
  /* and 60W incandescent values for a wide range.   */
  /* Note: Y = Illuminance or lux                    */
  X = (-0.14282F * r) + (1.54924F * g) + (-0.95641F * b);
  Y = (-0.32466F * r) + (1.57837F * g) + (-0.73191F * b);
  Z = (-0.68202F * r) + (0.77073F * g) + (0.56332F * b);

  /* 2. Calculate the chromaticity co-ordinates      */
  xc = (X) / (X + Y + Z);
  yc = (Y) / (X + Y + Z);

  /* 3. Use McCamy's formula to determine the CCT    */
  n = (xc - 0.3320F) / (0.1858F - yc);


  /* Calculate the final CCT */
  cct = (float)
      (449.0F * n*n*n) + (3525.0F *n*n) + (6823.3F * n) + 5520.33F;

  /* Return the results in degrees Kelvin */
  return cct;
}

float AUSEX_TCS34725_CLASS::calculateColorTemperature_dn40(void) {
  int rc;              /* Error return code */
  uint16_t r2, g2, b2; /* RGB values minus IR component */
  int gl;              /* Results of the initial lux conversion */
  uint8_t gain_int;    /* Gain multiplier as a normal integer */
  uint16_t sat;        /* Digital saturation level */
  uint16_t ir;         /* Inferred IR content */

  /* Analog/Digital saturation:
   *
   * (a) As light becomes brighter, the clear channel will tend to
   *     saturate first since R+G+B is approximately equal to C.
   * (b) The TCS34725 accumulates 1024 counts per 2.4ms of integration
   *     time, up to a maximum values of 65535. This means analog
   *     saturation can occur up to an integration time of 153.6ms
   *     (64*2.4ms=153.6ms).
   * (c) If the integration time is > 153.6ms, digital saturation will
   *     occur before analog saturation. Digital saturation occurs when
   *     the count reaches 65535.
   */
  if ((256 - _tcs34725IntegrationTime) > 63) {
    /* Track digital saturation */
    sat = 65535;
  } else {
    /* Track analog saturation */
    sat = 1024 * (256 - _tcs34725IntegrationTime);
  }

  /* Ripple rejection:
   *
   * (a) An integration time of 50ms or multiples of 50ms are required to
   *     reject both 50Hz and 60Hz ripple.
   * (b) If an integration time faster than 50ms is required, you may need
   *     to average a number of samples over a 50ms period to reject ripple
   *     from fluorescent and incandescent light sources.
   *
   * Ripple saturation notes:
   *
   * (a) If there is ripple in the received signal, the value read from C
   *     will be less than the max, but still have some effects of being
   *     saturated. This means that you can be below the 'sat' value, but
   *     still be saturating. At integration times >150ms this can be
   *     ignored, but <= 150ms you should calculate the 75% saturation
   *     level to avoid this problem.
   */
  if ((256 - _tcs34725IntegrationTime) <= 63) {
    /* Adjust sat to 75% to avoid analog saturation if atime < 153.6ms */
    sat -= sat / 4;
  }

  /* Check for saturation and mark the sample as invalid if true */
  if (c >= sat) {
    return 0;
  }

  /* AMS RGB sensors have no IR channel, so the IR content must be */
  /* calculated indirectly. */
  ir = (r + g + b > c) ? (r + g + b - c) / 2 : 0;

  /* Remove the IR component from the raw RGB values */
  r2 = r - ir;
  g2 = g - ir;
  b2 = b - ir;

  /* Convert gain to a usable integer value */
  switch (_tcs34725Gain) {
  case TCS34725_GAIN_4X: /* GAIN 4X */
    gain_int = 4;
    break;
  case TCS34725_GAIN_16X: /* GAIN 16X */
    gain_int = 16;
    break;
  case TCS34725_GAIN_60X: /* GAIN 60X */
    gain_int = 60;
    break;
  case TCS34725_GAIN_1X: /* GAIN 1X */
  default:
    gain_int = 1;
    break;
  }

  /* Calculate the counts per lux (CPL), taking into account the optional
   * arguments for Glass Attenuation (GA) and Device Factor (DF).
   *
   * GA = 1/T where T is glass transmissivity, meaning if glass is 50%
   * transmissive, the GA is 2 (1/0.5=2), and if the glass attenuates light
   * 95% the GA is 20 (1/0.05). A GA of 1.0 assumes perfect transmission.
   *
   * NOTE: It is recommended to have a CPL > 5 to have a lux accuracy
   *       < +/- 0.5 lux, where the digitization error can be calculated via:
   *       'DER = (+/-2) / CPL'.
   */
  float cpl =
      (((256 - _tcs34725IntegrationTime) * 2.4f) * gain_int) / (1.0f * 310.0f);

  /* Determine lux accuracy (+/- lux) */
  float der = 2.0f / cpl;

  /* Determine the maximum lux value */
  float max_lux = 65535.0 / (cpl * 3);

  /* Lux is a function of the IR-compensated RGB channels and the associated
   * color coefficients, with G having a particularly heavy influence to
   * match the nature of the human eye.
   *
   * NOTE: The green value should be > 10 to ensure the accuracy of the lux
   *       conversions. If it is below 10, the gain should be increased, but
   *       the clear<100 check earlier should cover this edge case.
   */
  gl = 0.136f * (float)r2 + /** Red coefficient. */
       1.000f * (float)g2 + /** Green coefficient. */
       -0.444f * (float)b2; /** Blue coefficient. */

  float lux = gl / cpl;

  /* A simple method of measuring color temp is to use the ratio of blue */
  /* to red light, taking IR cancellation into account. */
  float cct = (3810 * (uint32_t)b2) / /** Color temp coefficient. */
                     (uint32_t)r2 +
                 1391; /** Color temp offset. */

  return cct;
}

float AUSEX_TCS34725_CLASS::calculateLux(void) {
  float illuminance;

  /* This only uses RGB ... how can we integrate clear or calculate lux */
  /* based exclusively on clear since this might be more reliable?      */
  illuminance = (-0.32466F * r) + (1.57837F * g) + (-0.73191F * b);

  return illuminance;
}

void AUSEX_TCS34725_CLASS::setInterrupt(boolean i) {
  uint8_t r = read8(TCS34725_ENABLE);
  if (i) {
    r |= TCS34725_ENABLE_AIEN;
  } else {
    r &= ~TCS34725_ENABLE_AIEN;
  }
  write8(TCS34725_ENABLE, r);
}

void AUSEX_TCS34725_CLASS::clearInterrupt() {
  _wire->beginTransmission(_i2caddr);
  _wire->write(TCS34725_COMMAND_BIT | 0x66);
  _wire->endTransmission();
}

void AUSEX_TCS34725_CLASS::setIntLimits(uint16_t low, uint16_t high) {
  write8(0x04, low & 0xFF);
  write8(0x05, low >> 8);
  write8(0x06, high & 0xFF);
  write8(0x07, high >> 8);
}

/*
 * 
 */
AUSEX_TCS34725_CLASS::AUSEX_TCS34725_CLASS(TwoWire *theWire, int32_t sensorID){
  _wire=theWire;
  _sensorID=sensorID;
  _tcs34725Initialised = false;
  _tcs34725IntegrationTime = TCS34725_INTEGRATIONTIME_2_4MS;
  _tcs34725Gain = TCS34725_GAIN_1X;
}

bool AUSEX_TCS34725_CLASS::begin(uint32_t addr){
  _i2caddr=addr;
  _wire->begin();
  /* Make sure we're actually connected */
  uint8_t x = read8(TCS34725_ID);
  if ((x != 0x44) && (x != 0x10)) {
    return false;
  }
  _tcs34725Initialised = true;

  /* Set default integration time and gain */
  setIntegrationTime(_tcs34725IntegrationTime);
  setGain(_tcs34725Gain);

  /* Note: by default, the device is in power down mode on bootup */
  enable();
  return true;
}

bool AUSEX_TCS34725_CLASS::getEvent(sensors_event_t* event){
  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->size      = sizeof(sensors_event_t);
  event->sensor_id = _sensorID;
  event->type      = AUSEX_TCS34725_SENSOR_TYPE;
  event->timestamp = millis();

  //uint16_t r, g, b, c;
  getRawData(&r, &g, &b, &c);

  // Avoid divide by zero errors ... if clear = 0 return black
  if (c == 0) {
    r = g = b = 0;
    event->color.r=0;
    event->color.g=0;
    event->color.b=0;


    event->color.rgba= (uint8_t)(event->color.r * 0xFF) << 16|
                      (uint8_t)(event->color.g * 0xFF) << 8 |
                      (uint8_t)(event->color.b * 0xFF) |
                      0xFF000000;
    return true;
  }

  event->color.r=(float)r/c;
  event->color.g=(float)g/c;
  event->color.b=(float)b/c;


  event->color.rgba= (uint8_t)(event->color.r * 0xFF) << 16|
                      (uint8_t)(event->color.g * 0xFF) << 8 |
                      (uint8_t)(event->color.b * 0xFF) |
                      0xFF000000;
  return true;
}

void AUSEX_TCS34725_CLASS::getSensor(sensor_t* sensor){
  /* Clear the sensor_t object */
  memset(sensor, 0, sizeof(sensor_t));

  /* Insert the sensor name in the fixed length char array */
  strncpy (sensor->name, AUSEX_TCS34725_SENSOR_NAME , sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  sensor->version     = AUSEX_TCS34725_SENSOR_LIBRARY_VERSION;
  sensor->sensor_id   = _sensorID;
  sensor->type        = AUSEX_TCS34725_SENSOR_TYPE;
  sensor->min_value   = AUSEX_TCS34725_SENSOR_MIN_VALUE;
  sensor->max_value   = AUSEX_TCS34725_SENSOR_MAX_VALUE;
  sensor->resolution  = AUSEX_TCS34725_SENSOR_RESOLUTION;
  sensor->min_delay   = AUSEX_TCS34725_SENSOR_MIN_DELAY;
  sensor->init_delay   = AUSEX_TCS34725_SENSOR_INIT_DELAY;
}

bool AUSEX_TCS34725_CLASS::enableAutoRange(bool enabled) {
  return false;
}

int AUSEX_TCS34725_CLASS::generateMode(tcs34725Gain_t gain , tcs34725IntegrationTime_t itime) {
  return gain*256+itime;
}

bool AUSEX_TCS34725_CLASS::parseMode(int mode, tcs34725Gain_t *gain , tcs34725IntegrationTime_t *itime){
  uint32_t flag = 0xFF & mode;
  switch (flag) {
    case 0xFF: *itime=TCS34725_INTEGRATIONTIME_2_4MS;break;
    case 0xF6: *itime=TCS34725_INTEGRATIONTIME_24MS;break;
    case 0xEB: *itime=TCS34725_INTEGRATIONTIME_50MS;break;
    case 0xD5: *itime=TCS34725_INTEGRATIONTIME_101MS;break;
    case 0xC0: *itime=TCS34725_INTEGRATIONTIME_154MS;break;
    case 0x00: *itime=TCS34725_INTEGRATIONTIME_700MS;break;
    default: return false;
  }
  flag=(mode >> 8) & 0xFF;
  switch (flag) {
    case 0x00: *gain=TCS34725_GAIN_1X;break;
    case 0x01: *gain=TCS34725_GAIN_4X;break;
    case 0x02: *gain=TCS34725_GAIN_16X;break;
    case 0x03: *gain=TCS34725_GAIN_60X;break;
    default: return false;
  }
  return true;
}


int AUSEX_TCS34725_CLASS::setMode(int mode) {
  tcs34725Gain_t gain;
  tcs34725IntegrationTime_t itime;
  if (parseMode(mode,&gain, &itime)) {
    setGain(gain);
    setIntegrationTime(itime);
    return 1;
  }
  return 0;
}

int AUSEX_TCS34725_CLASS::getMode() {
  return generateMode(_tcs34725Gain,_tcs34725IntegrationTime);
}
