/*
* main_func.c
*
*  Author: Asus
*/ 

#include "main_func.h"


void init_data(void){
	contor_sec_1 = timp_sec_1;
}

//intrerupere
ISR(TIMER0_COMPA_vect){
	contor_sec_1--;
	
	if(contor_sec_1 == 0){
		flag1 = 1;
		contor_sec_1 = timp_sec_1;
	}
}
	

void aprinde_led_1()
{
	if(flag1 == 1 )
	{
		pinToggle(&LED2_PORT, LED2_PIN);
		flag1 = 0;
	}
}


//functie care afiseaza pe lcd secundele 00:-s
void afiseaza()
{
	
	
	if(flag1 == 1 )
	{
		lcd_clear();
			
		sec_1++;
		
		
		if(sec_1 ==60){
			
			min_1++;
			sec_1 = 0;
			
				
		}
		if(min_1==60){
			min_1=0;
			sec_1=0;
			
		}
		if(h_1==24){
			h_1=0;
			min_1=0;
			sec_1=0;
			
			
		}
		lcd_setCursor();
		//lcd_setCursor(2, 1);
		sprintf(buffer, "ORA:%d:%d:%d", h_1, min_1, sec_1);
		lcd_print(buffer);
		
		flag1 = 0;
	}
}


//initializare lcd
void initialize (void)
{
	lcd_data_dir = 0xFF;	//Control LCD Pins (D4-D7)
		
	_delay_ms(15);
	lcd_command((1<<4)|(1<<5));
		
	_delay_ms(5);
	lcd_command((1<<4)|(1<<5));
		
	_delay_us(150);
	lcd_command((1<<4)|(1<<5));
		
	lcd_command(0x02);		 //Bit Control
	lcd_command(0x28);       //Control Matrix @ 4-Bit
	lcd_command(0x01);       //Clean LCD
		
	lcd_command(1<<3);
	// 	lcd_command(0x0c);       //Disable Cursor
	// 	lcd_command(0x06);       //Move Cursor
	_delay_ms(2);
}

//pentru a trimite comenzi catre lcd
void lcd_command( unsigned char cmnd )
{
	lcd_port = (lcd_port & 0x0F) | (cmnd & 0xF0);
	lcd_port &= ~ (1<<rs);
	lcd_port |= (1<<en);
	_delay_us(1);
	lcd_port &= ~ (1<<rs);
	_delay_us(200);
	lcd_port = (lcd_port & 0x0F) | (cmnd << 4);
	lcd_port |= (1<<en);
	_delay_us(1);
	lcd_port &= ~ (1<<en);
	_delay_ms(2);
}


//clear lcd
void lcd_clear()
{
	lcd_command (0x01);		//Clear LCD
	_delay_ms(2);			//Wait to clean LCD
	lcd_command (0x80);		//Move to Position Line 1, Position 1
}

//afisare lcd
void lcd_print (char *str)
{
	int i;
	for(i=0; str[i]!=0; i++)
	{
		lcd_port = (lcd_port & 0x0F) | (str[i] & 0xF0);
		lcd_port |= (1<<rs);
		lcd_port|= (1<<en);
		_delay_us(1);
		lcd_port &= ~ (1<<en);
		_delay_us(200);
		lcd_port = (lcd_port & 0x0F) | (str[i] << 4);
		lcd_port |= (1<<en);
		_delay_us(1);
		lcd_port &= ~ (1<<en);
		_delay_ms(2);
	}
}


// void lcd_setCursor(unsigned char x, unsigned char y){
// 	unsigned char adr[] = {0x80, 0xC0, 0x94, 0xD4};
// 		
// 	lcd_command(adr[y-1] + x-1);
// 	_delay_us(100);
//}

void lcd_setCursor()
{
	lcd_data_dir = 0xFF;	//Control LCD Pins (D4-D7)
	//lcd_clear();
	
	//_delay_ms(100);
	
	lcd_command(1<<1); //return home
	
	_delay_ms(200);

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
