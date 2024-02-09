/*
 * buzzer.h
 *
 *  Created on: Nov 6, 2023
 *      Author: Amira
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "gpio.h"

#define BUZZER_PORT PORTC_ID
#define BUZZER_PIN PIN2_ID

void Buzzer_init(void);

void Buzzer_on(void);

void Buzzer_off(void);


#endif /* BUZZER_H_ */
