#include "AusExLSP22HB.h"


AusExLSP22HB ausExLSP22HB=AusExLSP22HB(&Wire);

void setup()  
{
  Serial.begin(9600);
  ausExLSP22HB.begin();
  sensor_t sensor;
  ausExLSP22HB.getSensor(&sensor);
  Serial.println("---------------");
  Serial.print("Sensor name    :") ; Serial.println(sensor.name);
  Serial.print("Driver version : "); Serial.println(sensor.version);
  Serial.print("sensor ID      : "); Serial.println(sensor.sensor_id);
  Serial.print("Max Value:    "); Serial.println(sensor.max_value);
  Serial.print("Min Value:    "); Serial.println(sensor.min_value);
  Serial.print("Resolution:   "); Serial.println(sensor.resolution);
  Serial.println("---------------");
  Serial.print("set sensor mode to Kpa....");
  if (0!=ausExLSP22HB.setMode(AUSEX_LPS22HB_MODE_KPA)) {
    Serial.println("Fail.");
  } else {
    Serial.println("Success.");
  }
}
void loop()  
{
  sensors_event_t event;
  if (ausExLSP22HB.getEvent(&event)) {
    Serial.print("air pressure = "); Serial.print(event.pressure); Serial.println("Kpa.");
  } else {
    Serial.println("read sensor error.");
  }
  delay(3000);
}
