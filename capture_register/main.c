//program for capture refgister.
#include "LPC17xx.h"
#include "system_LPC17xx.h"

uint32_t A,B,HighCount,LowCount;
uint32_t  PinRead(uint32_t Port_number, uint32_t Pin_number)
{
                
                                uint32_t *port_addr;
                  uint32_t return_value;
                
                                port_addr =(uint32_t*)( LPC_GPIO_BASE + 0x14 + 0x20 * Port_number);
                
                                return_value= ((*port_addr )>> Pin_number) & 0x01;
                return return_value;
}

int main()
{
		SystemInit();
		LPC_SC->PCONP |= (1<<1);						//power on the tiumer 0.
		LPC_SC->PCLKSEL0 &= ~(3<<2);				//seleck the pclk /4.
		LPC_TIM0->CTCR &=	~(3<<0);					//selecting the timer mode.
		LPC_TIM0->PR = 0x11;								//set PR value 17.
		LPC_PINCON->PINSEL3 |= (3<<20);			//selecting capture0.0 on pin p1.26.
		//LPC_GPIO1->FIODIR |= (0<<26);				//setting direction as input.
		//LPC_GPIO1->FIOCLR |= (1<<26);				//clearing the pin.
		//LPC_PINCON->PINMODE3 |=(2<<20);			//selecting niether pull upnor pull down for p1.26.
		LPC_TIM0->CCR |=(7 << 0);						// rising edge falling edge and interrupt on cap0.0 pin 1.26
		
	
		LPC_TIM0->TCR |= (1<<0);						//enabling the timer.
		NVIC_EnableIRQ(TIMER0_IRQn);				//enabling timer0 intrupt.
	  while(1);
}

void TIMER0_IRQHandler(void)
{
	LPC_TIM0->IR |= (1<<0);								//reset the intrupt in ir reg.
	
	if( PinRead(1,26) == 0)
	{
				B = LPC_TIM0->CR0;							//capture the value from cr0.
		HighCount = B - A;
		
	}
	else	
	{
			A= LPC_TIM0->CR0;									//capture the value from cr0.
			LowCount = A - B;
		
	}
}
