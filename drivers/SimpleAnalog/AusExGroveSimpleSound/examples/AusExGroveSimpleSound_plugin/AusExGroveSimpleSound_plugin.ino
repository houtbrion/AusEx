#include "AusExOutputPlugin.h"
#include "AusExGroveSimpleSound.h"

#define SENSOR_PIN A0

GroveSimpleSoundAusEx groveSimpleSoundSensor = GroveSimpleSoundAusEx(SENSOR_PIN);
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
  groveSimpleSoundSensor.begin();
  sensor_t sensor;
  groveSimpleSoundSensor.getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
}
void loop()  
{
  sensors_event_t event;
  if (groveSimpleSoundSensor.getEvent(&event)) {
    outputDevice.EventOutput(event);
  } else {
    Serial.println("read sensor error.");
  }
  delay(3000);
}
