# AusExGroveI2cTouchSensor

このライブラリ(センサ類のドライバ)は，
[Adafruitのセンサ統合ライブラリ][AdafruitUSD]を拡張した上で，いろいろなセンサ類を
[統合ライブラリ][AdafruitUSD]のAPIでアクセス可能にするプロジェクトの一部で，
[GroveI2C接続タッチセンサ][ProductPage]用ドライバです．

本デバイスは，
FreeScaleのMPR121で最大12個のタッチセンサを同居させているけど，12個のセンサとして
取り扱うのが面倒なので，16bitのintの各ビットに1つのタッチデバイスを
割り当てています．

そのため，このセンサクラスには，16bitのintから，各タッチデバイスの
値がどうなっているかを確認するためのメンバ関数を追加しています．

## 仕様

|項目|値|単位|
|:---|---:|:---|
|動作電圧|3-5.5|V|
|待機時電流|2|μA|
|I2Cアドレス|0x5A-0x5D||


## ベースとなるコードとライセンス

ベースとなるコードはSeeedStudioの[Githubのプログラム][github]であり，
『LGPL v2.1』となっているので，それに従います．

## 動作検証
|CPU| 機種 |ベンダ| 結果 | 備考 |
| :--- | :--- | :--- | :---: | :--- |
|AVR| [Uno R3][Uno]  |[Arduino][Arduino]|  ○    |      |
|       | [Mega2560 R3][Mega] |[Arduino][Arduino] |  ○    |      |
|       | [Leonardo Ethernet][LeonardoEth] |[Arduino][Arduino] | ○     |      |
|       | [Uno WiFi][UnoWiFi] |[Arduino][Arduino] | ○     | 
|       | [Pro mini 3.3V][ProMini] | [Sparkfun][Sparkfun] |   ×   |      |
| ARM/M0+ | [M0 Pro][M0Pro] |[Arduino][Arduino] |○||
|ESP8266|[ESPr developer][ESPrDev]| [スイッチサイエンス][SwitchScience] |○||
|ESP32 | [ESPr one 32][ESPrOne32] | [スイッチサイエンス][SwitchScience] ||未検証|

Arduino Pro miniは，動作確認に利用した自作の拡張基板が原因の可能性もあるので，動作しないと
確定したわけではありません．暇ができたら，基板から外して試してみます．

## 使い方
このタッチセンサはたくさん触れる部分があり，どこが触られているかを「uint32_t」の値1つに
まとめて返してくるため，分離する必要があります．

それをサポートするためにメンバ関数を1つ「getTouchState()」追加しています．
この関数は第一引数にセンサから取得した値をとり，第2引数に何番目のパネルかを
指定することで，そのパネルが触られているか否かをboolで返します．

```
bool getTouchState(uint32_t val, uint8_t num);
```



## 外部リンク


- Seeed Studio技術Wiki [http://wiki.seeedstudio.com/Grove-I2C_Touch_Sensor/][SeedWiki]
- 商品ページ [https://www.seeedstudio.com/Grove-I2C-Touch-Sensor-p-840.html][ProductPage]
- ソースリポジトリ [https://github.com/Seeed-Studio/Grove_I2C_Touch_Sensor][ProductPage]
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
- ESpr one - [https://www.switch-science.com/catalog/2620/][ESPrOne]
- ESPr one 32 - [https://www.switch-science.com/catalog/3555/][ESPrOne32]
- Grove - [https://www.seeedstudio.io/category/Grove-c-1003.html][Grove]
- Seed Studio - [https://www.seeedstudio.io/][SeedStudio]
- Sparkfun Electronics - [https://www.sparkfun.com/][Sparkfun]
- スイッチサイエンス - [https://www.switch-science.com/][SwitchScience]

<!-- 以下は，外部リンクの定義 -->
[Grove]:https://www.seeedstudio.io/category/Grove-c-1003.html
[SeedStudio]:https://www.seeedstudio.io/
[ProductPage]:https://www.seeedstudio.com/Grove-I2C-Touch-Sensor-p-840.html
[SeedWiki]:http://wiki.seeedstudio.com/Grove-I2C_Touch_Sensor/
[github]:https://github.com/Seeed-Studio/Grove_I2C_Touch_Sensor
[AdafruitUSD]:https://github.com/adafruit/Adafruit_Sensor
[shield]:https://www.seeedstudio.com/Base-Shield-V2-p-1378.html
[M0Pro]:https://store.arduino.cc/usa/arduino-m0-pro
[Due]:https://store.arduino.cc/usa/arduino-due
[Uno]:https://store.arduino.cc/usa/arduino-uno-rev3
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
