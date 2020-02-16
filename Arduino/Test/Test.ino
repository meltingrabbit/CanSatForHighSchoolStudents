#include "./IMU.h"
#include "./GPS.h"
#include "./SD.h"
#include "./Servo.h"

int loop_count = 0;

void setup()
{
	// Wire(Arduino-I2C)の初期化
	Wire.begin();
	// デバック用シリアル通信は9600bps
	Serial.begin(9600);


	IMU_Init();
	GPS_Init();
	SD_Init();
	SRV_Init();

	Serial.print(F("Init done\n"));
	delay(300);
}

void loop()
{
	IMU_UpdateAll();
	IMU_PrintAcc();
	IMU_PrintGyr();
	IMU_PrintMag();
	GPS_Update();
	SD_Write(String(loop_count));

	loop_count++;
	delay(1001);
}
