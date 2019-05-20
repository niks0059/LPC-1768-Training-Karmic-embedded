//program for ext interrupt.
#include "lpc17xx.h"
//#include "type.h"
#include "extint.h"
volatile uint32_t count;

int main(void)
{
        
			EINTInit();
			while(1);
}


void EINT3_IRQHandler (void) 						//what action will occur on interrupt
{
			NVIC_Type->ICER[0]=0x00800000;			//clearing the intrpt.
			LPC_SC->EXTINT = EINT3;						// clear interrupt by setting any bit (means reading any bit onto this resets the interrupt) 		
			
		
					
			count++; 														//count 0.
			if (count & 0x01)										// alternate the LED
			{
					LPC_GPIO1->FIOSET |= (1<<29);		// turn off P1.29 	
					LPC_GPIO1->FIOCLR |= (1<<29);		// turn on P1.29 
			}
			else
			{
					LPC_GPIO1->FIOSET |= (1<<29);		// turn on P1.29 	
					LPC_GPIO1->FIOSET |= (1<<29);		// turn off P1.29 
			}

}

uint32_t EINTInit(void)								//initializing the interrupt
{

	
				/*LPC_PINCON->PINSEL4 = 0x00100000;			// set P2.10 as EINT0 and p2.11
				LPC_GPIO2->FIODIR |=1<<29;						// port 1, bit 29       
				LPC_GPIO2->FIOCLR |=1<<29;						// turn off LED */

				LPC_PINCON->PINSEL0 = 0x00000000;
				LPC_GPIOINT->IO0IntEnF = 0x200;			// Port2.10 is falling edge.
				LPC_SC->EXTMODE = EINT0_EDGE;				// INT0 edge trigger 
				LPC_SC->EXTPOLAR = 0;								// INT0 is falling edge by default
				
				LPC_GPIOINT->IO0IntEnR |= (1<<9);		//Enable GPIO interrupts in IO0/2IntEnR.
				NVIC_Type->ISER[0] =0x00800000;			//Interrupts  enabled in Interrupt Set Enable 0 register.

				NVIC_EnableIRQ(EINT3_IRQn);			//enabling the interrupt by passing the irq number.
				return( 1 );
	
}
