/*
 * main_mcu_init.c
 *
 *  Author: Asus
 */ 

#include "main_mcu_init.h"


void init_data_contor(void){
	lcd_data_dir = 0xFF;	//pin D4-D7
	lcd_pin_dir = 0xFF;	//pin D4-D7
	//contor_sec_1 = timp_sec_1;
}

// 
// void init_timer(void)
// {
// 	cli();
// 
// 	timer0_init();
// 	
// 	sei();
// }



//Pentru registrii timerului
// void timer0_init(void){
// 	
// 	TCCR0A |= (1 << WGM01);
// 	
// 	TCCR0B |= (0 << CS02)|(1 << CS01)|(1 << CS00);
// 
// 	OCR0A = 0xF9;
// 	
// 	TIMSK0 |= 1 << OCIE0A;
// }

