#include "AusExOutputPlugin.h"
#include "AusExADXL335.h"

#define PIN_X A0  // センサはアナログの0から3番ポートに接続
#define PIN_Y A1
#define PIN_Z A2

AUSEX_ADXL335_CLASS adxl335 = AUSEX_ADXL335_CLASS(PIN_X,PIN_Y,PIN_Z,5.0, AUSEX_ADXL335_ZERO_X, AUSEX_ADXL335_ZERO_Y, AUSEX_ADXL335_ZERO_Z, AUSEX_ADXL335_SENSITIVITY, 12345);
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
  adxl335.begin();
  sensor_t sensor;
  adxl335.getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
}
void loop()
{
  sensors_event_t event;
  if (adxl335.getEvent(&event)) {
    outputDevice.EventOutput(event);
  } else {
    Serial.println("read sensor error.");
  }
  delay(3000);
}
