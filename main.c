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

// FUNCTION DECLARATIONS -----------------------------------------------------|

void main(void);                                                  //COMPULSORY
void init_LCD(void);
void display_on_LCD(uint8_t number); 
void init_LEDs(void);
void display_on_LEDs(uint8_t number);
void delay();
void init_switches(void);

// MAIN FUNCTION -------------------------------------------------------------|

void main(void){

}

// OTHER FUNCTIONS -----------------------------------------------------------|
void display_on_LCD(uint8_t number){
	lcd_command(CLEAR);
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
	GPIOA -> MODER &= ~(GPIO_MODER_MODER1 | GPIO_MODER_MODER2);
	//enable pull-up resistors//
	GPIOA -> PUPDR |= (GPIO_PUPDR_PUPDR1_0 | GPIO_PUPDR_PUPDR2_0);
}
