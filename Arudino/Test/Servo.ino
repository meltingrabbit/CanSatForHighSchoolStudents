#include "./Servo.h"


Servo_t servo;

void SRV_Init() {
	servo.position = 0;

	servo.servo.attach(PIN_SRV);
	delay(1000);
	servo.servo.write(servo.position);

	Serial.println(F("Servo initialization done."));
}

void SRV_SetPosition(int pos) {
	servo.position = pos;
}
void SRV_Run() {
	servo.servo.write(servo.position);
}
