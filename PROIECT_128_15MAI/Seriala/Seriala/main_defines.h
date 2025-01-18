


#ifndef MAIN_DEFINES_H_
#define MAIN_DEFINES_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <string.h>

#define PORT_LED_RX_USART1	PORTB ///SE APRINDE DUPA CE SE TRANSMITE BUFFERUL DE PE USART0 DIN PUTTY
#define PIN_LED_RX_USART1	PB0
#define PORT_LED_RX_USART0	PORTB
#define PIN_LED_RX_USART0 PB1

#define BAUD 9600
#define MYUBRR (F_CPU/16/BAUD)-1

#define timp_USART0 20
#define timp_USART1 30

//USART 1 ------------------------------------------------------------------
uint16_t flag_start_USART1;
uint16_t contor_start_USART1;
uint16_t flag_stop_USART1;
uint8_t data_UDR1; ///VARIABILA IN CARE LUAM/SALVAM CE ESTE IN REGISTRUL UDR

char buffer_UDR1[16];	///acesta se incarca cu valorile primite de la transmit_sir; dupa ce nu mai primeste acesta activeaza flagul timer_expired
uint8_t cnt_UDR1;



//USART 0 -------------------------------------------------------------------
uint16_t flag_start_USART0; 
uint16_t contor_start_USART0;
uint16_t flag_stop_USART0;
uint8_t data_UDR0; ///variabila in care iau ce e in registrul UDR0

char buffer_UDR0[16]; ///acesta se incarca cu valorile primite de la putty , dupa ce nu mai primeste acesta activeaza flagul time out
uint8_t cnt_UDR0;
char buffer_Tx_USART0[16];

#endif /* MAIN_DEFINES_H_ */