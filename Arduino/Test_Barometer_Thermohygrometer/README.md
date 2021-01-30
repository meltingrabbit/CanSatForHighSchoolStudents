# 気圧計・温湿度計の単体テストコード
## 概要
気圧計の単体テストコード  
温度と湿度も取得可能  
気圧から高度が計算できる


## 機器詳細
気圧・温湿度センサ BME280  
https://akizukidenshi.com/catalog/g/gK-09421/


## 回路図
![](../../Schematic/PNG/BarometerThermohygrometer.png)

+ 通信はI2C
+ 電圧は3.3V
	- I2Cの信号線は，レベル変換を挟むとなお良い
+ J1, J2, J3をはんだでショートさせ，I2Cとして使う

## ソースコードへのリンク
[GitHub](https://github.com/meltingrabbit/CanSatForHighSchoolStudents/tree/master/Arduino/Test_Barometer_Thermohygrometer)
