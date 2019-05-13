#include <iostm8s003f3.h>

#define V_REF 3.3

//������������ ������ ������, ��� ��� ���������� � ������.
int ports_conf(){
  /*
    PA3 - ���������� �����������
    PC7 - ����� �1, PC6 - ����� �2, PC5 - ����� �3, PC4 - ����� �4
    ��3 - ���� � ���������, ��4, ��5 - ���� � ���������.
    PD2, PD3 - ���������� �����.
  */
  PA_CR1 = 0x08; //������������ � ����� ����/������ ��3
  PA_DDR = 0x08; //������������ ������ �� ����� ��3
  PA_ODR = 0x08; //��������� ��3 � ������� (������� �������).
  PC_CR1 = 0xF0; //��������� ��4 - ��5 � ����� ���� ������, ��3 - ���� � ���������.
  PC_DDR = 0xF0; //������� ������ ��4 - ��5 � ����� ������.
  PB_CR1 = 0x30; //��4, ��5 ���� � ���������.
  return 0;
}

int adc_conf(){
  /* Configure ADC channel 4 (PD3)  */
  ADC_CSR |= (1 << 3) | (1 << 4);
  /* Right-align data */
  ADC_CR2 |= MASK_ADC_CR2_ALIGN;
  /* Wake ADC from power down */
  ADC_CR1 |= MASK_ADC_CR1_ADON;
  return 0;
}

unsigned int ADC_read(){
  unsigned int adcH, adcL;
  ADC_CR1 |= MASK_ADC_CR1_ADON;
  while (!(ADC_CSR & MASK_ADC_CSR_EOC));
  adcL = ADC_DRL;
  adcH = ADC_DRH;
  ADC_CSR &= ~MASK_ADC_CSR_EOC; // Clear EOC flag
  return (adcL | (adcH << 8));
}