#include "./SD.h"
#include "./BarometerThermohygrometer.h"
#include "./IMU.h"
#include "./GPS.h"

void log();

void setup() {
	// Wire(Arduino-I2C)の初期化
	Wire.begin();
	// デバック用シリアル通信は9600bps
	Serial.begin(9600);

	SD_Init();			// SDカードの初期化．これは絶対最初に初期化！
	BTH_Init();			// 気圧・温度計を初期化
	IMU_Init();			// 9軸センサの初期化
	GPS_Init();			// GPSの初期化

	Serial.println(F("Init done"));
	delay(300);
}

void loop() {
	// 気圧・温度の値を更新
	BTH_Update();
	// 9軸センサの値を更新
	IMU_UpdateAll();
	// GPSの値を更新
	GPS_Update();
	log();
}


void log() {
	// 気圧の値を取得
	float pressure = BTH_GetPressure();
	// 湿度の値を取得
	float humidity = BTH_GetHumidity();
	// 温度の値を取得
	float temperature = BTH_GetTemperature();

	// 加速度センサのX軸の値を取得
	float acc_x = IMU_GetAccX();
	// 加速度センサのY軸の値を取得
	float acc_y = IMU_GetAccY();
	// 加速度センサのZ軸の値を取得
	float acc_z = IMU_GetAccZ();
	// ジャイロセンサのX軸の値を取得
	float gyr_x = IMU_GetGyrX();
	// ジャイロセンサのY軸の値を取得
	float gyr_y = IMU_GetGyrY();
	// ジャイロセンサのZ軸の値を取得
	float gyr_z = IMU_GetGyrZ();
	// 磁気センサのX軸の値を取得
	int mag_x = IMU_GetMagX();
	// 磁気センサのY軸の値を取得
	int mag_y = IMU_GetMagY();
	// 磁気センサのZ軸の値を取得
	int mag_z = IMU_GetMagZ();

	// 経度の値を取得
	float lat = GPS_GetLat();
	// 緯度の値を取得
	float lng = GPS_GetLng();
	// 高度の値を取得
	float height = GPS_GetHeight();

	// TODO: 本当にこれで望んでいたデータが保存できてるか確認しよう
	SD_Write(","
			 + String(pressure) + ","
			 + String(humidity) + ","
			 + String(temperature) + ","
			 + String(acc_x) + ","
			 + String(acc_y) + ","
			 + String(acc_z) + ","
			 + String(gyr_x) + ","
			 + String(gyr_y) + ","
			 + String(gyr_z) + ","
			 + String(mag_x) + ","
			 + String(mag_y) + ","
			 + String(mag_z) + ","
			 + String(lat) + ","
			 + String(lng) + ","
			 + String(height) + ","
			 );		// SDカードに保存
}