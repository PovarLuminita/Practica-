//INFORMATII!!!!
//Registrii de stare si control : ADCSRA si ADCSRB 
//Registru cu biti de selectie pt multiplexoare ADMUX (selectam ce canal va genera input pt covertor)
//Resigtru ADC - pt rezultat
//Tensiune de referinta - tensiunea de alimentare AVCC
//ADC ul are nevoie de o frecv de ceas pt a stii cat timp dureaza o conversie
//deoarece semnalul de ceas al microcontrollerului este prea rapid, avem nevoie de un prescalar
//F_ADC = F_CPU/prescalar
//free running mode este cel in care convertorul functioneaza continuu, la finalul conversiei va incepe automat urmatoarea conversie
//de fiecare data rezultatul precedent va fi suprascris
//pt a incepe o conversie setam pe registru ADSC 1; acesta nu va fi pus automat pe 0
//return ADCW;

//REGISTRU ADMUX 
//Bit 7:6 - REFS1:0: Reference Selection Bits ? Selecteaza tensiunea de referinta
//Bit 5 - ADLAR ADC: Left Adjust Result ? Modul de aliniere a celor 10 biti. (left-aligned sau right-aligned)
//Bits 3:0 - MUX3:0: Analog Channel Selection Bits ? Selecteaza portul de intrare de pe care se face conversia


//REGISTRU ADCSRA 
// Bit 7 – ADEN: ADC Enable ? Porneste convertorul
// Bit 6 – ADSC: ADC Start Conversion ? Folosit pentru a incepe o conversie
// Bit 5 – ADATE: ADC Auto Trigger Enable ? Porneste modul in care se conversiile ADC incep automat in functie de o sursa specificata in ADCSRB
// Bit 4 – ADIF: ADC Interrupt Flag ? Setat pe 1 atunci cand o conversie s-a terminat. Acest flag este sters automat atunci cand se apeleaza o rutina de tratate a intreruperilor.
// Bit 3 – ADIE: ADC Interrupt Enable ? Porneste intreruperile pentru ADC
// Bits 2:0 – ADPS2:0: ADC Prescaler Select Bits ? Setare prescaler

//RESGISTRU ADCSRB
//Bit 2:0 – ADTS2:0: ADC Auto Trigger Source ? Sursa de la care sa se genereze o noua conversie. Depinde de ADATE din ADCSRA



#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>


#define lcd_port_pin PORTD			    //Define LCD Port
#define lcd_port PORTC
#define lcd_pin_dir  DDRD
#define lcd_data_dir  DDRC			//PD4-PD7 PORT D - pe 4 biti
#define rs PC1			//RS Pin
#define en PC2 			//E Pin

void init_data(void);
void port_init(void);
void adc_init(void);
void init_devices(void);
void initialize (void); //pentru initializare lcd
void lcd_command( unsigned char cmnd );
void lcd_clear();
void lcd_print (char *str); // char str[]
void lcd_setCursor(void);
void init_data_contor(void);

void basic_delay(uint32_t interations);
void pinToggle(volatile uint8_t *port, uint8_t pin);
void pinSet(volatile uint8_t *port, uint8_t pin);
void pinReset(volatile uint8_t *port, uint8_t pin);

ISR(ADC_vect);

#define ADC_PORT PORTC
#define ADC_PIN PINC0

#define LED_ADC_PORT PORTB
#define LED_ADC_PIN PINB0


// uint8_t valoare_old =10;
// uint8_t valoare_new =10;
uint16_t adcValue;
char buffer[16];
#define valoare_adc 120
//uint16_t adcValue_buff;


void init_data_contor(void){
	lcd_data_dir = 0xFF;	//pin D4-D7
	lcd_pin_dir = 0xFF;	//pin D4-D7
}

//initializare lcd
void initialize (void)
{
	lcd_data_dir = 0xFF;	//pin D4-D7
	
	_delay_ms(15);
	lcd_command((1<<4)|(1<<5));
	
	_delay_ms(5);
	lcd_command((1<<4)|(1<<5));
	
	_delay_us(150);
	lcd_command((1<<4)|(1<<5));
	
	lcd_command(0x02);
	lcd_command(0x28);
	lcd_command(0x01);
	
	lcd_command(1<<3);
	
	_delay_ms(2);
}

