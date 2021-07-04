#include "./SD.h"
#include "./Camera2.h"
#include "./Light.h"
#include "./Servo.h"


void setup() {
	// Wire(Arduino-I2C)の初期化
	Wire.begin();
	// デバック用シリアル通信は9600bps
	Serial.begin(9600);

	SD_Init();			// SDカードの初期化．これは絶対最初に初期化！
	CAM2_Init();		// カメラの初期化．SDの後！
	LIT_Init();			// 光センサの初期化
	SRV_Init();			// サーボモータの初期化

	SRV_SetPosition(0);	// サーボモータの司令角度を0度に設定
	SRV_Run();			// 設定した回転角へサーボモータを動かす

	Serial.println(F("Init done"));
	delay(300);
}

void loop() {
	// TODO: このままでは，打ち上げ前にプログラムが進んでしまう．
	//       打ち上がる前には先に進まないように修正しよう
  delay(90000);
	// TODO: パラシュートが開いたことを判定するのはこれで大丈夫？
	//       実際の場所では，パラシュートが開く前後で光センサの値がどう変化するか実験し
	//       条件式を適切に修正しよう
	while (1) {
		int light = LIT_Get();
		if (light > 700) {
			break;		// ループを抜ける
		}
		delay(1000);		// 3秒待つ
	}

	delay(3000);		// 3秒まつ
						// TODO: 3秒で目的の動作ができるかな？

	SRV_SetPosition(180);	// サーボモータの司令角度を180度に設定
							// TODO: 90度で大丈夫か検討する
	SRV_Run();				// 設定した回転角へサーボモータを動かす

	delay(200);		// 0.2秒まつ

	//CAM2_TakePic();		// 写真を撮る

	// TODO: 写真は１枚でいいのかな？

	while (5) {
  CAM2_TakePic();
		Serial.println(F("End of program"));
		delay(100);
	}
}
