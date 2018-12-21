# AusExGrove3AxisCompass

このライブラリは，
[Seeed Studio][SeedStudio]の[Grove][Grove]システムのいろいろなセンサ類のライブラリを
Adafruitのセンサ統合ライブラリと同じAPIに修正してみるプロジェクトの一部で，
[Grove3軸コンパス][ProductPage]用ドライバです．


搭載されているセンサは「HMC5883L」です．


## ベースとなるコードとライセンス

ベースとなるコードはSeeedStudioの[Github][github]のプログラムであり，ライセンスは『LGPL v2.1』
となっているので，それに従います．

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

* Seeed Studio技術Wiki [http://wiki.seeedstudio.com/Grove-3-Axis_Compass_V1.0/][SeedWiki]
* 商品ページ [https://www.seeedstudio.com/Grove-3-Axis-Digital-Compass-p-759.html][ProductPage]
* ソースリポジトリ [https://github.com/Seeed-Studio/Grove_3Axis_Digital_Compass_HMC5883L][github]

[Grove]:https://www.seeedstudio.io/category/Grove-c-1003.html
[SeedStudio]:https://www.seeedstudio.io/
[ProductPage]:https://www.seeedstudio.com/Grove-3-Axis-Digital-Compass-p-759.html
[SeedWiki]:http://wiki.seeedstudio.com/Grove-3-Axis_Compass_V1.0/
[github]:https://github.com/Seeed-Studio/Grove_3Axis_Digital_Compass_HMC5883L


