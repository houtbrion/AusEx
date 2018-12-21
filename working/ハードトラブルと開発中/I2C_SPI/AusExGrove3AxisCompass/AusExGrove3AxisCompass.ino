#include "AusExGrove3AxisCompass.h"


Grove3AxisCompassAusEx compass;

void setup()  
{
  Serial.begin(9600);

  if (!compass.begin()) {
    Serial.println("fail to start sensor");
    while (1){
      
    }
  }
  sensor_t sensor;
  compass.getSensor(&sensor);
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
  if (compass.getEvent(&event)) {
    Serial.print("sensor value x = "); Serial.println(event.magnetic.x);
    Serial.print("sensor value y = "); Serial.println(event.magnetic.y);
    Serial.print("sensor value z = "); Serial.println(event.magnetic.z);
  } else {
    Serial.println("read sensor error.");
  }
  delay(3000);
}
