#include "AusExSHT2x.h"

AusExSHT2x sht2x = AusExSHT2x(&Wire, SHT21);

uint32_t delayMS;

void setup()  
{
  Serial.begin(9600);
  while (!Serial) {
    ; // シリアルポートが開くのを待つ。Leonardoでだけ必要。
  }
  // Initialize device.
  sht2x.begin();
  Serial.println(F("sht2x Unified Sensor Example"));
  // Print temperature sensor details.
  sensor_t sensor;
  sht2x.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  //
  delayMS = sensor.min_delay/1000;
  // Print humidity sensor details.
  sht2x.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
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
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }
  // Get temperature event and print its value.
  sht2x.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  } else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }

}
