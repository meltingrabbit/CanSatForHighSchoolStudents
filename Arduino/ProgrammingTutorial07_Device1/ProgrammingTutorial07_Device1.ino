// 気圧計のライブラリ（便利なコードまとめ）を使うよ！ と宣言
#include "./BarometerThermohygrometer.h"
// すると，
// BarometerThrmohygrometer.h に宣言されている
//  void BTH_Init();
//  void BTH_Update();
//  void BTH_Print();
//  float BTH_GetPressure();
//  float BTH_GetHumidity();
//  float BTH_GetTemperature();
// という関数が使えるようになる
// 関数の中身は Barometer.c にかかれている


void setup()
{
  // Wire(Arduino-I2C)の初期化．気圧計との通信を開始
  Wire.begin();
  // デバック用シリアル通信は9600bps
  Serial.begin(9600);

  // 気圧計を初期化
  BTH_Init();

  Serial.println(F("Init done"));
  delay(300);
}

void loop()
{
  // 気圧計の値を更新
  BTH_Update();
  // // 気圧計の値を表示
  BTH_Print();
  float pressure = BTH_GetPressure();

  // 気圧から高度に変換
  // まあ，ざっくり 10m上昇すると1hPa下がるとしようか．
  float pressure_at_sea_level = 1013.250;
  float height = (pressure_at_sea_level - pressure) * 10;

  Serial.print(F("Heig = "));
  Serial.print(height);
  Serial.println(F(" [m]"));
  delay(1000);
}
