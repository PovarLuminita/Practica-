/*
 * main_mcu_init.c
 *
 *  Author: Asus
 */ 



#include "main_mcu_init.h"


void init_data_contor(void){
	contor_sec_1 = timp_sec_1;
}


void init_timer(void)
{
	cli();
	//port_init();
	timer0_init();
	
	sei();
}



//Pentru registrii timerului
void timer0_init(void){
	
	TCCR0A |= (1 << WGM01);
	
	TCCR0B |= (0 << CS02)|(1 << CS01)|(1 << CS00);

	OCR0A = 0xF9;
	
	TIMSK0 |= 1 << OCIE0A;
}



void port_init(void)
{
	DDRB  = 0xFF;
	PORTB  = 0x00;

	DDRC  = 0x7F;
	PORTC = 0x00;

	DDRD  = 0xFF;
	PORTD = 0x00;
}