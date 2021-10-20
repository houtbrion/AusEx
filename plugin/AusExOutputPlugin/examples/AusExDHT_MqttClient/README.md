# AusExDHT_MqttClient

このサンプルプログラムは，arduinoをmqttクライアントにし，センサを用いた測定結果をmqttブローカにpublishするものとなっています．

このプログラムを使う場合は，このライブラリ(AusExOutputPlugin)の``config.h``で``#define __USE_MQTT_CLIENT__``を有効にすることを忘れないようにしてください．

## arduinoの準備
### 本プログラムソースの確認と修正
以下の7点を確認・編集してください．
- 動作確認したものは，Arduino Mega 2560R3にイーサネットシールドを載せ，温湿度センサとしてDHT22を用い，EPSON8564NBというRTCを用いる例となっています．
RTCを用いない場合，プログラム4行目の``#define USE_RTC``をコメントアウトして，3行目の``#define USE_NTP``を有効にしてください．
- 温湿度センサは，DHT22以外に，DHT11, DHT21が選べます．23から25行目でどれを使うか選択してください．
- 21行目を編集して，DHTをつないだピン番号を書き込んでください．
- 43行目を編集して，自分の持っているイーサネットシールドのMACアドレスに書き換えてください．
- 46行目を編集して，mqttブローカを動作させるホストのIPアドレスに書き換える．
- Arduinoを固定IPにする場合は，2行目``#define USE_DHCP``をコメントアウトし，57から60行目を自分の環境に合わせて変更してください．
- publishするデータのフォーマットをJSONやプレーンテキストに変更する場合は，172行目を変更してください．

### ライブラリのインストール
以下のライブラリのインストールをおねがいします．
- [Arduino Mqtt Client][ArduinoMqttClient]
- DHT温湿度センサライブラリ「本ライブラリのディレクトリ/AusEx/drivers/SimpleDigital/AusExDHT」
    -プラグインではなく，センサライブラリ本体
- RTCを使う場合は，[RTC_U][RTC_U]
- NTPを使う場合は，[Arduino NTP client][ntpClient]


## 事前準備
Linuxに[mosquitto][mosquitto]をインストールして，サーバにします．

以下にUbuntuの場合のインストール方法を簡単に書いておきますが，詳しくは[参考文献][mosquitto_install]を見てください．

```bash
$ sudo apt-get update
(中略)
$ sudo apt-get install mosquitto
```


## 動作確認
Linux側でmqttブローカを立ち上げ，このプログラムをarduino Mega2560で動作させると以下のような出力shellに出力され，arduinoがpublishした内容が届いていることが確認できます．
```
$ mosquitto_sub -d -t test
Client mosq-ZpLs4uhinFh8fKHJX0 sending CONNECT
Client mosq-ZpLs4uhinFh8fKHJX0 received CONNACK (0)
Client mosq-ZpLs4uhinFh8fKHJX0 sending SUBSCRIBE (Mid: 1, Topic: test, QoS: 0, Options: 0x00)
Client mosq-ZpLs4uhinFh8fKHJX0 received SUBACK
Subscribed (mid: 1): 0
Client mosq-ZpLs4uhinFh8fKHJX0 received PUBLISH (d0, q0, r0, m0, 'test', ... (72 bytes))
Sensor_ID=-1
Sensor_Type=13
Data_Time=1215316802
Temperature=21.90C

Client mosq-ZpLs4uhinFh8fKHJX0 received PUBLISH (d0, q0, r0, m0, 'test', ... (69 bytes))
Sensor_ID=-1
Sensor_Type=12
Data_Time=1215316802
Humidity=47.80%

Client mosq-ZpLs4uhinFh8fKHJX0 received PUBLISH (d0, q0, r0, m0, 'test', ... (72 bytes))
Sensor_ID=-1
Sensor_Type=13
Data_Time=1215316812
Temperature=21.90C

Client mosq-ZpLs4uhinFh8fKHJX0 received PUBLISH (d0, q0, r0, m0, 'test', ... (69 bytes))
Sensor_ID=-1
Sensor_Type=12
Data_Time=1215316812
Humidity=47.80%

^CClient mosq-ZpLs4uhinFh8fKHJX0 sending DISCONNECT
$
```


[mosquitto]:https://mosquitto.org/
[mosquitto_install]:https://qiita.com/kyoro353/items/b862257086fca02d3635
[RTC_U]:https://github.com/houtbrion/RTC_U
[ArduinoHttpClient]:https://github.com/arduino-libraries/ArduinoHttpClient
[ArduinoMqttClient]:https://github.com/arduino-libraries/ArduinoMqttClient
[ntpClient]:https://github.com/arduino-libraries/NTPClient