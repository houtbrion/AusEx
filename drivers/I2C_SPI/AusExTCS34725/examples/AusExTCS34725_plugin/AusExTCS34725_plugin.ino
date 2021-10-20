#include "AusExOutputPlugin.h"
#include "AusExTCS34725.h"


AUSEX_TCS34725_CLASS colorSensor=AUSEX_TCS34725_CLASS(&Wire);
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
  colorSensor.begin();
  sensor_t sensor;
  colorSensor.getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
}

bool setSensorMode(uint8_t g, uint8_t i ){
  tcs34725Gain_t gain;
  tcs34725IntegrationTime_t intTime;
  switch(g){
    case 0: gain=TCS34725_GAIN_1X;break;
    case 1: gain=TCS34725_GAIN_4X;break;
    case 2: gain=TCS34725_GAIN_16X;break;
    case 3: gain=TCS34725_GAIN_60X;break;
  }
  switch(i){
    case 0: intTime=TCS34725_INTEGRATIONTIME_2_4MS;break;
    case 1: intTime=TCS34725_INTEGRATIONTIME_24MS;break;
    case 2: intTime=TCS34725_INTEGRATIONTIME_50MS;break;
    case 3: intTime=TCS34725_INTEGRATIONTIME_101MS;break;
    case 4: intTime=TCS34725_INTEGRATIONTIME_154MS;break;
    case 5: intTime=TCS34725_INTEGRATIONTIME_700MS;break;
  }
  if (0==colorSensor.setMode(colorSensor.generateMode(gain,intTime))) return false;
  return true;
}

void printSensorMode(void){
  tcs34725Gain_t gain;
  tcs34725IntegrationTime_t intTime;
  int mode=colorSensor.getMode();
  Serial.print("sensor mode = ");Serial.println(mode,HEX);
  if (!colorSensor.parseMode(mode,&gain,&intTime)) {
    Serial.println("can not read current sensor gain and integration time");
    return;
  }
  Serial.print("sensor gain : ");Serial.print(gain,HEX);Serial.print(" = ");
  switch (gain) {
    case TCS34725_GAIN_1X : Serial.println("TCS34725_GAIN_1X");break;
    case TCS34725_GAIN_4X : Serial.println("TCS34725_GAIN_4X");break;
    case TCS34725_GAIN_16X : Serial.println("TCS34725_GAIN_16X");break;
    case TCS34725_GAIN_60X : Serial.println("TCS34725_GAIN_60X");break;
  }
  Serial.print("sensor integration time : ");Serial.print(intTime,HEX);Serial.print(" = ");
  switch(intTime){
    case TCS34725_INTEGRATIONTIME_2_4MS: Serial.println("TCS34725_INTEGRATIONTIME_2_4MS");break;
    case TCS34725_INTEGRATIONTIME_24MS: Serial.println("TCS34725_INTEGRATIONTIME_24MS");break;
    case TCS34725_INTEGRATIONTIME_50MS: Serial.println("TCS34725_INTEGRATIONTIME_50MS");break;
    case TCS34725_INTEGRATIONTIME_101MS: Serial.println("TCS34725_INTEGRATIONTIME_101MS");break;
    case TCS34725_INTEGRATIONTIME_154MS: Serial.println("TCS34725_INTEGRATIONTIME_154MS");break;
    case TCS34725_INTEGRATIONTIME_700MS: Serial.println("TCS34725_INTEGRATIONTIME_700MS");break;
  }
}

void loop()  
{
  sensors_event_t event;
  for (int i=0;i<4;i++){
    for (int j=0;j<6;j++){
      Serial.print("set sonsor mode");
      if (setSensorMode(i,j)){
        Serial.println("....done");
      } else {
        Serial.println(".... fail");
      };
      printSensorMode();
      if (colorSensor.getEvent(&event)) {
        outputDevice.EventOutput(event);
        Serial.print("Lux               : ");Serial.println(colorSensor.calculateLux());
        Serial.print("ColorTemperature  : ");Serial.println(colorSensor.calculateColorTemperature());
      } else {
        Serial.println("read sensor error.");
      };
      delay(3000);
    }
  }
}
