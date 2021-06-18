#include "./SD.h"
#include "./BarometerThermohygrometer.h"
#include "./Light.h"
#include "./IMU.h"
#include "./GPS.h"


void setup() {
	// Wire(Arduino-I2C)の初期化
	Wire.begin();
	// デバック用シリアル通信は9600bps
	Serial.begin(9600);

	SD_Init();			// SDカードの初期化．これは絶対最初に初期化！
	BTH_Init();			// 気圧・温度計を初期化
	LIT_Init();			// 光センサの初期化
	IMU_Init();			// 9軸センサの初期化
	GPS_Init();			// GPSの初期化

	Serial.println(F("Init done"));
	delay(300);
}

void loop() {
	// TODO: このままでは，打ち上げ前にプログラムが進んでしまう．
	//       打ち上がる前には先に進まないように修正しよう

	// TODO: パラシュートが開いたことを判定するのはこれで大丈夫？
	//       実際の場所では，パラシュートが開く前後で光センサの値がどう変化するか実験し
	//       条件式を適切に修正しよう
	while (1) {
		int light = LIT_Get();
		if (light > 100) {
			break;		// ループを抜ける
		}
		delay(1000);		// 1秒待つ
	}

	while (1) {
		// 気圧・温度計の値の更新
		BTH_Update();
		// GPSの値を更新
		GPS_Update();

		// 気圧の値を取得
		float pressure = BTH_GetPressure();
		// 湿度の値を取得
		float humidity = BTH_GetHumidity();
		// 温度の値を取得
		float temperature = BTH_GetTemperature();

		// 経度の値を取得
		float lat = GPS_GetLat();
		// 緯度の値を取得
		float lng = GPS_GetLng();
		// 高度の値を取得
		float height = GPS_GetHeight();

		// TODO: 取得した値はどうする？

		delay(1000);		// 1秒待つ
	}

	while (1) {
		Serial.println(F("End of program"));
		delay(1000);
	}
}
