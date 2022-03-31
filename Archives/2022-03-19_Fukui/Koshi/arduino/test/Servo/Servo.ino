/*
 * サーボモータのテスト
 */

#include <Servo.h>

//配列を参照して角度を指定する場合コメント解除, 解除しない場合1度づつ角度変更:
//#define readArray

#define servoPin    5
#define volumes    12
#define delayTime 200

Servo servo;

#ifdef readArray
uint8_t angles[volumes] = {0, 30, 60, 90, 120, 150, 180, 150, 120, 90, 60, 30};
#endif

void setup() {
  servo.attach(servoPin);
  delay(500);
}

void loop() {
#ifdef readArray
  for(uint8_t i = 0; i < volumes; i++){
    servo.write(angles[i]);
    delay(delayTime);
  }
#else
  for(uint8_t i = 0; i < 180; i++){
    servo.write(i);
    delay(1000/180);
  }
  for(uint8_t i = 180; i > 0; i--){
    servo.write(i);
    delay(1000/180);
  }
#endif
}
