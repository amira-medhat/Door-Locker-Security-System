/*
 * PWM.h
 *
 *  Created on: Oct 14, 2023
 *      Author: Amira
 */

#ifndef PWM_TIMER0_H_
#define PWM_TIMER0_H_

#include "gpio.h"

#define TOP 0xFF
#define OC0_PORT PORTB_ID
#define OC0_PIN PIN3_ID


void PWM_Timer0_Start(uint8 duty_cycle);

#endif /* PWM_TIMER0_H_ */
