/*
 * timer.c
 *
 *  Created on: 1 Nov 2024
 *      Author: farah
 */

#include"timer.h"
#include<avr/io.h>
#include<avr/interrupt.h>

static volatile void((*g_Timer0_CallBackPtr)(void))=NULL_PTR;
static volatile void((*g_Timer1_CallBackPtr)(void))=NULL_PTR;
static volatile void((*g_Timer2_CallBackPtr)(void))=NULL_PTR;

ISR(TIMER0_OVF_vect)
{
	if(g_Timer0_CallBackPtr!=NULL_PTR)
	{
	(*g_Timer0_CallBackPtr)();
	}
}

ISR(TIMER0_COMP_vect)
{
	if(g_Timer0_CallBackPtr!=NULL_PTR)
		{
		(*g_Timer0_CallBackPtr)();
		}
}

ISR(TIMER1_OVF_vect)
{
	if(g_Timer1_CallBackPtr!=NULL_PTR)
		{
		(*g_Timer1_CallBackPtr)();
		}
}

ISR(TIMER1_COMPA_vect)
{
	if(g_Timer1_CallBackPtr!=NULL_PTR)
		{
		(*g_Timer1_CallBackPtr)();
		}
}

ISR(TIMER2_OVF_vect)
{
	if(g_Timer2_CallBackPtr!=NULL_PTR)
		{
		(*g_Timer2_CallBackPtr)();
		}
}

