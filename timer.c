#include <iostm8s003f3.h>
#include "timer.h"

//Настройка таймера
void timer_init(void){
  TIM2_CR1 |= (1 << 0);
  TIM2_PSCR = 0x04;
  TIM2_ARRH = (char)(1000 >> 8);
  TIM2_ARRL = (char)1000;
  TIM2_IER |= (1 << 0);
}

#pragma vector=TIM2_OVR_UIF_vector
__interrupt void TIM2_interrupt(void){
  TMR0++;
  if(TMR0 == 1000){
    PA_ODR_bit.ODR3 = ~PA_ODR_bit.ODR3;
    TMR0 = 0;
}
  TIM2_SR1 = 0;
}