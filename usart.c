#include <iostm8s003f3.h>
#include "usart.h"

char bufr[100];
int buf_ptr = 0;

void usart_init(int baud){
// int div;
//Расчет скорости работы Усарта.
//  div = XTALL/baud;
//Установка скорости обмена УАРТА на 9600 для частоты процессора 16000000
  UART1_BRR1 = 0x68;
  UART1_BRR2 = 0x03;
  //Включение передатчика и приемника, разрешение прерывания от передатчика и приемник, а так же при простое линии.
  UART1_CR2 = (1 << 2) | (1 << 3) | (1 << 5); 
//  PD_ODR |= (1 << 4);
}

void usart_tx(char byte){
  PD_ODR |= (1 << 4);
  //Если передача не завершена, то ждем
  while(!(UART1_SR && UART1_SR_TXE));;
  UART1_DR = byte; //Помещаем байт для отправки в регистр УАРТА
  PD_ODR &= ~(1 << 4);
}

int usart_rx(void){
  while(!(UART1_SR && UART1_SR_RXNE)); 
  return UART1_DR;
}

int usart_tx_buff(char *buf, int len){
  int pntr = 0;
  while(pntr < len){
    usart_tx(buf[pntr]);
    pntr++;
  }
  return pntr;
}

#pragma vector=UART1_T_TC_vector
__interrupt void TX_interrupt(void)
{
  UART1_SR &= ~(1 << 6);
}

#pragma vector=UART1_R_RXNE_vector
__interrupt void RX_interrupt(void)
{
  //Если прерывание пришло по приему нового символа.
  if(UART1_SR & UART!_SR.bit.RXNE){
    bufr[buf_ptr] = UART1_DR; //Флаг прерывания очищается при чтении регистра.
    buf_ptr++;
  }
  //Если прерывание пришло по простою линии.
  if(UART1_SR & UART!_SR.bit.IDLE){
    UART1_SR &= ~(1 << 4); //сбрасываем флаг прерывания
  }
}
