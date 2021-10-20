# AusExOutputPlugin : センサ情報出力プラクライン

本ライブラリは，AusExセンサライブラリで取得できるセンサの情報を出力するプログラムを簡単に作ることができるようにするライブラリです．



## 使い方

下のプログラムは温湿度センサ(DHT22)を使って，温度を出力する例です．
```
AuxExSensorIO outputDevice =  AuxExSensorIO();     // センサ情報を出力するオブジェクトを作成
AusExDHT dht = AusExDHT(2, DHT22);                 // 温湿度センサ DHT22 はデジタルの2番ピンに接続

// ハードウェアシリアルをセンサ情報を出力するI/Oチャンネルに定義
OutputChannel channel;
channel.serial= &Serial;

Serial.begin(9600);  // シリアルの初期化

// センサ情報の出力先「channel」とフォーマットを設定．
//outputDevice.SetIO(AUSEX_OUTPUT_CHANNEL_SERIAL, channel, FORMAT_TYPE_SYSLOG);
outputDevice.SetIO(AUSEX_OUTPUT_CHANNEL_SERIAL, channel, FORMAT_TYPE_PLAIN_TEXT);
//outputDevice.SetIO(AUSEX_OUTPUT_CHANNEL_SERIAL, channel, FORMAT_TYPE_JSON);
//outputDevice.SetLogParam("localhost", "TestApp");   // フォーマットがsyslogの時のみ必要

dht.begin();        // センサの初期化

sensor_t sensor;
dht.temperature().getSensor(&sensor);　　// 温度センサの情報を取得
outputDevice.InfoOutput(sensor);         // 取得したセンサの情報を出力

sensors_event_t event;
dht.temperature().getEvent(&event);      // 温度を測定
outputDevice.EventOutput(event);         // 測定結果を出力
```

上のプログラムでは，フォーマットをプレーンテキストにしており，次のような出力が得られる．
```
Temperature Sensor
Sensor Type: DHT22
Driver Ver:  1
Unique ID:   -1
Max Value:   125.00C
Min Value:   -40.00C
Resolution:  0.10C

Sensor_ID=-1
Sensor_Type=13
Data_Time=1215230851
Temperature=21.90C
```

フォーマットをJSONにした場合の出力は以下の通り．
```
{
"type": 13,
"name": "DHT22",
"version": 1,
"id":   -1,
"max_value":   125.00,
"min_value":   -40.00,
"resolution":  0.10
}

{
"id": -1,
"type": 13,
"time": 1215230682,
"data": [
{
"temperature": 21.90,
"unit": 2}
]
}
```

syslogフォーマットを定義した場合は下のような出力が得られる．時刻がUNIXのsyslogと異なるのは，OSやハードに時計がないため起動時からの経過ミリ秒を用いているためです．
```
0 localhost TestApp : Temperature Sensor
0 localhost TestApp : Sensor Type: DHT22
0 localhost TestApp : Driver Ver:  1
0 localhost TestApp : Unique ID:   -1
0 localhost TestApp : Max Value:   125.00C
0 localhost TestApp : Min Value:   -40.00C
0 localhost TestApp : Resolution:  0.10C

2595 localhost TestApp : Sensor_ID=-1
2595 localhost TestApp : Sensor_Type=13
2595 localhost TestApp : Data_Time=2595
2595 localhost TestApp : Temperature=21.90C
```

