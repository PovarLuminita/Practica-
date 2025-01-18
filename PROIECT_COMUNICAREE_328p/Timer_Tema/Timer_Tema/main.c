//328p COMUNICARE 
//FOLOSIND INTRERUPERE RX

//--------------------PROIECT ACCESAT 02.03.2023 ---------------------------------------------------------------

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#define PORT_LED_328_VERIFICARE_PRIMIRE_CARACTER	PORTB	///CAND ESTE UN CARACTER PRIMIT DE LA 128 ATUNCI SE APRINDE UN LED!
#define PIN_LED_328_VERIFICARE_PRIMIRE_CARACTER 	PB0

///BAUD RATE
#define BAUD 9600
#define MYUBRR (F_CPU/16/BAUD)-1

uint8_t data; ///VARIABILA IN CARE LUAM/SALVAM CE ESTE IN REGISTRUL UDR

///FLAGURI SEMNALIZARE  
uint8_t	 flag_intrerupere_activare_la_primire_caracter = 0;	//ESTE ACTIVAT DUPA CE PRIMESTE UN CARACTER

//INITIALIZARI 
void initializare_porturi(void); ///porturi de intrare/iesire
void initializare_devices(void); ///folosim cli; sei;
void USART_Initializare_registrii(unsigned int ubrr); 

void pinToggle(volatile uint8_t *port, uint8_t pin);
void pinSet(volatile uint8_t *port, uint8_t pin);
void pinReset(volatile uint8_t *port, uint8_t pin);

///FUNCTII TRANSMITERE
void USART_Transmit_sir_de_caractere(char *string); //ia un sir de caractere (STRING) si extrage pe rand fiecare caracter in parte
void USART_Transmit_un_singur_caracter(unsigned char data);

///INTRERUPERE RECEPTIE 328p
ISR(USART_RX_vect);


///------------------------- COD ---------------------------------------------------------------------

int main(void)
{
	initializare_devices();
	USART_Initializare_registrii(MYUBRR);
	
	pinReset(&PORT_LED_328_VERIFICARE_PRIMIRE_CARACTER, PIN_LED_328_VERIFICARE_PRIMIRE_CARACTER);
	
	do
	{
		if(flag_intrerupere_activare_la_primire_caracter == 1)
		{
			USART_Transmit_un_singur_caracter('C');
			pinToggle(&PORT_LED_328_VERIFICARE_PRIMIRE_CARACTER, PIN_LED_328_VERIFICARE_PRIMIRE_CARACTER);
			flag_intrerupere_activare_la_primire_caracter = 0;
		}
	} while(1);
	
	return 0;
}

void USART_Transmit_un_singur_caracter(unsigned char data)
{
	//astept sa se goleasca bufferul de transmitere
	while(!(UCSR0A &(1<<UDRE0)));
	
	//pun date in registru, trimit datele
	UDR0 = data;//scriu in registru
}

void USART_Transmit_sir_de_caractere(char *string)
{
	//luam un sir de caractere si extrage cate un caracter pe rand, pana la terminarea sirului
	// pointam la fiecare caracter din string, pornind de la primul, folosind incrementarea indexului
	while(*string!= 0x00)
	{
		USART_Transmit_un_singur_caracter(*string);
		string++;
	}
	
}

 ISR(USART_RX_vect)
 {
 	//CITESC DATE DIN REGISTRU
 	data = UDR0;
 	flag_intrerupere_activare_la_primire_caracter = 1;
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
