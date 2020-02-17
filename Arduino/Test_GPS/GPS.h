#ifndef GPS_H
#define GPS_H

#include <SoftwareSerial.h>
#include "./PIN_ASSIGN.h"

/*
http://akizukidenshi.com/catalog/g/gK-09991/
*/

// #################### GPS ####################

void GPS_Init();
void GPS_Update();
void GPS_Print();

typedef struct {
	float lat;
	float lng;
	float height;
	uint16_t last_received_time;
} Gps_t;


#endif

