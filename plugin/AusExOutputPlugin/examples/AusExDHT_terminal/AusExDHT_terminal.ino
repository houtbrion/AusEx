
//#define USE_DHCP                 // IPアドレスをDHCPで行う (コメントアウトした場合は固定IP)
//#define USE_NTP                  // NTPで時刻を合わせる場合
//#define USE_RTC                  // RTCを使うか否か
//#define USE_SOFT_SERIAL          // センサデータ出力先にソフトウェアシリアルを使う
#define USE_SD                   // SDカードにセンサのログを書き込む場合
//#define USE_HARD_SERIAL          // センサデータ出力先にハードウェアシリアルの1番(Serial)を使う

#if defined(USE_NTP) && defined(USE_RTC)
#error "do not define USE_NTP and USE_RTC togather."
#endif /* USE_NTP && USE_RTC */

#include "AusExOutputPlugin.h"
#include "AusExDHT.h"

#ifdef USE_SOFT_SERIAL
#include <SoftwareSerial.h>
#endif /* USE_SOFT_SERIAL */

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

#define LOG_FILE_NAME "log.txt"  // SDカードに書き込むログファイル名
#define SD_CHIP_SELECT 4         // SDのチップセレクトピン番号
#define CLEAR_FILE               // ブート時に古いログファイルを消す設定

#define SOFT_SERIAL_TX 6         // ソフトシリアルの送信ピン番号
#define SOFT_SERIAL_RX 7         // ソフトシリアルの受信ピン番号

#define WAIT_TIME 2000           // 測定の待ち時間　(3秒に一回測定)
#define LONG_WAIT 10000          // 1周期(下のLOOP_NUM回測定)の測定後に，ログファイルの内容をダンプした後の長い待ち時間
#define LOOP_NUM 5               // 1回の周期で何回センサの測定を行うかの設定

#define HOSTNAME "arduinoMega"   // syslog形式のログ出力に利用
#define APP_NAME "foo"           // syslog形式のログ出力に利用

// センサ測定結果の出力先選択
#ifdef USE_SD
#define AUSEX_OUTPUT_CHANNEL AUSEX_OUTPUT_CHANNEL_FILE
#endif /* USE_SD */
#ifdef USE_HARD_SERIAL
#define AUSEX_OUTPUT_CHANNEL AUSEX_OUTPUT_CHANNEL_SERIAL
#endif /* USE_HARD_SERIAL */
#ifdef USE_SOFT_SERIAL
#define AUSEX_OUTPUT_CHANNEL AUSEX_OUTPUT_CHANNEL_SOFT_SERIAL
#endif /* USE_SOFT_SERIAL */


#ifdef USE_NTP
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <NTPClient.h>

/*
   ネットワーク関係の設定
   注意 : DHCPでのアドレス取得失敗時の対策や，長時間経過後のアドレス再割当て等は対応していない
*/
//byte mac[] = { 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff }; //アドレスは手持ちのarduinoやシールドのモノに変更すること
byte mac[] = { 0x90, 0xa2, 0xda, 0x10, 0x11, 0x51 }; //アドレスは手持ちのarduinoのものに変更すること

#ifdef USE_DHCP
boolean useDhcp = true;   // DHCPでIPアドレスを設定
#else /* USE_DHCP */
boolean useDhcp = false;  // 固定IPアドレス
#endif /* USE_DHCP */

/* 以下は固定IP運用の場合の変数なので適宜変更して使用すること */
IPAddress ip(192, 168, 0, 201);
IPAddress dnsServer(192, 168, 0, 1);
IPAddress gatewayAddress(192, 168, 0, 1);
IPAddress netMask(255, 255, 255, 0);

EthernetUDP ntpUDP;
NTPClient timeClient(ntpUDP, 9 * 60 * 60); // JST
#endif /* USE_NTP */

#if defined(USE_NTP) || defined(USE_RTC)
unsigned long currentTime;
#endif /* USE_NTP or USE_RTC */

#ifdef USE_SD
File logFile;
#endif /* USE_SD */

#ifdef USE_RTC
RTC_8564NB_U rtc = RTC_8564NB_U(&Wire);
#endif /* USE_RTC */

