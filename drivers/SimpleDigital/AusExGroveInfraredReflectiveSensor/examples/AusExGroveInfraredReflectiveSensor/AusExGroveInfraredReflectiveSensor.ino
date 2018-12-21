#include "AusExGroveInfraredReflectiveSensor.h"

#define SENSOR_PIN 2

GroveInfraredReflectiveSensorAusEx analogSensor = GroveInfraredReflectiveSensorAusEx(SENSOR_PIN);

void setup()  
{
  Serial.begin(9600);
  delay(3000);
  analogSensor.begin();
  sensor_t sensor;
  analogSensor.getSensor(&sensor);
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
  if (analogSensor.getEvent(&event)) {
    Serial.print("sensor value = "); Serial.println(event.value);
  } else {
    Serial.println("read sensor error.");
  }
  delay(3000);
}
