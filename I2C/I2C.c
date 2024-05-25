/*
 * I2C.c
 *
 *  Created on: Nov 20, 2023
 *      Author: kunal
 */


#include "I2C.h"

static uint32_t temp;

DMA_Config xI2C_TX;
DMA_Config xI2C_RX;

static void pin_setup(I2C_Config *config)
{
	if(config->Port == I2C1)
	{
		if(config->SCL_Pin == I2C1_SCL_Pin.PB6) GPIO_Pin_Init(GPIOB, 6, MODE.Alternate_Function, Output_Type.Open_Drain, Speed.Very_High_Speed, Pull.Pull_Up, Alternate_Functions.I2C_1);
		else if(config->SCL_Pin == I2C1_SCL_Pin.PB8) GPIO_Pin_Init(GPIOB, 8, MODE.Alternate_Function, Output_Type.Open_Drain, Speed.Very_High_Speed, Pull.Pull_Up, Alternate_Functions.I2C_1);

		if(config->SDA_Pin == I2C1_SDA_Pin.PB7) GPIO_Pin_Init(GPIOB, 7, MODE.Alternate_Function, Output_Type.Open_Drain, Speed.Very_High_Speed, Pull.Pull_Up, Alternate_Functions.I2C_1);
		else if(config->SDA_Pin == I2C1_SDA_Pin.PB9) GPIO_Pin_Init(GPIOB, 9, MODE.Alternate_Function, Output_Type.Open_Drain, Speed.Very_High_Speed, Pull.Pull_Up, Alternate_Functions.I2C_1);

	}
	else if(config->Port == I2C2)
	{
		if(config->SCL_Pin == I2C2_SCL_Pin.PB10) GPIO_Pin_Init(GPIOB, 10, MODE.Alternate_Function, Output_Type.Open_Drain, Speed.Very_High_Speed, Pull.Pull_Up, Alternate_Functions.I2C_2);
		if(config->SDA_Pin == I2C2_SDA_Pin.PB11) GPIO_Pin_Init(GPIOB, 11, MODE.Alternate_Function, Output_Type.Open_Drain, Speed.Very_High_Speed, Pull.Pull_Up, Alternate_Functions.I2C_2);
	}
	else if(config->Port == I2C3)
	{
		if(config->SCL_Pin == I2C3_SCL_Pin.PA8) GPIO_Pin_Init(GPIOA, 8, MODE.Alternate_Function, Output_Type.Open_Drain, Speed.Very_High_Speed, Pull.Pull_Up, Alternate_Functions.I2C_3);
		if(config->SDA_Pin == I2C3_SDA_Pin.PC9) GPIO_Pin_Init(GPIOC, 9, MODE.Alternate_Function, Output_Type.Open_Drain, Speed.Very_High_Speed, Pull.Pull_Up, Alternate_Functions.I2C_3);
	}
}

void I2C_Clock_Enable(I2C_Config *config)
{
	if(config->Port == I2C1)
	{
		RCC -> APB1ENR |= RCC_APB1ENR_I2C1EN;
	}
	else if(config->Port == I2C2)
	{
		RCC -> APB1ENR |= RCC_APB1ENR_I2C2EN;
	}
	else if(config->Port == I2C3)
	{
		RCC -> APB1ENR |= RCC_APB1ENR_I2C3EN;
	}
}

void I2C_Clock_Disable(I2C_Config *config)
{
	if(config->Port == I2C1)
	{
		RCC -> APB1ENR &= ~RCC_APB1ENR_I2C1EN;
	}
	else if(config->Port == I2C2)
	{
		RCC -> APB1ENR &= ~RCC_APB1ENR_I2C2EN;
	}
	else if(config->Port == I2C3)
	{
		RCC -> APB1ENR &= ~RCC_APB1ENR_I2C3EN;
	}
}

