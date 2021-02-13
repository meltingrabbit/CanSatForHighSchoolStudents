#ifndef XBEE_H
#define XBEE_H

#include <SoftwareSerial.h>
#include "./PIN_ASSIGN.h"

SoftwareSerial XbeeSerial(PIN_XBEE_TX, PIN_XBEE_RX);

/*
https://www.switch-science.com/catalog/4089/
https://www.switch-science.com/catalog/1166/
https://www.switch-science.com/catalog/3495/
https://qiita.com/s_fujii/items/9804eaf3599139164aa3
*/

// #################### XBEE ####################

void XBEE_Init();
void XBEE_Test();

#define XBEE_Print(str)   XbeeSerial.print(str)
#define XBEE_Println(str) XbeeSerial.println(str)

#endif

