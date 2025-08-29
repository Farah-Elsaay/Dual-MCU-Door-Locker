/*
 * dc_motor.c
 *
 *  Created on: 12 Oct 2024
 *      Author: farah
 */
#include"dc_motor.h"
#include"gpio.h"
#include"pwm.h"
/*
 * Description :
 * Initialises the DC motor by setting the direction for the motor pins and stopping the
 * motor at the beginning
 */
void DcMotor_Init(void)
{
	 GPIO_setupPinDirection( IN1_PORT_ID , IN1_PIN_ID , PIN_OUTPUT);
     GPIO_setupPinDirection( IN2_PORT_ID , IN2_PIN_ID , PIN_OUTPUT);
     GPIO_setupPinDirection( ENABLE1_PORT_ID , ENABLE1_PIN_ID , PIN_OUTPUT);

	 GPIO_writePin( IN1_PORT_ID , IN1_PIN_ID, LOGIC_LOW);
	 GPIO_writePin( IN2_PORT_ID , IN2_PIN_ID , LOGIC_LOW);


}
/*
 * Description :
 * Controls the motor's state (Clockwise/Anti-Clockwise/Stop) and adjusts the speed based
 * on the input duty cycle
 */
void DcMotor_Rotate(DcMotor_State state , uint8 speed)
{
	 PWM_Timer0_Start(speed);
	 switch(state)
		 {
		 case clockwise:
			 GPIO_writePin( IN1_PORT_ID , IN1_PIN_ID, LOGIC_HIGH);
			 GPIO_writePin( IN2_PORT_ID , IN2_PIN_ID , LOGIC_LOW);
			 break;
		 case anticlockwise:
			 GPIO_writePin( IN1_PORT_ID , IN1_PIN_ID, LOGIC_LOW);
		     GPIO_writePin( IN2_PORT_ID , IN2_PIN_ID , LOGIC_HIGH);
			 break;
		 case stop:
			 GPIO_writePin( IN1_PORT_ID , IN1_PIN_ID, LOGIC_LOW);
			 GPIO_writePin( IN2_PORT_ID , IN2_PIN_ID , LOGIC_LOW);
			 break;
		 }

}


