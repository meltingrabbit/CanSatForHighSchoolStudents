// サーボモータのライブラリ（便利なコードまとめ）を使うよ！ と宣言
#include "./Servo.h"
// すると，
// Servo.h に宣言されている
//   void SRV_Init();
//   void SRV_SetPosition(uint8_t angle);
//   uint8_t SRV_GetPosition();
//   void SRV_Run();
//   void SRV_Detach();
//   void SRV_Attach();
// という関数が使えるようになる
// 関数の説明は Servo.h に書かれている
// 関数の中身は Servo.ino に書かれている

uint16_t loop_count = 0;      // プログラムのどこからでも使える変数 loop_count を準備しておく

void setup()
{
  // デバック用シリアル通信は 9600bps
  Serial.begin(9600);

  SRV_Init();		// サーボモータを初期化

  Serial.println(F("Init done"));
  delay(300);
}

void loop()
{
  // 今何周目のループか表示
  Serial.println(loop_count);

  // ループカウンタが10の倍数のときに実行
  if (loop_count % 10 == 0) {
    Serial.println(F("Move Up!"));
    // 0 ~ 180 度に， 30 度ずつ， 0.5秒ごとに回転させる
    for(uint8_t angle = 0; angle <= 180; angle = angle + 30) {
      Serial.print(F("angle:"));
      Serial.println(angle);
      SRV_SetPosition(angle);
      SRV_Run();
      delay(500);       // 500 ms （0.5秒）待つ
    }
  }

  // ループカウンタを10で割った剰余が5のときに実行
  if (loop_count % 10 == 5) {
    Serial.println(F("Move Down!"));
    // 180 - 0 度に， 1 度ずつ， 0.02秒ごとに回転させる
    // 0.02秒と人間にとっては短い時間なので，なめらかにゆっくり回転するように見える
    for(uint8_t angle = 180; angle > 0; angle--) {
      Serial.print(F("angle:"));
      Serial.println(angle);
      SRV_SetPosition(angle);
      SRV_Run();
      delay(20);        // 20 ms （0.02秒）待つ
    }
  }

  // ループカウントを 1 増やす
  loop_count++;
  delay(1000);
}
