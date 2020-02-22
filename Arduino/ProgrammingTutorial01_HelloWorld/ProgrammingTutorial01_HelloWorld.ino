void setup()                        // 最初に実行される
{
  Serial.begin(9600);               // 通信速度 9600 bps で通信開始
  Serial.println("Hello World!!");  // 文字を出力
  delay(1000);                      // 1000 ms 待つ
  Serial.println("Setup!");
  delay(1000);
}

void loop()                         // Setup後，繰り返し実行される
{
  Serial.println(F("Loop!"));       // F() で囲むと（Fマクロ），使用メモリを抑えることができる（ROMを消費する）
  // Serial.println(“Comment”);   // コメント行（実行されない）
  delay(1000);
}

