#define IN1 PB_IDR_bit.IDR4
#define IN2 PB_IDR_bit.IDR5
#define IN3 PC_IDR_bit.IDR3

#define OUT1 PC_ODR_bit.ODR4
#define OUT2 PC_ODR_bit.ODR5
#define OUT3 PC_ODR_bit.ODR6
#define OUT4 PC_ODR_bit.ODR7

int ports_conf();
void usart_init(int baud);