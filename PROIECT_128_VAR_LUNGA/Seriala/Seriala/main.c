/*
PROIECT 128 ---> MASTER
*/
#include "main_config.h"
#include "main_defines.h"
#include "main_func.h"
#include "main_mcu_init.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <string.h>


///--------------------------------- COD --------------------------------------

int main(void)
{
	initializari();
	initializare_devices();
	pinReset(&PORT_LED_TX_USART0,PIN_LED_TX_USART0);
	pinReset(&PORT_LED_TX_USART1, PIN_LED_TX_USART1);
	do{
		if(flag_stop_usart1 == 1)
		{
			
			///bufferul pe care-l primesc , pe o anumita pozitie sa ii schimb valoarea
			memcpy(buffer_transfer_usart0, buffer_usart1, strlen(buffer_usart1) + 1);
			buffer_transfer_usart0[6] = buffer_transfer_usart0[6] + 1;
			
			USART0_Tx_sir_size(buffer_transfer_usart0, strlen(buffer_transfer_usart0));
			
			cnt_usart1 = 0;
			flag_stop_usart1 = 0;
			flag_start_usart1 = 0;
			memset(buffer_usart1, 0, sizeof(buffer_usart1));
			memset(buffer_transfer_usart0, 0, sizeof(buffer_transfer_usart0));
			USART0_Tx_sir_size("\n\r",4);
			pinToggle(&PORT_LED_TX_USART0, PIN_LED_TX_USART0);
			
		}
		
		
		if(flag_stop_usart0 == 1){
			if(cnt_usart0 > 16)
			{
				cnt_usart0 = 16;
			}
			
			flag_stop_usart0 = 0;
			flag_start_usart0 = 0;
			USART1_Tx_sir_size(buffer_usart0, cnt_usart0);
			cnt_usart0 = 0;
			pinToggle(&PORT_LED_TX_USART1, PIN_LED_TX_USART1);
			
		}
		
	}while(1);
	
	sleep_mode();
	return 0;
}
