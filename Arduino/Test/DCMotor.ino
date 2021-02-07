#include "./DCMotor.h"

DcMotor_t dcmotor;

void DCM_Init() {
	pinMode(PIN_DC_MOTER1, OUTPUT);
	pinMode(PIN_DC_MOTER2, OUTPUT);
	digitalWrite(PIN_DC_MOTER1, LOW);
	digitalWrite(PIN_DC_MOTER2, LOW);
	Serial.println(F("DC Motor init done."));
}

void DCM_COAST() {
	digitalWrite(PIN_DC_MOTER1, LOW);
	digitalWrite(PIN_DC_MOTER2, LOW);
}

void DCM_FORWARD() {
	digitalWrite(PIN_DC_MOTER1, HIGH);
	digitalWrite(PIN_DC_MOTER2, LOW);
}

void DCM_REVERSE() {
	digitalWrite(PIN_DC_MOTER1, LOW);
	digitalWrite(PIN_DC_MOTER2, HIGH);
}

void DCM_BRAKE() {
	digitalWrite(PIN_DC_MOTER1, HIGH);
	digitalWrite(PIN_DC_MOTER2, HIGH);
}


