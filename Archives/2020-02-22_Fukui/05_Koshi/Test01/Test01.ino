#include "./IMU.h"
#include "./SD.h"
#include "./Camera.h"

void setup()
{
  // Wire(Arduino-I2C)の初期化
  Wire.begin();
  // デバック用シリアル通信は9600bps
  Serial.begin(9600);

  SD_Init();    // これは絶対最初に初期化！
  CAM_Init();   // SDの後！
  IMU_Init();

  Serial.println(F("Init done"));
  delay(300);
}

void loop()
{
  IMU_UpdateAll();
  IMU_PrintAcc();
  IMU_PrintGyr();
  IMU_PrintMag();

  float zAcc = IMU_GetAccZ();

  if (zAcc<-7) {
    CAM_TakePic();
  }
  //SD_Write(String(loop_count));

  delay(1000);
}
