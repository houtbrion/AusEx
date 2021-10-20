#include "AusExOutputPlugin.h"
#include "AusExSHT31.h"

AusExSHT31 sht31 = AusExSHT31(&Wire);
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
  sht31.begin();
  Serial.println(F("SHT31 Unified Sensor Example"));
  // Print temperature sensor details.
  sensor_t sensor;
  sht31.temperature().getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
  // Print humidity sensor details.
  sht31.humidity().getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
  // Set delay between sensor readings based on sensor details.
  delayMS = 8000;
}
void loop()  
{
  // Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;
  sht31.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  } else {
    outputDevice.EventOutput(event);
  }
  // Get humidity event and print its value.
  sht31.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  } else {
    outputDevice.EventOutput(event);
  }
}
