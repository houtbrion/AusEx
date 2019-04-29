
#ifndef __AUSEX_GROVE_ANALOG_TEMPERATURE_SENSOR_H__
#define __AUSEX_GROVE_ANALOG_TEMPERATURE_SENSOR_H__


#define AUSEX_GROVE_ANALOG_TEMPERATURE_CLASS AusExGroveAnalog1Temperature
#define AUSEX_GROVE_ANALOG_TEMPERATURE_SENSOR_NAME "AusExGroveAnalog1Temperature"
#define AUSEX_GROVE_ANALOG_TEMPERATURE_SENSOR_TYPE SENSOR_TYPE_AMBIENT_TEMPERATURE
#define AUSEX_GROVE_ANALOG_TEMPERATURE_SENSOR_LIBRARY_VERSION 1
#define AUSEX_GROVE_ANALOG_TEMPERATURE_SENSOR_RETURN_VALUE temperature
#define AUSEX_GROVE_ANALOG_TEMPERATURE_SENSOR_VALUE_TYPE float
#define AUSEX_GROVE_ANALOG_TEMPERATURE_SENSOR_DEFAULT_VDD 5
#define AUSEX_GROVE_ANALOG_TEMPERATURE_SENSOR_MIN_VALUE -40
#define AUSEX_GROVE_ANALOG_TEMPERATURE_SENSOR_MAX_VALUE 125
#define AUSEX_GROVE_ANALOG_TEMPERATURE_SENSOR_RESOLUTION 0.038
#define AUSEX_GROVE_ANALOG_TEMPERATURE_SENSOR_MIN_DELAY 0

#include <AusEx.h>
#include <math.h>

#define THERMISTOR_B 3975 // B value of the thermistor
#define RESISTOR_R0 100000 // Resistor R0 = 100k

class AUSEX_GROVE_ANALOG_TEMPERATURE_CLASS : public Adafruit_SensorEx
{
  public:
    AUSEX_GROVE_ANALOG_TEMPERATURE_CLASS(int analogPin, int32_t sensorID = -1);

    bool begin(void);
    bool getEvent(sensors_event_t*);
    void getSensor(sensor_t*);
    bool enableAutoRange(bool enabled);
    int setMode(int mode);
    int getMode(void);
  private:
    int32_t _sensorID;
    int _pin_number;
};

#endif /* __AUSEX_GROVE_ANALOG_TEMPERATURE_SENSOR_H__ */
