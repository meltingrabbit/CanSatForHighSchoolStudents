#include "./GPS.h"

Gps_t gps;

SoftwareSerial GpsSerial(PIN_GPS_TX, PIN_GPS_RX);

// 非公開関数
// String GPS_NMEA2DMS_(float val);
// String GPS_NMEA2DM_(float val);
// String GPS_NMEA2DD_(float val);
float GPS_NMEA2DDf_(float val);
// String GPS_UTC2GMT900_(String str);



void GPS_Init() {
	GpsSerial.begin(9600);
	gps.lat = 0.0;
	gps.lng = 0.0;
	gps.height = 0.0;
	gps.last_received_time = 0;
	Serial.println(F("GPS init done"));
}


void GPS_Update() {
	// 1つのセンテンスを読み込む
	String line = GpsSerial.readStringUntil('\n');
	Serial.println(line);

	if(line != ""){
		uint16_t i;
		uint8_t  index = 0;
		uint16_t len = line.length();
		String   str = "";

		// StringListの生成(簡易)
		// const uint8_t MAX_LIST = 30;		// メモリ節約のために，極限まで小さくしたい！
		const uint8_t MAX_LIST = 12;		// メモリ節約のために，極限まで小さくしたい！ [9]までしか使わないから小さくしても良いはず．
		String list[MAX_LIST];
		for (i = 0; i < MAX_LIST; i++) {
			list[i] = "";
		}

		// 「,」を区切り文字として文字列を配列にする
		for (i = 0; i < len; i++) {
			if (index >= MAX_LIST) {
				break;
			}
			if (line[i] == ',') {
				list[index++] = str;
				str = "";
				continue;
			}
			str += line[i];
		}

		// $GPGGAセンテンスのみ読み込む
		if (list[0] == "$GPGGA") {

			// ステータス
			if(list[6] != "0") {
				// // 現在時刻
				// Serial.print(GPS_UTC2GMT900_(list[1]));

				// 緯度
				// Serial.print(F(" 緯度:"));
				// // Serial.print(GPS_NMEA2DMS_(list[2].toFloat()));
				// Serial.print(F("("));
				// Serial.print(GPS_NMEA2DD_(list[2].toFloat()));
				// Serial.print(F(")"));

				gps.lat = GPS_NMEA2DDf_(list[2].toFloat());

				// 経度
				// Serial.print(F(" 経度:"));
				// // Serial.print(GPS_NMEA2DMS_(list[4].toFloat()));
				// Serial.print(F("("));
				// Serial.print(GPS_NMEA2DD_(list[4].toFloat()));
				// Serial.print(F(")"));

				gps.lng = GPS_NMEA2DDf_(list[4].toFloat());

				// 海抜
				// Serial.print(F(" 海抜:"));
				// Serial.print(list[9]);
				// // list[10].toLowerCase();
				// // Serial.print(list[10]);
				// Serial.print(F(" m"));

				gps.height = list[9].toFloat();

				gps.last_received_time = millis() / 1000;
				Serial.print(F("測位成功"));
				// Serial.print(F("GPS OK"));
			} else {
				Serial.print(F("測位失敗"));
				// Serial.print(F("GPS NG"));
			}

			Serial.println(F(""));
		}
	}
}

void GPS_Print() {
	Serial.print(F("測位結果："));
	Serial.print(F("GPS: Lat="));
	Serial.print(GPS_GetLat(),6);
	Serial.print(F(", Lng="));
	Serial.print(GPS_GetLng(),6);
	Serial.print(F(", Height="));
	Serial.print(GPS_GetHeight(),2);
	Serial.print(F(", RecTime="));
	Serial.print(gps.last_received_time);
	Serial.println(F(""));
}

float GPS_GetLat() {
	return gps.lat;
}
float GPS_GetLng() {
	return gps.lng;
}
float GPS_GetHeight() {
	return gps.height;
}



// // NMEAの緯度経度を「度分秒」(DMS)の文字列に変換する
// String GPS_NMEA2DMS_(float val) {
// 	int d = val / 100;
// 	int m = ((val / 100.0) - d) * 100.0;
// 	float s = ((((val / 100.0) - d) * 100.0) - m) * 60;
// 	return String(d) + "度" + String(m) + "分" + String(s, 1) + "秒";
// }

// // (未使用)NMEAの緯度経度を「度分」(DM)の文字列に変換する
// String GPS_NMEA2DM_(float val) {
// 	int d = val / 100;
// 	float m = ((val / 100.0) - d) * 100.0;
// 	return String(d) + "度" + String(m, 4) + "分";
// }

// // NMEAの緯度経度を「度」(DD)の文字列に変換する
// String GPS_NMEA2DD_(float val) {
// 	int d = val / 100;
// 	int m = (((val / 100.0) - d) * 100.0) / 60;
// 	float s = (((((val / 100.0) - d) * 100.0) - m) * 60) / (60 * 60);
// 	return String(d + m + s, 6);
// }

// NMEAの緯度経度を「度」(DD)のfloatに変換する
// dddmm.mmmmmm
float GPS_NMEA2DDf_(float val) {
	int   d = (int)(val / 100);
	float m = (((val / 100.0) - d) * 100.0) / 60;
	// float s = (((((val / 100.0) - d) * 100.0) - m) * 60) / (60 * 60);
	// return d + m + s;
	return d + m;
}

// // UTC時刻から日本の標準時刻に変換する(GMT+9:00)
// String GPS_UTC2GMT900_(String str) {
// 	int hh = (str.substring(0,2).toInt()) + 9;
// 	if(hh > 24) hh = hh - 24;
// 	return String(hh,DEC) + ":" + str.substring(2,4) + ":" + str.substring(4,6);
// }

