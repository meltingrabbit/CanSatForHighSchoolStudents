uint8_t i = 0;

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.print("Hello World!! ");
  Serial.println(i);
  i++;
  delay(1000);
}
