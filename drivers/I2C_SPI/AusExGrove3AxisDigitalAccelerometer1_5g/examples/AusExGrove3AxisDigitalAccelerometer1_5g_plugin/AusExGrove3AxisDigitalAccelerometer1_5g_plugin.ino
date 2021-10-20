#include "AusExOutputPlugin.h"
#include "AusExGrove3AxisDigitalAccelerometer1_5g.h"


AusExGrove3AxisDigitalAccelerometer1_5g groveI2cDigitalSensor=AusExGrove3AxisDigitalAccelerometer1_5g(&Wire);
OutputChannel channel;
AuxExSensorIO outputDevice =  AuxExSensorIO();

int calcSamplingRate(int val) {
  int rate=-1;
  switch(val){
    case 0 : rate=120;break;
    case 1 : rate=64;break;
    case 2 : rate=32;break;
    case 3 : rate=16;break;
    case 4 : rate=8;break;
    case 5 : rate=4;break;
    case 6 : rate=2;break;
    case 7 : rate=1;
  }
  return rate;
}

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
  int rate=calcSamplingRate(groveI2cDigitalSensor.getMode());
  Serial.print("default Sampling Rate = ");Serial.print(rate);Serial.println(" (times/s)");
  Serial.println("set  64 to sampling rate ");
  rate=calcSamplingRate(groveI2cDigitalSensor.getMode());
  Serial.print("new Sampling Rate = ");Serial.print(rate);Serial.println(" (times/s)");
}
void loop()  
{
  sensors_event_t event;
  if (groveI2cDigitalSensor.getEvent(&event)) {
    outputDevice.EventOutput(event);
  } else {
    Serial.println("read sensor error.");
  }
  delay(3000);
}
