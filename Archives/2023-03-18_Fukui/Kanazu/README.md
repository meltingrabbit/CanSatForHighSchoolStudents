# 統合テストコード
## 概要
各センサ，アクチュエータを統合して動かすためのテストコード  
個々の機器については，それぞれの単体テストコードを参照のこと．


## 回路図
![](../../Schematic/PNG/All.png)


## 既知の問題
+ Arduino Nanoではメモリ容量が足りないため，動作が不安定になる．
	- 適宜センサを減らすこと．
+ 後継機であるArduino Nano Everyを用いれば，SRAMが３倍になるので問題ない．


## 注意
+ 高度計（気圧計）・温湿度計は，秋月電子のものを載せている．スイッチサイエンスのものの場合は [こちら](../Test_Barometer_Thermohygrometer) を参照すること．なお，ソースコードはそのままでOK．
+ IMU (9軸センサ) は，秋月電子のもの (BMX055) である．スイッチサイエンスのもの (Pololu MinIMU-9 v5) の場合は [こちら](../Test_IMU_Pololu) を参照すること．


## ソースコードへのリンク
[GitHub](https://github.com/meltingrabbit/CanSatForHighSchoolStudents/tree/master/Arduino/Test)
