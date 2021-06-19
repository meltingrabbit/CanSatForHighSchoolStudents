 #include "./SD.h"
#include "./GPS.h"
Sd_t sd;


// フォルダ分け or 接頭辞
// #define SD_IS_MKDIR

float GPS_GetLat();
float GPS_GetLng();
float GPS_GetHeight();


void SD_Init() {
  sd.logFileName = "GPS.txt";

  pinMode(PIN_SD_SS, OUTPUT);

  if (!SD.begin(PIN_SD_SS)) {
    Serial.println(F("SD: init failed!"));
    while (1);
  }


  strcpy(sd.DirName, "D000");
  for (uint16_t i = 0; i <= 1000; i++) {
    if (i == 1000) {
      Serial.println(F("SD: Number of Folder is MAX!"));
      while (1);
    }

    sd.DirName[1] = '0' + i/100;
    sd.DirName[2] = '0' + (i/10)%10;
    sd.DirName[3] = '0' + i%10;
    if (! SD.exists(SD_GetDirName() + sd.logFileName) ) {
      #ifdef SD_IS_MKDIR
        SD.mkdir(sd.DirName);   // フォルダわけではなく，接頭辞の場合コメントアウト！
      #else
      #endif
      break;
    }
  }


  // File logFile = SD.open(SD_GetDirName() + sd.logFileName, FILE_WRITE);
  // if (logFile) {
  //  // logFile.println("testing 1, 2, 3.");
  //  logFile.println(F("START UP!!"));
  //  // logFile.close();
  //  Serial.println(F("SD: Write done"));
  // } else {
  //  // if the file didn't open, print an error:
  //  Serial.println(F("SD: error opening file"));
  // }
  // logFile.close();

  SD_Write(F("START UP!!"));

  Serial.println(F("SD init done."));
}


void SD_Write(String str) {

  
    GPS_Update();    // GPSの値をアップデート
    GPS_Print();    // GPSの値を表示

  File logFile = SD.open(SD_GetDirName() + sd.logFileName, FILE_WRITE);

  if (logFile) {
        //logFile.println("[" + String(millis()) + "]\t" + str);
        logFile.println("[" + String(millis()) + "]\t" +"Lat=" + GPS_GetLat());
        logFile.println("[" + String(millis()) + "]\t" +"Height" + GPS_GetLng());
        logFile.println("[" + String(millis()) + "]\t" +"RecTime" + GPS_GetHeight());
    // close the file:
    logFile.close();
    Serial.println(F("SD: Write OK"));
  } else {
    // if the file didn't open, print an error:
    Serial.println(F("SD: Open Error"));
  }

  logFile.close();
  
}



String SD_GetDirName() {
  #ifdef SD_IS_MKDIR
    return (String(sd.DirName) + "/");
  #else
    return (String(sd.DirName) + "_");
  #endif
}
