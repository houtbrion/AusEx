#include "AusExGroveRotaryAngleSensor.h"

#define SENSOR_PIN A0

AusExGroveRotaryAngleSensor groveRotaryAngleSensor = AusExGroveRotaryAngleSensor(SENSOR_PIN, (float)5.0);

void setup()  
{
  Serial.begin(9600);
  groveRotaryAngleSensor.begin();
  sensor_t sensor;
  groveRotaryAngleSensor.getSensor(&sensor);
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
  if (groveRotaryAngleSensor.getEvent(&event)) {
    Serial.print("sensor value = "); Serial.println(event.angle);
  } else {
    Serial.println("read sensor error.");
  }
  delay(3000);
}
