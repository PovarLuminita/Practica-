/*
* main_func.c
*
*  Author: Asus
*/

#include "main_func.h"
// 
// void init_data(void){
// 	contor_sec_1 = timp_sec_1;
// }
// 
// //intrerupere
// ISR(TIMER0_COMPA_vect){
// 	contor_sec_1--;
// 	
// 	if(contor_sec_1 == 0){
// 		flag1 = 1;
// 		
// 		sec_1++;
// 		
// 		// 		if(sec_1 ==60){
// 		// 			min_1++;
// 		// 			sec_1 = 0;
// 		// 		}
// 		// 		if(min_1==60){
// 		// 			min_1=0;
// 		// 			sec_1=0;
// 		// 			h_1++;
// 		// 		}
// 		// 		if(h_1==24){
// 		// 			h_1=0;
// 		// 			min_1=0;
// 		// 		sec_1=0;}
// 		
// 		contor_sec_1 = timp_sec_1;
// 	}
// }

//functie care afiseaza pe lcd secundele
// void afiseaza()
// {
	
	//if(flag1 == 1 )
// 	{
// 		lcd_clear();
// 		lcd_setCursor();
		
// 		if(sec_1 ==60){
// 			min_1++;
// 			sec_1 = 0;
// 		}
// 		if(min_1==60){
// 			min_1=0;
// 			sec_1=0;
// 			h_1++;
// 		}
// 		if(h_1==24){
// 			h_1=0;
// 			min_1=0;
// 		sec_1=0;}
		//sprintf(buffer, "ORA %d:%d:%d  ", h_1, min_1, sec_1);
		//lcd_print(buffer);
		
		//flag1 = 0;
	//}
//}


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