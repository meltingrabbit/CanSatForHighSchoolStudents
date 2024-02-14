#include "./Barometer.h"


Barometer_t barometer;


float readTemperature();
float readPressure();

void readCoefficients(void);
void write8(byte reg, byte value);
uint8_t read8(byte reg);
uint16_t read16(byte reg);
uint32_t read24(byte reg);
// int16_t readS16(byte reg);
uint16_t read16_LE(byte reg);
int16_t readS16_LE(byte reg);
void setSampling(sensor_mode mode = MODE_NORMAL,
								 sensor_sampling tempSampling = SAMPLING_X16,
								 sensor_sampling pressSampling = SAMPLING_X16,
								 sensor_filter filter = FILTER_OFF,
								 standby_duration duration = STANDBY_MS_1);




void BMP_Init() {
	// Wire.begin();はされている前提！

	barometer.pressure = 0.0;
	barometer.temperature = 0.0;


	uint8_t chipid = BMP280_CHIPID;

	if (read8(BMP280_REGISTER_CHIPID) != chipid) {
		Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
		while (1) delay(10);
	}

	readCoefficients();
	// write8(BMP280_REGISTER_CONTROL, 0x3F); /* needed? */
	// setSampling();
	/* Default settings from datasheet. */
	setSampling(MODE_NORMAL,     /* Operating Mode. */
							SAMPLING_X2,     /* Temp. oversampling */
							SAMPLING_X16,    /* Pressure oversampling */
							FILTER_X16,      /* Filtering. */
							STANDBY_MS_500); /* Standby time. */
	delay(100);
}

void BMP_Update() {
	int32_t t_fine;

	// 温度と t_fine の更新
	{
		int32_t var1, var2;

		int32_t adc_T = read24(BMP280_REGISTER_TEMPDATA);
		adc_T >>= 4;

		var1 = ((((adc_T >> 3) - ((int32_t)barometer._bmp280_calib.dig_T1 << 1))) *
						((int32_t)barometer._bmp280_calib.dig_T2)) >>
					 11;

		var2 = (((((adc_T >> 4) - ((int32_t)barometer._bmp280_calib.dig_T1)) *
							((adc_T >> 4) - ((int32_t)barometer._bmp280_calib.dig_T1))) >>
						 12) *
						((int32_t)barometer._bmp280_calib.dig_T3)) >>
					 14;

		t_fine = var1 + var2;

		barometer.temperature = (t_fine * 5 + 128) >> 8;
		barometer.temperature = barometer.temperature / 100.0;
	}


	// 圧力の更新
	{
		int64_t var1, var2, p;

		int32_t adc_P = read24(BMP280_REGISTER_PRESSUREDATA);
		adc_P >>= 4;

		var1 = ((int64_t)t_fine) - 128000;
		var2 = var1 * var1 * (int64_t)barometer._bmp280_calib.dig_P6;
		var2 = var2 + ((var1 * (int64_t)barometer._bmp280_calib.dig_P5) << 17);
		var2 = var2 + (((int64_t)barometer._bmp280_calib.dig_P4) << 35);
		var1 = ((var1 * var1 * (int64_t)barometer._bmp280_calib.dig_P3) >> 8) +
					 ((var1 * (int64_t)barometer._bmp280_calib.dig_P2) << 12);
		var1 =
				(((((int64_t)1) << 47) + var1)) * ((int64_t)barometer._bmp280_calib.dig_P1) >> 33;

		if (var1 == 0) {
			barometer.pressure = 0; // avoid exception caused by division by zero
			return;
		}
		p = 1048576 - adc_P;
		p = (((p << 31) - var2) * 3125) / var1;
		var1 = (((int64_t)barometer._bmp280_calib.dig_P9) * (p >> 13) * (p >> 13)) >> 25;
		var2 = (((int64_t)barometer._bmp280_calib.dig_P8) * p) >> 19;

		p = ((p + var1 + var2) >> 8) + (((int64_t)barometer._bmp280_calib.dig_P7) << 4);
		barometer.pressure = (float)p / 256.0;
	}
}


void BMP_Print() {
	Serial.print(F("Temp="));
	Serial.println(barometer.temperature);
	Serial.print(F("Pres="));
	Serial.println(barometer.pressure);
}


