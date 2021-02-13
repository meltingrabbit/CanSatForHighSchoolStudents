#ifndef LIGHT2_H
#define LIGHT2_H


/*
http://akizukidenshi.com/catalog/g/gI-00110/
*/


// #################### LIGHT ####################


#include "./PIN_ASSIGN.h"

// 初期化
void LIT2_Init();
// 光センサの値を更新して取得
int  LIT2_Get();
// 光センサの値を表示
void LIT2_Print();

// typedef struct {
// } Light_t;


#endif
