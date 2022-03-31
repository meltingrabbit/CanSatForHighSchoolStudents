#ifndef DC_MOTER_H
#define DC_MOTER_H


/*
https://akizukidenshi.com/catalog/g/gK-09848/
*/

// #################### DC Motor ####################
#include "./PIN_ASSIGN.h"

// 初期化
void DCM_Init();
// 空転させる
void DCM_COAST();
// 正転させる
void DCM_FORWARD();
// 逆転させる
void DCM_REVERSE();
// ブレーキさせる
void DCM_BRAKE();

typedef struct {
} DcMotor_t;


#endif
