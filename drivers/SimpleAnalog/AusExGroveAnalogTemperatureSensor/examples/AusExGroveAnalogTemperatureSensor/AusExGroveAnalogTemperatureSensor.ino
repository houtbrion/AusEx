//  Grove - Temperature Sensor V1.1/1.2用 サンプルプログラム

#include "AusExGroveAnalogTemperatureSensor.h"

#ifndef ESP32
Grove_Analog_Temperature_Sensor_AusEx groveTemperatureSensor=Grove_Analog_Temperature_Sensor_AusEx(A0);
#else
Grove_Analog_Temperature_Sensor_AusEx groveTemperatureSensor=Grove_Analog_Temperature_Sensor_AusEx(A0,-1);
#endif /* ESP32 */

void setup()
{
#ifndef ESP8266
  while (!Serial); // for Leonardo/Micro/Zero
#endif
  Serial.begin(9600);
  Serial.println("Temperature sensor Test"); Serial.println("");
  if (!groveTemperatureSensor.begin()){
    Serial.println("Sensor error in begin()");
    while(1);
  }
  sensor_t sensor;
  groveTemperatureSensor.getSensor(&sensor);
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
  groveTemperatureSensor.getEvent(&event);
  Serial.print("temperature = ");
  Serial.println(event.temperature);
  delay(3000);
}
