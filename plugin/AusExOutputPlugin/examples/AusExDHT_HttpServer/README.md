# AusExDHT_HttpServer

このサンプルプログラムは，Arduinoをwebサーバにし，センサでの測定結果をhttpクライアントに送信するプログラムとなっています．

動作確認したものは，Arduino Mega 2560R3にイーサネットシールドを載せ，温湿度センサとしてDHT22を用い，EPSON8564NBというRTCを用いる組み合わせです．

このプログラムでは，測定データに含まれる温湿度センサを使った測定時刻にRTC利用，NTP利用，両方使わないの3通りを選ぶことができますが，両方使わない場合はarduinoが起動してからの経過ミリ秒となるため，実用的には意味のあるデータは取得できません．

他に，選択の余地があるのはDHCP/固定IP設定と温湿度センサがDHT11, 21, 22のどれを用いるかを選択することができます．


## Arduinoの準備

### 各種ライブラリのインストール
どのパターンでもコンパイルできるように，関連するライブラリはすべてインストールしておくことを勧めます．

- [統合RTCライブラリ][ntpClient]とそこに収録されているEPSON 8564NBドライバ
- このプログラムの親元であるAusEXライブラリに収録されているDHT用ドライバ
- [NTPクライアント][ntpClient]

### 必須の修正項目
- 43行目のMACアドレスは自分が利用している装置のMACアドレスに変更してください．

### 選択項目

#### センサの種類の選択
このプログラムでは，DHT11,21,22を選択できますが，21から23行目のうち利用するセンサの定義を有効にして，それ以外はコメントアウトしてください．また，センサをつないだピン番号は19行目に反映します．

#### DHCPと固定IPの選択
デフォルトはDHCPになっているので，DHCPを利用する方はそのままで構いません．
もし，Arduinoを固定IPにする場合は，以下の2点を編集してください．
- 2行目``#define USE_DHCP``をコメントアウト
- 53から56行目を自分の環境に合わせて変更

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

Arduino IDEで本プログラムをコンパイルし，Arduinoにインストールします．インストールが成功したら，Arduino IDEのシリアルモニタを開いてください．

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

本プログラムは，158行目から162行目で，返すデータのフォーマットを変更しており，本プログラムが利用しているライブラリはプレーンテキスト以外にJSONが選択できるため，158行目から162行目のところのHTTPヘッダと，145行目の出力フォーマット選択の部分をjsonに変更することで，jsonをクライアントに送信することができる．

[RTC_U]:https://github.com/houtbrion/RTC_U
[ArduinoHttpClient]:https://github.com/arduino-libraries/ArduinoHttpClient
[ntpClient]:https://github.com/arduino-libraries/NTPClient


