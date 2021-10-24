# AusExAM232X_WiFi_HttpServer

このサンプルプログラムは，ESP32 devkit等のESP32を搭載した開発用ボードをwebサーバにし，センサでの測定結果をhttpクライアントに送信するプログラムとなっています．

動作確認したものは，ESPr One 32とAM2321, RTCとしてEPSON 8564NBの組み合わせを利用しました．AM232XはOne WireとI2Cの両方で動作するセンサですが，ドライバとしては
I2Cでしか動作確認できていません．

このプログラムでは，測定データに含まれる温湿度センサを使った測定時刻にRTC利用，NTP利用，両方使わないの3通りを選ぶことができますが，両方使わない場合はarduinoが起動してからの経過ミリ秒となるため，実用的には意味のあるデータは取得できません．

## Arduinoの準備

### 各種ライブラリのインストール
どのパターンでもコンパイルできるように，関連するライブラリはすべてインストールしておくことを勧めます．

- [統合RTCライブラリ][ntpClient]とそこに収録されているEPSON 8564NBドライバ
- このプログラムの親元であるAusEXライブラリに収録されているDHT用ドライバ
- [NTPクライアント][ntpClient]


### 選択項目

#### センサの種類の選択
AM232XのドライバはAM2321とAM2322に対応しています．使う方のセンサを69行目で定義してください．

#### DHCPと固定IPの選択
デフォルトはDHCPになっているので，DHCPを利用する方はそのままで構いません．
もし，Arduinoを固定IPにする場合は，以下の2点を編集してください．
- 2行目``#define USE_DHCP``をコメントアウト
- 53から56行目を自分の環境に合わせて変更

ただし，固定IPだとなぜかNTPでの時刻取得が正しい結果を返さないという問題があります．

### RTC/NTPの選択
#### どちらも使わない
- 3と4行目の``#define USE_NTP``と``#define USE_RTC``を両方コメントアウト

#### NTPを使う
- 3行目の``#define USE_NTP``を有効にする
- 4行目の``#define USE_RTC``をコメントアウト
- 本プログラムが収録されているライブラリAusExOutputPluginの``config.h``の``#define __USE_RTC__``をコメントアウト
#### RTCを使う
- 3行目の``#define USE_NTP``をコメントアウト
- 4行目の``#define USE_RTC``を有効にする
- 本プログラムが収録されているライブラリAusExOutputPluginの``config.h``の``#define __USE_RTC__``を有効にする


## Arduinoへのプログラムのインストールと実行

Arduino IDEで本プログラムをコンパイルし，ESP32にインストールします．インストールが成功したら，Arduino IDEのシリアルモニタを開いてください．

## ブラウザでのArduinoへのアクセス
WebブラウザでArduinoにアクセスすると，以下のようなデータが得られる．
```
Sensor_ID=-1
Sensor_Type=13
Data_Time=8202
Temperature=22.40C
Sensor_ID=-1
Sensor_Type=12
Data_Time=8202
Humidity=38.20%
```

本プログラムは，154行目から158行目で，返すデータのフォーマットを変更しており，本プログラムが利用しているライブラリはプレーンテキスト以外にJSONが選択できるため適宜編集してください．
また，その変更に合わせて，171から176行目のHTTPのcontent-typeの定義も調整が必要です．

[RTC_U]:https://github.com/houtbrion/RTC_U
[ArduinoHttpClient]:https://github.com/arduino-libraries/ArduinoHttpClient
[ntpClient]:https://github.com/arduino-libraries/NTPClient


