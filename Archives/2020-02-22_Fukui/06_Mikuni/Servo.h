#ifndef SRV_H
#define SRV_H

#include "./PIN_ASSIGN.h"
#include <Servo.h>

/*
http://akizukidenshi.com/catalog/g/gM-08914/
*/

// #################### Servo ####################


void SRV_Init();
void SRV_SetPosition(uint8_t pos);
uint8_t SRV_GetPosition();
void SRV_Run();
void SRV_Detach();
void SRV_Attach();

typedef struct {
	Servo servo;
	uint8_t setPosition;
	uint8_t position;
} Servo_t;


#endif

