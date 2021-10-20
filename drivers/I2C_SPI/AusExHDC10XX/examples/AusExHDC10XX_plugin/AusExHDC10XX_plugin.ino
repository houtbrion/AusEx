#include "AusExOutputPlugin.h"
#include "AusExHDC10XX.h"

AusExHDC10XX hdc10xx = AusExHDC10XX(&Wire, HDC1000);
OutputChannel channel;
AuxExSensorIO outputDevice =  AuxExSensorIO();
uint32_t delayMS;

void setup()  
{
  Serial.begin(9600);
  while (!Serial) {
    ; // シリアルポートの準備ができるのを待つ(Leonardoのみ必要)
  }
  channel.serial= &Serial;
  outputDevice.SetIO(AUSEX_OUTPUT_CHANNEL_SERIAL, channel, FORMAT_TYPE_PLAIN_TEXT);
  //
  // Initialize device.
  hdc10xx.begin();
  Serial.println(F("hdc10xx Unified Sensor Example"));
  // Print temperature sensor details.
  sensor_t sensor;
  hdc10xx.temperature().getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
  // Print humidity sensor details.
  hdc10xx.humidity().getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
  // Set delay between sensor readings based on sensor details.
  delayMS = 10000;
}
void loop()  
{
  // Delay between measurements.
  delay(delayMS);

  sensors_event_t event;
  // Get humidity event and print its value.
  hdc10xx.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  } else {
    outputDevice.EventOutput(event);
  }
  // Get temperature event and print its value.
  hdc10xx.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  } else {
    outputDevice.EventOutput(event);
  }

}
