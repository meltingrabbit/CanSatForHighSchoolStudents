#include "./Servo.h"

void setup()
{
	// デバック用シリアル通信は9600bps
	Serial.begin(9600);

	SRV_Init();
	LIT_Init();

	Serial.println(F("Init done"));
	delay(300);
}

void loop()
{
	uint32_t light = 0;
	uint8_t  sampling_num = 20;

	// sampling_num回の平均値をとる
	for (int i = 0; i < sampling_num; i = i + 1) {
		light = light + LIT_Get();
	}
	light = light / sampling_num;

	// lightは 0 - 1024
	// サーボは 0 - 180
	uint8_t angle = (uint8_t)( (float)light * 180.0 / 1024.0);

	SRV_SetPosition(angle);
	SRV_Run();

	delay(50);
}