#ifdef USE_SOFT_SERIAL
SoftwareSerial sSerial(SOFT_SERIAL_RX, SOFT_SERIAL_TX); // RX, TX
#endif /* USE_SOFT_SERIAL */

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

#ifdef USE_SD
bool seekEOF(File * file){
  return file->seek(file->size());
}

bool dumpFile(File * file) {
  if (file->seek(0)){
    while (file->available()) {
      Serial.write(file->read());
      if (file->position() == file->size()) {
        return true;
      }
    }
  } else {
    return false;
  }
}
#endif /* USE_SD */

void setup() {
  Serial.begin(9600) ;    // シリアル通信の初期化
  while (!Serial) {       // シリアルポートが開くのを待つ
    ;
  }
  Serial.println("setup start.");
#ifdef USE_SD
  if (!SD.begin(SD_CHIP_SELECT)) {
    Serial.println("initialization failed!");
    reboot();
  }
#ifdef CLEAR_FILE
  if (SD.exists(LOG_FILE_NAME)) {
    if (!SD.remove(LOG_FILE_NAME)) {
      Serial.println("Can not remove log file.");
      reboot();
    }
  }
#endif /* CLEAR_FILE */
  if (!(logFile = SD.open(LOG_FILE_NAME, FILE_READ | FILE_WRITE ))) {
    Serial.println("opening file failed!");
    reboot();
  }
  while (logFile.available()) {
    if (!seekEOF(&logFile)) {
      Serial.println("fail to seek of file.");
      reboot();
    } else {
      break;
    }
    Serial.println("wait to access the log file.");
  }
#endif /* USE_SD */

#ifdef USE_SD
  channel.file= &logFile;
#endif /* USE_SD */
#ifdef USE_HARD_SERIAL
  channel.serial= &Serial;
#endif /* USE_HARD_SERIAL*/
#ifdef USE_SOFT_SERIAL
  channel.sserial= &sSerial;
#endif /* USE_SOFT_SERIAL*/

  outputDevice.SetIO(AUSEX_OUTPUT_CHANNEL, channel, FORMAT_TYPE_SYSLOG);
  outputDevice.SetLogParam(HOSTNAME, APP_NAME);
  //outputDevice.SetIO(AUSEX_OUTPUT_CHANNEL, channel, FORMAT_TYPE_PLAIN_TEXT);
  //outputDevice.SetIO(AUSEX_OUTPUT_CHANNEL, channel, FORMAT_TYPE_JSON);

#ifdef USE_RTC
  if (rtc.begin()) {
    Serial.println("Successful initialization of the RTC"); // 初期化成功
  } else {
    Serial.print("Failed initialization of the RTC");  // 初期化失敗
    reboot();
  }
#endif /* USE_RTC */

  date_t dateTime;

#ifdef USE_NTP
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
  Serial.println(F("network setup done"));
  timeClient.begin();
#endif /* USE_NTP */

#ifdef USE_RTC
  outputDevice.SetRtc(&rtc);
#endif /* USE_RTC */

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
  // Delay between measurements.
  delay(WAIT_TIME);
  // Get temperature event and print its value.
  sensors_event_t event;
  Serial.println("******************");
#ifdef USE_NTP
  timeClient.update();
  currentTime = timeClient.getEpochTime();
#endif /* USE_NTP */
#ifdef USE_RTC
  date_t dateTime;
  rtc.getTime(&dateTime);
  currentTime = rtc.convertDateToEpoch(dateTime);
#endif /* USE_RTC */
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  } else {
#if defined(USE_NTP) || defined(USE_RTC)
    event.timestamp=currentTime;
#endif /* USE_NTP or USE_RTC */
    outputDevice.EventOutput(event);
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
#if defined(USE_NTP) || defined(USE_RTC)
    event.timestamp=currentTime;
#endif /* USE_NTP or USE_RTC */
    outputDevice.EventOutput(event);
  }

  loopCount++;
  if (loopCount == LOOP_NUM) {
    loopCount=0;
#ifdef USE_SD
    Serial.println("==========================");
    if (!dumpFile(&logFile)) {
      Serial.println("dump file fail.");
      reboot();
    }
    if (!seekEOF(&logFile)) {
      Serial.println("seek file fail");
      reboot();
    }
    Serial.println("==========================");
    delay(LONG_WAIT);
#endif /* USE_SD */
  }
}
