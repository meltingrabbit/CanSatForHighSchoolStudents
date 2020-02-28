#ifndef SRV2_H
#define SRV2_H

#include "./PIN_ASSIGN.h"
#include <Servo.h>

/*
http://akizukidenshi.com/catalog/g/gM-08914/
*/

// #################### Servo ####################


void SRV2_Init();
void SRV2_SetPosition(uint8_t pos);
uint8_t SRV2_GetPosition();
void SRV2_Run();

// typedef struct {
// 	Servo servo;
// 	uint8_t setPosition;
// 	uint8_t position;
// } Servo_t;


#endif
