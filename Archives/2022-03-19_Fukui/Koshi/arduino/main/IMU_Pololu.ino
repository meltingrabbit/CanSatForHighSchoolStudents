#include "./IMU_Pololu.h"

ImuPololu_t imu;

static uint16_t IMUP_io_timeout = 100;		// タイムアウト [ms]

// https://github.com/pololu/lsm6-arduino
#define IMUP_LSM6_FUNC_CFG_ACCESS   (0x01)

#define IMUP_LSM6_FIFO_CTRL1        (0x06)
#define IMUP_LSM6_FIFO_CTRL2        (0x07)
#define IMUP_LSM6_FIFO_CTRL3        (0x08)
#define IMUP_LSM6_FIFO_CTRL4        (0x09)
#define IMUP_LSM6_FIFO_CTRL5        (0x0A)
#define IMUP_LSM6_ORIENT_CFG_G      (0x0B)

#define IMUP_LSM6_INT1_CTRL         (0x0D)
#define IMUP_LSM6_INT2_CTRL         (0x0E)
#define IMUP_LSM6_WHO_AM_I          (0x0F)
#define IMUP_LSM6_CTRL1_XL          (0x10)
#define IMUP_LSM6_CTRL2_G           (0x11)
#define IMUP_LSM6_CTRL3_C           (0x12)
#define IMUP_LSM6_CTRL4_C           (0x13)
#define IMUP_LSM6_CTRL5_C           (0x14)
#define IMUP_LSM6_CTRL6_C           (0x15)
#define IMUP_LSM6_CTRL7_G           (0x16)
#define IMUP_LSM6_CTRL8_XL          (0x17)
#define IMUP_LSM6_CTRL9_XL          (0x18)
#define IMUP_LSM6_CTRL10_C          (0x19)

#define IMUP_LSM6_WAKE_UP_SRC       (0x1B)
#define IMUP_LSM6_TAP_SRC           (0x1C)
#define IMUP_LSM6_D6D_SRC           (0x1D)
#define IMUP_LSM6_STATUS_REG        (0x1E)

#define IMUP_LSM6_OUT_TEMP_L        (0x20)
#define IMUP_LSM6_OUT_TEMP_H        (0x21)
#define IMUP_LSM6_OUTX_L_G          (0x22)
#define IMUP_LSM6_OUTX_H_G          (0x23)
#define IMUP_LSM6_OUTY_L_G          (0x24)
#define IMUP_LSM6_OUTY_H_G          (0x25)
#define IMUP_LSM6_OUTZ_L_G          (0x26)
#define IMUP_LSM6_OUTZ_H_G          (0x27)
#define IMUP_LSM6_OUTX_L_XL         (0x28)
#define IMUP_LSM6_OUTX_H_XL         (0x29)
#define IMUP_LSM6_OUTY_L_XL         (0x2A)
#define IMUP_LSM6_OUTY_H_XL         (0x2B)
#define IMUP_LSM6_OUTZ_L_XL         (0x2C)
#define IMUP_LSM6_OUTZ_H_XL         (0x2D)

#define IMUP_LSM6_FIFO_STATUS1      (0x3A)
#define IMUP_LSM6_FIFO_STATUS2      (0x3B)
#define IMUP_LSM6_FIFO_STATUS3      (0x3C)
#define IMUP_LSM6_FIFO_STATUS4      (0x3D)
#define IMUP_LSM6_FIFO_DATA_OUT_L   (0x3E)
#define IMUP_LSM6_FIFO_DATA_OUT_H   (0x3F)
#define IMUP_LSM6_TIMESTAMP0_REG    (0x40)
#define IMUP_LSM6_TIMESTAMP1_REG    (0x41)
#define IMUP_LSM6_TIMESTAMP2_REG    (0x42)

#define IMUP_LSM6_STEP_TIMESTAMP_L  (0x49)
#define IMUP_LSM6_STEP_TIMESTAMP_H  (0x4A)
#define IMUP_LSM6_STEP_COUNTER_L    (0x4B)
#define IMUP_LSM6_STEP_COUNTER_H    (0x4C)

#define IMUP_LSM6_FUNC_SRC          (0x53)

#define IMUP_LSM6_TAP_CFG           (0x58)
#define IMUP_LSM6_TAP_THS_6D        (0x59)
#define IMUP_LSM6_INT_DUR2          (0x5A)
#define IMUP_LSM6_WAKE_UP_THS       (0x5B)
#define IMUP_LSM6_WAKE_UP_DUR       (0x5C)
#define IMUP_LSM6_FREE_FALL         (0x5D)
#define IMUP_LSM6_MD1_CFG           (0x5E)
#define IMUP_LSM6_MD2_CFG           (0x5F)


