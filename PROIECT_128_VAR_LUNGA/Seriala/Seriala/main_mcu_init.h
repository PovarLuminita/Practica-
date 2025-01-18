


#ifndef MAIN_MCU_INIT_H_
#define MAIN_MCU_INIT_H_

#include "main_config.h"
#include "main_defines.h"

#include <avr/wdt.h>
#include <avr/interrupt.h>


///INITIALIZARI
void initializare_porturi(void); ///porturi de intrare/iesire
void initializare_devices(void); ///folosim cli; sei;
void USART0_init(unsigned int ubrr);
void USART1_init(unsigned int ubrr);

///FUNCTII PENTRU TIMER
void initializare_timer0(void);
void initializari(void);




#endif /* MAIN_MCU_INIT_H_ */