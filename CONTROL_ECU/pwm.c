/*
 * pwm.c
 *
 *  Created on: 12 Oct 2024
 *      Author: farah
 */
#include "pwm.h"
#include "common_macros.h"
#include "avr/io.h" /* To use the timer Registers */
#include "gpio.h"
/*
 * Description :
 *Initialises Timer0 in PWM mode and sets the required duty cycle.
 */
void PWM_Timer0_Start(uint8 duty_cycle)
{
	    TCNT0 = 0; // Set Timer Initial Value to 0

		/* configure the timer
		 * 1. Fast PWM mode FOC0=0
		 * 2. Fast PWM Mode WGM01=1 & WGM00=1
		 * 3. Clear OC0 when match occurs (non inverting mode) COM00=0 & COM01=1
		 * 4. clock = F_CPU/64 CS00=0 CS01=1 CS02=1
		 */

		TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS02)| (1<<CS00);

		OCR0  = (int)((duty_cycle/100.00)*255); /*because duty cycle is in percentage*/

		GPIO_writePin( PORTB_ID , PIN3_ID , PIN_OUTPUT ); //set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.
}


