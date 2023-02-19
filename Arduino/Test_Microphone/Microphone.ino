#include "./Microphone.h"

Microphone_t microphone;

void MIC_Init() {}

int MIC_Get_Average() {
  // たくさんとって平均してもいいかも？
  int32_t valueSum = 0;
  int averageNum = 10;
  for (int8_t i = 0; i < averageNum; i++) {
    valueSum = abs(analogRead(PIN_MIC) - 512);
  }
  int value = valueSum / averageNum;
  return value;
}

int MIC_Get_Maximum() {
  int averageNum = 10;
  int value = 0;
  for (int8_t i = 0; i < averageNum; i++) {
    int valueTmp = abs(analogRead(PIN_MIC) - 512);
    if (value < valueTmp) {
      value = valueTmp;
    }
  }
  return value;
}

void MIC_Print() {
  int value = MIC_Get_Maximum();
  Serial.print(F("Microphone= "));
  Serial.print(value);
  Serial.println(F(""));
}
