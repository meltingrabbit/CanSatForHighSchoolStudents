void setup()
{
  Serial.begin(9600);

  int a = 10;                         // 整数型 (int) の変数 a に整数 10 を代入

  Serial.println("a == 10 ? :");
  if (a == 10) {                      // a は 10 ？
    Serial.println("  -> a == 10");
  } else {                            // それ以外
    Serial.println("  -> otherwise");
  }

  Serial.println("a != 10 ? :");
  if (a != 10) {                      // a は 10 ではない？
    Serial.println("  -> a != 10");
  } else {                            // それ以外
    Serial.println("  -> otherwise");
  }

  Serial.println("a > 10 or a >= 10 ? :");
  if (a > 10) {                       // a は 10 より大きい？
    Serial.println("  -> a > 10");
  } else if (a >= 10) {               // a は 10 より大きくはないけど， 10 以上？
    Serial.println("  -> a >= 10");
  } else {                            // それ以外
    Serial.println("  -> otherwise");
  }


  Serial.println("(a > 5) && (a < 20) ? :");
  if ((a > 5) && (a < 20)) {          // a は 5 より大きく，かつ， 20 より小さい？
    Serial.println("  -> (a > 5) && (a < 20)");
  } else {                            // それ以外
    Serial.println("  -> otherwise");
  }

  Serial.println("(a > 5) || (a > 20) ? :");
  if ((a > 5) || (a > 20)) {          // a は 5 より大きい，または， 20 より大きい？
    Serial.println("  -> (a > 5) || (a > 20)");
  } else {                            // それ以外
    Serial.println("  -> otherwise");
  }
}

void loop()
{
}
