# プログラミング講習 04. 条件分岐
## 概要
+ 条件によってプログラムを分岐することができる
	- `if`, `else if`, `else` を使って， `{}` で囲う．
+ 比較演算子
	- `==` : 等しい
	- `!=` : 等しくない
	- `<`, `>` : より大きい，より小さい
	- `<=`, `>=` : 以上，以下
+ 論理演算子
	- `&&` : かつ
	- `||` : または
+ 注意
	- プログラムで，コードのまとまりは `{}` を，式のまとまりは `()` を使う．


## ソースコード
```cpp
void setup()
{
  Serial.begin(9600);

  int a = 10;                         // 整数型 (int) の変数 a に整数 10 を代入

  Serial.println("a == 10 ? :");
  if (a == 10) {                      // a は 10 ？
    Serial.println("  -> a == 10");
  } else {                            // それ以外
    Serial.println("  -> otherwise");
  }

  Serial.println("a != 10 ? :");
  if (a != 10) {                      // a は 10 ではない？
    Serial.println("  -> a != 10");
  } else {                            // それ以外
    Serial.println("  -> otherwise");
  }

  Serial.println("a > 10 or a >= 10 ? :");
  if (a > 10) {                       // a は 10 より大きい？
    Serial.println("  -> a > 10");
  } else if (a >= 10) {               // a は 10 より大きくはないけど， 10 以上？
    Serial.println("  -> a >= 10");
  } else {                            // それ以外
    Serial.println("  -> otherwise");
  }


  Serial.println("(a > 5) && (a < 20) ? :");
  if ((a > 5) && (a < 20)) {          // a は 5 より大きく，かつ， 20 より小さい？
    Serial.println("  -> (a > 5) && (a < 20)");
  } else {                            // それ以外
    Serial.println("  -> otherwise");
  }

  Serial.println("(a > 5) || (a > 20) ? :");
  if ((a > 5) || (a > 20)) {          // a は 5 より大きい，または， 20 より大きい？
    Serial.println("  -> (a > 5) || (a > 20)");
  } else {                            // それ以外
    Serial.println("  -> otherwise");
  }
}

void loop()
{
}
```

+ `a` の値を変えて，想像通りに動くか試してみよう
+ 条件式も変えてみよう


## リファレンス
詳細な説明はリファレンス（説明書）を参考にしよう！  
[http://www.musashinodenpa.com/arduino/ref/index.php](http://www.musashinodenpa.com/arduino/ref/index.php)


## ソースコードへのリンク
[GitHub](https://github.com/meltingrabbit/CanSatForHighSchoolStudents/tree/master/Arduino/ProgrammingTutorial04_IfElse)
