# IMU（９軸センサ）の単体テストコード
## 概要
IMU（９軸センサ）の単体テストコード  
９軸センサとは，以下のセンサがそれぞれ３軸あることによる

+ 加速度
+ 角加速度
+ 地磁気


## 機器詳細
ＢＭＸ０５５使用９軸センサーモジュール  
http://akizukidenshi.com/catalog/g/gK-13010/


## 回路図
![](../../Schematic/PNG/IMU.png)

+ 通信はI2C
+ 電圧は5V
	- 電源電圧，通信電圧は，素子のジャンパで5Vと3.3Vで選択可能
	- ここでは，JP6のみをショートさせ，ともに5Vとして使用している
	- 詳細はデータシートを参照のこと

## ソースコードへのリンク
[GitHub](https://github.com/meltingrabbit/CanSatForHighSchoolStudents/tree/master/Arduino/Test_IMU)
