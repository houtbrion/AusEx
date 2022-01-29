
#define USE_DHCP                 // IPアドレスをDHCPで行う (コメントアウトした場合は固定IP)
#define USE_NTP                  // NTPで時刻を合わせる場合
//#define USE_RTC                  // RTCを使うか否か

#include "AusExOutputPlugin.h"
#include "AusExAM232X.h"

#define SSID_STR "foo"
#define WIFI_PASS "bar"

#include <ArduinoHttpClient.h>

#if defined(USE_NTP) && defined(USE_RTC)
#error "do not define USE_NTP and USE_RTC togather."
#endif /* USE_NTP && USE_RTC */

#ifdef USE_RTC
#include "RTC_8564NB_U.h"
#else /* USE_RTC */
#include "RTC_U.h"
#endif /* USE_RTC */


#define WAIT_TIME 5000           // 測定の待ち時間

#define HOSTNAME "esp32"   // syslog形式のログ出力に利用
#define APP_NAME "foo"           // syslog形式のログ出力に利用

#include <WiFi.h>

#ifdef USE_NTP
#include <WiFiUdp.h>
#include <NTPClient.h>
#endif /* USE_NTP */

/*
   ネットワーク関係の設定
   注意 : DHCPでのアドレス取得失敗時の対策や，長時間経過後のアドレス再割当て等は対応していない
*/

char serverAddress[] = "192.168.1.213";  // server address
int port = 80;

#ifdef USE_DHCP
boolean useDhcp = true;   // DHCPでIPアドレスを設定
#else /* USE_DHCP */
boolean useDhcp = false;  // 固定IPアドレス
#endif /* USE_DHCP */

/* 以下は固定IP運用の場合の変数なので適宜変更して使用すること */
IPAddress ip(192, 168, 1, 222);
IPAddress dnsServer(192, 168, 1, 1);
IPAddress gatewayAddress(192, 168, 1, 1);
IPAddress netMask(255, 255, 255, 0);

#if defined(USE_NTP) || defined(USE_RTC)
unsigned long currentTime;
#endif /* USE_NTP or USE_RTC */

#ifdef USE_NTP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, 9 * 60 * 60); // JST
#endif /* USE_NTP */

#ifdef USE_RTC
RTC_8564NB_U rtc = RTC_8564NB_U(&Wire);
#endif /* USE_RTC */

WiFiClient wifiClient;
HttpClient client = HttpClient(wifiClient, serverAddress, port);

AuxExSensorIO outputDevice =  AuxExSensorIO();
AusExAM232X am232x = AusExAM232X(&Wire, AM2321);

OutputChannel channel;

//
// 本体をリセットする関数
//
void reboot() {
  ESP.restart();
}


void setup() {
  Serial.begin(9600) ;    // シリアル通信の初期化
  while (!Serial) {       // シリアルポートが開くのを待つ
    ;
  }
  Serial.println("setup start.");
  channel.serial= &Serial;
  outputDevice.SetIO(AUSEX_OUTPUT_CHANNEL_SERIAL, channel, FORMAT_TYPE_PLAIN_TEXT);
  //outputDevice.SetIO(AUSEX_OUTPUT_CHANNEL_SERIAL, channel, FORMAT_TYPE_SYSLOG);
  //outputDevice.SetLogParam(HOSTNAME, APP_NAME);

#ifdef USE_RTC
  if (rtc.begin()) {
    Serial.println("Successful initialization of the RTC"); // 初期化成功
  } else {
    Serial.print("Failed initialization of the RTC");  // 初期化失敗
    reboot();
  }
#endif /* USE_RTC */

  date_t dateTime;

  // MACアドレスとIPアドレスの設定
  // 参考URL http://arduino.cc/en/Reference/EthernetBegin
  if (useDhcp) {
    WiFi.begin(SSID_STR, WIFI_PASS);

    while ( WiFi.status() != WL_CONNECTED ) {
      delay ( 500 );
      Serial.print ( "." );
    }
  } else {
    WiFi.config(ip, dnsServer, gatewayAddress, netMask);
    WiFi.begin(SSID_STR, WIFI_PASS);
    while ( WiFi.status() != WL_CONNECTED ) {
      delay ( 500 );
      Serial.print ( "." );
    }

    Serial.println(F("network setup done"));
  }
  Serial.print(F("IP address : ")); Serial.println(WiFi.localIP());
  Serial.println(F("network setup done"));

#ifdef USE_NTP
  timeClient.begin();
#endif /* USE_NTP */


#ifdef USE_RTC
  outputDevice.SetRtc(&rtc);
#endif /* USE_RTC */

  // Initialize device.
  am232x.begin();
  Serial.println(F("AM232X Unified Sensor Example"));
  // Print temperature sensor details.
  sensor_t sensor;
  am232x.temperature().getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
  // Print humidity sensor details.
  am232x.humidity().getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
}

void loop() {
  delay(WAIT_TIME); // am232xは測定の周波数が非常に長いため，連続してアクセスできないように，待ち時間をはさむ
  channel.httpClient= &client;
  outputDevice.SetIO(AUSEX_OUTPUT_CHANNEL_HTTP_CLIENT , channel, FORMAT_TYPE_JSON);
  //
  Serial.println("making PUT request");
  outputDevice.SetHttpPostParam("/sensor-data", "application/json");

  // Get temperature event and print its value.
  sensors_event_t event;
#ifdef USE_NTP
  timeClient.update();
  currentTime = timeClient.getEpochTime();
#endif /* USE_NTP */
#ifdef USE_RTC
  date_t dateTime;
  rtc.getTime(&dateTime);
  currentTime = rtc.convertDateToEpoch(dateTime);
#endif /* USE_RTC */

  Serial.println("read temperature");
  am232x.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  } else {
#if defined(USE_NTP) || defined(USE_RTC)
    event.timestamp=currentTime;
#endif /* USE_NTP or USE_RTC */
    Serial.println("output temperature");
    outputDevice.EventOutput(event);
    int statusCode = client.responseStatusCode();
    String response = client.responseBody();
    Serial.print("Status code: ");
    Serial.println(statusCode);
    Serial.print("Response: ");
    Serial.println(response);
  }
  Serial.println("read humidity");
  // Get humidity event and print its value.
  outputDevice.SetHttpPostParam("/sensor-data2", "application/json");
  am232x.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  } else {
#if defined(USE_NTP) || defined(USE_RTC)
    event.timestamp=currentTime;
#endif /* USE_NTP or USE_RTC */
    Serial.println("output humidity");
    outputDevice.EventOutput(event);
    int statusCode = client.responseStatusCode();
    String response = client.responseBody();
    Serial.print("Status code: ");
    Serial.println(statusCode);
    Serial.print("Response: ");
    Serial.println(response);
  }
}
