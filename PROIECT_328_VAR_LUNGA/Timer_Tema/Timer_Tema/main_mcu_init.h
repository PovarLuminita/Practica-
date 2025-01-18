/*
 * main_mcu_init.h
 *
 * Created: 11/10/2022 08:12:24
 *  Author: Asus
 */ 


#ifndef MAIN_MCU_INIT_H_
#define MAIN_MCU_INIT_H_

#include "main_config.h"
#include "main_defines.h"

#include <avr/wdt.h>
#include <avr/interrupt.h>

void init_data_pin_lcd(void);
//INITIALIZARI
void init_Porturi(void); ///porturi de intrare/iesire
void init_Devices(void); ///folosim cli; sei;
void Init_USART0(unsigned int ubrr);
//set_sleep_mode(SLEEP_MODE_IDLE);

#endif /* MAIN_MCU_INIT_H_ */