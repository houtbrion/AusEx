# AusExGrove3AxisDigitalGyro

このライブラリ(センサ類のドライバ)は，
[Adafruitのセンサ統合ライブラリ][AdafruitUSD]を拡張した上で，いろいろなセンサ類を
[統合ライブラリ][AdafruitUSD]のAPIでアクセス可能にするプロジェクトの一部で，
[Grove3軸ジャイロ][ProductPage]用ドライバです．

## 仕様

搭載されているセンサは「ITG 3200」です.

|項目|値|単位|
|:---|---:|:---|
|動作電圧|3.3/5|V|
|動作時電流|6.5|mA|
|待機時電流|5|μA|
|感度|14|LSBs per °/sec|
|測定範囲| ±2000|°/sec|
|加速度|10,000g|(for 0.3ms)|
|その他|On-chip温度センサ|　|



## ベースとなるコードとライセンス

ベースとなるコードはSeeedStudioの[Githubのプログラム][github]であり，
『MIT License』となっているので，それに従います．


## 動作検証

|CPU| 機種 |ベンダ| 結果 | 備考 |
| :--- | :--- | :--- | :---: | :--- |
|AVR| [Uno R3][Uno]  |[Arduino][Arduino]|  ○    |      |
|       | [Mega2560 R3][Mega] |[Arduino][Arduino] |  ○    |      |
|       | [Leonardo Ethernet][LeonardoEth] |[Arduino][Arduino] | ○     |      |
|       | [Pro mini 3.3V][ProMini] | [Sparkfun][Sparkfun] |   ×   |      |
| ARM/M0+ | [M0 Pro][M0Pro] |[Arduino][Arduino] |○||
|ESP32 | [ESPr one 32][ESPrOne32] | [スイッチサイエンス][SwitchScience] |×|　|


## 外部リンク

- Seeed Studio技術Wiki [http://wiki.seeedstudio.com/Grove-3-Axis_Digital_Gyro/][SeedWiki]
- 商品ページ [https://www.seeedstudio.com/Grove-3-Axis-Digital-Gyro-p-750.html][ProductPage]
- ソースリポジトリ [https://github.com/Seeed-Studio/Grove_3_Axis_Digital_Gyro][github]
- Adafruit Unified Sensor Driver - [https://github.com/adafruit/Adafruit_Sensor][AdafruitUSD]
- Groveシールド - [https://www.seeedstudio.com/Base-Shield-V2-p-1378.html][shield]
- Arduino M0 Pro - [https://store.arduino.cc/usa/arduino-m0-pro][M0Pro]
- Arduino Due - [https://store.arduino.cc/usa/arduino-due][Due]
- Arduino Uno R3 - [https://store.arduino.cc/usa/arduino-uno-rev3][Uno]
- Arduino Leonardo Ethernet - [https://store.arduino.cc/usa/arduino-leonardo-eth][LeonardoEth]
- Arduino Mega2560 R3 - [https://store.arduino.cc/usa/arduino-mega-2560-rev3][Mega]
- Arduino Pro mini 328 - 3.3V/8MHz - [https://www.sparkfun.com/products/11114][ProMini]
- ESpr one - [https://www.switch-science.com/catalog/2620/][ESPrOne]
- ESPr one 32 - [https://www.switch-science.com/catalog/3555/][ESPrOne32]
- Grove - [https://www.seeedstudio.io/category/Grove-c-1003.html][Grove]
- Seed Studio - [https://www.seeedstudio.io/][SeedStudio]
- Sparkfun Electronics - [https://www.sparkfun.com/][Sparkfun]
- スイッチサイエンス - [https://www.switch-science.com/][SwitchScience]

<!-- 以下は，外部リンクの定義 -->
[Grove]:https://www.seeedstudio.io/category/Grove-c-1003.html
[SeedStudio]:https://www.seeedstudio.io/
[ProductPage]:https://www.seeedstudio.com/Grove-3-Axis-Digital-Gyro-p-750.html
[SeedWiki]:http://wiki.seeedstudio.com/Grove-3-Axis_Digital_Gyro/
[github]:https://github.com/Seeed-Studio/Grove_3_Axis_Digital_Gyro
[AdafruitUSD]:https://github.com/adafruit/Adafruit_Sensor
[shield]:https://www.seeedstudio.com/Base-Shield-V2-p-1378.html
[M0Pro]:https://store.arduino.cc/usa/arduino-m0-pro
[Due]:https://store.arduino.cc/usa/arduino-due
[Uno]:https://store.arduino.cc/usa/arduino-uno-rev3
[Mega]:https://store.arduino.cc/usa/arduino-mega-2560-rev3
[LeonardoEth]:https://store.arduino.cc/usa/arduino-leonardo-eth
[ProMini]:https://www.sparkfun.com/products/11114
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
