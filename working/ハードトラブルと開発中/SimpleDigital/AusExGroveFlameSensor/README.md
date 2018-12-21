# AusExGroveFlameSensor

このライブラリは，
[Seeed Studio][SeedStudio]の[Grove][Grove]システムのいろいろなセンサ類のライブラリを
Adafruitのセンサ統合ライブラリと同じAPIに修正してみるプロジェクトの一部で，
[Grove火炎センサ][FlameSensor]用ドライバです．

このモジュールに搭載されているセンサ本体は「YG1006 」です．

## ベースとなるコードとライセンス

ベースとなるコードはSeeedStudioの[Seeed StudioのGitHubのリポジトリ][SeeedGit]のプログラムで，ライセンスとしては「The MIT License (MIT)」となっていますので，これを継承します．


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

* Seeed Studio技術Wiki [http://wiki.seeedstudio.com/Grove-Flame_Sensor/][SeedWiki]
* 商品ページ [https://www.seeedstudio.com/Grove-Flame-Sensor-p-1450.html][FlameSensor]



[Grove]:https://www.seeedstudio.io/category/Grove-c-1003.html
[SeedStudio]:https://www.seeedstudio.io/
[FlameSensor]:https://www.seeedstudio.com/Grove-Flame-Sensor-p-1450.html
[SeeedGit]:https://github.com/Seeed-Studio/Grove_Flame_Sensor
[SeedWiki]:http://wiki.seeedstudio.com/Grove-Flame_Sensor/
