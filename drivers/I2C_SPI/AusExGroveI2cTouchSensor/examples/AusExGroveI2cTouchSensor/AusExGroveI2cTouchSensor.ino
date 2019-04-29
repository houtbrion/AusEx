#include "AusExGroveI2cTouchSensor.h"


AusExGroveI2cTouchSensor groveI2cDigitalSensor=AusExGroveI2cTouchSensor(&Wire);

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
}
void loop()  
{
  sensors_event_t event;
  if (groveI2cDigitalSensor.getEvent(&event)) {
    Serial.print("sensor value = "); Serial.println(event.value);
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
