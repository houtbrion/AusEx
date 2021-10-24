
#define USE_DHCP                 // IPアドレスをDHCPで行う (コメントアウトした場合は固定IP)
//#define USE_NTP                  // NTPで時刻を合わせる場合
//#define USE_RTC                  // RTCを使うか否か

#include "AusExOutputPlugin.h"
#include "AusExAM232X.h"

#define SSID_STR "foo"
#define WIFI_PASS "bar"

#if defined(USE_NTP) && defined(USE_RTC)
#error "do not define USE_NTP and USE_RTC togather."
#endif /* USE_NTP && USE_RTC */

#ifdef USE_RTC
#include "RTC_8564NB_U.h"
#else /* USE_RTC */
#include "RTC_U.h"
#endif /* USE_RTC */

#define WAIT_TIME 1000           // 測定の待ち時間

#define HOSTNAME "arduinoMega"   // syslog形式のログ出力に利用
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

//EthernetServer server(80); // サーバオブジェクトの定義． 引数はポート番号
WiFiServer server(80); // サーバオブジェクトの定義． 引数はポート番号
AuxExSensorIO outputDevice =  AuxExSensorIO();
AusExAM232X am232x = AusExAM232X(&Wire, AM2321);


OutputChannel channel;

//
// 本体をリセットする関数
//
void reboot() {
  //asm volatile ("  jmp 0");
  ESP.restart();
}

void setup() {
  Serial.begin(9600) ;    // シリアル通信の初期化
  while (!Serial) {       // シリアルポートが開くのを待つ
    ;
  }
  Serial.println("setup start.");
  //channel.serial= &Serial;
  //outputDevice.SetIO(AUSEX_OUTPUT_CHANNEL_SERIAL, channel, FORMAT_TYPE_SYSLOG);
  //outputDevice.SetIO(AUSEX_OUTPUT_CHANNEL_SERIAL , channel, FORMAT_TYPE_PLAIN_TEXT);
  //outputDevice.SetLogParam(HOSTNAME, APP_NAME);
  //outputDevice.SetLogParam("a", "a");
  //outputDevice.SetIO(AUSEX_OUTPUT_CHANNEL_SERIAL , channel, FORMAT_TYPE_JSON);

#ifdef USE_RTC
  if (rtc.begin()) {
    Serial.println("Successful initialization of the RTC"); // 初期化成功
  } else {
    Serial.print("Failed initialization of the RTC");  // 初期化失敗
    reboot();
  }
#endif /* USE_RTC */

  rtc_date_t dateTime;

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
  }
  Serial.print(F("IP address : ")); Serial.println(WiFi.localIP());
  Serial.println(F("network setup done"));
#ifdef USE_NTP
  timeClient.begin();
#endif /* USE_NTP */

#ifdef USE_RTC
  outputDevice.SetRtc(&rtc);
#endif /* USE_RTC */


  server.begin();
  // Initialize device.
  am232x.begin();
  Serial.println(F("am232xxx Unified Sensor Example"));
  // Print temperature sensor details.
  //sensor_t sensor;
  //am232x.temperature().getSensor(&sensor);
  //outputDevice.InfoOutput(sensor);
  // Print humidity sensor details.
  //am232x.humidity().getSensor(&sensor);
  //outputDevice.InfoOutput(sensor);

}

void loop() {
  // 接続してきたクライアントを示すオブジェクトを生成
  //EthernetClient client = server.available();
  WiFiClient client = server.available();
  if (client) {
    channel.wifi_client= &client;
    //outputDevice.SetIO(AUSEX_OUTPUT_CHANNEL_WIFI_CLIENT , channel, FORMAT_TYPE_PLAIN_TEXT);
    outputDevice.SetIO(AUSEX_OUTPUT_CHANNEL_WIFI_CLIENT , channel, FORMAT_TYPE_JSON);
    //outputDevice.SetIO(AUSEX_OUTPUT_CHANNEL_SERIAL , channel, FORMAT_TYPE_SYSLOG);
    //outputDevice.SetLogParam(HOSTNAME, APP_NAME);
    //outputDevice.SetIO(AUSEX_OUTPUT_CHANNEL_SERIAL , channel, FORMAT_TYPE_PLAIN_TEXT);
    delay(WAIT_TIME); // am232xは測定の周波数が非常に長いため，連続してアクセスできないように，待ち時間をはさむ
    Serial.println(F("Connection established by a client"));
    // an http request ends with a blank line
    uint8_t endToken = 0;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read(); //一文字読み取り
        if (c == '\n' && endToken == 3) {
          Serial.println(F("generate output for client."));
          // HTTPのレスポンスのヘッダ生成
          client.println("HTTP/1.1 200 OK");
          //返答する文字コードの定義
          //client.println(F("Content-Type: text/plain; charset=iso-2022-jp")); // JIS
          //client.println(F("Content-Type: text/plain; charset=shift_jis")); // SJIS
          //client.println(F("Content-Type: text/plain; charset=euc-jp")); // EUC
          //client.println(F("Content-Type: text/plain; charset=UTF-8")); // UTF-8
          //client.println(F("Content-Type: text/plain"));  // 定義なし
          client.println(F("Content-Type: text/json"));  // 定義なし
          client.println(F("Connection: close"));  // the connection will be closed after completion of the response
          client.println(F("Refresh: 10"));  // refresh the page automatically every 10 sec
          client.println();
          Serial.println("generate header . done.");
          // Get temperature event and print its value.
          sensors_event_t event;
#ifdef USE_NTP
          timeClient.update();
          currentTime = timeClient.getEpochTime();
#endif /* USE_NTP */
#ifdef USE_RTC
          rtc_date_t dateTime;
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
            Serial.println("output temperature  .. done");
          }
          Serial.println("read humidity");
          // Get humidity event and print its value.
          am232x.humidity().getEvent(&event);
          if (isnan(event.relative_humidity)) {
            Serial.println(F("Error reading humidity!"));
          } else {
#if defined(USE_NTP) || defined(USE_RTC)
            event.timestamp=currentTime;
#endif /* USE_NTP or USE_RTC */
            Serial.println("output humidity");
            outputDevice.EventOutput(event);
            Serial.println("output humidity  .. done.");
          }
          Serial.println("generate response . done.");
          break;
        }
        if (c == '\n') {
          switch (endToken) {
            case 1: endToken++;break;
            default: endToken=0;
          }
        } else if (c == '\r') {
          // CR
          switch (endToken) {
            case 0: endToken++;break;
            case 2: endToken++;break;
            default: endToken=0;
          }
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
  }
}
