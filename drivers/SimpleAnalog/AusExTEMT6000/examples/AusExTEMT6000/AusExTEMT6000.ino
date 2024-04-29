#include "AusExTEMT6000.h"

#define SENSOR_PIN A2  // センサはアナログの3番ポートに接続

AusExTEMT6000 temt6000 = AusExTEMT6000(SENSOR_PIN);

void setup()  
{
  Serial.begin(9600);
  while (!Serial) {
    ; // シリアルポートの準備ができるのを待つ(Leonardoのみ必要)
  }
  temt6000.begin();
  sensor_t sensor;
  temt6000.getSensor(&sensor);
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
  if (temt6000.getEvent(&event)) {
    Serial.print("sensor value = "); Serial.println(event.AUSEX_TEMT6000_SENSOR_RETURN_VALUE);
  } else {
    Serial.println("read sensor error.");
  }
  delay(3000);
}
