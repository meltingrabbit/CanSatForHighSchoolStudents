void print_number(String str, int i);
int  my_max(int a, int b);

void setup()
{
	Serial.begin(9600);

	int a = 10;
	int b = 20;

	print_number("a", a);
	print_number("b", b);
	print_number("my_max(a,b)", my_max(a,b));
}

void loop()
{
}


void print_number(String str, int i) {
	Serial.print(Str);
	Serial.print(" :");
	Serial.println(i);
}

int  my_max(int a, int b) {
	int ret = 0;
	if (a > b) {
		ret = a;
	} else {
		ret = b;
	}
	return ret;
}