// https://github.com/pololu/LIS3MDL-arduino

#define IMUP_LIS3MDL_WHO_AM_I    (0x0F)

#define IMUP_LIS3MDL_CTRL_REG1   (0x20)
#define IMUP_LIS3MDL_CTRL_REG2   (0x21)
#define IMUP_LIS3MDL_CTRL_REG3   (0x22)
#define IMUP_LIS3MDL_CTRL_REG4   (0x23)
#define IMUP_LIS3MDL_CTRL_REG5   (0x24)

#define IMUP_LIS3MDL_STATUS_REG  (0x27)
#define IMUP_LIS3MDL_OUT_X_L     (0x28)
#define IMUP_LIS3MDL_OUT_X_H     (0x29)
#define IMUP_LIS3MDL_OUT_Y_L     (0x2A)
#define IMUP_LIS3MDL_OUT_Y_H     (0x2B)
#define IMUP_LIS3MDL_OUT_Z_L     (0x2C)
#define IMUP_LIS3MDL_OUT_Z_H     (0x2D)
#define IMUP_LIS3MDL_TEMP_OUT_L  (0x2E)
#define IMUP_LIS3MDL_TEMP_OUT_H  (0x2F)
#define IMUP_LIS3MDL_INT_CFG     (0x30)
#define IMUP_LIS3MDL_INT_SRC     (0x31)
#define IMUP_LIS3MDL_INT_THS_L   (0x32)
#define IMUP_LIS3MDL_INT_THS_H   (0x33)


static void IMUP_LSM6_WriteReg_(uint8_t reg, uint8_t value);
static void IMUP_LSM6_SetDefault_();

static void IMUP_LIS3MDL_WriteReg_(uint8_t reg, uint8_t value);
static void IMUP_LIS3MDL_SetDefault_();

static void IMUP_ClearWireReadBuffer_();

boolean isFirstTime = true;

void IMUP_Init() {
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

  // For fall detection
	imu.allAccl = 1.0;
	imu.prevAllAccl = 1.0;
	imu.fallen = false;


	// Accl
	IMUP_LSM6_SetDefault_();
	IMUP_LSM6_WriteReg_(IMUP_LSM6_CTRL1_XL, 0x3C);		// 52 Hz, 8 g full scale
	// Mag
	IMUP_LIS3MDL_SetDefault_();
	// Gyro
	IMUP_LSM6_WriteReg_(IMUP_LSM6_CTRL2_G, 0x4C);		// 104 Hz, 2000 dps full scale

	Serial.println(F("IMU Pololu MinIMU-9 v5 init done"));
}


void IMUP_UpdateAll() {
	IMUP_UpdateAcc();
	IMUP_UpdateGyr();
	IMUP_UpdateMag();
  IMUP_UpdateAllAccl();

  isFirstTime = false;
}


void IMUP_UpdateAcc() {
	IMUP_ClearWireReadBuffer_();
	Wire.beginTransmission(IMUP_LSM6_ADDR);
	// automatic increment of register address is enabled by default (IF_INC in CTRL3_C)
	Wire.write(IMUP_LSM6_OUTX_L_XL);
	Wire.endTransmission();
	Wire.requestFrom(IMUP_LSM6_ADDR, (uint8_t)6);

	unsigned long millis_start = millis();
	while (Wire.available() < 6) {
		if (IMUP_io_timeout > 0 && (millis() - millis_start) > IMUP_io_timeout)
		{
			IMUP_ClearWireReadBuffer_();
			return;
		}
	}

	uint8_t xla = Wire.read();
	uint8_t xha = Wire.read();
	uint8_t yla = Wire.read();
	uint8_t yha = Wire.read();
	uint8_t zla = Wire.read();
	uint8_t zha = Wire.read();

	// combine high and low bytes
	int16_t x = (int16_t)(xha << 8 | xla);
	int16_t y = (int16_t)(yha << 8 | yla);
	int16_t z = (int16_t)(zha << 8 | zla);

	// accelerometer: 8 g sensitivity
	// 3.9 mg/digit; 1 g = 256
	// shift right 4 bits to use 12-bit representation (1 g = 256)
	imu.xAccl = (x >> 4) / 256.0;
	imu.yAccl = (y >> 4) / 256.0;
	imu.zAccl = (z >> 4) / 256.0;
}


