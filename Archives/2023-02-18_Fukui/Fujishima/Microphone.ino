#include "./Microphone.h"

Microphone_t microphone;

static void MIC_Update_();

static const uint8_t MIC_SAMPLING_NUM = 10;
static const uint32_t MIC_MEDIAN = 512;

void MIC_Init() {
	microphone.average = 0;
	microphone.maximum = 0;
}

static void MIC_Update_()
{
	// Serial.println(millis());
	uint32_t average = 0;
	uint32_t maximum = 0;
	for (int8_t i = 0; i < MIC_SAMPLING_NUM; i++) {
		uint32_t value = abs(analogRead(PIN_MIC) - MIC_MEDIAN);
		average += value;
		if (maximum < value) {
			maximum = value;
		}
	}
	microphone.average = average / MIC_SAMPLING_NUM;
	microphone.maximum = maximum;
	// Serial.println(millis());
}

int MIC_GetAverage() {
	MIC_Update_();
	return (int)microphone.average;
}

int MIC_GetMaximum() {
	MIC_Update_();
	return (int)microphone.maximum;
}

void MIC_Print() {
	MIC_Update_();
	Serial.print(F("Mic= "));
	Serial.print(microphone.average);
	Serial.print(F(", "));
	Serial.print(microphone.maximum);
	Serial.println(F(""));
}