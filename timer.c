#include <iostm8s003f3.h>
#include "timer.h"

//Настройка таймера
void timer_init(void){
  TIM2_CR1 |= (1 << 7) | (1 << 0);
  TIM2_PSCR = 0x04;
}