#include "AusExOutputPlugin.h"
#include "AusExTEMT6000.h"

#define SENSOR_PIN A2  // センサはアナログの3番ポートに接続

AusExTEMT6000 temt6000 = AusExTEMT6000(SENSOR_PIN);
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

  temt6000.begin();
  sensor_t sensor;
  temt6000.getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
}
void loop()  
{
  sensors_event_t event;
  if (temt6000.getEvent(&event)) {
    outputDevice.EventOutput(event);
  } else {
    Serial.println("read sensor error.");
  }
  delay(3000);
}
