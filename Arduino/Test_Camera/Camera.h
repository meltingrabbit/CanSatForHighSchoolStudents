#ifndef CAMERA_H
#define CAMERA_H

/*
https://www.switch-science.com/catalog/1241/
https://www.adafruit.com/product/397
*/

// #################### CAMERA ####################


#include "./PIN_ASSIGN.h"

#include "./Adafruit_VC0706.h"
#include <SPI.h>
#include <SoftwareSerial.h>
// #include <SD.h>


void CAM_Init();
void CAM_TakePic();

typedef struct {
} Camera_t;


#endif
