/*
 * buzzer.c
 *
 *  Created on: 12 Oct 2024
 *      Author: farah
 */
#include"buzzer.h"
#include"gpio.h"
/*
 * Description :
 * Initialises the buzzer pin direction and turn off the buzzer.
 */
void Buzzer_init(void)
{
	GPIO_setupPinDirection( BUZZER_PORT_ID, BUZZER_PIN_ID , PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID , LOGIC_LOW);
}
/*
 * Description :
 * Activates the buzzer.
 */
void Buzzer_on(void)
{
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID , LOGIC_HIGH);
}
/*
 * Description :
 * Deactivates the buzzer.
 */
void Buzzer_off(void)
{
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID , LOGIC_LOW);
}


