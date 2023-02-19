#include "./Light.h"
#include "./Light4.h"

Light_t light4;



void LIT4_Init() {
}

int  LIT4_Get() {
	// たくさんとって平均してもいいかも？
	int value = analogRead(PIN_LIT4);
	return value;
}

void LIT4_Print() {
	int value = LIT4_Get();
	Serial.print(F("Lit4= "));
	Serial.print(value);
	Serial.println(F(""));
}
