#ifndef SD_H
#define SD_H


#include <SPI.h>
#include <SD.h>
#include<Wire.h>


/*
http://akizukidenshi.com/catalog/g/gK-14015/
http://akizukidenshi.com/download/ds/akizuki/AE-microSD-LLCNV_sch_20190218_01.pdf
*/

// #################### SD ####################
#include "./PIN_ASSIGN.h"




void SD_Init();
void SD_Write(String str);
String SD_GetDirName();

typedef struct {
	String  logFileName;
	// char    logFileName[8];
	char    DirName[6];
	// File    logFile;
} Sd_t;


#endif
