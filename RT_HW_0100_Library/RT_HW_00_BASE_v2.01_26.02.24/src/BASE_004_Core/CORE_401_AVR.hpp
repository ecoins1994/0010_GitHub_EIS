//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//						Программная среда AVR
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//----------------------0.Идентификация программной среды------------------------------------------ 
#if !defined(RT_HW_CORE_DEFINED) && defined(RT_HW_CORE_AVR)
  #define RT_HW_CORE_DEFINED     		1		//--Идентификатор программной среды;
//=================================================================================================
//						1.Идентификационные параметры
//================================================================================================= 
  #define RT_HW_ARCH_CODE        	1			//--Код архитектуры;
  #define RT_HW_ARCH_NAME        	"AVR"		//--Наименование архитектуры;
  #define RT_HW_CORE_NAME        	"AVR"	 	//--Наименование программной среды;
//=================================================================================================
//						2.Основные параметры
//=================================================================================================
  #define RT_HW_BOARD_DEPTH_SYS  	12			//--Системная разрядность;
  #define RT_HW_BOARD_DEPTH_PWM  	8			//--PWM разрядность;
  #define RT_HW_BOARD_DEPTH_ADC  	10			//--ADC разрядность;
  #define RT_HW_BOARD_DRIFT_ADC  	3			//--ADC дрейф показаний;
  #define RT_HW_BOARD_NULL_ADC  	4			//--ADC дрейф нуля;
//=================================================================================================
//						3.Дополнительные макросы
//=================================================================================================
  #define RT_HW_IRAM_ATTR						//--Атрибут для совместимости c ESP8266;	
  #define RT_HW_PWM_FREQ            500         //--Частота для PWM умолчанию;
//=================================================================================================
//						4.Таймеры
//=================================================================================================
// Для последующего развития
//=================================================================================================
//						5.UART
//=================================================================================================
  #define RT_HW_UART_SPEED		115200			//--Скорость UART; 
  #define RT_HW_SERIAL							//--Доступен объект Serial;
  #if defined(HAVE_HWSERIAL1)
    #define RT_HW_SERIAL1											//--Доступен объект Serial1;
  #endif
  #if defined(HAVE_HWSERIAL2)
    #define RT_HW_SERIAL2											//--Доступен объект Serial2;
  #endif
  #if defined(HAVE_HWSERIAL3)
    #define RT_HW_SERIAL3											//--Доступен объект Serial3;
  #endif
  #if defined(HAVE_HWSERIAL4)
    #define RT_HW_SERIAL4											//--Доступен объект Serial4;
  #endif
//=================================================================================================
//						6.i2c
//=================================================================================================  
  #define RT_HW_I2C_BLOCK_USER_PINS								//--Блокировка изменения пинов;
  #define RT_HW_I2C_SPEED  	        400000UL					//--Код скорости i2c=400kHz;
//=================================================================================================
//						7.SPI
//================================================================================================= 
  #define RT_HW_SPI_BLOCK_USER_PINS								//--Блокировка изменения пинов;
  #define RT_HW_SPI_INTERRUPT_MODE	0							//--Режим работы с прерываниями SPI;
  #define RT_HW_SPI_SPEED				4000000UL				//--Скорость SPI в кГц; 
  #define RT_HW_SPN_DELAY				0						//--Задержка для RT_HW_PIN_DIR_WRITE_HIGH->0=0ns;1=600ns;2=650ns;3=700ns;4=850ns;5=900ns;
//----------------------8.Интерфейс CAN------------------------------------------------------------																
//----------------------9.Интерфейс Wi-Fi----------------------------------------------------------



//----------------------20.Макросы для работы c пинами через функции WIRING------------------------  
  #define RT_HW_PIN_MODE_INPUT  				INPUT			//--Дискретный вход;
  #define RT_HW_PIN_MODE_OUTPUT  				OUTPUT			//--Дискретный выход;
  #define RT_HW_PIN_MODE_INPUT_PULLUP  			INPUT_PULLUP 	//--Дискретный вход с подтяжкой к +Vcc;
//----------------------21.Макросы для совместимости с STM32---------------------------------------
  #define RT_HW_PIN_MODE_INPUT_FLOATING  		INPUT			//--Дискретный вход - аналог INPUT;
  #define RT_HW_PIN_MODE_INPUT_PULLDOWN  		INPUT			//--Дискретный вход с подтяжкой к GND;
  #define RT_HW_PIN_MODE_INPUT_ANALOG  			INPUT			//--Аналоговый вход;
  #define RT_HW_PIN_MODE_OUTPUT_OPEN_DRAIN  	OUTPUT			//--Дискретный выход с открытым выходом;
  #define RT_HW_PIN_MODE_OUTPUT_PWM				OUTPUT			//--ШИМ выход;
  #define RT_HW_PIN_MODE_OUTPUT_PWM_OPEN_DRAIN	OUTPUT			//--ШИМ выход с открытым коллектором;
