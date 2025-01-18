
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
//#include <stdint.h>
//#include <stdbool.h>
//#include <avr/wdt.h>



void init_data(void);
void port_init(void);
void timer0_init(void);
void init_devices(void);

void pinToggle(volatile uint8_t *port, uint8_t pin);
void pinSet(volatile uint8_t *port, uint8_t pin);
void pinReset(volatile uint8_t *port, uint8_t pin);

void aprinde_led_1();
void aprinde_led_2();
void aprinde_led_3();


ISR(TIMER0_COMP_vect);


#define LED0_PORT PORTD
#define LED0_PIN PIND4

#define LED1_PORT PORTD
#define LED1_PIN PIND5

#define LED2_PORT PORTD
#define LED2_PIN PIND6


#define timp_led_1 50
#define timp_led_2 100
#define timp_led_3 1000

uint16_t contor_led_1; // verifica daca a trecut timpul fiecarui led
uint16_t contor_led_2;
uint16_t contor_led_3;
uint8_t flag1; //semafor
uint8_t flag2;
uint8_t flag3;


void init_data(void){
	contor_led_1 = timp_led_1;
	contor_led_2 = timp_led_2;
	contor_led_3 = timp_led_3;
}

//Init MCU peripherals and any devices connected to the MCU
void init_devices(void)
{
	//stop errant interrupts until set up. Disable all interrupts while we init the peripherals.
	cli();

	port_init();
	
	timer0_init();
	
	sei(); //re-enable interrupts. All peripherals are now initialized.
}


void port_init(void)
{
	DDRB  = 0xFF; // output
	PORTB  = 0x00; // low

	DDRC  = 0x7F;
	PORTC = 0x00;

	DDRD  = 0xFF;
	PORTD = 0x00;
}

//FORMULE + CALCULE
// Create a 100Hz timer to provide a 10ms timebase.
void timer0_init(void){
	//Put Timer0 in CTC Mode, no compare match output
	TCCR0A |= (1 << WGM01);
	
	//Set the prescaler. This will divide the input frequency by 64
	TCCR0B |= (0 << CS02)|(1 << CS01)|(1 << CS00);

	//The output frequency if Fclock / prescaler / OCR.
	OCR0A = 0xF9; //249
	
	//Enable Timer/Counter Output Compare Match Interrupt
	TIMSK0 |= 1 << OCIE0A;
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


//The ISR for the 100Hz timer. This interrupt is generated every 10ms
ISR(TIMER0_COMPA_vect){
	contor_led_1--;
	contor_led_2--;
	contor_led_3--;
	
	if(contor_led_1 == 0){
		flag1 = 1;
		contor_led_1 = timp_led_1;
	}

	if(contor_led_2 == 0){
		flag2 = 1;
		contor_led_2 =  timp_led_2;
	}
	
	if(contor_led_3 == 0){
		flag3 = 1;
		contor_led_3 =  timp_led_3;
	}
	
	
}


void aprinde_led_1()
{
	if(flag1 == 1 )
	{
		pinToggle(&LED0_PORT, LED0_PIN);
		flag1 = 0;
	}
}

void aprinde_led_2()
{
	if(flag2 == 1 )
	{
		pinToggle(&LED1_PORT, LED1_PIN);
		flag2 = 0;
	}
}


void aprinde_led_3()
{
	if(flag3 == 1 )
	{
		pinToggle(&LED2_PORT, LED2_PIN);
		flag3 = 0;
	}
}

int main(void)
{
	init_data();
	init_devices();

	do{
		aprinde_led_1();
		aprinde_led_2();
		aprinde_led_3();
	}
	while(1);
}