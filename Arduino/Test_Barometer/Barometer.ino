#include "./Barometer.h"


Barometer_t barometer;


ctrl_meas _measReg;
config _configReg;
uint8_t _i2caddr = BMP280_ADDRESS;
bmp280_calib_data _bmp280_calib;

int32_t t_fine;

// Adafruit_BMP280 bmp; // use I2C interface
// Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
// Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();






float readTemperature();
float readPressure();

void readCoefficients(void);
void write8(byte reg, byte value);
uint8_t read8(byte reg);
uint16_t read16(byte reg);
uint32_t read24(byte reg);
int16_t readS16(byte reg);
uint16_t read16_LE(byte reg);
int16_t readS16_LE(byte reg);

void setSampling(sensor_mode mode = MODE_NORMAL,
								 sensor_sampling tempSampling = SAMPLING_X16,
								 sensor_sampling pressSampling = SAMPLING_X16,
								 sensor_filter filter = FILTER_OFF,
								 standby_duration duration = STANDBY_MS_1);


void BMP_Init() {
	// Wire.begin();はされている前提！

	uint8_t chipid = BMP280_CHIPID;

	if (read8(BMP280_REGISTER_CHIPID) != chipid) {
		Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
		while (1) delay(10);
	}

	readCoefficients();
	// write8(BMP280_REGISTER_CONTROL, 0x3F); /* needed? */
	setSampling();
	delay(100);
}

void BMP_Update() {
	Serial.print(F("Temp: "));
	Serial.println(readTemperature());
	Serial.print(F("Pres: "));
	Serial.println(readPressure());

}

// void BMP_Init() {
// 	if (!bmp.begin()) {
// 		Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
// 		while (1) delay(10);
// 	}

// 	/* Default settings from datasheet. */
// 	bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
// 									Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
// 									Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
// 									Adafruit_BMP280::FILTER_X16,      /* Filtering. */
// 									Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

// 	bmp_temp->printSensorDetails();
// }


// void BMP_Update() {
// 	sensors_event_t temp_event, pressure_event;
// 	bmp_temp->getEvent(&temp_event);
// 	bmp_pressure->getEvent(&pressure_event);

// 	Serial.print(F("Temperature = "));
// 	Serial.print(temp_event.temperature);
// 	Serial.println(" *C");

// 	Serial.print(F("Pressure = "));
// 	Serial.print(pressure_event.pressure);
// 	Serial.println(" hPa");

// 	Serial.println();
// 	// delay(2000);
// }





float readTemperature() {
	int32_t var1, var2;

	int32_t adc_T = read24(BMP280_REGISTER_TEMPDATA);
	adc_T >>= 4;

	var1 = ((((adc_T >> 3) - ((int32_t)_bmp280_calib.dig_T1 << 1))) *
					((int32_t)_bmp280_calib.dig_T2)) >>
				 11;

	var2 = (((((adc_T >> 4) - ((int32_t)_bmp280_calib.dig_T1)) *
						((adc_T >> 4) - ((int32_t)_bmp280_calib.dig_T1))) >>
					 12) *
					((int32_t)_bmp280_calib.dig_T3)) >>
				 14;

	t_fine = var1 + var2;

	float T = (t_fine * 5 + 128) >> 8;
	return T / 100;
}

