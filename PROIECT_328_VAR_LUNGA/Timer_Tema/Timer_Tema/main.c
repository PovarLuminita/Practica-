/*
PROIECT 328 ---> SLAVE
*/

#include "main_config.h"
#include "main_defines.h"
#include "main_func.h"
#include "main_mcu_init.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdio.h>
#include <string.h>

///------------------------- COD ---------------------------------------------------------------------

int main(void)
{
	init_lcd();
	init_Devices();
	Init_USART0(MYUBRR);
	
	
	lcd_clear();
	lcd_setCursor();
	pinReset(&PORT_LED_tx, PIN_LED_tx);
	
	do
	{
		Receptie_Transmisie_usart0();
	}
	while(1);
	
	return 0;
}

