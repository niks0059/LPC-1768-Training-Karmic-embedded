#include	"LPC17xx.h"
#define	FEED	LPC_SC-&GT;PLL0FEED=0xAA; LPC_SC-&GT;PLL0FEED=0x55;
void	SystemInit( )	{
LPC_SC-&GT;SCS = 1 &LT;&LT;5;
while (!(LPC_SC-&GT;SCS & (1&LT;&LT;6)));
LPC_SC-&GT;CLKSRCSEL = 1;
// code for the PLL0
LPC_SC-&GT;PLL0CFG =0x0B;	//N=1 & M=12
FEED
LPC_SC-&GT;PLL0CON = 1;	//PLL0 enable
FEED
LPC_SC-&GT;CCLKCFG = 2;	//divide by 3
while (!(LPC_SC-&GT;PLL0STAT & (1&LT;&LT;26)));	//wait until locked
LPC_SC-&GT;PLL0CON |= 1&LT;&LT;1;	//PLL0 connect
FEED
//PLL0 operational
//Code for CLKOUT on pin p1.27
LPC_PINCON-&GT;PINSEL3 = 1&LT;&LT;22; //connect CLK
LPC_SC-&GT;CLKOUTCFG = 0x3&LT;&LT;4; //divide by 4
LPC_SC-&GT;CLKOUTCFG |= 1&LT;&LT;8; //enable cclk
}
int	main( )	{
while (1) {
}
}