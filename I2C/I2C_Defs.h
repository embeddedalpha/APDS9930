/*
 * I2C_Defs.h
 *
 *  Created on: Nov 20, 2023
 *      Author: kunal
 */

#ifndef I2C_DEFS_H_
#define I2C_DEFS_H_

#include "main.h"


static const struct I2C1_SDA_Pin
{
	uint8_t PB7;
	uint8_t PB9;
}I2C1_SDA_Pin={27,29};

static const struct I2C1_SCL_Pin
{
	uint8_t PB6;
	uint8_t PB8;
}I2C1_SCL_Pin={26,28};

static const struct I2C2_SDA_Pin
{
	uint8_t PB11;
}I2C2_SDA_Pin={211};

static const struct I2C2_SCL_Pin
{
	uint8_t PB10;
}I2C2_SCL_Pin={210};

static const struct I2C3_SDA_Pin
{
	uint8_t PC9;
}I2C3_SDA_Pin={39};

static const struct I2C3_SCL_Pin
{
	uint8_t PA8;
}I2C3_SCL_Pin={18};

static const struct I2C_Mode
{
	uint8_t Master;
	uint8_t Slave;
}I2C_Mode={0,1};

static const struct I2C_Interrupts
{
	uint16_t Disable;
	uint16_t Error;
	uint16_t Event;
	uint16_t Buffer;
}I2C_Interrupts={0,1<<8,1<<9,1<<10};

static const struct I2C_DMA
{
	uint16_t Disable;
	uint16_t Enable;
}I2C_DMA = {0,1};



#endif /* I2C_DEFS_H_ */
