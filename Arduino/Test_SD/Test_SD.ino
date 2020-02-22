#include "./SD.h"

uint16_t loop_count = 0;

void setup()
{
	// Wire(Arduino-I2C)の初期化
	Wire.begin();
	// デバック用シリアル通信は9600bps
	Serial.begin(9600);

	// SDカードの初期化
	SD_Init();

	Serial.println(F("Init done"));
	delay(300);
}

void loop()
{
	SD_Write(String(loop_count));		// loop_count の値をSDカードに書き込む

	loop_count++;				// loop_countに１を足す
	delay(1000);
}
