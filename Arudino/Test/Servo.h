#ifndef SRV_H
#define SRV_H

#include "./PIN_ASSIGN.h"
#include <Servo.h>


// #################### Servo ####################




void SRV_Init();
void SRV_SetPosition(int pos);
void SRV_Run();

typedef struct {
	Servo servo;
	int position;
} Servo_t;


#endif

