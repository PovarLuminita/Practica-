/*
 * USART_slave.c
 *
 * Created: 18/07/2023 15:08:44
 *  Author: Luminita
 */ 

#include "USART_slave.h"

USART_slave p_usart0;

ISR(USART_RX_vect)
{
	p_usart0.BUFFER_RX_USART[p_usart0.CONTOR_BUFFER_USART] = UDR0;
	FLAG_START_TIMER_USART = 1;
	p_usart0.CONTOR_BUFFER_USART++;
}



void USART0_TX_SIR_SIZE(USART_slave *p0){
	
	for(int i = 0; i < p0->CONTOR_BUFFER_USART; i++)
	{
		USART0_TX_CHAR(p0->BUFFER_RX_USART[i]);
	}
	
}


void USART0_TX_CHAR(unsigned char data){
	while(!(UCSR0A &(1<<UDRE0))); //astept pana se goleste bufferul de transmitere
	UDR0 = data; //pun datele in buffer(registru), trimit datele
	
}



void USART_Init(unsigned int ubrr)
{
	UBRR0H = (unsigned char) (ubrr>>8);
	UBRR0L = (unsigned char) ubrr;
	
	UCSR0B = 0x00;
	UCSR0C = 0x00;
	
	UCSR0B |= (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0);
	
	//8 data , 1 bit stop
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
	
	
}


void init_data(void){
	CONTOR_RX_TIMER_USART = TIMER_RX_USART ;
}


ISR(TIMER0_COMPA_vect){
	if(FLAG_START_TIMER_USART == 1){
		CONTOR_RX_TIMER_USART--;
	}
	
	if(CONTOR_RX_TIMER_USART == 0){
		FLAG_STOP_TIMER_USART = 1;
		CONTOR_RX_TIMER_USART = TIMER_RX_USART;
	}

}



void timer0_init(void){
	TCCR0A |= (1 << WGM01);
	
	TCCR0B |= (0 << CS02)|(1 << CS01)|(1 << CS00);

	OCR0A = 0xF9; //249
	
	TIMSK0 |= 1 << OCIE0A;
}


void init_porturi(void)
{
	DDRB  = 0xFF; // output
	PORTB  = 0x00; // low
	
	DDRC  = 0x7F;
	PORTC = 0x00;
	
	DDRD  = 0xFF;
	PORTD = 0x00;
}

void init_devices(void)
{
	cli();
	init_porturi();
	timer0_init();
	sei();
}