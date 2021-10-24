#ifndef __AUSEX_OUTPUT_PLUGIN_H__
#define __AUSEX_OUTPUT_PLUGIN_H__

#include "config.h"

#define AUSEX_OUTPUT_CHANNEL_SERIAL             1
#define AUSEX_OUTPUT_CHANNEL_SOFT_SERIAL        2
#define AUSEX_OUTPUT_CHANNEL_FILE               3
#define AUSEX_OUTPUT_CHANNEL_ETHERNET_CLIENT    4
#define AUSEX_OUTPUT_CHANNEL_WIFI_CLIENT        5
#define AUSEX_OUTPUT_CHANNEL_HTTP_CLIENT        6
#define AUSEX_OUTPUT_CHANNEL_MQTT_CLIENT        7

#define LOG_HEADER ""
//#define DEFAULT_CONTENT_TYPE "text/plain"
#define DEFAULT_CONTENT_TYPE "application/json;charset=utf8"

#if !defined(__USE_SD__) && !defined(__USE_SERIAL__) && !defined(__USE_SOFT_SERIAL__) && !defined(__USE_ETHERNET_CLIENT__) && !defined(__USE_WIFI_CLIENT__) && !defined(__USE_HTTP_CLIENT__) && !defined(__USE_MQTT_CLIENT__)
#error " you must define __USE_SD__ and/or __USE_SERIAL__ , __USE_SOFT_SERIAL__ , __USE_ETHERNET_CLIENT__ , __USE_WIFI_CLIENT__ , __USE_HTTP_CLIENT__ , __USE_MQTT_CLIENT__"
#endif /* not __USE_SD__ and not __USE_SERIAL__ and not __USE_SOFT_SERIAL__ and not __USE_ETHERNET_CLIENT__ and not __USE_WIFI_CLIENT__ and not __USE_HTTP_CLIENT__ and not __USE_MQTT_CLIENT__*/

#ifdef __USE_SD__
#include <SPI.h>
#include <SD.h>
#endif /* __USE_SD__ */

#ifdef __USE_SERIAL__
#include <HardwareSerial.h>
#endif /* __USE_SERIAL__ */

#ifdef __USE_SOFT_SERIAL__
#include <SoftwareSerial.h>
#endif /* __USE_SOFT_SERIAL__ */

#ifdef __USE_ETHERNET_CLIENT__
#include <Ethernet.h>
#endif /* __USE_ETHERNET_CLIENT__ */

#ifdef __USE_WIFI_CLIENT__
#include <WiFi.h>
#endif /* __USE_WIFI_CLIENT__ */

#ifdef __USE_HTTP_CLIENT__
//#include <Ethernet.h>
#include <ArduinoHttpClient.h>
#endif /* __USE_HTTP_CLIENT__ */

#ifdef __USE_MQTT_CLIENT__
//#include <Ethernet.h>
#include <ArduinoMqttClient.h>
#endif /* __USE_MQTT_CLIENT__ */

#ifdef __USE_RTC__
#include <RTC_U.h>
#endif /* __USE_RTC__ */

#include <AusEx.h>


#define AUSEX_OUTPUT_PLUGIN_LIBRARY_VERSION 0.1

typedef enum {
    FORMAT_TYPE_SYSLOG       = (1),
    FORMAT_TYPE_PLAIN_TEXT   = (2),
    FORMAT_TYPE_JSON         = (3)
} format_type_t;



typedef union OutputChannel {
#ifdef __USE_SD__
	File * file;
#endif /* __USE_SD__ */
#ifdef __USE_SERIAL__
	HardwareSerial * serial;
#endif /* __USE_SERIAL__ */
#ifdef __USE_SOFT_SERIAL__
    SoftwareSerial * sserial;
#endif /* __USE_SOFT_SERIAL__ */
#ifdef __USE_ETHERNET_CLIENT__
    EthernetClient * client;
#endif /* __USE_ETHERNET_CLIENT__ */
#ifdef __USE_WIFI_CLIENT__
    WiFiClient * wifi_client;
#endif /* __USE_WIFI_CLIENT__ */
#ifdef __USE_HTTP_CLIENT__
    HttpClient * httpClient;
#endif /* __USE_HTTP_CLIENT__ */
#ifdef __USE_MQTT_CLIENT__
    MqttClient * mqttClient;
#endif /* __USE_MQTT_CLIENT__ */
};

class AuxExSensorIO  {
    public:
        AuxExSensorIO();
        void SetIO(uint8_t type, OutputChannel outputChannel, format_type_t format=FORMAT_TYPE_PLAIN_TEXT);
        bool InfoOutput(sensor_t sensor);
        bool EventOutput(sensors_event_t event);
        void SetLogParam(String defaultHostName=LOG_HEADER, String defaultAppName=LOG_HEADER);
#ifdef __USE_RTC__
        void SetRtc(RTC_Unified *rtcObject);
#endif /* __USE_RTC__ */
#ifdef __USE_HTTP_CLIENT__
        void SetHttpPostParam(String url_Path, String typeString=DEFAULT_CONTENT_TYPE);
#endif /* __USE_HTTP_CLIENT__ */
#ifdef __USE_MQTT_CLIENT__
        void SetMqttTopic(char * topic);
        void SetMessageParam(unsigned long size, bool retain = false, uint8_t qos =0, bool dup = false);
#endif /* __USE_MQTT_CLIENT__ */

    private:
        bool InfoOutputPlain(sensor_t sensor);
        bool InfoOutputJson(sensor_t sensor);
        bool InfoOutputSyslog(sensor_t sensor);
        bool EventOutputPlain(sensors_event_t event);
        bool EventOutputJson(sensors_event_t event);
        bool EventOutputSyslog(sensors_event_t event);
        String getWday(uint8_t);
        uint8_t channelType;
        format_type_t formatType;
        OutputChannel channel;
        String hostName;
        String appName;
        //String[] wdayString = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
#ifdef __USE_HTTP_CLIENT__
        String contentType;
        String urlPath;
#endif /* __USE_HTTP_CLIENT__ */
#ifdef __USE_MQTT_CLIENT__
        //String topic;
        char * topic;
        unsigned long size;
        bool retain;
        uint8_t qos;
        bool dup;
#endif /* __USE_MQTT_CLIENT__ */
#ifdef __USE_RTC__
        RTC_Unified *rtc;
#endif /* __USE_RTC__ */

};



#endif /* __AUSEX_OUTPUT_PLUGIN_H__ */