このライブラリのsyslogフォーマットはRTCを使う機能も持っており，RTCと連携すると下のような出力となります．
```
2021/10/18 Mon 18:49:26 localhost TestApp : Temperature Sensor
2021/10/18 Mon 18:49:26 localhost TestApp : Sensor Type: DHT22
2021/10/18 Mon 18:49:26 localhost TestApp : Driver Ver:  1
2021/10/18 Mon 18:49:26 localhost TestApp : Unique ID:   -1
2021/10/18 Mon 18:49:26 localhost TestApp : Max Value:   125.00C
2021/10/18 Mon 18:49:26 localhost TestApp : Min Value:   -40.00C
2021/10/18 Mon 18:49:26 localhost TestApp : Resolution:  0.10C

2021/10/18 Mon 18:49:29 localhost TestApp : Sensor_ID=-1
2021/10/18 Mon 18:49:29 localhost TestApp : Sensor_Type=13
2021/10/18 Mon 18:49:29 localhost TestApp : Data_Time=1634582969
2021/10/18 Mon 18:49:29 localhost TestApp : Temperature=22.10C
```


## 出力チャンネルの選択

**指定方法**
```
出力デバイスオブジェクト.SetIO(出力チャンネルの種類, 出力チャンネル, 出力フォーマット);
```

**例**
```
outputDevice.SetIO(AUSEX_OUTPUT_CHANNEL_SERIAL, channel, FORMAT_TYPE_SYSLOG);
```

### 指定できるチャンネルの種類
``SetIO()``の第1引数で下の表のいずれかを指定．
|出力チャンネルの種類|指定方法(マクロ)|
|---|---|
|ハードウェアシリアル|AUSEX_OUTPUT_CHANNEL_SERIAL|
|ソフトウェアシリアル|AUSEX_OUTPUT_CHANNEL_SOFT_SERIAL|
|マイクロSD上のファイル|AUSEX_OUTPUT_CHANNEL_FILE|
|tcpソケット(サーバ側)|AUSEX_OUTPUT_CHANNEL_ETHERNET_CLIENT|
|HTTPクライアント|AUSEX_OUTPUT_CHANNEL_HTTP_CLIENT|
|MQTTクライアント|AUSEX_OUTPUT_CHANNEL_MQTT_CLIENT|

第2引数でチャンネルを指定するが，ハードウェアシリアルやマイクロSDのファイルを直接渡すのではなく，
下のように``OutputChannel``型の変数のメンバにハードウェアシリアル等のポインタを代入した上で
``SetIO()``の第2引数とする．下はハードウェアシリアルの例．
```
OutputChannel channel;
channel.serial= &Serial;
```
なお，``OutputChannel``型の変数のメンバは以下の通り．
```
typedef union OutputChannel {
	File * file;
	HardwareSerial * serial;
    SoftwareSerial * sserial;
    EthernetClient * client;
    HttpClient * httpClient;
    MqttClient * mqttClient;
};
```

### ライブラリの``config.h``
すべてのチャンネルを有効にすると，オブジェクトサイズが非常に大きくなり，Arduino Megaのフラッシュサイズより大きくなってしまいます．
不要な機能をオブジェクトに入れないため，本ライブラリの``src``ディレクトリ内の``config.h``(下はその内容)を編集し，利用しないチャネルに
対応する定義をコメントアウトしてください．

また，最後の``__USE_RTC__``はsyslog形式で時刻情報を出力したい場合以外はかならずコメントアウトしてください．
ArduinoのEthernetシールドを利用しており，プログラム中でRTCを使わないにも関わらず，``config.h``で``__USE_RTC__``を生かしていると，
イーサネットが正しく動作しなくなります．
```
#define __USE_SD__              /* ログ出力先にSD/microSDカードを使う */
#define __USE_SERIAL__          /* ログ出力先にシリアルを使う */
#define __USE_SOFT_SERIAL__     /* ログ出力先にソフトシリアルを使う */
#define __USE_ETHERNET_CLIENT__ /* ログ出力先にTCPコネクション(server側)を使う */
#define __USE_HTTP_CLIENT__     /* ログ出力先にHTTP Clientを使う */
#define __USE_MQTT_CLIENT__     /* ログ出力先にHTTP Clientを使う */

#define __USE_RTC__             /* ログの時刻情報の取得にRTCを使う */
```

