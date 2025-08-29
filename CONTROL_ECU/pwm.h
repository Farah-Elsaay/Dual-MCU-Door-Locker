/*
 * pwm.h
 *
 *  Created on: 12 Oct 2024
 *      Author: farah
 */

#ifndef PWM_H_
#define PWM_H_


#include "std_types.h"

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 *Initialises Timer0 in PWM mode and sets the required duty cycle.
 */
void PWM_Timer0_Start(uint8 duty_cycle);


#endif /* PWM_H_ */
