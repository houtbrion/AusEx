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
#ifndef ADAFRUIT_HDC1000_H
#define ADAFRUIT_HDC1000_H

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include "Wire.h"

/*
 * 機種の種別
 */
#define HDC1000 1000
#define HDC1008 1008
#define HDC1010 1010
#define HDC1080 1080
#define HDC2010 2010

/*
 * HDC1000の定義
 */
#define HDC1000_I2CADDR       0x40
#define HDC1000_TEMP          0x00
#define HDC1000_HUMID         0x01
#define HDC1000_CONFIG        0x02
#define HDC1000_CONFIG_RST    (1 << 15)
#define HDC1000_CONFIG_HEAT   (1 << 13)
#define HDC1000_CONFIG_MODE   (1 << 12)
#define HDC1000_CONFIG_BATT   (1 << 11)
#define HDC1000_CONFIG_TRES_14  0
#define HDC1000_CONFIG_TRES_11  (1 << 10)
#define HDC1000_CONFIG_HRES_14  0
#define HDC1000_CONFIG_HRES_11  (1 << 8)
#define HDC1000_CONFIG_HRES_8   (1 << 9)

#define HDC1000_SERIAL1       0xFB
#define HDC1000_SERIAL2       0xFC
#define HDC1000_SERIAL3       0xFD
#define HDC1000_MANUFID_REG   0xFE
#define HDC1000_DEVICEID_REG  0xFF
#define HDC1000_MANUFID       0x5449
#define HDC1000_DEVICEID      0x1000


/*
 * HDC1008の定義
 */
#define HDC1008_I2CADDR        HDC1000_I2CADDR
#define HDC1008_TEMP           HDC1000_TEMP
#define HDC1008_HUMID          HDC1000_HUMID
#define HDC1008_CONFIG         HDC1000_CONFIG
#define HDC1008_CONFIG_RST     HDC1000_CONFIG_RST
#define HDC1008_CONFIG_HEAT    HDC1000_CONFIG_HEAT
#define HDC1008_CONFIG_MODE    HDC1000_CONFIG_MODE
#define HDC1008_CONFIG_BATT    HDC1000_CONFIG_BATT
#define HDC1008_CONFIG_TRES_14 HDC1000_CONFIG_TRES_14
#define HDC1008_CONFIG_TRES_11 HDC1000_CONFIG_TRES_11
#define HDC1008_CONFIG_HRES_14 HDC1000_CONFIG_HRES_14
#define HDC1008_CONFIG_HRES_11 HDC1000_CONFIG_HRES_11
#define HDC1008_CONFIG_HRES_8  HDC1000_CONFIG_HRES_8

#define HDC1008_SERIAL1        HDC1000_SERIAL1
#define HDC1008_SERIAL2        HDC1000_SERIAL2
#define HDC1008_SERIAL3        HDC1000_SERIAL3
#define HDC1008_MANUFID_REG    HDC1000_MANUFID_REG
#define HDC1008_DEVICEID_REG   HDC1000_DEVICEID_REG
#define HDC1008_MANUFID        HDC1000_MANUFID
#define HDC1008_DEVICEID       HDC1000_DEVICEID

/*
 * HDC1010の定義
 */
#define HDC1010_I2CADDR        HDC1000_I2CADDR
#define HDC1010_TEMP           HDC1000_TEMP
#define HDC1010_HUMID          HDC1000_HUMID
#define HDC1010_CONFIG         HDC1000_CONFIG
#define HDC1010_CONFIG_RST     HDC1000_CONFIG_RST
#define HDC1010_CONFIG_HEAT    HDC1000_CONFIG_HEAT
#define HDC1010_CONFIG_MODE    HDC1000_CONFIG_MODE
#define HDC1010_CONFIG_BATT    HDC1000_CONFIG_BATT
#define HDC1010_CONFIG_TRES_14 HDC1000_CONFIG_TRES_14
#define HDC1010_CONFIG_TRES_11 HDC1000_CONFIG_TRES_11
#define HDC1010_CONFIG_HRES_14 HDC1000_CONFIG_HRES_14
#define HDC1010_CONFIG_HRES_11 HDC1000_CONFIG_HRES_11
#define HDC1010_CONFIG_HRES_8  HDC1000_CONFIG_HRES_8

#define HDC1010_SERIAL1        HDC1000_SERIAL1
#define HDC1010_SERIAL2        HDC1000_SERIAL2
#define HDC1010_SERIAL3        HDC1000_SERIAL3
#define HDC1010_MANUFID_REG    HDC1000_MANUFID_REG
#define HDC1010_DEVICEID_REG   HDC1000_DEVICEID_REG
#define HDC1010_MANUFID        HDC1000_MANUFID
#define HDC1010_DEVICEID       HDC1000_DEVICEID


/*
 * HDC1080の定義
 */
#define HDC1080_I2CADDR        HDC1000_I2CADDR
#define HDC1080_TEMP           HDC1000_TEMP
#define HDC1080_HUMID          HDC1000_HUMID
#define HDC1080_CONFIG         HDC1000_CONFIG
#define HDC1080_CONFIG_RST     HDC1000_CONFIG_RST
#define HDC1080_CONFIG_HEAT    HDC1000_CONFIG_HEAT
#define HDC1080_CONFIG_MODE    HDC1000_CONFIG_MODE
#define HDC1080_CONFIG_BATT    HDC1000_CONFIG_BATT
#define HDC1080_CONFIG_TRES_14 HDC1000_CONFIG_TRES_14
#define HDC1080_CONFIG_TRES_11 HDC1000_CONFIG_TRES_11
#define HDC1080_CONFIG_HRES_14 HDC1000_CONFIG_HRES_14
#define HDC1080_CONFIG_HRES_11 HDC1000_CONFIG_HRES_11
#define HDC1080_CONFIG_HRES_8  HDC1000_CONFIG_HRES_8

#define HDC1080_SERIAL1        HDC1000_SERIAL1
#define HDC1080_SERIAL2        HDC1000_SERIAL2
#define HDC1080_SERIAL3        HDC1000_SERIAL3
#define HDC1080_MANUFID_REG    HDC1000_MANUFID_REG
#define HDC1080_DEVICEID_REG   HDC1000_DEVICEID_REG
#define HDC1080_MANUFID        HDC1000_MANUFID
#define HDC1080_DEVICEID       0x1050


class Adafruit_HDC1000 {
public:
	Adafruit_HDC1000();
	//Adafruit_HDC1000(uint8_t type);
	//Adafruit_HDC1000(uint8_t type, uint32_t addr);
	Adafruit_HDC1000(uint32_t type, uint8_t addr);
	//boolean begin();
	//boolean begin(TwoWire *theWire, uint8_t addr = HDC1000_I2CADDR);
	boolean begin(TwoWire *theWire,uint32_t type=HDC1000, uint8_t addr = HDC1000_I2CADDR);
	float readTemperature(void);
	float readHumidity(void);
	void reset(void);
	void drySensor(void);

	uint16_t read16(uint8_t addr, uint8_t d=0);
	uint32_t read32(uint8_t addr, uint8_t d=0);
	void writeConfig(uint16_t config);

private:
	boolean readData(void);
	boolean setup(void);
	float humidity, temp;
	//uint32_t _i2caddr;
	uint8_t _i2caddr;
	//uint8_t _type;
	uint32_t _type;
	TwoWire * _i2c_if;
};

#endif /* ADAFRUIT_HDC1000_H */
