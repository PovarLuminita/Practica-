/*
 * main_mcu_init.c
 *
 *  Author: Asus
 */ 

#include "main_mcu_init.h"

void initializare_porturi(void)
{
	DDRB  = 0xFF; // output
	PORTB  = 0x00; // low
	
	DDRC  = 0x7F;
	PORTC = 0x00;
	
	DDRD  = 0xFF;
	PORTD = 0x00;
}

void initializare_devices(void)
{
	cli();
	initializare_porturi();
	timer0_init();
	sei();
}


void USART_Initializare_registrii(unsigned int ubrr)
{
	//set baud rate
	UBRR0H = (unsigned char) (ubrr>>8);
	UBRR0L = (unsigned char) ubrr;
	
	UCSR0B = 0x00;
	UCSR0C = 0x00;
	
	//activ doar sa transmita si sa primeasca
	UCSR0B |= (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0);
	
	//setez frame format : 8 data , 1 bit stop
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
	
	//enable global interrupts
	set_sleep_mode(SLEEP_MODE_IDLE);
	sei();
}




void timer0_init(void){
	//Put Timer0 in CTC Mode, no compare match output
	TCCR0A |= (1 << WGM01);
	
	//Set the prescaler. This will divide the input frequency by 64
	TCCR0B |= (0 << CS02)|(1 << CS01)|(1 << CS00);

	//The output frequency if Fclock / prescaler / OCR.
	OCR0A = 0xF9; //249
	
	//Enable Timer/Counter Output Compare Match Interrupt
	TIMSK0 |= 1 << OCIE0A;
}


void init_data(void){
	contor_rx = timp_rx;
}


void init_data_contor(void){
	lcd_data_dir = 0xFF;	//pin D4-D7
	lcd_pin_dir = 0xFF;	//pin D4-D7
}



