# プログラミング講習 08. 機器の利用 その２
## 概要
+ マイコンに接続した機器を使ってみよう
	- 機器のテストコードで使った[９軸センサの回路とプログラム](../Test_IMU)を使う
	- ここでは，９軸センサをつかって，コンパス（方位磁針）を作ってみよう


## ソースコード
```cpp
// ９軸センサのライブラリ（便利なコードまとめ）を使うよ！ と宣言
#include "./IMU.h"
// すると，
// IMU.h に宣言されている
//   void IMU_Init();
//   void IMU_UpdateAll();
//   void IMU_UpdateAcc();
//   void IMU_UpdateGyr();
//   void IMU_UpdateMag();
//   void IMU_PrintAcc();
//   void IMU_PrintGyr();
//   void IMU_PrintMag();
//   float IMU_GetAccX();
//   float IMU_GetAccY();
//   float IMU_GetAccZ();
//   float IMU_GetGyrX();
//   float IMU_GetGyrY();
//   float IMU_GetGyrZ();
//   int16_t IMU_GetMagX();
//   int16_t IMU_GetMagY();
//   int16_t IMU_GetMagZ();
// という関数が使えるようになる
// 関数の中身は IMU.c にかかれている


void setup()
{
  // Wire(Arduino-I2C)の初期化．気圧計との通信を開始
  Wire.begin();
  // デバック用シリアル通信は9600bps
  Serial.begin(9600);

  // 9軸センサを初期化
  IMU_Init();

  Serial.println(F("Init done"));
  delay(300);
}

void loop()
{
  IMU_UpdateAll();    // 9軸センサの値をアップデート
  // IMU_PrintAcc();     // 取得した加速度を表示
  // IMU_PrintGyr();     // 取得した角加速度を表示
  // IMU_PrintMag();     // 取得した磁気を表示

  // x, y の地磁気の値を取得
  int mag_x = IMU_GetMagX();
  int mag_y = IMU_GetMagY();

  // x, y の地磁気から，北からの方位を求める．
  // なお，本来は地磁気のxy平面が描く楕円を原点を中心とした真円になおすキャリブレーションが必要
  float magnet_radian = atan2((float)mag_y, (float)mag_x);
  float magnet_degree = magnet_radian * 180.0 / PI;

  Serial.print(F("Direction: "));
  Serial.print(magnet_degree);
  Serial.println(F(" [deg]"));

  delay(250);
}

```

+ 缶サットを回転させ，方位が変わることを確認しよう
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
http://www.musashinodenpa.com/arduino/ref/index.php