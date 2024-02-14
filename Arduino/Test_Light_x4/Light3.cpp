#include "./Light.h"
#include "./Light3.h"

Light_t light3;



void LIT3_Init() {
}

int  LIT3_Get() {
	// たくさんとって平均してもいいかも？
	int value = analogRead(PIN_LIT3);
	return value;
}

void LIT3_Print() {
	int value = LIT3_Get();
	Serial.print(F("Lit3= "));
	Serial.print(value);
	Serial.println(F(""));
}
