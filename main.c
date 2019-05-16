#include "ioport.h"
#include "usart.h"
#include "clk.h"
#include "adc.h"

unsigned int adcv;

int main( void )
{
  ports_conf();
  adc_conf();
  if(swclksrc(HSE)){
    usart_init(9600);
  }
  while(1){
    adcv = ADC_read();
  }
}
