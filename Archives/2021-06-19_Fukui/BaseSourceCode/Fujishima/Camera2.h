#ifndef CAMERA2_H
#define CAMERA2_H

/*
https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/  
https://www.switch-science.com/catalog/3780/
*/

// #################### CAMERA ####################


#include "./PIN_ASSIGN.h"
#include "./ArduCAM.h"
#include <SPI.h>

// 初期化
void CAM2_Init(ArduCAM myCAM, int PIN_CAM2_SS);
// 撮影し，SDに保存
void CAM2_TakePic(ArduCAM myCAM, int PIN_CAM2_SS);

typedef struct {

} Camera2_t;


#endif
