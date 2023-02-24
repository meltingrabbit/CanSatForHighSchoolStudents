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

	SD_Init();			// これは絶対最初に初期化！
	CAM2_Init();		// SDの後！
	BTH_Init();
	//DCM_Init();
	//IMU_Init();
	//LIT_Init();
	//SRV_Init();
	GPS_Init();
	//XBEE_Init();

	Serial.println(F("Init done"));

  

	delay(300);
}

void loop()
{

  while(1)
  {
    float height = GetHeight();
    Serial.print(F("height: "));
    Serial.println(height);
    if (height > 45.0)
    {
      break;
    }
  	Serial.println(F("Waiting for starting..."));
    delay(1000);
  }

  while(1)
  {
    //IMU_UpdateAll();
    //IMU_PrintAcc();
    //IMU_PrintGyr();
    //IMU_PrintMag();
    GPS_Update();
    GPS_Print();
    //LIT_Print();
    BTH_Update();
    BTH_Print();
    float height = GetHeight();
    Serial.print(F("Height in Main Loop: "));
    Serial.println(height);

    if(height<=40)
    {
      CAM2_TakePic();
    }

    float latitude;
    float longitude;
    float gps_height;

    if(height<=30)
    {
      GPS_Update();
      GPS_Print();
      latitude = GPS_GetLat();
      longitude = GPS_GetLng();
      gps_height = GPS_GetHeight();

      SD_Write(String(latitude));
      SD_Write(String(longitude)); 
      SD_Write(String(gps_height));
    }

    if(height<=5)
    {	
      break;
    }
  }	

  while(1)
  {
  	Serial.println(F("END!!!"));
    delay(2000);
  }
}

float GetHeight()
{
  BTH_Update();		// センサの値をアップデート
  float pressure = BTH_GetPressure();
  Serial.print(F("pressure: "));
  Serial.println(pressure);
  float pressure_at_sea_level = 1013.250;
  float height = (pressure_at_sea_level - pressure) * 10; 
  return height;
}