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


## ソースコードへのリンク
[GitHub](https://github.com/meltingrabbit/CanSatForHighSchoolStudents/tree/master/Arduino/Test)