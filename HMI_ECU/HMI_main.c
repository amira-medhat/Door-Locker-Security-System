/*
 * HMI_main.c
 *
 *  Created on: Nov 6, 2023
 *      Author: Amira
 */


#include "lcd.h"
#include "keypad.h"
#include "uart.h"
#include "Timer1.h"
#include "gpio.h"
#include <util/delay.h>
#include <avr/io.h>

#define MC1_READY 0x1F
#define MC2_READY 0x10

uint16 password_1 = 0;
uint16 password_2 = 0;
uint16 password = 0;
volatile uint16 key; /* from the keypad */
volatile uint8 fails = 0; /* for wrong passwords from user */
volatile uint8 visits = 1; /* to indicate which step the user in */
unsigned char flag; /* to check if the password is correct */
volatile uint8 timer_counts = 0;
unsigned char first_pass_flag = 0; // Due to proteus error

void Timer1_CallBack(void)
{
	timer_counts++;
}

void Modules_init(void)
{
	LCD_init();
	LCD_displayString("**Welcome**");
	_delay_ms(1000);
	UART_ConfigType UART_state = {_8_bit_data, disabled, _1_bit, std_baudrate_1};
	UART_init(&UART_state);
	SREG |= (1<<7);
}

void Timer_init(void)
{
	Timer1_ConfigType Timer_state = {0, 23437, CLK_1024, CTC}; //to calculate 3 sec
	Timer1_init(&Timer_state);
	Timer1_setCallBack(Timer1_CallBack);
}

void Get_Password(uint16 *password)
{
	*password = 0;
	int r;
	if (visits == 1 && first_pass_flag == 0)     // Due to an error in proteus
		r = 5;
	else
		r = 6;
	for (int i = 0; i < r ; i++)
	{
		while (KEYPAD_getPressedKey() == -1){}
		key = KEYPAD_getPressedKey();
		_delay_ms(500);
		if((key <= 9) && (key >= 0))
		{
			LCD_displayCharacter('*');
			*password = key + ((*password) * 10);
		}
	}
	first_pass_flag = 1;
}

void Send_Password(uint16 password)
{
	UART_sendByte(MC1_READY);
	while(UART_recieveByte() != MC2_READY){}
	UART_sendByte(password);
}


int main(void)
{
	uint8 menu_option;
	Modules_init();
	while(1)
	{
		switch(visits)
		{
		case 1:

			LCD_clearScreen();
			LCD_displayString("Plz Enter Pass:");
			LCD_moveCursor(1,0);
			Get_Password(&password_1);
			_delay_ms(5);
			while (KEYPAD_getPressedKey() != '='){}
			_delay_ms(5);
			Send_Password(password_1);
			visits++;
			break;
		case 2:
			LCD_clearScreen();
			LCD_moveCursor(0,0);
			LCD_displayString("Plz re-enter:");
			LCD_moveCursor(1,0);
			Get_Password(&password_2);
			_delay_ms(5);
			while (KEYPAD_getPressedKey() != '='){}
			_delay_ms(5);
			Send_Password(password_2);
			UART_sendByte(MC1_READY);
			while(UART_recieveByte() != MC2_READY){}
			flag = UART_recieveByte();
			if (flag == 1)
			{
				visits++;
			}
			else
			{
				LCD_clearScreen();
				LCD_moveCursor(0,0);
				LCD_displayString("**WRONG**");
				_delay_ms(500);
				visits = 1;
			}
			break;
		case 3:
			LCD_clearScreen();
			LCD_moveCursor(0,0);
			LCD_displayString("+ : Open Door");
			LCD_moveCursor(1,0);
			LCD_displayString("- : Change Pass");
			menu_option = KEYPAD_getPressedKey();
			if (menu_option == '+' || menu_option == '-')
			{
				UART_sendByte(MC1_READY);
				while(UART_recieveByte() != MC2_READY){}
				UART_sendByte(menu_option);
				visits++;
			}
			else
			{
				visits = 3;
			}
			break;
		case 4:
			LCD_clearScreen();
			LCD_moveCursor(0,0);
			LCD_displayString("Plz Enter Pass:");
			LCD_moveCursor(1,0);
			Get_Password(&password);
			_delay_ms(5);
			while (KEYPAD_getPressedKey() != '='){}
			_delay_ms(5);
			Send_Password(password);
			while(UART_recieveByte() != MC2_READY){}
			UART_sendByte(MC1_READY);
			flag = UART_recieveByte();
			if (flag == 1)
			{
				fails = 0;
				if (menu_option == '+')
				{
					visits = 5;
				}
				else if(menu_option == '-')
				{
					visits = 1;
				}
			}
			else
			{
				LCD_clearScreen();
				LCD_moveCursor(0,0);
				LCD_displayString("**WRONG**");
				_delay_ms(500);
				fails++;
				if (fails == 3)
				{
					visits = 6;
				}
			}
			break;
		case 5:
			LCD_clearScreen();
			LCD_moveCursor(0,0);
			Timer_init();
			LCD_displayString("Door is Unlocking");
			while(timer_counts < 5){}
			Timer1_deInit();
			timer_counts = 0;
			LCD_clearScreen();
			LCD_moveCursor(0,0);
			Timer_init();
			LCD_displayString("Door is Open");
			while(timer_counts < 1){} // to hold the door for 3 sec
			Timer1_deInit();
			timer_counts = 0;
			LCD_clearScreen();
			LCD_moveCursor(0,0);
			Timer_init();
			LCD_displayString("Door is Locking");
			while(timer_counts < 5){}
			Timer1_deInit();
			timer_counts = 0;
			visits = 3;
			break;
		case 6:
			LCD_clearScreen();
			LCD_moveCursor(0,0);
			LCD_displayString("**ERROR**");
			_delay_ms(1000);
			LCD_clearScreen();
			visits = 3;
			break;


		}

	}
}
