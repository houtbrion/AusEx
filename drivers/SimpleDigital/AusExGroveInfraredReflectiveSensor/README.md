# AusExGroveInfraredReflectiveSensor


このライブラリは，
[Seeed Studio][SeedStudio]の[Grove][Grove]システムのいろいろなセンサ類のライブラリを
Adafruitのセンサ統合ライブラリと同じAPIに修正してみるプロジェクトの一部で，
[Grove赤外線反射センサ][ProductPage]用ドライバです．

## 仕様

|項目|値|単位など|
|:---|---:|:---|
|動作電圧|3.3/5|V|
|動作電流|14.69-15.35|mA|
|有効距離|4-15|mm|
|センサ応答時間|10|μs|
|センサピーク周波数|800|nm|
|LEDピーク周波数|940|nm|


## ライセンスについて

このドライバは，[Seeed Studioのwiki上のサンプルプログラム][SeedWiki]がベースに
なっているのですが，サンプルプログラムにライセンス表記がないことと，seeedstudioのGithubのページを見ても，
このセンサに対応するドライバ(ライブラリ)のリポジトリを発見できなかったため，
あえて宣言しません．気になる人はseeed studioに確認してください．



## 動作検証

|CPU| 機種 |ベンダ| 結果 | 備考 |
| :--- | :--- | :--- | :---: | :--- |
|AVR| [Uno R3][Uno]  |[Arduino][Arduino]|  ○    |      |
|       | [Mega2560 R3][Mega] |[Arduino][Arduino] |  ○    |      |
|       | [Leonardo Ethernet][LeonardoEth] |[Arduino][Arduino] | ○     |      |
|       | [Uno WiFi][UnoWiFi] |[Arduino][Arduino] | ○     |
|       | [Pro mini 3.3V][ProMini] | [Sparkfun][Sparkfun] |   ○   |      |
| ARM/M0+ | [M0 Pro][M0Pro] |[Arduino][Arduino] |×|*1|
|ESP8266|[ESPr developer][ESPrDev]| [スイッチサイエンス][SwitchScience] |×|*1|
|ESP32 | [ESPr one 32][ESPrOne32] | [スイッチサイエンス][SwitchScience] |×|*1|

<d1>
<dt>＊1</dt><dd>感度の調整がうまくいかない．</dd>
</d1>

## 使い方
このセンサは0/1を返すだけのシンプルなセンサで，動作モードなどもない．
そのため，AusEx標準APIのみでgetMode()やsetMode()は-1を返すだけ．


## 外部リンク

- Seeed Studio技術Wiki [http://wiki.seeedstudio.com/Grove-Infrared_Reflective_Sensor/][SeedWiki]
- 商品ページ [https://www.seeedstudio.com/Grove-Infrared-Reflective-Sensor-v1.2-p-2791.html][ProductPage]
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

<!-- 以下は，外部リンクの定義 -->


[Grove]:https://www.seeedstudio.io/category/Grove-c-1003.html
[SeedStudio]:https://www.seeedstudio.io/
[ProductPage]:https://www.seeedstudio.com/Grove-Infrared-Reflective-Sensor-v1.2-p-2791.html
[SeedWiki]:http://wiki.seeedstudio.com/Grove-Infrared_Reflective_Sensor/
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
