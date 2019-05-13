#include "hardware.h"

int main( void )
{
  unsigned int ad_val;
  ports_conf();
  adc_conf();
  while(1){
    ad_val = ADC_read();
  }
}
