#ifndef IMU_POLOLU_H
#define IMU_POLOLU_H

/*
https://www.switch-science.com/catalog/2658/
*/

// #################### 9AXIS ####################
#include "./PIN_ASSIGN.h"


#include<Wire.h>
// デフォルトの I2C アドレス
#define IMUP_LSM6_ADDR     (0b1101011)
#define IMUP_LIS3MDL_ADDR  (0b0011110)

// 初期化
void IMUP_Init();
// 9軸すべての値をアップデート
void IMUP_UpdateAll();
// 加速度センサの値をアップデート
void IMUP_UpdateAcc();
// ジャイロセンサの値をアップデート
void IMUP_UpdateGyr();
// 磁気センサの値をアップデート
void IMUP_UpdateMag();
// 加速度センサの値を表示
void IMUP_PrintAcc();
// ジャイロセンサの値を表示
void IMUP_PrintGyr();
// 磁気センサの値を表示
void IMUP_PrintMag();

// 加速度センサのX軸の値を取得
float IMUP_GetAccX();
// 加速度センサのY軸の値を取得
float IMUP_GetAccY();
// 加速度センサのZ軸の値を取得
float IMUP_GetAccZ();
// ジャイロセンサのX軸の値を取得
float IMUP_GetGyrX();
// ジャイロセンサのY軸の値を取得
float IMUP_GetGyrY();
// ジャイロセンサのZ軸の値を取得
float IMUP_GetGyrZ();
// 磁気センサのX軸の値を取得
int IMUP_GetMagX();
// 磁気センサのY軸の値を取得
int IMUP_GetMagY();
// 磁気センサのZ軸の値を取得
int IMUP_GetMagZ();

// 落下後かどうか
boolean IMUP_GetFallDetected();


typedef struct {
	float xAccl;
	float yAccl;
	float zAccl;
	float xGyro;
	float yGyro;
	float zGyro;
	int   xMag ;
	int   yMag ;
	int   zMag ;
	float allAccl;
	float prevAllAccl;
	boolean fallen;
} ImuPololu_t;


#endif
