#include "./IMU.h"
#include "./GPS.h"
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
  GPS_Init();

  Serial.println(F("Init done"));
  delay(300);
}

void loop()
{
  IMU_UpdateAll();
  IMU_PrintAcc();
  IMU_PrintGyr();
  IMU_PrintMag();
  GPS_Update();
  float lat = GPS_GetLat();
  float lng = GPS_GetLng(); 
  GPS_Print();
  if ((lat > 36.1242) && (lat < 36.1244)) {
    if ((lng > 136.220310) && (lng < 136.220330)) {
      CAM_TakePic();
    }
  }
}
