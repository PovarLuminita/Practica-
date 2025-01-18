/*
-proiect luna mai 2023
----------------------------------------------------------------------
*/


//328p COMUNICARE PROIECT OFICIAL 
///ACESTA ESTE SLAVE!!!!!
#include "main_config.h"
#include "main_defines.h"
#include "main_func.h"
#include "main_mcu_init.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdio.h>

#define PORT_LED_328	PORTB	///CAND ESTE UN CARACTER PRIMIT DE LA 128 ATUNCI SE APRINDE UN LED!
#define PIN_LED_328 	PB0

///BAUD RATE
#define BAUD 9600
#define MYUBRR (F_CPU/16/BAUD)-1

uint8_t data; ///VARIABILA IN CARE LUAM/SALVAM CE ESTE IN REGISTRUL UDR
uint8_t inc_ch = 0 ; ///INCREMENTEAZA CATE CARACTERE SUNT PRIMITE

///FLAGURI SEMNALIZARE
uint8_t flag_rx = 0; //flag care se activeaza in intreruperea rx dupa ce a primit un caracter

///buffer pentru a lua ce transmite transmit_buffer
char buffer[16] = {};	///acesta se incarca cu valorile primite de la transmit_sir; dupa ce nu mai primeste acesta activeaza flagul timer_expired
char buffer_copy[20] = {}; ///ia ce se transmite de pe usart0 si mai adauga ceva in plus
int copy = 0; //vreau sa incrementez de fiecare data cand primesc ceva de la usart0
//INITIALIZARI
void initializare_porturi(void); ///porturi de intrare/iesire
void initializare_devices(void); ///folosim cli; sei;
void USART_Initializare_registrii(unsigned int ubrr);

void pinToggle(volatile uint8_t *port, uint8_t pin);
void pinSet(volatile uint8_t *port, uint8_t pin);
void pinReset(volatile uint8_t *port, uint8_t pin);

///FUNCTII TRANSMITERE
void USART_Transmit_sir(char *string, int size); //ia un sir de caractere (STRING) si extrage pe rand fiecare caracter in parte
void USART_Transmit_caracter(unsigned char data);
void receive(void);

///INTRERUPERE RECEPTIE 328p
ISR(USART_RX_vect);

ISR(TIMER0_COMP_vect);

void init_data(void);
void timer0_init(void);
#define timp_rx 30
uint16_t contor_rx;
uint16_t flag_start_timer = 0;
uint16_t flag_stop = 0;

///------------------------- COD ---------------------------------------------------------------------

int main(void)
{
	initialize();
	initializare_devices();
	USART_Initializare_registrii(MYUBRR);
	
	
	lcd_clear();
	lcd_setCursor();
	pinReset(&PORT_LED_328, PIN_LED_328);
	
	do
	{	
		receive();
	}
	while(1);
	
	return 0;
}


ISR(USART_RX_vect)
{
	//CITESC DATE DIN REGISTRU
	buffer[inc_ch] = UDR0;
	flag_start_timer = 1;
	
	inc_ch++;	///incrementez pozitia
	
}

void USART_Transmit_caracter(unsigned char data)
{
	//astept sa se goleasca bufferul de transmitere
	while(!(UCSR0A &(1<<UDRE0)));
	
	//pun date in registru, trimit datele
	UDR0 = data;//scriu in registru
}


///IN LOC DE WHILE SA PUN CONDITIE DE LUNGIME A SIRULUI SAU SA DAU VALOAREA MAX A POZITIEI ULTIMULUI CARACTER DIN TRANSMITERE TX
void USART_Transmit_sir(char *string, int size)
{
	//luam un sir de caractere si extrage cate un caracter pe rand, pana la terminarea sirului
	// pointam la fiecare caracter din string, pornind de la primul, folosind incrementarea indexului
	for(int i = 0; i < size; i++)
	{
		
		USART_Transmit_caracter(string[i]); ///II TRANSMIT DIRECT PENTRU CA SE SI INCREMENTEAZA
	}
	//USART_Transmit_caracter('\0');
}

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


void pinToggle(volatile uint8_t *port, uint8_t pin)
{
	*port ^=  1 << pin;
}

void pinSet(volatile uint8_t *port, uint8_t pin)
{
	*port |=  1 << pin;
}

void pinReset(volatile uint8_t *port, uint8_t pin)
{
	*port &=  ~(1 << pin);
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


ISR(TIMER0_COMPA_vect){
 	if(flag_start_timer == 1){
 		contor_rx--;
 	}
	
	if(contor_rx == 0){
		flag_stop = 1;
		contor_rx = timp_rx;
	}

}

void receive(){
	if(flag_stop == 1)
	{
		inc_ch = 0;
		flag_stop = 0;
		flag_start_timer = 0;
		lcd_clear();
		lcd_setCursor();
		lcd_print(buffer,16);
		memcpy(buffer_copy, buffer, strlen(buffer) + 1);
		buffer_copy[4] = buffer_copy[4] + 1;
		USART_Transmit_sir(buffer_copy, 17);
		pinToggle(&PORT_LED_328, PIN_LED_328);
		
	}
}