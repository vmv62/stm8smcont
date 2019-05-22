#define XTALL 16000000UL

void usart_init(int baud);
void usart_tx(unsigned char byte);
int usart_rx(void);
int usart_tx_buff(unsigned char *buf, int len);
