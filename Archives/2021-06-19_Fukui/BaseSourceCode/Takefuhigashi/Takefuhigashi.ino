#include "./SD.h"
#include "./Camera2.h"
#include "./BarometerThermohygrometer.h"
#include "./Servo.h"


void setup() {
	// Wire(Arduino-I2C)の初期化
	Wire.begin();
	// デバック用シリアル通信は9600bps
	Serial.begin(9600);

	SD_Init();			// SDカードの初期化．これは絶対最初に初期化！
	BTH_Init();			// 気圧・温度計を初期化
	CAM2_Init();		// カメラの初期化．SDの後！
	SRV_Init();			// サーボモータの初期化

	SRV_SetPosition(0);	// サーボモータの司令角度を0度に設定
	SRV_Run();			// 設定した回転角へサーボモータを動かす

	Serial.println(F("Init done"));
	delay(300);
}

void loop() {
	// TODO: このままでは，打ち上げ前にプログラムが進んでしまう．
	//       打ち上がる前には先に進まないように修正しよう

	while (1) {
		// 気圧・温度計の値の更新
		BTH_Update();
		// 気圧を取得 [hPa]
		float pressure = BTH_GetPressure();

		// 気圧から高度に変換
		// まあ，ざっくり 10m上昇すると1hPa下がるとしよう．
		// TODO: この計算式が正しいか，実験で確かめよう
		float pressure_at_sea_level = 1013.250;
		float height = (pressure_at_sea_level - pressure) * 10;

		// 標高から地上からの高さに変換
		// TODO: 数式を正しくなおそう！
		float ground_height = height - 10.0;

		// 高度が30m以下なら，whileループを抜ける
		if (ground_height <= 30.0) {
			break;
		}
	}

	SRV_SetPosition(90);	// サーボモータの司令角度を90度に設定
							// TODO: 90度で大丈夫か検討する
	SRV_Run();				// 設定した回転角へサーボモータを動かす

	delay(200);		// 0.2秒まつ

	while (1) {
		// 写真を撮る
		CAM2_TakePic();

		// 気圧・温度計の値の更新
		BTH_Update();
		// 気圧を取得 [hPa]
		float pressure = BTH_GetPressure();

		// 気圧から高度に変換
		// まあ，ざっくり 10m上昇すると1hPa下がるとしよう．
		// TODO: この計算式が正しいか，実験で確かめよう
		float pressure_at_sea_level = 1013.250;
		float height = (pressure_at_sea_level - pressure) * 10;

		// 標高から地上からの高さに変換
		// TODO: 数式を正しくなおそう！
		float ground_height = height - 10.0;

		// 高度が5m以下なら，whileループを抜ける
		if (ground_height <= 5.0) {
			break;
		}
	}

	while (1) {
		Serial.println(F("End of program"));
		delay(1000);
	}
}
