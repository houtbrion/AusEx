# AusExTEMT6000
このドライバは，
[Adafruitのセンサ統合ライブラリ][AdafruitUSD]を拡張した上で，いろいろなセンサ類を
[統合ライブラリ][AdafruitUSD]のAPIでアクセス可能にするプロジェクトの一部で，
VishayセミコンダクタのTEMT6000用のドライバです．


## ベースとなるコードとライセンス

ベースとなるコードは[Adafruit][Adafruit]の[Githubのプログラム][AdafruitGithub]で，
『BSD Liceense』となっているので，それに従います．


なお，Adafrutiのコードをベースにした理由は以下の2点です．
 - AdafruitのドライバのみSPIをサポートしている
 - 統合するインターフェースはAdaruitのものであるため，Adafruitのコードのほうが変更量が少なくてすむ．

 あと，元のAdafuitのドライバからインターフェース関係以外で変更した主要は部分は以下の通りです．
 - ハードウェアSPIのサポート

ただし，TEMT6000はアナログインターフェースしかないため，SPIの件は無関係です．

## 動作検証

手元にあるTEMT6000が，Arduino MKR ENVシールドに搭載されたチップのみであるため，動作確認は
MKRシリーズのSAMDアーキテクチャ(MKR WiFi1010)のみで実施した．


## 外部リンク

- Adafruit Unified Sensor Driver - [https://github.com/adafruit/Adafruit_Sensor][AdafruitUSD]
- Grove - [https://www.seeedstudio.io/category/Grove-c-1003.html][Grove]
- Seed Studio - [https://www.seeedstudio.io/][SeedStudio]


<!-- 以下は，外部リンクの定義 -->
[Grove]:https://www.seeedstudio.io/category/Grove-c-1003.html
[SeedStudio]:https://www.seeedstudio.io/
[Adafruit]:https://www.adafruit.com/
[github]:https://github.com/adafruit/Adafruit_BME280_Library
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
