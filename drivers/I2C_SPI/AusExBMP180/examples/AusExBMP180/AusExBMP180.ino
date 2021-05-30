#include "AusExBMP180.h"


AUSEX_BMP180_CLASS AusExBMP180=AUSEX_BMP180_CLASS(&Wire);
unsigned int count=0;

void setup()  
{
  Serial.begin(9600);
  AusExBMP180.begin();
  sensor_t sensor;
  AusExBMP180.getSensor(&sensor);
  Serial.println("---------------");
  Serial.print("Sensor name    :") ; Serial.println(sensor.name);
  Serial.print("Driver version : "); Serial.println(sensor.version);
  Serial.print("sensor ID      : "); Serial.println(sensor.sensor_id);
  Serial.print("Max Value:    "); Serial.println(sensor.max_value);
  Serial.print("Min Value:    "); Serial.println(sensor.min_value);
  Serial.print("Resolution:   "); Serial.println(sensor.resolution);
  Serial.println("---------------");
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
      Serial.print("sensor value = "); Serial.println(event.AUSEX_BMP180_SENSOR_RETURN_VALUE);
    } else {
      Serial.println("read sensor error.");
    }
    delay(3000);
  }
}
