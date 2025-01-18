//COMUNICARE 128 PROIECT OFICIAL
///ACESTA ESTE MASTER!!!!!

//------------- PROIECT ACCESAT 10.03.2023 -------------------------------------------------

#define F_CPU 16000000UL //FRECVENTA CEAS

#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

#define PORT_LED_128	PORTB ///CAND ESTE UN CARACTER PRIMIT DE LA 128 ATUNCI SE APRINDE UN LED!
#define PIN_LED_128	PB0
#define PORT_LED_RX	PORTB
#define PIN_LED_RX PB1

#define BAUD 9600
#define MYUBRR (F_CPU/16/BAUD)-1

#define timp_pentru_activare_led 100
#define timp_rx 30
uint16_t contor_rx;
uint16_t flag_start_timer = 0;
uint16_t flag_stop = 0;

uint8_t data; ///VARIABILA IN CARE LUAM/SALVAM CE ESTE IN REGISTRUL UDR
uint16_t contor_decrementare_timp;

///FLAGURI SEMNALIZARE
uint8_t flag_timp; //flag care se activeaza dupa ce s-a decrementat contorul (este apelata intreruperea la 1 ms)
uint8_t flag_rx = 0; //flag care se activeaza in intreruperea rx dupa ce a primit un caracter
uint8_t a = 0 ;
///INITIALIZARI
void initializare_porturi(void); ///porturi de intrare/iesire
void initializare_devices(void); ///folosim cli; sei;
void USART_Initializare_registrii(unsigned int ubrr);

///FUNCTII PENTRU TIMER
void initializare_timer0(void);
void initializare_contor_timp(void);


//uint8_t Receive_Buffer(char *buffer);
char buffer[16] = {};	///acesta se incarca cu valorile primite de la transmit_sir; dupa ce nu mai primeste acesta activeaza flagul timer_expired

///INTRERUPERE PENTRU TIMER
ISR(TIMER0_OVF_vect);

void pinToggle(volatile uint8_t *port, uint8_t pin);
void pinSet(volatile uint8_t *port, uint8_t pin);
void pinReset(volatile uint8_t *port, uint8_t pin);

///FUNCTII TRANSMITERE
void USART_Transmit_sir(char *string, int size); //ia un sir de caractere (STRING) si extrage pe rand fiecare caracter in parte
void USART_Transmit_caracter(unsigned char data);

void Receive_Buffer(char *buffer);
///INTRERUPERE RECEPTIE 128
ISR(USART1_RX_vect);

//FUNCTIE CARE APRINDE LEDUL DUPA CE A PRIMIT UN CARACTER; TRIMITE UN CARACTER CU TIMER DE 1 SECUNDA
void verificare_led_primire_caracter();


///--------------------------------- COD --------------------------------------

int main(void)
{
	initializare_contor_timp();
	initializare_devices();
	USART_Initializare_registrii(MYUBRR);
	pinReset(&PORT_LED_RX,PIN_LED_RX);
	do{
		verificare_led_primire_caracter();	
		
		if(flag_stop == 1)
		{
			a = 0;
			flag_stop = 0;
			flag_start_timer = 0;
			pinToggle(&PORT_LED_RX, PIN_LED_RX);
			
		}
	//	Receive_Buffer(buffer);
// 	if(flag_rx == 1){
// 		pinToggle(&PORT_LED_RX, PIN_LED_RX);
// 		flag_rx = 0;
// 		a = 0;
// 	}
	}while(1);
	
	sleep_mode();
	return 0;
}


void initializare_timer0(void){
	
	TCCR0 = 0x00;
	TCCR0 |= (0 << WGM01)|(0<<WGM00);
	TCCR0 |= (1 << CS02)|(0 << CS01)|(0 << CS00);

	OCR0 = 0x00;
	OCR0=0x7C;
	
	TIMSK = 0x00;
	TIMSK |= (1 << TOIE0);
}

void initializare_contor_timp(void){
	contor_decrementare_timp = timp_pentru_activare_led;
	contor_rx = timp_rx;
}

ISR(TIMER0_OVF_vect){
	///to do : fac o conditie ca sa fie activ sau nu timerul
	if(flag_start_timer == 1){
		contor_rx--;
	}
	//	contor_rx--;
	
	if(contor_rx == 0){
		flag_stop = 1;
		contor_rx = timp_rx;
	}
	
	contor_decrementare_timp--;
	
	if(contor_decrementare_timp == 0){
		flag_timp = 1;
		contor_decrementare_timp = timp_pentru_activare_led;
	}
		
}

void USART_Transmit_caracter(unsigned char data)
{
	//ASTEPT SA SE GOLEASCA BUFFERUL PENTRU TRANSMIS
	while(!(UCSR1A &(1<<UDRE1)));
	
	//PUN DATE IN BUFFER, TRIMIT DATELE
	UDR1 = data;//SCRIU IN REGISTRU
	
}

void USART_Transmit_sir(char *string, int size)
{
	//FUNCTIE CARE IA UN SIR DE CARACTERE SI EXTRAGE CATE UN CARACTER PE RAND, PANA LA TERMINAREA SIRULUI
	//while(*string!= 0x00)
	for(int i = 0; i < size; i++)
	{
		
		USART_Transmit_caracter(*string); ///II MODIFIC VALOAREA
		
		string++; //II MUT ADRESA!!!!
		
	}	
	//USART_Transmit_caracter('\0');
}

	
ISR(USART1_RX_vect)
{
  	buffer[a] = UDR1;
 	flag_start_timer = 1;
//   	if( buffer[a] == '\0'){
//   		flag_rx = 1; ///dupa ce se termina sirul, se activeaza
//   	
// 	  	  }
  	
  	a++;	///incrementez pozit	
	//citesc registru
// 	data = UDR1;
// 	flag_rx = 1;
}


void verificare_led_primire_caracter()
{
	
	if(flag_timp == 1){
		USART_Transmit_sir("test sir   t", 10); ///TRIMITE CATE UN SIR DE CARACTERE DUPA 3 secunde
		pinToggle(&PORT_LED_128, PIN_LED_128);
		flag_timp = 0;
	}
}


void initializare_porturi()
{
	DDRB  = 0xFF; // output
	PORTB  = 0x00; // low

	DDRC  = 0x7F;
	PORTC = 0x00;

	DDRD  = 0xFF;
	PORTD = 0x00;
}

void initializare_devices()
{
	cli();

	initializare_porturi();
	initializare_timer0();
	
	sei();
}

void USART_Initializare_registrii(unsigned int ubrr)
{
	//set baud rate
	UBRR1H = (unsigned char) (ubrr>>8);
	UBRR1L = (unsigned char) ubrr;
	
	//activ doar sa transmita si sa primeasca
	UCSR1B |= (1<<RXCIE1)|(1<<RXEN1)|(1<<TXEN1);
	
	//setez frame format : 8 data , 1 bit stop
	UCSR1C |= (1<<UCSZ11)|(1<<UCSZ10);
	
	//enable global interrupts
	set_sleep_mode(SLEEP_MODE_IDLE);
	sei();
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


