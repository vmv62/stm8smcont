#include <iostm8s003f3.h>
#include "adc.h"


int adc_conf(){
  /* Configure ADC channel 4 (PD3)  */
  ADC_CSR = 0x38;
  //Отключение тригера шмидта
  ADC_TDRH = 24;
  ADC_TDRL = 24;
  /* Right-align data */
  ADC_CR2 |= MASK_ADC_CR2_ALIGN;
  /* Wake ADC from power down */
  ADC_CR1 |= MASK_ADC_CR1_ADON; //Первое включение. Для начала преобразования нужна повторная операция установки бита.
  return 0;
}

unsigned int ADC_read(){
  unsigned int adcH, adcL;
  ADC_CR1 |= MASK_ADC_CR1_ADON;
  while (!(ADC_CSR & MASK_ADC_CSR_EOC));
  adcL = ADC_DRL; //ADC_DBxRL
  adcH = ADC_DRH; //ADC_DBxRH
  ADC_CSR &= ~MASK_ADC_CSR_EOC; // Clear EOC flag
  return (adcL | (adcH << 8));
}