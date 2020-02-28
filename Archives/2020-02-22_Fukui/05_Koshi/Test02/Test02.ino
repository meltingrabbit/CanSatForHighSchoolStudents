#include "./SD.h"
#include "./Light.h"
#include "./Camera.h"

uint16_t loop_count = 0;

void setup()
{
  // Wire(Arduino-I2C)の初期化
  Wire.begin();
  // デバック用シリアル通信は9600bps
  Serial.begin(9600);

  SD_Init();    // これは絶対最初に初期化！
  CAM_Init();   // SDの後！
  LIT_Init();


  Serial.println(F("Init done"));
  delay(10000);
}

void loop()
{
  uint32_t light = 0;

  {
    light = light + LIT_Get();
  }

  LIT_Print();
  if (light <100) {
    Serial.println(F("Light is low"));
    CAM_TakePic();
  } else {
      Serial.println(F("Light is high"));
  }
  SD_Write(String(loop_count));
}


