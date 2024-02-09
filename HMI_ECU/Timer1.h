
#ifndef TIMER1_H_
#define TIMER1_H_

#include "std_types.h"

/*******************************************************************************
 *                       definitions                                    *
 *******************************************************************************/

typedef enum
{
	NO_CLOCK, CLK_1, CLK_8, CLK_64, CLK_256, CLK_1024
}Timer1_Prescaler;

typedef enum
{
	NORMAL, CTC=4
}Timer1_Mode;

typedef struct {
 uint16 initial_value;
 uint16 compare_value; // it will be used in compare mode only.
 Timer1_Prescaler prescaler;
 Timer1_Mode mode;
} Timer1_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/* Description
â®š Function to initialize the Timer driver*/
void Timer1_init(const Timer1_ConfigType * Config_Ptr);

/*Description
â®š Function to disable the Timer1.*/
void Timer1_deInit(void);


/*Description
â®š Function to set the Call Back function address.*/
void Timer1_setCallBack(void(*a_ptr)(void));


#endif /* TIMER1_H_ */
