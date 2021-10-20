#include "AusExOutputPlugin.h"
#include "AusExSHT2x.h"

AusExSHT2x sht2x = AusExSHT2x(&Wire, SHT21);
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
  sht2x.begin();
  Serial.println(F("sht2x Unified Sensor Example"));
  // Print temperature sensor details.
  sensor_t sensor;
  sht2x.temperature().getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
  //
  delayMS = sensor.min_delay/1000;
  // Print humidity sensor details.
  sht2x.humidity().getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
  if ((sensor.min_delay/1000) > delayMS) {
    delayMS = sensor.min_delay/1000;
  }
}

void loop()
{
  // Delay between measurements.
  delay(delayMS);

  sensors_event_t event;
  // Get humidity event and print its value.
  sht2x.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  } else {
    outputDevice.EventOutput(event);
  }
  // Get temperature event and print its value.
  sht2x.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  } else {
    outputDevice.EventOutput(event);
  }
}
