/*
328p COMUNICARE PROIECT OFICIAL 
ACESTA ESTE SLAVE!!!!!
----------------------------------------------------------------------
*/

#define F_CPU 16000000UL

#define BAUD 9600
#define MYUBRR (F_CPU/16/BAUD)-1

#include "USART_slave.h"


int main(void)
{
	init_devices();
	USART_Init(MYUBRR);
	
	//pinReset(&PORT_TX, PIN_TX);
	
	do
	{	
		if(FLAG_STOP_TIMER_USART == 1)
		{
			if(p_usart0.CONTOR_BUFFER_USART > 16){
				p_usart0.CONTOR_BUFFER_USART = 16;
			}
			
			p_usart0.CONTOR_BUFFER_USART = 0;
			FLAG_STOP_TIMER_USART = 0;
			FLAG_START_TIMER_USART = 0;
			
		
			p_usart0.BUFFER_RX_USART[4] = p_usart0.BUFFER_RX_USART[4] + 1;
			USART0_TX_SIR_SIZE(&p_usart0);
			//pinToggle(&PORT_TX, PIN_TX);	
		}
	}
	while(1);
	
	return 0;
}