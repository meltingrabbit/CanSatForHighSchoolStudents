#include "./Light.h"
#include "./Light2.h"

Light_t light2;



void LIT2_Init() {
}

int  LIT2_Get() {
	// たくさんとって平均してもいいかも？
	int value = analogRead(PIN_LIT2);
	return value;
}

void LIT2_Print() {
	int value = LIT2_Get();
	Serial.print(F("Lit2= "));
	Serial.print(value);
	Serial.println(F(""));
}
