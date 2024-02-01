#include "AusExOutputPlugin.h"
#include "AusExHTS221.h"

AusExHTS221 HTS221 = AusExHTS221(&Wire);

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

  // Initialize device.
  HTS221.begin();
  Serial.println(F("HTS221 Unified Sensor Example"));
  // Print temperature sensor details.
  sensor_t sensor;
  HTS221.temperature().getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
  // Print humidity sensor details.
  HTS221.humidity().getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
  delayMS = 10000;
}
void loop()  
{
  // Delay between measurements.
  delay(delayMS);

  sensors_event_t event;
  // Get humidity event and print its value.
  if (!HTS221.humidity().getEvent(&event)) {
    Serial.println("** humidity read error **");
  }
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  } else {
    outputDevice.EventOutput(event);
  }
  // Get temperature event and print its value.
  if (!HTS221.temperature().getEvent(&event)) {
    Serial.println("** temperature read error **");
  }
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  } else {
    outputDevice.EventOutput(event);
  }

}
