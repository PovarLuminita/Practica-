

#ifndef MAIN_DEFINES_H_
#define MAIN_DEFINES_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

#define PORT_LED_TX_USART1	PORTB ///SE APRINDE DUPA CE SE TRANSMITE BUFFERUL
#define PIN_LED_TX_USART1	PB0
#define PORT_LED_TX_USART0	PORTB
#define PIN_LED_TX_USART0 PB1

#define BAUD 9600
#define MYUBRR (F_CPU/16/BAUD)-1

#define timp_usart0 20
#define timp_usart1 30
uint16_t contor_usart1;
uint16_t contor_usart0;
uint16_t flag_start_usart1;
uint16_t flag_stop_usart1;

uint8_t data; ///VARIABILA IN CARE LUAM/SALVAM CE ESTE IN REGISTRUL UDR


///FLAGURI SEMNALIZARE
uint8_t cnt_usart1;
uint8_t cnt_usart0;
uint16_t flag_start_usart0; //flag pentru usart0
uint16_t flag_stop_usart0;

char buffer_usart1[16];	///acesta se incarca cu valorile primite de la transmit_sir; dupa ce nu mai primeste acesta activeaza flagul timer_expired
char buffer_usart0[16]; ///acesta se incarca cu valorile primite de la putty , dupa ce nu mai primeste acesta activeaza flagul time out
char buffer_transfer_usart0[16];


#endif /* MAIN_DEFINES_H_ */