#include "AusExOutputPlugin.h"
#include "AusExADXL345.h"

#ifdef ESP32
#define ADXL_SCK GPIO_NUM_18
#define ADXL_MISO GPIO_NUM_19
#define ADXL_MOSI GPIO_NUM_23
#define ADXL_CS GPIO_NUM_16
#else
/* Uno等 AVR系 */
#define ADXL_SCK 13
#define ADXL_MISO 12
#define ADXL_MOSI 11
#define ADXL_CS 8
#endif

/* Assign a unique ID to this sensor at the same time */
// I2C接続の場合
AusExADXL345 accel = AusExADXL345(&Wire, 12345);
// ソフトウェアSPI接続の場合
//AusExADXL345 accel = AusExADXL345(ADXL_SCK, ADXL_MISO, ADXL_MOSI, ADXL_CS, 12345);
// ハードウェアSPI接続の場合
//AusExADXL345 accel = AusExADXL345(0xFF, 0, 0, ADXL_CS, 12345);
OutputChannel channel;
AuxExSensorIO outputDevice =  AuxExSensorIO();

void displaySensorDetails(void)
{
  sensor_t sensor;
  accel.getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
  delay(500);
}

void displayDataRate(void)
{
  Serial.print  ("Data Rate:    "); 
  switch(accel.getRateParam(accel.getMode()))
  {
    case AUSEX_ADXL345_DATARATE_3200_HZ:
      Serial.print  ("3200 ");
      break;
    case AUSEX_ADXL345_DATARATE_1600_HZ:
      Serial.print  ("1600 ");
      break;
    case AUSEX_ADXL345_DATARATE_800_HZ:
      Serial.print  ("800 ");
      break;
    case AUSEX_ADXL345_DATARATE_400_HZ:
      Serial.print  ("400 ");
      break;
    case AUSEX_ADXL345_DATARATE_200_HZ:
      Serial.print  ("200 ");
      break;
    case AUSEX_ADXL345_DATARATE_100_HZ:
      Serial.print  ("100 ");
      break;
    case AUSEX_ADXL345_DATARATE_50_HZ:
      Serial.print  ("50 ");
      break;
    case AUSEX_ADXL345_DATARATE_25_HZ:
      Serial.print  ("25 ");
      break;
    case AUSEX_ADXL345_DATARATE_12_5_HZ:
      Serial.print  ("12.5 ");
      break;
    case AUSEX_ADXL345_DATARATE_6_25HZ:
      Serial.print  ("6.25 ");
      break;
    case AUSEX_ADXL345_DATARATE_3_13_HZ:
      Serial.print  ("3.13 ");
      break;
    case AUSEX_ADXL345_DATARATE_1_56_HZ:
      Serial.print  ("1.56 ");
      break;
    case AUSEX_ADXL345_DATARATE_0_78_HZ:
      Serial.print  ("0.78 ");
      break;
    case AUSEX_ADXL345_DATARATE_0_39_HZ:
      Serial.print  ("0.39 ");
      break;
    case AUSEX_ADXL345_DATARATE_0_20_HZ:
      Serial.print  ("0.20 ");
      break;
    case AUSEX_ADXL345_DATARATE_0_10_HZ:
      Serial.print  ("0.10 ");
      break;
    default:
      Serial.print  ("???? ");
      break;
  }
  Serial.println(" Hz");  
}

void displayRange(void)
{
  Serial.print  ("Range:         +/- "); 
  switch(accel.getRangeParam(accel.getMode()))
  {
    case AUSEX_ADXL345_RANGE_16_G:
      Serial.print  ("16 ");
      break;
    case AUSEX_ADXL345_RANGE_8_G:
      Serial.print  ("8 ");
      break;
    case AUSEX_ADXL345_RANGE_4_G:
      Serial.print  ("4 ");
      break;
    case AUSEX_ADXL345_RANGE_2_G:
      Serial.print  ("2 ");
      break;
    default:
      Serial.print  ("?? ");
      break;
  }
  Serial.println(" g");  
}

void setup(void) 
{
  Serial.begin(9600);
#ifndef ESP8266
  while (!Serial); // for Leonardo/Micro/Zero
#endif
  Serial.println("Accelerometer Test"); Serial.println("");
  channel.serial= &Serial;
  outputDevice.SetIO(AUSEX_OUTPUT_CHANNEL_SERIAL, channel, FORMAT_TYPE_PLAIN_TEXT);
  
  /* Initialise the sensor */
  if(!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while(1);
  }

  /* Display some basic information on this sensor */
  displaySensorDetails();
  /* Display additional settings (outside the scope of sensor_t) */
  Serial.println("Default sampling rate and range");
  displayDataRate();
  displayRange();
  Serial.println("");

  /* Set the range to whatever is appropriate for your project */
  Serial.println("set new sampling rate and range");
  //accel.setMode(accel.getModeParam(AUSEX_ADXL345_RANGE_2_G,AUSEX_ADXL345_DATARATE_0_20_HZ));
  accel.setMode(accel.getModeParam(AUSEX_ADXL345_RANGE_2_G,AUSEX_ADXL345_DATARATE_100_HZ));
  
  /* Display additional settings (outside the scope of sensor_t) */
  Serial.println("New sampling rate and range");
  displayDataRate();
  displayRange();
  Serial.println("");
}

void loop(void) 
{
  /* Get a new sensor event */ 
  sensors_event_t event; 
  accel.getEvent(&event);
 
  /* Display the results (acceleration is measured in m/s^2) */
  outputDevice.EventOutput(event);
  delay(500);
}
