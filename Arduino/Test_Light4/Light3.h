#ifndef LIGHT3_H
#define LIGHT3_H


/*
http://akizukidenshi.com/catalog/g/gI-00110/
*/


// #################### LIGHT ####################


#include "./PIN_ASSIGN.h"

// 初期化
void LIT3_Init();
// 光センサの値を更新して取得
int  LIT3_Get();
// 光センサの値を表示
void LIT3_Print();

// typedef struct {
// } Light_t;


#endif
