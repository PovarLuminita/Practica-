

#ifndef MAIN_MCU_INIT_H_
#define MAIN_MCU_INIT_H_

#include "main_config.h"
#include "main_defines.h"

#include <avr/wdt.h>
#include <avr/interrupt.h>
///INITIALIZARI
void PORTURI_INIT(void); ///porturi de intrare/iesire
void DEVICES_INIT(void); ///folosim cli; sei;
void USART0_INIT(unsigned int ubrr);
void USART1_INIT(unsigned int ubrr);

///FUNCTII PENTRU TIMER
void TIMER0_INIT(void);
void CONTOR_INIT(void);


#endif /* MAIN_MCU_INIT_H_ */