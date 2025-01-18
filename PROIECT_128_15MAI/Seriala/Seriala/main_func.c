
#include "main_func.h"



ISR(TIMER0_OVF_vect){
	if(flag_start_USART1 == 1){
		contor_start_USART1--;
	}
	
	if(flag_start_USART0 == 1){
		contor_start_USART0--;
	}
	
	if(contor_start_USART1 == 0){
		flag_stop_USART1 = 1;
		contor_start_USART1 = timp_USART1;
	}
	
	if(contor_start_USART0 == 0){
		flag_stop_USART0 = 1;
		contor_start_USART0 = timp_USART0;
	}
	
	
	
}

void USART1_Tx_char(unsigned char data)
{
	//ASTEPT SA SE GOLEASCA BUFFERUL PENTRU TRANSMIS
	while(!(UCSR1A &(1<<UDRE1)));
	
	//PUN DATE IN BUFFER, TRIMIT DATELE
	UDR1 = data_UDR1;//SCRIU IN REGISTRU
	
}

void USART1_Tx_size(char *string, int size)
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
	buffer_UDR1[cnt_UDR1] = UDR1;
	flag_start_USART1 = 1;
	cnt_UDR1++;	

}

ISR(USART0_RX_vect)
{
	buffer_UDR0[cnt_UDR0] = UDR0;
	flag_start_USART0 = 1;
	cnt_UDR0++;
}


void USART0_Tx_size(char *string, int size)
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
	UDR0 = data_UDR0;//scriu in registru
	
}



void USART0_Tx(char *string)//functie care ia un sir de caractere si extrage cate un caracter pe rand, pana la terminarea sirului
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
