/*
 * APDS9930.c
 *
 *  Created on: Jan 31, 2024
 *      Author: kunal
 */


#include "../APDS9930/APDS9930.h"

#include "math.h"
#include "fastmath.h"
#include "APDS9930_Defs.h"

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



	//Read ID to verify connection with IC

	config->ID = Read_Reg(APDS9930_Regs.ID);
	if(config -> ID == 0x39)
	{
		// Go forward with initialization
		Write_Reg(APDS9930_Regs.ENABLE, 0x00);

		if((config->ALS_Interrupt_Enable || config->Proximity_Interrupt_Enable) && config->Interrupt_Port != NULL)
		{
				//enable interrupt
			GPIO_Pin_Init(config->Interrupt_Port, config->Interrupt_Pin, MODE.Input, Output_Type.Open_Drain, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.None);
			GPIO_Interrupt_Setup(config->Interrupt_Pin,Interrupt_Edge.FALLING_EDGE , 0);


			if(config->ALS_Interrupt_Enable)
			{
				Write_Reg(APDS9930_Regs.AIHTL,  0x00FF & config->ALS_High_Threshold);
				Write_Reg(APDS9930_Regs.AIHTH, (0xFF00 & config->ALS_High_Threshold)>>8);
				Write_Reg(APDS9930_Regs.AILTL,  0x00FF & config->ALS_Low_Threshold);
				Write_Reg(APDS9930_Regs.AILTH, (0xFF00 & config->ALS_Low_Threshold)>>8);
			}

			if(config->Proximity_High_Threshold)
			{
				Write_Reg(APDS9930_Regs.PIHTL,  0x00FF & config->Proximity_High_Threshold);
				Write_Reg(APDS9930_Regs.PIHTH, (0xFF00 & config->Proximity_High_Threshold)>>8);
				Write_Reg(APDS9930_Regs.PILTL,  0x00FF & config->Proximity_Low_Threshold);
				Write_Reg(APDS9930_Regs.PILTH, (0xFF00 & config->Proximity_Low_Threshold)>>8);
			}

		}



		Write_Reg(APDS9930_Regs.ATIME, 0xED);
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



void APDS9930_Get_Lux(APDS9930 *config)
{
	float DF = 52.0;
	float GA = 0.49;
	float ALSIT = 2.73 * (256 - 0xED);
	float Ch0 = 0.0;
	float Ch1 = 0.0;
	Ch0 = Read_Word(APDS9930_Regs.Ch0DATAL);
	Ch1 = Read_Word(APDS9930_Regs.Ch1DATAL);
	float iac = MAX(Ch0 - 1.862 * Ch1,0.746 * Ch0 - 1.291 * Ch1);
	if (iac < 0) iac = 0;
	float lpc  = GA * DF / (ALSIT * 1);
	config->Lux_Data = iac * lpc;
}

void APDS9930_Get_Proximity(APDS9930 *config)
{
	config->Proximity_Data = Read_Word(APDS9930_Regs.PDATAL);
}
