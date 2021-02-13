#ifndef BTH_H
#define BTH_H

#include "./PIN_ASSIGN.h"
#include <Wire.h>

// #################### Barometer & Thermohygrometer ####################

// 初期化
void BTH_Init();
// センサ値の更新
void BTH_Update();
// センサ値の表示
void BTH_Print();
// 気圧の値を取得
float BTH_GetPressure();
// 湿度の値を取得
float BTH_GetHumidity();
// 温度の値を取得
float BTH_GetTemperature();

typedef struct {
	float   pressure;
	float   humidity;
	float   temperature;
} BarometerThermohygrometer_t;

#endif

