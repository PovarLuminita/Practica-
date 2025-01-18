/*
 * USART_slave.h
 *
 * Created: 18/07/2023 15:08:55
 *  Author: Luminita
 */ 


#ifndef USART_SLAVE_H_
#define USART_SLAVE_H_


#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <string.h>

#define PORT_TX	PORTB
#define PIN_TX 	PB0
#define TIMER_RX_USART 30


uint16_t FLAG_START_TIMER_USART;
uint16_t FLAG_STOP_TIMER_USART;


uint16_t CONTOR_RX_TIMER_USART;

uint8_t data;


typedef struct{
	uint8_t CONTOR_BUFFER_USART;
	char BUFFER_RX_USART[16];
	
}USART_slave;

extern USART_slave p_usart0;

void init_porturi(void); ///porturi de intrare/iesire
void init_devices(void); ///folosim cli; sei;
void USART_Init(unsigned int ubrr);
void init_data(void);
void timer0_init(void);


void pinToggle(volatile uint8_t *port, uint8_t pin);
void pinSet(volatile uint8_t *port, uint8_t pin);
void pinReset(volatile uint8_t *port, uint8_t pin);

ISR(USART_RX_vect);
ISR(TIMER0_COMPA_vect);

void USART0_TX_SIR_SIZE(USART_slave *p0);
void USART0_TX_CHAR(unsigned char data);


#endif /* USART_SLAVE_H_ */