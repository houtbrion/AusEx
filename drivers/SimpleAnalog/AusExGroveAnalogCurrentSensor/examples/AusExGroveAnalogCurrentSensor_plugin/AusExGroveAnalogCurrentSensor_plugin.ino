#include "AusExOutputPlugin.h"
#include "AusExGroveAnalogCurrentSensor.h"


#define SENSOR_PIN A0

AusExGroveAnalogCurrentSensor groveAnalogCurrentSensor = AusExGroveAnalogCurrentSensor(SENSOR_PIN, (float)5.0);
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
  groveAnalogCurrentSensor.begin();
  sensor_t sensor;
  groveAnalogCurrentSensor.getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
}
void loop()
{
  int sensorMode=groveAnalogCurrentSensor.getMode();
  if (0 == sensorMode) {
    Serial.println("Sensor Mode = average current");
  } else {
    Serial.println("Sensor Mode = peak current");
  }
  sensor_t sensor;
  groveAnalogCurrentSensor.getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
  for (int i=0 ; i< 10 ; i++){
    sensors_event_t event;
    if (groveAnalogCurrentSensor.getEvent(&event)) {
      outputDevice.EventOutput(event);
    } else {
      Serial.println("read sensor error.");
    }
    delay(3000);
  }
  int result;
  if (sensorMode == 0) {
    result = groveAnalogCurrentSensor.setMode(1);
  } else {
    result = groveAnalogCurrentSensor.setMode(0);
  }
  if (1 != result) Serial.println("set sensor mode fail");
}
