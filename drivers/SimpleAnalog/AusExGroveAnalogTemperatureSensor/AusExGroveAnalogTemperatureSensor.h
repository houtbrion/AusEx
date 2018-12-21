
#ifndef __AUEX_GROVE_ANALOG_TEMPERATURE_SENSOR_H__
#define __AUEX_GROVE_ANALOG_TEMPERATURE_SENSOR_H__

#include <AusEx.h>

#include <math.h>



#define THERMISTOR_B 3975 // B value of the thermistor
#define RESISTOR_R0 100000 // Resistor R0 = 100k
#define DEFAULT_PIN A0
#define SENSOR_VERSION 1

#define _SENSOR_MIN_VALUE -40
#define _SENSOR_MAX_VALUE 125
#define _SENSOR_RESOLUTION 0.038
#define _SENSOR_MIN_DELAY 0

class Grove_Analog_Temperature_Sensor_AusEx : public Adafruit_SensorEx
{
  public:
    Grove_Analog_Temperature_Sensor_AusEx(int32_t sensorID = -1);
    Grove_Analog_Temperature_Sensor_AusEx(int analogPin, int32_t sensorID = -1);

    bool begin(void);
    bool getEvent(sensors_event_t*);
    void getSensor(sensor_t*);
    bool enableAutoRange(bool enabled);
    int setMode(int mode);
  private:
    int32_t _sensorID;
    int _pin_number;
};

#endif /* __AUEX_GROVE_ANALOG_TEMPERATURE_SENSOR_H__ */
