#ifndef LIGHT4_H
#define LIGHT4_H


/*
http://akizukidenshi.com/catalog/g/gI-00110/
*/


// #################### LIGHT ####################


#include "./PIN_ASSIGN.h"

// 初期化
void LIT4_Init();
// 光センサの値を更新して取得
int  LIT4_Get();
// 光センサの値を表示
void LIT4_Print();

// typedef struct {
// } Light_t;


#endif
