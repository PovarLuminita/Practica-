#define F_CPU 50000UL

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

#include <avr/io.h>
#include <util/delay.h>

uint32_t delay;

//void delay(uint32_t interations);
void pinToggle(volatile uint8_t *port, uint8_t pin);
void pinSet(volatile uint8_t *port, uint8_t pin);
void pinReset(volatile uint8_t *port, uint8_t pin);

int main(void)
{
	//Initialize peripherals. Set all ports as outputs
	DDRB = 0xFF;
	DDRD = 0xFF;

	//Set the output value of the ports to low
	PORTB = 0x00;
	PORTD = 0x00;

	volatile uint8_t* vector_port[] =  {&PORT_LED0,
										&PORT_LED1,
										&PORT_LED2,
										&PORT_LED3,
										&PORT_LED4,
										&PORT_LED5,
										&PORT_LED6,
										&PORT_LED7,
										&PORT_LED8,
										&PORT_LED9};
	
	uint8_t vector_pini[] ={PIN_LED0,
							PIN_LED1,
							PIN_LED2,
							PIN_LED3,
							PIN_LED4,
							PIN_LED5,
							PIN_LED6,
							PIN_LED7,
							PIN_LED8,
							PIN_LED9};
	
// (*PORTB) = 
(*PORTB) = 15;
	pinSet(&PORT_LED0, PIN_LED0);
	//Main loop of the application.
	do{
		
		for(int i = 1; i <= 10; i++)
		{
			pinSet(vector_port[i], vector_pini[i]);
			_delay_ms(50000);
			pinReset(vector_port[i-1], vector_pini[i-1]);
			
		}
		
		//pinSet(&PORT_LED1, PIN_LED1);
		//_delay_ms(50000);
		//
		//pinReset(&PORT_LED0, PIN_LED0);
		//
		//pinSet(&PORT_LED2, PIN_LED2);
		//_delay_ms(50000);
		//
		//pinReset(&PORT_LED1, PIN_LED1);
		//
		//pinSet(&PORT_LED3, PIN_LED3);
		//_delay_ms(50000);
		//
		//pinReset(&PORT_LED2, PIN_LED2);
		//
		//pinSet(&PORT_LED4, PIN_LED4);
		//_delay_ms(50000);
		//
		//pinReset(&PORT_LED3, PIN_LED3);
		//
		//pinSet(&PORT_LED5, PIN_LED5);
		//_delay_ms(50000);
		//
		//pinReset(&PORT_LED4, PIN_LED4);
		//
		//pinSet(&PORT_LED6, PIN_LED6);
		//_delay_ms(50000);
		//
		//pinReset(&PORT_LED5, PIN_LED5);
		//
		//pinSet(&PORT_LED7, PIN_LED7);
		//_delay_ms(50000);
		//
		//pinReset(&PORT_LED6, PIN_LED6);
		//
		//pinSet(&PORT_LED8, PIN_LED8);
		//_delay_ms(50000);
		//
		//pinReset(&PORT_LED7, PIN_LED7);
		//
		//pinSet(&PORT_LED9, PIN_LED9);
		//_delay_ms(50000);
		//
		//pinReset(&PORT_LED8, PIN_LED8);
		//
		//pinSet(&PORT_LED0, PIN_LED0);
		//_delay_ms(50000);
		//
		//pinReset(&PORT_LED9, PIN_LED9);
		
	}
	while(1);
}


void pinToggle(volatile uint8_t *port, uint8_t pin){
	*port ^=  1 << pin;
}

void pinSet(volatile uint8_t *port, uint8_t pin){
	*port |=  1 << pin;
}

void pinReset(volatile uint8_t *port, uint8_t pin){
	*port &=  ~(1 << pin);
}




//TEMA 2 METODA 1

