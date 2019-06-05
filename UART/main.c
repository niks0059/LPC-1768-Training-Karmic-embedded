/*program for uart transmition of data from mu's to computer*/
#include "LPC17xx.h"

int main()
{			
			SystemInit();
			uint32_t val;
			LPC_SC->PCONP |= (1<<3);						//powering up the uart0.
			LPC_SC->PCLKSEL0 |=(0<<6);					//Peripheral clock select for uart0.
			LPC_SC->PCLKSEL0 = 0x00000050;			//selecting p0.2 and p0.3 as Tx and Rx.
			LPC_UART0->LCR = 0x00000083;					//Configuring LCR register.
			LPC_UART0->DLL = 0x4E;								//setting DLL value as 78. 
			LPC_UART0->DLM = 0x00;								//setting dlm value.
			
	
			LPC_UART0->FCR = 0x00000007;					//Enable FIFO ,Clear Rx and Tx in FCR Register.
			LPC_UART0->FDR = 0x21;								//passing divaddval and divmul value.
			LPC_UART0->LCR &= ~(1<<7);						//Disabling DLAB bit locks the DLL and DLM values.
	
			while(((LPC_UART0->LSR)&(1<<5))==0);		//wait till THRE is Empty for writing.
			LPC_UART0->THR = 0xAA;									//Writing to the UART Transmit Holding Register.
			while(((LPC_UART0->LSR)&(1<<0))!=0);		//Check Line Status Register and wait for valid data.
			val=LPC_UART0->RBR;											//Read data from RBR Register.
}