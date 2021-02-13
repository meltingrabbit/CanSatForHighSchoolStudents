#ifndef GPS_H
#define GPS_H

#include <SoftwareSerial.h>
#include "./PIN_ASSIGN.h"

/*
http://akizukidenshi.com/catalog/g/gK-09991/
*/

// #################### GPS ####################

// 初期化
void GPS_Init();
// センサ値の更新
void GPS_Update();
// センサ値の表示
void GPS_Print();
// 経度の値を取得
float GPS_GetLat();
// 緯度の値を取得
float GPS_GetLng();
// 高度の値を取得
float GPS_GetHeight();

typedef struct {
	float lat;
	float lng;
	float height;
	uint16_t last_received_time;
} Gps_t;


#endif

