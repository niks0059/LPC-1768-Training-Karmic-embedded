//program for match to generate 10% and 90% pulse.

#include "LPC17xx.h"
#include "system_LPC17xx.h"
#define Pulse_Interval 1000						//Pulse_Interval interval.
#define Pulse_Width 10

int main(void)
{
		LPC_SC->PCONP |= (1<<1);						//power on the tiumer 0.
		LPC_SC->PCLKSEL0 &= ~(3<<2);				//seleck the pclk /4.
		LPC_TIM0->CTCR &=	~(3<<0);					//selecting the timer mode.
		LPC_TIM0->MCR |= (3<<0);						//load mcr for interrupt and reset condtn.
		LPC_TIM0->EMR |= (3<<4);						//select toogle functionality.
		LPC_TIM0->PR = 0x11;								//set PR value 17.
	
		LPC_PINCON->PINSEL3 |= (3<<24);			//selecting pin p1.28 as mat0.0.
		LPC_GPIO1->FIODIR |= (1<<28);			//setting direction as output.
		
		LPC_TIM0->TCR |= (1<<0);						//enabling the timer.
		NVIC_EnableIRQ(TIMER0_IRQn);				//enabling timer0 intrupt.

	
}
void TIMER0_IRQHandler(void)
{
		
		LPC_TIM0->IR |= (1<<0);							//reset the intrupt in ir reg. 
		
		if((LPC_PINCON->PINSEL3 |= (3<<24))	== 0)
		{
				LPC_TIM0->MR0 = ((100-Pulse_Width)*Pulse_Interval)/100;				//pusle OFF interval.
		}
		else
		{
				LPC_TIM0->MR0 = (Pulse_Width*Pulse_Interval)/100;				//pusle ON interval.
		}
}
