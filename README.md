# OwnRTOS

## Project Description

A simple realtime operating system for ARM M4 architecture

## Inspiration

A RTOS course on udemy only supports keil uvision on windows. Not even using a code base too.
A cross platfrom code is required for this project. 

Share with others and make it opensource.

## Requirements

* eclipse
* eclipse GNU MCU
* ARM ebedded complier tool set
* CMSIS
* Scons (build system) from python package
* MCU board ( STM32F4DISCO)

### Optional

* STM32CUBEMX

## Hardware setup

### STM32F4-DISCO Pin Assignment

PROBE

Probe 0  : PC1

Probe 1	 : PC2

Probe 2  : PC4

Probe 3  : PC5

### ADC

ADC      : PA4


### GLCD ST7735


SCK  			:   PA5

MOSI (SDA)		:   PA7

RS				:	PA4

DC				:	PA3

CS				:	PA2

[ref](https://www.stm32duino.com/viewtopic.php?t=486)

## Source

[Original course](https://www.udemy.com/rtos-building-from-ground-up-on-arm-processors/learn/v4/content)

## Advantages

* no loyalty! totally free for your embedded system.
* Very light
* Customisable

## Limitation

* No supporting for Percepio Tracer or system view from Jagger yet
* No queue yet -> Atomic Circular buffer will come in.
* Only C and GNU Assembly code, C++ will come in the scope too.
 
