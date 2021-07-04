#include <SD.h>
#include <SPI.h>
#include "./GPS.h"
#include "./IMU.h"
#include "./Camera2.h"
#include "./SD.h"
#include "./Temp.h"

void setup()
{
  Wire.begin();
  // デバック用シリアル通信は9600bps
  Serial.begin(9600);
  SPI.begin();
  

  SD_Init();
  CAM2_Init();
  BTH_Init();
  GPS_Init();   // GPSの初期化
  IMU_Init();
  Serial.println(F("Init done"));
  delay(300);
}

float decidedirection(){
  float x = IMU_GetMagX();
  float y = IMU_GetMagY();
  float a = atan(y/x);
  return a;
}


void loop()
{
  BTH_Update();
  float pressure = BTH_GetPressure();
  float pressure_at_sea_level = 1013.250;
  float height = (pressure_at_sea_level - pressure) * 10;
  Serial.println(height);
  GPS_Update();   // GPSの値をアップデート
  GPS_Print();    // GPSの値を表示
  IMU_UpdateAll();
  IMU_PrintAcc();
  IMU_PrintGyr();
  IMU_PrintMag();
  CAM2_TakePic();

  File datafile1  = SD.open("degree.txt",FILE_WRITE);
  File dataFile = SD.open("kiroku.txt",FILE_WRITE);
  if (dataFile){
    int value = height;
    dataFile.println(value);
    dataFile.println("緯度");
    dataFile.println(GPS_GetLat());
    dataFile.println("経度");
    dataFile.println(GPS_GetLng());
    dataFile.println("高さ");
    dataFile.println(GPS_GetHeight());
    dataFile.close();
  }
  if (datafile1){  
    float value2 = decidedirection();
    datafile1.println("degree:");
    datafile1.println(value2);
    datafile1.close();
    Serial.println(value2);
  }
  delay(1000);    // 10m 待つ
}
