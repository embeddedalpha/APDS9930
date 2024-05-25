/*
 * APDS9930.c
 *
 *  Created on: Jan 31, 2024
 *      Author: kunal
 */


#include "APDS9930.h"
#include "math.h"
#include "APDS9930_Defs.h"
#include "fastmath.h"

I2C_Config APDS9930_I2C;

#define Proximity_Interrupt_Clear_Command 0x05
#define ALS_Interrupt_Clear_Command 0x06
#define Prox_and_ALS_Interrupt_Clear_Command 0x07


void Write_Reg(uint8_t reg, uint8_t data)
{
	I2C_Master_Write_Register(&APDS9930_I2C, 0x39, 0x80 | reg, data);
}

uint8_t Read_Reg(uint8_t reg)
{

	return I2C_Master_Read_Register(&APDS9930_I2C, 0x39, 0xA0 | reg);
}

uint16_t Read_Word(uint8_t reg)
{
	uint16_t x;
	uint16_t y;

	x = Read_Reg(reg);
	y = Read_Reg(reg+1)<<8;

	return (x|y);
}

void APDS9930_Proximity_Interrupt_Clear(APDS9930 *config)
{
	I2C_Master_Start(&APDS9930_I2C);
	I2C_Master_Address(&APDS9930_I2C, 0x39,0);
	I2C_Master_Send_Byte(&APDS9930_I2C, 0xE0 | Proximity_Interrupt_Clear_Command);
	I2C_Master_Stop(&APDS9930_I2C);

}

void APDS9930_ALS_Interrupt_Clear(APDS9930 *config)
{
	I2C_Master_Start(&APDS9930_I2C);
	I2C_Master_Address(&APDS9930_I2C, 0x39,0);
	I2C_Master_Send_Byte(&APDS9930_I2C, 0xE0 | ALS_Interrupt_Clear_Command);
	I2C_Master_Stop(&APDS9930_I2C);
}

void APDS9930_Prox_and_ALS_Interrupt_Clear(APDS9930 *config)
{
	I2C_Master_Start(&APDS9930_I2C);
	I2C_Master_Address(&APDS9930_I2C, 0x39,0);
	I2C_Master_Send_Byte(&APDS9930_I2C, 0xE0 | Prox_and_ALS_Interrupt_Clear_Command);
	I2C_Master_Stop(&APDS9930_I2C);
}

void APDS9930_DeInit(APDS9930 *config)
{
	config->Port = NULL;
	config->Interrupt_Port = NULL;
	config->SDA_Pin = 0;
	config->SCL_Pin = 0;
	config->Proximity_Interrupt_Enable = false;
	config->ALS_Interrupt_Enable = false;
	config->Proximity_Data = -1;
	config->Lux_Data = -1;
}


bool APDS9930_Init(APDS9930 *config)
{
	bool retval;

	I2C_Reset(&APDS9930_I2C);
	APDS9930_I2C.Port = config->Port;
	APDS9930_I2C.SCL_Pin = config->SCL_Pin;
	APDS9930_I2C.SDA_Pin = config->SDA_Pin;
	APDS9930_I2C.mode = I2C_Mode.Master;
	APDS9930_I2C.speed = 400000;
	I2C_Init(&APDS9930_I2C);

	if((config->ALS_Interrupt_Enable || config->Proximity_Interrupt_Enable) && config->Interrupt_Port != NULL)
	{
		//enable interrupt
	GPIO_Pin_Init(config->Interrupt_Port, config->Interrupt_Pin, MODE.Input, Output_Type.Open_Drain, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.None);
	GPIO_Interrupt_Setup(config->Interrupt_Pin,Interrupt_Edge.FALLING_EDGE , 0);
	}

	//Read ID to verify connection with IC

	config->ID = Read_Reg(APDS9930_Regs.ID);
	if(config -> ID == 0x39)
	{
		// Go forward with initialization
		Write_Reg(APDS9930_Regs.ENABLE, 0x00);
		Write_Reg(APDS9930_Regs.ATIME, 0xff);
		Write_Reg(APDS9930_Regs.PTIME, 0xFF);
		Write_Reg(APDS9930_Regs.WTIME, 0xff);
		Write_Reg(APDS9930_Regs.PPULSE, 0x04); //0x01
		Write_Reg(APDS9930_Regs.CONTROL, 0x20);
		Write_Reg(APDS9930_Regs.CONFIG, 0x00);
		Write_Reg(APDS9930_Regs.POFFSET, 0x00);
		Write_Reg(APDS9930_Regs.ENABLE, 0x2F);
		Delay_ms(12);

		retval = true;

//		APDS9930_Prox_and_ALS_Interrupt_Clear(config);

	}
	else
	{
		config->ID = 0;
		retval = false;
	}

	return retval;
}

void APDS9930_Read_Data(APDS9930 *config)
{
//	APDS9930_Prox_and_ALS_Interrupt_Clear(config);
	config->Proximity_Data = Read_Word(0x18);

	float CH0_data = 0.0;
	float CH1_data = 0.0;
	float DF = 52.0;
	float IAC[3];
	float LPC = 0.0;
	float ALSIT = 400.0;
	float AGAIN = 1.0;
	float GA = 0.49;
	float B = 1.862;
	float C = 0.746;
	float D = 1.291;

	CH0_data = Read_Word(APDS9930_Regs.Ch0DATAL);
	CH1_data = Read_Word(APDS9930_Regs.Ch1DATAL);

	// LUX Equation:

	IAC[1] =   CH0_data - B*CH1_data;
	IAC[2] = C*CH0_data - D*CH1_data;
	IAC[0] = MAX(IAC[1], IAC[2]);
	LPC = GA * DF / (ALSIT * AGAIN);
	config->Lux_Data = IAC[0] * LPC;

}

