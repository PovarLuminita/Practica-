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

void initialize (void); //pentru initializare lcd
void lcd_command( unsigned char cmnd );
void lcd_clear();
void lcd_print (char *str); // char str[]
//void lcd_setCursor(unsigned char x, unsigned char y);
void lcd_setCursor(void);
void init_data_contor(void); //pt a lua contorul valoarea timpului
void timer0_init(void);
void init_timer(void);
void afiseaza();
void port_init(void);
void init_data(void);

void pinToggle(volatile uint8_t *port, uint8_t pin);
void pinSet(volatile uint8_t *port, uint8_t pin);
void pinReset(volatile uint8_t *port, uint8_t pin);

void aprinde_led_1();

ISR(TIMER0_COMP_vect);



#endif /* MAIN_FUNC_H_ */