void IMUP_UpdateGyr() {
	IMUP_ClearWireReadBuffer_();
	Wire.beginTransmission(IMUP_LSM6_ADDR);
	// automatic increment of register address is enabled by default (IF_INC in CTRL3_C)
	Wire.write(IMUP_LSM6_OUTX_L_G);
	Wire.endTransmission();
	Wire.requestFrom(IMUP_LSM6_ADDR, (uint8_t)6);

	unsigned long millis_start = millis();
	while (Wire.available() < 6) {
		if (IMUP_io_timeout > 0 && (millis() - millis_start) > IMUP_io_timeout)
		{
			IMUP_ClearWireReadBuffer_();
			return;
		}
	}

	uint8_t xla = Wire.read();
	uint8_t xha = Wire.read();
	uint8_t yla = Wire.read();
	uint8_t yha = Wire.read();
	uint8_t zla = Wire.read();
	uint8_t zha = Wire.read();

	// combine high and low bytes
	int16_t x = (int16_t)(xha << 8 | xla);
	int16_t y = (int16_t)(yha << 8 | yla);
	int16_t z = (int16_t)(zha << 8 | zla);

	// gyro: 2000 dps full scale
	// 70 mdps/digit; 1 dps = 0.07
	// To Rad: 0.01745329252 = pi / 180
	imu.xGyro = x * 0.01745329252 * 0.07; //  Full scale = +/- 125 degree/s
	imu.yGyro = y * 0.01745329252 * 0.07; //  Full scale = +/- 125 degree/s
	imu.zGyro = z * 0.01745329252 * 0.07; //  Full scale = +/- 125 degree/s
	imu.xGyro = x * 0.07; //  Full scale = +/- 125 degree/s
	imu.yGyro = y * 0.07; //  Full scale = +/- 125 degree/s
	imu.zGyro = z * 0.07; //  Full scale = +/- 125 degree/s
}


void IMUP_UpdateMag() {
	IMUP_ClearWireReadBuffer_();
	Wire.beginTransmission(IMUP_LIS3MDL_ADDR);
	// assert MSB to enable subaddress updating
	Wire.write(IMUP_LIS3MDL_OUT_X_L | 0x80);
	Wire.endTransmission();
	Wire.requestFrom(IMUP_LIS3MDL_ADDR, (uint8_t)6);

	unsigned long millis_start = millis();
	while (Wire.available() < 6) {
		if (IMUP_io_timeout > 0 && (millis() - millis_start) > IMUP_io_timeout)
		{
			IMUP_ClearWireReadBuffer_();
			return;
		}
	}

	uint8_t xlm = Wire.read();
	uint8_t xhm = Wire.read();
	uint8_t ylm = Wire.read();
	uint8_t yhm = Wire.read();
	uint8_t zlm = Wire.read();
	uint8_t zhm = Wire.read();

	// combine high and low bytes
	imu.xMag = (int16_t)(xhm << 8 | xlm);
	imu.yMag = (int16_t)(yhm << 8 | ylm);
	imu.zMag = (int16_t)(zhm << 8 | zlm);
}


void IMUP_PrintAcc() {
	Serial.print(F("Acc= "));
	Serial.print(imu.xAccl);
	Serial.print(F(","));
	Serial.print(imu.yAccl);
	Serial.print(F(","));
	Serial.print(imu.zAccl);
	Serial.println(F(""));
}


void IMUP_PrintGyr() {
	Serial.print(F("Gyr= "));
	Serial.print(imu.xGyro);
	Serial.print(F(","));
	Serial.print(imu.yGyro);
	Serial.print(F(","));
	Serial.print(imu.zGyro);
	Serial.println(F(""));
}


void IMUP_PrintMag() {
	Serial.print(F("Mag= "));
	Serial.print(imu.xMag);
	Serial.print(F(","));
	Serial.print(imu.yMag);
	Serial.print(F(","));
	Serial.print(imu.zMag);
	Serial.println(F(""));
}


float IMUP_GetAccX() {
	return imu.xAccl;
}
float IMUP_GetAccY() {
	return imu.yAccl;
}
float IMUP_GetAccZ() {
	return imu.zAccl;
}
float IMUP_GetGyrX() {
	return imu.xGyro;
}
float IMUP_GetGyrY() {
	return imu.yGyro;
}
float IMUP_GetGyrZ() {
	return imu.zGyro;
}
int IMUP_GetMagX() {
	return imu.xMag;
}
int IMUP_GetMagY() {
	return imu.yMag;
}
int IMUP_GetMagZ() {
	return imu.zMag;
}


