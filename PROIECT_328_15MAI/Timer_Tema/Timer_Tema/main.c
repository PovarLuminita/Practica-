/*
-proiect luna mai 2023
----------------------------------------------------------------------
*/


//328p COMUNICARE PROIECT OFICIAL 
////ACESTA ESTE SLAVE!!!!!
#include "main_config.h"
#include "main_defines.h"
#include "main_func.h"
#include "main_mcu_init.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>



///------------------------- COD ---------------------------------------------------------------------

int main()
{
	initialize();
	initializare_devices();
	USART_Initializare_registrii(MYUBRR);
	
	
	lcd_clear();
	lcd_setCursor();
	pinReset(&PORT_LED_328, PIN_LED_328);
	
	do
	{	
		receive();
	}
	while(1);
	
	return 0;
}
