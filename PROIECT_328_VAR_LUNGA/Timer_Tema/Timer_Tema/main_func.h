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
#include <string.h>

//INITIALIZARI
void init_Porturi(void); ///porturi de intrare/iesire
void init_Devices(void); ///folosim cli; sei;
void Init_USART0(unsigned int ubrr);

void pinToggle(volatile uint8_t *port, uint8_t pin);
void pinSet(volatile uint8_t *port, uint8_t pin);
void pinReset(volatile uint8_t *port, uint8_t pin);

///FUNCTII TRANSMITERE
void USART0_tx_sir_size(char *string, int size); //ia un sir de caractere (STRING) si extrage pe rand fiecare caracter in parte
void USART0_tx_char(unsigned char data);
void Receptie_Transmisie_usart0(void);

///INTRERUPERE RECEPTIE 328p
ISR(USART_RX_vect);

ISR(TIMER0_COMP_vect);

void init_Contor(void);
void init_Timer0(void);
void afiseaza();
void init_lcd (void); //pentru initializare lcd
void lcd_command( unsigned char cmnd );
void lcd_clear();
void lcd_print (char *str,int size); // char str[]
void lcd_setCursor(void);




#endif /* MAIN_FUNC_H_ */