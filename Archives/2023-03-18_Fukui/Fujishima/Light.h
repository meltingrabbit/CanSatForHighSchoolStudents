#ifndef LIGHT_H
#define LIGHT_H


/*
http://akizukidenshi.com/catalog/g/gI-00110/
*/


// #################### LIGHT ####################


#include "./PIN_ASSIGN.h"

// 初期化
void LIT_Init();
// 光センサの値を更新して取得
int  LIT_Get();
// 光センサの値を表示
void LIT_Print();

typedef struct {
} Light_t;


#endif
