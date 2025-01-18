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
void init_timer(void);
void timer0_init(void);



#endif /* MAIN_MCU_INIT_H_ */