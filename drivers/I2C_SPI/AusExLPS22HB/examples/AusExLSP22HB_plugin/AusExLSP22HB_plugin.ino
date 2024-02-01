#include "AusExOutputPlugin.h"
#include "AusExLSP22HB.h"


AusExLPS22HB ausExLPS22HB=AusExLPS22HB(&Wire);
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

  ausExLPS22HB.begin();

  sensor_t sensor;
  ausExLPS22HB.getSensor(&sensor);
  outputDevice.InfoOutput(sensor);

  Serial.print("set sensor mode to hpa....");
  if (0!=ausExLPS22HB.setMode(AUSEX_LPS22HB_MODE_HPA)) {
    Serial.println("Fail.");
  } else {
    Serial.println("Success.");
  }
}
void loop()  
{
  sensors_event_t event;
  if (ausExLPS22HB.getEvent(&event)) {
    outputDevice.EventOutput(event);
  } else {
    Serial.println("read sensor error.");
  }
  delay(3000);
}
