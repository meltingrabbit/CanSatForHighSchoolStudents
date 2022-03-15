# SDカードの単体テストコード
## 概要
SDカードの単体テストコード


## 機器詳細
ｍｉｃｒｏＳＤカードスロット　レベルシフタ付きブレークアウト基板キット (AE-microSD-LLCNV)  
http://akizukidenshi.com/catalog/g/gK-14015/


## 回路図
![](../../Schematic/PNG/SD.png)

| 素子 Pin | Arduino Pin | 備考 |
| ---- | ---- | ---- |
| 5V IN | 5V | 5V 電源 |
| 3.3V ENABLE | - | 3.3V 内部レギュレータ ON/OFF．ここではJ1 をショートして使うため，接続不要． |
| 3.3V OUT | - | 内部3.3Vレギュレータ出力．未使用． |
| GND | GND | GND |
| SCL | D13 (SCL) | SPI のシリアルクロック |
| DATA | D12 (MISO) | SPI の受信データ (Master In Slave Out) |
| CMD | D11 (MOSI) | SPI の送信データ (Master Out Slave In) |
| CS | D10 (SS) | チップセレクト |
| SW | - | SDカード検出スイッチ．ここでは未使用． |

+ 通信はSPI
+ 電圧は5V
	- 素子の内部で3.3Vにレギュレート & レベル変換してくれるので，5V系マイコンで利用するにはとても便利
+ ジャンパJ1をショートさせることに注意

## ソースコードへのリンク
[GitHub](https://github.com/meltingrabbit/CanSatForHighSchoolStudents/tree/master/Arduino/Test_SD)

