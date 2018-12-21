#include "AusExGrove3AxisDigitalGyro.h"


Grove3AxisDigitalGyroAusEx groveDigitalGyro;

void setup()  
{
  Serial.begin(9600);
  groveDigitalGyro.begin();
  sensor_t sensor;
  groveDigitalGyro.getSensor(&sensor);
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
  if (groveDigitalGyro.getEvent(&event)) {
    Serial.print("sensor value x = "); Serial.println(event.gyro.x);
    Serial.print("sensor value y = "); Serial.println(event.gyro.y);
    Serial.print("sensor value z = "); Serial.println(event.gyro.z);
  } else {
    Serial.println("read sensor error.");
  }
  delay(3000);
}
