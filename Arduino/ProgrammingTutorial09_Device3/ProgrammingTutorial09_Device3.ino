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
// 関数の説明は IMU.h に書かれている
// 関数の中身は IMU.ino に書かれている


void setup()
{
  // Wire(Arduino-I2C) の初期化．気圧計との通信を開始
  Wire.begin();
  // デバック用シリアル通信は 9600bps
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
  // なお，本来は地磁気の xy 平面が描く楕円を原点を中心とした真円になおすキャリブレーションが必要
  float magnet_radian = atan2((float)mag_y, (float)mag_x);
  float magnet_degree = magnet_radian * 180.0 / PI;

  Serial.print(F("Direction: "));
  Serial.print(magnet_degree);
  Serial.println(F(" [deg]"));

  delay(250);
}
