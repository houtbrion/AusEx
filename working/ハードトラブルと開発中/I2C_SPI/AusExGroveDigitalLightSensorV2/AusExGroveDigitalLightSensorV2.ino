#include "AusExGroveDigitalLightSensorV2.h"


GroveDigitalLightSensorV2AusEx groveI2cDigitalSensor;

void setup()  
{
  Serial.begin(9600);
  groveI2cDigitalSensor.begin();
  sensor_t sensor;
  groveI2cDigitalSensor.getSensor(&sensor);
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
  if (groveI2cDigitalSensor.getEvent(&event)) {
    Serial.print("sensor value = "); Serial.println(event._SENSOR_RETURN_VALUE);
  } else {
    Serial.println("read sensor error.");
  }
  delay(3000);
}
