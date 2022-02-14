#include "./IMU.h"

Imu_t imu;

void IMU_Init() {
	// Wire.begin();はされている前提！

	imu.xAccl = 0.0;
	imu.yAccl = 0.0;
	imu.zAccl = 0.0;
	imu.xGyro = 0.0;
	imu.yGyro = 0.0;
	imu.zGyro = 0.0;
	imu.xMag  = 0;
	imu.yMag  = 0;
	imu.zMag  = 0;

	//------------------------------------------------------------//
	Wire.beginTransmission(IMU_ADDR_ACCL);
	Wire.write(0x0F); // Select PMU_Range register
	Wire.write(0x03);   // Range = +/- 2g
	Wire.endTransmission();
	delay(100);
	//------------------------------------------------------------//
	Wire.beginTransmission(IMU_ADDR_ACCL);
	Wire.write(0x10);  // Select PMU_BW register
	Wire.write(0x08);  // Bandwidth = 7.81 Hz
	Wire.endTransmission();
	delay(100);
	//------------------------------------------------------------//
	Wire.beginTransmission(IMU_ADDR_ACCL);
	Wire.write(0x11);  // Select PMU_LPW register
	Wire.write(0x00);  // Normal mode, Sleep duration = 0.5ms
	Wire.endTransmission();
	delay(100);
	//------------------------------------------------------------//
	Wire.beginTransmission(IMU_ADDR_GYRO);
	Wire.write(0x0F);  // Select Range register
	Wire.write(0x04);  // Full scale = +/- 125 degree/s
	Wire.endTransmission();
	delay(100);
	//------------------------------------------------------------//
	Wire.beginTransmission(IMU_ADDR_GYRO);
	Wire.write(0x10);  // Select Bandwidth register
	Wire.write(0x07);  // ODR = 100 Hz
	Wire.endTransmission();
	delay(100);
	//------------------------------------------------------------//
	Wire.beginTransmission(IMU_ADDR_GYRO);
	Wire.write(0x11);  // Select LPM1 register
	Wire.write(0x00);  // Normal mode, Sleep duration = 2ms
	Wire.endTransmission();
	delay(100);
	//------------------------------------------------------------//
	Wire.beginTransmission(IMU_ADDR_MAG);
	Wire.write(0x4B);  // Select Mag register
	Wire.write(0x83);  // Soft reset
	Wire.endTransmission();
	delay(100);
	//------------------------------------------------------------//
	Wire.beginTransmission(IMU_ADDR_MAG);
	Wire.write(0x4B);  // Select Mag register
	Wire.write(0x01);  // Soft reset
	Wire.endTransmission();
	delay(100);
	//------------------------------------------------------------//
	Wire.beginTransmission(IMU_ADDR_MAG);
	Wire.write(0x4C);  // Select Mag register
	Wire.write(0x00);  // Normal Mode, ODR = 10 Hz
	Wire.endTransmission();
	//------------------------------------------------------------//
	Wire.beginTransmission(IMU_ADDR_MAG);
	Wire.write(0x4E);  // Select Mag register
	Wire.write(0x84);  // X, Y, Z-Axis enabled
	Wire.endTransmission();
	//------------------------------------------------------------//
	Wire.beginTransmission(IMU_ADDR_MAG);
	Wire.write(0x51);  // Select Mag register
	Wire.write(0x04);  // No. of Repetitions for X-Y Axis = 9
	Wire.endTransmission();
	//------------------------------------------------------------//
	Wire.beginTransmission(IMU_ADDR_MAG);
	Wire.write(0x52);  // Select Mag register
	Wire.write(0x16);  // No. of Repetitions for Z-Axis = 15
	Wire.endTransmission();

	Serial.println(F("IMU init done"));
}


void IMU_UpdateAll() {
	IMU_UpdateAcc();
	IMU_UpdateGyr();
	IMU_UpdateMag();
}


void IMU_UpdateAcc() {
	// int data[6];
	uint8_t data[6];
	for (uint8_t i = 0; i < 6; i++)
	{
		Wire.beginTransmission(IMU_ADDR_ACCL);
		Wire.write((2 + i));// Select data register
		Wire.endTransmission();
		Wire.requestFrom(IMU_ADDR_ACCL, 1);// Request 1 byte of data
		// Read 6 bytes of data
		// imu.xAccl lsb, imu.xAccl msb, imu.yAccl lsb, imu.yAccl msb, imu.zAccl lsb, imu.zAccl msb
		if (Wire.available() == 1)
			data[i] = Wire.read();
	}
	// Convert the data to 12-bits
	imu.xAccl = ((data[1] * 256) + (data[0] & 0xF0)) / 16;
	if (imu.xAccl > 2047)  imu.xAccl -= 4096;
	imu.yAccl = ((data[3] * 256) + (data[2] & 0xF0)) / 16;
	if (imu.yAccl > 2047)  imu.yAccl -= 4096;
	imu.zAccl = ((data[5] * 256) + (data[4] & 0xF0)) / 16;
	if (imu.zAccl > 2047)  imu.zAccl -= 4096;
	imu.xAccl = imu.xAccl * 0.0098; // renge +-2g
	imu.yAccl = imu.yAccl * 0.0098; // renge +-2g
	imu.zAccl = imu.zAccl * 0.0098; // renge +-2g
}


