# AusExGrovePirSensor

このライブラリは，
[Seeed Studio][SeedStudio]の[Grove][Grove]システムのいろいろなセンサ類のライブラリを
Adafruitのセンサ統合ライブラリと同じAPIに修正してみるプロジェクトの一部で，
[GrovePIRセンサ][ProductPage]用ドライバです．


## ライセンスについて

このドライバは，[Github][GitHub]の
[GrovePIRセンサ][ProductPage]用サンプルプログラムをベースにしており，
該当ドライバは「The MIT License (MIT)」となっているので，それを踏襲します．


## 動作検証

|CPU| 機種 |ベンダ| 結果 | 備考 |
| :--- | :--- | :--- | :---: | :--- |
|AVR| Uno  |Arduino|       |      |
|       | Mega | |      |      |
| ARM/M3 | Due | Arduino | | |
| ARM/M0+ | M0 Pro | |||
|ESP8266| ESPr One|スイッチサイエンス| | |
|ESP32 | ESPr one 32 | スイッチサイエンス ||　|

## 外部リンク

* Seeed Studio技術Wiki [http://wiki.seeedstudio.com/Grove-PIR_Motion_Sensor/][SeedWiki]
* 商品ページ [https://www.seeedstudio.com/Grove-PIR-Motion-Sensor-p-802.html][ProductPage]

[Grove]:https://www.seeedstudio.io/category/Grove-c-1003.html
[SeedStudio]:https://www.seeedstudio.io/
[ProductPage]:https://www.seeedstudio.com/Grove-Dust-Sensor-p-1050.html
[SeedWiki]:http://wiki.seeedstudio.com/Grove-PIR_Motion_Sensor/
[GitHub]:https://github.com/Seeed-Studio/PIR_Motion_Sensor
