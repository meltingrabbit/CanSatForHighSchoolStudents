#include "./Microphone.h"

void setup() {
  // デバック用シリアル通信は9600bps
  Serial.begin(9600);

  MIC_Init(); // マイクロフォンの値の表示を初期化

  Serial.println(F("Init done"));
  delay(300);
}

void loop() {
  MIC_Print(); // マイクロフォンの値を表示

  delay(5); // 50 ms 待つ
}
