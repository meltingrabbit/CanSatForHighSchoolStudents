#include "./SoundSensor.h"
#include "./SD.h"
#include <Wire.h>
#include <SPI.h>

int SoundSensor_GetIntensity() {
  int intensity_sum = 0; // 全サンプルの強度の和
  int intensity_ave = 0; // 全サンプルの強度の平均値
  int sample_num = 64;   // サンプルの取得回数（適当に与えたので変更して良い）
  
  for(int i = 0; i < sample_num; i++) {
    intensity_sum += analogRead(PIN_SOUND_SENSOR);
    
  }

  intensity_ave = intensity_sum / sample_num;

  return intensity_ave;
}
