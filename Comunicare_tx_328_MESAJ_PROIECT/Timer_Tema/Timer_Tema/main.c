//COMUNICARE TX 328
//ACCESARE: 13.02.2023
//VERIFIC DACA SE TRANSMITE IN PUTTY CARACTERUL -> APRIND LEDUL 
//TRANSMITE IN PUTTY CU SUCCES

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

// defines

///LED ROSU
#define PORT_LED_328	PORTB
#define PIN_LED_328 	PB0

///LED GALBEN
#define PORT_LED_mesaj	PORTB
#define PIN_LED_mesaj 	PB1

///BAUD RATE
#define BAUD 9600
#define MYUBRR (F_CPU/16/BAUD)-1

#define timp_led 1000 // timer


// declarari si initializari

uint16_t contor_led; // timer
uint8_t data;

// flags  
uint8_t flag, // timer
		flag_mesaj = 0, // activat de trimiterea unui caracter
		flag_rx = 0;

// inits

void init_data(void);
void port_init(void);
void timer0_init(void);
void init_devices(void);
void USART_Init(unsigned int ubrr); 



// led

void pinToggle(volatile uint8_t *port, uint8_t pin);
void pinSet(volatile uint8_t *port, uint8_t pin);
void pinReset(volatile uint8_t *port, uint8_t pin);

///FUNCTII TRANSMITERE

void USART_Transmit_string(char *string); //ia un sir de caractere si extrage pe rand fiecare caracter in parte
void USART_Transmit(unsigned char data);

///FUNCTIE RECEPTIE

void USART_Receive(unsigned char data);

// verificari
void aprinde_led();
void aprinde_led_mesaj();
void verificare_rx();

///INTRERUPERE RECEPTIE 328p

ISR(USART0_RX_vect);

 // INTRERUPERE TIMER
 
ISR(TIMER0_COMP_vect);


int main(void)
{
	init_data();
	init_devices();
	USART_Init(MYUBRR);
	
	
	do
	{
		//aprinde_led();
		aprinde_led_mesaj(); //led rosu
	
		//data = USART_Receive(); 
		USART_Receive(data);
		
		verificare_rx(); //verif led galben
		// 		if(data != 'A')
				//{
					//pinToggle(&PORT_LED_328, PIN_LED_328);
				//}
				
		//USART_Transmit(data);
	} while(1);
}

ISR(TIMER0_COMPA_vect)
{
	 contor_led--;
	 
	 if(contor_led == 0){
		 flag = 1;
		 contor_led = timp_led;
	 }
 }
 // todo - nu merge (rx)
ISR(USART_RX_vect)
 {
 	//citesc registru
 	data = UDR0;
 	flag_rx = 1;
 	
 }

// initializari

void init_data(void)
{
	contor_led = timp_led;
}

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

void timer0_init(void)
{
	TCCR0A |= (1 << WGM01);
	
	//Set the prescaler
	TCCR0B |= (0 << CS02)|(1 << CS01)|(1 << CS00);

	//The output frequency if Fclock / prescaler / OCR.
	OCR0A = 0xF9; //249
	
	//Enable Timer/Counter Output Compare Match Interrupt
	TIMSK0 |= 1 << OCIE0A;
}

void USART_Init(unsigned int ubrr)
{
	//set baud rate
	UBRR0H = (unsigned char) (ubrr>>8);
	UBRR0L = (unsigned char) ubrr;
	UCSR0B = 0x00;
	UCSR0C = 0x00;
	//activ doar sa transmita si sa primeasca
	//UCSR0B |= (1<<RXCIE0)|(1<<TXCIE0)|(1<<RXEN0)|(1<<TXEN0);
	//UCSR0B |= (1<<TXCIE0)|(1<<RXEN0)|(1<<TXEN0);
	UCSR0B |= (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0);
	
	//setez frame format : 8 data , 1 bit stop
	///+ MOD SINCRON  !!!!!!!!!!!!!!!
	UCSR0C |= (1 << UMSEL00 )|(1<<UCSZ01)|(1<<UCSZ00);
	
	//enable global interrupts
	set_sleep_mode(SLEEP_MODE_IDLE);
	sei();
}


// verificari
void aprinde_led()
{
	if(flag == 1 )
	{
		USART_Transmit(65);//A
		flag_mesaj = 1;
		flag = 0;
	}
}

void aprinde_led_mesaj()
{
	if(flag_mesaj == 1)
	{
		pinToggle(&PORT_LED_mesaj, PIN_LED_mesaj);
		flag_mesaj = 0;
	}
}

void verificare_rx()
{
	if(flag_rx == 1)
	{
		pinToggle(&PORT_LED_328, PIN_LED_328);
		flag_rx = 0;
	}
}


///LEDURI
void pinToggle(volatile uint8_t *port, uint8_t pin)
{
	*port ^=  1 << pin;
}

void pinSet(volatile uint8_t *port, uint8_t pin)
{
	*port |=  1 << pin;
}

void pinReset(volatile uint8_t *port, uint8_t pin)
{
	*port &=  ~(1 << pin);
}


///USART

void USART_Transmit(unsigned char data)
{
	//wait for empty transmit buffer
	while(!(UCSR0A &(1<<UDRE0)));
	
	//put data into buffer, sends the data
	UDR0 = data;//scriu in registru
}

void USART_Transmit_string(char *string)
{
	//luam un sir de caractere si extrage cate un caracter pe rand, pana la terminarea sirului
	// pointam la fiecare caracter din string, pornind de la primul, folosind incrementarea indexului
	while(*string!= 0x00)
	{
		USART_Transmit(*string);
		string++;
	}
	
}

void USART_Receive(unsigned char data)
{
	/* Wait for data to be received */
	if(UCSR0A & (1<<RXC0)){
		data = UDR0;
		flag_rx = 1;
	}
// 	while (!(UCSR0A & (1<<RXC0)));
// 	data = UDR0;
// 	flag_rx = 1;
	/* Get and return received data from buffer */
}