# HDC1000 統合センサライブラリ

このライブラリは，TIのHDC1000温湿度センサ(http://www.tij.co.jp/product/jp/HDC1000)とその後継チップのArduino用ライブラリで，
Adafruitが配布(https://github.com/adafruit/Adafruit_HDC1000_Library)しているものをAdafruitが提唱するセンサ類を
統一的に扱うためのインターフェース()https://github.com/adafruit/Adafruit_Sensor)に合うように拡張したものです．

HDC1000自体が製造中止となっているせいか，Adafruit自身がHDC1000用ライブラリを統合インターフェースをサポートするよう
改修してくれないので，統合インターフェースサポートライブラリの開発経験を積むためと，手近にHDCシリーズのチップを使った
モジュール(http://akizukidenshi.com/download/ds/akizuki/AE-HDC1000.pdf)が転がっていたので，練習兼ねてやってみた．

Unoで温度と湿度が測定できるところまで確認した．

## 使い方
このライブラリに添付している統合インターフェース用サンプルプログラム(
HDC1000_Unified_Sensor)を見ていただければわかるように，プログラムの先頭で，チップの種類や，I2Cの引数を与えて初期化した後は，Adafruitの統合インターフェースでアクセスできる．

サンプルプログラムの主要な部分を抜き出して紹介するので，
詳細は実際のサンプルプログラムを見ていただきたい．

### プログラムの冒頭部分
```
#define SENSOR_CLASS Adafruit_HDC1000_Unified // ライブラリの種類を定義
#define SENSOR_TYPE HDC1000                   // センサチップの種類を定義

#if SENSOR_TYPE == Adafruit_HDC1000_Unified   // ライブラリのヘッダをインクルード
#include "Adafruit_HDC1000_U.h"
#endif /* SENSOR_TYPE */

SENSOR_CLASS sensorObj(SENSOR_TYPE);          // センサを示すオブジェクトを生成
```

### 初期化
引数なしで，beginを呼び出すことで，初期化は完了
```
void setup()
{
  Serial.begin(9600);
  sensorObj.begin();
}
```

### センサ値の取得など
センサを読み出すのは，Adafruitの統合センサライブラリのインターフェースを参照してね．

### I2Cのアドレスなどを変更したい場合
ヘッダからセンサオブジェクトを生成する時のイニシャライズの定義は以下の通りなので，センサに番号をつけたり，I2Cのアドレスを変更するのは，センサオブジェクトを生成する時の引数でできます．
```
Adafruit_HDC1000_Unified(uint8_t type, int32_t tempSensorId=-1, int32_t humiditySensorId=-1, uint8_t addr=HDC1000_I2CADDR);
```
このあたりは，Adafruitの統合センサインターフェースのしきたりに従っています．

### HDC1000の後継チップを使う場合
上で，初期化の手順を説明したところに，以下のdefine文がありましたが，ここを変えればいいです．
```
#define SENSOR_TYPE HDC1000                   // センサチップの種類を定義
```

以下のdefine文のうちの一つを活かし，他のコメントアウトする方法でOK．
```
#define SENSOR_TYPE HDC1000
#define SENSOR_TYPE HDC1008
#define SENSOR_TYPE HDC1010
#define SENSOR_TYPE HDC1080
#define SENSOR_TYPE HDC2010
```




## 注意事項
### 後継チップについて
データシートをざっと見る範囲では，HDC1000の後継チップのうち，HDC1008,HDC1010,HDC1080はそのまま動きそうではあるものの，
HDC2000シリーズはそのまま動くかどうかあやしい．

ぱっと見た範囲では，HDC1080のI2CのアドレスがHDC1000と違うのは見つけられたので，ソースに反映したけど，他はぱっと見た範囲ではわからなかったので，HDC1000と同じパラメータになってます．

一応，HDC2010用の定義までは入れたが，本当に動く自信はない．

### センサの連続アクセスについて
一般的に，センサ系のチップは，一度環境を測定した後，一定時間放置しないと，測定ができなかったり，測定値が信頼できなくなる．これに対応するため，Adafruitの統合インターフェースでは，一度アクセスすると，時刻を記憶しておき，チップに定められた経過時間を過ぎていないと，APIを叩いても，古い測定値を返す仕組みになっている．

この機能を活かすためには，各チップごとに異なるチップが安定化する時間をコードに埋める必要があるが，HDC1000と後継チップのデータシートを見たときに，見つけられなかったので，待機時間を0にしている．

そのため，連続アクセスの場合のデータの保証がないのはご勘弁．

誰か，データシートを熟読した人がいれば教えてもらえると嬉しい．

## 参考資料
- 日本語化(非公式)データシート http://www.ne.jp/asahi/o-family/extdisk/SHT21/HDC1000_DJP.pdf
