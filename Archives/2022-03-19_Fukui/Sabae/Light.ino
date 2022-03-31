#include "./Light.h"

Light_t light;



void LIT_Init() {
}

int  LIT_Get() {
	// たくさんとって平均してもいいかも？
	int value = analogRead(PIN_LIT);
	return value;
}

void LIT_Print() {
	int value = LIT_Get();
	Serial.print(F("Lit= "));
	Serial.print(value);
	Serial.println(F(""));
}

void LIT_wait(){
  while(LIT_Get() < 700){
    Serial.println("Dark");
  }
  Serial.println("明るい！！！！！");
}
