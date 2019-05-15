#include <iostm8s003f3.h>

#define V_REF 3.3

//Конфигурация портов жеткая, так как определены в железе.
int ports_conf(){
  /*
    PA3 - управление светодиодом
    PC7 - выход №1, PC6 - выход №2, PC5 - выход №3, PC4 - выход №4
    РС3 - вход с подтяжкой, РВ4, РВ5 - вход с подтяжкой.
    PD2, PD3 - аналоговые входа.
  */
  PA_CR1 = 0x08; //Переключение в режим тяни/толкай РА3
  PA_DDR = 0x08; //Переключение портов на выход РА3
  PA_ODR = 0x08; //Высталяет РА3 в единицу (Высокий уровень).
  PC_CR1 = 0xF0; //Настройка РС4 - РС5 в режим тяни толкай, РС3 - вход с подтяжкой.
  PC_DDR = 0xF0; //Перевод портов РС4 - РС5 в режим выхода.
  PB_CR1 = 0x30; //РВ4, РВ5 вход с подтяжкой.
  return 0;
}

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
void usart_init(int baud){
  //Установка скорости обмена УАРТА на 9600 для частоты процессора 4000000
/*  UART_BRR1 = 0x1A;
  UART_BRR1 = 0x00; */
//Установка скорости обмена УАРТА на 9600 для частоты процессора 16000000
  UART_BRR1 = 0x68;
  UART_BRR1 = 0x03;
  //Включение передатчика и приемника
  UART_CR2 |= (MASK_UART_CR2_TEN | MASK_UART_CR2_REN);
}
