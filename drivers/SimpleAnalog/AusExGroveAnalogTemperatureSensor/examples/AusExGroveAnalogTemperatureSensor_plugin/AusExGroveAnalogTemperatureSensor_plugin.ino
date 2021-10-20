//  Grove - Temperature Sensor V1.1/1.2用 サンプルプログラム
#include "AusExOutputPlugin.h"
#include "AusExGroveAnalogTemperatureSensor.h"

AusExGroveAnalog1Temperature groveTemperatureSensor=AusExGroveAnalog1Temperature(A0);
OutputChannel channel;
AuxExSensorIO outputDevice =  AuxExSensorIO();

void setup()
{

  while (!Serial); // for Leonardo/Micro/Zero

  Serial.begin(9600);
  while (!Serial) {
    ; // シリアルポートの準備ができるのを待つ(Leonardoのみ必要)
  }
  channel.serial= &Serial;
  outputDevice.SetIO(AUSEX_OUTPUT_CHANNEL_SERIAL, channel, FORMAT_TYPE_PLAIN_TEXT);
  //
  Serial.println("Temperature sensor Test"); Serial.println("");
  if (!groveTemperatureSensor.begin()){
    Serial.println("Sensor error in begin()");
    while(1);
  }
  sensor_t sensor;
  groveTemperatureSensor.getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
}

void loop()
{
  sensors_event_t event;
  groveTemperatureSensor.getEvent(&event);
  outputDevice.EventOutput(event);
  delay(3000);
}
