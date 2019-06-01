#include "AusExGroveTemperatureSensor.h"

#define SENSOR_PIN A1  // センサはアナログの3番ポートに接続

AUSEX_TEMPERATURE_CLASS generalAnalogSensor = AUSEX_TEMPERATURE_CLASS(SENSOR_PIN);

void setup()  
{
  Serial.begin(9600);
  generalAnalogSensor.begin();
  sensor_t sensor;
  generalAnalogSensor.getSensor(&sensor);
  Serial.println("---------------");
  Serial.print("Sensor name    :") ; Serial.println(sensor.name);
  Serial.print("Driver version : "); Serial.println(sensor.version);
  Serial.print("sensor ID      : "); Serial.println(sensor.sensor_id);
  Serial.print("Max Value:    "); Serial.println(sensor.max_value);
  Serial.print("Min Value:    "); Serial.println(sensor.min_value);
  Serial.print("Resolution:   "); Serial.println(sensor.resolution);
  Serial.println("---------------");
}
void loop()  
{
  sensors_event_t event;
  if (generalAnalogSensor.getEvent(&event)) {
    Serial.print("sensor value = "); Serial.println(event.AUSEX_GROVE_TEMPERATURE_SENSOR_RETURN_VALUE);
  } else {
    Serial.println("read sensor error.");
  }
  delay(3000);
}