void IMU_UpdateGyr() {
	// int data[6];
	uint8_t data[6];
	for (uint8_t i = 0; i < 6; i++)
	{
		Wire.beginTransmission(IMU_ADDR_GYRO);
		Wire.write((2 + i));    // Select data register
		Wire.endTransmission();
		Wire.requestFrom(IMU_ADDR_GYRO, 1);    // Request 1 byte of data
		// Read 6 bytes of data
		// imu.xGyro lsb, imu.xGyro msb, imu.yGyro lsb, imu.yGyro msb, imu.zGyro lsb, imu.zGyro msb
		if (Wire.available() == 1)
			data[i] = Wire.read();
	}
	// Convert the data
	imu.xGyro = (data[1] * 256) + data[0];
	if (imu.xGyro > 32767)  imu.xGyro -= 65536;
	imu.yGyro = (data[3] * 256) + data[2];
	if (imu.yGyro > 32767)  imu.yGyro -= 65536;
	imu.zGyro = (data[5] * 256) + data[4];
	if (imu.zGyro > 32767)  imu.zGyro -= 65536;

	imu.xGyro = imu.xGyro * 0.0038; //  Full scale = +/- 125 degree/s
	imu.yGyro = imu.yGyro * 0.0038; //  Full scale = +/- 125 degree/s
	imu.zGyro = imu.zGyro * 0.0038; //  Full scale = +/- 125 degree/s
}


void IMU_UpdateMag() {
	// int data[8];
	uint8_t data[8];
	for (uint8_t i = 0; i < 8; i++)
	{
		Wire.beginTransmission(IMU_ADDR_MAG);
		Wire.write((0x42 + i));    // Select data register
		Wire.endTransmission();
		Wire.requestFrom(IMU_ADDR_MAG, 1);    // Request 1 byte of data
		// Read 6 bytes of data
		// imu.xMag lsb, imu.xMag msb, imu.yMag lsb, imu.yMag msb, imu.zMag lsb, imu.zMag msb
		if (Wire.available() == 1)
			data[i] = Wire.read();
	}
	// Convert the data
	imu.xMag = ((data[1] <<8) | (data[0]>>3));
	if (imu.xMag > 4095)  imu.xMag -= 8192;
	imu.yMag = ((data[3] <<8) | (data[2]>>3));
	if (imu.yMag > 4095)  imu.yMag -= 8192;
	imu.zMag = ((data[5] <<8) | (data[4]>>3));
	if (imu.zMag > 16383)  imu.zMag -= 32768;
}


void IMU_PrintAcc() {
	Serial.print(F("Acc= "));
	Serial.print(imu.xAccl);
	Serial.print(F(","));
	Serial.print(imu.yAccl);
	Serial.print(F(","));
	Serial.print(imu.zAccl);
	Serial.println(F(""));
}


void IMU_PrintGyr() {
	Serial.print(F("Gyr= "));
	Serial.print(imu.xGyro);
	Serial.print(F(","));
	Serial.print(imu.yGyro);
	Serial.print(F(","));
	Serial.print(imu.zGyro);
	Serial.println(F(""));
}


void IMU_PrintMag() {
	Serial.print(F("Mag= "));
	Serial.print(imu.xMag);
	Serial.print(F(","));
	Serial.print(imu.yMag);
	Serial.print(F(","));
	Serial.print(imu.zMag);
	Serial.println(F(""));
}


float IMU_GetAccX() {
	return imu.xAccl;
}
float IMU_GetAccY() {
	return imu.yAccl;
}
float IMU_GetAccZ() {
	return imu.zAccl;
}
float IMU_GetGyrX() {
	return imu.xGyro;
}
float IMU_GetGyrY() {
	return imu.yGyro;
}
float IMU_GetGyrZ() {
	return imu.zGyro;
}
int IMU_GetMagX() {
	return imu.xMag;
}
int IMU_GetMagY() {
	return imu.yMag;
}
int IMU_GetMagZ() {
	return imu.zMag;
}
