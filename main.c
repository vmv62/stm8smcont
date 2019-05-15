#include "hardware.h"
#include "usart.h"
#include "clk.h"

unsigned int adcv;

int main( void )
{
  ports_conf();
  adc_conf();
  if(enable_hse()){
    usart_init(9600);
  }
  while(1){
    adcv = ADC_read();
  }
}
