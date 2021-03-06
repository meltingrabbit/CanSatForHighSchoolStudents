void setup()
{
  Serial.begin(9600);

  Serial.println("#### FOR ####");
  // 初期化; 継続条件; 変化式
  // ↓
  // 最初に実行される; ループを続けるかの条件; ループの最後に毎回実行される文
  for (int num = 0; num <= 10; num = num + 1) {
    Serial.print("Loop1: ");
    Serial.println(num);
    delay(100);
  }

  Serial.println("#### FOR BREAK ####");
  for (int num = 0; num <= 10; num = num + 1) {

    if (num == 5) {
      break;                      // ループから抜ける
    }

    Serial.print("Loop2: ");
    Serial.println(num);
    delay(100);
  }


  Serial.println("#### WHILE ####");
  int count = 0;
  // 継続条件
  while (count < 10) {
    Serial.print("Loop3: ");
    Serial.println(count);
    delay(100);

    count = count + 1;
  }

  Serial.println("#### WHILE BREAK ####");
  count = 0;
  while (1) {
    Serial.print("Loop4: ");
    Serial.println(count);
    delay(100);

    count = count + 1;

    if (count >= 10) {
      break;                      // ループから抜ける
    }
  }
}

void loop()
{
}

