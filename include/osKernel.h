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

void osBinarySemaphore_Init(int32_t * semaphore, int32_t value);
void osBinarySemaphore_Signal_Wait(int32_t * semaphore);
void osBinarySemaphore_Signal_Set(int32_t * semaphore);

void osBinaryCooperativeSemaphore_Init(int32_t * semaphore, int32_t value);
void osBinaryCooperativeSemaphore_Signal_Wait(int32_t * semaphore);
void osBinaryCooperativeSemaphore_Signal_Set(int32_t * semaphore);

#endif /* INCLUDE_OSKERNEL_H_ */
