#include "./XBee.h"


void setup()
{
	// デバック用シリアル通信は9600bps
	Serial.begin(9600);

	XBEE_Init();		// XBEEの初期化

	Serial.println(F("Init done"));
	delay(300);
}

void loop()
{
	XBEE_Test();		// XBEEの送受信テスト

	delay(25);			// 25 ms 待つ
}
