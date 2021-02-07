#ifndef CAMERA2_H
#define CAMERA2_H

/*
https://www.arducam.com/product/arducam-2mp-spi-camera-b0067-arduino/  
https://www.switch-science.com/catalog/3780/
*/

// #################### CAMERA ####################


#include "./PIN_ASSIGN.h"

#include <SPI.h>

void CAM2_Init();
void CAM2_TakePic();

typedef struct {

} Camera2_t;


#endif
