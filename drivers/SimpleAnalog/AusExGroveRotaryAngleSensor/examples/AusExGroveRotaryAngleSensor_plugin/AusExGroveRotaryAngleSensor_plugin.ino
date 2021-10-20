#include "AusExOutputPlugin.h"
#include "AusExGroveRotaryAngleSensor.h"

#define SENSOR_PIN A0

AusExGroveRotaryAngleSensor groveRotaryAngleSensor = AusExGroveRotaryAngleSensor(SENSOR_PIN, (float)5.0);
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
  groveRotaryAngleSensor.begin();
  sensor_t sensor;
  groveRotaryAngleSensor.getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
}

void loop()  
{
  sensors_event_t event;
  if (groveRotaryAngleSensor.getEvent(&event)) {
    outputDevice.EventOutput(event);
  } else {
    Serial.println("read sensor error.");
  }
  delay(3000);
}
