#include "./GPS.h"


void setup()
{
	// デバック用シリアル通信は9600bps
	Serial.begin(9600);

	GPS_Init();		// GPSの初期化

	Serial.println(F("Init done"));
	delay(300);
}

void loop()
{
	GPS_Update();		// GPSの値をアップデート
	GPS_Print();		// GPSの値を表示

	delay(25);		// 25 ms 待つ
}
