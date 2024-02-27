//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//						Программная среда STM32duino
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//----------------------0.Идентификация программной среды------------------------------------------
#if !defined(RT_HW_CORE_DEFINED) && defined(RT_HW_CORE_STM32)
    #define  RT_HW_CORE_DEFINED          						//--Идентификатор программной среды;
//----------------------1.Основные параметры-------------------------------------------------------
#define RT_HW_ARCH_CODE        	6								//--Код архитектуры;
#define RT_HW_ARCH_NAME        	"STM32"							//--Наименование архитектуры;
#define RT_HW_CORE_NAME        	"STM32"	 						//--Наименование программной среды
#define RT_HW_BOARD_DEPTH_SYS  	12								//--Системная разрядность;
#define RT_HW_BOARD_DEPTH_PWM  	12								//--PWM разрядность;
#define RT_HW_BOARD_DEPTH_DAC  	12								//--PWM разрядность;
#define RT_HW_BOARD_DEPTH_ADC  	12								//--ADC разрядность;
#define RT_HW_BOARD_DRIFT_ADC  	20								//--ADC дрейф показаний;
#define RT_HW_BOARD_NULL_ADC  	15								//--ADC дрейф нуля;
//----------------------2.Дополнительные макросы---------------------------------------------------
#define RT_HW_IRAM_ATTR											//--Атрибут для совместимости c ESP8266;
#define RT_HW_ADC_PERMIT_SET_RESOLUTION							//--Разрешение изменения разрешения ADC;
#define RT_HW_PWM_PERMIT_SET_RESOLUTION							//--Разрешение изменения разрешения PWM;
#define RT_HW_PWM_FREQ             1000                         //--Частота для PWM умолчанию;
//----------------------3.Общие библиотеки---------------------------------------------------------
#include <avr/pgmspace.h>										//--Работа с PROGMEM;
//----------------------4.Таймеры------------------------------------------------------------------
//----------------------5.Интерфейсы UART----------------------------------------------------------
#define RT_HW_UART_SPEED		115200					//--Speed UART; 
#include "usbd_cdc_if.h"										//--Для работы с USB_CDC в среде STM32duino
//----------------------6.Интерфейсы i2c-----------------------------------------------------------
#include <Wire.h>												//--Подключение библиотеки i2c;
#define RT_HW_I2C_SPEED         	400000UL					//--Код скорости шины i2c (default 400kHz);
//----------------------7.Интерфейсы SPI-----------------------------------------------------------
#include <SPI.h>												//--Подключение библиотеки SPI	
#define RT_HW_SPI_SPEED				4000000UL					//--Скорость SPI в Гц; 
#define RT_HW_SPI_BIT_ORDER         MSBFIRST					//--Порядок следования битов в байте SPI;
#define RT_HW_SPI_DATA_MODE         SPI_MODE0					//--Режим для импульсов SPI;
#define RT_HW_SPI_INTERRUPT_MODE	0							//--Режим работы с прерываниями SPI;
#define RT_HW_SPI_BLOCK_USER_PINS	1							//--Блокировка изменения пинов SPI;
#define RT_HW_SPN_DELAY				1							//--Задержка для RT_HW_PIN_DIR_WRITE_HIGH->
//----------------------8.Интерфейс CAN------------------------------------------------------------
//----------------------9.Интерфейс Wi-Fi----------------------------------------------------------
//----------------------20.Макросы для работы c пинами через функции WIRING------------------------
#define RT_HW_PIN_MODE_INPUT  				INPUT				//--Дискретный вход;
#define RT_HW_PIN_MODE_OUTPUT  				OUTPUT				//--Дискретный выход;
#define RT_HW_PIN_MODE_INPUT_PULLUP  		INPUT_PULLUP 		//--Дискретный вход с подтяжкой к +Vcc;
//----------------------21.Макросы для совместимости с STM32---------------------------------------
#define RT_HW_PIN_MODE_INPUT_FLOATING  		INPUT				//--Дискретный вход - аналог INPUT;
#define RT_HW_PIN_MODE_INPUT_PULLDOWN  		INPUT_PULLDOWN		//--Дискретный вход с подтяжкой к GND;
#define RT_HW_PIN_MODE_INPUT_ANALOG  		INPUT_ANALOG		//--Аналоговый вход;
#define RT_HW_PIN_MODE_OUTPUT_OPEN_DRAIN  	OUTPUT_OPEN_DRAIN	//--Дискретный выход с открытым выходом;
#define RT_HW_PIN_MODE_OUTPUT_PWM			OUTPUT				//--ШИМ выход;
#define RT_HW_PIN_MODE_OUTPUT_PWM_OPEN_DRAIN OUTPUT_OPEN_DRAIN	//--ШИМ выход с открытым коллектором;	
//----------------------22.Базовый размер переменной и структура для GPIO---------------------------
#define RT_HW_DATE_TYPE 		uint32_t 						//--Тип базовой переменной при прямом управлении пинами;
struct  RT_HW_PIN_DIR_ID {uint8_t pin=255; uint8_t dir=0; uint8_t bit; char mode='N';}; //--Структура для прямого управления пинами
//----------------------23.Встроенные функции управления GPIO--------------------------------------
//----------------------24.Макросы прямого управления пинами---------------------------------------
#define RT_HW_PIN_DIR_SET_ID(id,p)	  id.pin=p;  
#define RT_HW_PIN_DIR_MODE_INPUT(id)  pinMode(id.pin,INPUT);		//pin_function((PinName)id.pin, STM_PIN_DATA(STM_MODE_INPUT,     GPIO_NOPULL,0))
#define RT_HW_PIN_DIR_MODE_PULLUP(id) pinMode(id.pin,INPUT_PULLUP);	//pin_function((PinName)id.pin, STM_PIN_DATA(STM_MODE_INPUT,     GPIO_NOPULL,0))
#define RT_HW_PIN_DIR_MODE_OUTPUT(id) pinMode(id.pin,OUTPUT);		//pin_function((PinName)id.pin, STM_PIN_DATA(STM_MODE_OUTPUT_PP, GPIO_NOPULL,0))
#define RT_HW_PIN_DIR_READ(id)        digitalRead(id.pin)			//digitalReadFast((PinName)id.pin);  //digitalRead(id.pin);
#define RT_HW_PIN_DIR_WRITE(id,val)   digitalWrite(id.pin,val);		//if(val){digitalWriteFast((PinName)id.pin,HIGH);} else {digitalWriteFast((PinName)id.pin,LOW);} 
#define RT_HW_PIN_DIR_WRITE_LOW(id)   digitalWrite(id.pin,LOW);		//digitalWriteFast((PinName)id.pin, LOW); 	//digitalWrite(id.pin,0);
#define RT_HW_PIN_DIR_WRITE_HIGH(id)  digitalWrite(id.pin,HIGH);		//digitalWriteFast((PinName)id.pin, HIGH);	//digitalWrite(id.pin,1);
//----------------------25.Макросы для 1-Wire------------------------------------------------------
struct  RT_HW_PIN_ONEWIRE_ID {uint32_t pin;};  //--dir используется в функциях настройки пинов;
#define RT_HW_PIN_ONEWIRE_SET_ID(id,p) 	    	RT_HW_PIN_DIR_SET_ID(id,p)
#define RT_HW_PIN_ONEWIRE_NOINTERRUTS           //noInterrupts(); 
#define RT_HW_PIN_ONEWIRE_INTERRUTS             //interrupts();
#define RT_HW_PIN_ONEWIRE_MODE_INPUT(id)        RT_HW_PIN_ONEWIRE_NOINTERRUTS                               RT_HW_PIN_DIR_MODE_INPUT(id)  RT_HW_PIN_ONEWIRE_INTERRUTS
#define RT_HW_PIN_ONEWIRE_MODE_INPUT_LOW(id)    RT_HW_PIN_ONEWIRE_NOINTERRUTS  RT_HW_PIN_DIR_MODE_INPUT(id) RT_HW_PIN_DIR_WRITE_LOW(id)   RT_HW_PIN_ONEWIRE_INTERRUTS
#define RT_HW_PIN_ONEWIRE_MODE_OUTPUT_LOW(id)   RT_HW_PIN_ONEWIRE_NOINTERRUTS  RT_HW_PIN_DIR_WRITE_LOW(id)  RT_HW_PIN_DIR_MODE_OUTPUT(id) RT_HW_PIN_ONEWIRE_INTERRUTS
#define RT_HW_PIN_ONEWIRE_WRITE_HIGH(id)        RT_HW_PIN_ONEWIRE_NOINTERRUTS  RT_HW_PIN_DIR_WRITE_HIGH(id)                               RT_HW_PIN_ONEWIRE_INTERRUTS
#define RT_HW_PIN_ONEWIRE_WRITE_LOW(id)         RT_HW_PIN_ONEWIRE_NOINTERRUTS  RT_HW_PIN_DIR_WRITE_LOW(id)	                       	      RT_HW_PIN_ONEWIRE_INTERRUTS 
#define RT_HW_PIN_ONEWIRE_READ(id)                           	               RT_HW_PIN_DIR_READ(id)
//-------------------------------------------------------------------------------------------------
#endif
