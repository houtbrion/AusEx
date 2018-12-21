#ifndef __SERIAL_TEMPLATE_AUSEX_H__
#define __SERIAL_TEMPLATE_AUSEX_H__

#define _TEMPLATE_CLASS serialTemplateAusEx
#define _SENSOR_NAME "serialTemplateAusEx"
#define _SENSOR_TYPE SENSOR_TYPE_SIMPLE
#define _SENSOR_LIBRARY_VERSION 1
#define _SENSOR_RETURN_VALUE value
#define _SENSOR_VALUE_TYPE uint32_t
#define _SENSOR_MIN_VALUE 0
#define _SENSOR_MAX_VALUE 1
#define _SENSOR_RESOLUTION 1
#define _SENSOR_MIN_DELAY 0

#define _MAX_DATA_STRING 512

#include "AusEx.h"
#include <SoftwareSerial.h>



class _TEMPLATE_CLASS : public Adafruit_SensorEx {
public:
  _TEMPLATE_CLASS(uint32_t sensorID = -1);
  _TEMPLATE_CLASS(HardwareSerial *port, uint32_t sensorID = -1);
  _TEMPLATE_CLASS(SoftwareSerial *port, uint32_t sensorID = -1);
  _TEMPLATE_CLASS(SoftwareSerial *port, bool multi, uint32_t sensorID = -1);
  bool begin(long baud);
  bool begin(long baud, byte s_config);
  bool getEvent(sensors_event_t*);
  void getSensor(sensor_t*);
  bool enableAutoRange(bool enabled);
  int setMode(int mode);

private:
  SoftwareSerial *_port;
  HardwareSerial *_h_port;
  uint8_t mode; /* 0:ハードシリアル, 1:ソフトシリアル 2:ソフトシリアルかつマルチポート */
  bool _multi;
  uint32_t _sensorID;

  _SENSOR_VALUE_TYPE calcValue(String);
  bool _autoRange;
  String read(void);
  String readHard(void);
};



#endif /* __SERIAL_TEMPLATE_AUSEX_H__ */
