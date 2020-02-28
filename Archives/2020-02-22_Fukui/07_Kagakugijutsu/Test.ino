#include "./IMU.h"
#include "./SD.h"
#include "./Servo.h"
#include "./Camera.h"

void setup()
{
  // Wire(Arduino-I2C)の初期化
  Wire.begin();
  // デバック用シリアル通信は9600bps
  Serial.begin(9600);

  //SD_Init();    // これは絶対最初に初期化！
  //CAM_Init();   // SDの後！
  IMU_Init();
  //SRV_Init();


  Serial.println(F("Init done"));
  delay(300);
}

void loop()
{

  while (1) {
    IMU_UpdateAll();
    int mag_x=IMU_GetMagX();
    int mag_y=IMU_GetMagY();

    Serial.println(mag_x);
    Serial.println(mag_y);

    float magnet_radian=atan2((float)mag_y,(float)mag_x);
    float magnet_degree=magnet_radian*180.0/PI;
    Serial.print(F("Direction: "));
    Serial.print(magnet_degree);
    Serial.println(F("[deg]"));

    if (magnet_degree<30&&magnet_degree>-30){
      Serial.println("kita");
      break;
    }

    delay(1000);
  }
  CAM_TakePic();    // 写真を撮る
  delay(1000);

  Serial.println(F("END"));
  while (1) {
  }
}
