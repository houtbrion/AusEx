
/*

 チップ名 |     温度 (C)       |        湿度 (%)    |
          +------+------+------+------+------+------+
          | 最低 | 最高 | 精度 | 最低 | 最高 | 精度 |
 ---------+------+------+------+------+------+------+
  HDC1000 |  -40 |  125 |  0.2 |   0  |  100 |    3 |
  HDC1008 |  -40 |  125 |  0.2 |   0  |  100 |    4 |
  HDC1010 |  -40 |  125 |  0.2 |   0  |  100 |    2 |
  HDC1080 |  -40 |  125 |  0.2 |   0  |  100 |    2 |
  HDC2010 |  -40 |  125 |  0.2 |   0  |  100 |    2 |


 */


#ifndef __AUSEX_ HDC10XX__
#define __AUSEX_ HDC10XX__

#include <AusEx.h>
#include <Adafruit_HDC1000.h>


#define HDC1000U_DRIVER_VERSION 1

#define HDC10XX_NAME "HDC10XX"
#define HDC1000_NAME "HDC1000"
#define HDC1008_NAME "HDC1008"
#define HDC1010_NAME "HDC1010"
#define HDC1080_NAME "HDC1080"
#define HDC2010_NAME "HDC2010"
#define HDC1000_MIN_DELAY 0
#define HDC1008_MIN_DELAY 0
#define HDC1010_MIN_DELAY 0
#define HDC1080_MIN_DELAY 0
#define HDC2010_MIN_DELAY 0

#define HDC1000_TEMPERATURE_MAX_VALUE 125.0F
#define HDC1008_TEMPERATURE_MAX_VALUE 125.0F
#define HDC1010_TEMPERATURE_MAX_VALUE 125.0F
#define HDC1080_TEMPERATURE_MAX_VALUE 125.0F
#define HDC2010_TEMPERATURE_MAX_VALUE 125.0F

#define HDC1000_TEMPERATURE_MIN_VALUE -40.0F
#define HDC1008_TEMPERATURE_MIN_VALUE -40.0F
#define HDC1010_TEMPERATURE_MIN_VALUE -40.0F
#define HDC1080_TEMPERATURE_MIN_VALUE -40.0F
#define HDC2010_TEMPERATURE_MIN_VALUE -40.0F

#define HDC1000_TEMPERATURE_RESOLUTION 0.2F
#define HDC1008_TEMPERATURE_RESOLUTION 0.2F
#define HDC1010_TEMPERATURE_RESOLUTION 0.2F
#define HDC1080_TEMPERATURE_RESOLUTION 0.2F
#define HDC2010_TEMPERATURE_RESOLUTION 0.2F

#define HDC1000_HUMIDITY_MAX_VALUE 100.0F
#define HDC1008_HUMIDITY_MAX_VALUE 100.0F
#define HDC1010_HUMIDITY_MAX_VALUE 100.0F
#define HDC1080_HUMIDITY_MAX_VALUE 100.0F
#define HDC2010_HUMIDITY_MAX_VALUE 100.0F

#define HDC1000_HUMIDITY_MIN_VALUE 0.0F
#define HDC1008_HUMIDITY_MIN_VALUE 0.0F
#define HDC1010_HUMIDITY_MIN_VALUE 0.0F
#define HDC1080_HUMIDITY_MIN_VALUE 0.0F
#define HDC2010_HUMIDITY_MIN_VALUE 0.0F

#define HDC1000_HUMIDITY_RESOLUTION 3.0F
#define HDC1008_HUMIDITY_RESOLUTION 4.0F
#define HDC1010_HUMIDITY_RESOLUTION 2.0F
#define HDC1080_HUMIDITY_RESOLUTION 2.0F
#define HDC2010_HUMIDITY_RESOLUTION 2.0F

class AusExHDC10XX {
public:
	AusExHDC10XX(TwoWire *theWire, uint32_t type=HDC1000 , int32_t tempSensorId=-1, int32_t humiditySensorId=-1);
  	boolean begin(uint32_t addr=HDC1000_I2CADDR);

	class Temperature : public Adafruit_SensorEx {
	public:
		Temperature(AusExHDC10XX * parent, int32_t id);
		bool getEvent(sensors_event_t * event);
		void getSensor(sensor_t * sensor);
		bool enableAutoRange(bool);
		int setMode(int);
		int getMode();
	private:
		AusExHDC10XX * _parent;
		int32_t _id;

	};

	class Humidity : public Adafruit_SensorEx {
	public:
		Humidity(AusExHDC10XX * parent, int32_t id);
		bool getEvent(sensors_event_t * event);
		void getSensor(sensor_t * sensor);
		bool enableAutoRange(bool);
		int setMode(int);
		int getMode();
	private:
		AusExHDC10XX * _parent;
		int32_t _id;
	};

	Temperature temperature() {
		return _temp;
	}

	Humidity humidity() {
		return _humidity;
	}

	int setMode(int);
	int getMode();
	bool enableAutoRange(bool);

private:
	uint32_t _type;
	TwoWire * _i2c_if;
	uint8_t _i2c_addr;
	unsigned long lastTime;
	float oldTemperature;
	float oldHumidity;
	Temperature _temp;
	Humidity _humidity;
	Adafruit_HDC1000 _hdc;

	void setName(sensor_t * sensor);
	void setMinDelay(sensor_t * sensor);
};

#endif /* __AUSEX_ HDC10XX__ */
