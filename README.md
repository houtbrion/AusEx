# AusExBasedLibraries

このライブラリは，Adafruitが公開しているセンサ類を統一して取り扱うためのドライバ(
[Adafruit Unified Sensor Driver][AdafruitUSD])を更に拡張して，より多くの
センサやセンサと似た使い方ができるデバイスを使うことができるようにするものです．

一般的に，Arduinoでセンサ類を取り扱う場合のプログラムの構造は下のようになりますが，同じ対象を測定可能なセンサが複数種類あった場合に，プログラムの「loop()」の中身を極力変更しなくてすむようにすることが目的です．

```
センサの定義

setup(){
  // センサのセットアップを行う
}

loop(){
  // センサの値を読み取り，なにかの処理をする
}
```

## ライセンスについて
いろんなライブラリを変更するものなので，基本的に改造前のベースのソースプラグに従います．
各デバイスのドライバでインクルードしているこのライブラリ本体は，[Adafruit Unified Sensor Driver][AdafruitUSD]を
拡張したものなので，Apache License v2.0となります．

なお，各種のセンサ等の周辺機器用のライブラリは，ベースとなるソースがそれぞれ異なるため，ドライバの各ディレクトリのREADME.mdを参照してください．

今のところ各ドライバやライブラリのライセンスの記述は不十分ですが，作業中なのでご容赦ください．

## 現在対応しているセンサ類
今の所，手元にセンサがある(もしくは過去に持っていたもの)だけを作成したため，
[Seeed Studio][SeedStudio]の[Grove][Grove]システムのいろいろなセンサ類だけが
対象になっています．
そのため，SPIとI2Cの両方に対応しているチップが搭載されているGroveのモジュールに
ついては，I2Cのみの対応になっています(GroveではSPI接続機器が存在しないため)．

