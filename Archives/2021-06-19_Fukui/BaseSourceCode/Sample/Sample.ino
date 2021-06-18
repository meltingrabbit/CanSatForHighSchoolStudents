#include "./SD.h"
#include "./Camera2.h"
#include "./BarometerThermohygrometer.h"
#include "./Light.h"
#include "./IMU.h"
#include "./GPS.h"
#include "./Servo.h"
#include "./XBee.h"


void setup() {
	// Wire(Arduino-I2C)の初期化
	Wire.begin();
	// デバック用シリアル通信は9600bps
	Serial.begin(9600);

	SD_Init();			// SDカードの初期化．これは絶対最初に初期化！
	BTH_Init();			// 気圧・温度計を初期化
	CAM2_Init();		// カメラの初期化．SDの後！
	LIT_Init();			// 光センサの初期化
	IMU_Init();			// 9軸センサの初期化
	GPS_Init();			// GPSの初期化
	SRV_Init();			// サーボモータの初期化
	XBEE_Init();		// XBEE無線機の初期化


	SRV_SetPosition(0);	// サーボモータの司令角度を0度に設定
	SRV_Run();			// 設定した回転角へサーボモータを動かす

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
		delay(100);		// 0.1秒待つ
	}

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

		// XBEEで高度を送信
		XBEE_Println(String(ground_height));

		// 高度が30m以下なら，whileループを抜ける
		if (ground_height <= 30.0) {
			break;
		}
	}

	SRV_SetPosition(90);	// サーボモータの司令角度を90度に設定
							// TODO: 90度で大丈夫か検討する
	SRV_Run();				// 設定した回転角へサーボモータを動かす

	while (1) {
		// GPSの値の更新
		GPS_Update();

		// 高度の値を取得
		float height = GPS_GetHeight();

		// 標高から地上からの高さに変換
		// TODO: 数式を正しくなおそう！
		float ground_height = height - 10.0;

		// SDカードに高度を保存
		SD_Write(String(ground_height));

		// 高度が10m以下なら，whileループを抜ける
		if (ground_height <= 10.0) {
			break;
		}
	}

	// 5枚写真を取る
	for (int i = 0; i < 5; i++) {
		CAM2_TakePic();		// 写真を撮る
	}


	// GPSの値の更新
	GPS_Update();
	// 位置情報を取得し，SDに保存
	SD_Write(String(GPS_GetLat()));
	SD_Write(String(GPS_GetLng()));
	SD_Write(String(GPS_GetHeight()));

	while (1) {
		Serial.println(F("End of program"));
		delay(1000);
	}
}
