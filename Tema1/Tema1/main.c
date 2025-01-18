/*
 * Tema1.c
 *
 * Created: 11/08/2022 15:13:47
 * Author : Asus
 */ 


 #define F_CPU 1000000UL
 #include <avr/io.h>
 #include <util/delay.h>
 
 
 #define PORT_LED0	PORTD
 #define PIN_LED0	PIND4
 #define PORT_LED1	PORTD
 #define PIN_LED1	PIND5
 #define PORT_LED2	PORTD
 #define PIN_LED2	PIND6
 #define PORT_LED3	PORTD
 #define PIN_LED3	PIND7
 #define PORT_LED4	PORTB
 #define PIN_LED4	PINB0
 #define PORT_LED5	PORTB
 #define PIN_LED5	PINB1
 #define PORT_LED6	PORTB
 #define PIN_LED6	PINB2
 #define PORT_LED7	PORTB
 #define PIN_LED7	PINB3
 #define PORT_LED8	PORTB
 #define PIN_LED8	PINB4
 #define PORT_LED9	PORTB
 #define PIN_LED9	PINB5
 
 
 int main(void)
 {
 	DDRB = 0xFF; //out
 	DDRC = 0x3F;
 	DDRD = 0xFF;
 
 	PORTB = 0x00; //low
 	PORTC = 0x00;
 	PORTD = 0x00;
 	
 	
 	while(1)
 	{
		 PORTD |= (1<<PIND4);	// led pin6 on
		 _delay_ms(1000);             // 50ms delay
		 PORTD &= ~(1<<PIND4);		// led pin5 off
		 _delay_ms(1000);             // 50ms delay
		  PORTD |= (1<<PIND4);	// led pin6 on
		  _delay_ms(1000);             // 50ms delay
		  PORTD &= ~(1<<PIND4);		// led pin5 off
		  _delay_ms(1000);             // 50ms delay
		   PORTD |= (1<<PIND4);	// led pin6 on
		   _delay_ms(1000);             // 50ms delay
		   PORTD &= ~(1<<PIND4);		// led pin5 off
		   _delay_ms(1000);             // 50ms delay
		 
 		
 		PORTD |= (1<<PIND6);	// led pin6 on
 		_delay_ms(5000);             // 50ms delay
 		
 		PORTD |= (1<<PIND6);	// led pin6 on
 		_delay_ms(5000);             // 50ms delay
 		PORTD |= (1<<PIND6);	// led pin6 on
 		_delay_ms(5000);             // 50ms delay
 		PORTD |= (1<<PIND6);	// led pin6 on
 		PORTD |= (1<<PIND6);	// led pin6 on
 		
 		PORTB |= (1<<PINB5);	// led pin13 on
 		PORTB |= (1<<PINB3);	// led pin11 on
 		PORTB |= (1<<PINB1); 	// led pin9 on
 		PORTD |= (1<<PIND7);	// led pin7 on
 		PORTD |= (1<<PIND5);	// led pin5 on
 		_delay_ms(5000);             // 50ms delay
 		
 		PORTB &= ~(1 << PINB5);     // LED off
 		PORTB &= ~(1<<PINB3);		// led pin11 off
 		PORTB &= ~(1<<PINB1);		// led pin9 off
 		PORTD &= ~(1<<PIND7);		// led pin7 off
 		PORTD &= ~(1<<PIND5);		// led pin5 off
 		_delay_ms(5000);             // 50ms delay
 		
 		PORTB |= (1<<PINB4);	// led pin12 on
 		PORTB |= (1<<PINB2);	// led pin10 on
 		PORTB |= (1<<PINB0);	// led pin8 on
 		PORTD |= (1<<PIND6);	// led pin6 on
 		PORTD |= (1<<PIND4);	// led pin4 on
 		_delay_ms(5000);
 		
 		PORTB &= ~(1<<PINB4);	// led pin12 off
 		PORTB &= ~(1<<PINB2);	// led pin10 off
 		PORTB &= ~(1<<PINB0);	// led pin8 off
 		PORTD &= ~(1<<PIND6);	// led pin6 off
 		PORTD &= ~(1<<PIND4);	// led pin4 off
 		_delay_ms(5000);
 	}
 
 }




