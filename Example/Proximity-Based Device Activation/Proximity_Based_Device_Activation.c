#include "main.h"
#include "Console.h"
#include "GPIO.h"
#include "APDS9930.h"

APDS9930 ALSensor;


int flag = 0;


void EXTI0_IRQHandler(void)
{
		APDS9930_Get_Proximity(&ALSensor);
		EXTI->PR |= EXTI_PR_PR0;
		APDS9930_Proximity_Interrupt_Clear(&ALSensor);
		if(ALSensor->Proximity_Data >= 50 || ALSensor->Proximity_Data <= 200)
		{
			flag = 1;
		}

}

int Proximity_Based_Device_Activation(void)
{

	MCU_Clock_Setup();
	Delay_Config();
	Console_Init(USART1, 256000);

	APDS9930_DeInit(&ALSensor);

	ALSensor.Port = I2C1;
	ALSensor.SCL_Pin = I2C1_SCL_Pin.PB8;
	ALSensor.SDA_Pin = I2C1_SDA_Pin.PB9;
	ALSensor.Interrupt_Port = GPIOA;
	ALSensor.Interrupt_Pin = 0;
	ALSensor.Proximity_Interrupt_Enable = true;
	APDS9930_Init(&ALSensor);




    /* Loop forever */
	for(;;)
	{

		if(flag == 1)
		{
			printConsole("Object Triggered \r\n");
			flag = 0;
		}
	}

}

