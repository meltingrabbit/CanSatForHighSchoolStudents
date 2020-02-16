#include "./SD.h"

Sd_t sd;



void SD_Init() {
	sd.logFileName = "log.txt";

	if (!SD.begin(PIN_SD_SS)) {
		Serial.println(F("SD initialization failed!"));
		while (1);
	}

	sd.logFile = SD.open(sd.logFileName, FILE_WRITE);
	if (sd.logFile) {
		// sd.logFile.println("testing 1, 2, 3.");
		sd.logFile.println("START UP!!");
		// sd.logFile.close();
		Serial.println(F("SD: Write done"));
	} else {
		// if the file didn't open, print an error:
		Serial.println(F("SD: error opening file"));
	}

	sd.logFile.close();
	Serial.println(F("SD initialization done."));
}



void SD_Write(String str) {
	sd.logFile = SD.open(sd.logFileName, FILE_WRITE);

	if (sd.logFile) {
		sd.logFile.println("[" + String(millis()) + "]\t" + str);
		// close the file:
		sd.logFile.close();
		Serial.println(F("SD: Write done"));
	} else {
		// if the file didn't open, print an error:
		Serial.println(F("SD: error opening file"));
	}


	sd.logFile.close();
}



