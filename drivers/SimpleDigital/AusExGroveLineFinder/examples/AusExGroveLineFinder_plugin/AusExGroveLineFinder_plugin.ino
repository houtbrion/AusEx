#include "AusExOutputPlugin.h"
#include "AusExGroveLineFinder.h"

#define SENSOR_PIN 4  // センサはデジタルの2番ポートに接続

AUSEX_GROVE_LINE_FINDER_CLASS digitalSensor = AUSEX_GROVE_LINE_FINDER_CLASS(SENSOR_PIN);
OutputChannel channel;
AuxExSensorIO outputDevice =  AuxExSensorIO();

void setup()
{
  Serial.begin(9600);
  while (!Serial) {
    ; // シリアルポートの準備ができるのを待つ(Leonardoのみ必要)
  }
  channel.serial= &Serial;
  outputDevice.SetIO(AUSEX_OUTPUT_CHANNEL_SERIAL, channel, FORMAT_TYPE_PLAIN_TEXT);
  //
  digitalSensor.begin();
  sensor_t sensor;
  digitalSensor.getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
}
void loop()  
{
  sensors_event_t event;
  if (digitalSensor.getEvent(&event)) {
    outputDevice.EventOutput(event);
  } else {
    Serial.println("read sensor error.");
  }
  delay(3000);
}
