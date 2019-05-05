#ifndef __AUSEX_SERIAL_TEMPLATE_H__
#define __AUSEX_SERIAL_TEMPLATE_H__

#define AUSEX_SERIAL_TEMPLATE_CLASS AusExSerialTemplate
#define AUSEX_SERIAL_TEMPLATE_SENSOR_NAME "AusExSerialTemplate"
#define AUSEX_SERIAL_TEMPLATE_SENSOR_TYPE SENSOR_TYPE_SIMPLE
#define AUSEX_SERIAL_TEMPLATE_SENSOR_LIBRARY_VERSION 1
#define AUSEX_SERIAL_TEMPLATE_SENSOR_RETURN_VALUE value
#define AUSEX_SERIAL_TEMPLATE_SENSOR_VALUE_TYPE uint32_t
#define AUSEX_SERIAL_TEMPLATE_SENSOR_MIN_VALUE 0
#define AUSEX_SERIAL_TEMPLATE_SENSOR_MAX_VALUE 1
#define AUSEX_SERIAL_TEMPLATE_SENSOR_RESOLUTION 1
#define AUSEX_SERIAL_TEMPLATE_SENSOR_MIN_DELAY 0
#define AUSEX_SERIAL_TEMPLATE_SENSOR_INIT_DELAY 0

#define AUSEX_SERIAL_TEMPLATE_MAX_DATA_STRING 512

#include "AusEx.h"
#include <SoftwareSerial.h>



class AUSEX_SERIAL_TEMPLATE_CLASS : public Adafruit_SensorEx {
public:
  AUSEX_SERIAL_TEMPLATE_CLASS(int32_t sensorID = -1);
  AUSEX_SERIAL_TEMPLATE_CLASS(HardwareSerial *port, int32_t sensorID = -1);
  AUSEX_SERIAL_TEMPLATE_CLASS(SoftwareSerial *port, int32_t sensorID = -1);
  AUSEX_SERIAL_TEMPLATE_CLASS(SoftwareSerial *port, bool multi, int32_t sensorID = -1);
  bool begin(long baud);
  bool begin(long baud, byte s_config);
  bool getEvent(sensors_event_t*);
  void getSensor(sensor_t*);
  bool enableAutoRange(bool enabled);
  int setMode(int mode);
  int getMode();

private:
  SoftwareSerial *_port;
  HardwareSerial *_h_port;
  uint8_t mode; /* 0:ハードシリアル, 1:ソフトシリアル 2:ソフトシリアルかつマルチポート */
  bool _multi;
  int32_t _sensorID;

  AUSEX_SERIAL_TEMPLATE_SENSOR_VALUE_TYPE calcValue(String);
  bool _autoRange;
  String read(void);
  String readHard(void);
};



#endif /* __AUSEX_SERIAL_TEMPLATE_H__ */
