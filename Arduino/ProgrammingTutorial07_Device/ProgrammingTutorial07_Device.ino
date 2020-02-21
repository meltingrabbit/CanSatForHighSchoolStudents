void setup()
{
	Serial.begin(9600);
	Serial.print("5+2: ");
	Serial.println(5+2);

	Serial.print("5-2: ");
	Serial.println(5-2);

	Serial.print("5*2: ");
	Serial.println(5*2);

	Serial.print("5/2: ");
	Serial.println(5/2);

	Serial.print("5/2.0: ");
	Serial.println(5/2.0);

	Serial.print("5%2: ");
	Serial.println(5%2);

	int a = 5;
	int b = 2;
	Serial.print("a/b: ");
	Serial.println(a/b);

	int c = a / b;
	Serial.print("c: ");
	Serial.println(c);

	float d = 5;
	float e = 2;
	Serial.print("d/e: ");
	Serial.println(d/e);

	float f = e / d;
	Serial.print("f: ");
	Serial.println(c);

}

void loop()
{
}

