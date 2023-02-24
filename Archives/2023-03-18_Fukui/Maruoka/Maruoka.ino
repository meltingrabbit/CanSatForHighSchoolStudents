#include "./SD.h"
#include "./Camera2.h"
#include "./BarometerThermohygrometer.h"
// #include "./DCMotor.h"
// #include "./IMU.h"
// #include "./Light.h"
// #include "./Servo.h"
// #include "./GPS.h"
// #include "./XBee.h"


uint16_t loop_count = 0;

// 気圧の初期値を取得
float reference_pressure = 0.0;
float current_pressure = 0.0;

// モード設定
int mode = 0; // モード0: 気圧測定モード、モード1: カメラ撮影モード、モード2: 撮影終了


void setup()
{
  // Wire(Arduino-I2C)の初期化
  Wire.begin();
  // デバック用シリアル通信は9600bps
  Serial.begin(9600);

  SD_Init();			// これは絶対最初に初期化！
  CAM2_Init();		// SDの後！
  BTH_Init();
  // DCM_Init();
  // IMU_Init();
  // LIT_Init();
  // SRV_Init();
  // GPS_Init();
  // XBEE_Init();
  reference_pressure = BTH_GetPressure();
  current_pressure = BTH_GetPressure();

  Serial.println(F("Init done"));
  delay(300);
  mode = 1; // 本番は消す
}

void loop()
{
  // IMU_UpdateAll();
  // IMU_PrintAcc();
  // IMU_PrintGyr();
  // IMU_PrintMag();
  // GPS_Update();
  // GPS_Print();
  // LIT_Print();
  BTH_Update();
  current_pressure = BTH_GetPressure();
  //   float pressure_at_sea_level = 1013.250;
  //   float height = (pressure_at_sea_level - pressure) * 10;
  //	 BTH_Print();
  //  Serial.print(F("Height = "));
  //  Serial.print(height);
  //  Serial.println(F(" [m]"));
  //  delay(1000);
  // 40m以上なので4hPa下がる

  if ((mode == 0) && (reference_pressure - current_pressure >= 4.0)) {
    mode = 1;
    delay(5000);
  } else if (mode = 1) {
    CAM2_TakePic();   // 写真を撮る
    delay(2000);      // 2000 ms 待つ
    if (reference_pressure - current_pressure >= 0.5) {
      // mode = 2; // 本番はこのコードのコメントアウトをなくす
      // Serial.println(F("Finish Mission!!")); // 本番はこのコードのコメントアウトをなくす
    }
  }


  SD_Write(String(loop_count));

  // DCは一旦含んでいない（基本的に使わないと考えているため）

  loop_count++;
  delay(1000);
}
