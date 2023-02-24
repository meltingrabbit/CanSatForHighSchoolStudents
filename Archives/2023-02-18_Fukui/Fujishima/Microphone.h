#ifndef MICROPHONE_H
#define MICROPHONE_H

/*
https://akizukidenshi.com/catalog/g/gK-05757/
*/

// #################### MICROPHONE ####################

#include "./PIN_ASSIGN.h"

// 初期化
void MIC_Init();
// 直近のマイクロフォンの値の平均値を取得
int MIC_GetAverage();
// 直近のマイクロフォンの値の最大値を取得
int MIC_GetMaximum();
// 直近のマイクロフォンの値を表示
void MIC_Print();

typedef struct {
	uint32_t average;
	uint32_t maximum;
} Microphone_t;

#endif