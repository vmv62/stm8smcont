#include <iostm8s003f3.h>
#include "adc.h"


int adc_conf(){
  ;;
  return 0;
}

unsigned int ADC_read(int chanel){
  unsigned int val=0;
  //using ADC in single conversion mode
 // ADC_CSR_bit.CH |= chanel;
  switch(chanel){
  case 1: ADC_CSR |= (1 << 0) | (1 << 1); // select channel
          ADC_CR1_bit.ADON = 0;
          break;
  case 2: ADC_CSR |= (1 << 2); // select channel
          ADC_CR1_bit.ADON = 0;
          break;
    }
  ADC_CR2 |= (1<<3); // Right Aligned Data
  ADC_CR1 |= (1<<0); // ADC ON 
  ADC_CR1 |= (1<<0); // ADC Start Conversion
  while(ADC_CSR_bit.EOC == 0); // Wait till EOC
  ADC_CSR_bit.EOC = 0;
  val |= (unsigned int)ADC_DRL;
  val |= (unsigned int)ADC_DRH << 8;
//  ADC_CR1_bit.ADON = 0;
  return (val);
}

#pragma vector=ADC1_EOC_vector
__interrupt void ADC_interrupt(void){
  ;;
}