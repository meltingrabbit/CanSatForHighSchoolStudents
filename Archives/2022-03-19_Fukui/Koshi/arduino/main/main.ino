#include "./IMU_Pololu.h"

void setup() {
  Wire.begin();

  Serial.begin(115200);
  Serial.println("Booting...");

  IMUP_Init();

  delay(500);
  Serial.println("setup done.");
  delay(50);
}

void loop() {
  IMUP_UpdateAll();

  /*
   * GPSからデータ取ってXBeeに飛ばすコードをこの辺に
   */
  
  Serial.println(IMUP_GetFallDetected());
  delay(10);
}