//METODA 2
// #define INITIAL_DELAY 500000UL
// 
// #define PORT_LED0	PORTD
// #define PIN_LED0	PIND4
// #define PORT_LED1	PORTD
// #define PIN_LED1	PIND5
// #define PORT_LED2	PORTD
// #define PIN_LED2	PIND6
// #define PORT_LED3	PORTD
// #define PIN_LED3	PIND7
// #define PORT_LED4	PORTB
// #define PIN_LED4	PINB0
// #define PORT_LED5	PORTB
// #define PIN_LED5	PINB1
// #define PORT_LED6	PORTB
// #define PIN_LED6	PINB2
// #define PORT_LED7	PORTB
// #define PIN_LED7	PINB3
// #define PORT_LED8	PORTB
// #define PIN_LED8	PINB4
// #define PORT_LED9	PORTB
// #define PIN_LED9	PINB5	//This also corresponds to the onboard LED
// 
// 
// #include <avr/io.h>
// 
// uint32_t delay;
// 
// void basic_delay(uint32_t interations);
// void pinToggle(volatile uint8_t *port, uint8_t pin);
// void pinSet(volatile uint8_t *port, uint8_t pin);
// void pinReset(volatile uint8_t *port, uint8_t pin);
// 
// int main(void)
// {
// 	//Initialize data
// 	delay = INITIAL_DELAY;
// 	
// 	//Initialize peripherals. Set all ports as outputs
// 	DDRB = 0xFF; //cei 8 pini de pe portul B vor fi toti de iesire
// 	DDRC = 0x3F;
// 	DDRD = 0xFF;
// 
// 	//Set the output value of the ports to low
// 	PORTB = 0x00;
// 	PORTC = 0x00;
// 	PORTD = 0x00;
// 
// 	//Main loop of the application.
// 	do{
// 		delay = INITIAL_DELAY;
// 		
// 		pinSet(&PORT_LED0, PIN_LED0);
// 		pinSet(&PORT_LED2, PIN_LED2);
// 		pinSet(&PORT_LED4, PIN_LED4);
// 		pinSet(&PORT_LED6, PIN_LED6);
// 		pinSet(&PORT_LED8, PIN_LED8);
// 		
// 		basic_delay(delay);
// 
// 		pinReset(&PORT_LED0, PIN_LED0);
// 		pinReset(&PORT_LED2, PIN_LED2);
// 		pinReset(&PORT_LED4, PIN_LED4);
// 		pinReset(&PORT_LED6, PIN_LED6);
// 		pinReset(&PORT_LED8, PIN_LED8);
// 		
// 		pinSet(&PORT_LED1, PIN_LED1);
// 		pinSet(&PORT_LED3, PIN_LED3);
// 		pinSet(&PORT_LED5, PIN_LED5);
// 		pinSet(&PORT_LED7, PIN_LED7);
// 		pinSet(&PORT_LED9, PIN_LED9);
// 		
// 		basic_delay(delay);
// 		
// 		pinReset(&PORT_LED1, PIN_LED1);
// 		pinReset(&PORT_LED3, PIN_LED3);
// 		pinReset(&PORT_LED5, PIN_LED5);
// 		pinReset(&PORT_LED7, PIN_LED7);
// 		pinReset(&PORT_LED9, PIN_LED9);
// 		
// 	}
// 	while(1);
// }
// 
// void basic_delay(uint32_t interations){
// 	do{
// 		interations--;
// 	}
// 	while(interations>0);
// }
// 
// void pinToggle(volatile uint8_t *port, uint8_t pin){
// 	*port ^=  1 << pin;
// }
// 
// void pinSet(volatile uint8_t *port, uint8_t pin){
// 	*port |=  1 << pin;
// 	//PORTD = PORTD || (1 << PIND4) // PORTD |= 1 << PIND4
// }
// 
// void pinReset(volatile uint8_t *port, uint8_t pin){
// 	*port &=  ~(1 << pin);
// }


//
//#define F_CPU 50000UL
//
//#define PORT_LED0	PORTD
//#define PIN_LED0	PIND4
//#define PORT_LED1	PORTD
//#define PIN_LED1	PIND5
//#define PORT_LED2	PORTD
//#define PIN_LED2	PIND6
//#define PORT_LED3	PORTD
//#define PIN_LED3	PIND7
//#define PORT_LED4	PORTB
//#define PIN_LED4	PINB0
//#define PORT_LED5	PORTB
//#define PIN_LED5	PINB1
//#define PORT_LED6	PORTB
//#define PIN_LED6	PINB2
//#define PORT_LED7	PORTB
//#define PIN_LED7	PINB3
//#define PORT_LED8	PORTB
//#define PIN_LED8	PINB4
//#define PORT_LED9	PORTB
//#define PIN_LED9	PINB5
//
//#include <avr/io.h>
//#include <util/delay.h>
//
//uint32_t delay;
//
////void delay(uint32_t interations);
//void pinToggle(volatile uint8_t *port, uint8_t pin);
//void pinSet(volatile uint8_t *port, uint8_t pin);
//void pinReset(volatile uint8_t *port, uint8_t pin);
//
//
//int main(void)
//{
	//
	////Initialize peripherals. Set all ports as outputs
	//DDRB = 0xFF;
	//DDRC = 0x3F;
	//DDRD = 0xFF;
//
	////Set the output value of the ports to low
	//PORTB = 0x00;
	//PORTC = 0x00;
	//PORTD = 0x00;
//
	//do
	//{
		//pinSet(&PORT_LED0, PIN_LED0);
		//pinSet(&PORT_LED2, PIN_LED2);
		//pinSet(&PORT_LED4, PIN_LED4);
		//pinSet(&PORT_LED6, PIN_LED6);
		//pinSet(&PORT_LED8, PIN_LED8);
		//
		//pinReset(&PORT_LED1, PIN_LED1);
		//pinReset(&PORT_LED3, PIN_LED3);
		//pinReset(&PORT_LED5, PIN_LED5);
		//pinReset(&PORT_LED7, PIN_LED7);
		//pinReset(&PORT_LED9, PIN_LED9);
		//_delay_ms(50000);
		//
		//pinReset(&PORT_LED0, PIN_LED0);
		//pinReset(&PORT_LED2, PIN_LED2);
		//pinReset(&PORT_LED4, PIN_LED4);
		//pinReset(&PORT_LED6, PIN_LED6);
		//pinReset(&PORT_LED8, PIN_LED8);
		//
		//pinSet(&PORT_LED1, PIN_LED1);
		//pinSet(&PORT_LED3, PIN_LED3);
		//pinSet(&PORT_LED5, PIN_LED5);
		//pinSet(&PORT_LED7, PIN_LED7);
		//pinSet(&PORT_LED9, PIN_LED9);
		//
		//_delay_ms(50000);
		//
	//} while (1);
//}
//
//void pinToggle(volatile uint8_t *port, uint8_t pin){
	//*port ^=  1 << pin;
//}
//
//void pinSet(volatile uint8_t *port, uint8_t pin){
	//*port |=  1 << pin;
//}
//
//void pinReset(volatile uint8_t *port, uint8_t pin){
	//*port &=  ~(1 << pin);
//}