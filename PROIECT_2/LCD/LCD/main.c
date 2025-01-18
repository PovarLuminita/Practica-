
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
	min_1 = 30;
	h_1 = 11;
	
	initialize();
	init_data_contor();
	init_timer();

	while(1)
	{
		lcd_clear();
		afiseaza();
	}
	
}











