#include <iostm8s003f3.h>
#include "usart.h"

void usart_init(int baud){
  int div;
//Расчет скорости работы Усарта.
  div = XTALL/baud;
//Установка скорости обмена УАРТА на 9600 для частоты процессора 16000000
  UART1_BRR1 = 0x68;
  UART1_BRR2 = 0x03;
  //Включение передатчика и приемника, разрешение прерывания от передатчика и приемник, а так же при простое линии.
  UART1_CR2 |= (UART1_CR2_TEN | UART1_CR2_REN | UART1_CR2_TIEN | UART1_CR2_RIEN | UART1_CR2_ILIEN); 
}

int usart_tx(char byte){
  //Если передача не завершена, то ждем
  while(!UART1_SR_TXE);;
  UART1_DR = byte; //Помещаем байт для отправки в регистр УАРТА
}
