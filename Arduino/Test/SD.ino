#include "./SD.h"

Sd_t sd;



void SD_Init() {
	sd.logFileName = "log.txt";
	// sd.DirName     = "CS0000";

	pinMode(PIN_SD_SS, OUTPUT);

	if (!SD.begin(PIN_SD_SS)) {
		Serial.println(F("SD: initialization failed!"));
		while (1);
	}


	strcpy(sd.DirName, "CS0000");
	for (int i = 0; i <= 1000; i++) {
		if (i == 1000) {
			Serial.println(F("SD: Number of Folder is MAX!"));
			while (1);
		}

		sd.DirName[3] = '0' + i/100;
		sd.DirName[4] = '0' + (i/10)%10;
		sd.DirName[5] = '0' + i%10;
		if (! SD.exists(SD_GetDirName() + "/" + sd.logFileName) ) {
			SD.mkdir(sd.DirName);
			break;
		}
	}


	sd.logFile = SD.open(SD_GetDirName() + "/" + sd.logFileName, FILE_WRITE);
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
	sd.logFile = SD.open(SD_GetDirName() + "/" + sd.logFileName, FILE_WRITE);

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


String SD_GetDirName() {
	return String(sd.DirName);
}
