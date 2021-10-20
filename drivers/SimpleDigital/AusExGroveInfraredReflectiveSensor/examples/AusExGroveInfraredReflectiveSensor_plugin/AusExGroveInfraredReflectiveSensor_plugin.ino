#include "AusExOutputPlugin.h"
#include "AusExGroveInfraredReflectiveSensor.h"

#define SENSOR_PIN 13

AusExGroveInfraredReflectiveSensor irSensor = AusExGroveInfraredReflectiveSensor(SENSOR_PIN);
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
  irSensor.begin();
  sensor_t sensor;
  irSensor.getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
}
void loop()  
{
  sensors_event_t event;
  if (irSensor.getEvent(&event)) {
    if (isnan(event.value)) {
      Serial.println("read sensor error.");
    } else {
      outputDevice.EventOutput(event);
    }
  } else {
    Serial.println("read sensor error.");
  }
  delay(3000);
}
