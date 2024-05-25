/*
 * APDS9930.h
 *
 *  Created on: Jan 31, 2024
 *      Author: kunal
 */

#ifndef APDS9930_H_
#define APDS9930_H_

#include "main.h"
#include "GPIO.h"
#include "I2C.h"


typedef struct APDS9930{

	I2C_TypeDef *Port;
	uint8_t SDA_Pin;
	uint8_t SCL_Pin;

	GPIO_TypeDef *Interrupt_Port;
	uint8_t Interrupt_Pin;

	bool Proximity_Interrupt_Enable;
	uint16_t Proximity_Low_Threshold;
	uint16_t Proximity_High_Threshold;

	bool ALS_Interrupt_Enable;
	uint16_t ALS_Low_Threshold;
	uint16_t ALS_High_Threshold;

	uint16_t Proximity_Data;
	float Lux_Data;

	uint8_t ID;

}APDS9930;

void APDS9930_DeInit(APDS9930 *config);
bool APDS9930_Init(APDS9930 *config);
void APDS9930_Read_Data(APDS9930 *config);
void APDS9930_Proximity_Interrupt_Clear(APDS9930 *config);
void APDS9930_ALS_Interrupt_Clear(APDS9930 *config);
void APDS9930_Prox_and_ALS_Interrupt_Clear(APDS9930 *config);


#endif /* APDS9930_H_ */