#define F_CPU 5000000UL
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
		
		PORTB |= (1<<PINB5);		// led pin13 on
		PORTB |= (1<<PINB4);		// led pin12 on
		_delay_ms(1000);             
		PORTB &= ~(1 << PINB5);     // led pin13 off
				
		PORTB |= (1<<PINB3);		// led pin11 on	
		_delay_ms(1000);           
		PORTB &= ~(1<<PINB4);		// led pin12 off
		
		PORTB |= (1<<PINB2);		// led pin10 on
		_delay_ms(1000);           
		PORTB &= ~(1<<PINB3);		// led pin11 off
		
		PORTB |= (1<<PINB1); 		// led pin9 on
		_delay_ms(1000);            
		PORTB &= ~(1<<PINB2);		// led pin10 off
		
		PORTB |= (1<<PINB0);		// led pin8 on
		_delay_ms(1000);           
		PORTB &= ~(1<<PINB1);		// led pin9 off
		
		PORTD |= (1<<PIND7);		// led pin7 on
		_delay_ms(1000);           
		PORTB &= ~(1<<PINB0);		// led pin8 off
		
		PORTD |= (1<<PIND6);		// led pin6 on
		_delay_ms(1000);       
		PORTD &= ~(1<<PIND7);		// led pin7 off
		
		PORTD |= (1<<PIND5);		// led pin5 on
		_delay_ms(1000);         
		PORTD &= ~(1<<PIND6);		// led pin6 off
		
		
		//EXTRA: At the end shift them to opossite direction
		
		PORTD |= (1<<PIND4);		// led pin4 on
		
		_delay_ms(1000);  
		PORTD &= ~(1<<PIND5);		// led pin5 off
		PORTD &= ~(1<<PIND4);		// led pin4 off
			
		PORTD &= ~(1<<PINB5);		// led pin13 off
		
		 
		PORTD |= (1<<PIND4);		// led pin4 on
		PORTD |= (1<<PIND5);		// led pin5 on
		
		_delay_ms(1000);
		PORTD &= ~(1<<PIND4);		// led pin4 off
		
		
		PORTD |= (1<<PIND6);		// led pin6 on		
		_delay_ms(1000); 
		PORTD &= ~(1<<PIND5);		// led pin5 off
		
		PORTD |= (1<<PIND7);		// led pin7 on
		
		_delay_ms(1000);
		PORTD &= ~(1<<PIND6);		// led pin6 off
		
		PORTB |= (1<<PINB0);		// led pin8 on
		_delay_ms(1000);
		PORTD &= ~(1<<PIND7);		// led pin7 off
		
		PORTB |= (1<<PINB1); 		// led pin9 on
		_delay_ms(1000);
		PORTB &= ~(1<<PINB0);		// led pin8 off
		
		PORTB |= (1<<PINB2);		// led pin10 on
		_delay_ms(1000);
		PORTB &= ~(1<<PINB1);		// led pin9 off
		
		
		PORTB |= (1<<PINB3);		// led pin11 on
		_delay_ms(1000);
		PORTB &= ~(1<<PINB2);		// led pin10 off
		
		PORTB |= (1<<PINB4);		// led pin12 on
		
		_delay_ms(1000);
		PORTB &= ~(1<<PINB3);		// led pin11 off
			
		PORTB |= (1<<PINB5);		// led pin13 on
		
		_delay_ms(1000);
		PORTB &= ~(1<<PINB4);		// led pin12 off
	}
}


/*
//METODA 2
#define INITIAL_DELAY 50000UL
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
#define PIN_LED9	PINB5	//This also corresponds to the onboard LED
#include <avr/io.h>
uint32_t delay;
void basic_delay(uint32_t interations);
void pinToggle(volatile uint8_t *port, uint8_t pin);
void pinSet(volatile uint8_t *port, uint8_t pin);
void pinReset(volatile uint8_t *port, uint8_t pin);
int main(void)
{
	//Initialize data
	delay = INITIAL_DELAY;
	
	//Initialize peripherals. Set all ports as outputs
	DDRB = 0xFF; //cei 8 pini de pe portul B vor fi toti de iesire
	DDRC = 0x3F;
	DDRD = 0xFF;
	//Set the output value of the ports to low
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
	//Main loop of the application.
	do{
		delay = INITIAL_DELAY;
		
		pinSet(&PORT_LED0, PIN_LED0);
		
		pinSet(&PORT_LED1, PIN_LED1);
		basic_delay(delay);
		
		pinReset(&PORT_LED0, PIN_LED0);
		
		pinSet(&PORT_LED2, PIN_LED2);
		basic_delay(delay);
		
		pinReset(&PORT_LED1, PIN_LED1);
		pinSet(&PORT_LED3, PIN_LED3);
		basic_delay(delay);
		
		pinReset(&PORT_LED2, PIN_LED2);
		pinSet(&PORT_LED4, PIN_LED4);
		basic_delay(delay);
		
		pinReset(&PORT_LED3, PIN_LED3);
		pinSet(&PORT_LED5, PIN_LED5);
		basic_delay(delay);
		
		pinReset(&PORT_LED4, PIN_LED4);
		pinSet(&PORT_LED6, PIN_LED6);
		basic_delay(delay);
		
		pinReset(&PORT_LED5, PIN_LED5);
		pinSet(&PORT_LED7, PIN_LED7);
		basic_delay(delay);
		
		pinReset(&PORT_LED6, PIN_LED6);
		pinSet(&PORT_LED8, PIN_LED8);
		basic_delay(delay);
		
		pinReset(&PORT_LED7, PIN_LED7);
		pinSet(&PORT_LED9, PIN_LED9);
		basic_delay(delay);
		
		pinReset(&PORT_LED8, PIN_LED8);
		
		pinSet(&PORT_LED0, PIN_LED0);
		basic_delay(delay);
		
		pinReset(&PORT_LED9, PIN_LED9);
		
	}
	while(1);
}
void basic_delay(uint32_t interations){
	do{
		interations--;
	}
	while(interations>0);
}
void pinToggle(volatile uint8_t *port, uint8_t pin){
	*port ^=  1 << pin;
}
void pinSet(volatile uint8_t *port, uint8_t pin){
	*port |=  1 << pin;
	//PORTD = PORTD || (1 << PIND4) // PORTD |= 1 << PIND4
}
void pinReset(volatile uint8_t *port, uint8_t pin){
	*port &=  ~(1 << pin);
}*/