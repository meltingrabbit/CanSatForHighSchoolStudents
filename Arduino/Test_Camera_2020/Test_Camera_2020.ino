#include "./SD.h"
#include "./Camera.h"


void setup()
{
	// Wire(Arduino-I2C)の初期化
	Wire.begin();
	// デバック用シリアル通信は9600bps
	Serial.begin(9600);

	// 初期化
	SD_Init();		// これは絶対最初に初期化！
	CAM_Init();		// SDの後！

	Serial.println(F("Init done"));
	delay(300);
}

void loop()
{
	CAM_TakePic();		// 写真を撮る
	delay(1000);			// 1000 ms 待つ
}
