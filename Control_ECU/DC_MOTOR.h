/*
 * DC_MOTOR.h
 *
 *  Created on: Oct 15, 2023
 *      Author: Amira
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "gpio.h"

#define DC_MOTOR_INPUT_PORT PORTB_ID
#define DC_MOTOR_IN1_PIN PIN0_ID
#define DC_MOTOR_IN2_PIN PIN1_ID
#define DC_MOTOR_EN_PORT PORTB_ID
#define DC_MOTOR_EN_PIN PIN3_ID

typedef enum{
	OFF,A_CW, CW
}DC_Motor_State;

void DC_Motor_init(void);

void DC_Motor_rotate(DC_Motor_State state, uint8 speed);

#endif /* DC_MOTOR_H_ */
