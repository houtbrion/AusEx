
#include "AusExOutputPlugin.h"
#include "AusExDHT.h"

#define SENSOR_PIN 4  // センサはデジタルの4番ポートに接続
// Uncomment the type of sensor in use:
//#define DHTTYPE    DHT11     // DHT 11
#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

AusExDHT dht = AusExDHT(SENSOR_PIN,DHTTYPE);

uint32_t delayMS;
OutputChannel channel;

void setup()  
{
  Serial.begin(9600);
  while (!Serial) {
    ; // シリアルポートの準備ができるのを待つ(Leonardoのみ必要)
  }
  channel.serial= &Serial;
  // Initialize device.
  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  AusExSensorInfoOutput(AUSEX_OUTPUT_CHANNEL_SERIAL, channel, sensor);
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  AusExSensorInfoOutput(AUSEX_OUTPUT_CHANNEL_SERIAL, channel, sensor);
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
}
void loop()  
{
  // Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    AusExSensorEventOutput(AUSEX_OUTPUT_CHANNEL_SERIAL, channel, event);
  }
  Serial.println("==================");
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    AusExSensorEventOutput(AUSEX_OUTPUT_CHANNEL_SERIAL, channel, event);
  }
}
