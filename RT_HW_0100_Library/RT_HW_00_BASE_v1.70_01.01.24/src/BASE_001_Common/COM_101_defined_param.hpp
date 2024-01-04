

/*
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//						2.Константы в PROGMEM для отображения bool
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	
static const unsigned char  RT_HW_ARR_BOOL_SIGN_1[] PROGMEM= {'1', '+', '*', '#', '|', '>', '+', '*', '+', 255};  
static const unsigned char  RT_HW_ARR_BOOL_SIGN_0[] PROGMEM= {'0', '-', ' ', ' ', '-', '<', '_', '_', ' ', ' '}; 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//    Таблица для расчета контрольной суммы
// Dow-CRC using polynomial X^8 + X^5 + X^4 + X^0
// Tiny 2x16 entry CRC table created by Arjen Lentz
// See http://lentz.com.au/blog/calculating-crc-with-a-tiny-32-entry-lookup-table
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static const uint8_t PROGMEM RT_HW_PGM_TABLE_CRC8_2X16[]= {
0x00, 0x5E, 0xBC, 0xE2, 0x61, 0x3F, 0xDD, 0x83,
0xC2, 0x9C, 0x7E, 0x20, 0xA3, 0xFD, 0x1F, 0x41,
0x00, 0x9D, 0x23, 0xBE, 0x46, 0xDB, 0x65, 0xF8,
0x8C, 0x11, 0xAF, 0x32, 0xCA, 0x57, 0xE9, 0x74
};//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//						1.Библиотеки привязки к Arduino
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if defined(ARDUINO) && (ARDUINO >= 100) 
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <stdint.h>
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//						2.ПАРАМЕТРЫ ИЗ БИБЛИОТЕК FLPROG
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define RT_HW_SENSOR_NOT_ERROR 0
#define RT_HW_SENSOR_NOT_READY_ERROR 1
#define RT_HW_SENSOR_DEVICE_NOT_FOUND_ERROR 2
#define RT_HW_SENSOR_DEVICE_NOT_CORRECT_BUS_NUMBER_ERROR 65
#define RT_HW_SENSOR_DEVICE_NOT_CORRECT_DEVICE_ADDRESS_ERROR 61
#define RT_HW_SENSOR_DEVICE_NOT_DEFINED_ERROR 5
#define RT_HW_SENSOR_DEVICE_NOT_CORRECT_DATA_ERROR 6
#define RT_HW_SENSOR_CRC_ERROR 72
#define RT_HW_SENSOR_WAITING_READ_STEP 0
#define RT_HW_SENSOR_WAITING_DELAY 1
//=================================================================================================
//						Типы UART
//=================================================================================================
#define RT_HW_TYPE_UART_USB   	0		//--USB;
#define RT_HW_TYPE_UART_UART  	1		//--UART
#define RT_HW_TYPE_UART_USART  	2		//--USART;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//						2.ПАРАМЕТРЫ ДЛЯ РАБОТЫ С UART
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//						Коды скоростей UART
//=================================================================================================
#define RT_HW_SPEED_300         0
#define RT_HW_SPEED_600         1
#define RT_HW_SPEED_1200        2
#define RT_HW_SPEED_2400        3
#define RT_HW_SPEED_4800        4
#define RT_HW_SPEED_9600        5
#define RT_HW_SPEED_14400       6
#define RT_HW_SPEED_19200       7
#define RT_HW_SPEED_28800       8
#define RT_HW_SPEED_38400       9
#define RT_HW_SPEED_57600      10
#define RT_HW_SPEED_115200     11
//=================================================================================================
//						 Параметры UART
//=================================================================================================
#define RT_HW_PORT_STOP_BITS_1   1
#define RT_HW_PORT_STOP_BITS_2   2

#define RT_HW_PORT_DATA_BITS_5 	 5
#define RT_HW_PORT_DATA_BITS_6   6
#define RT_HW_PORT_DATA_BITS_7   7
#define RT_HW_PORT_DATA_BITS_8   8

#define RT_HW_PORT_PARITY_NONE   0
#define RT_HW_PORT_PARITY_EVEN   1
#define RT_HW_PORT_PARITY_ODD    2
//=================================================================================================
//						 Коды типов беспроводного интерфейса
//=================================================================================================
#define RT_HW_INTERFACE_ANON	 	0
#define RT_HW_INTERFACE_ETHERNET 	1
#define RT_HW_INTERFACE_WIFI     	2
#define RT_HW_INTERFACE_BLUETOOTH   3	//---Встроенный BlueTooth;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//						3.Макросы для RT_HW_BASE
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define RT_HW_MICROS				micros()				//--Макрос измерения времени в mcs;
#define RT_HW_MILLIS				millis()				//--Макрос измерения времени в ms;
#define RT_HW_BREAK_CHAR			'~'						//--Блокирующий символ для работы со строками;
#define RT_HW_BLANK_CHAR			' '						//--Cимвол для заполнения свободного поля;
#define RT_HW_READ_BYTE_PGM(arr,n) 	pgm_read_byte(&arr[n])	//--Чтение из массива arr n байта;

#define RT_HW_DEFAULT_T_NAN -1
#define RT_HW_DEFAULT_H_NAN  1

#define RT_HW_DELAY(x) if(x>0){do{for(int i=0;i<x;i++) {asm volatile("nop");}}while(0);}  //--Задержка в у.е.
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//						4.Макросы для ускоренных битовых операций
// code для битов 0-7->1,2,4,6,8,16,32,64,128
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define RT_HW_BIT_SET(state,code)               (state) |= (code)			//--Установка битов;
#define RT_HW_BIT_CLEAR(state,code)             (state) &=~(code)			//--Очистка битов;			
#define RT_HW_BIT_BLINK(state,code)             (state) ^= (code)			//--Инверсия битов;
#define RT_HW_BIT_READ(state,code)        (bool((state) &  (code)))			//--Чтение бита;
#define RT_HW_BIT_WRITE(state,code,val) if(val){(state) |= (code);} else {(state) &=~(code);} 	//--Запись битов;									  
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//						5.Макросы min, max
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// can't define max() / min() because of conflicts with C++
#define RT_HW_MIN(a,b)     ((a)<(b)?(a):(b))  
#define RT_HW_MAX(a,b)     ((a)>(b)?(a):(b))
#define RT_HW_MIDLE(a,b,c) ((a < b) ? ((b < c) ? b : ((c < a) ? a : c)) : ((a < c) ? a : ((c < b) ? b : c)))
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define  RT_HW_BIT_QUICK_NUM_0 	1
#define  RT_HW_BIT_QUICK_NUM_1 	2
#define  RT_HW_BIT_QUICK_NUM_2 	4
#define  RT_HW_BIT_QUICK_NUM_3 	8
#define  RT_HW_BIT_QUICK_NUM_4 	16
#define  RT_HW_BIT_QUICK_NUM_5 	32
#define  RT_HW_BIT_QUICK_NUM_6 	64
#define  RT_HW_BIT_QUICK_NUM_7 	128
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//						6.Макросы для управления servo
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define RT_HW_SERVO_PULSE_WIDTH_MIN           544	//--Минимальная ширина импульсаthe shortest pulse sent to a servo; 
#define RT_HW_SERVO_PULSE_WIDTH_MAX          2400 	// the longest pulse sent to a servo
#define RT_HW_SERVO_PULSE_WIDTH_DEFAULT      1500 	// default pulse width when servo is attached
#define RT_HW_SERVO_REFRESH_INTERVAL        20000 	// minumim time to refresh servos in microseconds 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//						7.Макросы для поиска на шине i2c
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++;
#define RT_HW_I2C_FIND_QNT    		 3   	//--Кол-во повторений при поиске адреса;
#define RT_HW_I2C_FIND_PERIOD_CUR   20   	//--Штатный период(ms) при нормальном поиске адреса;
#define RT_HW_I2C_FIND_PERIOD_MAX 2000    	//--Кол-во повторений при поиске адреса;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//						8.Макросы для SPI
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++;
#define RT_HW_SPI_MSBFIRST 1
#define RT_HW_SPI_LSBFIRST 0
#define RT_HW_SPI_MODE0    0
#define RT_HW_SPI_MODE1    1
#define RT_HW_SPI_MODE2    2
#define RT_HW_SPI_MODE3    3
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define RT_HW_DEVICE_DELAY 50
//
#define RT_HW_UNIX_CORRECTION_1900 2208988800UL; //--Разница в сек между датами 01.01.1990 и 01.01.1970;                              
/*
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//    10.Получение даты и времени компиляции из __DATE__ и __TIME__
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
#define RT_HW_YEAR_DIG0 (__DATE__[7]-'0')
#define RT_HW_YEAR_DIG1 (__DATE__[8]-'0')
#define RT_HW_YEAR_DIG2 (__DATE__[9]-'0')
#define RT_HW_YEAR_DIG3 (__DATE__[10]-'0')
#define RT_HW_YEAR_DATE ((RT_HW_YEAR_DIG0*1000) + (RT_HW_YEAR_DIG1*100) + (RT_HW_YEAR_DIG2*10) + (RT_HW_YEAR_DIG3))
//-------------------------------------------------------------------------------------------------
#define RT_HW_MONTH_JAN (__DATE__[0] == 'J' && __DATE__[1] == 'a' && __DATE__[2] == 'n')
#define RT_HW_MONTH_FEB (__DATE__[0] == 'F')
#define RT_HW_MONTH_MAR (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'r')
#define RT_HW_MONTH_APR (__DATE__[0] == 'A' && __DATE__[1] == 'p')
#define RT_HW_MONTH_MAY (__DATE__[0] == 'M' && __DATE__[1] == 'a' && __DATE__[2] == 'y')
#define RT_HW_MONTH_JUN (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'n')
#define RT_HW_MONTH_JUL (__DATE__[0] == 'J' && __DATE__[1] == 'u' && __DATE__[2] == 'l')
#define RT_HW_MONTH_AUG (__DATE__[0] == 'A' && __DATE__[1] == 'u')
#define RT_HW_MONTH_SEP (__DATE__[0] == 'S')
#define RT_HW_MONTH_OCT (__DATE__[0] == 'O')
#define RT_HW_MONTH_NOV (__DATE__[0] == 'N')
#define RT_HW_MONTH_DEC (__DATE__[0] == 'D')
//-------------------------------------------------------------------------------------------------
#define RT_HW_MONTH_DATE ( (RT_HW_MONTH_JAN) ? 1  : (RT_HW_MONTH_FEB) ? 2  : (RT_HW_MONTH_MAR) ? 3 : \
                         (RT_HW_MONTH_APR) ? 4  : (RT_HW_MONTH_MAY) ? 5  : (RT_HW_MONTH_JUN) ? 6 : \
                         (RT_HW_MONTH_JUL) ? 7  : (RT_HW_MONTH_AUG) ? 8  : (RT_HW_MONTH_SEP) ? 9 : \
					    (RT_HW_MONTH_OCT) ? 10 : (RT_HW_MONTH_NOV) ? 11 : (RT_HW_MONTH_DEC) ? 12 : 12)
//-------------------------------------------------------------------------------------------------
#define RT_HW_DAY_DIG0 (((__DATE__[4] >= '0') ? (__DATE__[4]) : '0')-'0')
#define RT_HW_DAY_DIG1   (__DATE__[5]-'0')
#define RT_HW_DAY_DATE   (RT_HW_DAY_DIG0*10 + RT_HW_DAY_DIG1)
//=================================================================================================
#define RT_HW_HOUR_DIG0  (__TIME__[0]-'0')
#define RT_HW_HOUR_DIG1  (__TIME__[1]-'0')
#define RT_HW_HOUR_TIME   (RT_HW_HOUR_DIG0*10 + RT_HW_HOUR_DIG1)
//-------------------------------------------------------------------------------------------------
#define RT_HW_MIN_DIG0   (__TIME__[3]-'0')
#define RT_HW_MIN_DIG1   (__TIME__[4]-'0')
#define RT_HW_MIN_TIME   (RT_HW_MIN_DIG0*10 + RT_HW_MIN_DIG1)
//-------------------------------------------------------------------------------------------------
#define RT_HW_SEC_DIG0   (__TIME__[6]-'0')
#define RT_HW_SEC_DIG1   (__TIME__[7]-'0')
#define RT_HW_SEC_TIME   (RT_HW_SEC_DIG0*10 + RT_HW_SEC_DIG1)
*/


//=================================================================================================