- Grove - 3-Axis Digital Accelerometer(±1.5g) [http://wiki.seeedstudio.com/Grove-3-Axis_Digital_Accelerometer-1.5g/][AusExGrove3AxisDigitalAccelerometer1_5g]
- Grove - 3-Axis Digital Gyro [http://wiki.seeedstudio.com/Grove-3-Axis_Digital_Gyro/][AusExGrove3AxisDigitalGyro]
- Grove - I2C Touch Sensor [http://wiki.seeedstudio.com/Grove-I2C_Touch_Sensor/][AusExGroveI2cTouchSensor]
- Grove-Single Axis Analog Gyro [http://wiki.seeedstudio.com/Grove-Single_Axis_Analog_Gyro/][AusExGroveAnalog1AxisGyro]
- Grove - Electricity Sensor [http://wiki.seeedstudio.com/Grove-Electricity_Sensor/][AusExGroveAnalogCurrentSensor]
- Grove - Temperature Sensor V1.2 [http://wiki.seeedstudio.com/Grove-Temperature_Sensor_V1.2/][AusExGroveAnalogTemperatureSensor]
- Grove - GSR Sensor [http://wiki.seeedstudio.com/Grove-GSR_Sensor/][AusExGroveGsr]
- Grove - Rotary Angle Sensor [http://wiki.seeedstudio.com/Grove-Rotary_Angle_Sensor/][AusExGroveRotaryAngleSensor]
- Grove - Light Sensor [http://wiki.seeedstudio.com/Grove-Light_Sensor/][AusExGroveSimpleLight]
- Grove - Moisture Sensor [http://wiki.seeedstudio.com/Grove-Moisture_Sensor/][AusExGroveSimpleMoisture]
- Grove - Loudness Sensor [http://wiki.seeedstudio.com/Grove-Loudness_Sensor/][AusExGroveSimpleSound]
- Grove - Switch(P) [http://wiki.seeedstudio.com/Grove-Switch-P/][AusExDigitalSwitch]
- Grove - Dust Sensor [http://wiki.seeedstudio.com/Grove-Dust_Sensor/][AusExGroveDustSensor]
- Grove - IR Distance Interrupter v1.2 [http://wiki.seeedstudio.com/Grove-IR_Distance_Interrupter_v1.2/][AusExGroveInfraredDistanceSensor]
- Grove - Infrared Reflective Sensor [http://wiki.seeedstudio.com/Grove-Infrared_Reflective_Sensor/][AusExGroveInfraredReflectiveSensor]
- Grove - Touch Sensor [http://wiki.seeedstudio.com/Grove-Touch_Sensor/][AusExGroveTouchSensor]
- Grove - Ultrasonic Ranger [http://wiki.seeedstudio.com/Grove-Ultrasonic_Ranger/][AusExGroveUltrasonicRanger]
- Grove - Water Sensor [http://wiki.seeedstudio.com/Grove-Water_Sensor/][AusExGroveWaterSensor]

## ディレクトリ構成

|名前|内容|
|:---|:---|
|このディレクトリ|[Adafruit Unified Sensor Driver][AdafruitUSD]を拡張したセンサ等のAPI定義|
|drivers|動作を確認できたArduinoライブラリ形式の各種デバイス用ドライバ|
|templates|ドライバ開発用のテンプレートを入れたディレクトリ|
|working|開発中のソースや調査に用いた資料など|

### ドライバディレクトリの中身
|名前|内容|
|:---|:---|
|I2C_SPI|I2CやSPIインターフェイスのデバイス|
|SimpleAnalog|アナログ端子の電圧を読み取るタイプのデバイス|
|SimpleDigital|デジタル端子のHIGH,LOWを読み取るタイプのデバイス|
|Serial|シリアルで接続する機器|

## 利用準備(インストール)
- このディレクトリをArduino IDEのライブラリ置き場にコピー
- 使いたいドライバをArduino IDEのライブラリ置き場にコピー
- IDEのスケッチ例からインストールしたライブラリのサンプルプログラムを開く


## 検証に用いた機種
|ベンダ            | 機種              |CPUアーキ| MCU       | 備考     |
| :---            | :---              | :---   | :---       | :---    |
|[Arduino][Arduino]         | [Uno R3][Uno]              |AVR     |ATmega328P  |         |
|                 | [Mega 2560 R3][Mega]              |        |ATmega2560  |         |
|                 | [Leonardo Ethernet][LeonardoEth] |        |ATmega32U4  |         |
|                 | [M0 Pro][M0Pro]            |ARM M0+ |ATSAMD21G18A|3.3V     |
|[Sparkfun][Sparkfun] | [Pro mini 328][ProMini]      |AVR     |ATmega328P  |3.3V 8MHz|
|[スイッチサイエンス][SwitchScience] | [ESPr Developer][ESPrDev]      |Xtensa   |ESP8266       |3.3V     |
|[スイッチサイエンス][SwitchScience] | [ESPr one 32][ESPrOne32]      |Xtensa   |ESP32       |3.3V     |

どの機種で動いたかは，各デバイス用のドライバによって違うので，各ドライバのREADME.mdを参照してください．



### アナログセンサについて
ESP32の検証に用いた「ESPr One 32」のアナログ端子は，WiFiと同時に利用できないなどいろいろややこしいので，アナログ接続のセンサ類の検証は断念しました．

気力が復活したらやるかもしれませんが，あまり期待しないでください．

## 利用がうまくいかなかった機種
Groveのシールドと組み合わせ場合に，動作がおかしくなる，というかシリアルポートが壊れるため，検証作業を断念した機種．

|ベンダ            | 機種              |CPUアーキ| MCU     | 備考     |
| :---            | :---              | :---   | :---     | :---    |
| [Arduino][Arduino]         | [Due][Due]              |ARM M3   |SAM3X8E   |3.3V     |
|[スイッチサイエンス][SwitchScience] | [ESPr one][ESPrOne]         |Xtensa   |ESP8266   |3.3V     |

マイコンが壊れてしまい，新品を買い直してジャンパ線で配線を頑張る気持ちがなくなったため，
断念していましたが，[ESPr developer][ESPrDev]と[ESPr Developer用GROVEシールド][ESPrDevShield]を
購入して，検証作業を再開しました．


### アナログセンサについて
ESP8266のアナログ端子は1.0Vの仕様のため，ハードウェア的に変換が必要だったりします．
自分でやる際にには，ご注意ください．

## API定義
### sensors_type_t
対応するセンサの種類が増えているため，センサタイプも追加になっています．

|追加|センサの種類|内容|
|:---:|:---|:---|
||SENSOR_TYPE_ACCELEROMETER|Gravity + linear acceleration|
||SENSOR_TYPE_MAGNETIC_FIELD|磁気センサ|
||SENSOR_TYPE_ORIENTATION|方位|
||SENSOR_TYPE_GYROSCOPE|ジャイロ|
||SENSOR_TYPE_LIGHT|光|
||SENSOR_TYPE_PRESSURE|圧力|
||SENSOR_TYPE_PROXIMITY|近接|
||SENSOR_TYPE_GRAVITY|重力|
||SENSOR_TYPE_LINEAR_ACCELERATION|加速度(重力なし)|
||SENSOR_TYPE_ROTATION_VECTOR|回転方向|
||SENSOR_TYPE_RELATIVE_HUMIDITY|湿度|
||SENSOR_TYPE_AMBIENT_TEMPERATURE|温度|
||SENSOR_TYPE_VOLTAGE|電圧|
||SENSOR_TYPE_CURRENT|電流|
||SENSOR_TYPE_COLOR|色|
|○|SENSOR_TYPE_SIMPLE|単純な値|
|○|SENSOR_TYPE_ANGLE|角度|
|○|SENSOR_TYPE_1AXIS_GYRO|1軸ジャイロ|
|○|SENSOR_TYPE_DISTANCE|距離|
|○|SENSOR_TYPE_LARGE_INT|longの整数|
|○|SENSOR_TYPE_DUST|塵|



### sensors_vec_t
|型|名前|内容|
|:---|:---|:---|
|union|3軸データ||
|int8_t|status|要調査|
|uint8_t[3]|reserved|予約|


### sensors_color_t
|型|名前|内容|
|:---|:---|:---|
|union|色データ|rgbを格納するfloatの3つ組|
|uint32_t|rgba|24-bit RGBA|

### 色データ
|型|名前|内容|
|:---|:---|:---|
|float[3]|c||
|floatの3つ組struct|r, g, b|赤, 緑, 青|



### sensors_event_t型
|型|名前|内容|
|:---|:---|:---|
|int32_t|version|must be sizeof(struct sensors_event_t)|
|int32_t|sensor_id|unique sensor identifier|
|int32_t|type|sensor type|
|int32_t|reserved0|reserved
|int32_t|timestamp|time is in milliseconds|
|union|センサの値|各種の型変数のいずれか|

### センサの値
センサの返す値の種類もセンサ種類の増加に伴い追加されています．

|追加|型|名前|内容|
|:---|:---|:---|:---|
||float[4]|data||
||sensors_vec_t|acceleration|acceleration values are in meter per second per second (m/s^2)|
||sensors_vec_t|magnetic|magnetic vector values are in micro-Tesla (uT)|
||sensors_vec_t|orientation|orientation values are in degrees|
||sensors_vec_t|gyro|gyroscope values are in rad/s|
||float|temperature|temperature is in degrees centigrade (Celsius)|
||float|distance|distance in centimeters|
||float|light|light in SI lux units|
||float|pressure|pressure in hectopascal (hPa)|
||float|relative_humidity|relative humidity in percent|
||float|current|current in milliamps (mA)|
||float|voltage|voltage in volts (V)|
|○|float|angle|angle (degree)|
|○|float|roll|1 axis gyro (deg/s)|
||float|dust||
|○|uint32_t|value|output value of analogRead() or digitalRead()|
||sensors_color_t|color|color in RGB component values|

### sensor_t型
|追加|型|名前|内容|
|:---|:---|:---|:---|
||char|name[12]|sensor name|
||int32_t|version|version of the hardware + driver|
||int32_t|sensor_id|unique sensor identifier|
||int32_t|type|this sensor's type (ex. SENSOR_TYPE_LIGHT)|
||float|max_value|maximum value of this sensor's value in SI units|
||float|min_value|minimum value of this sensor's value in SI units|
||float|resolution|smallest difference between two values reported by this sensor|
||int32_t|min_delay|min delay in microseconds between events. zero = not a constant rate|



### メンバ関数

|追加|返り値の型|関数|引数|概要|変更点など|
|:---:|:---|---:|:---|:---|:---|
||bool|getEvent(sensors_event_t*)|センサの測定値を格納するための変数へのポインタ|センサの測定に成功したか否かをboolで返す||
||void|getSensor(sensor_t*)|センサの性質を示すデータを格納する変数へのポインタ|なし||
|△|bool|enableAutoRange(bool enabled)|センサレンジの自動調整を有効にするか否かを表す|自動レンジ調整をサポートしている場合はenableを返し，自動レンジ調整をサポートしていない場合はfalseを返す|自動レンジ調整がないセンサ対策のため，返り値の型をvoidからboolに変更．|
|○|int|setMode(int mode)|センサのレンジ等の動作を切り替えるモードを整数で表して引数とする|動作モード(レンジも含む)の設定を変更するための関数で動作モードがないセンサは -1 . 設定変更に失敗したら0, 設定変更に成功したら1|自動レンジ調整があるなら，手動もあるべきで，レンジ以外にも動作モードが存在するセンサもあるため，それを1つの関数にまとめる．|




## 外部リンク
- Adafruit Unified Sensor Driver - [https://github.com/adafruit/Adafruit_Sensor][AdafruitUSD]
- Groveシールド - [https://www.seeedstudio.com/Base-Shield-V2-p-1378.html][shield]
- Arduino M0 Pro - [https://store.arduino.cc/usa/arduino-m0-pro][M0Pro]
- Arduino Due - [https://store.arduino.cc/usa/arduino-due][Due]
- Arduino Uno R3 - [https://store.arduino.cc/usa/arduino-uno-rev3][Uno]
- Arduino Leonardo Ethernet - [https://store.arduino.cc/usa/arduino-leonardo-eth][LeonardoEth]
- Arduino Mega2560 R3 - [https://store.arduino.cc/usa/arduino-mega-2560-rev3][Mega]
- Arduino Pro mini 328 - 3.3V/8MHz - [https://www.sparkfun.com/products/11114][ProMini]
- ESPr developer - [https://www.switch-science.com/catalog/2652/][ESPrDev]
- ESPr Developer用GROVEシールド - [https://www.switch-science.com/catalog/2811/][ESPrDevShield]
- ESPr one 32 - [https://www.switch-science.com/catalog/3555/][ESPrOne32]
- Grove - [https://www.seeedstudio.io/category/Grove-c-1003.html][Grove]
- Seed Studio - [https://www.seeedstudio.io/][SeedStudio]
- Sparkfun Electronics - [https://www.sparkfun.com/][Sparkfun]
- スイッチサイエンス - [https://www.switch-science.com/][SwitchScience]

<!-- 以下は，外部リンクの定義 -->
[Grove]:https://www.seeedstudio.io/category/Grove-c-1003.html
[SeedStudio]:https://www.seeedstudio.io/
[AdafruitUSD]:https://github.com/adafruit/Adafruit_Sensor
[shield]:https://www.seeedstudio.com/Base-Shield-V2-p-1378.html
[M0Pro]:https://store.arduino.cc/usa/arduino-m0-pro
[Due]:https://store.arduino.cc/usa/arduino-due
[Uno]:https://store.arduino.cc/usa/arduino-uno-rev3
[Mega]:https://store.arduino.cc/usa/arduino-mega-2560-rev3
[LeonardoEth]:https://store.arduino.cc/usa/arduino-leonardo-eth
[ProMini]:https://www.sparkfun.com/products/11114
[ESPrDev]:https://www.switch-science.com/catalog/2652/
[ESPrDevShield]:https://www.switch-science.com/catalog/2811/
[ESPrOne]:https://www.switch-science.com/catalog/2620/
[ESPrOne32]:https://www.switch-science.com/catalog/3555/
[Grove]:https://www.seeedstudio.io/category/Grove-c-1003.html
[SeedStudio]:https://www.seeedstudio.io/
[Arduino]:http://https://www.arduino.cc/
[Sparkfun]:https://www.sparkfun.com/
[SwitchScience]:https://www.switch-science.com/
[AusExGrove3AxisDigitalAccelerometer1_5g]:http://wiki.seeedstudio.com/Grove-3-Axis_Digital_Accelerometer-1.5g/
[AusExGrove3AxisDigitalGyro]:http://wiki.seeedstudio.com/Grove-3-Axis_Digital_Gyro/
[AusExGroveI2cTouchSensor]:http://wiki.seeedstudio.com/Grove-I2C_Touch_Sensor/
[AusExGroveAnalog1AxisGyro]:http://wiki.seeedstudio.com/Grove-Single_Axis_Analog_Gyro/
[AusExGroveAnalogCurrentSensor]:http://wiki.seeedstudio.com/Grove-Electricity_Sensor/
[AusExGroveAnalogTemperatureSensor]:http://wiki.seeedstudio.com/Grove-Temperature_Sensor_V1.2/
[AusExGroveGsr]:http://wiki.seeedstudio.com/Grove-GSR_Sensor/
[AusExGroveRotaryAngleSensor]:http://wiki.seeedstudio.com/Grove-Rotary_Angle_Sensor/
[AusExGroveSimpleLight]:http://wiki.seeedstudio.com/Grove-Light_Sensor/
[AusExGroveSimpleMoisture]:http://wiki.seeedstudio.com/Grove-Moisture_Sensor/
[AusExGroveSimpleSound]:http://wiki.seeedstudio.com/Grove-Loudness_Sensor/
[AusExDigitalSwitch]:http://wiki.seeedstudio.com/Grove-Switch-P/
[AusExGroveDustSensor]:http://wiki.seeedstudio.com/Grove-Dust_Sensor/
[AusExGroveInfraredDistanceSensor]:http://wiki.seeedstudio.com/Grove-IR_Distance_Interrupter_v1.2/
[AusExGroveInfraredReflectiveSensor]:http://wiki.seeedstudio.com/Grove-Infrared_Reflective_Sensor/
[AusExGroveTouchSensor]:http://wiki.seeedstudio.com/Grove-Touch_Sensor/
[AusExGroveUltrasonicRanger]:http://wiki.seeedstudio.com/Grove-Ultrasonic_Ranger/
[AusExGroveWaterSensor]:http://wiki.seeedstudio.com/Grove-Water_Sensor/



<!--- コメント
[Adafruit Unified Sensor Driver][AdafruitUSD]
[Groveシールド][shield]
[Arduino M0 Pro][M0Pro]
[Arduino Due][Due]
[Arduino Uno R3][Uno]
[Arduino Mega2560 R3][Mega]
[Arduino Leonardo Ethernet][LeonardoEth]
[Arduino Pro mini 328 - 3.3V/8MHz][ProMini]
[ESpr one][ESPrOne]
[ESPr one 32][ESPrOne32]
[Grove][Grove]
[Seed Studio][SeedStudio]
[Arduino][Arduino]
[Sparkfun][Sparkfun]
[スイッチサイエンス][SwitchScience]
--->
