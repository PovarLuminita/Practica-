/*
 * main_defines.h
 *
 *  Author: Asus
 */ 


#ifndef MAIN_DEFINES_H_
#define MAIN_DEFINES_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

#define lcd_port_pin PORTD			    //Define LCD Port
#define lcd_port PORTC
#define lcd_pin_dir  DDRD
#define lcd_data_dir  DDRC			//PD4-PD7 PORT D - pe 4 biti
#define rs PC1			//RS Pin
#define en PC2 			//E Pin

#define PORT_LED_tx	PORTB	///CAND ESTE UN CARACTER PRIMIT DE LA 128 ATUNCI SE APRINDE UN LED!
#define PIN_LED_tx 	PB0

///BAUD RATE
#define BAUD 9600
#define MYUBRR (F_CPU/16/BAUD)-1

#define timp_usart0 30
uint16_t contor_timp_usart0;
uint16_t flag_start_usart0;
uint16_t flag_stop_usart0;

uint8_t data_udr0; ///VARIABILA IN CARE LUAM/SALVAM CE ESTE IN REGISTRUL UDR
uint8_t inc_usart0; ///INCREMENTEAZA CATE CARACTERE SUNT PRIMITE

///buffer_rx_usart0 pentru a lua ce transmite transmit_buffer_rx_usart0
char buffer_rx_usart0[16];	///acesta se incarca cu valorile primite de la transmit_sir; dupa ce nu mai primeste acesta activeaza flagul timer_expired
char buffer_rx_usart0_copy[20]; ///ia ce se transmite de pe usart0 si mai adauga ceva in plus

#endif /* MAIN_DEFINES_H_ */