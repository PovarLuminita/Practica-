

#include "main_func.h"


ISR(TIMER0_OVF_vect){
	if(flag_start_usart1 == 1){
		contor_usart1--;
	}
	
	if(flag_start_usart0 == 1){
		contor_usart0--;
	}
	
	if(contor_usart1 == 0){
		flag_stop_usart1 = 1;
		contor_usart1 = timp_usart1;
	}
	
	if(contor_usart0 == 0){
		flag_stop_usart0 = 1;
		contor_usart0 = timp_usart0;
	}
	
}

void USART1_Tx_char(unsigned char data)
{
	//ASTEPT SA SE GOLEASCA BUFFERUL PENTRU TRANSMIS
	while(!(UCSR1A &(1<<UDRE1)));
	
	//PUN DATE IN BUFFER, TRIMIT DATELE
	UDR1 = data;//SCRIU IN REGISTRU
	
}

void USART1_Tx_sir_size(char *string, int size)
{
	//FUNCTIE CARE IA UN SIR DE CARACTERE SI EXTRAGE CATE UN CARACTER PE RAND, PANA LA TERMINAREA SIRULUI
	for(int i = 0; i < size; i++)
	{
		
		USART1_Tx_char(*string); ///II MODIFIC VALOAREA
		
		string++; //II MUT ADRESA!!!!
		
	}
}


ISR(USART1_RX_vect)
{
	buffer_usart1[cnt_usart1] = UDR1;
	flag_start_usart1 = 1;
	cnt_usart1++;	///incrementez pozit

}

ISR(USART0_RX_vect)
{
	buffer_usart0[cnt_usart0] = UDR0;
	flag_start_usart0 = 1;
	cnt_usart0++;
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



void USART0_Tx_sir(char *string)//functie care ia un sir de caractere si extrage cate un caracter pe rand, pana la terminarea sirului
{
	while(*string!= 0x00)
	{
		USART0_Tx_char(*string);
		string++;
	}
	
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

