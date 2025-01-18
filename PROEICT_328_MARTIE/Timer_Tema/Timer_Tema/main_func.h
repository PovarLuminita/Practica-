/*
 * main_func.h
 *
 *  Author: Asus
 */ 


#ifndef MAIN_FUNC_H_
#define MAIN_FUNC_H_

#include "main_config.h"
#include "main_defines.h"

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

void init_data(void);
//ISR(TIMER0_COMP_vect);

void afiseaza();
void initialize (void); //pentru initializare lcd
void lcd_command( unsigned char cmnd );
void lcd_clear();
void lcd_print (char *str); // char str[]
void lcd_setCursor(void);

// void init_data_contor(void); //pt a lua contorul valoarea timpului
// void timer0_init(void);
// void init_timer(void);



#endif /* MAIN_FUNC_H_ */