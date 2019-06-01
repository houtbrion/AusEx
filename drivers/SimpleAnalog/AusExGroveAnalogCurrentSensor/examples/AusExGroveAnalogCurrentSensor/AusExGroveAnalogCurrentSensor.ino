#include "AusExGroveAnalogCurrentSensor.h"


#define SENSOR_PIN A0

AusExGroveAnalogCurrentSensor groveAnalogCurrentSensor = AusExGroveAnalogCurrentSensor(SENSOR_PIN, (float)5.0);

void setup()  
{
  Serial.begin(9600);
  groveAnalogCurrentSensor.begin();
  sensor_t sensor;
  groveAnalogCurrentSensor.getSensor(&sensor);
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
  int sensorMode=groveAnalogCurrentSensor.getMode();
  if (0 == sensorMode) {
    Serial.println("Sensor Mode = average current");
  } else {
    Serial.println("Sensor Mode = peak current");
  }
  sensor_t sensor;
  groveAnalogCurrentSensor.getSensor(&sensor);
  Serial.print("Sensor Max Value = ");Serial.println(sensor.max_value);
  for (int i=0 ; i< 10 ; i++){
    sensors_event_t event;
    if (groveAnalogCurrentSensor.getEvent(&event)) {
      Serial.print("sensor value = "); Serial.println(event.current);
    } else {
      Serial.println("read sensor error.");
    }
    delay(3000);
  }
  int result;
  if (sensorMode == 0) {
    result = groveAnalogCurrentSensor.setMode(1);
  } else {
    result = groveAnalogCurrentSensor.setMode(0);
  }
  if (1 != result) Serial.println("set sensor mode fail");
}
