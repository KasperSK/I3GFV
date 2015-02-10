#include "LM75.h"

struct LM75 {
	int16_t temperature;
	uint8_t status;
	size_t id;
};

LM75_t Create_LM75(size_t id) {
	TEMPERATUR_Start();
	LM75_t lm = (LM75_t)malloc(sizeof(struct LM75));
	lm->id = id;
	return lm;
}

void LM75_poll(LM75_t lm) {
	uint8_t values[2];
	TEMPERATUR_I2CMasterClearStatus();
	lm->status = TEMPERATUR_I2CMasterSendStart(LM75_BASE_ADDRESS + lm->id, 1);
	if (lm->status == TEMPERATUR_I2C_MSTR_NO_ERROR) {
		values[HIGH] = TEMPERATUR_I2CMasterReadByte(TEMPERATUR_I2C_ACK_DATA);
		values[LOW] = TEMPERATUR_I2CMasterReadByte(TEMPERATUR_I2C_NAK_DATA);  
		lm->temperature = ((int16_t)(values[HIGH] << 8 | values[LOW]))>>7;
    }
	TEMPERATUR_I2CMasterSendStop();
}

int16 LM75_temperature(LM75_t lm) {
	//Temperatur factor 10 higher than the correct temp due to float being a biatch
	return lm->temperature*5;   
}
