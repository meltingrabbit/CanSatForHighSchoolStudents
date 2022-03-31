#include "./IMU.h"

#define PULLUP

#ifdef PULLUP
  #define Pressed  0
  #define Released 1
#else
  #define Pressed  1
  #define Released 0
#endif

#define SW_Pin        3
#define BaudRate 115200
#define dataSize    128

uint8_t SW_stat = Released * 0b11111111;
uint8_t IMU_Datas[dataSize];

void setup() {
  Serial.begin(BaudRate);
  pinMode(SW_Pin, INPUT_PULLUP);
  
}

void loop() {
  IMU_Data_Switch();
  IMU_Datas[0] = random(128);  //仮でランダムデータを代入:
  show_All_IMU_Datas();
  delay(1000);
/*
  SW_stat = SW_stat << 1 + digitalRead(SW_Pin);
  if(SW_old == Released && SW_new == Pressed){
    //とりあえずパス:
  }
 */
}

void show_All_IMU_Datas(){
  for(uint16_t i = 0; i < dataSize; i++){
    Serial.print("IMU_Datas[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(IMU_Datas[i]);
  }
  Serial.println();
}

void IMU_Data_Switch(){
  for(uint16_t i = dataSize - 1; i > 0; i--){
    IMU_Datas[i] = IMU_Datas[i - 1];
  }
}
