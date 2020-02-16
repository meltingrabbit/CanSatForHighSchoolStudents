#include "./Servo.h"


Servo_t servo;

void SRV_Init() {
	servo.position = 0;
	servo.setPosition = 0;

	servo.servo.attach(PIN_SRV);
	delay(1000);
	SRV_Run();

	Serial.println(F("Servo init done"));
}

void SRV_SetPosition(int pos) {
	servo.position = pos;
}

int SRV_GetPosition() {
	return servo.position;
}


void SRV_Run() {
	servo.servo.write(servo.setPosition);
	servo.position = servo.setPosition;
}
