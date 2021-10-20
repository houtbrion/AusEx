#include "AusExOutputPlugin.h"
#include "AusExGroveTemperatureSensor.h"

#define SENSOR_PIN A1  // センサはアナログの3番ポートに接続

AUSEX_TEMPERATURE_CLASS generalAnalogSensor = AUSEX_TEMPERATURE_CLASS(SENSOR_PIN);
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
  generalAnalogSensor.begin();
  sensor_t sensor;
  generalAnalogSensor.getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
}

void loop()
{
  sensors_event_t event;
  if (generalAnalogSensor.getEvent(&event)) {
    outputDevice.EventOutput(event);
  } else {
    Serial.println("read sensor error.");
  }
  delay(3000);
}
