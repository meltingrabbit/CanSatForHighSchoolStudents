#include "./SD.h"
#include "./Camera2.h"
#include "./BarometerThermohygrometer.h"
#include "./DCMotor.h"
//#include "./IMU.h"
#include "./Light.h"
#include "./Servo.h"
#include "./GPS.h"
#include "./XBee.h"
#include "./IMU_Pololu.h"

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
	//DCM_Init();
	IMUP_Init();
	//LIT_Init();
	SRV_Init();
	GPS_Init();
	//XBEE_Init();

	Serial.println(F("Init done"));
	delay(300);
}

void loop()
{
  int flag = 0;

  while(1)
  {
  	IMUP_UpdateAll();
  	IMUP_PrintAcc();
  	IMUP_PrintGyr();
  	IMUP_PrintMag();
  	GPS_Update();
  	GPS_Print();
  	//LIT_Print();
  	BTH_Update();
  	BTH_Print();
  	//XBEE_Test();
  
  float p=BTH_GetPressure();
  float pressure_at_sea_level=1013.250;
  float height=(pressure_at_sea_level-p)*10+17.5;
  Serial.print("Height = ");
  Serial.print(height);
  Serial.println("[m]");

// x, y の地磁気の値を取得
  int mag_x = IMUP_GetMagX();
  int mag_y = IMUP_GetMagY();

  // x, y の地磁気から，北からの方位を求める．
  // なお，本来は地磁気の xy 平面が描く楕円を原点を中心とした真円になおすキャリブレーションが必要
  float magnet_radian = atan2((float)mag_y, (float)mag_x);
  float magnet_degree = magnet_radian * 180.0 / PI;

  Serial.print(F("Direction: "));
  Serial.print(magnet_degree);
  Serial.println(F(" [deg]"));


  
    if (height>19&&flag==0)
  {
   SRV_SetPosition(10);  // 北を向く;
   SRV_Run(); 
  CAM2_TakePic();
  flag=1;
  }
  if (height>16&&flag==1)
  {
  CAM2_TakePic();
  flag=2;
  }
  if (height>12&&flag==2)
  {
  CAM2_TakePic();
  flag=3;
  }
  if (height>8&&flag==3)
  {
  CAM2_TakePic();
  flag=4;
  }
  if (height>4&&flag==4)
  {
  CAM2_TakePic();
  flag=5;
  }
  

 
   
  
  
    
  	if (loop_count % 10 == 3) {
  		CAM2_TakePic();
  	}
  	SD_Write(String(loop_count));
  
  	loop_count++;
  	delay(1000);
  }
}
