#ifndef DC_MOTER_X2_H
#define DC_MOTER_X2_H


/*
https://akizukidenshi.com/catalog/g/gK-09848/
*/

// #################### DC Motor ####################
#include "./PIN_ASSIGN.h"

void DCM2_Init();
void DCM2_COAST();
void DCM2_FORWARD();
void DCM2_REVERSE();
void DCM2_BRAKE();

typedef struct {
} DcMotor2_t;


#endif
