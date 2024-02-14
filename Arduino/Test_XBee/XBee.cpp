#include "./XBee.h"


void XBEE_Init() {
	XbeeSerial.begin(9600);
	Serial.println(F("Xbee init done"));
}

void XBEE_Test() {
	// char receiveData[5];
	// if (XbeeSerial.available() > 5) {
	// 	XbeeSerial.readBytes(receiveData, 5);
	// 	Serial.println("");
	// 	Serial.print("Receive data:");
	// 	Serial.println(receiveData);
	// 	XbeeSerial.println("rec!!");
	// }
	static uint32_t rec_count = 0;

	const uint8_t MAX_LEN = 32;
	char receive_data[MAX_LEN+1];

	delay(500);

	uint8_t  len = 0;
	uint32_t rec_len = XbeeSerial.available();

	if (rec_len == 0) return;

	// Serial.print("Rec len: ");
	// Serial.println(rec_len);

	if (rec_len < MAX_LEN) {
		len = rec_len;
	} else {
		len = MAX_LEN;
	}

	XbeeSerial.readBytes(receive_data, len);
	// なんか文字列終端のnullが消えて，変なデータが入ってるきがしたので．
	receive_data[len] = '\0';

	// Serial.print("len: ");
	// Serial.println(len);

	Serial.print("Receive data ");
	Serial.print(rec_count);
	Serial.print(": ");
	// Serial.println(receive_data);
	Serial.println(receive_data);
	XBEE_Print("rec_count: ");
	XBEE_Println(rec_count);

	rec_count++;
}

