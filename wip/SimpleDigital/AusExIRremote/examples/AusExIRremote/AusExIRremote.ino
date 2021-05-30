#include "AusExIRremote.h"

#define SENSOR_PIN 4  // センサはデジタルの4番ポートに接続

AUSEX_IRREMOTE_CLASS digitalSensor = AUSEX_IRREMOTE_CLASS(SENSOR_PIN);

void setup()  
{
  Serial.begin(9600);
  digitalSensor.begin();
  sensor_t sensor;
  digitalSensor.getSensor(&sensor);
  Serial.println("---------------");
  Serial.print("Sensor name    :") ; Serial.println(sensor.name);
  Serial.print("Driver version : "); Serial.println(sensor.version);
  Serial.print("sensor ID      : "); Serial.println(sensor.sensor_id);
  Serial.print("Max Value:    "); Serial.println(sensor.max_value);
  Serial.print("Min Value:    "); Serial.println(sensor.min_value);
  Serial.print("Resolution:   "); Serial.println(sensor.resolution);
  Serial.println("---------------");
}

void printIrData(sensors_event_t *event){
  Serial.print("Vender : ");
  switch (event->irremote.decode_type) {
    default:
    case UNKNOWN:      Serial.println("UNKNOWN");       break ;
    case NEC:          Serial.println("NEC");           break ;
    case SONY:         Serial.println("SONY");          break ;
    case RC5:          Serial.println("RC5");           break ;
    case RC6:          Serial.println("RC6");           break ;
    case DISH:         Serial.println("DISH");          break ;
    case SHARP:        Serial.println("SHARP");         break ;
    case JVC:          Serial.println("JVC");           break ;
    case SANYO:        Serial.println("SANYO");         break ;
    case MITSUBISHI:   Serial.println("MITSUBISHI");    break ;
    case SAMSUNG:      Serial.println("SAMSUNG");       break ;
    case LG:           Serial.println("LG");            break ;
    case WHYNTER:      Serial.println("WHYNTER");       break ;
    case AIWA_RC_T501: Serial.println("AIWA_RC_T501");  break ;
    case PANASONIC:    Serial.println("PANASONIC");     break ;
    case DENON:        Serial.println("Denon");         break ;
  }
  Serial.print("Address : ");Serial.println(event->irremote.address,HEX);
  Serial.print("Value   : ");Serial.println(event->irremote.value,HEX);
}

void loop()  
{
  sensors_event_t event;
  if (digitalSensor.getEvent(&event)) {
    if (1==event.irremote.overflow) {
      Serial.println("data size is too big.");
    } else {
      printIrData(&event);
    }
  } else {
    Serial.println("no data.");
  }
  delay(3000);
}
