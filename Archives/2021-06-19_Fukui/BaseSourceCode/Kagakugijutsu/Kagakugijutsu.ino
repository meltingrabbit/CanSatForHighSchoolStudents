#include "./GPS.h"
#include "./DCMotor.h"
#include "./DCMotor2.h"
#include "./SD.h"
#include "./IMU.h"

void setup()
{
  // デバック用シリアル通信は9600bps
  Serial.begin(9600);

  GPS_Init();		// GPSの初期化
  DCM_Init();     // DCモータを初期化
  DCM2_Init();    // DCモータ2を初期化
  SD_Init();
  IMU_Init();     // 9軸センサを初期化

  Serial.println(F("Init done"));
  delay(300);
}

void loop()
{
  GPS_Update();		// GPSの値をアップデート
  GPS_Print();		// GPSの値を表示

  delay(25);		// 25 ms 待つ

  IMU_UpdateAll();    // 9軸センサの値をアップデート
  IMU_PrintAcc();     // 取得した加速度を表示
  IMU_PrintGyr();     // 取得した角加速度を表示
  IMU_PrintMag();     // 取得した磁気を表示

  Serial.println(F("DCM1 Forward"));
  DCM_FORWARD();      // 正転
  delay(5000);      // 5000 ms 待つ
  Serial.println(F("DCM1 Coast"));
  DCM_COAST();      // 空転
  delay(5000);      // 5000 ms 待つ
  Serial.println(F("DCM1 Reverse"));
  DCM_REVERSE();      // 逆転
  delay(5000);      // 5000 ms 待つ
  Serial.println(F("DCM1 Brake"));
  DCM_BRAKE();      // ブレーキ
  delay(5000);      // 5000 ms 待つ

  Serial.println(F("DCM2 Forward"));
  DCM2_FORWARD();     // 正転
  delay(5000);      // 5000 ms 待つ
  Serial.println(F("DCM2 Coast"));
  DCM2_COAST();     // 空転
  delay(5000);      // 5000 ms 待つ
  Serial.println(F("DCM2 Reverse"));
  DCM2_REVERSE();     // 逆転
  delay(5000);      // 5000 ms 待つ
  Serial.println(F("DCM2 Brake"));
  DCM2_BRAKE();     // ブレーキ
  delay(5000);      // 5000 ms 待つ
}
