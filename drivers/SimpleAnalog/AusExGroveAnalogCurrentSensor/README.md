# AusExGroveAnalogCurrentSensor

このライブラリ(センサ類のドライバ)は，
[Adafruitのセンサ統合ライブラリ][AdafruitUSD]を拡張した上で，いろいろなセンサ類を
[統合ライブラリ][AdafruitUSD]のAPIでアクセス可能にするプロジェクトの一部で，
[Grove電流センサ][ProductPage]用ドライバです．



## 仕様

|項目|値|単位など|
|:---|---:|:---|
|入力電流最大|5|A|

## ライセンスについて
このドライバは，[Seeed studioのwiki][SeedWiki]のソースに基づいていますので，
ライセンスはseeed studioのライセンスに従います．

ただし，wikiのページには，ライセンス条項の記載がないので，
気になる人は，seeed studioに問い合わせてください．



## 使い方
apiは共通のもののみ，センサからの出力値はmAに変換してfloat型で出力される．

デフォルトでは，平均電流を出力するが，setMode(1)でピーク電流を出力する動作にかわる．
なお，setMode()を行うと，getSensor()の返り値のセンサ値の最大値(max_value)も変化するので
要注意．

また，クラス生成時の引数にVDDを指定することが可能であるが，Groveの電流センサは
5Vのマイコンでしか動作しないため，3.3V系のArduinoで利用する場合は，電圧変換回路を
通して使う必要があり，そのような回路を使った場合のための引数になっている
(デフォルトはVDDが5Vと想定)．

ただし，Seeed studioのセンサのページを見ると，入力が最大5Aで2000対1で抵抗が800オーム
となっているので，最大出力電圧は2Vになるはず．そのまま3.3V系の回路につないでも
うごかなくはなさそう(こわいけど)だが，そのような配線には対応していません．
センサの動作モードを増やせば良いだけなのだが，なんかあったときに3.3VのArduinoに
5Vがかかると怖いので，現状対応するつもりはないです．


## 動作検証
ソース上は変換回路付きでの3.3V動作も対応していますが，分圧回路を組んで検証する余力(気力)がないので
3.3V系のArduino(と互換機)は検証していません．

|CPU| 機種 |ベンダ| 結果 | 備考 |
| :--- | :--- | :--- | :---: | :--- |
|AVR| [Uno R3][Uno]  |[Arduino][Arduino]| ○ |      |
|       | [Mega2560 R3][Mega] |[Arduino][Arduino] |  ○    |      |
|       | [Leonardo Ethernet][LeonardoEth] |[Arduino][Arduino] | ○ |      |
|       | [Uno WiFi][UnoWiFi] |[Arduino][Arduino] | ○ | 
|       | [Pro mini 3.3V][ProMini] | [Sparkfun][Sparkfun] |     |      |
| ARM/M0+ | [M0 Pro][M0Pro] |[Arduino][Arduino] |||
|ESP8266|[ESPr developer][ESPrDev]| [スイッチサイエンス][SwitchScience] |||
|ESP32 | [ESPr one 32][ESPrOne32] | [スイッチサイエンス][SwitchScience] ||　|


## 外部リンク


- Seeed Studio技術Wiki [http://wiki.seeedstudio.com/Grove-Electricity_Sensor/][SeedWiki]
- 商品ページ [https://www.seeedstudio.com/Grove-Electricity-Sensor-p-777.html][ProductPage]
- gitリポジトリ [https://github.com/houtbrion/arduino-grove/blob/master/Electricity_Sensor/Electricity_Sensor.ino][github]
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
[ProductPage]:https://www.seeedstudio.com/Grove-Electricity-Sensor-p-777.html
[SeedWiki]:http://wiki.seeedstudio.com/Grove-Electricity_Sensor/
[github]:https://github.com/houtbrion/arduino-grove/blob/master/Electricity_Sensor/Electricity_Sensor.ino
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
