# AusExAM232X_WiFi_HttpClient

このプログラムは，ESP32のボードに温湿度センサをつなげ，測定した温湿度センサの結果をjson形式でwebサーバに対してpostするものになっています．

動作確認したものは，ESPr One 32と温湿度センサとしてAM2321を用い，EPSON8564NBというRTCを用いる組み合わせです．

このプログラムでは，測定データに含まれる温湿度センサを使った測定時刻にRTC利用，NTP利用，両方使わないの3通りを選ぶことができますが，両方使わない場合はarduinoが起動してからの経過ミリ秒となるため，実用的には意味のあるデータは取得できません．

他に，選択の余地があるのはDHCP/固定IP設定と温湿度センサがAM2321, AM2322のどれを用いるかを選択することができます．


## Arduinoの準備

### 各種ライブラリのインストール
どのパターンでもコンパイルできるように，関連するライブラリはすべてインストールしておくことを勧めます．

- [統合RTCライブラリ][ntpClient]とそこに収録されているEPSON 8564NBドライバ
- このプログラムの親元であるAusEXライブラリに収録されているDHT用ドライバ
- [Arduino HTTP Client][ntpClient]
- [NTPクライアント][ntpClient]

### 選択項目

#### センサの種類の選択
74行目で現状はAM2321を指定していますがAM2322に変更することで，センサはAM2322に変更することができます．

#### DHCPと固定IPの選択
デフォルトはDHCPになっているので，DHCPを利用する方はそのままで構いません．
もし，固定IPにする場合は，以下の2点を編集してください．
- 2行目``#define USE_DHCP``をコメントアウト
- 52から55行目を自分の環境に合わせて変更

ただし，DHCPとntpの組み合わせが正しく動作しない(時刻の取得結果がおかしい)ので注意してください．

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


## Webサーバの準備
ここでは，Ubuntu20.04での事例を紹介します．

### パッケージのインストール
まず，Ubuntu20.04のホストのroot権限で以下の一連のコマンドを実行し，``json-server``をインストールします．
すでに，node.jsやnpm，nをインストール済みの人はnpmでjson-serverだけインストールすればOKです．
```
apt install nodejs npm
npm -g install n
apt purge nodejs npm
n lts
npm install -g json-server
```
ただし，動作を確認した環境は2021/10現在のlts最新版を使っているため，aptでインストールした
ディストリビューションのnpmやnode.jsを使った場合は，異なる結果となる可能性があります．

### サーバ側設定ファイルの作成
任意のディレクトリで以下のような内容のファイル(ここでは``arduino-test.json``)を作成します．
```
$ cat arduino-test.json
{
  "sensor-data": {
    "id": -1,
    "type": 13,
    "time": 1,
    "data": [
      {
        "temperature": 0,
        "unit": 2
      }
    ]
  },
  "sensor-data2": {
    "id": -1,
    "type": 12,
    "time": 1,
    "data": [
      {
        "humidity": 0,
        "unit": 3
      }
    ]
  }
}
$
```

## json-serverの実行
shell画面を2つ開き，そのうちの一つに以下のコマンドを入力し，json-serverを実行しますが，IPアドレスはjson-serverを動作させる(下のコマンドを投入する)ホストのIPアドレスで置き換えてください．
```
$sudo  json-server --watch arduino-test.json --host 192.168.1.213 --port 80
```
もう一つのshell画面でcurlコマンドを入力すると，設定ファイルの内容が見えるはずです．
```
$ curl -X  GET http://192.168.1.213/sensor-data
{
  "id": -1,
  "type": 13,
  "time": 1,
  "data": [
    {
      "temperature": 0,
      "unit": 2
    }
  ]
}$ curl -X  GET http://192.168.1.213/sensor-data2
{
  "id": -1,
  "type": 12,
  "time": 1,
  "data": [
    {
      "humidity": 0,
      "unit": 3
    }
  ]
}
```
この時，json-server側のshell画面では，curlでアクセスされたログが出力されているはずです．
```
$sudo  json-server --watch arduino-test.json --host 192.168.1.213 --port 80
  \{^_^}/ hi!

  Loading arduino-test.json
  Done

  Resources
  http://192.168.1.213:80/sensor-data
  http://192.168.1.213:80/sensor-data2

  Home
  http://192.168.1.213:80

  Type s + enter at any time to create a snapshot of the database
  Watching...

GET /sensor-data 200 7.510 ms - 110
GET /sensor-data2 200 5.947 ms - 107
```

## Arduinoへのプログラムのインストールと実行

Arduino IDEで本プログラムをコンパイルし，Arduinoにインストールします．インストールが成功したら，Arduino IDEのシリアルモニタを開いてください．

## 実行結果
ちゃんとArduinoが動作していれば，ArduinoからPostした履歴がjson-server側のshell画面に出力されます．
```
$sudo  json-server --watch arduino-test.json --host 192.168.1.213 --port 80
  \{^_^}/ hi!

  Loading arduino-test.json
  Done

  Resources
  http://192.168.1.213:80/sensor-data
  http://192.168.1.213:80/sensor-data2

  Home
  http://192.168.1.213:80

  Type s + enter at any time to create a snapshot of the database
  Watching...

GET /sensor-data 200 7.510 ms - 110
GET /sensor-data2 200 5.947 ms - 107
POST /sensor-data 201 56.718 ms - 122
POST /sensor-data2 201 4.030 ms - 119
POST /sensor-data 201 5.384 ms - 122
POST /sensor-data2 201 4.980 ms - 119
GET /sensor-data 200 6.330 ms - 122
GET /sensor-data2 200 16.993 ms - 119
POST /sensor-data 201 4.009 ms - 122
POST /sensor-data2 201 5.450 ms - 119
POST /sensor-data 201 6.803 ms - 122
^C
$
```


先程のcurl用のshellで再度curlを実行すると，Arduinoがpostしたデータが見えるはずです．

```
$ curl -X  GET http://192.168.1.213/sensor-data
{
  "id": -1,
  "type": 13,
  "time": 1634707140,
  "data": [
    {
      "temperature": 23.8,
      "unit": 2
    }
  ]
}$ curl -X  GET http://192.168.1.213/sensor-data2
{
  "id": -1,
  "type": 12,
  "time": 1634707140,
  "data": [
    {
      "humidity": 45.3,
      "unit": 3
    }
  ]
}$
```
最後に，json-serverを止めて設定ファイルの中身を確認すると，Arduinoが最後にpostしたデータで設定ファイルの内容が更新されています．
```
$ cat arduino-test.json
{
  "sensor-data": {
    "id": -1,
    "type": 13,
    "time": 1634707154,
    "data": [
      {
        "temperature": 23.8,
        "unit": 2
      }
    ]
  },
  "sensor-data2": {
    "id": -1,
    "type": 12,
    "time": 1634707147,
    "data": [
      {
        "humidity": 45.3,
        "unit": 3
      }
    ]
  }
}$
```





[RTC_U]:https://github.com/houtbrion/RTC_U
[ArduinoHttpClient]:https://github.com/arduino-libraries/ArduinoHttpClient
[ntpClient]:https://github.com/arduino-libraries/NTPClient

