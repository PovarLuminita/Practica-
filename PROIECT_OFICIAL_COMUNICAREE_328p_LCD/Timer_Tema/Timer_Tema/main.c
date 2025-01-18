//328p COMUNICARE PROIECT OFICIAL
///ACESTA ESTE SLAVE!!!!!
//FOLOSIND INTRERUPERE RX

//--------------------PROIECT ACCESAT 03.03.2023 ---------------------------------------------------------------


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
//uint8_t a = 0 ; ///INCREMENTEAZA CATE CARACTERE SUNT PRIMITE

///FLAGURI SEMNALIZARE  
uint8_t flag_rx = 0; //flag care se activeaza in intreruperea rx dupa ce a primit un caracter
uint8_t flag_received = 0; //flag care se activeaza dupa ce a primit un caracter de la transmit_sir
uint8_t flag_start_timer = 0; //flag care se activeaza in intrerupere si ramane 1 cat timp primeste caractere

///buffer pentru a lua ce transmite transmit_buffer
char buffer[16] = {};	///acesta se incarca cu valorile primite de la transmit_sir; dupa ce nu mai primeste acesta activeaza flagul timer_expired
char *p_receive_buffer = buffer; 
char buffer_ch[16] = {};
///FUNCTIE RECEIVE SIR
uint8_t Receive_Buffer(char *buffer);


///FLAG TIMER EXPIRED
uint8_t flag_timer_expired = 0; ///flag care se activeaza dupa ce nu au mai fost primite date in buffer; acesta dezactiveaza flag_start_timer
								///DACA TIMER_EXPIRED = 0 -> aprinde ledul! -> ar trebui dupa accea sa afisez undeva bufferul primit! (LCD/Putty)
//INITIALIZARI 
void initializare_porturi(void); ///porturi de intrare/iesire
void initializare_devices(void); ///folosim cli; sei;
void USART_Initializare_registrii(unsigned int ubrr); 

void pinToggle(volatile uint8_t *port, uint8_t pin);
void pinSet(volatile uint8_t *port, uint8_t pin);
void pinReset(volatile uint8_t *port, uint8_t pin);

///FUNCTII TRANSMITERE
void USART_Transmit_sir(char *string); //ia un sir de caractere (STRING) si extrage pe rand fiecare caracter in parte
void USART_Transmit_caracter(unsigned char data);

///INTRERUPERE RECEPTIE 328p
ISR(USART_RX_vect);


///------------------------- COD ---------------------------------------------------------------------

int main(void)
{
	initialize();
	initializare_devices();
	USART_Initializare_registrii(MYUBRR);
	
	
 	lcd_clear();
 	lcd_setCursor();
 	lcd_print("TEST PROIECT");
 	_delay_ms(2000);
 	lcd_clear();
 	lcd_setCursor();
 	_delay_ms(2000);	uint8_t a = 0 ;
// 	
	pinReset(&PORT_LED_328, PIN_LED_328);
	
	do
	{
		
		uint8_t a = Receive_Buffer(buffer);
		lcd_clear();
		lcd_setCursor();
// 		sprintf(buffer_ch, "%d     ", a);
// 		lcd_print(buffer_ch);
		//_delay_ms(200);
		
		lcd_print(buffer);
		
		//lcd_clear();
		//lcd_setCursor();
		//sprintf(buffer_ch, "nr ch %d", a);
// 		if(flag_rx == 1)
// 		{
// 			USART_Transmit_caracter('C');
// 			pinToggle(&PORT_LED_328, PIN_LED_328);
// 			flag_rx = 0;
// 		}
	} while(1);
	
	return 0;
}

void USART_Transmit_caracter(unsigned char data)
{
	//astept sa se goleasca bufferul de transmitere
	while(!(UCSR0A &(1<<UDRE0)));
	
	//pun date in registru, trimit datele
	UDR0 = data;//scriu in registru
}

void USART_Transmit_sir(char *string)
{
	//luam un sir de caractere si extrage cate un caracter pe rand, pana la terminarea sirului
	// pointam la fiecare caracter din string, pornind de la primul, folosind incrementarea indexului
	while(*string!= 0x00)
	{
		USART_Transmit_caracter(*string);
		string++;
	}
	
}

////COMPLETARI!!!
uint8_t Receive_Buffer(char *buffer){
	uint8_t a = 0 ; 
	while(a < 16 ){
		
		if(flag_rx == 1){
			buffer[a] = data;
			
			flag_rx = 0;
		
			if( buffer[a] == '\0'){
				break;
			}	 
			a++;
		}}
		
	pinToggle(&PORT_LED_328, PIN_LED_328);
	return a;
}

 ISR(USART_RX_vect)
 {
 	//CITESC DATE DIN REGISTRU
 	data = UDR0;
	 
 	flag_rx = 1;
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
