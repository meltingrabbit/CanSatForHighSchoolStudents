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

// 初期化
void XBEE_Init();
// テスト用コード
void XBEE_Test();

// Xbeeで str 文字列を送信
#define XBEE_Print(str)   XbeeSerial.print(str)
// Xbeeで str 文字列を送信（改行あり）
#define XBEE_Println(str) XbeeSerial.println(str)

#endif