float BMP_GetPressure() {
	return barometer.pressure;
}
float BMP_GetTemperature() {
	return barometer.temperature;
}




void write8(byte reg, byte value) {
	Wire.beginTransmission((uint8_t)BMP280_ADDRESS);
	Wire.write((uint8_t)reg);
	Wire.write((uint8_t)value);
	Wire.endTransmission();
}


/*!
 *  @brief  Reads an 8 bit value over I2C/SPI
 *  @param  reg
 *          selected register
 *  @return value from selected register
 */
uint8_t read8(byte reg) {
	uint8_t value;

	Wire.beginTransmission((uint8_t)BMP280_ADDRESS);
	Wire.write((uint8_t)reg);
	Wire.endTransmission();
	Wire.requestFrom((uint8_t)BMP280_ADDRESS, (byte)1);
	value = Wire.read();

	return value;
}


/*!
 *  @brief  Reads a 16 bit value over I2C/SPI
 */
uint16_t read16(byte reg) {
	uint16_t value;

	Wire.beginTransmission((uint8_t)BMP280_ADDRESS);
	Wire.write((uint8_t)reg);
	Wire.endTransmission();
	Wire.requestFrom((uint8_t)BMP280_ADDRESS, (byte)2);
	value = (Wire.read() << 8) | Wire.read();

	return value;
}


uint16_t read16_LE(byte reg) {
	uint16_t temp = read16(reg);
	return (temp >> 8) | (temp << 8);
}


/*!
 *   @brief  Reads a signed 16 bit value over I2C/SPI
 */
// int16_t readS16(byte reg) { return (int16_t)read16(reg); }
int16_t readS16_LE(byte reg) {
	return (int16_t)read16_LE(reg);
}


/*!
 *  @brief  Reads a 24 bit value over I2C/SPI
 */
uint32_t read24(byte reg) {
	uint32_t value;

	Wire.beginTransmission((uint8_t)BMP280_ADDRESS);
	Wire.write((uint8_t)reg);
	Wire.endTransmission();
	Wire.requestFrom((uint8_t)BMP280_ADDRESS, (byte)3);

	value = Wire.read();
	value <<= 8;
	value |= Wire.read();
	value <<= 8;
	value |= Wire.read();

	return value;
}


/*!
 *  @brief  Reads the factory-set coefficients
 */
void readCoefficients() {
	barometer._bmp280_calib.dig_T1 = read16_LE(BMP280_REGISTER_DIG_T1);
	barometer._bmp280_calib.dig_T2 = readS16_LE(BMP280_REGISTER_DIG_T2);
	barometer._bmp280_calib.dig_T3 = readS16_LE(BMP280_REGISTER_DIG_T3);

	barometer._bmp280_calib.dig_P1 = read16_LE(BMP280_REGISTER_DIG_P1);
	barometer._bmp280_calib.dig_P2 = readS16_LE(BMP280_REGISTER_DIG_P2);
	barometer._bmp280_calib.dig_P3 = readS16_LE(BMP280_REGISTER_DIG_P3);
	barometer._bmp280_calib.dig_P4 = readS16_LE(BMP280_REGISTER_DIG_P4);
	barometer._bmp280_calib.dig_P5 = readS16_LE(BMP280_REGISTER_DIG_P5);
	barometer._bmp280_calib.dig_P6 = readS16_LE(BMP280_REGISTER_DIG_P6);
	barometer._bmp280_calib.dig_P7 = readS16_LE(BMP280_REGISTER_DIG_P7);
	barometer._bmp280_calib.dig_P8 = readS16_LE(BMP280_REGISTER_DIG_P8);
	barometer._bmp280_calib.dig_P9 = readS16_LE(BMP280_REGISTER_DIG_P9);
}


void setSampling(sensor_mode mode,
								 sensor_sampling tempSampling,
								 sensor_sampling pressSampling,
								 sensor_filter filter,
								 standby_duration duration) {
	barometer._measReg.mode = mode;
	barometer._measReg.osrs_t = tempSampling;
	barometer._measReg.osrs_p = pressSampling;

	barometer._configReg.filter = filter;
	barometer._configReg.t_sb = duration;

	write8(BMP280_REGISTER_CONFIG, barometer._configReg.get());
	write8(BMP280_REGISTER_CONTROL, barometer._measReg.get());
}

