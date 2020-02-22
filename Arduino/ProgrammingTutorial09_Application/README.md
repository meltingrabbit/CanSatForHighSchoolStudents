# プログラミング講習 09. アプリケーション例 明るさ計
## 概要
+ マイコンに接続した複数の機器を用いてアプリケーションを作ろう
	- 機器のテストコードで使った[光センサの回路とプログラム](../Test_Light)と[サーボモータの回路とプログラム](../Test_Servo)を使う
	- ここでは，光センサからの入力に応じて動く明るさ計を作る．


## ソースコード
```cpp
// サーボモータのライブラリ（便利なコードまとめ）を使うよ！ と宣言
#include "./Servo.h"
// すると，
// Servo.h に宣言されている
//   void SRV_Init();
//   void SRV_SetPosition(uint8_t pos);
//   uint8_t SRV_GetPosition();
//   void SRV_Run();
//   void SRV_Detach();
//   void SRV_Attach();
// という関数が使えるようになる
// 関数の中身は Servo.c にかかれている

// 光センサのライブラリ（便利なコードまとめ）を使うよ！ と宣言
#include "./Light.h"
// すると，
// Light.h に宣言されている
//   void LIT_Init();
//   int  LIT_Get();
//   void LIT_Print();
// という関数が使えるようになる
// 関数の中身は Light.c にかかれている


void setup()
{
  // デバック用シリアル通信は9600bps
  Serial.begin(9600);

  // サーボモータを初期化
  SRV_Init();
  // 光センサを初期化
  LIT_Init();

  Serial.println(F("Init done"));
  delay(300);
}

void loop()
{
  // 変数の初期化
  uint32_t light = 0;
  uint8_t  sampling_num = 20;

  // sampling_num回の平均値をとる
  for (int i = 0; i < sampling_num; i = i + 1) {
    light = light + LIT_Get();
  }
  light = light / sampling_num;

  // 明るさを角度に変換
  // lightは 0 - 1024
  // サーボは 0 - 180
  uint8_t angle = (uint8_t)( (float)light * 180.0 / 1024.0);

  // 表示
  Serial.print(F("Light = "));
  Serial.print(light);
  Serial.print(F(", Angle = "));
  Serial.println(angle);

  // サーボモータの角度をセット
  SRV_SetPosition(angle);
  // セットした角度にサーボモータを動かす
  SRV_Run();

  // 実行周期を調整
  delay(50);
}
```

+ 光センサにライトを当てて，サーボモータがそれに合わせて動くことを試してみよう．


## ピンアサイン（ピン配置）
+ `PIN_ASSIGN.h` というファイルで，マイコンのどのピンにどこを接続するかを定義している．
+ たとえば，サーボモータで使う信号線や光センサのための入力ピンにどのピンを使うかを規定している．
```cpp
#define PIN_SRV 4
#define PIN_LIT A0
```
+ 適切にピンアサインを変更することで，複数の機器を同時に接続したり，回路の設計を簡単にすることができる．


## 備考
+ ここでは，講義の時間の都合上，用意された関数群を用いた．
+ 本来であれば，センサに応じたサンプルコードをインターネットなどからダウンロードすると良い．
	- 「センサ名 Arduino サンプルコード」などでGoogle検索をかけるとよい．


## リファレンス
詳細な説明はリファレンス（説明書）を参考にしよう！  
http://www.musashinodenpa.com/arduino/ref/index.php

