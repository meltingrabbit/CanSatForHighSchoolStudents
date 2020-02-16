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


void IMU_Init();
void IMU_UpdateAll();
void IMU_UpdateAcc();
void IMU_UpdateGyr();
void IMU_UpdateMag();
void IMU_PrintAcc();
void IMU_PrintGyr();
void IMU_PrintMag();

float IMU_GetAccX();
float IMU_GetAccY();
float IMU_GetAccZ();
float IMU_GetGyrX();
float IMU_GetGyrY();
float IMU_GetGyrZ();
int IMU_GetMagX();
int IMU_GetMagY();
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
