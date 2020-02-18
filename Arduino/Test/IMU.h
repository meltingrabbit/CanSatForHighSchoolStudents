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


#define IMU_COEF  (100.0)

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
int16_t IMU_GetMagX();
int16_t IMU_GetMagY();
int16_t IMU_GetMagZ();


typedef struct {
	// floatだとメモリを多く消費するので，intで保持し，Getterで変換
	int16_t xAccl;
	int16_t yAccl;
	int16_t zAccl;
	int16_t xGyro;
	int16_t yGyro;
	int16_t zGyro;
	int16_t xMag ;
	int16_t yMag ;
	int16_t zMag ;
} Imu_t;


#endif
