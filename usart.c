#include <iostm8s003f3.h>
#include "usart.h"

unsigned char bufr[256];
char buf_ptr = 0;
unsigned int tx_len = 0;
unsigned int msg_recieved = 0;

void usart_init(int baud){
//Установка скорости обмена УАРТА на 9600 для частоты процессора 16000000
  UART1_BRR1 = 0x68;
  UART1_BRR2 = 0x03;
  //Включение передатчика и приемника, разрешение прерывания от передатчика и приемник, а так же при простое линии.
  UART1_CR2 = (1 << 2) | (1 << 3) | (1 << 5) | (1 << 4); 
//  PD_ODR |= (1 << 4);
}

void usart_tx(unsigned char byte){
  PD_ODR |= (1 << 4);
  //Если передача не завершена, то ждем
  //while(!(UART1_SR && UART1_SR_TXE));;
  while(!UART1_SR_bit.TC);;
  UART1_SR_bit.TC = 0;
  UART1_DR = byte; //Помещаем байт для отправки в регистр УАРТА
  PD_ODR &= ~(1 << 4);
}

int usart_rx(void){
  while(!(UART1_SR && UART1_SR_RXNE)); 
  return UART1_DR;
}

int usart_tx_buff(unsigned char *buf, int len){
  tx_len = len;
  for(unsigned char i = 0; i < len + 1; i++){

    usart_tx(*buf);
    buf++;
  }
//  UART1_CR2_bit.TIEN = 0;
  return 0;
}

#pragma vector=UART1_T_TC_vector
__interrupt void TX_interrupt(void)
{
 /* if(UART1_SR_bit.TXE){
    UART1_DR = bufr[buf_ptr];
    buf_ptr++;
    if(buf_ptr >= tx_len){
      UART1_CR2_bit.TIEN = 0;
    }
  }*/
  UART1_SR_bit.TXE = 0;
  UART1_SR_bit.TC = 0;
}

#pragma vector=UART1_R_RXNE_vector
__interrupt void RX_interrupt(void)
{
  //Если прерывание пришло по приему нового символа.
  if(UART1_SR_bit.RXNE){
    UART1_CR2_bit.ILIEN = 1;
    bufr[buf_ptr] = UART1_DR; //Флаг прерывания очищается при чтении регистра.
    buf_ptr++;
  }
  //Если прерывание пришло по простою линии.
  if(UART1_SR_bit.IDLE){
    UART1_CR2_bit.ILIEN = 0;
    UART1_SR_bit.IDLE = 0; //сбрасываем флаг прерывания
    msg_recieved = 1;
  }
}
