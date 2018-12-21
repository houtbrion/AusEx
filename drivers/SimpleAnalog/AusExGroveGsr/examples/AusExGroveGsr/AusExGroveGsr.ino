#include "AusExGroveGsr.h"

#define SENSOR_PIN A0

GroveGsrAusEx groveGsrSensor = GroveGsrAusEx(SENSOR_PIN);

void setup()  
{
  delay(3000);
  Serial.begin(9600);
  groveGsrSensor.begin();
  sensor_t sensor;
  groveGsrSensor.getSensor(&sensor);
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
  if (groveGsrSensor.getEvent(&event)) {
    Serial.print("sensor value = "); Serial.println(event.value);
  } else {
    Serial.println("read sensor error.");
  }
  delay(3000);
}
