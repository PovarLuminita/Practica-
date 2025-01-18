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

#define lcd_port PORTD			    //Define LCD Port
#define lcd_data_dir  DDRD			//PD4-PD7 PORT D - pe 4 biti
#define rs PD0			//RS Pin
#define en PD1 			//E Pin

#define timp_sec_1 1000 // o secunda

uint16_t contor_sec_1;  //contor secunda
uint16_t flag1;  //semafor
uint8_t sec_1 ;  //secunde
uint8_t min_1;	//minute
uint8_t h_1;	//ore
uint8_t sec_old;
char buffer[16];



#endif /* MAIN_DEFINES_H_ */