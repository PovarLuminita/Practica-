/*
PROIECT 128 - MASTER - 16 mai 2023
*/

#include "main_config.h"
#include "main_defines.h"
#include "main_mcu_init.h"
#include "main_func.h"

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <string.h>

int main(void)
{
	CONTOR_INIT();
	DEVICES_INIT();
	USART0_INIT(MYUBRR);
	USART1_INIT(MYUBRR);
	
	pinReset(&PORT_LED_RX_USART0,PIN_LED_RX_USART0);
	pinReset(&PORT_LED_RX_USART1,PIN_LED_RX_USART1);
	
	do{
		if(flag_stop_USART1 == 1)
		{
			
			///bufferul pe care-l primesc, pe o anunmita pozitie fac +1
			memcpy(buffer_Tx_USART0, buffer_UDR1, strlen(buffer_UDR1) + 1);
			buffer_Tx_USART0[6] = buffer_Tx_USART0[6] + 1;
			
			USART0_Tx_size(buffer_Tx_USART0, strlen(buffer_Tx_USART0));
			
			cnt_UDR1 = 0;
			flag_stop_USART1 = 0;
			flag_start_USART1 = 0;
			memset(buffer_UDR1, 0, sizeof(buffer_UDR1));
			memset(buffer_Tx_USART0, 0, sizeof(buffer_Tx_USART0)); 
			USART0_Tx_size("\n\r",4);
			pinToggle(&PORT_LED_RX_USART0, PIN_LED_RX_USART0);
			
		}
		
		if(flag_stop_USART0 == 1){
			if(cnt_UDR0 > 16)
			{
			cnt_UDR0 = 16;
			}
			
			flag_stop_USART0 = 0;
			flag_start_USART0 = 0;
			USART1_Tx_size(buffer_UDR0, cnt_UDR0);
			cnt_UDR0 = 0;
			pinToggle(&PORT_LED_RX_USART1, PIN_LED_RX_USART1);
			
		}
	}while(1);
	
	sleep_mode();
	return 0;
}

