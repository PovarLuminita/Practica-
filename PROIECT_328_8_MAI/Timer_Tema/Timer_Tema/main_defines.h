/*
 * main_defines.h
 *
 *  Author: Asus
 */ 


#ifndef MAIN_DEFINES_H_
#define MAIN_DEFINES_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

#define lcd_port_pin PORTD			    //Define LCD Port
#define lcd_port PORTC
#define lcd_pin_dir  DDRD
#define lcd_data_dir  DDRC			//PD4-PD7 PORT D - pe 4 biti
#define rs PC1			//RS Pin
#define en PC2 			//E Pin

#endif /* MAIN_DEFINES_H_ */