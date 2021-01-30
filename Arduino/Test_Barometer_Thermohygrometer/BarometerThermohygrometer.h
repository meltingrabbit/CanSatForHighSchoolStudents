#ifndef BTH_H
#define BTH_H

#include "./PIN_ASSIGN.h"
#include "./SparkFunBME280.h"
#include <Wire.h>


// #################### Barometer & Thermohygrometer ####################


void BTH_Init();
void BTH_Update();
void BTH_Print();
float BTH_GetPressure();
float BTH_GetHumidity();
float BTH_GetTemperature();
float BTH_GetAltitude();

typedef struct {
	BME280  bme280;
	float   pressure;
	float   humidity;
	float   temperature;
	float   altitude;
} BarometerThermohygrometer_t;


#endif

