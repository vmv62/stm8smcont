#define TRUE 1
#define FALSE 0
#define FLASH_START 0x08000000

#define MDB_ADDR	25
#define PDU_HEAD_SIZE	3
#define COIL_REG_COUNT	16
#define INP_REG_COUNT	5
#define HLD_REG_COUNT	10
#define CRC_BYTE_CNT	2
//Контрольные флаги(настройки)
#define COILS_HDW	((uint16_t)0x0001) 			//читаем флаги аппаратных регистров или програмных регистров.
#define BTEMP_EN	((uint16_t)0x0002)			//Включение чтения внутреннего датчика температуры.
#define LSENS_EN	((uint16_t)0x0004)			///Включение/отключение датчика света.


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
    MODBUS_ILLEGAL_SLAVE_ADDR,
    MODBUS_BAD_CRC
};

//Названия регистров хранения данных.
//Нужно сохранить в энергонезависимой памяти.
enum{
	MODBUS_HOLDING_REG_SLAVE_ADRESS

};


int mb_parse_pdu(unsigned char *buff, int len);
int read_holding_registers(unsigned char *buff);
int read_input_registers(unsigned char *buff);
unsigned int CRC16(unsigned char *buf, int len);
void error_handler(unsigned char *buff, char err_numb);

