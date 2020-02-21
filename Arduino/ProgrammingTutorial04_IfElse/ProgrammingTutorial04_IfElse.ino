void setup()
{
  Serial.begin(9600);

  int a = 10;                     // aに整数10を代入

  if (a == 10) {                  // aは10？
    Serial.println("a == 10");
  } else {                        // それ以外
    Serial.println("otherwise");
  }

  if (a != 10) {                  // aは10ではない？
    Serial.println("a != 10");
  } else {                        // それ以外
    Serial.println("otherwise");
  }

  if (a > 10) {                   // aは10より大きい？
    Serial.println("a > 10");
  } else if (a >= 10) {           // aは10より大きくはないけど，10以上？
    Serial.println("a >= 10");
  } else {                        // それ以外
    Serial.println("otherwise");
  }


  if ((a > 5) && (a < 20)) {      // aは5より大きく，かつ，20より小さい？
    Serial.println("(a > 5) && (a < 20)");
  } else {                        // それ以外
    Serial.println("otherwise");
  }

  if ((a > 5) || (a > 20)) {      // aは5より大きい，または，20より大きい？
    Serial.println("(a > 5) || (a > 20)");
  } else {                        // それ以外
    Serial.println("otherwise");
  }
}

void loop()
{
}

