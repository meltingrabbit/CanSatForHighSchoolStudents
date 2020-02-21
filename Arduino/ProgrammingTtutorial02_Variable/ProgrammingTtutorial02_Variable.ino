void setup()
{
  Serial.begin(9600);
  String str = "String";        // 文字列のための型 "String"
  Serial.print("String: ");
  Serial.println(str);

  int i = 10;                   // 整数のための型 "int"
  Serial.print("Int: ");
  Serial.println(i);

  float f = 10;                 // 小数のための型 "float"
  Serial.print("Float: ");
  Serial.println(f);
}

void loop()
{
}

