# 高校生のためのCanSat開発キット
## 概要
+ 高校生向け缶サット開発キット
+ Arduino Nanoを想定

<img src="./Structure/overview_in_bottle.jpg" width="30%"> <img src="./Structure/overview.jpg" width="30%">
<img src="./Structure/board_side.jpg" width="50%">



## 搭載機器
### センサ
+ GPS
+ 9軸センサ
+ 高度計（気圧計）
+ 光センサ
+ カメラ

### アクチュエータ
+ サーボモータ

### ストレージ
+ SDカード


## フォルダ構成
+ `./Arduino` ：サンプルコードとその設定など
	- 機器のテストコード（動作試験）
		* [GPSの単体テスト](./Arduino/Test_GPS)
		* [9軸センサの単体テスト](./Arduino/Test_IMU)
		* [高度計（気圧計）の単体テスト](./Arduino/Test_Barometer)
		* [光センサの単体テスト](./Arduino/Test_Light)
		* [カメラの単体テスト](./Arduino/Test_Camera)
		* [サーボモータの単体テスト](./Arduino/Test_Servo)
		* [SDカードの単体テスト](./Arduino/Test_SD)
		* [全機器の統合状態のテスト](./Arduino/Test)
	- プログラミング講習
		* [HelloWorld](./Arduino/ProgrammingTtutorial01_HelloWorld)
+ `./Schematic` ：[回路図](./Schematic)
+ `./Structure` ：[構造など](./Structure)
