void setup()
{
	Serial.begin(9600);
	String str = "String"
	Serial.print("String: ");
	Serial.println(str);

	int i = 10;
	Serial.print("Int: ");
	Serial.println(i);

	float f = 10;
	Serial.print("Float: ");
	Serial.println(f);
}

void loop()
{
}