### TCPソケット(サーバ側)を利用する場合
TCPソケットのサーバ側を出力チャンネルに利用するのは，主にArduinoをHTTPサーバにすることを想定して
作成しました．

サーバをArduinoで立ち上げて，つないできたclientを出力チャンネルにし，HTTPのヘッダ部分は自力で出力した後，
センサデータをこのライブラリの機能を使って出力します．下は，非常に単純化したサンプルですが，httpのネゴシエーションの処理なども必要になるので，
詳細は``example/AusExDHT_WebServer``を参照してください．
```
EthernetServer server(80);  // サーバオブジェクトの定義． 引数はポート番号
OutputChannel channel;      //　チャンネルを定義
server.begin();             // TCPのサーバを80番ポートで立ち上げる．

EthernetClient client = server.available(); //接続してきたクライアントをclientとして定義
channel.client= &client;                    // 出力チャンネルに接続してきたclient利用

// 出力フォーマットプレーンテキストで，出力先はつなぎに来たクライアントをライブラリに設定
outputDevice.SetIO(AUSEX_OUTPUT_CHANNEL_ETHERNET_CLIENT , channel, FORMAT_TYPE_PLAIN_TEXT);

// HTTPのレスポンスのヘッダ生成してクライアントに送信
client.println("HTTP/1.1 200 OK");
//返答する文字コードの定義
client.println(F("Content-Type: text/plain; charset=UTF-8")); // UTF-8
client.println(F("Connection: close"));  // the connection will be closed after completion of the response
client.println(F("Refresh: 10"));  // refresh the page automatically every 10 sec
client.println();

// センサで測定
sensors_event_t event;
dht.temperature().getEvent(&event);

// 測定結果をクライアントに送信
outputDevice.EventOutput(event);

// クライアントとの接続を切断
client.stop();
```

### Arduinoをhttpクライアントにする場合
Webサーバにpostメソッドを使って，arduinoで測定したデータをアップロードすることを想定して作成しました．
この機能は[ArduinoHttpClient][ArduinoHttpClient]を利用しているので，インストールしてください．

チャンネルをhttpクライアントにし，HTTPではpostメソッドを使うため，そのパラメータを下のAPIで登録する．
```
void SetIO(uint8_t type, OutputChannel outputChannel, format_type_t format=FORMAT_TYPE_PLAIN_TEXT);
void SetHttpPostParam(String url_Path, String typeString=DEFAULT_CONTENT_TYPE);
```
**例**
```
outputDevice.SetIO(AUSEX_OUTPUT_CHANNEL_HTTP_CLIENT , channel, FORMAT_TYPE_JSON);
outputDevice.SetHttpPostParam("/sensor-data", "application/json");
```
デフォルトのtypeは「application/json;charset=utf8」であるため，同じtypeを使う場合は指定する必要がない．

下に非常に単純化したサンプルを示しますが，
詳細は``example/AusExDHT_HttpClient``を参照してください．

```
EthernetClient etherClient;
HttpClient client = HttpClient(etherClient, serverAddress, port);

AusExDHT dht = AusExDHT(SENSOR_PIN,DHTTYPE);
dht.begin();

AuxExSensorIO outputDevice =  AuxExSensorIO();
OutputChannel channel;

channel.httpClient= &client;
outputDevice.SetIO(AUSEX_OUTPUT_CHANNEL_HTTP_CLIENT , channel, FORMAT_TYPE_JSON);
outputDevice.SetHttpPostParam("/sensor-data", "application/json");

sensors_event_t event;
dht.temperature().getEvent(&event);
outputDevice.EventOutput(event);
```

### ArduinoをMQTTクライアントにする場合
MQTTブローカに測定したデータをアップロードすることを想定し，[ArduinoMqttClient][ArduinoMqttClient]を
使う機能を実装しています．そのため，ArduinoのMQTTライブラリ[ArduinoMqttClient][ArduinoMqttClient]をインストールしておいてください．

