
//pag 114, 75, 84 datasheet

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
	//lcd_setCursor(2, 1); //lcd_setCursor(coloana,rand)
	
//  	lcd_setCursor();
// 	_delay_ms(500); 
// 	lcd_clear();
// 	_delay_ms(500); 
// 	lcd_print("TEST");
// 	_delay_ms(500);
// 	lcd_setCursor();
// 	_delay_ms(500);
// 	lcd_clear();
// 	_delay_ms(500);
// 	lcd_print("TEST");
// 	_delay_ms(500);
	init_data();
	init_timer();
	
 	while(1)
	{
 	aprinde_led_1();
	}
	
	
// 	while(1)
// 	{
// 		lcd_clear();
// 		//lcd_setCursor();
// 		afiseaza();}
// 		
 }


//itoa(sec_1, sec1, 10);     //sau char m = char(min);






	



