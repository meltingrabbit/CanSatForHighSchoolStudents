# プログラミング講習 01. Hello World
## 概要
+ “Hello World” とは，プログラミングで最初に行う例題
	- 手始めに文字だけ表示し，Arduinoのプログラミングの大枠を知ろう！


## ソースコード
```cpp
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
  // Serial.println("Comment");     // コメント行（実行されない）
  delay(1000);
}
```

+ 文字を変えて試してみよう


## 備考
+ `Serial.print`, `Serial.println` での文字列を `F()` で囲う事により，メモリ使用量を抑えることができる．
	- 代わりにROMを消費するが，メモリ (RAM) の少ないArduinoでは有効な手段である．
+ マイコンのリセットボタンを押すと，プログラムはリセットされ，再びソースコードの最初から実行される．


## リファレンス
詳細な説明はリファレンス（説明書）を参考にしよう！  
[http://www.musashinodenpa.com/arduino/ref/index.php](http://www.musashinodenpa.com/arduino/ref/index.php)


## ソースコードへのリンク
[GitHub](https://github.com/meltingrabbit/CanSatForHighSchoolStudents/tree/master/Arduino/ProgrammingTutorial01_HelloWorld)
