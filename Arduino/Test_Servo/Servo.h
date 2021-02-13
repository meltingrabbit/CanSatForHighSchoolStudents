#ifndef SRV_H
#define SRV_H

#include "./PIN_ASSIGN.h"
#include <Servo.h>

/*
http://akizukidenshi.com/catalog/g/gM-08914/
*/

// #################### Servo ####################

// 初期化
void SRV_Init();
// 回転角を設定
void SRV_SetPosition(uint8_t pos);
// 現在の回転角を取得
uint8_t SRV_GetPosition();
// 設定した回転角へ動かす
void SRV_Run();

typedef struct {
	Servo servo;
	uint8_t setPosition;
	uint8_t position;
} Servo_t;


#endif

