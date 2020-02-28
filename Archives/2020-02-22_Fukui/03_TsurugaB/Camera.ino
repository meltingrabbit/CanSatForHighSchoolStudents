#include "./Camera.h"
#include "./SD.h"

Camera_t camera;

// SoftwareSerial と Adafruit_VC0706 は初期値なしの初期化ができないので，仕方なくstructにはいれない．
SoftwareSerial CamSerial = SoftwareSerial(PIN_CAM_TX, PIN_CAM_RX);
Adafruit_VC0706 cam = Adafruit_VC0706(&CamSerial);


void CAM_Init() {
	// Try to locate the camera
	if (cam.begin()) {
		Serial.println(F("Cam Found"));
	} else {
		Serial.println(F("No cam!!"));
		return;
	}
	// // Print out the camera version information (optional)
	// char *reply = cam.getVersion();
	// if (reply == 0) {
	// 	Serial.println(F("Failed to get version"));
	// } else {
	// 	Serial.println(F("-----------------"));
	// 	Serial.print(reply);
	// 	Serial.println(F("-----------------"));
	// }

	cam.setImageSize(VC0706_640x480);        // biggest
	// cam.setImageSize(VC0706_320x240);        // medium
	// cam.setImageSize(VC0706_160x120);        // small


	// バッファークリアの意味も兼ねて一発撮る
	// 壊れた画像になるので確認．
	CAM_TakePic();
}


void CAM_TakePic() {
	SD_Write(F("TakePic"));

	// You can read the size back from the camera (optional, but maybe useful?)
	// uint8_t imgsize = cam.getImageSize();
	// Serial.print("Image size: ");
	// if (imgsize == VC0706_640x480) Serial.println("640x480");
	// if (imgsize == VC0706_320x240) Serial.println("320x240");
	// if (imgsize == VC0706_160x120) Serial.println("160x120");

	if (! cam.takePicture()) {
		Serial.println(F("Snap NG"));
		// return;
	} else {
		Serial.println(F("Snap OK"));
	}

	// Create an image with the name IMGxx.JPG
	char filename[12];
	strcpy(filename, "000.JPG");
	for (uint16_t i = 0; i < 1000; i++) {
		filename[0] = '0' + i/100;
		filename[1] = '0' + (i/10)%10;
		filename[2] = '0' + i%10;
		// create if does not exist, do not open existing, write, sync after write
		if ( ! SD.exists(SD_GetDirName() + String(filename)) ) {
			break;
		}
	}

	SD_Write("picname:" + SD_GetDirName() + String(filename));
	Serial.println(SD_GetDirName() + String(filename));

	// Open the file for writing
	File imgFile = SD.open(SD_GetDirName() + String(filename), FILE_WRITE);

	// Get the size of the image (frame) taken
	uint16_t jpglen = cam.frameLength();
	Serial.print(F("Storing "));
	Serial.print(jpglen, DEC);
	Serial.print(F(" byte."));

	// int32_t time = millis();
	// pinMode(8, OUTPUT);
	// Read all the data up to # bytes!
	byte wCount = 0; // For counting # of writes
	while (jpglen > 0) {
		// read 32 bytes at a time;
		uint8_t *buffer;
		uint8_t bytesToRead = min(32, jpglen); // change 32 to 64 for a speedup but may not work with all setups!
		buffer = cam.readPicture(bytesToRead);
		imgFile.write(buffer, bytesToRead);
		if(++wCount >= 64) { // Every 2K, give a little feedback so it doesn't appear locked up
			Serial.print('.');
			wCount = 0;
		}
		//Serial.print("Read ");  Serial.print(bytesToRead, DEC); Serial.println(" bytes");
		jpglen -= bytesToRead;
	}
	imgFile.close();

	// time = millis() - time;
	Serial.println(F("done!"));
	// Serial.print(time);
	// Serial.println(F(" ms elapsed"));
}
