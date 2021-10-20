#include "AusExOutputPlugin.h"
#include "AusExGroveAnalog1AxisGyro.h"

#define SENSOR_PIN A0

AusExGroveAnalog1AxisGyro groveAnalog1AxisGyroU = AusExGroveAnalog1AxisGyro(SENSOR_PIN);
OutputChannel channel;
AuxExSensorIO outputDevice =  AuxExSensorIO();

#define NUM_OF_TRY 1000
float reference_Value = 0;


void setup()  
{
  Serial.begin(9600);
  while (!Serial) {
    ; // シリアルポートの準備ができるのを待つ(Leonardoのみ必要)
  }
  channel.serial= &Serial;
  outputDevice.SetIO(AUSEX_OUTPUT_CHANNEL_SERIAL, channel, FORMAT_TYPE_PLAIN_TEXT);
  //
  groveAnalog1AxisGyroU.begin();
  sensor_t sensor;
  groveAnalog1AxisGyroU.getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
  sensors_event_t event;
  int count=0;
  for (int i=0;i<NUM_OF_TRY;i++){
    if (groveAnalog1AxisGyroU.getEvent(&event)) {
      reference_Value+=event.roll;
      count++;
    }
  }
  reference_Value=reference_Value/count;
}
void loop()  
{
  sensors_event_t event;
  if (groveAnalog1AxisGyroU.getEvent(&event)) {
    event.roll=event.roll-reference_Value;
    outputDevice.EventOutput(event);
  } else {
    Serial.println("read sensor error.");
  }
  delay(3000);
}
