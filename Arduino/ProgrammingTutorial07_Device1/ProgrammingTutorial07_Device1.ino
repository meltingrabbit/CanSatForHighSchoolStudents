// 気圧計のライブラリ（便利なコードまとめ）を使うよ！ と宣言
#include "./Barometer.h"
// すると，
// Barometer.h に宣言されている
//   void BMP_Init();
//   void BMP_Update();
//   void BMP_Print();
//   float BMP_GetPressure();
//   float BMP_GetTemperature();
// という関数が使えるようになる
// 関数の中身は Barometer.c にかかれている


void setup()
{
  // Wire(Arduino-I2C)の初期化．気圧計との通信を開始
  Wire.begin();
  // デバック用シリアル通信は9600bps
  Serial.begin(9600);

  // 気圧計を初期化
  BMP_Init();

  Serial.println(F("Init done"));
  delay(300);
}

void loop()
{
  // 気圧計の値を更新
  BMP_Update();
  // // 気圧計の値を表示
  // BMP_Print();

  // 気圧計の値を取得
  float pressure = BMP_GetPressure();
  Serial.print(F("Pressure: "));
  Serial.print(pressure);
  Serial.println(F(" [Pa]"));

  // 気圧から高度に変換
  // まあ，ざっくり 10m上昇すると1hPa下がるとしようか．
  float pressure_at_sea_level = 101325.0;
  float height = (pressure_at_sea_level - pressure) / 100 * 10;

  Serial.print(F("Height: "));
  Serial.print(height);
  Serial.println(F(" [m]"));

  delay(1000);
}
