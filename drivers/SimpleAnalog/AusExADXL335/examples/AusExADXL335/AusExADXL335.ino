#include "AusExADXL335.h"

#define PIN_X A0  // センサはアナログの0から3番ポートに接続
#define PIN_Y A1
#define PIN_Z A2

AUSEX_ADXL335_CLASS adxl335 = AUSEX_ADXL335_CLASS(PIN_X,PIN_Y,PIN_Z,5.0, AUSEX_ADXL335_ZERO_X, AUSEX_ADXL335_ZERO_Y, AUSEX_ADXL335_ZERO_Z, AUSEX_ADXL335_SENSITIVITY, 12345);


void printAccel(sensors_event_t * event){
  Serial.print("X : ");Serial.println(event->acceleration.x);
  Serial.print("Y : ");Serial.println(event->acceleration.y);
  Serial.print("Z : ");Serial.println(event->acceleration.z);
}

void setup()
{
  Serial.begin(9600);
  adxl335.begin();
  sensor_t sensor;
  adxl335.getSensor(&sensor);
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
  if (adxl335.getEvent(&event)) {
    printAccel(&event);
  } else {
    Serial.println("read sensor error.");
  }
  delay(3000);
}
