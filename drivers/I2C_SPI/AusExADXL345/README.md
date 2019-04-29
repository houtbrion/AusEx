# AusExADXL345
このドライバは，
[Adafruitのセンサ統合ライブラリ][AdafruitUSD]を拡張した上で，いろいろなセンサ類を
[統合ライブラリ][AdafruitUSD]のAPIでアクセス可能にするプロジェクトの一部で，
アナログ・デバイセズの[ADXL345 3軸加速度センサ][ADXL345]用のドライバです．
チップは，[Seeed studio][SeedStudio]の[Grove3軸加速度センサ][ProductPage]に
搭載されているだけでなく，[Adafruit][Adafruit]からのモジュールが販売されています．


そのため，[Seeed studio][SeedStudio]，[Adafruit][Adafruit]共に独自の
ドライバを公開しています．

## 仕様

仕様は[チップのページ]を見てね．

[チップのページ]:https://www.analog.com/jp/products/adxl345.html

## ベースとなるコードとライセンス

ベースとなるコードは[Adafruit][Adafruit]の[Githubのプログラム][AdafruitGithub]で，
『BSD Liceense』となっているので，それに従います．
[Seeed studio][SeedStudio]も独自のコードを[公開][github]していますが，seeed studioのコードは
Groveの[ProductPage]にあります．


なお，Adafrutiのコードをベースにした理由は以下の2点です．
 - AdafruitのドライバのみSPIをサポートしている
 - 統合するインターフェースはAdaruitのものであるため，Adafruitのコードのほうが変更量が少なくてすむ．

 あと，元のAdafuitのドライバからインターフェース関係以外で変更した主要は部分は以下の通りです．
 - ハードウェアSPIのサポート

 ハードウェアSPIを利用する場合は，クラスのオブジェクトを生成する際に，ソフトウェアSPIの
 インターフェース(全てのピンを指定する)を利用してもらい，クロックピンの番号を「-1 (0xFF)」に
 してもらえば，ArduinoのハードウェアSPIインターフェースを利用します．

 ESP32のように，SPIのインターフェースが「SPI, SPI1」とか複数ある場合は「SPIのみ対応」となります．

## 動作検証

|CPU| 機種 |ベンダ| I2C | ソフトSPI | ハードSPI | 備考 |
| :--- | :--- | :--- | :---: | :---: | :---: |:--- |
|AVR| [Uno R3][Uno]  |[Arduino][Arduino]| ○ | ○ | ○ |      |
|       | [Mega2560 R3][Mega] |[Arduino][Arduino] | ○ | ○ | ○ |      |
|       | [Leonardo Ethernet][LeonardoEth] |[Arduino][Arduino] | ○ | ○ | ○ |      |
|       | [Uno WiFi][UnoWiFi] |[Arduino][Arduino] | ○ | ○ | ○ |      |
|       | [Pro mini 3.3V][ProMini] | [Sparkfun][Sparkfun] | ○ | ○ | ○ |      |
| ARM/M0+ | [M0 Pro][M0Pro] |[Arduino][Arduino] | ○ | ○ | ○ |  |
|ESP8266|[ESPr Developer][ESPrDev]| [スイッチサイエンス][SwitchScience] | ○ |*1|*1||
|ESP32 | [ESPr One 32][ESPrOne32] | [スイッチサイエンス][SwitchScience] | ○ | ○ | ○ ||

- *1 機材の関係上未確認 (ESPr Developerはピン数が少ないなどなにかと不自由)


## 使い方

AusEX共通部分のI2CもしくはSPIの部分とサンプルプログラムを見れば基本的な使い方はわかります．
また，ADXL345独自の部分としては，センサの動作モードの設定と現在の設定モードの取得部分だけとなります．

ADXL345は，測定可能な加速度の範囲と測定のサンプリングレートを設定可能になっており，それぞれの値を8bit整数で指定します．
それを合成したものをセンサのモードとして設定する使い方になります．

### 測定可能な加速度の範囲
以下の4種類が選択可能です．
```
#define AUSEX_ADXL345_RANGE_16_G           0b11   // +/- 16g
#define AUSEX_ADXL345_RANGE_8_G            0b10   // +/- 8g
#define AUSEX_ADXL345_RANGE_4_G            0b01   // +/- 4g
#define AUSEX_ADXL345_RANGE_2_G            0b00    // +/- 2g (default value)
```

### サンプリングレート
サンプリングレートは周波数で指定することになります．
```
#define AUSEX_ADXL345_DATARATE_3200_HZ     0b1111 // 1600Hz Bandwidth   140・ｽA IDD
#define AUSEX_ADXL345_DATARATE_1600_HZ     0b1110 //  800Hz Bandwidth    90・ｽA IDD
#define AUSEX_ADXL345_DATARATE_800_HZ      0b1101 //  400Hz Bandwidth   140・ｽA IDD
#define AUSEX_ADXL345_DATARATE_400_HZ      0b1100 //  200Hz Bandwidth   140・ｽA IDD
#define AUSEX_ADXL345_DATARATE_200_HZ      0b1011 //  100Hz Bandwidth   140・ｽA IDD
#define AUSEX_ADXL345_DATARATE_100_HZ      0b1010 //   50Hz Bandwidth   140・ｽA IDD
#define AUSEX_ADXL345_DATARATE_50_HZ       0b1001 //   25Hz Bandwidth    90・ｽA IDD
#define AUSEX_ADXL345_DATARATE_25_HZ       0b1000 // 12.5Hz Bandwidth    60・ｽA IDD
#define AUSEX_ADXL345_DATARATE_12_5_HZ     0b0111 // 6.25Hz Bandwidth    50・ｽA IDD
#define AUSEX_ADXL345_DATARATE_6_25HZ      0b0110 // 3.13Hz Bandwidth    45・ｽA IDD
#define AUSEX_ADXL345_DATARATE_3_13_HZ     0b0101 // 1.56Hz Bandwidth    40・ｽA IDD
#define AUSEX_ADXL345_DATARATE_1_56_HZ     0b0100 // 0.78Hz Bandwidth    34・ｽA IDD
#define AUSEX_ADXL345_DATARATE_0_78_HZ     0b0011 // 0.39Hz Bandwidth    23・ｽA IDD
#define AUSEX_ADXL345_DATARATE_0_39_HZ     0b0010 // 0.20Hz Bandwidth    23・ｽA IDD
#define AUSEX_ADXL345_DATARATE_0_20_HZ     0b0001 // 0.10Hz Bandwidth    23・ｽA IDD
#define AUSEX_ADXL345_DATARATE_0_10_HZ     0b0000  // 0.05Hz Bandwidth    23・ｽA IDD (default value)
```

