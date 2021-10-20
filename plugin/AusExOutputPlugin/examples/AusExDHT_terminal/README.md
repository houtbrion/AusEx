# AusExDHT_terminal

このサンプルプログラムは，arduinoでセンサを用いた測定結果をシリアルへ出力したり，SDカードのログファイルに保存するものです．


## 各種ライブラリのインストール
どのパターンでもコンパイルできるように，関連するライブラリはすべてインストールしておくことを勧めます．

- [統合RTCライブラリ][ntpClient]とそこに収録されているEPSON 8564NBドライバ
- このプログラムの親元であるAusEXライブラリに収録されているDHT用ドライバ
- [NTPクライアント][ntpClient]

## 必須の修正項目
- 43行目のMACアドレスは自分が利用している装置のMACアドレスに変更してください．



## 選択項目

### センサの種類の選択
このプログラムでは，DHT11,21,22を選択できますが，28から30行目のうち利用するセンサの定義を有効にして，それ以外はコメントアウトしてください．また，センサをつないだピン番号は26行目に反映します．

### DHCPと固定IPの選択
デフォルトは固定IPになっているので，DHCPを利用する場合は2行目の``#define USE_DHCP``を有効にします．
固定IPで運用する場合は，77から80行目を自分の環境に合わせて変更してください．

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

### 出力先の選択
5から7行目でいずれか1つを有効にする．
```
#define USE_SOFT_SERIAL          // センサデータ出力先にソフトウェアシリアルを使う
#define USE_SD                   // SDカードにセンサのログを書き込む場合
#define USE_HARD_SERIAL          // センサデータ出力先にハードウェアシリアルの1番(Serial)を使う
```

上に加えて，ソフトウェアシリアルとSDについては以下の項目も編集&設定変更を行う．
#### ソフトウェアシリアル
36行目と37行目のシリアルの端子番号を自分の環境に合わせて変更する．
```
#define SOFT_SERIAL_TX 6         // ソフトシリアルの送信ピン番号
#define SOFT_SERIAL_RX 7         // ソフトシリアルの受信ピン番号
```

#### SD
32行目のファイル名，33行目のSDのチップセレクトに使うピン番号，34行目の起動毎に測定ログの入ったファイルを消すか否かの選択を自分の環境に合わせて変更する．
```
#define LOG_FILE_NAME "log.txt"  // SDカードに書き込むログファイル名
#define SD_CHIP_SELECT 4         // SDのチップセレクトピン番号
#define CLEAR_FILE               // ブート時に古いログファイルを消す設定
```

### 出力フォーマットの選択
179行目から182行目で，使うフォーマットだけを活かす．下はsyslogフォーマットを選択する場合．
```
  outputDevice.SetIO(AUSEX_OUTPUT_CHANNEL, channel, FORMAT_TYPE_SYSLOG);
  outputDevice.SetLogParam(HOSTNAME, APP_NAME);
  //outputDevice.SetIO(AUSEX_OUTPUT_CHANNEL, channel, FORMAT_TYPE_PLAIN_TEXT);
  //outputDevice.SetIO(AUSEX_OUTPUT_CHANNEL, channel, FORMAT_TYPE_JSON);
```

syslogフォーマットを選択する場合は，43,44行目でホスト名とアプリ名に相当する文字列を定義してください．

```
#define HOSTNAME "arduinoMega"   // syslog形式のログ出力に利用
#define APP_NAME "foo"           // syslog形式のログ出力に利用
```

## Arduinoへのプログラムのインストールと実行

Arduino IDEで本プログラムをコンパイルし，Arduinoにインストールします．インストールが成功したら，Arduino IDEのシリアルモニタを開いてください．

## 動作の確認

### RTCを有効にし，ハードウェアシリアルに出力した場合 : syslogフォーマット

