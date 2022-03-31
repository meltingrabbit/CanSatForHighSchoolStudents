//#include "./SD.h"
//#include "./Camera2.h"
#include "./BarometerThermohygrometer.h"
//#include "./DCMotor.h"
#include "./IMU_Pololu.h"
//#include "./Light.h"
#include "./Servo.h"
//#include "./GPS.h"
//#include "./XBee.h"


uint16_t loop_count = 0;

void setup()
{
  Wire.begin();
	// デバック用シリアル通信は9600bps
	Serial.begin(9600);

	//SD_Init();			// これは絶対最初に初期化！
	//CAM2_Init();		// SDの後！
	BTH_Init();
	//DCM_Init();
	IMUP_Init();
	//LIT_Init();
	SRV_Init();
	//GPS_Init();
	//XBEE_Init();

	Serial.println(F("Init done"));
	delay(300);
}



void loop()
{
  BTH_Update();    // センサの値をアップデート
  BTH_Print();    // アップデートした値を表示
  
  delay(500);

  IMUP_UpdateAll();    // 9軸センサの値をアップデート
  IMUP_PrintAcc();    // 取得した加速度を表示
  IMUP_PrintGyr();    // 取得した角加速度を表示
  IMUP_PrintMag();    // 取得した磁気を表示

  delay(250);       // 250 ms 待つ

  Serial.println(loop_count);
  if (loop_count % 10 == 0) {
    void SRV_attach();
    Serial.println(F("Move Up!"));
    for(uint8_t pos = 0; pos <= 180; pos = pos + 30) {
      Serial.print(F("pos:"));
      Serial.println(pos);
      SRV_SetPosition(pos);
      SRV_Run();
      delay(500);
    }
    void SRV_detach();
  }
  if (loop_count % 10 == 5) {
    Serial.println(F("Move Down!"));
    void SRV_attach();
    for(uint8_t pos = 180; pos > 0; --pos) {
      Serial.print(F("pos:"));
      Serial.println(pos);
      SRV_SetPosition(pos);
      SRV_Run();
      delay(20);
    }
    void SRV_detach();
  }

  loop_count++;
  delay(1000);
}
