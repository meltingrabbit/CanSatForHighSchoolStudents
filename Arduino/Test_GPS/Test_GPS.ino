#include "./GPS.h"

uint16_t loop_count = 0;

void setup()
{
	// デバック用シリアル通信は9600bps
	Serial.begin(9600);

	GPS_Init();

	Serial.println(F("Init done"));
	delay(300);
}

void loop()
{
	GPS_Update();
	GPS_Print();

	loop_count++;
	delay(25);
}
