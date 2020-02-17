#include "./Servo.h"
uint16_t loop_count = 0;

void setup()
{
	// デバック用シリアル通信は9600bps
	Serial.begin(9600);

	SRV_Init();

	Serial.println(F("Init done"));
	delay(300);
}

void loop()
{

	Serial.println(loop_count);
	if (loop_count % 10 == 0) {
		Serial.println(F("Move Up!"));
		for(uint8_t pos = 0; pos <= 180; pos = pos + 30) {
			Serial.print(F("pos:"));
			Serial.println(pos);
			SRV_SetPosition(pos);
			SRV_Run();
			delay(500);
		}
	}
	if (loop_count % 10 == 5) {
		Serial.println(F("Move Down!"));
		for(uint8_t pos = 180; pos > 0; --pos) {
			Serial.print(F("pos:"));
			Serial.println(pos);
			SRV_SetPosition(pos);
			SRV_Run();
			delay(20);
		}
	}

	loop_count++;
	delay(1000);
}
