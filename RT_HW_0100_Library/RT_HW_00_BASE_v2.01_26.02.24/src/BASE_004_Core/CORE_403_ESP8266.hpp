//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//						Программная среда ESP8266
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//----------------------0.Идентификация программной среды------------------------------------------
#if !defined(RT_HW_CORE_DEFINED) && defined(RT_HW_CORE_ESP8266)
#define RT_HW_CORE_DEFINED          							//--Идентификатор программной среды;
//----------------------1.Основные параметры-------------------------------------------------------
#define	RT_HW_ARCH_CODE        		3							//--Код архитектуры;
#define RT_HW_ARCH_NAME        		"ESP8266"					//--Наименование архитектуры;
#define RT_HW_CORE_NAME        		"ESP8266"	 				//--Наименование программной среды
#define RT_HW_BOARD_DEPTH_SYS  	12								//--Системная разрядность;
#define RT_HW_BOARD_DEPTH_PWM  	10								//--PWM разрядность;
#define RT_HW_BOARD_DEPTH_ADC  	10								//--ADC разрядность;
#define RT_HW_BOARD_DRIFT_ADC  	3								//--ADC дрейф показаний;
#define RT_HW_BOARD_NULL_ADC  	4								//--ADC дрейф нуля;
//----------------------2.Дополнительные макросы---------------------------------------------------
#define RT_HW_IRAM_ATTR				IRAM_ATTR					//--Атрибут для совместимости c ESP8266;
#define RT_HW_PWM_PERMIT_SET_RESOLUTION							//--Разрешение изменения разрешения PWM;
#define RT_HW_PWM_FREQ              1000                        //--Частота для PWM умолчанию;
//----------------------3.Общие библиотеки---------------------------------------------------------
#include <pgmspace.h>											//--Работа с PROGMEM;
//----------------------4.Таймеры------------------------------------------------------------------
//----------------------5.Интерфейсы UART----------------------------------------------------------
#define RT_HW_UART_SPEED		115200							//--Скорость UART; 
#define RT_HW_UART1_BLOCK_READ									//--Блокировка функций чтения с UART1;	
#include <SoftwareSerial.h>										//--Библиотека программного UART;
//----------------------6.Интерфейсы i2c-----------------------------------------------------------
#define RT_HW_I2C_SPEED          	100000UL					//--Код скорости i2c по умолчанию (->100kHz);
#include <Wire.h>												//--Подключение библиотеки i2c;
//----------------------7.Интерфейсы SPI-----------------------------------------------------------
#define RT_HW_SPI_INTERRUPT_MODE	0							//--Режим работы с прерываниями SPI;
#define RT_HW_SPI_SPEED				4000000UL					//--Скорость SPI в Гц; 
#define RT_HW_SPN_DELAY			0								//--Задержка для RT_HW_PIN_DIR_WRITE_HIGH->;
#include <SPI.h>												//--Подключение библиотеки SPI;
//----------------------8.Интерфейс CAN------------------------------------------------------------
//----------------------9.Интерфейс Wi-Fi----------------------------------------------------------
//----------------------20.Макросы для работы c пинами через функции WIRING------------------------ 
#define RT_HW_PIN_MODE_INPUT  					INPUT			//--Дискретный вход;
#define RT_HW_PIN_MODE_OUTPUT  					OUTPUT			//--Дискретный выход;
#define RT_HW_PIN_MODE_INPUT_PULLUP  			INPUT_PULLUP 	//--Дискретный вход с подтяжкой к +Vcc;
//----------------------21.Макросы для совместимости с STM32---------------------------------------
#define RT_HW_PIN_MODE_INPUT_FLOATING  			INPUT			//--Дискретный вход - аналог INPUT;
#define RT_HW_PIN_MODE_INPUT_PULLDOWN  			INPUT			//--Дискретный вход с подтяжкой к GND;
#define RT_HW_PIN_MODE_INPUT_ANALOG  			INPUT			//--Аналоговый вход;
#define RT_HW_PIN_MODE_OUTPUT_OPEN_DRAIN  		OUTPUT			//--Дискретный выход с открытым выходом;
#define RT_HW_PIN_MODE_OUTPUT_PWM				OUTPUT			//--ШИМ выход;
#define RT_HW_PIN_MODE_OUTPUT_PWM_OPEN_DRAIN	OUTPUT			//--ШИМ выход с открытым коллектором;
//----------------------22.Базовый размер переменной и структура для GPIO---------------------------
#define RT_HW_DATE_TYPE 		uint32_t		 				//--Тип базовой переменной при прямом управлении пинами;
struct  RT_HW_PIN_DIR_ID {uint8_t pin=255; uint8_t dir=0; uint8_t bit; char mode='N'; uint32_t GPFFS_pin; uint32_t LEFT_PIN; uint32_t LEFT_GPCI; uint32_t LEFT_GPCD; uint32_t LEFT_GPFPU;};

