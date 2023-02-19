#include "./Light.h"
#include "./Light2.h"
#include "./Light3.h"
#include "./Light4.h"


void setup()
{
	// デバック用シリアル通信は9600bps
	Serial.begin(9600);

	LIT_Init();				// 光センサを初期化
	LIT2_Init();			// 光センサを初期化
	LIT3_Init();			// 光センサを初期化
	LIT4_Init();			// 光センサを初期化

	Serial.println(F("Init done"));
	delay(300);
}

void loop()
{
	// LIT_Print();			// 光センサの値を表示

	Serial.print(F("LIT:"));
	Serial.print(LIT_Get());
	Serial.print(F(", "));
	Serial.print(LIT2_Get());
	Serial.print(F(", "));
	Serial.print(LIT3_Get());
	Serial.print(F(", "));
	Serial.print(LIT4_Get());
	Serial.println(F(""));

	delay(50);				// 50 ms 待つ
}
