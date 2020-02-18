# SDカードの単体テストコード
## 概要
SDカードの単体テストコード


## 機器詳細
ｍｉｃｒｏＳＤカードスロット　レベルシフタ付きブレークアウト基板キット (AE-microSD-LLCNV)  
http://akizukidenshi.com/catalog/g/gK-14015/


## 回路図
![](../../Schematic/PNG/SD.png)

+ 通信はSPI
+ 電圧は5V
	- 素子の内部で3.3Vにレギュレート & レベル変換してくれるので，5V系マイコンで利用するにはとても便利
