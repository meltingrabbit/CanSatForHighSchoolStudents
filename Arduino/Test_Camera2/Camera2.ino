#include "./Camera2.h"
#include "./SD.h"
#include <Wire.h>
#include <SPI.h>
#include "./ArduCAM.h"


Camera2_t camera2;

// 初期値なしの初期化ができないので，仕方なくstructにはいれない．
ArduCAM myCAM(OV2640, PIN_CAM2_SS);


// 公式サイト情報
//You can change the FRAMES_NUM count to change the number of the picture.
//IF the FRAMES_NUM is 0X00, take one photos
//IF the FRAMES_NUM is 0X01, take two photos
//IF the FRAMES_NUM is 0X02, take three photos
//IF the FRAMES_NUM is 0X03, take four photos
//IF the FRAMES_NUM is 0X04, take five photos
//IF the FRAMES_NUM is 0X05, take six photos
//IF the FRAMES_NUM is 0X06, take seven photos
//IF the FRAMES_NUM is 0XFF, continue shooting until the FIFO is full
#define   FRAMES_NUM    0x00
// 現状，1枚を仮定する．SD保存で上書きが発生しないようにするロジックなど，1枚を想定してコーディングしてある．
// → 複数枚対応した


#define  FINENAME_MAX_LEN 12


static uint8_t CAM2_save_to_sd_(ArduCAM myCAM);
static void    CAM2_get_filename_(char filename[FINENAME_MAX_LEN]);



void CAM2_Init() {
	// これはこのライブラリ外でされている前提
	// Wire.begin();

	pinMode(PIN_CAM2_SS, OUTPUT);
	digitalWrite(PIN_CAM2_SS, HIGH);

	SPI.begin();		// FIXME: これも本当はライブラリ外でやりたいが，今回はSPIが干渉しないので，ここで

	// Reset the CPLD
	myCAM.write_reg(0x07, 0x80);
	delay(100);
	myCAM.write_reg(0x07, 0x00);
	delay(100);

	while (1) {
		// Check if the ArduCAM SPI bus is OK
		myCAM.write_reg(ARDUCHIP_TEST1, 0x55);
		uint8_t temp = myCAM.read_reg(ARDUCHIP_TEST1);
		if (temp != 0x55)
		{
			Serial.println(F("CAMERA: SPI interface Error!"));
			delay(1000); continue;
		} else {
			Serial.println(F("CAMERA: SPI interface OK.")); break;
		}
	}

	while (1) {
		// Check if the camera module type is OV2640
		uint8_t vid, pid;
		myCAM.wrSensorReg8_8(0xff, 0x01);
		myCAM.rdSensorReg8_8(OV2640_CHIPID_HIGH, &vid);
		myCAM.rdSensorReg8_8(OV2640_CHIPID_LOW, &pid);
		if ((vid != 0x26 ) && (( pid != 0x41 ) || ( pid != 0x42 ))) {
			Serial.println(F("CAMERA: ACK CMD Can't find OV2640 module!"));
			delay(1000); continue;
		}
		else {
			Serial.println(F("CAMERA: ACK CMD OV2640 detected.")); break;
		}
	}

	// Change to JPEG capture mode and initialize the OV5640 module
	myCAM.set_format(JPEG);
	myCAM.InitCAM();
	myCAM.clear_fifo_flag();
	myCAM.write_reg(ARDUCHIP_FRAMES, FRAMES_NUM);

	myCAM.CS_HIGH();		// これしておかないとSDにかけない．

	Serial.println(F("Camera init done."));
}


void CAM2_TakePic() {
	myCAM.CS_HIGH();
	int total_time = 0;

	SD_Write(F("TakePic"));

	myCAM.CS_LOW();
	myCAM.flush_fifo();
	myCAM.clear_fifo_flag();
	myCAM.OV2640_set_JPEG_size(OV2640_1600x1200);		// FIXME: ここも要検討

	myCAM.start_capture();
	Serial.println(F("CAMERA: Start Capture"));

	total_time = millis();

	while ( !myCAM.get_bit(ARDUCHIP_TRIG, CAP_DONE_MASK));

	Serial.println(F("CAMERA: Capture Done."));
	total_time = millis() - total_time;
	Serial.print(total_time);
	Serial.println(F(" ms elapsed."));

	total_time = millis();

	CAM2_save_to_sd_(myCAM);

	total_time = millis() - total_time;
	Serial.print(total_time);
	Serial.println(F(" ms elapsed."));

	// Clear the capture done flag
	myCAM.clear_fifo_flag();
}


