/*************************************************** 
  This is a library for the HDC1000 Humidity & Temp Sensor

  Designed specifically to work with the HDC1000 sensor from Adafruit
  ----> https://www.adafruit.com/products/2635

  These sensors use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "Adafruit_HDC1000.h"
#if defined(__AVR__)
  #include <util/delay.h>
#endif

Adafruit_HDC1000::Adafruit_HDC1000() {
	_type=HDC1000;
	_i2caddr=HDC1000_I2CADDR;
}

/*
Adafruit_HDC1000::Adafruit_HDC1000(uint8_t type) {
	_type=type;
	switch(_type){
	case HDC1008:
	       _i2caddr=HDC1008_I2CADDR;
	case HDC1010:
	       _i2caddr=HDC1010_I2CADDR;
	case HDC1080:
	       _i2caddr=HDC1080_I2CADDR;
	default:
	       _i2caddr=HDC1000_I2CADDR;
	}
}
*/

//Adafruit_HDC1000::Adafruit_HDC1000(uint8_t type, uint32_t addr) {
Adafruit_HDC1000::Adafruit_HDC1000(uint32_t type, uint8_t addr) {
	_type=type;
	_i2caddr=addr;
}

boolean Adafruit_HDC1000::setup() {
	_i2c_if->begin();
	reset();
	switch(_type){
	case HDC1008:
		if (read16(HDC1008_MANUFID_REG) != HDC1008_MANUFID) return false;
		if (read16(HDC1008_DEVICEID_REG) != HDC1008_DEVICEID) return false;
	case HDC1010:
		if (read16(HDC1010_MANUFID_REG) != HDC1010_MANUFID) return false;
		if (read16(HDC1010_DEVICEID_REG) != HDC1010_DEVICEID) return false;
	case HDC1080:
		if (read16(HDC1080_MANUFID_REG) != HDC1080_MANUFID) return false;
		if (read16(HDC1080_DEVICEID_REG) != HDC1080_DEVICEID) return false;
	default:
		if (read16(HDC1000_MANUFID_REG) != HDC1000_MANUFID) return false;
		if (read16(HDC1000_DEVICEID_REG) != HDC1000_DEVICEID) return false;
	}
	return true;
}

/*
boolean Adafruit_HDC1000::begin() {
	return setup();
}
*/

boolean Adafruit_HDC1000::begin(TwoWire *theWire, uint32_t type,  uint8_t addr) {
	_i2c_if = theWire;
	_type = type;
	_i2caddr = addr;
	return setup();
}

void Adafruit_HDC1000::reset(void) {
	// reset, and select 14 bit temp & humidity
	uint16_t config;
	switch(_type){
	case HDC1008:
		config = HDC1008_CONFIG_RST | HDC1008_CONFIG_MODE | HDC1008_CONFIG_TRES_14 | HDC1008_CONFIG_HRES_14;
	case HDC1010:
		config = HDC1010_CONFIG_RST | HDC1010_CONFIG_MODE | HDC1010_CONFIG_TRES_14 | HDC1010_CONFIG_HRES_14;
	case HDC1080:
		config = HDC1080_CONFIG_RST | HDC1080_CONFIG_MODE | HDC1080_CONFIG_TRES_14 | HDC1080_CONFIG_HRES_14;
	default:
		config = HDC1000_CONFIG_RST | HDC1000_CONFIG_MODE | HDC1000_CONFIG_TRES_14 | HDC1000_CONFIG_HRES_14;
	}
	writeConfig(config);
}

float Adafruit_HDC1000::readTemperature(void) {
	float temp;
	switch(_type){
	case HDC1008:
		temp = (read32(HDC1008_TEMP, 20) >> 16);
	case HDC1010:
		temp = (read32(HDC1010_TEMP, 20) >> 16);
	case HDC1080:
		temp = (read32(HDC1080_TEMP, 20) >> 16);
	default:
		temp = (read32(HDC1000_TEMP, 20) >> 16);
	}
	temp /= 65536;
	temp *= 165;
	temp -= 40;

	return temp;
}

