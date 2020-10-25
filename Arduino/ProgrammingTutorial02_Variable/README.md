# プログラミング講習 02. 変数
## 概要
+ 変数とは，計算結果を入れておく箱
	- 人間は計算用紙に書いていくが，コンピュータは変数に入れていく
	- “型” という概念があり，箱の種類によって入れられるものが違う



## ソースコード
```cpp
void setup()
{
  Serial.begin(9600);
  String str = "String";        // 文字列のための型 "String"
  Serial.print("String: ");
  Serial.println(str);

  int i = 10;                   // 整数のための型 "int"
  Serial.print("Int: ");
  Serial.println(i);

  float f = 10;                 // 小数のための型 "float"
  Serial.print("Float: ");
  Serial.println(f);
}

void loop()
{
}
```

+ 値を自分で変えて試してみよう
+ 整数は，そのサイズによって， `int8_t`, `uint8_t`, `int16_t`, `uint16_t`, `int32_t`, `uint32_t` と種類がいろいろある．
	- `u` がつくのは正数のみで，つかないものは負数も扱える．
	- 数字が大きいほど大きな数字まで扱えるけど，その分，マイコンのメモリ（作業スペース）をたくさん使ってしまう．
+ 小数にも同様に， `float`, `double` と種類があり， `double` の方がより細かな値を扱える．


## リファレンス
詳細な説明はリファレンス（説明書）を参考にしよう！  
[http://www.musashinodenpa.com/arduino/ref/index.php](http://www.musashinodenpa.com/arduino/ref/index.php)


## ソースコードへのリンク
[GitHub](https://github.com/meltingrabbit/CanSatForHighSchoolStudents/tree/master/Arduino/ProgrammingTutorial02_Variable)

