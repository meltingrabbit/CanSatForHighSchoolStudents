#include "./SD.h"
#include "./Camera2.h"
#include "./BarometerThermohygrometer.h"
#include "./DCMotor.h"
#include "./IMU.h"
#include "./Light.h"
#include "./Servo.h"
#include "./GPS.h"
#include "./XBee.h"
#include "./Microphone.h"

Servo_t servo2;

uint16_t loop_count = 0;
int angle=0;//サーボモーターを回した角度
float lat;//緯度
float lng;//経度
int degree;//０～３６０で方角を表す
float height;
int SampleVolume=0;
int time=0;

void setup()
{
	// Wire(Arduino-I2C)の初期化
	Wire.begin();
	// デバック用シリアル通信は9600bps
	Serial.begin(9600);

	SD_Init();			// これは絶対最初に初期化！
	CAM2_Init();		// SDの後！
	BTH_Init();
	DCM_Init();
	IMU_Init();
	LIT_Init();
	SRV_Init();
	GPS_Init();
	XBEE_Init();
  MIC_Init();

	Serial.println(F("Init done"));
	delay(300);
}

void loop()
{
	height=MjHeight();
  if (height>10 && time>=1000){
    time=0;
    TakePicture();          
  }
  if (height>25 && height<45){
    MikeSample();
  }else if(height<25 && height>3){
    MikeRecord();
  }
  time+=20;
  delay(20);
}
void MikeRecord(){
    int volume=MIC_GetMaximum();
  if(volume>SampleVolume){
    sousin2();
    Record2();
      }}
      
void MikeSample(){
    int tmp_volume=MIC_GetMaximum();
  if (SampleVolume<tmp_volume){
    SampleVolume=tmp_volume;
    }
    
}
void TakePicture(){
  CAM2_TakePic();
  height=MjHeight();
  Serial.print(F("Height = "));
  Serial.print(height);
  Serial.println(F(" [m]"));

  lat=GPS_GetLat();//緯度を取得
  lng=GPS_GetLng();  //経度を取得

  degree=IMU_GetDeg();

  sousin();
  Record();   

  angle+=90;
  if (angle==360){
    angle=0;
  }  
  if (angle!=270){
    //SRV_SetPosition(angle);
    servo2.position = angle;
  }  else if (angle==270){
    //SRV_SetPosition(90);
    servo2.position = 90;
  }
  //SRV_Run();
}

void sousin(){
  XBEE_Print("rec_height:");  
  XBEE_Print(height);
  XBEE_Print("rec_lat:");
  XBEE_Print(lat);
  XBEE_Print("rec_lng:");
  XBEE_Print(lng);
  XBEE_Print("rec_degree:");
  XBEE_Print(degree);
  XBEE_Print("rec_angle:");
  XBEE_Print(angle);  
}

void sousin2(){
  XBEE_Print("voice!");
  XBEE_Print("rec_height:");  
  XBEE_Print(height);
  XBEE_Print("rec_lat:");
  XBEE_Print(lat);
  XBEE_Print("rec_lng:");
  XBEE_Print(lng);
}

void Record(){
  SD_Write("rec_height:");
  SD_Write(String(height));
  SD_Write("rec_lat:");
  SD_Write(String(lat));
  SD_Write("rec_lng:");
  SD_Write(String(lng));
  SD_Write("rec_degree:");
  SD_Write(String(degree));
  SD_Write("rec_angle:");
  SD_Write(String(angle));  
}

void Record2(){
  SD_Write("voice!");
  SD_Write("rec_height:");
  SD_Write(String(height));
  SD_Write("rec_lat:");
  SD_Write(String(lat));
  SD_Write("rec_lng:");
  SD_Write(String(lng)); 
}
float MjHeight(){
  // 高度計（気圧計）・温湿度計の値を更新
  BTH_Update();
  // // 高度計（気圧計）・温湿度計の値を表示
  // BTH_Print();
  float pressure = BTH_GetPressure();

  // 気圧から高度に変換
  // まあ，ざっくり 10m 上昇すると 1hPa 下がるとしようか．
  float pressure_at_sea_level = 1013.250;
  float height = (pressure_at_sea_level - pressure) * 10;
  return height;
}