float Adafruit_HDC1000::readHumidity(void) {
	float hum;
	switch(_type){
	case HDC1008:
		hum = (read32(HDC1008_TEMP, 20) & 0xFFFF);
	case HDC1010:
		hum = (read32(HDC1010_TEMP, 20) & 0xFFFF);
	case HDC1080:
		hum = (read32(HDC1080_TEMP, 20) & 0xFFFF);
	default:
		hum = (read32(HDC1000_TEMP, 20) & 0xFFFF);
	}
	hum /= 65536;
	hum *= 100;

	return hum;
}

void Adafruit_HDC1000::drySensor(void)
{
	uint16_t origConfig = read16(0x2);
	// reset, heat up, and select 14 bit temp & humidity
	uint16_t newConfig;
	switch(_type){
	case HDC1008:
		newConfig =  HDC1008_CONFIG_RST | HDC1008_CONFIG_HEAT | HDC1008_CONFIG_MODE | HDC1008_CONFIG_TRES_14 | HDC1008_CONFIG_HRES_14;
	case HDC1010:
		newConfig =  HDC1010_CONFIG_RST | HDC1010_CONFIG_HEAT | HDC1010_CONFIG_MODE | HDC1010_CONFIG_TRES_14 | HDC1010_CONFIG_HRES_14;
	case HDC1080:
		newConfig =  HDC1080_CONFIG_RST | HDC1080_CONFIG_HEAT | HDC1080_CONFIG_MODE | HDC1080_CONFIG_TRES_14 | HDC1080_CONFIG_HRES_14;
	default:
		newConfig =  HDC1000_CONFIG_RST | HDC1000_CONFIG_HEAT | HDC1000_CONFIG_MODE | HDC1000_CONFIG_TRES_14 | HDC1000_CONFIG_HRES_14;
	}

	writeConfig(newConfig);

	delay(15);

	// take 1000 readings & toss
	for ( int i = 0; i < 1000; i++)  {
		switch(_type){
		case HDC1008:
			read32(HDC1008_TEMP, 20);
		case HDC1010:
			read32(HDC1010_TEMP, 20);
		case HDC1080:
			read32(HDC1080_TEMP, 20);
		default:
			read32(HDC1000_TEMP, 20);
		}
		delay(1);
	}

	switch(_type){
	case HDC1008:
		origConfig |= HDC1008_CONFIG_RST;
	case HDC1010:
		origConfig |= HDC1010_CONFIG_RST;
	case HDC1080:
		origConfig |= HDC1080_CONFIG_RST;
	default:
		origConfig |= HDC1000_CONFIG_RST;
	}
	writeConfig(origConfig);
	delay(15);
}

void Adafruit_HDC1000::writeConfig(uint16_t config) {
	_i2c_if->beginTransmission(_i2caddr);
	_i2c_if->beginTransmission(0x02);
	_i2c_if->write(config>>8);
	_i2c_if->write(config&0xFF);
	_i2c_if->endTransmission();
	delay(15);
}

/*********************************************************************/

uint16_t Adafruit_HDC1000::read16(uint8_t a, uint8_t d) {
	_i2c_if->beginTransmission(_i2caddr);
	_i2c_if->write(a);
	_i2c_if->endTransmission();
	delay(d);
	_i2c_if->requestFrom((uint8_t)_i2caddr, (uint8_t)2);
	uint16_t r = _i2c_if->read();
	r <<= 8;
	r |= _i2c_if->read();
	//Serial.println(r, HEX);
	return r;
}

uint32_t Adafruit_HDC1000::read32(uint8_t a, uint8_t d) {
	_i2c_if->beginTransmission(_i2caddr);
	_i2c_if->write(a);
	_i2c_if->endTransmission();
	delay(50);
	_i2c_if->requestFrom((uint8_t)_i2caddr, (uint8_t)4);
	uint32_t r = _i2c_if->read();
	r <<= 8;
	r |= _i2c_if->read();
	r <<= 8;
	r |= _i2c_if->read();
	r <<= 8;
	r |= _i2c_if->read();
	//Serial.println(r, HEX);
	return r;
}
