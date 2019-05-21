#define XTALL 16000000UL



void usart_init(int baud);
void usart_tx(char byte);
int usart_rx(void);
int usart_tx_buff(char *buf, int len);