```
void SetMqttTopic(char * topic);
void SetMessageParam(unsigned long size, bool retain = false, uint8_t qos =0, bool dup = false);
```

実際の使用例は``example/AusExDHT_MqttClient``を参照してください．

## 出力フォーマットの選択
``SetIO()``の第3引数にフォーマットを指定することで，syslog形式, プレーンテキスト, JSON形式を選択することができる．
```
void SetIO(uint8_t type, OutputChannel outputChannel, format_type_t format=FORMAT_TYPE_PLAIN_TEXT);
```
第3引数で指定可能なパラメータは以下の3種類．
|フォーマット | 指定方法 |
|---|---|
| syslog形式 | FORMAT_TYPE_SYSLOG |
| プレーンテキスト | FORMAT_TYPE_PLAIN_TEXT |
| JSON形式 | FORMAT_TYPE_JSON |

### syslogフォーマットを利用する場合
syslogフォーマットを利用する場合，String型でホスト名に相当する部分とアプリ名に相当する部分を定義してください．
```
void SetLogParam(String defaultHostName=LOG_HEADER, String defaultAppName=LOG_HEADER);
```
**例**
```
outputDevice.SetLogParam("localhost", "TestApp");   // フォーマットがsyslogの時のみ必要
```

先にも実行例をあげましたが，RTCを使って時刻情報をsyslogに入れることができます．
```
2021/10/18 Mon 18:49:26 localhost TestApp : Temperature Sensor
```

この場合，``config.h``で``__USE_RTC__``を有効にする他，RTC用ライブラリとして[RTC_U][RTC_U]を使う必要があるため，
libraryをインストールしてください．現在，[RTC_U][RTC_U]で利用可能なRTCとしては，EPSON 8564NB, DS1307, DS3234があります．

また，Arduinoのプログラムで以下のAPIを使って，RTCを登録する必要があります．

```
void SetRtc(RTC_Unified *rtcObject);
```
**EPSON 8564NBを利用する事例**
```
RTC_8564NB_U rtc = RTC_8564NB_U(&Wire);
rtc.begin();
outputDevice.SetRtc(&rtc);
```

## サンプルプログラム
すべのプログラムは，DHTシリーズの温湿度センサを使うものとなっています．
- AusExDHT_HttpClient : webサーバにjsonで測定結果をpostするプログラム
- AusExDHT_MqttClient : mqttで測定をpublishするプログラム
- AusExDHT_WebServer : httpアクセスしてきたクライアントにプレーンテキストやjsonで測定結果を返すプログラム
- AusExDHT_terminal : 測定結果をシリアル/ソフトシリアル/SD上のログファイルに書き込むプログラム


## 外部リンク
- Adafruit Unified Sensor Driver - [https://github.com/adafruit/Adafruit_Sensor][AdafruitUSD]
- RTC-8564NB - [https://www5.epsondevice.com/ja/products/rtc/rtc8564nb.html][RTC8564NB]
- 秋月電子8564NB搭載モジュール - [http://akizukidenshi.com/catalog/g/gI-00233/][AkizukiRTC8564NB]
- DS1307 - [https://www.maximintegrated.com/jp/products/analog/real-time-clocks/DS1307.html][DS1307]
- Grove RTC - [https://www.seeedstudio.com/Grove-RTC.html][GroveRTC]
- DS3234 - [https://www.maximintegrated.com/jp/products/analog/real-time-clocks/DS3234.html][DS3234]
- SparkFun DeadOn RTC Breakout DS3234 - [https://www.sparkfun.com/products/10160][BOB-10160]
- RTC APIライブラリ - [https://github.com/houtbrion/RTC_U][RTC_U]


[RTC_U]:https://github.com/houtbrion/RTC_U
[ArduinoHttpClient]:https://github.com/arduino-libraries/ArduinoHttpClient
[ArduinoMqttClient]:https://github.com/arduino-libraries/ArduinoMqttClient


