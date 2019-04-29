#include "AusExSerialTemplate.h"

SoftwareSerial sSerial(2,3);
AUSEX_SERIAL_TEMPLATE_CLASS serialSensor(&sSerial);


void setup()  
{
  Serial.begin(9600);
  serialSensor.begin(9600);
  sensor_t sensor;
  serialSensor.getSensor(&sensor);
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
  if (serialSensor.getEvent(&event)) {
    Serial.print("sensor value = "); Serial.println(event.AUSEX_SERIAL_TEMPLATE_SENSOR_RETURN_VALUE);
  } else {
    Serial.println("read sensor error.");
  }
  delay(3000);
}
