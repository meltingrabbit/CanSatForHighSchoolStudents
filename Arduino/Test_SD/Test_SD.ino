#include "./SD.h"

uint16_t loop_count = 0;

void setup()
{
	// Wire(Arduino-I2C)の初期化
	Wire.begin();
	// デバック用シリアル通信は9600bps
	Serial.begin(9600);

	SD_Init();		// これは絶対最初に初期化！

	Serial.println(F("Init done"));
	delay(300);
}

void loop()
{
	SD_Write(String(loop_count));

	loop_count++;
	delay(1000);
}
