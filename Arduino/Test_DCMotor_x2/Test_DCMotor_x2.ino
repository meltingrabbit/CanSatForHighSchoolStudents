#include "./DCMotor.h"
#include "./DCMotor2.h"

void setup()
{
	// デバック用シリアル通信は9600bps
	Serial.begin(9600);

	DCM_Init();			// DCモータを初期化
	DCM2_Init();		// DCモータ2を初期化

	Serial.println(F("Init done"));
	delay(300);
}

void loop()
{
	Serial.println(F("DCM1 Forward"));
	DCM_FORWARD();			// 正転
	delay(5000);			// 5000 ms 待つ
	Serial.println(F("DCM1 Coast"));
	DCM_COAST();			// 空転
	delay(5000);			// 5000 ms 待つ
	Serial.println(F("DCM1 Reverse"));
	DCM_REVERSE();			// 逆転
	delay(5000);			// 5000 ms 待つ
	Serial.println(F("DCM1 Brake"));
	DCM_BRAKE();			// ブレーキ
	delay(5000);			// 5000 ms 待つ

	Serial.println(F("DCM2 Forward"));
	DCM2_FORWARD();			// 正転
	delay(5000);			// 5000 ms 待つ
	Serial.println(F("DCM2 Coast"));
	DCM2_COAST();			// 空転
	delay(5000);			// 5000 ms 待つ
	Serial.println(F("DCM2 Reverse"));
	DCM2_REVERSE();			// 逆転
	delay(5000);			// 5000 ms 待つ
	Serial.println(F("DCM2 Brake"));
	DCM2_BRAKE();			// ブレーキ
	delay(5000);			// 5000 ms 待つ
}
