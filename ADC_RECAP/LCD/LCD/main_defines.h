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

#define timp_sec_1 1000 // o secunda


uint16_t contor_sec_1;  //contor secunda
uint16_t flag1;  //semafor
uint8_t sec_1 ;  //secunde
uint8_t min_1;	//minute
uint8_t h_1;	//ore
char buffer[16];


#endif /* MAIN_DEFINES_H_ */