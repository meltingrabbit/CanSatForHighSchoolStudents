#ifndef DC_MOTER_X2_H
#define DC_MOTER_X2_H


/*
https://akizukidenshi.com/catalog/g/gK-09848/
*/

// #################### DC Motor ####################
#include "./PIN_ASSIGN.h"

// 初期化
void DCM2_Init();
// 空転させる
void DCM2_COAST();
// 正転させる
void DCM2_FORWARD();
// 逆転させる
void DCM2_REVERSE();
// ブレーキさせる
void DCM2_BRAKE();

// typedef struct {
// } DcMotor_t;


#endif
