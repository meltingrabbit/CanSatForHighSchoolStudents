void setup()
{
	Serial.begin(9600);

	int a = 10;

	if (a == 10) {
		Serial.println("a == 10");
	} else {
		Serial.println("otherwise");
	}

	if (a != 10) {
		Serial.println("a != 10");
	} else {
		Serial.println("otherwise");
	}

	if (a > 10) {
		Serial.println("a > 10");
	} else if (a >= 10) {
		Serial.println("a >= 10");
	} else {
		Serial.println("otherwise");
	}


	if ((a > 5) && (a < 20)) {
		Serial.println("(a > 5) && (a < 20)");
	} else {
		Serial.println("otherwise");
	}

	if ((a > 5) || (a > 20)) {
		Serial.println("(a > 5) || (a > 20)");
	} else {
		Serial.println("otherwise");
	}
}

void loop()
{
}

