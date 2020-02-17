#include "./IMU.h"

uint16_t loop_count = 0;

void setup()
{
	// Wire(Arduino-I2C)の初期化
	Wire.begin();
	// デバック用シリアル通信は9600bps
	Serial.begin(9600);

	IMU_Init();

	Serial.println(F("Init done"));
	delay(300);
}

void loop()
{
	IMU_UpdateAll();
	IMU_PrintAcc();
	IMU_PrintGyr();
	IMU_PrintMag();

	loop_count++;
	delay(250);
}