float readPressure() {
	int64_t var1, var2, p;

	// Must be done first to get the t_fine variable set up
	readTemperature();

	int32_t adc_P = read24(BMP280_REGISTER_PRESSUREDATA);
	adc_P >>= 4;

	var1 = ((int64_t)t_fine) - 128000;
	var2 = var1 * var1 * (int64_t)_bmp280_calib.dig_P6;
	var2 = var2 + ((var1 * (int64_t)_bmp280_calib.dig_P5) << 17);
	var2 = var2 + (((int64_t)_bmp280_calib.dig_P4) << 35);
	var1 = ((var1 * var1 * (int64_t)_bmp280_calib.dig_P3) >> 8) +
				 ((var1 * (int64_t)_bmp280_calib.dig_P2) << 12);
	var1 =
			(((((int64_t)1) << 47) + var1)) * ((int64_t)_bmp280_calib.dig_P1) >> 33;

	if (var1 == 0) {
		return 0; // avoid exception caused by division by zero
	}
	p = 1048576 - adc_P;
	p = (((p << 31) - var2) * 3125) / var1;
	var1 = (((int64_t)_bmp280_calib.dig_P9) * (p >> 13) * (p >> 13)) >> 25;
	var2 = (((int64_t)_bmp280_calib.dig_P8) * p) >> 19;

	p = ((p + var1 + var2) >> 8) + (((int64_t)_bmp280_calib.dig_P7) << 4);
	return (float)p / 256;
}





void write8(byte reg, byte value) {
	Wire.beginTransmission((uint8_t)_i2caddr);
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

	Wire.beginTransmission((uint8_t)_i2caddr);
	Wire.write((uint8_t)reg);
	Wire.endTransmission();
	Wire.requestFrom((uint8_t)_i2caddr, (byte)1);
	value = Wire.read();

	return value;
}

/*!
 *  @brief  Reads a 16 bit value over I2C/SPI
 */
uint16_t read16(byte reg) {
	uint16_t value;

	Wire.beginTransmission((uint8_t)_i2caddr);
	Wire.write((uint8_t)reg);
	Wire.endTransmission();
	Wire.requestFrom((uint8_t)_i2caddr, (byte)2);
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
int16_t readS16(byte reg) { return (int16_t)read16(reg); }

int16_t readS16_LE(byte reg) {
	return (int16_t)read16_LE(reg);
}

/*!
 *  @brief  Reads a 24 bit value over I2C/SPI
 */
uint32_t read24(byte reg) {
	uint32_t value;

	Wire.beginTransmission((uint8_t)_i2caddr);
	Wire.write((uint8_t)reg);
	Wire.endTransmission();
	Wire.requestFrom((uint8_t)_i2caddr, (byte)3);

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
	_bmp280_calib.dig_T1 = read16_LE(BMP280_REGISTER_DIG_T1);
	_bmp280_calib.dig_T2 = readS16_LE(BMP280_REGISTER_DIG_T2);
	_bmp280_calib.dig_T3 = readS16_LE(BMP280_REGISTER_DIG_T3);

	_bmp280_calib.dig_P1 = read16_LE(BMP280_REGISTER_DIG_P1);
	_bmp280_calib.dig_P2 = readS16_LE(BMP280_REGISTER_DIG_P2);
	_bmp280_calib.dig_P3 = readS16_LE(BMP280_REGISTER_DIG_P3);
	_bmp280_calib.dig_P4 = readS16_LE(BMP280_REGISTER_DIG_P4);
	_bmp280_calib.dig_P5 = readS16_LE(BMP280_REGISTER_DIG_P5);
	_bmp280_calib.dig_P6 = readS16_LE(BMP280_REGISTER_DIG_P6);
	_bmp280_calib.dig_P7 = readS16_LE(BMP280_REGISTER_DIG_P7);
	_bmp280_calib.dig_P8 = readS16_LE(BMP280_REGISTER_DIG_P8);
	_bmp280_calib.dig_P9 = readS16_LE(BMP280_REGISTER_DIG_P9);
}



void setSampling(sensor_mode mode,
																	sensor_sampling tempSampling,
																	sensor_sampling pressSampling,
																	sensor_filter filter,
																	standby_duration duration) {
	_measReg.mode = mode;
	_measReg.osrs_t = tempSampling;
	_measReg.osrs_p = pressSampling;

	_configReg.filter = filter;
	_configReg.t_sb = duration;

	write8(BMP280_REGISTER_CONFIG, _configReg.get());
	write8(BMP280_REGISTER_CONTROL, _measReg.get());
}

