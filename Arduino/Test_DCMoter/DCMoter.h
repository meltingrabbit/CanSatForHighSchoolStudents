#ifndef DC_MOTER_H
#define DC_MOTER_H


/*
https://akizukidenshi.com/catalog/g/gK-09848/
*/

// #################### DC Moter ####################
#include "./PIN_ASSIGN.h"

void DCM_Init();
void DCM_COAST();
void DCM_FORWARD();
void DCM_REVERSE();
void DCM_BRAKE();

typedef struct {
} DcMoter_t;


#endif