ISR(TIMER2_COMP_vect)
{
	if(g_Timer2_CallBackPtr!=NULL_PTR)
		{
		(*g_Timer2_CallBackPtr)();
		}
}
/*
void Timer_init(const Timer_ConfigType*Config_Ptr)
{

	if((Config_Ptr->timer_ID)==TIMER0)
	{
		if((Config_Ptr->timer_mode)==NORMAL)
		{
			TCCR0=((Config_Ptr->timer_clock)&0x07)|(1<<FOC0);
			TCNT0=Config_Ptr->timer_InitialValue;
			TIMSK|=(1<<TOIE0);
		}
		else if((Config_Ptr->timer_mode)==COMPARE_MATCH)
		{

			 TCCR0=(1<<FOC0)|(1<<WGM01)|((Config_Ptr->timer_clock)&0x07);

			 TCNT0=Config_Ptr->timer_InitialValue;
			 OCR0=Config_Ptr ->timer_compare_MatchValue;
			 TIMSK|=(1<<OCIE0);
		}
	}

	else if((Config_Ptr->timer_ID)==TIMER1)
	{
		 if((Config_Ptr->timer_mode)==NORMAL)
		 {
			 TCCR1A=(1<<FOC1A);
			 TCCR1B=((Config_Ptr->timer_clock)&0x07);
			 TIMSK=(1<<TOIE1);
		 }
		 else if((Config_Ptr->timer_mode)==COMPARE_MATCH)
		 {
			 TCCR1B=(1<<WGM12)|((Config_Ptr->timer_clock)&0x07);
			 OCR1A=(Config_Ptr->timer_compare_MatchValue);
			 TIMSK=(1<<OCIE1A);
			 TCCR1A=(1<<FOC1A);


		 }

	}
	else if((Config_Ptr->timer_ID)==TIMER2)
		{
			if((Config_Ptr->timer_mode)==NORMAL)
			{
				TCCR2=((Config_Ptr->timer_clock)&0x07)|(1<<FOC2);
				TCNT2=Config_Ptr->timer_InitialValue;
				TIMSK|=(1<<TOIE2);
			}
			else if((Config_Ptr->timer_mode)==COMPARE_MATCH)
			{

			  TCCR2=(1<<FOC2)|(1<<WGM21)|((Config_Ptr->timer_clock)&0x07);

			  TCNT2=Config_Ptr->timer_InitialValue;
			  OCR2=Config_Ptr ->timer_compare_MatchValue;
			  TIMSK|=(1<<OCIE2);
			}
		}
}
*/
void Timer_init(const Timer_ConfigType *Config_Ptr)
{
	switch(Config_Ptr->timer_ID)
	{
	case TIMER0:

		/* FOC0 = 1 for non-PWM Modes */
		TCCR0 = (1 << FOC0);

		/* Load the initial value to Timer0 counter */
		TCNT0 = (uint8)Config_Ptr->timer_InitialValue;

		if (Config_Ptr->timer_mode == NORMAL)
		{
			/* Enable Timer0 Overflow Interrupt */
			TIMSK |= (1 << TOIE0);
		}
		else if(Config_Ptr->timer_mode ==CTC)
		{
			/* Setting Timer0 to CTC */
			TCCR0 |= (1 << WGM01);

			/* Enable Timer0 Compare Interrupt */
			TIMSK |= (1 << OCIE0);

			/* Storing the Compare Match Value */
			OCR0 = (uint8)Config_Ptr->timer_compare_MatchValue;
		}
		else
		{
			/* Do nothing */
		}

		/* Start Timer0 */
		TCCR0 |= (Config_Ptr->timer_clock);

		break;
	case TIMER1:

		/* FOC1A = 1, FOC1B = 1 for non-PWM Modes */
		TCCR1A = (1 << FOC1A) | (1 << FOC1B);
		TCCR1B = 0;

		/* Load the initial value to Timer1 counter */
		TCNT1 = Config_Ptr->timer_InitialValue;

		if (Config_Ptr->timer_mode == NORMAL)
		{
			/* Enable Timer1 Overflow Interrupt */
			TIMSK |= (1 << TOIE1);
		}
		else if(Config_Ptr->timer_mode == CTC)
		{
			/* Setting CTC Mode */
			TCCR1B = (1 << WGM12);

			/* Enable Timer1 Compare Interrupt */
			TIMSK |= (1 << OCIE1A);

			/* Storing the Compare Match Value */
			OCR1A = Config_Ptr->timer_compare_MatchValue;
		}
		else
		{
			/* Do nothing */
		}

		/* Start Timer1 */
		TCCR1B |= (Config_Ptr->timer_clock);

		break;
	case TIMER2:

		/* FOC2 = 1 for non-PWM Modes */
		TCCR2 = (1 << FOC2);

		/* Load the initial value to Timer2 counter */
		TCNT2 = (uint8)Config_Ptr->timer_InitialValue;

		if (Config_Ptr->timer_mode == NORMAL)
		{
			/* Enable Timer2 Overflow Interrupt */
			TIMSK |= (1 << TOIE2);
		}
		else if(Config_Ptr->timer_mode == CTC)
		{
			/* Setting Timer2 to CTC */
			TCCR2 |= (1 << WGM21);

			/* Enable Timer2 Compare Interrupt */
			TIMSK |= (1 << OCIE2);

			/* Storing the Compare Match Value */
			OCR2 = (uint8)Config_Ptr->timer_compare_MatchValue;
		}
		else
		{
			/* Do nothing */
		}

		/* Start Timer2 */
		TCCR2 |= (Config_Ptr->timer_clock);

		break;
	}
}
/*
/void Timer_deInit(Timer_ID_Type timer_type)
{
	if(timer_type==TIMER0)
	{
		TCCR0&=0xF8; /*CLOCK=0*/
	/*}
	else if(timer_type==TIMER1)
	{
		TCCR1B&=0xF8; /*CLOCK=0*/
	/*}
	else if(timer_type==TIMER2)
	{
		TCCR2&=0xF8;   /*CLOCK=0*/
	/*}
}
*/
void Timer_deInit(Timer_ID_Type timer_type)
{
	/* Clear all registers contents and Disable Interrupts */
	switch(timer_type)
	{
	case TIMER0:
		TCCR0 = 0;
		TCNT0 = 0;
		OCR0 = 0;
		TIMSK &= ~(1 << TOIE0) & ~(1 << OCIE0);
		break;
	case TIMER1:
		TCCR1A = 0;
		TCNT1 = 0;
		OCR1A = 0;
		TIMSK &= ~(1 << TOIE1) & ~(1 << OCIE1A);
		break;
	case TIMER2:
		TCCR2 = 0;
		TCNT2 = 0;
		OCR2 = 0;
		TIMSK &= ~(1 << TOIE2) & ~(1 << OCIE2);
		break;
	}
}
/*
void Timer_setCallBack(void(*a_ptr)(void),Timer_ID_Type a_timer_ID)
{
    if(a_timer_ID==TIMER0)
       {
    	g_Timer0_CallBackPtr=a_ptr;
       }
    else if(a_timer_ID==TIMER1)
       {
       	g_Timer1_CallBackPtr=a_ptr;
       }
    else if(a_timer_ID==TIMER2)
       {
       	g_Timer2_CallBackPtr=a_ptr;
       }
}
*/
void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type a_timer_ID)
{
	switch(a_timer_ID)
	{
	case TIMER0:
		g_Timer0_CallBackPtr= a_ptr;
		break;
	case TIMER1:
		g_Timer1_CallBackPtr = a_ptr;
		break;
	case TIMER2:
		g_Timer2_CallBackPtr = a_ptr;
		break;
	}
}