//----------------------23.Встроенные функции управления GPIO--------------------------------------
static inline __attribute__((always_inline))		//--Чтение дискретного пина
bool RT_HW_BASE_digitalReadFast(RT_HW_PIN_DIR_ID &id) {if(id.pin < 16){return GPIP(id.pin);} else if(id.pin == 16){return GP16I & 0x01;} return 0;};
//----------------------24.Макросы прямого управления пинами---------------------------------------
#define RT_HW_PIN_DIR_SET_ID(id,p)        id.pin=p; id.GPFFS_pin=GPFFS(GPFFS_GPIO(id.pin)); id.LEFT_PIN=(1<<id.pin); id.LEFT_GPCI=(0xF<<GPCI);\
                                                    id.LEFT_GPCD=(1<<GPCD); id.LEFT_GPFPU=(1<<GPFPU);
#define RT_HW_PIN_DIR_MODE_INPUT(id)      GPF(id.pin) =id.GPFFS_pin; GPEC=id.LEFT_PIN; GPC(id.pin)=(GPC(id.pin) & id.LEFT_GPCI) | (id.LEFT_GPCD);
#define RT_HW_PIN_DIR_MODE_PULLUP(id)     GPF(id.pin) =id.GPFFS_pin; GPEC=id.LEFT_PIN; GPC(id.pin)=(GPC(id.pin) & id.LEFT_GPCI) | (id.LEFT_GPCD); GPF(id.pin)|=id.LEFT_GPFPU;
#define RT_HW_PIN_DIR_MODE_OUTPUT(id)     GPF(id.pin)=id.GPFFS_pin; GPC(id.pin)=GPC(id.pin) & id.LEFT_GPCI; GPES = id.LEFT_PIN;
#define RT_HW_PIN_DIR_READ(id)            RT_HW_BASE_digitalReadFast(id)
#define RT_HW_PIN_DIR_WRITE_LOW(id)       if(id.pin<16){GPOC=id.LEFT_PIN;} else if(id.pin==16){GP16O |=  1;}
#define RT_HW_PIN_DIR_WRITE_HIGH(id)      if(id.pin<16){GPOS=id.LEFT_PIN;} else if(id.pin==16){GP16O &= ~1;}
#define RT_HW_PIN_DIR_WRITE(id,val)       if(id.pin<16){if(val){GPOS=id.LEFT_PIN;} else{GPOC=id.LEFT_PIN;}} else if(id.pin==16){if(val){GP16O |= 1;} else{GP16O &= ~1;}}
#define DIRECT_WRITE_LOW(base, mask)    (GPOC = (mask))             //GPIO_OUT_W1TC_ADDRESS
#define DIRECT_WRITE_HIGH(base, mask)   (GPOS = (mask))             //GPIO_OUT_W1TS_ADDRESS
//----------------------25.Макросы для 1-Wire------------------------------------------------------
struct  RT_HW_PIN_ONEWIRE_ID {uint32_t pin; uint32_t dir=0; uint32_t GPFFS_pin; uint32_t LEFT_PIN;  uint32_t LEFT_GPCI; uint32_t LEFT_GPCD; uint32_t LEFT_GPFPU;};
#define RT_HW_PIN_ONEWIRE_SET_ID(id,p) 	    	RT_HW_PIN_DIR_SET_ID(id,p)
#define RT_HW_PIN_ONEWIRE_NOINTERRUTS           //noInterrupts(); 
#define RT_HW_PIN_ONEWIRE_INTERRUTS             //interrupts();
#define RT_HW_PIN_ONEWIRE_MODE_INPUT(id)        RT_HW_PIN_ONEWIRE_NOINTERRUTS                               RT_HW_PIN_DIR_MODE_INPUT(id)  RT_HW_PIN_ONEWIRE_INTERRUTS
#define RT_HW_PIN_ONEWIRE_MODE_INPUT_LOW(id)    RT_HW_PIN_ONEWIRE_NOINTERRUTS  RT_HW_PIN_DIR_MODE_INPUT(id) RT_HW_PIN_DIR_WRITE_LOW(id)   RT_HW_PIN_ONEWIRE_INTERRUTS
#define RT_HW_PIN_ONEWIRE_MODE_OUTPUT_LOW(id)   RT_HW_PIN_ONEWIRE_NOINTERRUTS  RT_HW_PIN_DIR_WRITE_LOW(id)  RT_HW_PIN_DIR_MODE_OUTPUT(id) RT_HW_PIN_ONEWIRE_INTERRUTS
#define RT_HW_PIN_ONEWIRE_WRITE_HIGH(id)        RT_HW_PIN_ONEWIRE_NOINTERRUTS  RT_HW_PIN_DIR_WRITE_HIGH(id)                               RT_HW_PIN_ONEWIRE_INTERRUTS
#define RT_HW_PIN_ONEWIRE_WRITE_LOW(id)         RT_HW_PIN_ONEWIRE_NOINTERRUTS  RT_HW_PIN_DIR_WRITE_LOW(id)	                       	      RT_HW_PIN_ONEWIRE_INTERRUTS 
#define RT_HW_PIN_ONEWIRE_READ(id)              digitalRead(id.pin)
//-------------------------------------------------------------------------------------------------
#endif
//=================================================================================================
