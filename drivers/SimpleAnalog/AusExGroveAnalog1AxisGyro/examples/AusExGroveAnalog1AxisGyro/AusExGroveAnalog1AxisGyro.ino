#include "AusExGroveAnalog1AxisGyro.h"

#define SENSOR_PIN A0

GroveAnalog1AxisGyroAusEx groveAnalog1AxisGyroU = GroveAnalog1AxisGyroAusEx(SENSOR_PIN);

#define NUM_OF_TRY 1000
float reference_Value = 0;


void setup()  
{
  Serial.begin(9600);
  groveAnalog1AxisGyroU.begin();
  sensor_t sensor;
  groveAnalog1AxisGyroU.getSensor(&sensor);
  Serial.println("---------------");
  Serial.print("Sensor name    :") ; Serial.println(sensor.name);
  Serial.print("Driver version : "); Serial.println(sensor.version);
  Serial.print("sensor ID      : "); Serial.println(sensor.sensor_id);
  Serial.print("Max Value:    "); Serial.println(sensor.max_value);
  Serial.print("Min Value:    "); Serial.println(sensor.min_value);
  Serial.print("Resolution:   "); Serial.println(sensor.resolution);
  Serial.println("---------------");
  sensors_event_t event;
  int count=0;
  for (int i=0;i<NUM_OF_TRY;i++){
    if (groveAnalog1AxisGyroU.getEvent(&event)) {
      reference_Value+=event.roll;
      count++;
    }
  }
  reference_Value=reference_Value/count;
}
void loop()  
{
  sensors_event_t event;
  double roll=0;
  if (groveAnalog1AxisGyroU.getEvent(&event)) {
    Serial.print("sensor value = "); Serial.println(event.roll);
    roll=(double)(event.roll-reference_Value);
    Serial.print("angular volocity = "); Serial.print(roll);Serial.println(" (deg/s)");
  } else {
    Serial.println("read sensor error.");
  }
  delay(3000);
}
