#include "./BarometerThermohygrometer.h"

BarometerThermohygrometer_t bthmeter;

void BTH_Init() {
	// Wire.begin();はされている前提！

	bthmeter.pressure    = 0.0;
	bthmeter.humidity    = 0.0;
	bthmeter.temperature = 0.0;
	bthmeter.altitude    = 0.0;

	if (bthmeter.bme280.beginI2C()) {
		Serial.println(F("Could not find a valid BME280 sensor, check wiring!"));
		while (1) delay(10);
	}
}


void BTH_Update() {
	bthmeter.pressure    = bthmeter.bme280.readFloatPressure();
	bthmeter.humidity    = bthmeter.bme280.readFloatHumidity();
	bthmeter.temperature = bthmeter.bme280.readTempC();
	bthmeter.altitude    = bthmeter.bme280.readFloatAltitudeMeters();
}


void BTH_Print() {
	Serial.print(F("Temp="));
	Serial.println(bthmeter.temperature);
	Serial.print(F("Hmid="));
	Serial.println(bthmeter.humidity);
	Serial.print(F("Pres="));
	Serial.println(bthmeter.pressure);
	Serial.print(F("Alti="));
	Serial.println(bthmeter.altitude);
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


float BTH_GetAltitude() {
	return bthmeter.altitude;
}

