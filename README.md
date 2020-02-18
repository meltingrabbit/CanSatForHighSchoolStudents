# 高校生のためのCanSat開発キット
## 概要
+ 高校生向け缶サット開発キットのためのコード類
+ Arduino Nanoを想定


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
	- [GPSの単体テスト](./Arduino/Test_GPS)
	- [9軸センサの単体テスト](./Arduino/Test_IMU)
	- [高度計（気圧計）の単体テスト](./Arduino/Test_Barometer)
	- [光センサの単体テスト](./Arduino/Test_Light)
	- [カメラの単体テスト](./Arduino/Test_Camera)
	- [サーボモータの単体テスト](./Arduino/Test_Servo)
	- [SDカードの単体テスト](./Arduino/Test_SD)
	- [全機器の統合状態のテスト](./Arduino/Test)
+ `./Schematic` ：回路図
