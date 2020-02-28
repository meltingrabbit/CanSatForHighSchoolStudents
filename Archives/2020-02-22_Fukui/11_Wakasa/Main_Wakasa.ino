#include "./Servo.h"
#include "./Barometer.h"


uint16_t loop_count = 0;

void setup()
{
  // Wire(Arduino-I2C)の初期化
  Wire.begin();
  // デバック用シリアル通信は9600bps
  Serial.begin(9600);

  SRV_Init();
  BMP_Init();


  Serial.println(F("Init done"));
  delay(300);
}

void loop()
{
  BMP_Update();
  //BMP_Print

float Pressure = BMP_GetPressure();
Serial.print(F("Preassure: "));
Serial.println(Pressure);
float Pressure_at_sea_level = 102504.0;

float height = (Pressure_at_sea_level - Pressure) / 100*10;
Serial.print(F("Height:"));
Serial.println(height);

if (height>=3){
if (height<4) {
  Serial.println(F("3-4"));
  SRV_SetPosition(60);
  SRV_Run();
 }
}
else if (height>=2) {

 if (height<3) {
  Serial.println(F("2-3"));
  SRV_SetPosition(120);
  SRV_Run();
 }
}
 else if (height<2) {

  Serial.println(F("-2  "));
  SRV_SetPosition(180);
  SRV_Run();
  }

 delay(1000);
 }
