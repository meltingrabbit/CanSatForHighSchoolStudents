#include "./BarometerThermohygrometer.h"

BarometerThermohygrometer_t bthmeter;

#define BME280_ADDR_ 0x76
#define CONFIG_      0xF5
#define CTRL_MEAS_   0xF4
#define CTRL_HUM_    0xF2

// 気温補正データ
static uint16_t dig_T1;
static int16_t  dig_T2;
static int16_t  dig_T3;

// 湿度補正データ
static uint8_t  dig_H1;
static int16_t  dig_H2;
static uint8_t  dig_H3;
static int16_t  dig_H4;
static int16_t  dig_H5;
static int8_t   dig_H6;

// 気圧補正データ
static uint16_t dig_P1;
static int16_t  dig_P2;
static int16_t  dig_P3;
static int16_t  dig_P4;
static int16_t  dig_P5;
static int16_t  dig_P6;
static int16_t  dig_P7;
static int16_t  dig_P8;
static int16_t  dig_P9;

int32_t t_fine;

static unsigned char buffer[26];

int32_t BME280_compensate_T_int32_(int32_t adc_T);
uint32_t BME280_compensate_H_int32_(int32_t adc_H);
uint32_t BME280_compensate_P_int32_(int32_t adc_P);

void BTH_Init() {
	// Wire.begin();はされている前提！

	bthmeter.pressure    = 0.0;
	bthmeter.humidity    = 0.0;
	bthmeter.temperature = 0.0;

	// BME280の設定
	// BME280動作設定
	Wire.beginTransmission(BME280_ADDR_);
	Wire.write(CONFIG_);	// 動作設定
	Wire.write(0x00);		// 「単発測定」，「フィルタなし」，「SPI 4線式」
	Wire.endTransmission();

	//BME280測定条件設定
	Wire.beginTransmission(BME280_ADDR_);
	Wire.write(CTRL_MEAS_);	// 測定条件設定
	Wire.write(0x24);		// 「温度・気圧オーバーサンプリングx1」，「スリープモード」
	Wire.endTransmission();

	//BME280温度測定条件設定
	Wire.beginTransmission(BME280_ADDR_);
	Wire.write(CTRL_HUM_);	// 湿度測定条件設定
	Wire.write(0x01);		// 「湿度オーバーサンプリングx1」
	Wire.endTransmission();

	//BME280補正データ取得
	Wire.beginTransmission(BME280_ADDR_);
	Wire.write(0x88);		// 出力データバイトを「補正データ」のアドレスに指定
	Wire.endTransmission();

	Wire.requestFrom(BME280_ADDR_, 26);
	for (uint8_t i=0; i<26; i++) {
		while (Wire.available() == 0) {
			Serial.println(F("Waiting for receiving data from BME280..."));
		}
		buffer[i] = Wire.read();
	}

	dig_T1 = ((uint16_t)((buffer[1] << 8) | buffer[0]));
	dig_T2 = ((int16_t) ((buffer[3] << 8) | buffer[2]));
	dig_T3 = ((int16_t) ((buffer[5] << 8) | buffer[4]));

	dig_P1 = ((uint16_t)((buffer[7] << 8) | buffer[6]));
	dig_P2 = ((int16_t) ((buffer[9] << 8) | buffer[8]));
	dig_P3 = ((int16_t)((buffer[11] << 8) | buffer[10]));
	dig_P4 = ((int16_t)((buffer[13] << 8) | buffer[12]));
	dig_P5 = ((int16_t)((buffer[15] << 8) | buffer[14]));
	dig_P6 = ((int16_t)((buffer[17] << 8) | buffer[16]));
	dig_P7 = ((int16_t)((buffer[19] << 8) | buffer[18]));
	dig_P8 = ((int16_t)((buffer[21] << 8) | buffer[20]));
	dig_P9 = ((int16_t)((buffer[23] << 8) | buffer[22]));

	dig_H1 = ((uint8_t)(buffer[25]));

	Wire.beginTransmission(BME280_ADDR_);
	Wire.write(0xE1);		// 出力データバイトを「補正データ」のアドレスに指定
	Wire.endTransmission();

	Wire.requestFrom(BME280_ADDR_, 7);
	for (uint8_t i=0; i<7; i++) {
		while (Wire.available() == 0) {
			Serial.println(F("Waiting for receiving data from BME280..."));
		}
		buffer[i] = Wire.read();
	}

	dig_H2 = ((int16_t)((buffer[1] << 8) | buffer[0]));
	dig_H3 = ((uint8_t)(buffer[2]));
	dig_H4 = ((int16_t)((buffer[3] << 4) + (buffer[4] & 0x0F)));
	dig_H5 = ((int16_t)((buffer[5] << 4) + ((buffer[4] >> 4) & 0x0F)));
	dig_H6 = ((int8_t)buffer[6]);
}


