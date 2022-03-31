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

void setup()
{
	// Wire(Arduino-I2C)の初期化
	Wire.begin();
	// デバック用シリアル通信は9600bps
	Serial.begin(9600);

	//SD_Init();			// これは絶対最初に初期化！
	// CAM2_Init();		// SDの後！
	BTH_Init();
	//DCM_Init();
	//IMU_Init();
	//LIT_Init();
	//SRV_Init();
	//GPS_Init();
	//XBEE_Init();

	Serial.println(F("Init done"));
	delay(300);
}

void loop()
{
	//IMU_UpdateAll();
	//IMU_PrintAcc();
	//IMU_PrintGyr();
	//IMU_PrintMag();
	//GPS_Update();
	//GPS_Print();
	//LIT_Print();
	BTH_Update();
	BTH_Print();
	//XBEE_Test();
 float pressure_at_sea_level = 1013.250;
 float pressure = BTH_GetPressure();
 float height = (pressure_at_sea_level - pressure) * 10;
 CAM2_TakePic();
 Serial.print(F("Height = "));
 Serial.print(height);
 Serial.println(F("[m]"));
 if(height<45){
  Serial.println("４５ｍ以下");
  float gyro_x = IMU_GetGyrX();
  float gyro_y = IMU_GetGyrY();
  float gyro_z = IMU_GetGyrZ();
  SD_Write("gyro");
  SD_Write(String(gyro_x));
  SD_Write(String(gyro_y));
  SD_Write(String(gyro_z));
  }
 delay(1000);
}
Serial.print(F("Height = "));
 Serial.print(height);
 Serial.println(F("[m]"));}
  Serial.println("0ｍ");
  break;
 }
  
  
