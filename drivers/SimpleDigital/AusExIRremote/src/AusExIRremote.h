#ifndef __AUSEX_IR_REMOTE_H__
#define __AUSEX_IR_REMOTE_H__



#define AUSEX_IRREMOTE_CLASS AusExIrRemote
#define AUSEX_IRREMOTE_NAME "IrRemote"
#define AUSEX_IRREMOTE_TYPE SENSOR_TYPE_IRREMOTE
#define AUSEX_IRREMOTE_LIBRARY_VERSION 1
#define AUSEX_IRREMOTE_RETURN_VALUE irremote
#define AUSEX_IRREMOTE_VALUE_TYPE sensors_irremote_t
#define AUSEX_IRREMOTE_MIN_VALUE 0
#define AUSEX_IRREMOTE_MAX_VALUE 1
#define AUSEX_IRREMOTE_RESOLUTION 1
#define AUSEX_IRREMOTE_MIN_DELAY 0
#define AUSEX_IRREMOTE_INIT_DELAY 0

#include "AusEx.h"
#include <IRremote.h>


class AUSEX_IRREMOTE_CLASS : public Adafruit_SensorEx {
public:
  AUSEX_IRREMOTE_CLASS(int, int32_t sensorID = -1);
  bool begin(void);
  bool getEvent(sensors_event_t*);
  void getSensor(sensor_t*);
  bool enableAutoRange(bool);
  int setMode(int);
  int getMode();

private:
  IRrecv _irrecv;
  int32_t _sensorID;
  bool convertValue(decode_results * results, sensors_event_t * event);
};



#endif /* __AUSEX_IR_REMOTE_H__ */
