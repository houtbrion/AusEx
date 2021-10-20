#include "AusExOutputPlugin.h"
#include "AusExAM232X.h"

AusExAM232X am232x = AusExAM232X(&Wire, AM2321);
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
  am232x.begin();
  Serial.println(F("am232x Unified Sensor Example"));
  // Print temperature sensor details.
  sensor_t sensor;
  am232x.temperature().getSensor(&sensor);
  outputDevice.InfoOutput(sensor);

  // Print humidity sensor details.
  am232x.humidity().getSensor(&sensor);
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
  am232x.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  } else {
    outputDevice.EventOutput(event);
  }
  // Get temperature event and print its value.
  am232x.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  } else {
    outputDevice.EventOutput(event);
  }

}
