#include "AusExOutputPlugin.h"
#include "AusExGroveDustSensor.h"

#define SENSOR_PIN 4

AusExGroveDustSensor dustSensor = AusExGroveDustSensor(SENSOR_PIN);
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
  dustSensor.begin();
  sensor_t sensor;
  dustSensor.getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
  Serial.println("---------------");
  Serial.print("Please wait until ");Serial.print(sensor.init_delay);Serial.println(" micro secs for sensor stability");
}

void loop()  
{
  sensors_event_t event;
  if (dustSensor.getEvent(&event)) {
    if (isnan(event.dust)) {
      Serial.println("read sensor error.");
    } else {
      outputDevice.EventOutput(event);
    }
  } else {
    Serial.println("read sensor error.");
  }
  delay(3000);
}
