# AusExDallasTemperature
このライブラリは，いろいろなセンサ類のライブラリを
Adafruitのセンサ統合ライブラリと同じAPIに修正してみるプロジェクトの一部で，
[Maxim][Dallas]の温度センサを取り扱うものです．

このライブラリは[Arduino Library for Maxim Temperature Integrated Circuits][DallasArduino]の上に
重ねる形で実装しています．また，[Arduino Library for Maxim Temperature Integrated Circuits][DallasArduino]は
[One Wireライブラリ][OneWire]を利用しますので，この2つのライブラリを事前にインストールしておいて
ください．

## ライセンスについて
このソフトは他のライブラリやソフトを拡張したものではないので，なんでも良いのですが，
このライブラリが利用している[Arduino Library for Maxim Temperature Integrated Circuits][DallasArduino]
がLGPLですので，それを踏襲します．

## 動作検証
動作確認には，秋月電子の[デジタル温度センサ（１ｗｉｒｅ）ＤＳ１８Ｂ２０＋][ProductPage]を利用しました．

|CPU| 機種 |ベンダ| 結果 | 備考 |
| :--- | :--- | :--- | :---: | :--- |
|AVR| [Uno R3][Uno]  |[Arduino][Arduino]|   ○   |      |
|       | [Mega2560 R3][Mega] |[Arduino][Arduino] |  ○    |      |
|       | [Leonardo Ethernet][LeonardoEth] |[Arduino][Arduino] |      |      |
|       | [Uno WiFi][UnoWiFi] |[Arduino][Arduino] |  ○   | |
|       | [Pro mini 3.3V][ProMini] | [Sparkfun][Sparkfun] |  ○   |      |
| ARM/M0+ | [M0 Pro][M0Pro] |[Arduino][Arduino] |○||
|ESP8266|[ESPr developer][ESPrDev]| [スイッチサイエンス][SwitchScience] |○||
|ESP32 | [ESPr one 32][ESPrOne32] | [スイッチサイエンス][SwitchScience] |×|　コンパイルエラー|

## 外部リンク

- センサ商品ページ [http://akizukidenshi.com/catalog/g/gI-05276/][ProductPage]
- 温度センサベースライブラリ [https://github.com/milesburton/Arduino-Temperature-Control-Library][DallasArduino]
- One Wireライブラリ [https://github.com/PaulStoffregen/OneWire][OneWire]
- Adafruit Unified Sensor Driver - [https://github.com/adafruit/Adafruit_Sensor][AdafruitUSD]
- Groveシールド - [https://www.seeedstudio.com/Base-Shield-V2-p-1378.html][shield]
- Arduino M0 Pro - [https://store.arduino.cc/usa/arduino-m0-pro][M0Pro]
- Arduino Due - [https://store.arduino.cc/usa/arduino-due][Due]
- Arduino Uno R3 - [https://store.arduino.cc/usa/arduino-uno-rev3][Uno]
- Arduino Uno WiFi - [https://store.arduino.cc/usa/arduino-uno-wifi-rev2][UnoWiFi]
- Arduino Leonardo Ethernet - [https://store.arduino.cc/usa/arduino-leonardo-eth][LeonardoEth]
- Arduino Mega2560 R3 - [https://store.arduino.cc/usa/arduino-mega-2560-rev3][Mega]
- Arduino Pro mini 328 - 3.3V/8MHz - [https://www.sparkfun.com/products/11114][ProMini]
- ESPr developer - [https://www.switch-science.com/catalog/2652/][ESPrDev]
- ESPr Developer用GROVEシールド - [https://www.switch-science.com/catalog/2811/][ESPrDevShield]
- ESpr one - [https://www.switch-science.com/catalog/2620/][ESPrOne]
- ESPr one 32 - [https://www.switch-science.com/catalog/3555/][ESPrOne32]
- Grove - [https://www.seeedstudio.io/category/Grove-c-1003.html][Grove]
- Seed Studio - [https://www.seeedstudio.io/][SeedStudio]
- Sparkfun Electronics - [https://www.sparkfun.com/][Sparkfun]
- スイッチサイエンス - [https://www.switch-science.com/][SwitchScience]

[Dallas]:https://www.maximintegrated.com/jp.html
[Grove]:https://www.seeedstudio.io/category/Grove-c-1003.html
[SeedStudio]:https://www.seeedstudio.io/
[ProductPage]:http://akizukidenshi.com/catalog/g/gI-05276/
[DallasArduino]:https://github.com/milesburton/Arduino-Temperature-Control-Library
[OneWire]:https://github.com/PaulStoffregen/OneWire
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
