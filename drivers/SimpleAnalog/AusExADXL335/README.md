# AusExGrove3AxisAnalogAccelerometer AusEx library template for simple analog sensor
このライブラリは，いろいろなセンサ類(主にseeed studioのGroveシステムのもの)のライブラリを
Adafruitのセンサ統合ライブラリと同じAPIに修正してみるプロジェクトの一部で，[Grove - 3-Axis Analog Accelerometer][ProductPage]に
搭載されているADXL335用ライブラリです．


## ライセンスについて
基本的に，アナログ端子3つから，値に変換するだけなので，参考にさせてもらったベースのソースと同じなのは値の変換式だけですが，
ライセンスは継承します．

参照したのは，Seeed Studioの[公式リポジトリ][github]です．こちらでは，「MIT」ライセンスと
なっているので，このライブラリもMITライセンスとなります．

## 動作検証
|CPU| 機種 |ベンダ| 結果 | 備考 |
| :--- | :--- | :--- | :---: | :--- |
|AVR| [Uno R3][Uno]  |[Arduino][Arduino]|  ○    |      |
|       | [Mega2560 R3][Mega] |[Arduino][Arduino] |  ○    |      |
|       | [Leonardo Ethernet][LeonardoEth] |[Arduino][Arduino] |  △   | 値が微妙に小さい(キャリブレーションが絶対必要) |
|       | [Uno WiFi][UnoWiFi] |[Arduino][Arduino] |   ○   | |
|       | [Pro mini 3.3V][ProMini] | [Sparkfun][Sparkfun] |      |   配線などの関係で未確認   |
| ARM/M0+ | [M0 Pro][M0Pro] |[Arduino][Arduino] |×|非常に大きな値がでる(キャリブレーションで治るかどうか微妙)|
|ESP8266|[ESPr developer][ESPrDev]| [スイッチサイエンス][SwitchScience] |||
|ESP32 | [ESPr one 32][ESPrOne32] | [スイッチサイエンス][SwitchScience] ||　|

esp8266とesp32はアナログ端子の性質・数のため検証不可．

## 外部リンク

- Seeed Studio技術Wiki [http://wiki.seeedstudio.com/Grove-3-Axis_Analog_Accelerometer/][SeedWiki]
- センサ商品ページ [https://www.seeedstudio.com/Grove-3-Axis-Analog-Accelerometer-p-1086.html][ProductPage]
- ソースリポジトリ [https://github.com/Seeed-Studio/Accelerometer_ADXL335][github]
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
[ProductPage]:https://www.seeedstudio.com/Grove-3-Axis-Analog-Accelerometer-p-1086.html
[SeedWiki]:http://wiki.seeedstudio.com/Grove-3-Axis_Analog_Accelerometer/
[github]:https://github.com/Seeed-Studio/Accelerometer_ADXL335
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
