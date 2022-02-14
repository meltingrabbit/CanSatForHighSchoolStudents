#include "./IMU_Pololu.h"

void setup()
{
	// Wire(Arduino-I2C)の初期化
	Wire.begin();
	// デバック用シリアル通信は9600bps
	Serial.begin(9600);

	IMUP_Init();			// 9軸センサを初期化

	Serial.println(F("Init done"));
	delay(300);
}

void loop()
{
	IMUP_UpdateAll();		// 9軸センサの値をアップデート
	IMUP_PrintAcc();		// 取得した加速度を表示
	IMUP_PrintGyr();		// 取得した角加速度を表示
	IMUP_PrintMag();		// 取得した磁気を表示

	delay(250);				// 250 ms 待つ
}
