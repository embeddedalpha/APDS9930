#include "main.h"
#include "Console.h"
#include "GPIO.h"
#include "APDS9930.h"

APDS9930 ALSensor;


#define Nominal_Brightness 50

int Brightness = 0;

int flag = 0;

void LED_Init();
void LED_Brightness_Update(int brightness);

void EXTI0_IRQHandler(void)
{
		APDS9930_Get_Lux(&ALSensor);
		EXTI->PR |= EXTI_PR_PR0;
		APDS9930_Proximity_Interrupt_Clear(&ALSensor);
		flag = 1;
		if(ALSensor.Lux_Data < 10)
		{
			Brightness = 0;
			LED_Brightness_Update(0);
		}
		else if(ALSensor.Lux_Data < 279)
		{
			Brightness = 25;
			LED_Brightness_Update(25);
		}
		else if(ALSensor.Lux_Data < 540)
		{
			Brightness = 50;
			LED_Brightness_Update(50);
		}
		else if( ALSensor.Lux_Data < 880)
		{
			Brightness = 75;
			LED_Brightness_Update(75);
		}
		else
		{
			Brightness = 100;
			LED_Brightness_Update(100);
		}

}

int Automatic_Display_Brightness(void)
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
	LED_Init();



    /* Loop forever */
	for(;;)
	{

		if(flag == 1)
		{
			printConsole("LUX Level = %f, Brightness = %d \r\n",ALSensor.Lux_Data,Brightness);
			flag = 0;
		}
	}

}

void LED_Init()
{

	GPIO_Pin_Init(GPIOD, 12, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.Pull_Up, Alternate_Functions.TIM_4);
	RCC -> APB1ENR |= RCC_APB1ENR_TIM4EN;
	TIM4 -> ARR = 100;
	TIM4 -> CCR1 = Nominal_Brightness;
	TIM4 -> CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2|TIM_CCMR1_OC1PE;
	TIM4 -> BDTR |= TIM_BDTR_MOE;
	TIM4 -> CCER |= TIM_CCER_CC1E;
	TIM4 -> CR1 |= TIM_CR1_ARPE;
	TIM4 -> EGR |= TIM_EGR_UG;
	TIM4 -> CR1 |= TIM_CR1_CEN;
}

void LED_Brightness_Update(int brightness)
{
	TIM4 -> CCR1 = brightness;
}
