


#ifndef MAIN_FUNC_H_
#define MAIN_FUNC_H_

#include "main_config.h"
#include "main_defines.h"

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

///INTRERUPERE PENTRU TIMER
ISR(TIMER0_OVF_vect);

///FUNCTII TRANSMITERE
void USART1_Tx_size(char *string, int size); //ia un sir de caractere (STRING) si extrage pe rand fiecare caracter in parte
void USART1_Tx_char(unsigned char data);

void USART0_Tx(char *string); //ia un sir de caractere si extrage pe rand fiecare caracter in parte
void USART0_Tx_char(unsigned char data);
void USART0_Tx_size(char *string, int size);

///INTRERUPERE RECEPTIE 128
ISR(USART1_RX_vect);
ISR(USART0_RX_vect);

void pinToggle(volatile uint8_t *port, uint8_t pin);
void pinSet(volatile uint8_t *port, uint8_t pin);
void pinReset(volatile uint8_t *port, uint8_t pin);

#endif /* MAIN_FUNC_H_ */