#include "./BarometerThermohygrometer.h"
#include "./Light.h"
#include "./SD.h"
int i=0;
float temperature = 0.0;
float humidity = 0.0;
float light = 0.0;
void setup()
{
  // Wire(Arduino-I2C) の初期化．高度計（気圧計）・温湿度計との通信を開始
  Wire.begin();
  // デバック用シリアル通信は 9600bps
  Serial.begin(9600);
  // 高度計（気圧計）・温湿度計を初期化
  BTH_Init();
  SD_Init();

  Serial.println(F("Init done"));
  delay(300);
  while(1){
    light= analogRead(PIN_LIT);         //光センサーの値を読み取る
     Serial.println(light);
     delay(100);
     if(light>350)                //光センサーの値が一定値を超えるまでループする
      SD_Write(String(light));
      break;
     }
}


void loop()
{
  // 高度計（気圧計）・温湿度計の値を更新
  BTH_Update();
  // // 高度計（気圧計）・温湿度計の値を表示
  // BTH_Print();
  temperature = temperature + BTH_GetTemperature();     //10回温度、湿度の値を読み取って足す
  humidity = humidity + BTH_GetHumidity();
  i=i+1;
  delay(100);
  if(i==10){                                //10回ループしたら平均値を求める
   //Serial.println("AVG");
   float Avgt = temperature/10.0;
   float Avgh = humidity/10.0;
   SD_Write(String(Avgt));
   Serial.println("AVG tempuerature=");
   Serial.println(Avgt);
   SD_Write(String(Avgh));
   Serial.println("AVG humidity=");
   Serial.println(Avgh);
   while (1) {
    // プログラムおわり
   }
  }
}
 