```
setup start.
Successful initialization of the RTC
DHTxx Unified Sensor Example
2008/7/6 Sun 22:22:31 arduinoMega foo : Temperature Sensor
2008/7/6 Sun 22:22:31 arduinoMega foo : Sensor Type: DHT22
2008/7/6 Sun 22:22:31 arduinoMega foo : Driver Ver:  1
2008/7/6 Sun 22:22:31 arduinoMega foo : Unique ID:   -1
2008/7/6 Sun 22:22:31 arduinoMega foo : Max Value:   125.00C
2008/7/6 Sun 22:22:31 arduinoMega foo : Min Value:   -40.00C
2008/7/6 Sun 22:22:31 arduinoMega foo : Resolution:  0.10C
2008/7/6 Sun 22:22:31 arduinoMega foo : Humidity Sensor
2008/7/6 Sun 22:22:31 arduinoMega foo : Sensor Type: DHT22
2008/7/6 Sun 22:22:31 arduinoMega foo : Driver Ver:  1
2008/7/6 Sun 22:22:31 arduinoMega foo : Unique ID:   -1
2008/7/6 Sun 22:22:31 arduinoMega foo : Max Value:   100.00%
2008/7/6 Sun 22:22:31 arduinoMega foo : Min Value:   0.00%
2008/7/6 Sun 22:22:31 arduinoMega foo : Resolution:  0.10%
******************
2008/7/6 Sun 22:22:34 arduinoMega foo : Sensor_ID=-1
2008/7/6 Sun 22:22:34 arduinoMega foo : Sensor_Type=13
2008/7/6 Sun 22:22:34 arduinoMega foo : Data_Time=1215382954
2008/7/6 Sun 22:22:34 arduinoMega foo : Temperature=24.80C
2008/7/6 Sun 22:22:34 arduinoMega foo : Sensor_ID=-1
2008/7/6 Sun 22:22:34 arduinoMega foo : Sensor_Type=12
2008/7/6 Sun 22:22:34 arduinoMega foo : Data_Time=1215382954
2008/7/6 Sun 22:22:34 arduinoMega foo : Humidity=25.40%
******************
2008/7/6 Sun 22:22:36 arduinoMega foo : Sensor_ID=-1
2008/7/6 Sun 22:22:36 arduinoMega foo : Sensor_Type=13
2008/7/6 Sun 22:22:36 arduinoMega foo : Data_Time=1215382956
2008/7/6 Sun 22:22:36 arduinoMega foo : Temperature=24.80C
2008/7/6 Sun 22:22:36 arduinoMega foo : Sensor_ID=-1
2008/7/6 Sun 22:22:36 arduinoMega foo : Sensor_Type=12
2008/7/6 Sun 22:22:36 arduinoMega foo : Data_Time=1215382956
2008/7/6 Sun 22:22:36 arduinoMega foo : Humidity=25.20%
******************
```

### RTC,NTP両方無効にし，SDに出力した場合 : プレーンテキストフォーマット

SDに出力する場合，「******************」のところで1回の測定結果がSDのログファイルに書き込みされ，5回測定した後(「==========================」にはさまれた部分)でログファイルの中身がシリアルにダンプする動作を行う．下はその実例です．
```
setup start.
DHTxx Unified Sensor Example
******************
******************
******************
******************
******************
==========================
Temperature Sensor
Sensor Type: DHT22
Driver Ver:  1
Unique ID:   -1
Max Value:   125.00C
Min Value:   -40.00C
Resolution:  0.10C
Humidity Sensor
Sensor Type: DHT22
Driver Ver:  1
Unique ID:   -1
Max Value:   100.00%
Min Value:   0.00%
Resolution:  0.10%
Sensor_ID=-1
Sensor_Type=13
Data_Time=2060
Temperature=24.70C
Sensor_ID=-1
Sensor_Type=12
Data_Time=2060
Humidity=21.90%
Sensor_ID=-1
Sensor_Type=13
Data_Time=4069
Temperature=24.70C
Sensor_ID=-1
Sensor_Type=12
Data_Time=4069
Humidity=22.10%
Sensor_ID=-1
Sensor_Type=13
Data_Time=6083
Temperature=24.70C
Sensor_ID=-1
Sensor_Type=12
Data_Time=6083
Humidity=22.10%
Sensor_ID=-1
Sensor_Type=13
Data_Time=8093
Temperature=24.70C
Sensor_ID=-1
Sensor_Type=12
Data_Time=8093
Humidity=22.10%
Sensor_ID=-1
Sensor_Type=13
Data_Time=10103
Temperature=24.70C
Sensor_ID=-1
Sensor_Type=12
Data_Time=10103
Humidity=22.10%
==========================
```

[RTC_U]:https://github.com/houtbrion/RTC_U
[ntpClient]:https://github.com/arduino-libraries/NTPClient