### 動作モードの指定と，現在の動作モードの取得
動作モードの指定は以下のコードで可能です．
```
センサ変数.setMode(センサ変数.getModeParam(測定レンジ,サンプリングレート));
```

動作モードの取得は以下のように行います．
```
動作モード = センサ変数.getMode();
測定レンジ = センサ変数.getRangeParam(動作モード);
サンプリングレート = センサ変数.getRateParam(動作モード);
```

## 外部リンク
- Seeed Studio技術Wiki [http://wiki.seeedstudio.com/Grove-3-Axis_Digital_Accelerometer-16g/][SeedWiki]
- センサ商品ページ [https://www.seeedstudio.com/Grove-3-Axis-Digital-Accelerometer-16-p-1156.html][ProductPage]
- Seeed Studioソースリポジトリ [https://github.com/Seeed-Studio/Accelerometer_ADXL345][github]
- Adafruitソースリポジトリ [https://github.com/adafruit/Adafruit_ADXL345][AdafruitGithub]
- Adafruit Unified Sensor Driver - [https://github.com/adafruit/Adafruit_Sensor][AdafruitUSD]
- Groveシールド - [https://www.seeedstudio.com/Base-Shield-V2-p-1378.html][shield]
- Arduino M0 Pro - [https://store.arduino.cc/usa/arduino-m0-pro][M0Pro]
- Arduino Due - [https://store.arduino.cc/usa/arduino-due][Due]
- Arduino Uno R3 - [https://store.arduino.cc/usa/arduino-uno-rev3][Uno]
- Arduino Uno WiFi - [https://store.arduino.cc/usa/arduino-uno-wifi-rev2][UnoWiFi]
- Arduino Leonardo Ethernet - [https://store.arduino.cc/usa/arduino-leonardo-eth][LeonardoEth]
- Arduino Mega2560 R3 - [https://store.arduino.cc/usa/arduino-mega-2560-rev3][Mega]
- Arduino Pro mini 328 - 3.3V/8MHz - [https://www.sparkfun.com/products/11114][ProMini]
- ESPr Developer - [https://www.switch-science.com/catalog/2652/][ESPrDev]
- ESPr Developer用GROVEシールド - [https://www.switch-science.com/catalog/2811/][ESPrDevShield]
- ESPr Developer 32 - [https://www.switch-science.com/catalog/3210/][ESPrDev32]
- Grove - [https://www.seeedstudio.io/category/Grove-c-1003.html][Grove]
- Seed Studio - [https://www.seeedstudio.io/][SeedStudio]
- Sparkfun Electronics - [https://www.sparkfun.com/][Sparkfun]
- スイッチサイエンス - [https://www.switch-science.com/][SwitchScience]

<!-- 以下は，外部リンクの定義 -->
[Grove]:https://www.seeedstudio.io/category/Grove-c-1003.html
[ADXL345]:https://www.analog.com/jp/products/adxl345.html
[SeedStudio]:https://www.seeedstudio.io/
[Adafruit]:https://www.adafruit.com/
[ProductPage]:https://www.seeedstudio.com/Grove-3-Axis-Digital-Accelerometer-16-p-1156.html
[SeedWiki]:http://wiki.seeedstudio.com/Grove-3-Axis_Digital_Accelerometer-16g/
[github]:https://github.com/Seeed-Studio/Accelerometer_ADXL345
[AdafruitGithub]:https://github.com/adafruit/Adafruit_ADXL345
[AdafruitUSD]:https://github.com/adafruit/Adafruit_Sensor
[shield]:https://www.seeedstudio.com/Base-Shield-V2-p-1378.html
[M0Pro]:https://store.arduino.cc/usa/arduino-m0-pro
[Due]:https://store.arduino.cc/usa/arduino-due
[Uno]:https://store.arduino.cc/usa/arduino-uno-rev3
[UnoWiFi]:https://store.arduino.cc/usa/arduino-uno-wifi-rev2
[Mega]:https://store.arduino.cc/usa/arduino-mega-2560-rev3
[LeonardoEth]:https://store.arduino.cc/usa/arduino-leonardo-eth
[ProMini]:https://www.sparkfun.com/products/11114
[ESPrDev]:https://www.switch-science.com/catalog/2652/
[ESPrDevShield]:https://www.switch-science.com/catalog/2811
[ESPrOne]:https://www.switch-science.com/catalog/2620/
[ESPrOne32]:https://www.switch-science.com/catalog/3555/
[Grove]:https://www.seeedstudio.io/category/Grove-c-1003.html
[SeedStudio]:https://www.seeedstudio.io/
[Arduino]:http://https://www.arduino.cc/
[Sparkfun]:https://www.sparkfun.com/
[SwitchScience]:https://www.switch-science.com/
[ESPrDev32]:https://www.switch-science.com/catalog/3210/

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
