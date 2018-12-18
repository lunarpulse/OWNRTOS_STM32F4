/*
 * osKernel.c
 *
 *  Created on: 17 Dec. 2018
 *      Author: lunarpulse
 */

#include "stm32f4xx.h"
#include "osKernel.h"

#define SYSPRI3 		        (*((volatile uint32_t *)0xE000ED20))
#define SYSTICK_INT_CNTL        (*((volatile uint32_t *)0xE000ED04))

#define NUM_THREADS 	3
#define STACK_SIZE 		100
#define BUS_FREQ 		16000000
uint32_t millisPrescaler;


struct tcb{
	int32_t  * stackPt;
	struct tcb *nextPt;
};

typedef struct tcb tcb_t;
tcb_t tcbs[NUM_THREADS];
tcb_t *currentPt;

int32_t TCB_STACK[NUM_THREADS][STACK_SIZE];

extern void osSchedulerLaunch(void); //from osKernelAS.S

void osKernel_Stack_Init(int i){ //argument i is thread number
	tcbs[i].stackPt = &TCB_STACK[i][STACK_SIZE-16];
	TCB_STACK[i][STACK_SIZE-1] = 0x01000000; //XPR
}
uint8_t osKernel_Add_Threads(
		void(*task0)(void),
		void(*task1)(void),
		void(*task2)(void)){
	asm("cpsid i" : /* Outputs */
				: /* Inputs */
				: "memory" /* Clobbers */);
	tcbs[0].nextPt = &tcbs[1];
	tcbs[1].nextPt = &tcbs[2];
	tcbs[2].nextPt = &tcbs[0];
	osKernel_Stack_Init(0);
	TCB_STACK[0][STACK_SIZE-2] = (int32_t)(task0); //PC
	osKernel_Stack_Init(1);
	TCB_STACK[1][STACK_SIZE-2] = (int32_t)(task1); //PC
	osKernel_Stack_Init(2);
	TCB_STACK[2][STACK_SIZE-2] = (int32_t)(task2); //PC

	currentPt = &tcbs[0];

	asm("cpsie i" : /* Outputs */
			: /* Inputs */
			: "memory" /* Clobbers */);

	return 1;
}
void osKernel_Init(void){
	asm("cpsid i" : /* Outputs */
			: /* Inputs */
			: "memory" /* Clobbers */);

	millisPrescaler	= BUS_FREQ/1000;

	//asm("cpsie i" : : : "memory");

}

void osKernel_Launch(uint32_t quanta){
	SysTick->CTRL = 0;
	SysTick->VAL = 0;
	SYSPRI3 = (SYSPRI3 & 0x00FFFFFF) | 0xE0000000; // priority 7
	SysTick->LOAD= (quanta*millisPrescaler) - 1;
	SysTick->CTRL = 0x00000007;
	osSchedulerLaunch();
}
void osThread_Yield(void){
	SYSTICK_INT_CNTL = 0x04000000; //Trigger SysTick Interrupt
}
/*
void SysTick_Handler (void) //  save r0,r1,r2,r3,r12,lr,pc,psr
{
	__asm volatile (
		"cpsid   i               \n"
		"push    {r4-r11}        \n" //  save r4,r5,r6,r7,r8,r9,r10,r11
		"ldr     r0, =currentPt  \n" //  r0 points to currentPt
		"ldr     r1, [r0]        \n" //  r1= currentPt
		"str     sp, [r1]        \n"
		"ldr     r1, [r1,#4]     \n" //  r1 =currentPt->next
		"str     r1, [r0]        \n" //  currentPt =r1
		"ldr     sp, [r1]        \n" //  sp= currentPt->stackPt
		"pop     {r4-r11}        \n"
		"cpsie   i               \n"
		"bx      lr              \n"
		: // Outputs
	    : // Inputs
	    : // Clobbers
			);
}

void osSchedulerLaunch(void){
	__asm volatile (
		"ldr     r0, =currentPt \n"
		"ldr     r2, [r0]       \n" // r2 =currentPt
		"ldr     sp, [r2]       \n" //  sp = currentPt->stackPt
		"pop     {r4-r11}       \n"
		"pop     {r0-r3}        \n"
		"pop     {r12}          \n"
		"add     sp,sp,#4       \n"
		"pop     {lr}           \n"
		"add     sp,sp,#4       \n"
		"cpsie   i              \n"
		"bx      lr             \n"
		: // Outputs
		: // Inputs
		: // Clobbers
			);
}
*/
