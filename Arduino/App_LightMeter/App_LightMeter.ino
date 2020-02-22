#include "./Servo.h"
#include "./Light.h"

void setup()
{
	// デバック用シリアル通信は9600bps
	Serial.begin(9600);

	// サーボモータを初期化
	SRV_Init();
	// 光センサを初期化
	LIT_Init();

	Serial.println(F("Init done"));
	delay(300);
}

void loop()
{
	// 変数の初期化
	uint32_t light = 0;
	uint8_t  sampling_num = 20;

	// sampling_num回の平均値をとる
	for (int i = 0; i < sampling_num; i = i + 1) {
		light = light + LIT_Get();
	}
	light = light / sampling_num;

	// 明るさを角度に変換
	// lightは 0 - 1024
	// サーボは 0 - 180
	uint8_t angle = (uint8_t)( (float)light * 180.0 / 1024.0);

	// 表示
	Serial.print(F("Light = "));
	Serial.print(light);
	Serial.print(F(", Angle = "));
	Serial.println(angle);

	// サーボモータの角度をセット
	SRV_SetPosition(angle);
	// セットした角度にサーボモータを動かす
	SRV_Run();

	// 実行周期を調整
	delay(50);
}