static uint8_t CAM2_save_to_sd_(ArduCAM myCAM) {
	// static int k = 0;
	// char str[16];

	byte buf[256];
	char filename[FINENAME_MAX_LEN];

	uint32_t length = myCAM.read_fifo_length();
	myCAM.CS_HIGH();
	Serial.print(F("CAMERA: The fifo length is :"));
	Serial.println(length, DEC);

	if (length >= MAX_FIFO_SIZE) {		// 8M
		Serial.println("CAMERA: Over size.");
		Serial.println("CAMERA: Failed to take pic");
		SD_Write(F("Failed to TakePic of OVER SIZE ERR"));
		return 0;
	}
	if (length == 0 ) {		// 0 kb
		Serial.println(F("CAMERA: Size is 0."));
		Serial.println("CAMERA: Failed to take pic");
		SD_Write(F("Failed to TakePic of SIZE 0 ERR"));
		return 0;
	}

	myCAM.CS_LOW();
	myCAM.set_fifo_burst();  // Set fifo burst mode

	int i = 0;
	bool is_header = false;
	File outFile;
	uint8_t temp = 0, temp_last = 0;
	while ( length-- ) {
		temp_last = temp;
		temp =  SPI.transfer(0x00);
		// Read JPEG data from FIFO
		if ( (temp == 0xD9) && (temp_last == 0xFF) ) {	// If find the end ,break while,
			buf[i++] = temp;  // save the last  0XD9
			// Write the remain bytes in the buffer
			myCAM.CS_HIGH();
			outFile.write(buf, i);
			// Close the file
			outFile.close();
			Serial.println(F("CAMERA: Save OK"));
			is_header = false;
			myCAM.CS_LOW();
			myCAM.set_fifo_burst();
			i = 0;
		}
		if (is_header == true) {
			// Write image data to buffer if not full
			if (i < 256) {
				buf[i++] = temp;
			} else {
				// Write 256 bytes image data to file
				myCAM.CS_HIGH();
				outFile.write(buf, 256);
				i = 0;
				buf[i++] = temp;
				myCAM.CS_LOW();
				myCAM.set_fifo_burst();
			}
		}
		else if ((temp == 0xD8) & (temp_last == 0xFF)) {
			Serial.println("CAMERA: HEADER FOUND!!!");
			is_header = true;

			myCAM.CS_HIGH();
			CAM2_get_filename_(filename);
			SD_Write("picname:" + SD_GetDirName() + String(filename));
			Serial.print(F("CAMERA: picname: "));
			Serial.println(SD_GetDirName() + String(filename));

			// k = k + 1;
			// itoa(k, str, 10);
			// strcat(str, ".jpg");
			// Open the new file
			// outFile = SD.open(str, O_WRITE | O_CREAT | O_TRUNC);
			// outFile = SD.open(SD_GetDirName() + String(filename), FILE_WRITE);
			outFile = SD.open(SD_GetDirName() + String(filename), O_WRITE | O_CREAT | O_TRUNC);
			// outFile = SD.open(String(filename), O_WRITE | O_CREAT | O_TRUNC);
			if (! outFile)
			{
				Serial.println(F("SD: File open failed"));
				// while (1);
			}
			myCAM.CS_LOW();
			myCAM.set_fifo_burst();
			buf[i++] = temp_last;
			buf[i++] = temp;
		}
	}

	myCAM.CS_HIGH();
	return 1;
}


static void CAM2_get_filename_(char filename[FINENAME_MAX_LEN]) {
	myCAM.CS_HIGH();
	strcpy(filename, "000.JPG");
	for (uint16_t i = 0; i < 1000; i++) {
		filename[0] = '0' + i/100;
		filename[1] = '0' + (i/10)%10;
		filename[2] = '0' + i%10;
		if ( ! SD.exists(SD_GetDirName() + String(filename)) ) {
			break;
		}
	}
	// FIXME: 上限枚数に達したときの挙動
}