#include <iostm8s003f3.h>
#include "ioport.h"
#include "usart.h"
#include "adc.h"
#include "clk.h"
#include "modbus.h"
#include "timer.h"


void hardware_init(void);
unsigned int adcv;
extern unsigned int msg_recieved;
extern unsigned int TMR2;
extern unsigned char buf_ptr;
extern unsigned char bufr[256];
extern res_t regs;

int main( void )
{
  hardware_init();
  
  while(1){
    if(msg_recieved){
      mb_parse_pdu(bufr, buf_ptr);
        msg_recieved = 0;
        buf_ptr = 0;
    }
 //   regs.ireg[0] = ADC_read(1);
    regs.ireg[1] = ADC_read(2);
    regs.ireg[2] = ADC_read(3);
    regs.ireg[3] = TMR2;
    regs.ireg[4] = 200;
    regs.ireg[5] = 100;  
  }
}

void hardware_init(void){
  asm("RIM");	//¬ключение прерываний
  ports_conf();
  timer_init();
 // adc_conf();
  if(swclksrc(HSE)){
    usart_init(9600);
  }
}