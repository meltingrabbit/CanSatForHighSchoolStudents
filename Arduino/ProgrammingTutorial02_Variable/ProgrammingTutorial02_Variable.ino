void setup()
{
  Serial.begin(9600);
  String s = "String";          // 文字列のための型 "String" 型変数 "s" に "String" を代入
  Serial.print("String: ");
  Serial.println(s);

  int i = 10;                   // 整数のための型 "int" 型変数 "i" に 10 を代入
  Serial.print("Int: ");
  Serial.println(i);

  float f = 10.0;               // 小数のための型 "float" 型変数 "f" に 10.0 を代入
  Serial.print("Float: ");
  Serial.println(f);
}

void loop()
{
}
