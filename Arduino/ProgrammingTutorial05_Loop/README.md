# プログラミング講習 05. ループ
## 概要
+ 繰り返しの処理や，ちょっとずつ処理を変化させたい時につかう．
	- `for` と `while` がある．
+ 注意
	- 意図しない無限ループに陥らないように注意すること！


## ソースコード
```cpp
void setup()
{
  Serial.begin(9600);

  Serial.println("#### FOR ####");
  // 初期化; 継続条件; 変化式
  // ↓
  // 最初に実行される; ループを続けるかの条件; ループの最後に毎回実行される文
  for (int num = 0; num <= 10; num = num + 1) {
    Serial.print("Loop1: ");
    Serial.println(num);
    delay(100);
  }

  Serial.println("#### FOR BREAK ####");
  for (int num = 0; num <= 10; num = num + 1) {

    if (num == 5) {
      break;                      // ループから抜ける
    }

    Serial.print("Loop2: ");
    Serial.println(num);
    delay(100);
  }


  Serial.println("#### WHILE ####");
  int count = 0;
  // 継続条件
  while (count < 10) {
    Serial.print("Loop3: ");
    Serial.println(count);
    delay(100);

    count = count + 1;
  }

  Serial.println("#### WHILE BREAK ####");
  count = 0;
  while (1) {
    Serial.print("Loop4: ");
    Serial.println(count);
    delay(100);

    count = count + 1;

    if (count >= 10) {
      break;                      // ループから抜ける
    }
  }
}

void loop()
{
}
```

+ 色んな所を変えてみよう！
	- 自分の想定通り動くかな？


## リファレンス
詳細な説明はリファレンス（説明書）を参考にしよう！  
http://www.musashinodenpa.com/arduino/ref/index.php