#include "AusExGrove3AxisDigitalAccelerometer1_5g.h"


AusExGrove3AxisDigitalAccelerometer1_5g groveI2cDigitalSensor=AusExGrove3AxisDigitalAccelerometer1_5g(&Wire);


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
  groveI2cDigitalSensor.begin();
  sensor_t sensor;
  groveI2cDigitalSensor.getSensor(&sensor);
  Serial.println("---------------");
  Serial.print("Sensor name    :") ; Serial.println(sensor.name);
  Serial.print("Driver version : "); Serial.println(sensor.version);
  Serial.print("sensor ID      : "); Serial.println(sensor.sensor_id);
  Serial.print("Max Value:    "); Serial.println(sensor.max_value);
  Serial.print("Min Value:    "); Serial.println(sensor.min_value);
  Serial.print("Resolution:   "); Serial.println(sensor.resolution);
  Serial.println("---------------");
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
    Serial.print("sensor value x = "); Serial.println(event.acceleration.x);
    Serial.print("sensor value y = "); Serial.println(event.acceleration.y);
    Serial.print("sensor value z = "); Serial.println(event.acceleration.z);
  } else {
    Serial.println("read sensor error.");
  }
  delay(3000);
}
