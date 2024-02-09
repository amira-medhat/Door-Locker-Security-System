/*
 * PWM.c
 *
 *  Created on: Oct 14, 2023
 *      Author: Amira
 */

#include "PWM_TIMER0.h"

#include <avr/io.h>
#include "std_types.h"

void PWM_Timer0_Start(uint8 duty_cycle)
{
	TCNT0 = 0;
	GPIO_setupPinDirection(OC0_PORT, OC0_PIN, PIN_OUTPUT);
	TCCR0 |= (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
	OCR0 = ((uint8)(((float)duty_cycle/100)*TOP));
}
