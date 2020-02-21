# プログラミング講習 01. Hello World
## 概要
+ “Hello World” とは，プログラミングで最初に行う例題
	- 手始めに文字だけ表示し，Arduinoのプログラミングの大枠を知ろう！


## ソースコード
```cpp
void setup()                              // 最初に実行される
{
  Serial.begin(9600);                     // 通信速度 9600 bps で通信開始
  Serial.println("Hello World!!");        // 文字を出力
  delay(1000);                            // 1000 ms 待つ
  Serial.println("Setup!");
  delay(1000);
}

void loop()                               // Setup後，繰り返し実行される
{
  Serial.println("Loop!");
  // Serial.println("Comment");           // コメント行（実行されない）
  delay(1000);
}
```


## リファレンス
詳細な説明はリファレンス（説明書）を参考にしよう！  
http://www.musashinodenpa.com/arduino/ref/index.php