#ifndef SRV_H
#define SRV_H

#include "./PIN_ASSIGN.h"
#include "./Adafruit_BMP280.h"

#include <Wire.h>

/*

http://okiraku-camera.tokyo/blog/?p=5291
*/

// #################### Barometer ####################


void BMP_Init();
void BMP_Update();

typedef struct {
} Barometer_t;


#endif

