LPC_SC->PCONP |= (1<<22);		//powering on timer.
LPC_SC->PCLKSEL1 &= ~(0x11<<12);	//selecting timer2 in pclksel1 reg.
LPC_TIM2->PR = 0x01;			//setting pr divider value as 1
LPC_PWM->CTCR &= ~(0x11<<0);		//timer mode with inc on PCLK rising Edge.
LPC_TIM2->TCR = 0x01;			//enabling the timer 0th bit as 1.

uin32_t a =LPC_TIM2->TC;
Systeminit();

a=((TC-a)*0.05);			//calculating time required.
while(1);

-------------------------------------------------------------------------------------------------

500ms delay using the timer interrupts

LPC_SC->PCONP |= (1<<22);		//powering on timer.
LPC_SC->PCLKSEL1 |= (0<<12);	//selecting timer2 in pclksel1 reg.	
LPC_TIM2->PR = 0x0011;			//setting pr value as 17	
LPC_TIM2->CTCR |= (3<<0);		//timer mode with inc on PCLK rising Edge.
LPC_PINCON->PINSEL9 |=(1<<25);		//selecting mat2.0 pin for timer 2.
LPC_TIM2->MR2 = 0x7A120;		//loading value in MR registers.
LPC_TIM2->MCR |=(1<<7);			//Reset on MR2: the TC will be reset if MR2 matches it.
LPC_TIM2->EMR = 0x00000300;		//When match occurs TC and MR0, this bit will toggle.
LPC_TIM2->TCR |= (1<<0);		//timer counter & prescale counter are enabled for counting.
while(1);

------------------------------------------------------------------------------------------------------
Using intrupts in timer.

#include "lpc17xx.h"
/*
#define BLINK_INTERVAL	20

extern uint32_t timer0_m0_counter, timer1_m0_counter;
extern uint32_t timer0_m1_counter, timer1_m1_counter;

uint32_t i,j,a;*/
int main (void)
{	    		
  
	SystemInit();
	/*
	LPC_SC->PCONP |= (1<<22);		//powering on timer.
	LPC_SC->PCLKSEL1 &= ~(0x11<<12);	//selecting timer2 in pclksel1 reg.
	LPC_TIM2->PR = 0x01;			//setting pr divider value as 1
	LPC_TIM2->CTCR &= ~(0x11<<0);		//timer mode with inc on PCLK rising Edge.
	LPC_TIM2->TCR = 0x01;			//enabling the timer 0th bit as 1.

	i =LPC_TIM2->TC;
	SystemClockUpdate();
	j =LPC_TIM2->TC;
	a=((j-i)*0.05);			//calculating time required.
	//while(1);
*/
/*Sample program for 500ms delay using timer2*/
	
LPC_SC->PCONP |= (1<<1);						//powering on timer0.
//LPC_SC->PCLKSEL1 = (0x00<<1);		//selecting timer2 in pclksel1 reg.	
LPC_TIM0->PR = 0x11;							//setting pr value as 17	
LPC_TIM0->CTCR |=0x00;				//timer mode with inc on PCLK rising Edge.
LPC_PINCON->PINSEL3 |=(3<<24);			//selecting mat2.0 pin for timer 2.
LPC_GPIO1->FIODIR = 0xffffffff;
LPC_TIM0->MR0 = 0x7A120;						//loading value in MR registers.
//LPC_TIM0->MCR |=(1<<1);							//Reset on MR2: the TC will be reset if MR2 matches it.
LPC_TIM0->MCR |=(1<<0);							//Interrupt on MR0: an interrupt is generated when MR0 matches the value in the TC.

LPC_TIM0->EMR = 0x3 << 4;					//When match occurs TC and MR0, this bit will toggle.
LPC_TIM0->TCR |= 0x01;						//timer counter & prescale counter are enabled for counting.
//while(1);

}


void TIMER0_IRQHandler(void)
{
		LPC_PINCON->PINSEL3 |= (0x00<<26);
		LPC_GPIO1->FIODIR |=  (1<<29);
		LPC_GPIO1->FIOSET |=(1<<29);
		LPC_TIM0->IR |= (1<<0);
}

