//328p COMUNICARE PUTTY 
//FOLOSIND INTRERUPERE RX

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

///LED ROSU
#define PORT_LED	PORTB
#define PIN_LED 	PB0

///BAUD RATE
#define BAUD 9600
#define MYUBRR (F_CPU/16/BAUD)-1

// declarari si initializari

uint8_t data;

// flags  
uint8_t flag_mesaj = 0, // activat de trimiterea unui caracter
		flag_rx = 0;

// inits
void port_init(void);
void init_devices(void);
void USART_Init(unsigned int ubrr); 

// led

void pinToggle(volatile uint8_t *port, uint8_t pin);
void pinSet(volatile uint8_t *port, uint8_t pin);
void pinReset(volatile uint8_t *port, uint8_t pin);

///FUNCTII TRANSMITERE

void USART_Transmit_string(char *string); //ia un sir de caractere si extrage pe rand fiecare caracter in parte
void USART_Transmit(unsigned char data);

///FUNCTIE RECEPTIE

//void USART_Receive(unsigned char data);

///INTRERUPERE RECEPTIE 328p
ISR(USART_RX_vect);

int main(void)
{
	init_devices();
	USART_Init(MYUBRR);
	
	pinReset(&PORT_LED, PIN_LED);
	do
	{
		//USART_Receive(data);
		
		if(flag_rx == 1)
		{
			USART_Transmit('C');
			pinToggle(&PORT_LED, PIN_LED);
			flag_rx = 0;
		}
	} while(1);
}

 ISR(USART_RX_vect)
 {
 	//CITESC DATE DIN REGISTRU
 	data = UDR0;
 	flag_rx = 1;
 	//UDR0 = data;
 }

void init_devices(void)
{
	cli();
	port_init();
	sei(); 
}


void port_init(void)
{
	DDRB  = 0xFF; // output
	PORTB  = 0x00; // low
	
	DDRC  = 0x7F;
	PORTC = 0x00;
	
	DDRD  = 0xFF;
	PORTD = 0x00;
}

void USART_Init(unsigned int ubrr)
{
	//set baud rate
	UBRR0H = (unsigned char) (ubrr>>8);
	UBRR0L = (unsigned char) ubrr;
	UCSR0B = 0x00;
	UCSR0C = 0x00;
	//activ doar sa transmita si sa primeasca
	//UCSR0B |= (1<<RXCIE0)|(1<<TXCIE0)|(1<<RXEN0)|(1<<TXEN0);
	//UCSR0B |= (1<<TXCIE0)|(1<<RXEN0)|(1<<TXEN0);
	UCSR0B |= (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0);
	
	//setez frame format : 8 data , 1 bit stop
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
	
	//enable global interrupts
	set_sleep_mode(SLEEP_MODE_IDLE);
	sei();
}

void aprinde_led_mesaj()
{
	if(flag_mesaj == 1)
	{
		pinToggle(&PORT_LED, PIN_LED);
		flag_mesaj = 0;
	}
}

///LEDURI
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

///USART
void USART_Transmit(unsigned char data)
{
	//wait for empty transmit buffer
	while(!(UCSR0A &(1<<UDRE0)));
	
	//put data into buffer, sends the data
	UDR0 = data;//scriu in registru
}

void USART_Transmit_string(char *string)
{
	//luam un sir de caractere si extrage cate un caracter pe rand, pana la terminarea sirului
	// pointam la fiecare caracter din string, pornind de la primul, folosind incrementarea indexului
	while(*string!= 0x00)
	{
		USART_Transmit(*string);
		string++;
	}
	
}

// void USART_Receive(unsigned char data)
// {
// 	/* Wait for data to be received */
//  	if(UCSR0A & (1<<RXC0)){
//  		data = UDR0;
//  		flag_rx = 1;
//  	}
//  	while (!(UCSR0A & (1<<RXC0)));
//  	data = UDR0;
//  	flag_rx = 1;
//}

