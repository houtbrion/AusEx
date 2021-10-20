#include "AusExOutputPlugin.h"
#include "AusExBME280.h"

/* ESP32のソフトSPI 
#define BME_SCK GPIO_NUM_14
#define BME_MISO GPIO_NUM_13
#define BME_MOSI GPIO_NUM_27
#define BME_CS GPIO_NUM_26
*/
/* ESP8266のソフトSPI 
#define BME_SCK 14
#define BME_MISO 12
#define BME_MOSI 13
#define BME_CS 15
*/
/* M0 proのソフトSPI 
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
*/
/* Pro mini 3.3V 8MHzのソフトSPI */
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10


//AusExBME280 bme280 = AusExBME280(&Wire);
//AusExBME280 bme280 = AusExBME280(0xFF, 0xFF, 0xFF, 5);  // ESP32のハードSPI
//AusExBME280 bme280 = AusExBME280(0xFF, 0xFF, 0xFF, 15);  // ESP8266のハードSPI
//AusExBME280 bme280 = AusExBME280(0xFF, 0xFF, 0xFF, 10);  // M0 proのハードSPI
//AusExBME280 bme280 = AusExBME280(14, 12, 13, 15);
AusExBME280 bme280 = AusExBME280(BME_SCK, BME_MOSI, BME_MISO, BME_CS);
OutputChannel channel;
AuxExSensorIO outputDevice =  AuxExSensorIO();
uint32_t delayMS;

void printMode(){
  int mode;
  mode=bme280.getMode();
  uint8_t state,tempSample,humSample,pressSample,filter,standby;
  if (!bme280.parseMode(mode,&state,&tempSample,&humSample,&pressSample,&filter,&standby)) {
    Serial.println("Sensor mode is unknown");
  } else {
    if (mode==BME280_NORMAL_MODE) {
      Serial.println("sensor is always on");
    } else {
      Serial.println("sensor is useally off");
    }
    switch(tempSample) {
      case BME280_SAMPLING_NONE: Serial.println("temperature sampling : BME280_SAMPLING_NONE");break;
      case BME280_SAMPLING_X1: Serial.println("temperature sampling : BME280_SAMPLING_X1");break;
      case BME280_SAMPLING_X2: Serial.println("temperature sampling : BME280_SAMPLING_X2");break;
      case BME280_SAMPLING_X4: Serial.println("temperature sampling : BME280_SAMPLING_X4");break;
      case BME280_SAMPLING_X8: Serial.println("temperature sampling : BME280_SAMPLING_X8");break;
      case BME280_SAMPLING_X16: Serial.println("temperature sampling : BME280_SAMPLING_X16");break;
    }
    switch(humSample) {
      case BME280_SAMPLING_NONE: Serial.println("humidity sampling : BME280_SAMPLING_NONE");break;
      case BME280_SAMPLING_X1: Serial.println("humidity sampling : BME280_SAMPLING_X1");break;
      case BME280_SAMPLING_X2: Serial.println("humidity sampling : BME280_SAMPLING_X2");break;
      case BME280_SAMPLING_X4: Serial.println("humidity sampling : BME280_SAMPLING_X4");break;
      case BME280_SAMPLING_X8: Serial.println("humidity sampling : BME280_SAMPLING_X8");break;
      case BME280_SAMPLING_X16: Serial.println("humidity sampling : BME280_SAMPLING_X16");break;
    }
    switch(pressSample) {
      case BME280_SAMPLING_NONE: Serial.println("pressure sampling : BME280_SAMPLING_NONE");break;
      case BME280_SAMPLING_X1: Serial.println("pressure sampling : BME280_SAMPLING_X1");break;
      case BME280_SAMPLING_X2: Serial.println("pressure sampling : BME280_SAMPLING_X2");break;
      case BME280_SAMPLING_X4: Serial.println("pressure sampling : BME280_SAMPLING_X4");break;
      case BME280_SAMPLING_X8: Serial.println("pressure sampling : BME280_SAMPLING_X8");break;
      case BME280_SAMPLING_X16: Serial.println("pressure sampling : BME280_SAMPLING_X16");break;
    }
    switch(filter) {
      case BME280_FILTER_OFF: Serial.println("filter : BME280_SAMPLING_NONE");break;
      case BME280_FILTER_X2: Serial.println("filter : BME280_SAMPLING_X1");break;
      case BME280_FILTER_X4: Serial.println("filter : BME280_SAMPLING_X2");break;
      case BME280_FILTER_X8: Serial.println("filter : BME280_SAMPLING_X4");break;
      case BME280_FILTER_X16: Serial.println("filter : BME280_SAMPLING_X8");break;
    }
    switch(standby) {
      case BME280_STANDBY_MS_0_5: Serial.println("standby : BME280_STANDBY_MS_0_5");break;
      case BME280_STANDBY_MS_10: Serial.println("standby : BME280_STANDBY_MS_10");break;
      case BME280_STANDBY_MS_20: Serial.println("standby : BME280_STANDBY_MS_20");break;
      case BME280_STANDBY_MS_62_5: Serial.println("standby : BME280_STANDBY_MS_62_5");break;
      case BME280_STANDBY_MS_125: Serial.println("standby : BME280_STANDBY_MS_125");break;
      case BME280_STANDBY_MS_250: Serial.println("standby : BME280_STANDBY_MS_250");break;
      case BME280_STANDBY_MS_500: Serial.println("standby : BME280_STANDBY_MS_500");break;
      case BME280_STANDBY_MS_1000: Serial.println("standby : BME280_STANDBY_MS_1000");break;
    }
  }
}

void setup()  
{
  int32_t delayMilli;
  Serial.begin(9600);
  while (!Serial) {
    ; // シリアルポートの準備ができるのを待つ(Leonardoのみ必要)
  }
  channel.serial= &Serial;
  outputDevice.SetIO(AUSEX_OUTPUT_CHANNEL_SERIAL, channel, FORMAT_TYPE_PLAIN_TEXT);
  //
  Serial.println(F("bme280 Unified Sensor Example"));
  // Initialize device.
  bool status;
  status=bme280.begin();
  delay(AUSEX_BME280_SENSOR_INIT_DELAY);  // この待ち合わせを入れないと，挙動不安定になる場合がある(ソフトSPIの場合は待ち合わせ必須)
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
  // Print temperature sensor details.
  sensor_t sensor;
  bme280.temperature().getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
  delayMilli = sensor.min_delay;
  // Print humidity sensor details.
  bme280.humidity().getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
  if (delayMilli < sensor.min_delay) delayMilli = sensor.min_delay;
  // Print pressure sensor details.
  bme280.pressure().getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
  if (delayMilli < sensor.min_delay) delayMilli = sensor.min_delay;
  printMode();
  // Set delay between sensor readings based on sensor details.
  delayMS = delayMilli / 1000;
}
void loop()  
{
  // Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;
  bme280.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  } else {
    outputDevice.EventOutput(event);
  }
  // Get humidity event and print its value.
  bme280.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  } else {
    outputDevice.EventOutput(event);
  }
  // Get pressure event and print its value.
  bme280.pressure().getEvent(&event);
  if (isnan(event.pressure)) {
    Serial.println(F("Error reading pressure!"));
  } else {
    outputDevice.EventOutput(event);
  }
}
