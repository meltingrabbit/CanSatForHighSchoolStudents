#include "./SD.h"
#include "./Camera2.h"
#include "./BarometerThermohygrometer.h"
#include "./Servo.h"
#include "./GPS.h"


void setup()
{
	// Wire(Arduino-I2C)の初期化
	Wire.begin();
	// デバック用シリアル通信は9600bps
	Serial.begin(9600);

	SD_Init();			// これは絶対最初に初期化！
	CAM2_Init();		// SDの後！
	BTH_Init();
	// IMU_Init();
  // LIT_Init();
	SRV_Init();
	GPS_Init();

	Serial.println(F("Init done"));
	delay(300);
}

void loop()
{
	// GPS_Update();
	// GPS_Print();

  // スタート待ち
  while(1)
  {
    Serial.println(F("Waiting for startig..."));
    float height= GetHeight();
    Serial.print (F("Height = "));
    Serial.print(height);
    Serial.println(F(" [m]"));

    if (height >= 22.0)
    {
      Serial.println(F("BREAK!"));
      break;
    }

    delay(500);    
  }

  // 上空
  while(1)
  {
    Serial.println(F("Waiting for down under 40m..."));
    float height= GetHeight();
    Serial.print (F("Height = "));
    Serial.print(height);
    Serial.println(F(" [m]"));

    if (height <= 21.0)
    {
      Serial.println(F("BREAK!"));
      break;
    }

    delay(500);    
  }

  SRV_SetPosition(90);
  SRV_Run();


  while(1)
  {
    Serial.println(F("Caputure Loop!"));

    CAM2_TakePic();

    // GPSを更新
    GPS_Update();
    // GPS値の表示
    GPS_Print();
    // 経度の値を取得
    float gps_lat = GPS_GetLat();
    // 緯度の値を取得
    float gps_lng = GPS_GetLng();
    // 高度の値を取得
    float gps_height = GPS_GetHeight();

    SD_Write(String(gps_lat));
    SD_Write(String(gps_lng));
    SD_Write(String(gps_height));
    
    float height= GetHeight();
    Serial.print (F("Height = "));
    Serial.print(height);
    Serial.println(F(" [m]"));

    if (height <= 20.5)
    {
      Serial.println(F("BREAK!"));
      break;
    }

    delay(500);    
  }

  SRV_SetPosition(0);
  SRV_Run();

  while(1)
  {
    Serial.println(F("END!!!!"));
    delay(200);   
  }
}

float GetHeight()
{
  // 高度計（気圧計）等の値を更新
  BTH_Update();
  // 値を表示
  // BTH_Print();
  float pressure = BTH_GetPressure();

  // 高度に変換
  // 10mで1hPa
  float pressure_at_sea_level = 1013.250;
  float height = (pressure_at_sea_level -pressure)* 10;
  return height;
}
