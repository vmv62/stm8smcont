#include <iostm8s003f3.h>
#include "usart.h"

void usart_init(int baud){
  //Установка скорости обмена УАРТА на 9600 для частоты процессора 4000000
/*  UART_BRR1 = 0x1A;
  UART_BRR1 = 0x00; */
//Установка скорости обмена УАРТА на 9600 для частоты процессора 16000000
  UART1_BRR1 = 0x68;
  UART1_BRR2 = 0x03;
  //Включение передатчика и приемника
  UART1_CR2 |= (MASK_UART1_CR2_TEN | MASK_UART1_CR2_REN);
}