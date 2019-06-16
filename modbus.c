#include <iostm8s003f3.h>
#include "modbus.h"
#include "usart.h"
#include "ioport.h"

res_t regs;

int mb_parse_pdu(unsigned char *buff, int len){
  unsigned char *buf_ptr = buff;
  unsigned int CRC_calc = 0;
  unsigned int CRC_rec = 0;
 
  //Проверяем адрес назначения пду
  if(buff[0] == MDB_ADDR){
    //Подсчет контрольной суммы в принятом пду и сравнение с принятой
    CRC_calc = CRC16(buf_ptr, len - 2);
    CRC_rec = (buff[len - 1] << 8) + buff[len - 2];
    
    //Если совпадает, парсим пду в соответствующей функции.
    if(CRC_calc == CRC_rec){
      switch(buff[1]){
        case READ_INPUT_REGISTERS:    read_input_registers(buff);  
                                      break;
        case READ_COIL_STATUS:        read_coil(buff);  
                                      break;
        case FORCE_SINGLE_COIL:       set_output_register(buff);  
                                      break;
        default:  error_handler(buff, MODBUS_EXCEPTION_ILLEGAL_FUNCTION);
                  return MODBUS_EXCEPTION_ILLEGAL_FUNCTION;
      }
    }
    else{ //Если контрольные суммы не совпадают ошибка и выход с ошибкой
      error_handler(buff, MODBUS_BAD_CRC);
      return MODBUS_BAD_CRC;
    }
  }
  else{
     error_handler(buff, MODBUS_ILLEGAL_SLAVE_ADDR); 
     return  MODBUS_ILLEGAL_SLAVE_ADDR;
  }
  return 0;
}

//Чтение входов, выходов
int read_coil(unsigned char *buff){
  unsigned int crc;
  unsigned char *reg_addr = (unsigned char *)(cti(buff, 2));
  unsigned int reg_cnt = cti(buff, 4);
  
  buff[2] = reg_cnt * 2;
  buff[3] = ((unsigned char)(*reg_addr >> 8));
  buff[4] = ((unsigned char)(*reg_addr));
  
  crc = CRC16(buff, PDU_HEADER + buff[2]);
  
  buff[PDU_HEADER + buff[2]] = (unsigned char)crc;
  buff[PDU_HEADER + buff[2] + 1] = (unsigned char)(crc >> 8);
  
  usart_tx_buff(buff, buff[2] + PDU_HEADER + 2);
  
  return 0; 
}

//Установка выходов
int set_output_register(unsigned char *buff){
  unsigned int reg_addr = (unsigned int)(cti(buff, 2));
  unsigned int value = cti(buff, 4);
  
   if(reg_addr > COCNT){
    error_handler(buff, MODBUS_EXCEPTION_ILLEGAL_DATA_ADDRESS);
    return 0;
  }
  
  switch(reg_addr){
    case 0: if(value){
            OUT1 = 1;
          }else{OUT1 = 0;}
          break;
    case 1: if(value){
            OUT2 = 1;
          }else{OUT2 = 0;}
          break;
    case 2: if(value){
            OUT3 = 1;
          }else{OUT3 = 0;}
          break;
    case 3: if(value){
            OUT4 = 1;
          }else{OUT4 = 0;}
          break;
  }
  
  usart_tx_buff(buff, 8);
  
  return 0; 
}

//Чтение входных регистров
int read_input_registers(unsigned char *buff){
  unsigned int crc;
  unsigned int reg_addr = cti(buff, 2);
  unsigned int reg_cnt = cti(buff, 4);
  
  if(reg_cnt > IRCNT){
    error_handler(buff, MODBUS_EXCEPTION_ILLEGAL_DATA_ADDRESS);
    return 0;
  }
  
  if((reg_cnt + reg_addr) > IRCNT){
    error_handler(buff, MODBUS_EXCEPTION_ILLEGAL_DATA_VALUE);
    return 0;
  }
  
  buff[2] = reg_cnt * 2;
  
  unsigned int n = 3;
  for(unsigned int i = reg_addr; i < reg_cnt + reg_addr; i++){
    buff[n] = (unsigned char)(regs.ireg[reg_addr + i] >> 8);
    n++;
    buff[n] = (unsigned char)(regs.ireg[reg_addr + i]);
    n++;
  }

  crc = CRC16(buff, PDU_HEADER + buff[2]);

  buff[PDU_HEADER + buff[2]] = (unsigned char)crc;
  buff[PDU_HEADER + buff[2] + 1] = (unsigned char)(crc >> 8);
  
  usart_tx_buff(buff, buff[2] + PDU_HEADER + 2);
  return 0;
}

//Сообщение распознается, но пишет что неправильная контрольная сумма
void error_handler(unsigned char *buff, char err_numb){
  unsigned int crc;
  buff[1] = 0x8F;
  buff[2] = err_numb;
  crc = CRC16(buff, 2);
  buff[4] |= (unsigned char)(crc >> 8);
  buff[3] |= (unsigned char)(crc);
  usart_tx_buff(buff, 5);
}

//Функция подсчета контрольной суммы работает.
unsigned int CRC16(unsigned char *buf, int len)
{  
  unsigned int crc = 0xFFFF;
  for (int pos = 0; pos < len; pos++)
  {
  crc ^= (unsigned int)buf[pos];    // XOR byte into least sig. byte of crc

  for (int i = 8; i != 0; i--) {    // Loop over each bit
    if ((crc & 0x0001) != 0) {      // If the LSB is set
      crc >>= 1;                    // Shift right and XOR 0xA001
      crc ^= 0xA001;
    }
    else                            // Else LSB is not set
      crc >>= 1;                    // Just shift right
    }
  }

  return crc;
}
