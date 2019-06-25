
#include "lpc17xx.h"
#include "types.h"
#define PIN_OFFSET 0x14
#define PINSELCT0ADDR 0x4002C000
#define PINMODE0ADDR  0x4002C040
enum state {LOW,HIGH};
enum pin_dir{OFF,ON};
//enum state PinRead{ uint32_t, uint32_t };
enum function_selection
{
                gpio = 0,
                first_alternate = 1,
                second_alternate = 2,
                third_alternate = 3,
                
};
enum pinmode
{
                pull_up = 0,
                repeater =1,
                no_pull_no_down =2,
                on_chip_pull_up =3
};
void delay(void);
void PinSelFunc(uint8_t , uint8_t ,enum function_selection );
void PinModeSel(uint8_t , uint8_t, enum pinmode);
void PinWrite(uint8_t , uint8_t ,enum state );
uint32_t PinRead(uint32_t, uint32_t);
int main (void)
{    
                //uint32_t  i=10000;        
                SystemClockUpdate();
                LPC_PINCON->PINSEL3 = LPC_PINCON->PINSEL3 & ~(3<<26);                    // selecting the GPIO1.select the pin 29 for LED.       
                LPC_GPIO1->FIODIR = LPC_GPIO1->FIODIR | (1<<29);                   //giving the direction 1 means is output for led pin
                //PinModeSel(1,29,2);
                //PinSelFunc(2,1,1);
}
void delay(void)
{
                uint32_t i;
                PinWrite(1,29,HIGH);
                i=8928;
                while(i--);
                PinWrite(1,29,LOW);
                i=8928;
                while(i--);
}


uint32_t  PinRead(uint32_t Port_number, uint32_t Pin_number)
{
                
    uint32_t *port_addr;
    uint32_t return_value;
                
    port_addr =(uint32_t*)( LPC_GPIO_BASE + 0x14 + 0x20 * Port_number);
                
    return_value= ((*port_addr )>> Pin_number) & 0x01;
    return return_value;
}
void PinWrite(uint8_t Port_number, uint8_t Pin_number,enum state pin_state)
{
                uint32_t *port_addr;
                if(pin_state !=0)
                {
                                
                                port_addr =(uint32_t*)((LPC_GPIO_BASE + PIN_OFFSET + 0x20 * Port_number));
                                *port_addr = (*port_addr) | 0x01<<Pin_number;
                }
                else
                {
                                port_addr =(uint32_t*)(LPC_GPIO_BASE+ PIN_OFFSET + (0x20 * Port_number));
                                *port_addr = (*port_addr )& ~(0x01<<Pin_number);
                }

}
void PinDir(uint8_t Port_number,uint8_t Pin_number,enum state pin_dir)
{
                uint32_t *port_addr;

                if(pin_dir !=0)
                {
                                
                                *port_addr =(uint32_t)( LPC_GPIO_BASE + 0x20 * Port_number);
                
                                *port_addr = (*port_addr )| 0x01<<Pin_number;
                }
                else
                {
                                *port_addr =(uint32_t) (LPC_GPIO_BASE + 0x20 * Port_number);
                                *port_addr = (*port_addr )& ~(0x01<<Pin_number);
                }              
}
void PinSelFunc(uint8_t  Port_number, uint8_t Pin_number, enum function_selection function_number)
{
                uint32_t* PortAddr;
                if(Pin_number<=15)
                {
                                PortAddr = (uint32_t*)( PINSELCT0ADDR + Port_number * 8);    
                                *(PortAddr)= *(PortAddr) & ~(3<<Pin_number *2);
                                *(PortAddr)= *(PortAddr) | (function_number<<Pin_number *2);
                }
                else
                {
                                Pin_number = Pin_number -16;
                                
                                PortAddr = (uint32_t*) (PINSELCT0ADDR + 0x4 + (Port_number * 8));
                                *(PortAddr)= *(PortAddr) & ~(3<<Pin_number *2);
                                *(PortAddr)= *(PortAddr) | (function_number<<Pin_number *2);
                }
}

void PinModeSel(uint8_t  Port_number, uint8_t Pin_number, enum pinmode mode)
{
                uint32_t* PortAddr;
                if(Pin_number<=15)
                {
                                PortAddr = (uint32_t*) (PINMODE0ADDR + Port_number * 8);  
                                *(PortAddr)= *(PortAddr) & ~(3<<Pin_number *2);
                                *(PortAddr)= *(PortAddr) | (mode<<Pin_number *2);
                }
                else
                {
                                Pin_number = Pin_number -16;
                                
                                PortAddr = (uint32_t*) (PINMODE0ADDR + 0x4 + (Port_number * 8));
                                *(PortAddr)= *(PortAddr) & ~(3<<Pin_number *2);
                                *(PortAddr)= *(PortAddr) | (mode<<Pin_number *2);
                }
}





uint32_t *port_addr,*port_addr2,*port_addr3;

PortAddr = (uint32_t*)( PINSELCT0ADDR + Port_number * 8);    
*(PortAddr)= *(PortAddr) & ~(3<<Pin_number *2);													//function for pinsel
*(PortAddr)= *(PortAddr) | (0x00<<Pin_number *2);
*port_addr =(uint32_t)( LPC_GPIO_BASE + 0x20 * 1);										//to set the direction of the pin p1.21 as output.
*port_addr = (*port_addr )| 0x01<<21;


PortAddr2 = (uint32_t*)( PINSELCT0ADDR + Port_number * 8);    
*(PortAddr2)= *(PortAddr2) & ~(3<<Pin_number *2);													//function for pinsel
*(PortAddr2)= *(PortAddr2) | (0x00<<Pin_number *2);						//to set the direction of the pin p1.22 as output.
*port_addr2 =(uint32_t)( LPC_GPIO_BASE + 0x20 * 1);
*port_addr2 = (*port_addr2 )| 0x01<<22;.



PortAddr3 = (uint32_t*)( PINSELCT0ADDR + Port_number * 8);    
*(PortAddr3)= *(PortAddr3) & ~(3<<Pin_number *2);													//function for pinsel
*(PortAddr3)= *(PortAddr3) | (0x00<<Pin_number *2);						//to set the direction of the pin p1.23 as output.
*port_addr3 =(uint32_t)( LPC_GPIO_BASE + 0x20 * 1);
*port_addr3 = (*port_addr3 )| 0x01<<23;


void delay(void)
{
                uint32_t i;																			//clock generation of 1khz
                PinWrite(1,29,HIGH);
                i=8928;
                while(i--);
                PinWrite(1,29,LOW);
                i=8928;
                while(i--);
}




