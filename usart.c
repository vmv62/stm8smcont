#include <iostm8s003f3.h>
#include "usart.h"

void usart_init(int baud){
  //��������� �������� ������ ����� �� 9600 ��� ������� ���������� 4000000
/*  UART_BRR1 = 0x1A;
  UART_BRR1 = 0x00; */
//��������� �������� ������ ����� �� 9600 ��� ������� ���������� 16000000
  UART1_BRR1 = 0x68;
  UART1_BRR2 = 0x03;
  //��������� ����������� � ���������
  UART1_CR2 |= (MASK_UART1_CR2_TEN | MASK_UART1_CR2_REN);
}