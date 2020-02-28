#include "./SD.h"
#include "./Servo.h"
#include "./Light.h"
#include "./Light2.h"
#include "./Light3.h"
#include "./Light4.h"
//#include "./Camera.h"

void setup()
{
  // Wire(Arduino-I2C)の初期化
  Wire.begin();
  // デバック用シリアル通信は9600bps
  Serial.begin(9600);

  //SD_Init();    // これは絶対最初に初期化！
  //CAM_Init();   // SDの後！
  SRV_Init();
  LIT_Init();
  LIT4_Init();
  LIT4_Init();
  LIT4_Init();


  Serial.println(F("Init done"));
  delay(300);
}

void loop()
{
  //LIT_Print();
  //LIT2_Print();
  //LIT3_Print();
  //LIT4_Print();

  float a = LIT_Get();
  float b = LIT2_Get();
  float c = LIT3_Get();
  float d = LIT4_Get();
  Serial.print("LIT:");
  Serial.println(a);
  Serial.print("LIT2:");
  Serial.println(b);
  Serial.print("LIT3:");
  Serial.println(c);
  Serial.print("LIT4:");
  Serial.println(d);
  float max = a;
  int num = 1;
  if (max<b){
  max = b;
  num = 2;
  }
  if (max<c){
  max = c;
  num = 3;
  }
  if (max<d){
  max = d;
  num = 4;
  }

  Serial.print("num:");
  Serial.println(num);

  if (num == 1){
  SRV_SetPosition(0);
  }
  else if (num == 2){
  SRV_SetPosition(60);
  }
  else if (num == 3){
  SRV_SetPosition(120);
  }
  else if (num == 4){
  SRV_SetPosition(180);
  }
  SRV_Run();

  delay(1000);
}

