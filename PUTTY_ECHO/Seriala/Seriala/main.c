// Seriala
// Raspuns - echo

#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL 

//baud rate
#define BAUD 9600
#define MYUBRR (F_CPU/16/BAUD)-1 // modul 7 si datasheet

//init
void init_devices(void);
void port_init(void);

void pinToggle(volatile uint8_t *port, uint8_t pin);
void pinSet(volatile uint8_t *port, uint8_t pin);
void pinReset(volatile uint8_t *port, uint8_t pin);


uint8_t flag_rx = 0; // activat dupa ce se primesc date
uint8_t data;

ISR(USART0_RX_vect); 

void USART0_Tx_char(unsigned char data);
void USART0_Tx_sir_size(char *string, int size);
void USART0_init(unsigned int ubrr);



//---------------- COD ----------------------------------
void init_devices(void)
{
	cli();
	port_init();
	sei(); 
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

//--------------------- MAIN ------------------------------
int main(void){
	init_devices();
	USART0_init(MYUBRR);


	do{
		if(flag_rx == 1)
		{	
			
			//METODA SWITCH/CASE
			switch(data){
				case 'A': UDR0 = '!';
				break;
				
			}
		}
	}while(1);
	
	return 0;
}

void USART0_init(unsigned int ubrr)
{
	///PENTRU USART 0
	//set baud rate
	UBRR0H = (unsigned char) (ubrr>>8);
	UBRR0L = (unsigned char) ubrr;
	
	//activ doar sa transmita si sa primeasca
	UCSR0B |= (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0);
	
	//setez frame format : 8 data , 1 bit stop
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
	sei();
}


void USART0_Tx_sir_size(char *string, int size)
{
	//FUNCTIE CARE IA UN SIR DE CARACTERE SI EXTRAGE CATE UN CARACTER PE RAND, PANA LA TERMINAREA SIRULUI
	for(int i = 0; i < size; i++)
	{
		
		USART0_Tx_char(*string); ///II MODIFIC VALOAREA
		
		string++; //II MUT ADRESA!!!!
		
	}
}

void USART0_Tx_char(unsigned char data)
{
	//wait for empty transmit buffer
	while(!(UCSR0A &(1<<UDRE0)));
	
	//put data into buffer, sends the data
	UDR0 = data;//scriu in registru
	
}


ISR(USART0_RX_vect)
{
	//CITESC DATE DIN REGISTRU
	data = UDR0;
	flag_rx = 1;
	UDR0 = data;
}

void pinToggle(volatile uint8_t *port, uint8_t pin){
	*port ^=  1 << pin;
}

void pinSet(volatile uint8_t *port, uint8_t pin){
	*port |=  1 << pin;
}

void pinReset(volatile uint8_t *port, uint8_t pin){
	*port &=  ~(1 << pin);
}








