
#define USE_DHCP                 // IPアドレスをDHCPで行う (コメントアウトした場合は固定IP)
//#define USE_NTP                  // NTPで時刻を合わせる場合
#define USE_RTC                  // RTCを使うか否か

#include "AusExOutputPlugin.h"
#include "AusExDHT.h"

#if defined(USE_NTP) && defined(USE_RTC)
#error "do not define USE_NTP and USE_RTC togather."
#endif /* USE_NTP && USE_RTC */

#include <ArduinoMqttClient.h>

#ifdef USE_RTC
#include "RTC_8564NB_U.h"
#else /* USE_RTC */
#include "RTC_U.h"
#endif /* USE_RTC */

#define SENSOR_PIN 2             // センサはデジタルの2番ピンに接続
// センサの種別の選択
//#define DHTTYPE    DHT11       // DHT 11
#define DHTTYPE    DHT22       // DHT 22 (AM2302)
//#define DHTTYPE    DHT21       // DHT 21 (AM2301)

#define WAIT_TIME 10000           // 測定の待ち時間

#define HOSTNAME "arduinoMega"   // syslog形式のログ出力に利用
#define APP_NAME "foo"           // syslog形式のログ出力に利用

#include <Ethernet.h>

#ifdef USE_NTP
#include <EthernetUdp.h>
#include <NTPClient.h>
#endif /* USE_NTP */

/*
   ネットワーク関係の設定
   注意 : DHCPでのアドレス取得失敗時の対策や，長時間経過後のアドレス再割当て等は対応していない
*/
//byte mac[] = { 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff }; //アドレスは手持ちのarduinoやシールドのモノに変更すること
byte mac[] = { 0x90, 0xa2, 0xda, 0x10, 0x11, 0x51 }; //アドレスは手持ちのarduinoのものに変更すること

char serverAddress[] = "192.168.1.213";  // server address
int port = 1883;
const char topic[]  = "test";

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
EthernetUDP ntpUDP;
NTPClient timeClient(ntpUDP, 9 * 60 * 60); // JST
#endif /* USE_NTP */

#ifdef USE_RTC
RTC_8564NB_U rtc = RTC_8564NB_U(&Wire);
#endif /* USE_RTC */

EthernetClient etherClient;
MqttClient mqttClient(etherClient);

AuxExSensorIO outputDevice =  AuxExSensorIO();
AusExDHT dht = AusExDHT(SENSOR_PIN,DHTTYPE);

OutputChannel channel;
uint8_t loopCount=0;

//
// 本体をリセットする関数
//
void reboot() {
  asm volatile ("  jmp 0");
}

void setup() {
  Serial.begin(9600) ;    // シリアル通信の初期化
  while (!Serial) {       // シリアルポートが開くのを待つ
    ;
  }
  Serial.println("setup start.");
  channel.serial= &Serial;
  outputDevice.SetIO(AUSEX_OUTPUT_CHANNEL_SERIAL, channel, FORMAT_TYPE_SYSLOG);
  outputDevice.SetLogParam(HOSTNAME, APP_NAME);

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
    if (Ethernet.begin(mac) == 0) {
      Serial.println(F("DHCP fail."));
      reboot();
    }
  } else {
    Ethernet.begin(mac, ip, dnsServer, gatewayAddress, netMask);
    Serial.println(F("ethernet setup done"));
  }
  Serial.print(F("IP address : ")); Serial.println(Ethernet.localIP());
  Serial.println(F("network setup done"));

#ifdef USE_NTP
  timeClient.begin();
#endif /* USE_NTP */


#ifdef USE_RTC
  outputDevice.SetRtc(&rtc);
#endif /* USE_RTC */

  // You can provide a unique client ID, if not set the library uses Arduino-millis()
  // Each client must have a unique client ID
  // mqttClient.setId("clientId");

  // You can provide a username and password for authentication
  // mqttClient.setUsernamePassword("username", "password");
  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(serverAddress);

  if (!mqttClient.connect(serverAddress, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
    reboot();
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

  // Initialize device.
  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  outputDevice.InfoOutput(sensor);
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  outputDevice.InfoOutput(sensor);

}

void loop() {
  delay(WAIT_TIME); // DHTは測定の周波数が非常に長いため，連続してアクセスできないように，待ち時間をはさむ
  mqttClient.poll();
  channel.mqttClient= &mqttClient;

  //outputDevice.SetIO(AUSEX_OUTPUT_CHANNEL_MQTT_CLIENT , channel, FORMAT_TYPE_JSON);
  outputDevice.SetIO(AUSEX_OUTPUT_CHANNEL_MQTT_CLIENT , channel, FORMAT_TYPE_PLAIN_TEXT);
  //
  Serial.println("making MQTT publish");
  outputDevice.SetMqttTopic(topic);

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
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  } else {
#if defined(USE_NTP) || defined(USE_RTC)
    event.timestamp=currentTime;
#endif /* USE_NTP or USE_RTC */
    Serial.println("output temperature");
    outputDevice.EventOutput(event);
  }
  Serial.println("read humidity");
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  } else {
#if defined(USE_NTP) || defined(USE_RTC)
    event.timestamp=currentTime;
#endif /* USE_NTP or USE_RTC */
    Serial.println("output humidity");
    outputDevice.EventOutput(event);
  }
}
