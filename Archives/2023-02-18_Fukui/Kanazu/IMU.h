#ifndef IMU_H
#define IMU_H


/*

http://akizukidenshi.com/catalog/g/gK-13010/

//================================================================//
//  AE-BMX055             Arduino UNO                             //
//    VCC                    +5V                                  //
//    GND                    GND                                  //
//    SDA                    A4(SDA)                              //
//    SCL                    A5(SCL)                              //
//                                                                //
//   (JP6,JP4,JP5はショートした状態)                              //
//   http://akizukidenshi.com/catalog/g/gK-13010/                 //
//================================================================//
*/

// #################### 9AXIS ####################
#include "./PIN_ASSIGN.h"


#include<Wire.h>
// BMX055 加速度センサのI2Cアドレス
#define IMU_ADDR_ACCL 0x19  // (JP1,JP2,JP3 = Openの時)
// BMX055 ジャイロセンサのI2Cアドレス
#define IMU_ADDR_GYRO 0x69  // (JP1,JP2,JP3 = Openの時)
// BMX055 磁気センサのI2Cアドレス
#define IMU_ADDR_MAG 0x13   // (JP1,JP2,JP3 = Openの時)

// 初期化
void IMU_Init();
// 9軸すべての値をアップデート
void IMU_UpdateAll();
// 加速度センサの値をアップデート
void IMU_UpdateAcc();
// ジャイロセンサの値をアップデート
void IMU_UpdateGyr();
// 磁気センサの値をアップデート
void IMU_UpdateMag();
// 加速度センサの値を表示
void IMU_PrintAcc();
// ジャイロセンサの値を表示
void IMU_PrintGyr();
// 磁気センサの値を表示
void IMU_PrintMag();

// 加速度センサのX軸の値を取得
float IMU_GetAccX();
// 加速度センサのY軸の値を取得
float IMU_GetAccY();
// 加速度センサのZ軸の値を取得
float IMU_GetAccZ();
// ジャイロセンサのX軸の値を取得
float IMU_GetGyrX();
// ジャイロセンサのY軸の値を取得
float IMU_GetGyrY();
// ジャイロセンサのZ軸の値を取得
float IMU_GetGyrZ();
// 磁気センサのX軸の値を取得
int IMU_GetMagX();
// 磁気センサのY軸の値を取得
int IMU_GetMagY();
// 磁気センサのZ軸の値を取得
int IMU_GetMagZ();


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
} Imu_t;


#endif
