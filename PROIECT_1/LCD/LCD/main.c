
#include "main_config.h"
#include "main_defines.h"
#include "main_mcu_init.h"
#include "main_func.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>


int main()
{
	sec_1 = 0;
	min_1 = 0;
	h_1 = 0;
	
	initialize();
	init_data_contor();
	init_timer();
	//_delay_ms(20);

	lcd_clear();
	lcd_setCursor();
	lcd_print("TEST ORA");
	_delay_ms(2000);
	lcd_clear();
	lcd_setCursor();
	_delay_ms(2000);
	
	


	while(1)
	{
		//lcd_clear();
		//lcd_setCursor();
		afiseaza();
	}
	
}











