#include <iostm8s003f3.h>
#include "ioport.h"
#include "usart.h"
#include "adc.h"
#include "clk.h"
#include "modbus.h"


unsigned int adcv;
extern unsigned int msg_recieved;
extern unsigned char buf_ptr;
extern unsigned char bufr[256];
extern res_t regs;

int main( void )
{
  asm("RIM");	//¬ключение прерываний
  ports_conf();
  adc_conf();
 
  if(swclksrc(HSE)){
    usart_init(9600);
  }
  
  while(1){
    if(msg_recieved){
      mb_parse_pdu(bufr, buf_ptr);
        msg_recieved = 0;
        buf_ptr = 0;
    }
    regs.ireg[0] = ADC_read();
    regs.ireg[1] = 1000;
    regs.ireg[2] = 500;
    regs.ireg[3] = 300;
    regs.ireg[4] = 200;
    regs.ireg[5] = 100;
    
  }
}
