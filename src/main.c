// ----------------------------------------------------------------------------
/*
#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "Timer.h"
#include "BlinkLed.h"
*/
#include "osKernel.h"
#include "STM32F4_RTOS_BSP.h"

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

#define QUANTA	250
#define YMAX 5000
#define YMIN 0

volatile uint32_t count0,count1,count2;
int32_t binarySemaphore0,binarySemaphore1;

uint32_t adc_sensorValue;

void drawInfoBar(void);
void drawaxes(void);
void plotData(void);

void Task0(void)
{

	ADC1_Init();
	while(1)
	{
		GPIOD->ODR ^= GPIO_PIN_12;
		HAL_ADC_Start(&hadc1);
		GPIOD->ODR ^= GPIO_PIN_13;
		HAL_ADC_PollForConversion(&hadc1, 10);
		GPIOD->ODR ^= GPIO_PIN_14;
		adc_sensorValue = HAL_ADC_GetValue(&hadc1);
		count0++;
		GPIOD->ODR ^= GPIO_PIN_15;
		osThread_Yield();

	}

}
static volatile int ST7735Inited = 0;
void Task1(void)
{
	ST7735Inited = ST7735_Init();
	GPIOD->ODR ^= GPIO_PIN_14;
	while(1)
	{
		GPIOD->ODR ^= GPIO_PIN_12;

		osBinarySemaphore_Signal_Set(&binarySemaphore0);

		osBinarySemaphore_Signal_Wait(&binarySemaphore1);
		GPIOD->ODR ^= GPIO_PIN_14;
		//ST7735_DrawString(3, 7, "####This is Task 1####", GREEN);
		count1++;
	}

}

void Task2(void)
{
	while(!ST7735Inited){
		osThread_Yield();
	}
	while(1)
	{
		GPIOD->ODR ^= GPIO_PIN_13;

		osBinarySemaphore_Signal_Set(&binarySemaphore1);

		osBinarySemaphore_Signal_Wait(&binarySemaphore0);
		GPIOD->ODR ^= GPIO_PIN_15;
		//ST7735_DrawString(3, 7, "####This is Task 2####", BLUE);
		count2++;
	}

}

int
main(int argc, char* argv[])
{
	HAL_Init();

	TIM2_Init_Start();
	TIM3_Init_Start();
	TIM4_Init_Start();

	LED_Init();


	Probe_Init();

	osBinarySemaphore_Init(&binarySemaphore0,0);
	osBinarySemaphore_Init(&binarySemaphore1,0);

	osKernel_Init();
	osKernel_Add_Threads(&Task0,&Task1,&Task2);
	osKernel_Launch(QUANTA);

}


void drawInfoBar(void)
{
	ST7735_DrawString(1,0,"CPU =", GREEN);
	ST7735_DrawString(7, 0, "75%", BLUE );
	ST7735_DrawString(11, 0, "Temp =", GREEN);
	ST7735_DrawString(18, 0, "30", BLUE );


}

void drawaxes(void)
{
	ST7735_Drawaxes(AXISCOLOR, BGCOLOR, "Time", "ADC", LIGHTGREEN, "", 0, YMAX, YMIN);

}

void plotData(void)
{
	ST7735_PlotPoint(adc_sensorValue,GREEN);
	ST7735_PlotIncrement();
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
