#include "AusExOutputPlugin.h"
#include "AusExGPS.h"

//SoftwareSerial sSerial(4,5);
SoftwareSerial sSerial(6,7);
AusExGPS ausExGPS(&sSerial);
//AusExGPS ausExGPS(&Serial1);
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
  ausExGPS.begin(9600);
  sensor_t sensor;
  ausExGPS.position().getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
  ausExGPS.date().getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
  ausExGPS.orientation().getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
  ausExGPS.speed().getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
}

void loop()
{
  sensors_event_t event;
  if (ausExGPS.position().getEvent(&event)) {
    outputDevice.EventOutput(event);
  } else {
    Serial.println("position read error.");
  }
  if (ausExGPS.date().getEvent(&event)) {
    outputDevice.EventOutput(event);
  } else {
    Serial.println("date read error.");
  }
  if (ausExGPS.orientation().getEvent(&event)) {
    outputDevice.EventOutput(event);
  } else {
    Serial.println("orientation read error.");
  }
  if (ausExGPS.speed().getEvent(&event)) {
    outputDevice.EventOutput(event);
  } else {
    Serial.println("speed read error.");
  }
  delay(3000);
}
