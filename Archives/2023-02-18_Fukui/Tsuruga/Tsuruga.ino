#include "./SD.h"
#include "./Camera2.h"
#include "./BarometerThermohygrometer.h"
#include "./Servo.h"


uint16_t loop_count = 0;

void setup()
{
	// Wire(Arduino-I2C)の初期化
	Wire.begin();
	// デバック用シリアル通信は9600bps
	Serial.begin(9600);

	SD_Init();			// これは絶対最初に初期化！
	CAM2_Init();		// SDの後！
	BTH_Init();
	// DCM_Init();
	// IMU_Init();
	// LIT_Init();
	SRV_Init();
	// GPS_Init();
	// XBEE_Init();

	Serial.println(F("Init done"));
	delay(300);
}

void loop()
{
	BTH_Update();
	BTH_Print();

	// if (loop_count % 10 == 3) {
		// CAM2_TakePic();
	//}
	// SD_Write(String(loop_count));

   // 無限ループ
  while(1)
  {
    Serial.println("Waintg for start...");
    float height = GetHeight();
    Serial.print("Height: ");
    Serial.println(height);
    // 計算した高さの表示
    if(height > 45.0)
    {
      break;
    }
    delay(1000);
  }

 while(1)
  {
    Serial.println("Waintg for driving servo...");
    float height = GetHeight();
    Serial.print("Height: ");
    Serial.println(height);
    // 計算した高さの表示
    if(height < 40.0)
    {
      break;
    }
    delay(1000);
  }
  //  float height =GetHeight();
  //  // 計測した高さを表示
  //  Serial.println(height);
  //  if (height<40.0)
  //  {
  //    SRV_SetPosition(180);
	// 		SRV_Run();
  //    break;
  //  }
  // }


}

float GetHeight()
{
  //高度計の値を更新
  BTH_Update();
  //  気圧から高度に変換
  // 10m上昇すると1hpa低下する
  float pressure=BTH_GetPressure();
  // 高さを計算する
  // 気圧から高度に変換
  float pressure_at_sea_level=1013.250;
  float height=(pressure_at_sea_level-pressure)*10;
  return height;
}
