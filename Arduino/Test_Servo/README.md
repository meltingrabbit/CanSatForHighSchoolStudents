# サーボモータの単体テストコード
## 概要
サーボモータの単体テストコード


## 機器詳細
マイクロサーボ　ＳＧ９２Ｒ  
http://akizukidenshi.com/catalog/g/gM-08914/

## ライブラリ
+ Arduinoの標準ライブラリであるServoライブラリを使用
+ Servoライブラリのバージョンが古いとArduino nano everyに対応しておらず，エラーが出る

![](./img/Servo_lib_error.png)

+ エラーが出た場合は，スケッチ＞ライブラリをインクルード＞ライブラリを管理 を選択
+ タイプから「アップデート可能」を選択し，Servoがあれば「更新」を選択

![](./img/Servo_lib_update1.png)
![](./img/Servo_lib_update2.png)


## 回路図
+ 信号電圧は5V

![](../../Schematic/PNG/Servo.png)

| 素子 Pin | Arduino Pin | 備考 |
| ---- | ---- | ---- |
| 茶（GND） | GND | GND |
| 赤（電源 [+]） | 5V | 5V 電源 |
| 橙（制御信号 [JRタイプ]） | D4 | 指定した回転角にモーターを制御するための信号 |


## ソースコードへのリンク
[GitHub](https://github.com/meltingrabbit/CanSatForHighSchoolStudents/tree/master/Arduino/Test_Servo)

