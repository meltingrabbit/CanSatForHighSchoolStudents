void setup()
{
	Serial.begin(9600);

	for (int num = 0; num <= 10; num = num + 1) {
		Serial.println(num);
		delay(100);
	}

	for (int num = 0; num <= 10; num = num + 1) {

		if (num == 5) {
			break;
		}

		Serial.println(num);
		delay(100);
	}

	int count = 0;
	while (count < 10) {
		Serial.println(count);
		delay(100);

		count = count + 1;
	}

	while (1) {
		Serial.println(count);
		delay(100);

		count = count + 1;

		if (count >= 10) {
			break;
		}
	}
}

void loop()
{
}

