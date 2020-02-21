# プログラミング講習 06. 関数
## 概要
+ 同じ処理をたくさん使う時は，“関数” というものにまとめることができる
	- こうすることで，プログラムの再利用性が高まる
	- プログラム全体が見やすくなる


## ソースコード
```cpp
// はじめに，作る関数を宣言する
// 返り値の型（何もない時はvoid），関数名，引数の型と変数名
void print_number(String str, int i);
int  my_max(int a, int b);

void setup()
{
  Serial.begin(9600);

  int a = 10;
  int b = 20;

  print_number("a", a);
  print_number("b", b);
  int c = my_max(a,b);
  print_number("c", c);
  print_number("my_max(a,b)", my_max(a,b));   // 関数は入れ子にできるよ
}

void loop()
{
}


// print_number という関数は，
//   String（文字）とint（整数）の２つの引数をもらう
//   返り値はの型は void（何も返さない）
//   もらった値を表示する
void print_number(String str, int i) {
  Serial.print(str);
  Serial.print(": ");
  Serial.println(i);
}

// my_max という関数は，
//   ２つのint（整数）の引数をもらう
//   返り値はの型はint
//   大きい数字を返す
int  my_max(int a, int b) {
  int ret = 0;
  if (a > b) {
    ret = a;
  } else {
    ret = b;
  }
  return ret;
}
```

+ 自分で考えた関数を作って動かしてみよう！


## リファレンス
詳細な説明はリファレンス（説明書）を参考にしよう！  
http://www.musashinodenpa.com/arduino/ref/index.php