// サーボモータのライブラリ（便利なコードまとめ）を使うよ！ と宣言
#include "./Servo.h"
// すると，
// Servo.h に宣言されている
//   void SRV_Init();
//   void SRV_SetPosition(uint8_t pos);
//   uint8_t SRV_GetPosition();
//   void SRV_Run();
//   void SRV_Detach();
//   void SRV_Attach();
// という関数が使えるようになる
// 関数の中身は Servo.c にかかれている

// 光センサのライブラリ（便利なコードまとめ）を使うよ！ と宣言
#include "./Light.h"
// すると，
// Light.h に宣言されている
//   void LIT_Init();
//   int  LIT_Get();
//   void LIT_Print();
// という関数が使えるようになる
// 関数の中身は Light.c にかかれている


void setup()
{
  // デバック用シリアル通信は9600bps
  Serial.begin(9600);

  // サーボモータを初期化
  SRV_Init();
  // 光センサを初期化
  LIT_Init();

  Serial.println(F("Init done"));
  delay(300);
}

void loop()
{

  while (1) {
    Serial.print(F("Light: "));
    Serial.println(LIT_Get());
    if ( LIT_Get() > 300) {
      break;
    }
    delay(100);
  }

  delay(1000);

  SRV_SetPosition(180);
  SRV_Run();

  delay(1500);

  SRV_SetPosition(0);
  SRV_Run();



  Serial.println(F("END"));
  while (1) {
  }
}
