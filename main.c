#include "hardware.h"

unsigned int adcv;
int main( void )
{
  ports_conf();
  adc_conf();
  while(1){
    adcv = ADC_read();
  }
}