void I2C_Reset(I2C_Config *config)
{
	config->speed = 100000;
	config->interrupts = I2C_Interrupts.Disable;
	config->mode = I2C_Mode.Master;
	if(config->Port == I2C1)
	{
		RCC -> APB1RSTR |= RCC_APB1RSTR_I2C1RST;
	}
	else if(config->Port == I2C2)
	{
		RCC -> APB1RSTR |= RCC_APB1RSTR_I2C2RST;
	}
	else if(config->Port == I2C3)
	{
		RCC -> APB1RSTR |= RCC_APB1RSTR_I2C3RST;
	}
}


void I2C_Init(I2C_Config *config)
{
	pin_setup(config);
	I2C_Clock_Enable(config);

	config->Port -> CR1 &= ~I2C_CR1_PE;
	config->Port -> CR1 |= I2C_CR1_SWRST | I2C_CR1_NOSTRETCH;
	config->Port -> CR1 &= ~I2C_CR1_SWRST;
	config->Port -> CR2 |= config->dma << I2C_CR2_DMAEN_Pos;
	config->Port -> CR2 |= config->interrupts << I2C_CR2_ITERREN_Pos;


	//CCR ==> [Tr + Tw]/(1/48000000)
	//TRISE ==> [Tr/(1/48000000)]

	if(config->speed == 400000)
	{
		config->Port -> CR2 |= 30; //42MHz
		config->Port -> CCR = (1<<15) | (1<<14) | 5;
		config->Port -> TRISE = 30;
	}
	else
	{
		config-> Port  -> CR2 = 25;
		config->Port  -> CCR = 0x28;
		config->Port  -> TRISE = 0x8;
	}



	if(config->dma == I2C_DMA.Enable)
	{
		if(config->Port == I2C1)
		{
			xI2C_TX.channel = I2C_DMA_Stream.I2C1_DMA_Channel;
			xI2C_RX.channel = I2C_DMA_Stream.I2C1_DMA_Channel;
			xI2C_TX.stream = I2C_DMA_Stream.I2C1_TX;
			xI2C_RX.stream = I2C_DMA_Stream.I2C1_RX;
		}
		else if(config->Port == I2C2)
		{
			xI2C_RX.channel = I2C_DMA_Stream.I2C2_DMA_Channel;
			xI2C_TX.channel = I2C_DMA_Stream.I2C2_DMA_Channel;
			xI2C_TX.stream = I2C_DMA_Stream.I2C2_TX;
			xI2C_RX.stream = I2C_DMA_Stream.I2C2_RX;
		}
		else if(config->Port == I2C3)
		{
			xI2C_RX.channel = I2C_DMA_Stream.I2C3_DMA_Channel;
			xI2C_TX.channel = I2C_DMA_Stream.I2C3_DMA_Channel;
			xI2C_TX.stream = I2C_DMA_Stream.I2C3_TX;
			xI2C_RX.stream = I2C_DMA_Stream.I2C3_RX;
		}

		xI2C_TX.controller = DMA1;

		xI2C_TX.circular_mode = DMA_Circular_Mode.Disable;
		xI2C_TX.flow_control = DMA_Flow_Control.DMA_Control;
		xI2C_TX.interrupts = DMA_Interrupts.Disable;
		xI2C_TX.memory_data_size = DMA_Memory_Data_Size.byte;
		xI2C_TX.peripheral_data_size = DMA_Peripheral_Data_Size.byte;
		xI2C_TX.priority_level = DMA_Priority_Level.Very_high;
		xI2C_TX.transfer_direction = DMA_Transfer_Direction.Memory_to_peripheral;

		xI2C_RX.controller = DMA1;
		xI2C_RX.circular_mode = DMA_Circular_Mode.Disable;
		xI2C_RX.flow_control = DMA_Flow_Control.DMA_Control;
		xI2C_RX.interrupts = DMA_Interrupts.Disable;
		xI2C_RX.memory_data_size = DMA_Memory_Data_Size.byte;
		xI2C_RX.peripheral_data_size = DMA_Peripheral_Data_Size.byte;
		xI2C_RX.priority_level = DMA_Priority_Level.Very_high;
		xI2C_RX.transfer_direction = DMA_Transfer_Direction.Peripheral_to_memory;
	}

	config -> Port -> CR1 |= I2C_CR1_NOSTRETCH;
	config -> Port -> CR1 |= I2C_CR1_PE;
}

