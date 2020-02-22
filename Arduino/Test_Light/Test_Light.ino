#include "./Light.h"


void setup()
{
	// デバック用シリアル通信は9600bps
	Serial.begin(9600);

	LIT_Init();			// 光センサを初期化

	Serial.println(F("Init done"));
	delay(300);
}

void loop()
{
	LIT_Print();			// 光センサの値を表示

	delay(50);				// 50 ms 待つ
}
