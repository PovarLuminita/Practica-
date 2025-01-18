
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define PORT_LED1 PORTD
#define PIN_LED1  PIND4
#define PORT_LED2 PORTD
#define PIN_LED2  PIND5
#define PORT_LED3 PORTD
#define PIN_LED3 PIND6

#define timp_led_1 50
#define timp_led_2 500
#define timp_led_3 1000 ///daca am aici 1000ms si se activeaza intreruperea la 1ms --->
						/// ----> asa stiu ca a trecut o secunda

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

///TREBUIE uint16_t pentru ca avem nevoie sa numere peste 255.
///uint8 are valori intre 0 si 256
///uint16 are valori intre 0 si 2^16 = 65535
uint16_t contor_led_1 =0; 
uint16_t contor_led_2 = 0;
uint16_t contor_led_3 = 0;

uint8_t flag_led_1 = 0; 
uint8_t flag_led_2 = 0;
uint8_t flag_led_3 = 0;

int main(void)
{
	init_devices();
	do{
		aprinde_led_1();
		aprinde_led_2();
		aprinde_led_3();
	}
	while(1);
}

void init_devices(void)
{
	cli();
	port_init();
	timer0_init();
	sei();
}

void port_init(void)
{
	DDRD  = 0xFF; // OUTPUT
	PORTD = 0x00; //LOW
}

void timer0_init(void){
	//MOD CTC 
	/*
	Este un mod mai bun decat cel normal pentru a genera semnal dreptunghiular deoarece
	frecventa semnalului poate fi ajustata usor folosind registrul OCR0A
	*/
	TCCR0A |= (1 << WGM01);
	
	//PRESCALARUL. VA IMPARTI FRECVENTA DE LA INTRARE.
	TCCR0B |= (0 << CS02)|(1 << CS01)|(1 << CS00); ///64

	//The output frequency if Fclock / prescaler / OCR.
	OCR0A = 0xF9; //249
	
	//ACTIVEZ INTRERUPEREA TIMER
	TIMSK0 |= 1 << OCIE0A;
}

void pinToggle(volatile uint8_t *port, uint8_t pin){
	*port ^=  1 << pin;
}

// TIMER de 1000Hz. 
//ACEASTA INTRERUPERE VA FI GENERATA LA FIECARE 1ms
ISR(TIMER0_COMPA_vect){
	
	contor_led_1++;
	contor_led_2++;
	contor_led_3++;
	
	if(contor_led_1 == timp_led_1){
		flag_led_1 = 1;
		contor_led_1 =  0;
	}
	
	if(contor_led_2 == timp_led_2){
		flag_led_2 = 1;
		contor_led_2 =  0;
	}
	
	if(contor_led_3 == timp_led_3){
		flag_led_3 = 1;
		contor_led_3 =  0;
	}
	
	
}

void aprinde_led_1()
{
	if(flag_led_1 == 1 )
	{
		pinToggle(&PORT_LED1, PIN_LED1);
		flag_led_1 = 0;
	}
}

void aprinde_led_2()
{
	if(flag_led_2 == 1 )
	{
		pinToggle(&PORT_LED2, PIN_LED2);
		flag_led_2 = 0;
	}
}


void aprinde_led_3()
{
	if(flag_led_3 == 1 )
	{
		pinToggle(&PORT_LED3, PIN_LED3);
		flag_led_3 = 0;
	}
}

