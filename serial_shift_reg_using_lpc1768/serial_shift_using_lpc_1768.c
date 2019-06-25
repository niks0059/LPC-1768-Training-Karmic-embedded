#include "lpc17xx.h"
#include "types.h"
int main (void)
{    
		SystemClockUpdate();
		PINSEL1 = PINSEL1   & ~(0x3<<10)
		FIO1DIR = FIO1DIR & ~(1<<21);
		
		PINSEL1 = PINSEL1   & ~(0x3<<12)
		FIO1DIR = FIO1DIR & ~(1<<22);
		
		PINSEL1 = PINSEL1   & ~(0x3<<14)
		FIO1DIR = FIO1DIR & ~(1<<23);
		
		
	