#include "AusExDallasTemperature.h"

#define SENSOR_PIN 4  // センサはデジタルの2番ポートに接続

AUSEX_DALLAS_TEMPERATURE_CLASS digitalSensor = AUSEX_DALLAS_TEMPERATURE_CLASS(SENSOR_PIN);

void setup()  
{
  Serial.begin(9600);
  while (!Serial) {
    ; // シリアルポートが開くのを待つ。Leonardoでだけ必要。
  }
  digitalSensor.begin();
  sensor_t sensor;
  digitalSensor.getSensor(&sensor);
  Serial.println("---------------");
  Serial.print("Sensor name    :") ; Serial.println(sensor.name);
  Serial.print("Driver version : "); Serial.println(sensor.version);
  Serial.print("sensor ID      : "); Serial.println(sensor.sensor_id);
  Serial.print("Max Value:    "); Serial.println(sensor.max_value);
  Serial.print("Min Value:    "); Serial.println(sensor.min_value);
  Serial.print("Resolution:   "); Serial.println(sensor.resolution);
  Serial.println("---------------");
  delay(sensor.init_delay);
}
void loop()  
{
  sensors_event_t event;
  if (digitalSensor.getEvent(&event)) {
    Serial.print("sensor value = "); Serial.println(event.AUSEX_DALLAS_TEMPERATURE_SENSOR_RETURN_VALUE);
  } else {
    Serial.println("read sensor error.");
  }
  delay(3000);
}
