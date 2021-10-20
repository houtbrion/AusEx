#include "AusExOutputPlugin.h"
#include "AusExGrovePirSensor.h"

#define SENSOR_PIN 4

AusExGrovePirSensor pirSensor = AusExGrovePirSensor(SENSOR_PIN, 1);
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
  pirSensor.begin();
  sensor_t sensor;
  pirSensor.getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
  delay(sensor.init_delay/1000);
}
void loop()  
{
  sensors_event_t event;
  if (pirSensor.getEvent(&event)) {
    outputDevice.EventOutput(event);
  } else {
    Serial.println("read sensor error.");
  }
  delay(3000);
}
