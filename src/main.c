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

#define QUANTA	10
#define YMAX 5000
#define YMIN 0

volatile uint32_t count0,count1,count2;

unsigned short leds[4]= {GPIO_PIN_12,GPIO_PIN_13,GPIO_PIN_14,GPIO_PIN_15};
volatile unsigned short led = 0;

uint32_t adc_sensorValue;

void drawInfoBar(void);
void drawaxes(void);
void plotData(void);

void Task0(void)
{

	ADC1_Init();
	while(1)
	{
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1, 10);
		adc_sensorValue = HAL_ADC_GetValue(&hadc1);
		count0++;
		osThread_Yield();

	}

}

void Task1(void)
{
	ST7735_Init();
	drawaxes();

	while(1)
	{
		drawInfoBar();
		plotData();
		count1++;
		osThread_Yield();
	}

}

void Task2(void)
{
	while(1)
	{
		count2++;
		osThread_Yield();
	}

}

int
main(int argc, char* argv[])
{
	HAL_Init();

	LED_Init();
	HAL_GPIO_TogglePin(GPIOD,leds[led++%4]);

	TIM2_Init_Start();
	TIM3_Init_Start();
	TIM4_Init_Start();
	//TIM5_Init_Start();

	Probe_Init();

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
extern int counter4;
/*
 * A simple periodic timer with a Timer
 * 500 ms , 1 Hz toggle of LEDs
 */
void TIM4_IRQHandler(void)
{
	//HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_13);
	counter4++;
	//HAL_GPIO_TogglePin(GPIOD,leds[led%4]);
	//HAL_GPIO_TogglePin(GPIOD,leds[(led-1)%4]);
	HAL_GPIO_TogglePin(GPIOD,leds[(led++)%4]);

	HAL_TIM_IRQHandler(&htim4);

}
#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
