#include "./Barometer.h"


Barometer_t barometer;

Adafruit_BMP280 bmp; // use I2C interface
Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();


void BMP_Init() {
	if (!bmp.begin()) {
		Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
		while (1) delay(10);
	}

	/* Default settings from datasheet. */
	bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
									Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
									Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
									Adafruit_BMP280::FILTER_X16,      /* Filtering. */
									Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

	bmp_temp->printSensorDetails();
}


void BMP_Update() {
	sensors_event_t temp_event, pressure_event;
	bmp_temp->getEvent(&temp_event);
	bmp_pressure->getEvent(&pressure_event);

	Serial.print(F("Temperature = "));
	Serial.print(temp_event.temperature);
	Serial.println(" *C");

	Serial.print(F("Pressure = "));
	Serial.print(pressure_event.pressure);
	Serial.println(" hPa");

	Serial.println();
	// delay(2000);
}