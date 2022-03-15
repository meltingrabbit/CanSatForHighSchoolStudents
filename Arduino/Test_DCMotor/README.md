# DCモータの単体テストコード
## 概要
DCモータの単体テストコード  

## 機器詳細
ＤＣモーター　ＦＡ－１３０ＲＡ－２２７０Ｌ  
https://akizukidenshi.com/catalog/g/gP-09169/

ＤＲＶ８８３５使用ステッピング＆ＤＣモータドライバモジュール  
https://akizukidenshi.com/catalog/g/gK-09848/


## 回路図
![](../../Schematic/PNG/DCMotor.png)

| 素子 Pin | Arduino Pin | 備考 |
| ---- | ---- | ---- |
| VCC | 5V | モータドライバ用の 5V 電源 |
| MODE | GND | モータドライバ用のモード設定．DCモータを使い場合はGND（ステッピングモーターを使う場合は VCC）． |
| AIN1 | D5 | １つ目のモータの動作（正転・逆転・空転・ブレーキ）を制御 |
| AIN2 | D6 | １つ目のモータの動作（正転・逆転・空転・ブレーキ）を制御 |
| BIN1 | - | ２つ目のモータの動作（正転・逆転・空転・ブレーキ）を制御 |
| BIN2 | - | ２つ目のモータの動作（正転・逆転・空転・ブレーキ）を制御 |
| VM | モータ用電池の＋極 | モーター電源 |
| AOUT1 | DC モータ | １つ目のモータへの出力 |
| AOUT2 | DC モータ | １つ目のモータへの出力 |
| BOUT1 | - | ２つ目のモータへの出力 |
| BOUT2 | - | ２つ目のモータへの出力 |
| GND | GND | GND |

+ DCモータの外部電源電圧は3V
+ DCモータには大電流が流れるため，マイコンとは別の電源を用意する．
	- 大電流のノイズがマイコンに悪影響を与えるのを防ぐために，コンデンサを入れている．

## ソースコードへのリンク
[GitHub](https://github.com/meltingrabbit/CanSatForHighSchoolStudents/tree/master/Arduino/Test_DCMotor)
