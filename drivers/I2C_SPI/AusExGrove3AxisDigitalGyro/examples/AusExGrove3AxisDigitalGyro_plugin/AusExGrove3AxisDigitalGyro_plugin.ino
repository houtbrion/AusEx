#include "AusExOutputPlugin.h"
#include "AusExGrove3AxisDigitalGyro.h"


//AusExGrove3AxisDigitalGyro groveDigitalGyro=AusExGrove3AxisDigitalGyro(&Wire);
AusExGrove3AxisDigitalGyro groveDigitalGyro=AusExGrove3AxisDigitalGyro(&Wire,100,100);
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
  groveDigitalGyro.begin();
  sensor_t sensor;
  groveDigitalGyro.getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
}


void loop()  
{
  sensors_event_t event;
  if (groveDigitalGyro.getEvent(&event)) {
    outputDevice.EventOutput(event);
  } else {
    Serial.println("read sensor error.");
  }
  delay(3000);
}
