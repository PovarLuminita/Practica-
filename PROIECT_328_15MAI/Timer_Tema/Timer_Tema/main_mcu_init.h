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

void init_data_contor(void);

void init_data(void);
void timer0_init(void);


//INITIALIZARI
void initializare_porturi(void); ///porturi de intrare/iesire
void initializare_devices(void); ///folosim cli; sei;
void USART_Initializare_registrii(unsigned int ubrr);

#endif /* MAIN_MCU_INIT_H_ */