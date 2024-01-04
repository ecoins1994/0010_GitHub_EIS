//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//						5.Программная среда Seeeduino
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//----------------------0.Идентификация программной среды------------------------------------------
#if !defined(RT_HW_CORE_DEFINED) && defined(RT_HW_CORE_SEEED)
#define RT_HW_CORE_DEFINED          							//--Идентификатор программной среды;
//----------------------1.Основные параметры-------------------------------------------------------
#define RT_HW_ARCH_CODE        		8							//--Код архитектуры;
#define RT_HW_ARCH_NAME        		"SEEED"						//--Наименование архитектуры;
#define RT_HW_CORE_NAME        		"SEEED"	 					//--Наименование программной среды
//----------------------2.Дополнительные макросы---------------------------------------------------
#define RT_HW_IRAM_ATTR											//--Атрибут для совместимости c ESP8266;	
#define RT_HW_ADC_PERMIT_SET_RESOLUTION							//--Разрешение изменения разрешения ADC;
#define RT_HW_PWM_PERMIT_SET_RESOLUTION							//--Разрешение изменения разрешения PWM;
#define RT_HW_PWM_FREQ              1000                        //--Частота для PWM умолчанию;
//----------------------3.Общие библиотеки---------------------------------------------------------
#include <avr/pgmspace.h>										//--Работа с PROGMEM;
//----------------------4.Таймеры------------------------------------------------------------------
//----------------------5.Интерфейсы UART----------------------------------------------------------
#define RT_HW_UART_SPEED		115200					//--Speed UART; 
//----------------------6.Интерфейсы i2c-----------------------------------------------------------
#define RT_HW_I2C_BLOCK_USER_PINS								//--Блокировка изменения пинов i2c;
#define RT_HW_I2C_SPEED          	400000UL					//--Код скорости шины i2c (default 400kHz);
#include <Wire.h>												//--Подключение библиотеки i2c;
//----------------------7.Интерфейсы SPI-----------------------------------------------------------
#define RT_HW_SPI_BLOCK_USER_PINS	1							//--Блокировка изменения пинов SPI;
#define RT_HW_SPI_INTERRUPT_MODE	0							//--Режим работы с прерываниями SPI;
#define RT_HW_SPI_SPEED				4000000UL					//--Скорость SPI в Гц; 
#define RT_HW_SPN_DELAY				1							//--Задержка для RT_HW_PIN_DIR_WRITE_HIGH->??? 0=0ns;1=600ns;2=650ns;3=700ns;4=850ns;5=900ns;
#include <SPI.h>
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
#define RT_HW_DATE_TYPE 		uint32_t						//--Тип базовой переменной при прямом управлении пинами;
struct  RT_HW_PIN_DIR_ID {uint8_t pin=255; uint8_t dir=0; uint8_t bit; char mode='N';}; 
//----------------------23.Встроенные функции управления GPIO--------------------------------------
//----------------------24.Макросы прямого управления пинами---------------------------------------
#define RT_HW_PIN_DIR_SET_ID(id,p) 	    	id.pin=p; 
#define RT_HW_PIN_DIR_MODE_INPUT(id)        pinMode(id.pin,INPUT); 				
#define RT_HW_PIN_DIR_MODE_PULLUP(id) 	    pinMode(id.pin,INPUT_PULLUP);
#define RT_HW_PIN_DIR_MODE_OUTPUT(id) 	    pinMode(id.pin,OUTPUT);
#define RT_HW_PIN_DIR_READ(id)           	digitalRead(id.pin) 
#define RT_HW_PIN_DIR_WRITE(id,val) 		digitalWrite(id.pin,val);
#define RT_HW_PIN_DIR_WRITE_LOW(id)         digitalWrite(id.pin,LOW);
#define RT_HW_PIN_DIR_WRITE_HIGH(id)        digitalWrite(id.pin,HIGH);
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
//=================================================================================================