//pentru a trimite comenzi catre lcd
void lcd_command( unsigned char cmnd )
{
	lcd_port_pin = (lcd_port_pin & 0x0F) | (cmnd & 0xF0);
	lcd_port &= ~ (1<<rs);
	lcd_port|= (1<<en);
	_delay_us(1);
	//lcd_port &= ~ (1<<en);
	//_delay_us(200);
	lcd_port &= ~ (1<<en);
	_delay_us(200);
	lcd_port_pin = (lcd_port_pin & 0x0F) | (cmnd << 4);
	lcd_port|= (1<<en);
	_delay_us(1);
	lcd_port &= ~ (1<<en);
	_delay_us(200);
}


//clear lcd
void lcd_clear()
{
	lcd_command (0x01);		//clear LCD
	_delay_ms(2);
	lcd_command (0x80);		//muta la linia 1, pozitia 1
}

//afisare lcd
void lcd_print (char *str)
{
	int i;
	for(i=0; str[i]!=0; i++)
	{
		lcd_port_pin = (lcd_port_pin & 0x0F) | (str[i] & 0xF0);
		lcd_port |= (1<<rs);
		lcd_port|= (1<<en);
		_delay_us(1);
		_delay_us(200);
		lcd_port &= ~ (1<<en);
		_delay_us(200);
		lcd_port_pin = (lcd_port_pin & 0x0F) | (str[i] << 4);
		lcd_port |= (1<<en);
		_delay_us(1);
		lcd_port &= ~ (1<<en);
		_delay_us(200);
	}
}


void lcd_setCursor()
{
	
	
	lcd_command(1<<1); //return home
	
	_delay_ms(20);

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
}

// void init_data(void){
// 	valoare = ADCL;
// }


void init_devices(void)
{

	cli();

	port_init();
	
	adc_init();
	
	sei(); 
}


void port_init(void)
{
	DDRB  = 0xFF;
	//DDRB = 0x00; //input
	PORTB  = 0x00;

	DDRC  = 0x00;
	//DDRC = 0x00; //input
	PORTC = 0x00;
}


void adc_init(void){
	ADMUX = 0x00;
	ADCSRA = 0x00;
	ADMUX |=  (0<<REFS1)|  (1<<REFS0);
	ACSR = (1<< ACD);
	ADCSRA |= (1<<ADIE);
	sei();
	ADCSRA |=  (1<<ADPS2) |(1<<ADPS1) | (1<<ADPS0)  | (1<<ADSC) | (1<<ADATE);  //setez prescalarul 128
	
	ADCSRA |=  (1<<ADEN);
	ADCSRA |= (1<<ADSC);
}




ISR(ADC_vect)
{
	
// 	if(1)
// 	{
// 		valoare = ADCL;
// 		if(valoare > 0 ){
// 			valoare_old = valoare_new;
// 			valoare_new = valoare;
// 		}
// 		if(valoare_old!= valoare_new){
// 			
// 			if(valoare_new > 120){
// 				pinSet(&LED_ADC_PORT, LED_ADC_PIN);
// 			}
// 			else{
// 				pinReset(&LED_ADC_PORT, LED_ADC_PIN);
// 		}}
//}
	
	adcValue = ADCL;
	adcValue |= (uint16_t)ADCH<<8;
	if(adcValue > valoare_adc)
	{
		pinSet(&LED_ADC_PORT, LED_ADC_PIN);
	}
	else {
		pinReset(&LED_ADC_PORT, LED_ADC_PIN);
	}

}




int main(void)
{
//	init_data();

	init_devices();
	initialize();
	init_data_contor();
	//adc_init();
	
	
	lcd_clear();
	lcd_setCursor();
	lcd_print("TEST ADC");
	//LED_ADC_PORT |= (1<<LED_ADC_PIN);
	_delay_ms(2000);
	
	lcd_clear();
	lcd_setCursor();
	lcd_print("VAL ADC");
	_delay_ms(2000);

	
	while(1)
	{
		lcd_clear();
		lcd_setCursor();
		sprintf(buffer, " %d ", adcValue);
		lcd_print(buffer);
		_delay_ms(1000);
	}
}

//la cateva 100ms sa stocheze valoarea din adcvalue intr o alta variabila 