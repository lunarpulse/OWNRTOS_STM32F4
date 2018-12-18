  .syntax unified
  .cpu cortex-m4
  .fpu softvfp
  .thumb
  .extern  currentPt
  .global	SysTick_Handler
  .global  osSchedulerLaunch

.align

.section  .text.SysTick_Handler
.type  SysTick_Handler, %function
SysTick_Handler:          @ save r0,r1,r2,r3,r12,lr,pc,psr
    cpsid   i
    push    {r4-r11}        @ SAVE R4,R5,R6,R7,R8,R9,R10,R11
    ldr     r0, =currentPt  @ R0 POINTS TO currentPt
    ldr     r1, [r0]        @ R1= currentPt
    str     sp, [r1]
    ldr     r1, [r1,#4]     @ R1 =currentPt->NEXT
    str     r1, [r0]        @ currentPt =R1
    ldr     sp, [r1]        @ sp= currentPt->STACKpT
    pop     {r4-r11}
    cpsie   i
    bx      lr
.size  SysTick_Handler, .-SysTick_Handler

.section  .text.osSchedulerLaunch
.type  osSchedulerLaunch, %function
osSchedulerLaunch:
    ldr     r0, =currentPt
    ldr     r2, [r0]       @ r2 =currentPt
    ldr     sp, [r2]       @ sp = currentPt->STACKpT
    pop     {r4-r11}
    pop     {r0-r3}
    pop     {r12}
    add     sp,sp,#4
    pop     {lr}
    add     sp,sp,#4
    cpsie   i
    bx      lr
.size  osSchedulerLaunch, .-osSchedulerLaunch

.align
.end
