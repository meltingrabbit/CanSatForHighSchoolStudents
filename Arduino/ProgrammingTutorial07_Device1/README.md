# プログラミング講習 07. 機器の利用 その１
## 概要
+ マイコンに接続した機器を使ってみよう
	- 機器のテストコードで使った[高度計（気圧計）・温湿度計の回路とプログラム](../Test_Barometer_Thermohygrometer)を使う
	- ここでは，気圧計をつかって，今の高度を求めてみよう


## ソースコード
```cpp
// 高度計（気圧計）・温湿度計のライブラリ（便利なコードまとめ）を使うよ！ と宣言
#include "./BarometerThermohygrometer.h"
// すると，
// BarometerThrmohygrometer.h に宣言されている
//  void BTH_Init();
//  void BTH_Update();
//  void BTH_Print();
//  float BTH_GetPressure();
//  float BTH_GetHumidity();
//  float BTH_GetTemperature();
// という関数が使えるようになる
// 関数の中身は BarometerThrmohygrometer.ino にかかれている


void setup()
{
  // Wire(Arduino-I2C)の初期化．高度計（気圧計）・温湿度計との通信を開始
  Wire.begin();
  // デバック用シリアル通信は9600bps
  Serial.begin(9600);

  // 高度計（気圧計）・温湿度計を初期化
  BTH_Init();

  Serial.println(F("Init done"));
  delay(300);
}

void loop()
{
  // 高度計（気圧計）・温湿度計の値を更新
  BTH_Update();
  // // 高度計（気圧計）・温湿度計の値を表示
  // BTH_Print();
  float pressure = BTH_GetPressure();

  // 気圧から高度に変換
  // まあ，ざっくり 10m上昇すると1hPa下がるとしようか．
  float pressure_at_sea_level = 1013.250;
  float height = (pressure_at_sea_level - pressure) * 10;

  Serial.print(F("Height = "));
  Serial.print(height);
  Serial.println(F(" [m]"));
  delay(1000);
}
```

+ 缶サットを上げ下げしたら，高度が変わることを確認しよう
+ 他の機器でも同じようなプログラムを作ってみよう


## ピンアサイン（ピン配置）
+ `PIN_ASSIGN.h` というファイルで，マイコンのどのピンにどこを接続するかを定義している．
+ たとえば，I2Cで使うピンである， SDA, SCL を定義してもよいが，ここではデフォルト値（初期値）を使っているため，特に記述してない（コメントアウトしている）．
```cpp
// #define SDA A4
// #define SCL A5
```
+ 適切にピンアサインを変更することで，複数の機器を同時に接続したり，回路の設計を簡単にすることができる．


## 備考
+ ここでは，講義の時間の都合上，用意された関数群を用いた．
+ 本来であれば，センサに応じたサンプルコードをインターネットなどからダウンロードすると良い．
	- 「センサ名 Arduino サンプルコード」などでGoogle検索をかけるとよい．


## リファレンス
詳細な説明はリファレンス（説明書）を参考にしよう！  
[http://www.musashinodenpa.com/arduino/ref/index.php](http://www.musashinodenpa.com/arduino/ref/index.php)


## ソースコードへのリンク
[GitHub](https://github.com/meltingrabbit/CanSatForHighSchoolStudents/tree/master/Arduino/ProgrammingTutorial07_Device1)

