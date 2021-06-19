#include "./SD.h"
#include "./Camera2.h"
#include "./BarometerThermohygrometer.h"
#include "./GPS.h"


void setup() {
	// Wire(Arduino-I2C)の初期化
	Wire.begin();
	// デバック用シリアル通信は9600bps
	Serial.begin(9600);

	SD_Init();			// SDカードの初期化．これは絶対最初に初期化！
	BTH_Init();			// 気圧・温度計を初期化
	CAM2_Init();		// カメラの初期化．SDの後！
	GPS_Init();			// GPSの初期化

	Serial.println(F("Init done"));
	delay(300);
}

void loop() {
	// TODO: このままでは，打ち上げ前にプログラムが進んでしまう．
	//       打ち上がる前には先に進まないように修正しよう

	while (1) {
		// 気圧・温度計の値の更新
		BTH_Update();
		// GPSの値を更新
		GPS_Update();

		// TODO: 取得したデータはどうする？どこに保存する？

		CAM2_TakePic();		// 写真を撮る

		delay(200);		// 0.2秒まつ
						// TODO: 0.2秒で目的の動作ができるかな？
	}

	while (1) {
		Serial.println(F("End of program"));
		delay(1000);
	}
}
