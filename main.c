// Description----------------------------------------------------------------|
/*
 *
 */
// DEFINES AND INCLUDES-------------------------------------------------------|

#define STM32F051												   //COMPULSORY
#include "stm32f0xx.h"											   //COMPULSORY
#include "lcd_stm32f0.h"
#include <stdio.h>

// GLOBAL VARIABLES ----------------------------------------------------------|
uint8_t selection = 0;

// FUNCTION DECLARATIONS -----------------------------------------------------|

void main(void);                                                   //COMPULSORY
void init_LEDs(void);
void init_LCD(void);
void delay();
void display_on_LCD(uint8_t number);
void display_on_LEDs(uint8_t number);
void init_switches(void);
void init_external_interrupts(void);

// MAIN FUNCTION -------------------------------------------------------------|

void main(void){
	init_LEDs();
	init_LCD();
	init_switches();
	init_external_interrupts();

	uint8_t count = 0;

	while(1){
		if((selection%2) != 0){
			if((GPIOA -> IDR & GPIO_IDR_1) == 0){
				if(count < 255){
					count++;
				}
				else{
					count = count;
				}
				lcd_command(CLEAR);
				display_on_LCD(count);
				display_on_LEDs(count);
				delay(50000);
				}
			else if((GPIOA -> IDR & GPIO_IDR_2) == 0){
				if(count <= 0){
					count = count;
				}
				else{
					count--;
				}
				lcd_command(CLEAR);
				display_on_LCD(count);
				display_on_LEDs(count);
				delay(50000);
			}
		}
		else{
			count = 0;
			lcd_command(CLEAR);
			display_on_LEDs(count);
		}
	}
}

// OTHER FUNCTIONS -----------------------------------------------------------|
void display_on_LCD(uint8_t number){
	//creates array to store number in binary//
	char num_string[3];
	//converts number from int to char and stores it in array//
	sprintf(num_string, "%d", number);
	lcd_putstring(num_string);
}

void init_LEDs(void){
	//enable clock for port B//
	RCC -> AHBENR |= RCC_AHBENR_GPIOBEN;
	//sets mode of pins 0-7 to output//
	GPIOB -> MODER |= 0b0101010101010101;
}

void display_on_LEDs(uint8_t number){
	GPIOB -> ODR = number;
}

void init_switches(void){
	//enables clock for port A//
	RCC -> AHBENR |= RCC_AHBENR_GPIOAEN;
	//sets pins 1 an 2 to input mode//
	GPIOA -> MODER &= ~(GPIO_MODER_MODER1 | GPIO_MODER_MODER2 | GPIO_MODER_MODER3);
	//enable pull-up resistors//
	GPIOA -> PUPDR |= (GPIO_PUPDR_PUPDR1_0 | GPIO_PUPDR_PUPDR2_0 | GPIO_PUPDR_PUPDR3_0);
}

void init_external_interrupts(void){
	RCC -> APB2ENR |= RCC_APB2ENR_SYSCFGCOMPEN;
	SYSCFG -> EXTICR[2] |= SYSCFG_EXTICR1_EXTI3_PA;
	EXTI -> IMR |= EXTI_IMR_MR3;
	EXTI -> FTSR |= EXTI_FTSR_TR3;
	NVIC_EnableIRQ(EXTI2_3_IRQn);
}

void EXTI2_3_IRQHandler(void){
	EXTI -> PR &= EXTI_PR_PR3;
	selection++;
	delay(50000);
}
