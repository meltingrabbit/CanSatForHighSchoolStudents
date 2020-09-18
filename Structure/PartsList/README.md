# パーツリスト
## マイコン
| パーツ名 | 型番 | 概要 | 購入先URL |
| :--- | :--- | :--- | :--- |
| Arduino Nano | ARDUINO-A000005 |  | [SWITCH SCIENCE](https://www.switch-science.com/catalog/2554/) |

+ Arduino NanoはSRAMが2KBと極めて少なく，高度なことをするのは厳しいので，後継機でありSRAMが6KBの[Arduino Nano Every](https://www.switch-science.com/catalog/6199/)の方が好ましいだろう．
+ また，個人的にはESP32系列（例えば[ESPr® Developer 32](https://www.switch-science.com/catalog/3210/)）は更に高性能でWiFiやBLEが搭載されているので，非常に使い勝手が良いと思っている（Arduino互換ではあるが，若干異なるので注意）．

## センサ
| パーツ名 | 型番 | 概要 | 購入先URL |
| :--- | :--- | :--- | :--- |
| GPS | AE-GYSFDMAXB | 実装参考は[こちら](../../Arduino/Test_GPS) | [秋月電子通商](http://akizukidenshi.com/catalog/g/gK-09991/) |
| 9軸センサ | AE-BMX055 | 実装参考は[こちら](../../Arduino/Test_IMU) | [秋月電子通商](http://akizukidenshi.com/catalog/g/gK-13010/) |
| 気圧計 | GY-BMP280-3.3 | 実装参考は[こちら](../../Arduino/Test_Barometer) | [LED PARADISE](https://www.led-paradise.com/product/2334) |
| 光センサ | MI527 | CdSセルを使用したセンサ<br>実装参考は[こちら](../../Arduino/Test_Light) | [秋月電子通商](http://akizukidenshi.com/catalog/g/gI-00110/) |
| TTLシリアルJPEGカメラ | ADA-397 | 実装参考は[こちら](../../Arduino/Test_Camera) | [SWITCH SCIENCE](https://www.switch-science.com/catalog/1241/) |

## アクチュエータ
| パーツ名 | 型番 | 概要 | 購入先URL |
| :--- | :--- | :--- | :--- |
| サーボモータ | SG92R | 制御角±90°のサーボモータ<br>実装参考は[こちら](../../Arduino/Test_Servo) | [秋月電子通商](http://akizukidenshi.com/catalog/g/gM-08914/) |

## その他基板実装パーツ
| パーツ名 | 型番 | 概要 | 購入先URL |
| :--- | :--- | :--- | :--- |
| 1kΩ抵抗 |  | 光センサ用負荷抵抗 |  |
| 10kΩ抵抗 |  | カメラ通信ラインの分圧用 |  |
| ロングピンソケット 1×42(42P) | FHU-1x42SG | センサやマイコンと基板間にはんだしておくソケット<br>基板間の電源・通信ライン接続にも用いる | [秋月電子通商](http://akizukidenshi.com/catalog/g/gC-05779/) |
| 足の長いピンソケット(10P)| SSCI-014182 | 基板間の電源・通信ライン接続用 | [SWITCH SCIENCE](https://www.switch-science.com/catalog/1418/) |
| ピンヘッダ 1×40(40P) | PH-1x40SG | サーボのコネクタと基板間にはんだしておくピン<br>基板間の電源・通信ライン接続にも用いる | [秋月電子通商](http://akizukidenshi.com/catalog/g/gC-00167/) |
| microSDカードスロット | AE-microSD-LLCNV | microSDカードへの書き込み・読み取り回路基板<br>実装参考は[こちら](../../Arduino/Test_SD) | [秋月電子通商](http://akizukidenshi.com/catalog/g/gK-14015/) |
| トグルスイッチ | 2MS1-T1-B4-VS2-Q-E | 電源ON/OFF用スイッチ<br>実装参考は[こちら](../switch) | [秋月電子通商](http://akizukidenshi.com/catalog/g/gP-00300/) |
| DCジャック | AE-DC-POWER-JACK-DIP | DCプラグ接続用コネクタ基板 | [秋月電子通商](http://akizukidenshi.com/catalog/g/gK-05148/) |
| ジャンパワイヤ(オス-オス) | BBJ-65 | カメラ等を直接配線する用 | [秋月電子通商](http://akizukidenshi.com/catalog/g/gC-05159/) |
| メッキ線 | P-13310 | 基板にはんだ固定する導通経路用 | [秋月電子通商](http://akizukidenshi.com/catalog/g/gP-13310/) |
| 被覆線 |  | ジャンプ配線に用いる |  |
| カプトンテープ |  | 導通防止箇所に貼るテープ |  |

## 構造部材
| パーツ名 | 型番 | 概要 | 購入先URL |
| :--- | :--- | :--- | :--- |
| 丸型基板 | AE-50.8mm-TH | 回路実装基板 | [秋月電子通商](http://akizukidenshi.com/catalog/g/gP-08758/) |
| スペーサー(30mm) | TP-30 | 基板間締結用 | [秋月電子通商](http://akizukidenshi.com/catalog/g/gP-07572/) |
| スペーサー(20mm) | TP-20 | 基板間締結用 | [秋月電子通商](http://akizukidenshi.com/catalog/g/gP-07570/) |
| プラスチックナット・ボルト | P-01885 | 基板間締結用 | [秋月電子通商](http://akizukidenshi.com/catalog/g/gP-01885/) |

## 周辺機器
| パーツ名 | 型番 | 概要 | 購入先URL |
| :--- | :--- | :--- | :--- |
| ＤＣプラグ付バッテリースナップ | BS-IR-1/150MM+DC5.5X2.1X10MM | 電池とDCジャックの接続用 | [秋月電子通商](http://akizukidenshi.com/catalog/g/gP-07356/) |
| 9Vアルカリ角電池 | GL6F22A | 缶サット単体での起動用 | [秋月電子通商](http://akizukidenshi.com/catalog/g/gB-03257/) |
| microSDカード |  | ログデータ・画像データ保存用 |  |
| ACアダプタ | GF12-US1210 | 缶サット単体での起動用(電池を消耗したくないときコンセントから電源を取る) | [秋月電子通商](http://akizukidenshi.com/catalog/g/gM-01804/) |
| usbケーブル | USBcable A-miniB | PCとArduinoの接続用 | [秋月電子通商](http://akizukidenshi.com/catalog/g/gC-07606/) |
