#include <iostm8s003f3.h>
#include "adc.h"


int adc_conf(){
  /* Configure ADC channel 4 (PD3)  */
  ADC_CSR = 0x08;
  //Отключение тригера шмидта
  ADC_TDRH = 24;
  ADC_TDRL = 24;
  /* Right-align data */
  ADC_CR2 |= MASK_ADC_CR2_ALIGN;
  /* Wake ADC from power down */
  ADC_CR1 |= MASK_ADC_CR1_ADON; //Первое включение. Для начала преобразования нужна повторная операция установки бита.
  return 0;
}

unsigned int ADC_read(int chanel){
 /* unsigned int adcH, adcL;
  ADC_CR2 |= (1 << 3);
  ADC_TDRL = 0x18;
  ADC_CSR = chanel;
  ADC_CR1 |= MASK_ADC_CR1_ADON; //Первое включение. Для начала преобразования нужна повторная операция установки бита.
  ADC_CR1 |= MASK_ADC_CR1_ADON;
  while (!(ADC_CSR & MASK_ADC_CSR_EOC));
  adcL = ADC_DRL; //ADC_DBxRL
  adcH = ADC_DRH; //ADC_DBxRH
  ADC_CSR &= ~MASK_ADC_CSR_EOC; // Clear EOC flag
  */
  
  unsigned int val=0;
  //using ADC in single conversion mode
  ADC_CSR |= (1 << chanel); // select channel
  ADC_CR2 |= (1<<3); // Right Aligned Data
  ADC_CR1 |= (1<<0); // ADC ON 
  ADC_CR1 |= (1<<0); // ADC Start Conversion
  while(ADC_CSR_bit.EOC == 0); // Wait till EOC
  ADC_CSR_bit.EOC = 0;
  val |= (unsigned int)ADC_DRL;
  val |= (unsigned int)ADC_DRH << 8;
  //ADC_CR1 &= ~(1<<0); // ADC Stop Conversion
  //val &= 0x03ff;
  return (val);
}

#pragma vector=ADC1_EOC_vector
__interrupt void ADC_interrupt(void){
  ;;
}