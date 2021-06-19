#include "./SD.h"
#include "./Camera2.h"
#include "./BarometerThermohygrometer.h"
#include "./IMU.h"
#include "./GPS.h"
#include "./XBee.h"
#include <SPI.h>

ArduCAM myCAM1(OV2640, PIN_CAM2_1_SS);
ArduCAM myCAM2(OV2640, PIN_CAM2_2_SS);

void setup() {
	// Wire(Arduino-I2C)の初期化
	Wire.begin();
	// デバック用シリアル通信は9600bps
	Serial.begin(9600);
  SPI.begin();    // SPIをここで初期化する

	SD_Init();			// SDカードの初期化．これは絶対最初に初期化！
	CAM2_Init(myCAM1, PIN_CAM2_1_SS);		// カメラの初期化．SDの後！
  CAM2_Init(myCAM2, PIN_CAM2_2_SS);    // カメラの初期化．SDの後！

	// FIXME: 2個目のカメラを入れる必要あり

	BTH_Init();			// 気圧計，温度計の初期化
	IMU_Init();			// 9軸センサの初期化
	GPS_Init();			// GPSの初期化
	XBEE_Init();		// XBEE無線機の初期化

	Serial.println(F("Init done"));
	delay(300);
}

void loop() {
	// TODO: このままでは，打ち上げ前にプログラムが進んでしまう．
	//       打ち上がる前には先に進まないように修正しよう

	while (1) {
		// GPSの値の更新
		GPS_Update();

		// 高度の値を取得
		float height = GPS_GetHeight();

		// 標高から地上からの高さに変換
		// TODO: 数式を正しくなおそう！
		float ground_height = height - 10.0;

		// 高度が35m以下なら？
		if (ground_height >= 35.0) {
			CAM2_TakePic(myCAM1);		// 1つ目のカメラで写真を撮る
      delay(1000);
      CAM2_TakePic(myCAM2);   // 1つ目のカメラで写真を撮る
		} else {
			break;
		}
	}


	while (1) {
		// GPSの値の更新
		GPS_Update();

		// 高度の値を取得
		float height = GPS_GetHeight();

		// 標高から地上からの高さに変換
		// TODO: 数式を正しくなおそう！
		float ground_height = height - 10.0;

		// 高度が3m以下なら，whileループを抜ける
		if (ground_height <= 3) {
			break;
		}
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
