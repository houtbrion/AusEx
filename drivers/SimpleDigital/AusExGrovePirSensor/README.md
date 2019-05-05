# AusExGrovePirSensor

このライブラリは，
[Seeed Studio][SeedStudio]の[Grove][Grove]システムのいろいろなセンサ類のライブラリを
Adafruitのセンサ統合ライブラリと同じAPIに修正してみるプロジェクトの一部で，一般的な
デジタル端子のHigh,Lowを読み取るタイプのドライバです．

ドライバの名前は[GrovePIRセンサ][ProductPage]から取っていますが，他社製のPirセンサ
でも動作するため，名前の由来は動作確認に[GrovePIRセンサ][ProductPage]を使いましたという
だけに近い状態です．

## ライセンスについて

このドライバは，[Github][GitHub]の
[GrovePIRセンサ][ProductPage]用サンプルプログラムをベースにしており，
該当ドライバは「The MIT License (MIT)」となっているので，それを踏襲します．


## 動作検証

|CPU| 機種 |ベンダ| 結果 | 備考 |
| :--- | :--- | :--- | :---: | :--- |
|AVR| Uno Wifi Developer edition  |[Arduino][Arduino]| ○ |  |
|       | [Mega2560 R3][Mega] |[Arduino][Arduino] | ○ |  |
|       | [Leonardo Ethernet][LeonardoEth] |[Arduino][Arduino] | ○ | |
|       | [Uno WiFi][UnoWiFi] |[Arduino][Arduino] | ○ | |
|       | [Pro mini 3.3V][ProMini] | [Sparkfun][Sparkfun] | ○ | |
| ARM/M0+ | [M0 Pro][M0Pro] |[Arduino][Arduino]| ○ ||
|ESP8266| [ESPr developer][ESPrDev]| [スイッチサイエンス][SwitchScience]| △ | |
|ESP32 |[ESPr one 32][ESPrOne32] | [スイッチサイエンス][SwitchScience] | ○ |　|

ESP8266は誤判定が多いです．あと，パナソニックのPIRセンサでも動作させましたが，
電源投入後，測定値が安定するまでに30秒かかるとデータシートにあるように，
動作開始直後は測定値が乱れます．あと，データシートには検出対象がなくなったらすぐに
測定値が0に変化するはずですが，実機で試したところ，測定対象が現れたときはすぐに
反応するのですが，なくなった場合は数秒間なくなったことを検出(測定値が0になる)
しないです．

本来なら，min_delayに値を入れるべきですが，PIRセンサの種類によってちがうことと，
個体差，検出対象が現れた場合の反応が早いことなども考えると真面目に測定するコストが個人の作業では無理なので
min_delayはとりあえず0にしてあります．

## 利用上の注意
一般的なPirセンサは動作モードを持たないので，setMode()やgetMode()に意味は無い状態です．

## 外部リンク

- Seeed Studio技術Wiki [http://wiki.seeedstudio.com/Grove-PIR_Motion_Sensor/][SeedWiki]
- 商品ページ [https://www.seeedstudio.com/Grove-PIR-Motion-Sensor-p-802.html][ProductPage]
- Seeed Studioソースリポジトリ [https://github.com/Seeed-Studio/Accelerometer_ADXL345][Github]
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
- ESPr developer - [https://www.switch-science.com/catalog/2652/][ESPrDev]
- ESPr Developer用GROVEシールド - [https://www.switch-science.com/catalog/2811/][ESPrDevShield]
- ESpr one - [https://www.switch-science.com/catalog/2620/][ESPrOne]
- ESPr one 32 - [https://www.switch-science.com/catalog/3555/][ESPrOne32]
- Grove - [https://www.seeedstudio.io/category/Grove-c-1003.html][Grove]
- Seed Studio - [https://www.seeedstudio.io/][SeedStudio]
- Sparkfun Electronics - [https://www.sparkfun.com/][Sparkfun]
- スイッチサイエンス - [https://www.switch-science.com/][SwitchScience]


[Grove]:https://www.seeedstudio.io/category/Grove-c-1003.html
[SeedStudio]:https://www.seeedstudio.io/
[Adafruit]:https://www.adafruit.com/
[ProductPage]:https://www.seeedstudio.com/Grove-Dust-Sensor-p-1050.html
[SeedWiki]:http://wiki.seeedstudio.com/Grove-3-Axis_Digital_Accelerometer-16g/
[GitHub]:https://github.com/Seeed-Studio/PIR_Motion_Sensor
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