void I2C_Master_Start(I2C_Config *config)
{
	int time_out = 1000;
	config -> Port -> CR1 |= I2C_CR1_START;
	config -> Port -> CR1 |= I2C_CR1_START;
	while( !(config -> Port -> SR1 & I2C_SR1_SB))
	{
		if(time_out == 0)
		{
			return -1;
		}
		time_out--;
	}
	return 0;
}

void I2C_Master_Address(I2C_Config *config, uint8_t address, uint8_t read_write)
{
	volatile int temp;
	config -> Port -> DR = address << 1  | read_write;
	while((config -> Port -> SR1 & 2) == 0){}
	while((config -> Port -> SR1 & 2))
	{
		temp = config -> Port -> SR1;
		temp = config -> Port -> SR2;
		if((config -> Port -> SR1 & 2) == 0)
		{
			break;
		}
	}
}

void I2C_Master_Send_Byte(I2C_Config *config, uint8_t data)
{
	while((config -> Port-> SR1 & 0x80) == 0){}
	config -> Port -> DR = data;
	while((config -> Port -> SR1 & 0x80) == 0){}
}

void I2C_Master_Send_Buffer(I2C_Config *config, uint8_t *data, int length)
{
	if(config->dma == I2C_DMA.Enable)
	{
		xI2C_TX.memory_address = (uint32_t)&data;
		xI2C_TX.buffer_length = length;
		xI2C_TX.peripheral_address = (uint32_t)&I2C1->DR;
		DMA_Set_Target(&xI2C_TX);
		DMA_Trigger(&xI2C_TX);
	}
	for(int i = 0; i < length; i++)
	{
		while((config -> Port -> SR1 & 0x80) == 0){}
		config -> Port -> DR = data[i];
		while((config -> Port -> SR1 & 0x80) == 0){}
	}
}



void I2C_Master_NACK(I2C_Config *config)
{
	config -> Port -> CR1 &= ~I2C_CR1_ACK;
}

void I2C_Master_ACK(I2C_Config *config)
{
	config -> Port -> CR1 |= I2C_CR1_ACK;
}

void I2C_Master_Stop(I2C_Config *config)
{
	config -> Port -> CR1 |= I2C_CR1_STOP;
}

void I2C_Master_Write_Register(I2C_Config *config, uint8_t device_address, uint8_t reg_address, uint8_t data)
{
	I2C_Master_Start(config);
	I2C_Master_Address(config, device_address,0);
	I2C_Master_Send_Byte(config, reg_address);
	I2C_Master_Send_Byte(config, data);
	I2C_Master_Stop(config);
}

int I2C_Master_Read_Register(I2C_Config *config, uint8_t device_address, uint8_t reg_address)
{
	volatile int temp;
	I2C_Master_Start(config);
	I2C_Master_Address(config, device_address, 0);
	I2C_Master_Send_Byte(config, reg_address);
	I2C_Master_Stop(config);
	I2C_Master_Start(config);
	I2C_Master_Address(config, device_address, 1);
	temp = I2C_Master_Receive_Byte(config);
	I2C_Master_Stop(config);
	return temp;
}

int I2C_Master_Receive_Byte(I2C_Config *config)
{
	volatile int temp;
	config -> Port -> CR1 |= I2C_CR1_ACK;
	while((config -> Port -> SR1 & I2C_SR1_RXNE) == 0){}
	temp = config -> Port -> DR;
	config -> Port -> CR1 &= ~I2C_CR1_ACK;
	return temp;
}



void I2C_Master_Write_Register_Block(I2C_Config *config, uint8_t device_address, uint8_t reg_address, uint8_t *data, int length)
{
	I2C_Master_Start(config);
	I2C_Master_Address(config, device_address,0);
	I2C_Master_Send_Byte(config, reg_address);
	I2C_Master_Send_Buffer(config, data, length);
	I2C_Master_Stop(config);
}


