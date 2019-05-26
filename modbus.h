#define TRUE 1
#define FALSE 0
#define PDU_HEADER      3
#define MDB_ADDR	11
#define IRCNT           10
#define HRCNT           10

//Macro
#define cti(a, b)      (a[b] << 8) | a[b + 1]

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;


//Команды протокола
enum{
	READ_COIL_STATUS = 0x01,	//чтение битов регистров выходов.
	READ_DESCRET_INPUTS,		//чтение битов регистров входов.
	READ_HOLDING_REGISTERS,		//чтение регистров харнения (настройки) 16 бит
	READ_INPUT_REGISTERS,		//чтение рагистров 16 бит (показания разных датчиков)
	FORCE_SINGLE_COIL,			//Установка бит выходов
	PRESET_SINGLE_REGISTER,		//запись в регистры настроек.
};

//Ошибки протокола
enum {
	MODBUS_EXCEPTION_ILLEGAL_FUNCTION = 0x01,	//Принятый код функции не может быть обработан
	MODBUS_EXCEPTION_ILLEGAL_DATA_ADDRESS,		//Адрес данных, указанный в запросе, недоступен.
	MODBUS_EXCEPTION_ILLEGAL_DATA_VALUE,		//Значение, содержащееся в поле данных запроса, является недопустимой величиной.
	MODBUS_EXCEPTION_SLAVE_OR_SERVER_FAILURE,	//
	MODBUS_EXCEPTION_ACKNOWLEDGE,				// Ведомое устройство приняло запрос и обрабатывает его, но это требует много времени. Этот ответ предохраняет ведущее устройство от генерации ошибки тайм-аута
	MODBUS_EXCEPTION_SLAVE_OR_SERVER_BUSY,		//Ведомое устройство занято обработкой команды. Ведущее устройство должно повторить сообщение позже, когда ведомое освободится.
	MODBUS_EXCEPTION_NEGATIVE_ACKNOWLEDGE,		//Ведомое устройство не может выполнить программную функцию, заданную в запросе. Этот код возвращается для неуспешного программного запроса, использующего функции с номерами 13 или 14. Ведущее устройство должно запросить диагностическую информацию или информацию об ошибках от ведомого.
	MODBUS_EXCEPTION_MEMORY_PARITY,				//Ведомое устройство при чтении расширенной памяти обнаружило ошибку контроля четности.
	MODBUS_EXCEPTION_NOT_DEFINED,
	MODBUS_EXCEPTION_GATEWAY_PATH,
	MODBUS_EXCEPTION_GATEWAY_TARGET,
	MODBUS_EXCEPTION_MAX,
	MODBUS_ILLEGAL_SLAVE_ADDR,	//Пду для другого адреса. Не является ошибкой.
	MODBUS_BAD_CRC		//Ошибка контрольной суммы
};

typedef struct{
  unsigned int ireg[10];
  unsigned int hreg[10];
}res_t;


int mb_parse_pdu(unsigned char *buff, int len);
int read_holding_registers(unsigned char *buff);
int read_input_registers(unsigned char *buff);
unsigned int CRC16(unsigned char *buf, int len);
void error_handler(unsigned char *buff, char err_numb);

