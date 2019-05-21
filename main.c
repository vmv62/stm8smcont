#include <iostm8s003f3.h>
#include "ioport.h"
#include "usart.h"
#include "adc.h"
#include "clk.h"


unsigned int adcv;


int main( void )
{
  int simb;
  asm("RIM");	//¬ключение прерываний
  ports_conf();
  adc_conf();
 
  if(swclksrc(HSE)){
    usart_init(9600);
  }
  
  while(1){
    adcv = ADC_read();
 //   simb = usart_rx();
//    usart_tx_buff("Hello!\r\n", 8);
  }
}
