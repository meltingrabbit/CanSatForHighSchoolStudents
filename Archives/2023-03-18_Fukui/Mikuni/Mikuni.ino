
#include "./SD.h"
#include "./Camera2.h"
#include "./BarometerThermohygrometer.h"
#include "./DCMotor.h"
#include "./IMU.h"
#include "./Light.h"
#include "./Servo.h"
#include "./GPS.h"
#include "./XBee.h"


uint16_t loop_count = 0;




//蓋の開閉フラグ
int huta_aita = 0;
int start_shita = 0;
int end_shita = 0;

void setup()
{
	// Wire(Arduino-I2C)の初期化
	Wire.begin();
	// デバック用シリアル通信は9600bps
	Serial.begin(9600);

	SD_Init();			// これは絶対最初に初期化！
	CAM2_Init();		// SDの後！
	BTH_Init();
//	DCM_Init();
//	IMU_Init();
//	LIT_Init();
	SRV_Init();
//	GPS_Init();
//	XBEE_Init();

	Serial.println(F("Init done"));
	delay(300);
}

void loop()
{
  if(end_shita == 1)
    return;

  if(start_shita ==0)
 { while(1)
  { //
    BTH_Update();
    float pressure = BTH_GetPressure();
     // 気圧から高度に変換
  // まあ，ざっくり 10m 上昇すると 1hPa 下がるとしようか．
  float pressure_at_sea_level = 1013.250;
  float height = (pressure_at_sea_level - pressure) * 10;

  Serial.print(F("Height = "));
  Serial.print(height);
  Serial.println(F(" [m]"));

  if(height>40)
  {
    Serial.println("start");
    start_shita = 1;
    break;
  }
  delay(1000);
    
    //高度を取得
    //高度が40m以上だったら、break
  }
 }



  // 高度計（気圧計）・温湿度計の値を更新
  BTH_Update();
  // // 高度計（気圧計）・温湿度計の値を表示
  // BTH_Print();
  float pressure = BTH_GetPressure();

  // 気圧から高度に変換
  // まあ，ざっくり 10m 上昇すると 1hPa 下がるとしようか．
  float pressure_at_sea_level = 1013.250;
  float height = (pressure_at_sea_level - pressure) * 10;

  Serial.print(F("Height = "));
  Serial.print(height);
  Serial.println(F(" [m]"));

  if (height<35 && huta_aita == 0)
  {
    Serial.print(F("pos:"));
 		Serial.println(90);
 		SRV_SetPosition(90);
	 	SRV_Run();
     huta_aita = 1;
     }



  delay(1000);



	// if (loop_count % 10 == 3) {
	// 	CAM2_TakePic();
	// }
	// SD_Write(String(loop_count));
if(height<30)
{
  	CAM2_TakePic();		// 写真を撮る
	delay(100);			// 1000 ms 待つ

	Serial.println(F("Init done"));
}

  if(height<5)
  {Serial.println(F("end"));
    end_shita = 1; 
    }
}
