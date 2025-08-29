/*
 * main_control.c
 *
 *  Created on: 1 Nov 2024
 *      Author: farah
 */
#include "std_types.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "twi.h"
#include "timer.h"
#include "buzzer.h"
#include "external_eeprom.h"
#include "dc_motor.h"
#include "pir.h"

/* #DEFINES AS ACK FOR UART COMMUNICATION BETWEEN TWO MICROCONTROLLERS */
#define NEW_PASS         0x01
#define DOOR_PASS_IN     0x02
#define PASS_UPDATE      0x03
#define MATCH            0x04
#define MISMATCH         0x05
#define MOTION           0x06
#define NO_MOTION        0x07
#define WARNING          0x08
#define start_address    0x0005

/*VARIABLE TO REPRESENT TIMER TICKS TO CALCULATE TIME*/
uint8 tick = 0;
/*VARIABLE REPRESENTS PROGRAM STATUS*/
uint8 PROGRAM= 0;
/*VARIABLE REPRESENTS EEPROM RETURN (SUCCESS / ERROR)*/
boolean status = FALSE;
/*VARIABLE REPRESENTS MOTION STATUS KNOWN FROM PIR SENSOR*/
boolean people_entering = FALSE;
/*ARRAY TO STORE FIRST TIME-ENTER PASSWORD*/
uint8 pass[5] = {0};
/*ARRAY TO STORE SECOND TIME-ENTER PASSWORD*/
uint8 pass2[5] = {0};
uint8 i = 0;

/*CALLBACK FUNCTION*/
void new_timer_tick(void)
{
	++tick;   /*INCREMENT TICKS*/
}

int main()
{

	/* UART */
	UART_ConfigType UART_CONFIGURATIONS = {BITS_MODE_8,NO_PARITY, STOPBIT_1BIT, 9600};
	UART_init(&UART_CONFIGURATIONS);

	/* BUZZER */
	Buzzer_init();

	/* I2C */
	TWI_ConfigType I2C_CONFIGURATIONS = {0x01, 2, prescaler_1};
	TWI_init(&I2C_CONFIGURATIONS);

	/* Motor */
	DcMotor_Init();

	/* PIR */
	PIR_init();

	/*TIMER*/
	/*SET INTERRUPT ENABLE*/
	sei();
	Timer_ConfigType TIMER_CONFIGURATIONS = {0, 31250, TIMER1, PRESCALER_256, CTC};
	Timer_init(&TIMER_CONFIGURATIONS);
	Timer_setCallBack(new_timer_tick, TIMER1);


	for(;;)
	{
		PROGRAM= UART_receiveByte();
		if(PROGRAM == NEW_PASS)
		{
			/*FIRST TIME PASSWORD ENTER*/
			for(i = 0; i < 5; ++i)
			{
				pass[i] = UART_receiveByte();
			}
			/*SECOND TIME PASSWORD ENTER*/
			for(i = 0; i < 5; ++i)
			{
				pass2[i] = UART_receiveByte();
			}

			/*CHECKING IF THE TWO PASSWORD ARE MATCHED OR NOT*/
			for(i = 0; i < 5; ++i)
			{
				if(pass[i] != pass2[i])
				{
					/*DIFFERENT PASSWORDS*/
					UART_sendByte(MISMATCH);
					break;
				}
			}
			if(i == 5)
			{
				/*MATCHED PASSWORDS*/
				UART_sendByte(MATCH);

				/*WRITING PASS IN EEPROM*/
				for(i = 0; i < 5; ++i)
				{
					status = EEPROM_writeByte(start_address + i, pass[i]);
					_delay_ms(10);
				}
			}
		}
		else if(PROGRAM==DOOR_PASS_IN)
		{
			/*ASKING USER TO ENTER SYSTEM'S PASSWORD*/
			for(i = 0; i < 5; ++i)
			{
				pass2[i] = UART_receiveByte();
			}

			/*READING SAVED PASSWORD IN EEPROM*/
			for(i = 0; i < 5; ++i)
			{
				status = EEPROM_readByte(start_address + i , &pass[i]);
				_delay_ms(10);
			}

			/*CHECKING IF THE TWO PASSWORD ARE MATCHED OR NOT*/
			for(i = 0; i < 5; ++i)
			{
				if(pass[i] != pass2[i])
				{

					UART_sendByte(MISMATCH);
					break;
				}
			}
			if(i == 5)
			{

				UART_sendByte(MATCH);

				/*UNLOCKING DOOR FOR 15 SECONDS*/
				DcMotor_Rotate(clockwise, 100);
				tick =0;
				while(tick < 15);

			    /*MOTOR STOP*/
				DcMotor_Rotate(stop, 0);

				/*CHECK,IF THERE IS MOTION KEEP MOTOR IN STOP STATE */
				do{
					people_entering = PIR_getState();
					UART_sendByte(MOTION);
				}while(people_entering);

				/*ELSE , CLOSE DOOR */
				UART_sendByte(NO_MOTION);
				tick = 0;
				DcMotor_Rotate(anticlockwise, 100);
				while(tick < 15);
				DcMotor_Rotate(stop, 0);
			}
		}
		else if(PROGRAM == PASS_UPDATE)
		{
			/*ASKING USER TO ENTER SYSTEM'S PASSWORD*/
			for(i = 0; i < 5; ++i)
			{
				pass2[i] = UART_receiveByte();
			}

			/*READING SAVED PASSWORD IN EEPROM*/
			for(i = 0; i < 5; ++i)
			{
				status = EEPROM_readByte(start_address + i , &pass[i]);
				_delay_ms(10);
			}

			/*CHECK*/
			for(i = 0; i < 5; ++i)
			{
				if(pass[i] != pass2[i])
				{
					UART_sendByte(MISMATCH);
					break;
				}
			}
			if(i == 5)
			{

				UART_sendByte(MATCH);

				/*RECIEVING FIRST ENTER-NEW PASS*/
				for(i = 0; i < 5; ++i)
				{
					pass[i] = UART_receiveByte();
				}
				/*RECIEVING SECOND ENTER-NEW PASS*/
				for(i = 0; i < 5; ++i)
				{
					pass2[i] = UART_receiveByte();
				}

				/* CHECK*/
				for(i = 0; i < 5; ++i)
				{
					if(pass[i] != pass2[i])
					{

						UART_sendByte(MISMATCH);
						break;
					}
				}
				if(i == 5)
				{

					UART_sendByte(MATCH);

					/*PASSWORD UPDATE IN EEPROM*/
					for(i = 0; i < 5; ++i)
					{
						status = EEPROM_writeByte(start_address + i, pass[i]);
						_delay_ms(10);
					}
				}
			}
		}
		else if(PROGRAM== WARNING)
		{
			/* Turning Alarm ON */
			Buzzer_on();
			tick = 0;
			while(tick < 60);
			Buzzer_off();
		}
	}
}