//----------------------22.Базовый размер переменной и структура для GPIO--------------------------
  #define RT_HW_DATE_TYPE 		uint8_t						
  struct  RT_HW_PIN_DIR_ID {uint8_t pin=255; uint8_t dir=0; uint8_t bit; char mode='N'; volatile uint8_t *base;};	
//----------------------23.Макросы прямого управления пинами---------------------------------------
  #define RT_HW_PIN_DIR_SET_ID(id,p) 	    	id.pin=p; id.bit=digitalPinToBitMask(p); id.base=portInputRegister(digitalPinToPort(p));
  #define RT_HW_PIN_DIR_MODE_INPUT(id)        *((id.base)+(1)) &=~id.bit; *((id.base)+(2))&=~id.bit; 
  #define RT_HW_PIN_DIR_MODE_PULLUP(id) 	  *((id.base)+(1)) &=~id.bit; *((id.base)+(2))|= id.bit;
  #define RT_HW_PIN_DIR_MODE_OUTPUT(id) 	  *((id.base)+(1)) |= id.bit;
  #define RT_HW_PIN_DIR_READ(id)           (((*((id.base)+(0))) & id.bit) ? (1) : (0)) 
  #define RT_HW_PIN_DIR_WRITE(id,val) if(val){*((id.base)+(2)) |= id.bit;}\
                                         else{*((id.base)+(2)) &=~id.bit;};
  #define RT_HW_PIN_DIR_WRITE_LOW(id)         *((id.base)+(2)) &=~id.bit;
  #define RT_HW_PIN_DIR_WRITE_HIGH(id)        *((id.base)+(2)) |= id.bit;
//----------------------24.Встроенные функции управления GPIO--------------------------------------
//----------------------25.Макросы для 1-Wire------------------------------------------------------
  struct  RT_HW_PIN_ONEWIRE_ID {uint8_t pin; uint8_t bit; volatile uint8_t *base;}; //--dir используется в функциях настройки пинов;
  #define RT_HW_PIN_ONEWIRE_SET_ID(id,p) 	    RT_HW_PIN_DIR_SET_ID(id,p);
  #define RT_HW_PIN_ONEWIRE_NOINTERRUTS           //noInterrupts(); 
  #define RT_HW_PIN_ONEWIRE_INTERRUTS             //interrupts();
  #define RT_HW_PIN_ONEWIRE_MODE_INPUT(id)      RT_HW_PIN_ONEWIRE_NOINTERRUTS                              RT_HW_PIN_DIR_MODE_INPUT(id)  RT_HW_PIN_ONEWIRE_INTERRUTS
  #define RT_HW_PIN_ONEWIRE_MODE_INPUT_LOW(id) 	RT_HW_PIN_ONEWIRE_NOINTERRUTS RT_HW_PIN_DIR_MODE_INPUT(id) RT_HW_PIN_DIR_WRITE_LOW(id)   RT_HW_PIN_ONEWIRE_INTERRUTS
  #define RT_HW_PIN_ONEWIRE_MODE_OUTPUT_LOW(id)	RT_HW_PIN_ONEWIRE_NOINTERRUTS RT_HW_PIN_DIR_WRITE_LOW(id)  RT_HW_PIN_DIR_MODE_OUTPUT(id) RT_HW_PIN_ONEWIRE_INTERRUTS
  #define RT_HW_PIN_ONEWIRE_WRITE_HIGH(id)     	RT_HW_PIN_ONEWIRE_NOINTERRUTS RT_HW_PIN_DIR_WRITE_HIGH(id)                               RT_HW_PIN_ONEWIRE_INTERRUTS
  #define RT_HW_PIN_ONEWIRE_WRITE_LOW(id)       RT_HW_PIN_ONEWIRE_NOINTERRUTS RT_HW_PIN_DIR_WRITE_LOW(id)	                       	     RT_HW_PIN_ONEWIRE_INTERRUTS 
  #define RT_HW_PIN_ONEWIRE_READ(id)                           	              RT_HW_PIN_DIR_READ(id)
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
#endif			
//=================================================================================================
