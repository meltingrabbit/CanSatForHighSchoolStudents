# プログラミング講習 03. 演算子
## 概要
+ 四則演算 ( `+-*/` )，剰余 ( `%` ), その他
	- 他にも， `sqrt` や `sin` , `max` なども
+ 型に注意！
	- 整数同士の演算結果は整数
	- 小数と整数の演算結果は小数
+ キャスト
  - `(型名)数字 or 変数` で，方を変換できる
  - 例: `(float)2` 整数 "2" を小数 "2.0" に変換
  - 例: `(int)2.5` 小数 "2.5" を整数 "2" に変換


## ソースコード
```cpp
void setup()
{
  Serial.begin(9600);

  Serial.print("5+2: ");
  Serial.println(5+2);            // 足し算

  Serial.print("5-2: ");
  Serial.println(5-2);            // 引き算

  Serial.print("5*2: ");
  Serial.println(5*2);            // 掛け算

  Serial.print("5/2: ");
  Serial.println(5/2);            // 整数の割り算（商）

  Serial.print("5/2.0: ");
  Serial.println(5/2.0);          // 小数の割り算

  Serial.print("(float)5/2: ");
  Serial.println((float)5/2);     // 整数 "5" を小数に変換してから，小数の割り算

  Serial.print("(int)(5/2.0): ");
  Serial.println((int)(5/2.0));   // 小数の割り算の結果を整数に変換

  Serial.print("5%2: ");
  Serial.println(5%2);            // 整数の割り算（剰余）

  int a = 5;
  int b = 2;
  Serial.print("a/b: ");
  Serial.println(a/b);            // 整数の割り算（変数同士）

  int c = a / b;                  // 整数の割り算結果を変数 "c" に代入
  Serial.print("c: ");
  Serial.println(c);

  float d = 5;
  float e = 2;
  Serial.print("d/e: ");
  Serial.println(d/e);            // 小数の割り算（変数同士）

  float f = e / d;                // 小数の割り算結果を変数 "f" に代入
  Serial.print("f: ");
  Serial.println(f);

  Serial.print("sin(3.14/2): ");
  Serial.println(sin(3.14/2));    // 三角関数（正弦）

  Serial.print("sqrt(2): ");
  Serial.println(sqrt(2));        // 平方根

  Serial.print("max(2,3): ");
  Serial.println(max(2,3));       // 最大値
}

void loop()
{
}
```

+ 値を自分で変えて試してみよう
+ 型の違いに意識してみよう


## リファレンス
詳細な説明はリファレンス（説明書）を参考にしよう！  
[http://www.musashinodenpa.com/arduino/ref/index.php](http://www.musashinodenpa.com/arduino/ref/index.php)


## ソースコードへのリンク
[GitHub](https://github.com/meltingrabbit/CanSatForHighSchoolStudents/tree/master/Arduino/ProgrammingTutorial03_Operator)

