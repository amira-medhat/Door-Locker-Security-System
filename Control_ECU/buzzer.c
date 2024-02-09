/*
 * buzzer.c
 *
 *  Created on: Nov 6, 2023
 *      Author: Amira
 */
#include "buzzer.h"
#include "common_macros.h"
#include <util/delay.h>

void Buzzer_init(void)
{
	GPIO_setupPinDirection(BUZZER_PORT, BUZZER_PIN, PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_LOW);
}

void Buzzer_on(void)
{
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_HIGH);
}

void Buzzer_off(void)
{
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_LOW);
}
