#include "./IMU.h"
//#include "./GPS.h"
#include "./Servo.h"
#include "./Servo2.h"


void setup()
{
  // Wire(Arduino-I2C)の初期化
  Wire.begin();
  // デバック用シリアル通信は9600bps
  Serial.begin(9600);

  IMU_Init();
  //GPS_Init();
  SRV_Init();
  SRV2_Init();

      Serial.println(F("Pos=0"));
      SRV_SetPosition(0);
      SRV2_SetPosition(180);
      SRV_Run();
      SRV2_Run();
      delay(2000);

  Serial.println(F("Init done"));
  delay(300);
}

void loop(){
  IMU_UpdateAll();
  IMU_PrintAcc();
  //IMU_PrintGyr();
  //IMU_PrintMag();
  //GPS_Update();
  //GPS_Print();

float Acc = IMU_GetAccZ();
  if((Acc>9.7)&&(Acc<10)){


      Serial.println(F("Pos=0"));
      SRV_SetPosition(0);
      SRV2_SetPosition(180);
      SRV_Run();
      SRV2_Run();
      delay(2000);

      Serial.println(F("Pos=180"));
      SRV_SetPosition(180);
      SRV2_SetPosition(0);
      SRV_Run();
      SRV2_Run();
      delay(2000);


//    Serial.println(F("Move Up!"));
//    for(int pos = 0; pos <= 180; pos = pos + 180) {
//      Serial.print(F("pos:"));
//      Serial.println(pos);
//      SRV_SetPosition(pos);
//      SRV2_SetPosition(180-pos);
//      SRV_Run();
//      SRV2_Run();
//      delay(1000);
//    }


  }

   Serial.println(F("END"));
   while (1) {
   }
}
