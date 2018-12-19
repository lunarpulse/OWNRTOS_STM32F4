/*
 * osKernel.h
 *
 *  Created on: 17 Dec. 2018
 *      Author: lunarpulse
 */

#ifndef INCLUDE_OSKERNEL_H_
#define INCLUDE_OSKERNEL_H_
#include <stdint.h>

void osKernel_Launch(uint32_t quanta);
void osKernel_Init(void);

uint8_t osKernel_Add_Threads(void(*task0)(void),void(*task1)(void),void(*task2)(void));
void osThread_Yield(void);

uint32_t period0;
uint32_t period1;
uint32_t period2;

extern void PeriodicTask0(void);
extern void PeriodicTask1(void);
extern void PeriodicTask2(void);

#endif /* INCLUDE_OSKERNEL_H_ */
