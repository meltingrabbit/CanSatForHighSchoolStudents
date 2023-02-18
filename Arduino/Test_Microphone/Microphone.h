#ifndef MICROPHONE_H
#define MICROPHONE_H

/*
http://akizukidenshi.com/catalog/g/gI-00110/
*/

// #################### LIGHT ####################

#include "./PIN_ASSIGN.h"

// 初期化
void MIC_Init();
// 直近のマイクロフォンの値を平均化して取得
int MIC_Get_Average();
// 直近のマイクロフォンの値の最大値を取得
int MIC_Get_Maximum();
// マイクロフォンの値を表示
void MIC_Print();

typedef struct {
} Microphone_t;

#endif
