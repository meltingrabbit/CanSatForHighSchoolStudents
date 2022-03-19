# プログラミング講習 09. 機器の利用 その３
## 概要
+ マイコンに接続した機器を使ってみよう
	- 機器のテストコードで使った[サーボモータの回路とプログラム](../Test_Servo)を使う
	- ここでは，サーボモータを使って遊んでみよう


## ソースコード
```cpp
// サーボモータのライブラリ（便利なコードまとめ）を使うよ！ と宣言
#include "./Servo.h"
// すると，
// Servo.h に宣言されている
//   void SRV_Init();
//   void SRV_SetPosition(uint8_t angle);
//   uint8_t SRV_GetPosition();
//   void SRV_Run();
//   void SRV_Detach();
//   void SRV_Attach();
// という関数が使えるようになる
// 関数の説明は Servo.h に書かれている
// 関数の中身は Servo.ino に書かれている

uint16_t loop_count = 0;      // プログラムのどこからでも使える変数 loop_count を準備しておく

void setup()
{
  // デバック用シリアル通信は 9600bps
  Serial.begin(9600);

  SRV_Init();		// サーボモータを初期化

  Serial.println(F("Init done"));
  delay(300);
}

void loop()
{
  // 今何周目のループか表示
  Serial.println(loop_count);

  // ループカウンタが10の倍数のときに実行
  if (loop_count % 10 == 0) {
    Serial.println(F("Move Up!"));
    // 0 ~ 180 度に， 30 度ずつ， 0.5秒ごとに回転させる
    for(uint8_t angle = 0; angle <= 180; angle = angle + 30) {
      Serial.print(F("angle:"));
      Serial.println(angle);
      SRV_SetPosition(angle);
      SRV_Run();
      delay(500);       // 500 ms （0.5秒）待つ
    }
  }

  // ループカウンタを10で割った剰余が5のときに実行
  if (loop_count % 10 == 5) {
    Serial.println(F("Move Down!"));
    // 180 - 0 度に， 1 度ずつ， 0.02秒ごとに回転させる
    // 0.02秒と人間にとっては短い時間なので，なめらかにゆっくり回転するように見える
    for(uint8_t angle = 180; angle > 0; angle--) {
      Serial.print(F("angle:"));
      Serial.println(angle);
      SRV_SetPosition(angle);
      SRV_Run();
      delay(20);        // 20 ms （0.02秒）待つ
    }
  }

  // ループカウントを 1 増やす
  loop_count++;
  delay(1000);
}
```

+ `dalay` などを変更し，回転する速度を変えてみよう
+ 回転角を変えてみよう


## ピンアサイン（ピン配置）
+ `PIN_ASSIGN.h` というファイルで，マイコンのどのピンにどこを接続するかを定義している．
+ たとえば，ここではサーボモータに回転角を司令する信号を4番ピンに指定している
```cpp
#define PIN_SRV 4
```
+ 適切にピンアサインを変更することで，複数の機器を同時に接続したり，回路の設計を簡単にすることができる．


## 備考
+ `hoge++` とは， 変数 `hoge` の値を 1 増やす． `hoge--` とは， 変数 `hoge` の値を 1 減らす．
+ ここでは，講義の時間の都合上，用意された関数群を用いた．
+ 本来であれば，センサに応じたサンプルコードをインターネットなどからダウンロードすると良い．
	- 「センサ名 Arduino サンプルコード」などでGoogle検索をかけるとよい．


## リファレンス
詳細な説明はリファレンス（説明書）を参考にしよう！  
[http://www.musashinodenpa.com/arduino/ref/index.php](http://www.musashinodenpa.com/arduino/ref/index.php)


## ソースコードへのリンク
[GitHub](https://github.com/meltingrabbit/CanSatForHighSchoolStudents/tree/master/Arduino/ProgrammingTutorial09_Device3)

