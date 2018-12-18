// ----------------------------------------------------------------------------
/*
#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "Timer.h"
#include "BlinkLed.h"
*/
#include "osKernel.h"

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

#define QUANTA	10

volatile uint32_t count0,count1,count2;

void Task0(void)
{
	while(1)
	{
		count0++;
		osThread_Yield();
	}

}

void Task1(void)
{
	while(1)
	{
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
	osKernel_Init();
	osKernel_Add_Threads(&Task0,&Task1,&Task2);
	osKernel_Launch(QUANTA);

}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
