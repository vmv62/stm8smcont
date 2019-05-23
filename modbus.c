#include "modbus.h"
#include "usart.h"


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

int read_input_registers(unsigned char *buff){
 // unsigned int *reg_addr = (unsigned int *)&buff[2];
  unsigned int crc;
//  unsigned int reg_addr = cti(buff, 2);
//  unsigned int reg_cnt = cti(buff, 4);
  
//  for(unsigned int i = 0; i < reg_cnt; i++){
//       buff[i + 2] = 0x00;
//       buff[i + 3] = 0x45;
//  }
  buff[2] = 0x02;
  buff[3] = 0x00;
  buff[4] = 0x45;
  crc = CRC16(buff, 5);

  buff[5] = crc >> 8;
  buff[6] = crc;
/*  
  buff[5] |= 0x58;
  buff[6] |= 0xC1;
 */ 
  usart_tx_buff(buff, 7);
  return 0;
}

void error_handler(unsigned char *buff, char err_numb){
  unsigned int crc;
  buff[1] = 0x8F;
  buff[2] = err_numb;
  crc = CRC16(buff, 3);
  buff[3] |= (crc >> 8);
  buff[4] |= crc;
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
