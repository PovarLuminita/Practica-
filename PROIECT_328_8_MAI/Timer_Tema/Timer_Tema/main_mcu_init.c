/*
 * main_mcu_init.c
 *
 *  Author: Asus
 */ 

#include "main_mcu_init.h"


void init_data_contor(void){
	lcd_data_dir = 0xFF;	//pin D4-D7
	lcd_pin_dir = 0xFF;	//pin D4-D7
}