static void IMUP_LSM6_WriteReg_(uint8_t reg, uint8_t value) {
	Wire.beginTransmission(IMUP_LSM6_ADDR);
	Wire.write(reg);
	Wire.write(value);
	Wire.endTransmission();
	delay(100);
}


/*
Enables the LSM6's accelerometer and gyro. Also:
- Sets sensor full scales (gain) to default power-on values, which are
  +/- 2 g for accelerometer and 245 dps for gyro
- Selects 1.66 kHz (high performance) ODR (output data rate) for accelerometer
  and 1.66 kHz (high performance) ODR for gyro. (These are the ODR settings for
  which the electrical characteristics are specified in the datasheet.)
- Enables automatic increment of register address during multiple byte access
Note that this function will also reset other settings controlled by
the registers it writes to.
*/
// https://github.com/pololu/lsm6-arduino/blob/4133a5b81d0c1da82a0e881538acb1d88801e2fc/LSM6.cpp#L98
static void IMUP_LSM6_SetDefault_() {
	// Accelerometer

	// 0x80 = 0b10000000
	// ODR = 1000 (1.66 kHz (high performance)); FS_XL = 00 (+/-2 g full scale)
	IMUP_LSM6_WriteReg_(IMUP_LSM6_CTRL1_XL, 0x80);

	// Gyro

	// 0x80 = 0b010000000
	// ODR = 1000 (1.66 kHz (high performance)); FS_XL = 00 (245 dps)
	IMUP_LSM6_WriteReg_(IMUP_LSM6_CTRL2_G, 0x80);

	// Common

	// 0x04 = 0b00000100
	// IF_INC = 1 (automatically increment register address)
	IMUP_LSM6_WriteReg_(IMUP_LSM6_CTRL3_C, 0x04);
}


static void IMUP_LIS3MDL_WriteReg_(uint8_t reg, uint8_t value) {
	Wire.beginTransmission(IMUP_LIS3MDL_ADDR);
	Wire.write(reg);
	Wire.write(value);
	Wire.endTransmission();
	delay(100);
}


/*
Enables the LIS3MDL's magnetometer. Also:
- Selects ultra-high-performance mode for all axes
- Sets ODR (output data rate) to default power-on value of 10 Hz
- Sets magnetometer full scale (gain) to default power-on value of +/- 4 gauss
- Enables continuous conversion mode
Note that this function will also reset other settings controlled by
the registers it writes to.
*/
// https://github.com/pololu/lis3mdl-arduino/blob/28ad6c1ed643fd67d65258ccfe49d41bec4829fa/LIS3MDL.cpp#L96
static void IMUP_LIS3MDL_SetDefault_() {
	// 0x70 = 0b01110000
	// OM = 11 (ultra-high-performance mode for X and Y); DO = 100 (10 Hz ODR)
	IMUP_LIS3MDL_WriteReg_(IMUP_LIS3MDL_CTRL_REG1, 0x70);

	// 0x00 = 0b00000000
	// FS = 00 (+/- 4 gauss full scale)
	IMUP_LIS3MDL_WriteReg_(IMUP_LIS3MDL_CTRL_REG2, 0x00);

	// 0x00 = 0b00000000
	// MD = 00 (continuous-conversion mode)
	IMUP_LIS3MDL_WriteReg_(IMUP_LIS3MDL_CTRL_REG3, 0x00);

	// 0x0C = 0b00001100
	// OMZ = 11 (ultra-high-performance mode for Z)
	IMUP_LIS3MDL_WriteReg_(IMUP_LIS3MDL_CTRL_REG4, 0x0C);
}


static void IMUP_ClearWireReadBuffer_() {
	while (Wire.available()) {
		char c = Wire.read();
		(void)c;
	}
}


boolean IMUP_GetFallDetected() {
	return imu.fallen;
}

// For fall detection
static void IMUP_UpdateAllAccl() {
	imu.prevAllAccl = imu.allAccl;
	imu.allAccl = imu.xAccl + imu.yAccl + imu.zAccl;

  if (isFirstTime) {
    return;
  }

	imu.fallen = imu.fallen || (imu.prevAllAccl + 2.0) < imu.allAccl;
}
