# プログラミング講習 03. 演算子
## 概要
+ 四則演算 (+-*/)，剰余 (%), その他
	- 他にも，sqrtやsin, maxなども
+ 型に注意！
	- 整数同士の演算結果は整数
	- 小数と整数の演算結果は小数



+ 変数とは，計算結果を入れておく箱
	- 人間は計算用紙に書いていくが，コンピュータは変数に入れていく
	- “型” という概念があり，箱の種類によって入れられるものが違う


## ソースコード
```cpp
void setup()
{
  Serial.begin(9600);
  Serial.print("5+2: ");
  Serial.println(5+2);

  Serial.print("5-2: ");
  Serial.println(5-2);

  Serial.print("5*2: ");
  Serial.println(5*2);

  Serial.print("5/2: ");
  Serial.println(5/2);

  Serial.print("5/2.0: ");
  Serial.println(5/2.0);

  Serial.print("(float)5/2: ");
  Serial.println((float)5/2);

  Serial.print("(int)(5/2.0): ");
  Serial.println((int)(5/2.0));

  Serial.print("5%2: ");
  Serial.println(5%2);

  int a = 5;
  int b = 2;
  Serial.print("a/b: ");
  Serial.println(a/b);

  int c = a / b;
  Serial.print("c: ");
  Serial.println(c);

  float d = 5;
  float e = 2;
  Serial.print("d/e: ");
  Serial.println(d/e);

  float f = e / d;
  Serial.print("f: ");
  Serial.println(f);
}

void loop()
{
}
```

+ 値を自分で変えて試してみよう
+ 型の違いに意識してみよう


## リファレンス
詳細な説明はリファレンス（説明書）を参考にしよう！  
http://www.musashinodenpa.com/arduino/ref/index.php