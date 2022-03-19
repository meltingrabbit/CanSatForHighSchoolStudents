void setup()                        // 最初に実行される
{
  Serial.begin(9600);               // 通信速度 9600 bps でPCとシリアル通信開始
  Serial.println("Hello World!!");  // 文字列 "Hello World!!" を出力
  delay(1000);                      // 1000 ms 待つ
  Serial.println("Setup!");         // 文字列 "Setup!" を出力
  delay(1000);                      // 1000 ms 待つ
}

void loop()                         // Setup後，繰り返し実行される
{
  Serial.println(F("Loop!"));       // 文字列 "Loop!" を出力
                                    // F() で囲むと（Fマクロ），使用メモリを抑えることができる（ROMを消費する）
  // Serial.println("Comment");     // "//" で始まる行はコメント行（実行されない）
  delay(1000);                      // 1000 ms 待つ
}
