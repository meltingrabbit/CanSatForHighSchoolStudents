#ifndef GPS_H
#define GPS_H

#include <SoftwareSerial.h>
#include "./PIN_ASSIGN.h"


// #################### GPS ####################

void GPS_Init();
void GPS_Update();
// void GPS_Print();

typedef struct {
} Gps_t;


#endif

