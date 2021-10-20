#include "AusExOutputPlugin.h"
#include "AusExGroveI2cTouchSensor.h"

AusExGroveI2cTouchSensor groveI2cDigitalSensor=AusExGroveI2cTouchSensor(&Wire);
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
  groveI2cDigitalSensor.begin();
  sensor_t sensor;
  groveI2cDigitalSensor.getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
}
void loop()  
{
  sensors_event_t event;
  if (groveI2cDigitalSensor.getEvent(&event)) {
    outputDevice.EventOutput(event);
    for (int i=0; i< AUSEX_GROVE_I2C_TOUCH_NUM_OF_SENSORS; i++){
      Serial.print("pin no.");
      Serial.print(i);
      Serial.print(" = ");
      if (groveI2cDigitalSensor.getTouchState(event.value,i)) {
        Serial.println("touched");
      } else {
        Serial.println("not touched");
      }
    }
  } else {
    Serial.println("read sensor error.");
  }
  delay(3000);
}
