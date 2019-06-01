#include "AusExGPS.h"

//SoftwareSerial sSerial(4,5);
SoftwareSerial sSerial(6,7);
AusExGPS ausExGPS(&sSerial);
//AusExGPS ausExGPS(&Serial1);

void setup()
{
  Serial.begin(9600);
  ausExGPS.begin(9600);
  sensor_t sensor;
  ausExGPS.position().getSensor(&sensor);
  Serial.println("---------------");
  Serial.print("Sensor name    :") ; Serial.println(sensor.name);
  Serial.print("Driver version : "); Serial.println(sensor.version);
  Serial.print("sensor ID      : "); Serial.println(sensor.sensor_id);
  Serial.print("Max Value:    "); Serial.println(sensor.max_value);
  Serial.print("Min Value:    "); Serial.println(sensor.min_value);
  Serial.print("Resolution:   "); Serial.println(sensor.resolution);
  Serial.println("---------------");
  ausExGPS.date().getSensor(&sensor);
  Serial.println("---------------");
  Serial.print("Sensor name    :") ; Serial.println(sensor.name);
  Serial.print("Driver version : "); Serial.println(sensor.version);
  Serial.print("sensor ID      : "); Serial.println(sensor.sensor_id);
  Serial.print("Max Value:    "); Serial.println(sensor.max_value);
  Serial.print("Min Value:    "); Serial.println(sensor.min_value);
  Serial.print("Resolution:   "); Serial.println(sensor.resolution);
  Serial.println("---------------");
  ausExGPS.orientation().getSensor(&sensor);
  Serial.println("---------------");
  Serial.print("Sensor name    :") ; Serial.println(sensor.name);
  Serial.print("Driver version : "); Serial.println(sensor.version);
  Serial.print("sensor ID      : "); Serial.println(sensor.sensor_id);
  Serial.print("Max Value:    "); Serial.println(sensor.max_value);
  Serial.print("Min Value:    "); Serial.println(sensor.min_value);
  Serial.print("Resolution:   "); Serial.println(sensor.resolution);
  Serial.println("---------------");
  ausExGPS.speed().getSensor(&sensor);
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
  if (ausExGPS.position().getEvent(&event)) {
    Serial.print("latitude = "); Serial.println(event.position.latitude);
    Serial.print("longtitude = "); Serial.println(event.position.longtitude);
    Serial.print("altitude = "); Serial.println(event.position.altitude);
    Serial.print("dop = "); Serial.println(event.position.dop);
  } else {
    Serial.println("position read error.");
  }
  if (ausExGPS.date().getEvent(&event)) {
    Serial.print("year = "); Serial.println(event.date.year);
    Serial.print("month = "); Serial.println(event.date.month);
    Serial.print("day = "); Serial.println(event.date.day);
    Serial.print("hour = "); Serial.println(event.date.hour);
    Serial.print("minute = "); Serial.println(event.date.minute);
    Serial.print("second = "); Serial.println(event.date.second);
    Serial.print("millisecond = "); Serial.println(event.date.millisecond);
  } else {
    Serial.println("date read error.");
  }
  if (ausExGPS.orientation().getEvent(&event)) {
    Serial.print("heading = "); Serial.println(event.orientation.heading);
  } else {
    Serial.println("orientation read error.");
  }
  if (ausExGPS.speed().getEvent(&event)) {
    Serial.print("speed = "); Serial.println(event.speed);
  } else {
    Serial.println("speed read error.");
  }
  delay(3000);
}
