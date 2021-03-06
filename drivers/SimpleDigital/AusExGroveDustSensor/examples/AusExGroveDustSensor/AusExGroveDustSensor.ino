#include "AusExGroveDustSensor.h"

#define SENSOR_PIN 4

AusExGroveDustSensor dustSensor = AusExGroveDustSensor(SENSOR_PIN);

void setup()  
{
  Serial.begin(9600);
  dustSensor.begin();
  sensor_t sensor;
  dustSensor.getSensor(&sensor);
  Serial.println("---------------");
  Serial.print("Sensor name    :") ; Serial.println(sensor.name);
  Serial.print("Driver version : "); Serial.println(sensor.version);
  Serial.print("sensor ID      : "); Serial.println(sensor.sensor_id);
  Serial.print("Max Value:    "); Serial.println(sensor.max_value);
  Serial.print("Min Value:    "); Serial.println(sensor.min_value);
  Serial.print("Resolution:   "); Serial.println(sensor.resolution);
  Serial.print("Delay :       "); Serial.println(sensor.min_delay);
  Serial.print("Init Delay :  "); Serial.println(sensor.init_delay);
  Serial.println("---------------");
  Serial.print("Please wait until ");Serial.print(sensor.init_delay);Serial.println(" micro secs for sensor stability");
}

void loop()  
{
  sensors_event_t event;
  if (dustSensor.getEvent(&event)) {
    Serial.print("measure time = "); Serial.print(event.timestamp);
    Serial.print(" , sensor value = "); Serial.println(event.dust);
  } else {
    Serial.println("read sensor error.");
  }
  delay(3000);
}
