/*
 * Control_ECU_main.c
 *
 *  Created on: Nov 6, 2023
 *      Author: Amira
 */


#include "uart.h"
#include "Timer1.h"
#include "buzzer.h"
#include "twi.h"
#include "DC_MOTOR.h"
#include "external_eeprom.h"
#include <util/delay.h>
#include <avr/io.h>

#define MC2_READY 0x10
#define MC1_READY 0x1F

uint16 password_1 = 0;
uint16 password_2 = 0;
uint16 password = 0;
uint16 password_eeprom = 0;
volatile uint8 visits = 1; /* to indicate which step the user in */
volatile uint8 fails = 0;
volatile uint8 timer_counts = 0;

void Modules_init(void)
{
	UART_ConfigType UART_state = {_8_bit_data, disabled, _1_bit, std_baudrate_1};
	UART_init(&UART_state);
	SREG |= (1<<7);
	TWI_ConfigType TWI_state = {1, 2};
	TWI_init(&TWI_state);
	Buzzer_init();
	DC_Motor_init();
}

void Timer1_CallBack(void)
{
	timer_counts++;
}

void Timer_init(void)
{
	Timer1_ConfigType Timer_state = {0, 23437, CLK_1024, CTC}; //to calculate 3 sec
	Timer1_init(&Timer_state);
	Timer1_setCallBack(Timer1_CallBack);
}

void Door_System(void)
{
	Timer_init();
	DC_Motor_rotate(CW,70);
	while(timer_counts < 5){}
	timer_counts = 0;
	Timer1_deInit();
	Timer_init();
	DC_Motor_rotate(OFF,0);
	while(timer_counts < 1){} // to hold the door for 3 sec
	timer_counts = 0;
	Timer1_deInit();
	Timer_init();
	DC_Motor_rotate(A_CW,70);
	while(timer_counts < 5){}
	DC_Motor_rotate(OFF,0);
	timer_counts = 0;
	Timer1_deInit();
}

void Receive_Password(uint16 *password)
{
	while(UART_recieveByte() != MC1_READY){}
	UART_sendByte(MC2_READY);
	*password = UART_recieveByte();
}

uint8 Passwords_is_equal(uint16 password1, uint16 password2)
{
	if (password1 == password2)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
void Save_Password_in_eeprom(uint16 password)
{
	EEPROM_writeByte(0x0311, password);
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
			Receive_Password(&password_1);
			_delay_ms(150);
			visits++;
			break;
		case 2:
			Receive_Password(&password_2);
			_delay_ms(150);
			if (Passwords_is_equal(password_1, password_2) == 1)
			{
				UART_sendByte(MC2_READY);
				while(UART_recieveByte() != MC1_READY){}
				UART_sendByte(1);
				Save_Password_in_eeprom(password_1);
				_delay_ms(150);
				visits++;
			}
			else
			{
				UART_sendByte(MC2_READY);
				while(UART_recieveByte() != MC1_READY){}
				UART_sendByte(0);
				visits = 1;
			}
			break;
		case 3:
			UART_sendByte(MC2_READY);
			while(UART_recieveByte() != MC1_READY){}
			menu_option = UART_recieveByte();
			if (menu_option == '+' || menu_option == '-')
			{
				visits++;
			}
			else
			{
				visits = 3;
			}
			break;
		case 4:
			Receive_Password(&password);
			_delay_ms(150);
			//Read Password from eeprom
			EEPROM_readByte(0x0311, (uint8 *)&password_eeprom);
			_delay_ms(150);
			if (Passwords_is_equal(password, password_eeprom) == 1)
			{
				fails = 0;
				UART_sendByte(MC2_READY);
				while(UART_recieveByte() != MC1_READY){}
				UART_sendByte(1);
				_delay_ms(150);
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
				UART_sendByte(MC2_READY);
				while(UART_recieveByte() != MC1_READY){}
				UART_sendByte(0);
				fails++;
				if (fails == 3)
				{
					visits = 6;
				}
			}
			break;
		case 5:
			Door_System();
			break;
		case 6:
			Buzzer_on();
			_delay_ms(1000);
			Buzzer_off();
			visits = 3;
			break;
		}
	}
}
