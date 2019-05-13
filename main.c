#include "hardware.h"
int main( void )
{
  ports_conf();
  adc_conf();
  while(1);;
}
