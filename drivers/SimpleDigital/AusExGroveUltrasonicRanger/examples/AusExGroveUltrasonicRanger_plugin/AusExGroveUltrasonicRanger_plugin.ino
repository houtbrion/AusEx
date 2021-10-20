#include "AusExOutputPlugin.h"
#include "AusExGroveUltrasonicRanger.h"

#define SENSOR_PIN 3

AusExGroveUltrasonicRanger ultraSonicRanger = AusExGroveUltrasonicRanger(SENSOR_PIN);
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
  ultraSonicRanger.begin();
  sensor_t sensor;
  ultraSonicRanger.getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
}
void loop()  
{
  sensors_event_t event;
  if (ultraSonicRanger.getEvent(&event)) {
    outputDevice.EventOutput(event);
  } else {
    Serial.println("read sensor error.");
  }
  delay(3000);
}
