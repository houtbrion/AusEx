#include "AusExOutputPlugin.h"
#include "AusExTSL2561.h"

/*
 * I2Cアドレス
 * Groveのモジュール(Didital Light Sensor)は0x29
 * AdafruitのTSL2561モジュールはハード的に選択可能
 */


#define ADDR TSL2561_ADDR_LOW   // (0x29)  default address (pin pulled low)
//#define ADDR TSL2561_ADDR_FLOAT // (0x39)                  (pin left floating)
//#define ADDR TSL2561_ADDR_HIGH  // (0x49)                   (pin pulled high)

AUSEX_TSL2561_CLASS lightSensor=AUSEX_TSL2561_CLASS(&Wire);
OutputChannel channel;
AuxExSensorIO outputDevice =  AuxExSensorIO();

void printSensorMode(){
  int mode=lightSensor.getMode();
  tsl2561Gain_t gain;
  tsl2561IntegrationTime_t itime;
  lightSensor.parseMode(mode,&gain,&itime);
  switch(gain){
    case 0x00 : Serial.println("sensor gain = 1x");break;
    case 0x10 : Serial.println("sensor gain = 16x");break;
  }
  switch(itime){
    case 0x00 : Serial.println("sensor integration time = 13.7ms");break;
    case 0x01 : Serial.println("sensor integration time = 101ms");break;
    case 0x02 : Serial.println("sensor integration time = 402ms");break;
  }
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
  lightSensor.begin(ADDR);
  sensor_t sensor;
  lightSensor.getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
}

void loop()
{
  for (int i=0;i<2;i++){
    for (int j=0;j<3;j++){
      tsl2561Gain_t gain;
      switch(i){
        case 0 : gain=TSL2561_GAIN_1X;break;
        case 1 : gain=TSL2561_GAIN_16X;break;
      }
      tsl2561IntegrationTime_t itime;
      switch(j){
        case 0 : itime=TSL2561_INTEGRATIONTIME_13MS;break;
        case 1 : itime=TSL2561_INTEGRATIONTIME_101MS;break;
        case 2 : itime=TSL2561_INTEGRATIONTIME_402MS;break;
      }
      int mode=lightSensor.generateMode(gain,itime);
      lightSensor.setMode(mode);
      printSensorMode();
      for (int k=0;k<5;k++){
        sensors_event_t event;
        if (lightSensor.getEvent(&event)) {
          outputDevice.EventOutput(event);
        } else {
          Serial.println("read sensor error.");
        }
        delay(3000);
      }
    }
  }
}
