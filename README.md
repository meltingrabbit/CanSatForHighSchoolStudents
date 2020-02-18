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
	- [GPSの単体テストコード](./Arduino/Test_GPS)
	- [9軸センサの単体テストコード](./Arduino/Test_IMU)
	- [高度計（気圧計）の単体テストコード](./Arduino/Test_Barometer)
	- [光センサの単体テストコード](./Arduino/Test_Light)
	- [カメラの単体テストコード](./Arduino/Test_Camera)
	- [サーボモータの単体テストコード](./Arduino/Test_Servo)
	- [SDカードの単体テストコード](./Arduino/Test_SD)
+ `./Schematic`
	- 回路図