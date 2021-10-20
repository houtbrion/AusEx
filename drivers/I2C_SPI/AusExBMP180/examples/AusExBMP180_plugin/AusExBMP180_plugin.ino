#include "AusExOutputPlugin.h"
#include "AusExBMP180.h"

AUSEX_BMP180_CLASS AusExBMP180=AUSEX_BMP180_CLASS(&Wire);
OutputChannel channel;
AuxExSensorIO outputDevice =  AuxExSensorIO();
unsigned int count=0;

void setup()  
{
  Serial.begin(9600);
  while (!Serial) {
    ; // シリアルポートの準備ができるのを待つ(Leonardoのみ必要)
  }
  channel.serial= &Serial;
  outputDevice.SetIO(AUSEX_OUTPUT_CHANNEL_SERIAL, channel, FORMAT_TYPE_PLAIN_TEXT);
  //
  AusExBMP180.begin();
  sensor_t sensor;
  AusExBMP180.getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
}
void loop()  
{
  sensors_event_t event;
  uint8_t mod=(count%4);
  
  AusExBMP180.setMode(mod);
  mod=AusExBMP180.getMode();
  count++;

  Serial.print("Mode of BMP085/180 = ");
  switch(mod){
    case BMP085_MODE_ULTRALOWPOWER : Serial.println("ULTRA LOW POWER");break;
    case BMP085_MODE_STANDARD      : Serial.println("STANDARD");break;
    case BMP085_MODE_HIGHRES       : Serial.println("HIGH RES");break;
    case BMP085_MODE_ULTRAHIGHRES  : Serial.println("ULTRA HIGH RES");break;
    break;
  }

  for (int i=0;i<10;i++) {
    if (AusExBMP180.getEvent(&event)) {
      outputDevice.EventOutput(event);
    } else {
      Serial.println("read sensor error.");
    }
    delay(3000);
  }
}