void BTH_Update() {
	int32_t  temp_cal;
	uint32_t humi_cal, pres_cal;

	// BME280測定条件設定 (1回測定後，スリープモード)
	Wire.beginTransmission(BME280_ADDR_);
	Wire.write(CTRL_MEAS_);				// 測定条件設定
	Wire.write(0x25);					// 「温度・気圧オーバーサンプリングx1」，「1回測定後，スリープモード」
	Wire.endTransmission();
	delay(1);

	// 測定データ取得
	Wire.beginTransmission(BME280_ADDR_);
	Wire.write(0xF7);					// 出力データバイトを「気圧データ」のアドレスに指定
	Wire.endTransmission();

	Wire.requestFrom(BME280_ADDR_, 8);
	for (uint8_t i=0; i<8; i++) {
		while (Wire.available() == 0 ) {
			Serial.println(F("Waiting for receiving data from BME280..."));
		}
		buffer[i] = Wire.read();
	}

	int32_t adc_T = ((uint32_t)buffer[3] << 12) | ((uint32_t)buffer[4] << 4) | ((buffer[5] >> 4) & 0x0F);
	int32_t adc_P = ((uint32_t)buffer[0] << 12) | ((uint32_t)buffer[1] << 4) | ((buffer[2] >> 4) & 0x0F);
	int32_t adc_H = ((uint32_t)buffer[6] << 8) | ((uint32_t)buffer[7]);

	temp_cal = BME280_compensate_T_int32_(adc_T);		// 温度データ補正計算
	pres_cal = BME280_compensate_P_int32_(adc_P);		// 気圧データ補正計算
	humi_cal = BME280_compensate_H_int32_(adc_H);		// 湿度データ補正計算

	bthmeter.temperature = (float)temp_cal / 100.0;		// 温度データを実際の値に計算
	bthmeter.pressure    = (float)pres_cal / 100.0;		// 気圧データを実際の値に計算
	bthmeter.humidity    = (float)humi_cal / 1024.0;	// 湿度データを実際の値に計算
}


void BTH_Print() {
	Serial.print(F("Temp = "));
	Serial.print(BTH_GetTemperature());
	Serial.println(" [degC]");
	Serial.print(F("Hmid = "));
	Serial.print(BTH_GetHumidity());
	Serial.println(F(" [parcent]"));
	Serial.print(F("Pres = "));
	Serial.print(BTH_GetPressure());
	Serial.println(F(" [hPa]"));
}


float BTH_GetPressure() {
	return bthmeter.pressure;
}


float BTH_GetHumidity() {
	return bthmeter.humidity;
}


float BTH_GetTemperature() {
	return bthmeter.temperature;
}


// 温度補正 関数
int32_t BME280_compensate_T_int32_(int32_t adc_T)
{
	int32_t var1, var2, T;
	var1   = ((((adc_T>>3) - ((int32_t)dig_T1<<1))) * ((int32_t)dig_T2)) >> 11;
	var2   = (((((adc_T>>4) - ((int32_t)dig_T1)) * ((adc_T>>4) - ((int32_t)dig_T1))) >> 12) * ((int32_t)dig_T3)) >> 14;
	t_fine = var1 + var2;
	T      = (t_fine * 5 + 128) >> 8;
	return T;
}

// 湿度補正 関数
uint32_t BME280_compensate_H_int32_(int32_t adc_H)
{
	int32_t v_x1_u32r;

	v_x1_u32r = (t_fine - ((int32_t)76800));
	v_x1_u32r = (((((adc_H << 14) - (((int32_t)dig_H4) << 20) - (((int32_t)dig_H5) * v_x1_u32r)) + ((int32_t)16384)) >> 15)
		* (((((((v_x1_u32r * ((int32_t)dig_H6)) >> 10) * (((v_x1_u32r * ((int32_t)dig_H3)) >> 11) + ((int32_t)32768))) >> 10)
		+ ((int32_t)2097152)) * ((int32_t)dig_H2) + 8192) >> 14));
	v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) * ((int32_t)dig_H1)) >> 4));
	v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
	v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);
	return (uint32_t)(v_x1_u32r>>12);
}

// 気圧補正 関数
uint32_t BME280_compensate_P_int32_(int32_t adc_P)
{
	int32_t var1, var2;
	uint32_t p;
	var1 = (((int32_t)t_fine)>>1) - (int32_t)64000;
	var2 = (((var1>>2) * (var1>>2)) >> 11 ) * ((int32_t)dig_P6);
	var2 = var2 + ((var1*((int32_t)dig_P5))<<1);
	var2 = (var2>>2)+(((int32_t)dig_P4)<<16);
	var1 = (((dig_P3 * (((var1>>2) * (var1>>2)) >> 13 )) >> 3) + ((((int32_t)dig_P2) * var1)>>1))>>18;
	var1 =((((32768+var1))*((int32_t)dig_P1))>>15);
	if (var1 == 0) {
		return 0; // avoid exception caused by division by zero
	}
	p = (((uint32_t)(((int32_t)1048576)-adc_P)-(var2>>12)))*3125;
	if (p < 0x80000000) {
		p = (p << 1) / ((uint32_t)var1);
	} else {
		p = (p / (uint32_t)var1) * 2;
	}
	var1 = (((int32_t)dig_P9) * ((int32_t)(((p>>3) * (p>>3))>>13)))>>12;
	var2 = (((int32_t)(p>>2)) * ((int32_t)dig_P8))>>13;
	p = (uint32_t)((int32_t)p + ((var1 + var2 + dig_P7) >> 4));
	return p;
}
