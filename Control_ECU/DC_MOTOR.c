/*
 * DC_MOTOR.c
 *
 *  Created on: Oct 15, 2023
 *      Author: Amira
 */

#include "DC_MOTOR.h"
#include "gpio.h"
#include "PWM_TIMER0.h"

void DC_Motor_init(void)
{
	GPIO_setupPinDirection(DC_MOTOR_INPUT_PORT, DC_MOTOR_IN1_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_INPUT_PORT, DC_MOTOR_IN2_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_EN_PORT, DC_MOTOR_EN_PIN, PIN_OUTPUT);
	GPIO_writePin(DC_MOTOR_INPUT_PORT, DC_MOTOR_IN1_PIN, LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_INPUT_PORT, DC_MOTOR_IN2_PIN, LOGIC_LOW);

}

void DC_Motor_rotate(DC_Motor_State state, uint8 speed)
{
	switch(state)
	{
	case OFF:
		GPIO_writePin(DC_MOTOR_INPUT_PORT, DC_MOTOR_IN1_PIN, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_INPUT_PORT, DC_MOTOR_IN2_PIN, LOGIC_LOW);
		break;
	case A_CW:
		GPIO_writePin(DC_MOTOR_INPUT_PORT, DC_MOTOR_IN1_PIN, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_INPUT_PORT, DC_MOTOR_IN2_PIN, LOGIC_HIGH);
		break;
	case CW:
		GPIO_writePin(DC_MOTOR_INPUT_PORT, DC_MOTOR_IN1_PIN, LOGIC_HIGH);
		GPIO_writePin(DC_MOTOR_INPUT_PORT, DC_MOTOR_IN2_PIN, LOGIC_LOW);
		break;
	}
	PWM_Timer0_Start(speed);
}
