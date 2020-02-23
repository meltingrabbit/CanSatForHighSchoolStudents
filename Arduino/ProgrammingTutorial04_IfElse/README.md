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

  int a = 10;                     // aに整数10を代入

  if (a == 10) {                  // aは10？
    Serial.println("a == 10");
  } else {                        // それ以外
    Serial.println("otherwise");
  }

  if (a != 10) {                  // aは10ではない？
    Serial.println("a != 10");
  } else {                        // それ以外
    Serial.println("otherwise");
  }

  if (a > 10) {                   // aは10より大きい？
    Serial.println("a > 10");
  } else if (a >= 10) {           // aは10より大きくはないけど，10以上？
    Serial.println("a >= 10");
  } else {                        // それ以外
    Serial.println("otherwise");
  }


  if ((a > 5) && (a < 20)) {      // aは5より大きく，かつ，20より小さい？
    Serial.println("(a > 5) && (a < 20)");
  } else {                        // それ以外
    Serial.println("otherwise");
  }

  if ((a > 5) || (a > 20)) {      // aは5より大きい，または，20より大きい？
    Serial.println("(a > 5) || (a > 20)");
  } else {                        // それ以外
    Serial.println("otherwise");
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
http://www.musashinodenpa.com/arduino/ref/index.php