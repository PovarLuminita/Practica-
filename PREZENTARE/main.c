/*
328p COMUNICARE PROIECT OFICIAL 
ACESTA ESTE SLAVE!!!!!
04.07.2023
----------------------------------------------------------------------
*/

#define F_CPU 16000000UL


#include <util/delay.h>

#define BAUD 9600
#define MYUBRR (F_CPU/16/BAUD)-1

#include "USART_slave.h"



int main(void)
{
	init_devices();
	USART_Init(MYUBRR);
	
	do
	{
			if(FLAG_STOP_TIMER_USART == 1)
			{
				if(CONTOR_BUFFER_USART > 100){
					CONTOR_BUFFER_USART = 100;
				}
				
				FLAG_STOP_TIMER_USART = 0;
				FLAG_START_TIMER_USART = 0;
				
				BUFFER_RX_USART[5] = BUFFER_RX_USART[5] + 1 ;
				USART0_TX_SIR_SIZE(BUFFER_RX_USART, strlen(BUFFER_RX_USART));
				
				CONTOR_BUFFER_USART = 0;

				
				
			}
	}
	while(1);
	
	return 0;
}
