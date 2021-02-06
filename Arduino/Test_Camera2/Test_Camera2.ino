#include "./SD.h"
#include "./Camera2.h"


void setup()
{
	// Wire(Arduino-I2C)の初期化
	Wire.begin();
	// デバック用シリアル通信は9600bps
	Serial.begin(9600);

	// 初期化
	SD_Init();		// これは絶対最初に初期化！
	CAM2_Init();		// SDの後！

	Serial.println(F("Init done"));
	delay(300);
}

void loop()
{
	CAM2_TakePic();		// 写真を撮る
	delay(3000);			// 3000 ms 待つ
}
