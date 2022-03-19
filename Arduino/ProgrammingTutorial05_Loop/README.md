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
  // for (初期化; 継続条件; 変化式)
  // つまり，
  // 最初に実行される; ループを続けるかの条件; ループの最後に毎回実行される文
  // ↓は，変数 "num" に，最初に 0 を代入し，ループごとに 1 を加え， 10 以下の間 {} の中を繰り返す．
  for (int num = 0; num <= 10; num = num + 1) {
    Serial.print("Loop1: ");
    Serial.println(num);
    delay(100);                   // 100 ms 待つ
  }

  Serial.println("#### FOR BREAK ####");
  for (int num = 0; num <= 10; num = num + 1) {

    if (num == 5) {               // もし， "num" が 5 なら
      break;                      // ループから抜ける
    }

    Serial.print("Loop2: ");
    Serial.println(num);
    delay(100);
  }


  Serial.println("#### WHILE ####");
  int count = 0;
  // while (継続条件)
  // ↓は，変数 "count" が 10 未満の間 {} の中を繰り返す．
  while (count < 10) {
    Serial.print("Loop3: ");
    Serial.println(count);
    delay(100);

    count = count + 1;          // count に 1 を足して， count に代入する
  }

  Serial.println("#### WHILE BREAK ####");
  count = 0;
  while (1) {                   // 無限ループ
    Serial.print("Loop4: ");
    Serial.println(count);
    delay(100);

    count = count + 1;

    if (count >= 10) {          // もし， "count" が 10 以上なら
      break;                    // ループから抜ける
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
[http://www.musashinodenpa.com/arduino/ref/index.php](http://www.musashinodenpa.com/arduino/ref/index.php)


## ソースコードへのリンク
[GitHub](https://github.com/meltingrabbit/CanSatForHighSchoolStudents/tree/master/Arduino/ProgrammingTutorial05_Loop)

