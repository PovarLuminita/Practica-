
#include <avr/io.h>
#include <util/delay.h>


#define F_CPU 16000000UL //clock speed
#define BAUD 9600
#define MYUBRR (F_CPU/16/BAUD)-1

void print_data(char *ptr); //ia un sir de caractere si extrage pe rand fiecare caracter in parte
void USART_Init(unsigned int ubrr); //initializare registrii si baud rate
void USART_Transmit(unsigned char data);
unsigned char USART_Receive( void );

uint8_t data;

int main(void){
	USART_Init(MYUBRR);
	
	USART_Transmit(66);//B 
	_delay_ms(1000);
	USART_Transmit(85);//U
	_delay_ms(1000);
	USART_Transmit(78);//N
	_delay_ms(1000);
	USART_Transmit(66);//B
	_delay_ms(1000);
	USART_Transmit(85);//U
	_delay_ms(1000);
	USART_Transmit(78);//N
	_delay_ms(1000);
	
	while (1)
	{	
	data = USART_Receive(); //returneaza din functie valoarea
	USART_Transmit(data);
	_delay_ms(1000);
	}
}

ISR(USART1_RX_vect)
{
		//citesc registru 
		data = UDR1;
}


void USART_Init(unsigned int ubrr)
{
	//set baud rate
	UBRR1H |= (unsigned char) (ubrr>>8);
	UBRR1L |= (unsigned char) ubrr;
	
	//activ doar sa transmita si sa primeasca
	UCSR1B |= (1<<RXEN1)|(1<<TXEN1);
	
	//setez frame format : 8 data , 1 bit stop
	UCSR1C |= (1<<UCSZ11)|(1<<UCSZ10);
}


void USART_Transmit(unsigned char data)
{
	//wait for empty transmit buffer
	while(!(UCSR1A &(1<<UDRE1))); 
	
	//put data into buffer, sends the data
	UDR1 = data;//scriu in registru	
}


//m128 ex pag 180
unsigned char USART_Receive(void)
{
	/* Wait for data to be received */
	while (!(UCSR1A & (1<<RXC1)));
	/* Get and return received data from buffer */
	return UDR1;
}


void print_data(char *ptr)//functie care ia un sir de caractere si extrage cate un caracter pe rand, pana la terminarea sirului
{
	while(*ptr!= 0x00)
	{
		USART_Transmit(*ptr);
		ptr++;
	}
	
}

