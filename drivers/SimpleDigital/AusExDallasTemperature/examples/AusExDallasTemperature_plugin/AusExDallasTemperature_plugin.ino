#include "AusExOutputPlugin.h"
#include "AusExDallasTemperature.h"

#define SENSOR_PIN 4  // センサはデジタルの2番ポートに接続

OutputChannel channel;
AuxExSensorIO outputDevice =  AuxExSensorIO();
AUSEX_DALLAS_TEMPERATURE_CLASS digitalSensor = AUSEX_DALLAS_TEMPERATURE_CLASS(SENSOR_PIN);

void setup()  
{
  Serial.begin(9600);
  while (!Serial) {
    ; // シリアルポートが開くのを待つ。Leonardoでだけ必要。
  }
  channel.serial= &Serial;
  outputDevice.SetIO(AUSEX_OUTPUT_CHANNEL_SERIAL, channel, FORMAT_TYPE_PLAIN_TEXT);

  digitalSensor.begin();
  sensor_t sensor;
  digitalSensor.getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
  delay(sensor.init_delay);
}
void loop()  
{
  sensors_event_t event;
  if (digitalSensor.getEvent(&event)) {
    if (isnan(event.temperature)) {
      Serial.println("read sensor error.");
    } else {
      outputDevice.EventOutput(event);
    }
  } else {
    Serial.println("read sensor error.");
  }
  delay(3000);
}
