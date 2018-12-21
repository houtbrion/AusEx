# AusExGroveDigitalLightSensorV2


このライブラリは，
[Seeed Studio][SeedStudio]の[Grove][Grove]システムのいろいろなセンサ類のライブラリを
Adafruitのセンサ統合ライブラリと同じAPIに修正してみるプロジェクトの一部で，
[Groveデジタル光センサ][ProductPage]用ドライバです．


Seeed studioの[Github][github]のプログラムを見ると，ISL29035とTSL2561のバージョンがあるようだが，
wikiの方にはTSL2561しか記述がなく，
TSL2561はadafruitのunified sensorライブラリがある．
そのため，本プログラムは，ISL29035用となっている．

なお，IRとかEVを測定するモードもあるが，
温湿度センサなどと同じくまっとうに対応するのは
面倒なので，今回は可視光のみに対応．

## ベースとなるコードとライセンス

ベースとなるコードはSeeedStudioの[Github][github]のプログラムであり，
『MIT License』となっているので，それに従います．

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

* Seeed Studio技術Wiki [http://wiki.seeedstudio.com/Grove-Digital_Light_Sensor/][SeedWiki]
* 商品ページ [https://www.seeedstudio.com/Grove-Digital-Light-Sensor-p-1281.html][ProductPage]
* ソースリポジトリ [https://github.com/Seeed-Studio/Grove_Digital_Light_Sensor][github]

[Grove]:https://www.seeedstudio.io/category/Grove-c-1003.html
[SeedStudio]:https://www.seeedstudio.io/
[ProductPage]:https://www.seeedstudio.com/Grove-Digital-Light-Sensor-p-1281.html
[SeedWiki]:http://wiki.seeedstudio.com/Grove-Digital_Light_Sensor/
[github]:https://github.com/Seeed-Studio/Grove_Digital_Light_Sensor



