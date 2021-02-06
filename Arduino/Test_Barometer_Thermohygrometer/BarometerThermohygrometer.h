#ifndef BTH_H
#define BTH_H

#include "./PIN_ASSIGN.h"
#include <Wire.h>

// #################### Barometer & Thermohygrometer ####################

void BTH_Init();
void BTH_Update();
void BTH_Print();
float BTH_GetPressure();
float BTH_GetHumidity();
float BTH_GetTemperature();

typedef struct {
	float   pressure;
	float   humidity;
	float   temperature;
} BarometerThermohygrometer_t;

#endif

