#include "./SD.h"
#include "./BarometerThermohygrometer.h"
#include "./Light.h"
#include "./IMU.h"

float get_height();

void setup() {
	// Wire(Arduino-I2C)の初期化
	Wire.begin();
	// デバック用シリアル通信は9600bps
	Serial.begin(9600);

	SD_Init();			// SDカードの初期化．これは絶対最初に初期化！
	BTH_Init();			// 気圧・温度計を初期化
	LIT_Init();			// 光センサの初期化
	IMU_Init();			// 9軸センサの初期化

	Serial.println(F("Init done"));
	delay(300);
}

void loop() {
	while (1) {
		IMU_UpdateAll();				// 9軸センサの値を更新
		float acc_z = IMU_GetAccZ();	// z軸の加速度を取得
		// TODO: どういう条件だと，放出を検出できる？
		if (acc_z > 0.0) {
			break;	// whileループを抜ける
		}
	}

	while (1) {
		float height = get_height();	// 高さを計算する関数を呼ぶ

		// 高度が45m以下なら，whileループを抜ける
		if (height <= 45.0) {
			break;
		}
	}


	while (1) {
		// TODO: スピーカーを鳴らすプログラム
		// TODO: マイクで計測するプログラム
		// TODO: SDカードに保存するプログラム


		float height = get_height();	// 高さを計算する関数を呼ぶ

		// 高度が5m以下なら，whileループを抜ける
		if (height <= 5.0) {
			break;
		}

		while (1) {
			float height_now = get_height();		// 高さを計算する関数を呼ぶ
			float distance = height - height_now;	// 進んだ距離を計算
			if (distance >= 5.0) {
				break;		// 5m以上進んでいたらwhileループを抜ける
			}
		}
	}

	while (1) {
		Serial.println(F("End of program"));
		delay(1000);
	}
}


// 高さを取得する関数
float get_height()
{
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

	return ground_height;		// 高さを返す
}