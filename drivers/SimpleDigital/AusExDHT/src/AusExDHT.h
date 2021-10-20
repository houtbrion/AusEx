#ifndef __AUSEX_DHT_H__
#define __AUSEX_DHT_H__

#define NO_MEASURE NAN

#define AUSEX_DHT_CLASS AusExDHT
#define AUSEX_DHT_SENSOR_LIBRARY_VERSION 1

// Define types of sensors.
#define DHT11 11
#define DHT12 12
#define DHT22 22
#define DHT21 21
#define AM2301 21

#define DHT_TIMEOUT -1

#include "AusEx.h"


class AusExDHT {
public:
  AusExDHT(int pin, uint8_t type, int32_t tempSensorId=-1, int32_t humiditySensorId=-1);
  bool begin(bool pullUp=true);


  class Temperature : public Adafruit_SensorEx {
  public:
    Temperature(AusExDHT* parent, int32_t id);
    bool getEvent(sensors_event_t* event);
    void getSensor(sensor_t* sensor);
    bool enableAutoRange(bool);
    int setMode(int);
    int getMode();
  private:
    AusExDHT* _parent;
    int32_t _id;
  };
  class Humidity : public Adafruit_SensorEx {
  public:
    Humidity(AusExDHT* parent, int32_t id);
    bool getEvent(sensors_event_t* event);
    void getSensor(sensor_t* sensor);
    bool enableAutoRange(bool);
    int setMode(int);
    int getMode();
  private:
    AusExDHT* _parent;
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
  int _pin;
  uint8_t _type;
  #ifdef __AVR
    // Use direct GPIO access on an 8-bit AVR so keep track of the port and bitmask
    // for the digital pin connected to the DHT.  Other platforms will use digitalRead.
    uint8_t _bit, _port;
  #endif
  uint8_t data[5];
  unsigned long lastTime;
  float oldTemperature;
  float oldHumidity;
  int32_t measure_delay;
  uint32_t _maxcycles;
  uint8_t pullTime; // Time (in usec) to pull up data line before reading
  Temperature _temp;
  Humidity _humidity;
  void setName(sensor_t* );
  int32_t getMinDelay(uint8_t);
  bool getTemperature(sensors_event_t*);
  bool getHumidity(sensors_event_t*);
  bool measure(void);
  bool readDHT(void);
  uint32_t expectPulse(bool level);
  float dataToTemperature(void);
  float dataToHumidity(void);
};

class AusExDhtInterruptLock {
  public:
   AusExDhtInterruptLock() {
#if !defined(ARDUINO_ARCH_NRF52)  
    noInterrupts();
#endif
   }
   ~AusExDhtInterruptLock() {
#if !defined(ARDUINO_ARCH_NRF52)  
    interrupts();
#endif
   }
};

#endif /* __AUSEX_DHT_H__ */
