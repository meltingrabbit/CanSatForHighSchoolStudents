#include "./DCMoter.h"

void setup()
{
	// デバック用シリアル通信は9600bps
	Serial.begin(9600);

	DCM_Init();			// DCモータを初期化

	Serial.println(F("Init done"));
	delay(300);
}

void loop()
{
	Serial.println(F("Forward"));
	DCM_FORWARD();			// 正転
	delay(5000);			// 5000 ms 待つ
	Serial.println(F("Coast"));
	DCM_COAST();			// 空転
	delay(5000);			// 5000 ms 待つ
	Serial.println(F("Reverse"));
	DCM_REVERSE();			// 逆転
	delay(5000);			// 5000 ms 待つ
	Serial.println(F("Brake"));
	DCM_BRAKE();			// ブレーキ
	delay(5000);			// 5000 ms 待つ
}
