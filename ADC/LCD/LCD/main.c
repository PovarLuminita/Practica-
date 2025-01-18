
#include "main_config.h"
#include "main_defines.h"
#include "main_mcu_init.h"
#include "main_func.h"
#include "adc.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>


int main()
{
	DDRB = 0xFF; //out
	

	PORTB = 0x00; //low
	

	
	sec_1 = 0;
	min_1 = 0;
	h_1 = 0;
	
	initialize();
///	init_data_contor();
//	init_timer();

	lcd_clear();
	lcd_setCursor();
// 	lcd_print("TEST ORA");
// 	_delay_ms(2000);
// 	lcd_clear();
// 	lcd_setCursor();
// 	_delay_ms(2000);
	

	while(1)
	{
		LED_ADC_PORT |= (1 << LED_ADC_PIN);
		
//		afiseaza();
//		aprinde_led();
	}
	
}











