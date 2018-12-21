# AusExGroveMagneticSwitch

このライブラリは，
[Seeed Studio][SeedStudio]の[Grove][Grove]システムのいろいろなセンサ類のライブラリを
Adafruitのセンサ統合ライブラリと同じAPIに修正してみるプロジェクトの一部で，
[Grove磁気スイッチ][ProductPage]用ドライバです．



## ベースとなるコード

ベースとなるコードはSeeedStudioの[技術Wiki][SeedWiki]のサンプルプログラムであり，[Seeed studioのGitHubのリポジトリ][GitHub]にも
掲載されているものを使っています．



## ライセンスについて
GitHubのリポジトリには，「MIT License」が指定されているので，
本ライブラリもこれを継承します．

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

* Seeed Studio技術Wiki [http://wiki.seeedstudio.com/Grove-Magnetic_Switch][SeedWiki]
* 商品ページ [https://www.seeedstudio.com/Grove-Magnetic-Switch-p-744.html][ProductPage]

[Grove]:https://www.seeedstudio.io/category/Grove-c-1003.html
[SeedStudio]:https://www.seeedstudio.io/
[ProductPage]:https://www.seeedstudio.com/Grove-Magnetic-Switch-p-744.html
[SeedWiki]:http://wiki.seeedstudio.com/Grove-Magnetic_Switch
[GitHub]:https://github.com/Seeed-Studio/Magnetic_Switch


