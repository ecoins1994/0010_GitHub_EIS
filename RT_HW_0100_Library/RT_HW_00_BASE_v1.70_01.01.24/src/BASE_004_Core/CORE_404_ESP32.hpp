//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//						Программная среда ESP32
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//----------------------0.Идентификация программной среды------------------------------------------
#if !defined(RT_HW_CORE_DEFINED) && defined(RT_HW_CORE_ESP32) 
#define RT_HW_CORE_DEFINED          3							//--Идентификатор программной среды;
//----------------------1.Основные параметры-----------------------------------------------------
#define	RT_HW_ARCH_CODE        		3							//--Код архитектуры;
#define RT_HW_ARCH_NAME        		"ESP32"						//--Наименование архитектуры;
#define RT_HW_CORE_NAME        		"ESP32"	 					//--Наименование программной среды
#define RT_HW_BOARD_DEPTH_SYS  	12								//--Системная разрядность;
#define RT_HW_BOARD_DEPTH_PWM  	16								//--PWM разрядность;
#define RT_HW_BOARD_DEPTH_ADC  	12								//--ADC разрядность;
#define RT_HW_BOARD_DRIFT_ADC  	30								//--ADC дрейф показаний;
#define RT_HW_BOARD_NULL_ADC  	40								//--ADC дрейф нуля;
//----------------------2.Дополнительные макросы-------------------------------------------------
#define RT_HW_IRAM_ATTR											//--Атрибут для совместимости c ESP8266;	
#define RT_HW_PWM_PERMIT_SET_RESOLUTION							//--Разрешение изменения разрешения PWM;
#define RT_HW_PWM_FREQ              1000                   	 	//--Частота для PWM умолчанию;
//----------------------3.Общие библиотеки-------------------------------------------------------
#include <pgmspace.h>											//--Работа с PROGMEM;
#include "esp32-hal-ledc.h"										//--Библиотека для работы с PWM и LED;	
#include <driver/rtc_io.h>										//--Служебные функции;
#if defined(RT_HW_CORE_ESP32S)
#include "BluetoothSerial.h"									//--Библиотека BlueTooth;
#endif
//----------------------4.Таймеры----------------------------------------------------------------
//----------------------4.1 Для ESP32С3,ESP32S2--------------------------------------------------
#if defined(RT_HW_CORE_ESP32C3) || defined(RT_HW_CORE_ESP32S2)
  #define RT_HW_USE_TIMER_NO        
  #define RT_HW_MAX_NUM_CHANNEL      6							//--Максимальное кол-во каналов LEDC
#endif
//----------------------4.2 Для ESP32S,ESP32S3---------------------------------------------------
#if defined(RT_HW_CORE_ESP32S) || defined(RT_HW_CORE_ESP32S3) || defined(RT_HW_CORE_ESP32PICO) 
  #define RT_HW_USE_TIMER_NO        
  #define RT_HW_MAX_NUM_CHANNEL      16							//--Максимальное кол-во каналов LEDC
#endif
//----------------------4.2 Для неопознанных типов ESP32-----------------------------------------
#if !defined(RT_HW_USE_TIMER_NO)
  #define RT_HW_USE_TIMER_NO        
  #define RT_HW_MAX_NUM_CHANNEL      6							//--Максимальное кол-во каналов LEDC
#endif
//----------------------5.Bus UART-----------------------------------------------------------------
#define RT_HW_UART_SPEED		115200					//--Speed UART; 
//----------------------6.Bus i2c------------------------------------------------------------------
#include <Wire.h>												//--Подключение библиотеки i2c;	
#define RT_HW_I2C_BLOCK_I2C_SLAVE								//--Блокировка функций поддержки i2c Slave;
#define RT_HW_I2C_SPEED          	400000UL					//--Код скорости шины i2c (default 400kHz);
//----------------------7.Bus SPI------------------------------------------------------------------
#include <SPI.h>												//--Подключение библиотеки SPI	
#define RT_HW_SPI_INTERRUPT_MODE	0							//--Режим работы с прерываниями SPI;
#define RT_HW_SPI_SPEED				4000000UL					//--Скорость SPI в Гц стандартная; 
#define RT_HW_SPN_DELAY				1							//--Задержка для RT_HW_PIN_DIR_WRITE_HIGH->;
//----------------------8.Интерфейс CAN------------------------------------------------------------
//----------------------9.Интерфейс Wi-Fi----------------------------------------------------------
//----------------------20.Макросы для работы c пинами через функции WIRING------------------------ 
#define RT_HW_PIN_MODE_INPUT  				 INPUT				//--Дискретный вход;
#define RT_HW_PIN_MODE_OUTPUT  				 OUTPUT				//--Дискретный выход;
#define RT_HW_PIN_MODE_INPUT_PULLUP  		 INPUT_PULLUP 		//--Дискретный вход с подтяжкой к +Vcc;
//----------------------21.Макросы для совместимости с STM32---------------------------------------
#define RT_HW_PIN_MODE_INPUT_FLOATING  		 INPUT				//--Дискретный вход - аналог INPUT;
#define RT_HW_PIN_MODE_INPUT_PULLDOWN  		 INPUT_PULLDOWN		//--Дискретный вход с подтяжкой к GND;
#define RT_HW_PIN_MODE_INPUT_ANALOG  		 INPUT				//--Аналоговый вход;
#define RT_HW_PIN_MODE_OUTPUT_OPEN_DRAIN  	 OUTPUT_OPEN_DRAIN	//--Дискретный выход с открытым выходом;
#define RT_HW_PIN_MODE_OUTPUT_PWM			 OUTPUT				//--ШИМ выход;
#define RT_HW_PIN_MODE_OUTPUT_PWM_OPEN_DRAIN OUTPUT				//--ШИМ выход с открытым коллектором;
//----------------------22.Базовый размер переменной и структура для GPIO---------------------------
// depthPWM - разрешение PWM. Если =255, в функциях PWM используется значение по умолчанию, иначе используется depthPWM;
#define RT_HW_DATE_TYPE 		uint32_t						
struct  RT_HW_PIN_DIR_ID {uint8_t pin=255; uint8_t dir=0; uint8_t bit; char mode='N';};
//----------------------23.Встроенные функции управления GPIO---------------------------------------
//- - - - - - - - - - - RT_HW_directRead() - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
static inline __attribute__((always_inline))
uint32_t RT_HW_directRead(uint32_t pin){
#if defined(RT_HW_CORE_ESP32C3)	
		     return ((GPIO.in.val  >>  pin)       & 0x1);
#else  //----ESP32S,ESP32S2,ESP32S3,ESP32PICO 
if (pin<32) {return ((GPIO.in      >>  pin)       & 0x1);}
if (pin<46) {return ((GPIO.in1.val >> (pin - 32)) & 0x1);}
#endif
return 0;}
//- - - - - - - - - - - RT_HW_directWriteLow() - - - - - - - - - - - - - - - - - - - - - - - - - -  
static inline __attribute__((always_inline))
void     RT_HW_directWriteLow(uint32_t pin){
#if defined(RT_HW_CORE_ESP32C3)	
                         GPIO.out_w1tc.val  = ((uint32_t)1 << pin);
#else  //----ESP32S,ESP32S2,ESP32S3 ,ESP32PICO 
if (pin<32) {GPIO.out_w1tc      = ((uint32_t)1 <<  pin);}
if (pin<46) {GPIO.out1_w1tc.val = ((uint32_t)1 << (pin - 32));}
#endif
}
//- - - - - - - - - - - RT_HW_directWritehIGH() - - - - - - - - - - - - - - - - - - - - - - - - - - 
static inline __attribute__((always_inline))
void 	RT_HW_directWriteHigh(uint32_t pin){
#if defined(RT_HW_CORE_ESP32C3)	
                         GPIO.out_w1ts.val  = ((uint32_t)1 << pin);
#else  //----ESP32S,ESP32S2,ESP32S3 ,ESP32PICO
if (pin<32) {GPIO.out_w1ts      = ((uint32_t)1 <<  pin);}
if (pin<46) {GPIO.out1_w1ts.val = ((uint32_t)1 << (pin - 32));}
#endif
}
//- - - - - - - - - - - RT_HW_directModeInput() - - - - - - - - - - - - - - - - - - - - - - - - - - 
static inline __attribute__((always_inline))
void 	RT_HW_directModeInput(uint32_t pin){
#if   defined(RT_HW_CORE_ESP32C3)	
    GPIO.enable_w1tc.val = ((uint32_t)1 << (pin));
#elif defined(RT_HW_CORE_ESP32PICO)
if (digitalPinIsValid(pin)){
    uint32_t rtc_reg(rtc_io_desc[pin].reg);
    if ( rtc_reg ){ESP_REG(rtc_reg) = ESP_REG(rtc_reg) & ~(rtc_io_desc[pin].mux);
				   ESP_REG(rtc_reg) = ESP_REG(rtc_reg) & ~(rtc_io_desc[pin].pullup | rtc_io_desc[pin].pulldown);}
    if (pin<32)   {GPIO.enable_w1tc      = ((uint32_t)1 <<  pin);}
    else          {GPIO.enable1_w1tc.val = ((uint32_t)1 << (pin - 32));}}
#else  //----ESP32S,ESP32S2,ESP32S3
if (digitalPinIsValid(pin)){
    if (pin<32)   {GPIO.enable_w1tc      = ((uint32_t)1 <<  pin);}
    else          {GPIO.enable1_w1tc.val = ((uint32_t)1 << (pin - 32));}}
#endif
}
//- - - - - - - - - - - RT_HW_directModeOutput() - - - - - - - - - - - - - - - - - - - - - - - - - 
static inline __attribute__((always_inline))
void 	RT_HW_directModeOutput(uint32_t pin){
#if   defined(RT_HW_CORE_ESP32C3)
    pinMode(pin,OUTPUT);								
   //GPIO.enable_w1ts.val = ((uint32_t)1 << (pin));
#elif defined(RT_HW_CORE_ESP32PICO)
if (digitalPinIsValid(pin) && pin <= 33 ){ //--пины >33 могут быть использованы только как входные;
    uint32_t rtc_reg(rtc_io_desc[pin].reg);
    if ( rtc_reg ){ESP_REG(rtc_reg) = ESP_REG(rtc_reg) & ~(rtc_io_desc[pin].mux);
				   ESP_REG(rtc_reg) = ESP_REG(rtc_reg) & ~(rtc_io_desc[pin].pullup | rtc_io_desc[pin].pulldown);}
    if (pin<32)   {GPIO.enable_w1ts      = ((uint32_t)1 <<  pin);}
    else          {GPIO.enable1_w1ts.val = ((uint32_t)1 << (pin - 32));}}
#else  //----ESP32S,ESP32S2,ESP32S3 
if (digitalPinIsValid(pin) && pin <= 33 ){ //--пины >33 могут быть использованы только как входные;
    if (pin<32)   {GPIO.enable_w1ts      = ((uint32_t)1 <<  pin);}
    else          {GPIO.enable1_w1ts.val = ((uint32_t)1 << (pin - 32));}}
#endif
}
//----------------------24.Макросы прямого управления пинами---------------------------------------
#define RT_HW_PIN_DIR_SET_ID(id,p) 	        id.pin=p;
#define RT_HW_PIN_DIR_MODE_INPUT(id)        RT_HW_directModeInput(id.pin);
#define RT_HW_PIN_DIR_MODE_PULLUP(id) 	    pinMode(id.pin,INPUT_PULLUP);
#define RT_HW_PIN_DIR_MODE_OUTPUT(id) 	    RT_HW_directModeOutput(id.pin); 	//--pinMode(id.pin,OUTPUT);
#define RT_HW_PIN_DIR_READ(id)              RT_HW_directRead(id.pin) 			//--digitalRead(id.pin)
#define RT_HW_PIN_DIR_WRITE(id,val) 		if(val){RT_HW_directWriteHigh(id.pin);} else{RT_HW_directWriteLow(id.pin);} //digitalWrite(id.pin,val);
#define RT_HW_PIN_DIR_WRITE_LOW(id)         RT_HW_directWriteLow(id.pin);		//--digitalWrite(id.pin,LOW);
#define RT_HW_PIN_DIR_WRITE_HIGH(id)        RT_HW_directWriteHigh(id.pin);		//--digitalWrite(id.pin,HIGH);
//----------------------25.Макросы для 1-Wire------------------------------------------------------
struct  RT_HW_PIN_ONEWIRE_ID {uint32_t pin;};  //--dir используется в функциях настройки пинов;
#define RT_HW_PIN_ONEWIRE_SET_ID(id,p) 	    	RT_HW_PIN_DIR_SET_ID(id,p)
#define RT_HW_PIN_ONEWIRE_NOINTERRUTS           noInterrupts(); 
#define RT_HW_PIN_ONEWIRE_INTERRUTS             interrupts();
#define RT_HW_PIN_ONEWIRE_MODE_INPUT(id)        RT_HW_PIN_ONEWIRE_NOINTERRUTS                               RT_HW_PIN_DIR_MODE_INPUT(id)  RT_HW_PIN_ONEWIRE_INTERRUTS
#define RT_HW_PIN_ONEWIRE_MODE_INPUT_LOW(id)    RT_HW_PIN_ONEWIRE_NOINTERRUTS  RT_HW_PIN_DIR_MODE_INPUT(id) RT_HW_PIN_DIR_WRITE_LOW(id)   RT_HW_PIN_ONEWIRE_INTERRUTS
#define RT_HW_PIN_ONEWIRE_MODE_OUTPUT_LOW(id)   RT_HW_PIN_ONEWIRE_NOINTERRUTS  RT_HW_PIN_DIR_WRITE_LOW(id)  RT_HW_PIN_DIR_MODE_OUTPUT(id) RT_HW_PIN_ONEWIRE_INTERRUTS
#define RT_HW_PIN_ONEWIRE_WRITE_HIGH(id)        RT_HW_PIN_ONEWIRE_NOINTERRUTS  RT_HW_PIN_DIR_WRITE_HIGH(id)                               RT_HW_PIN_ONEWIRE_INTERRUTS
#define RT_HW_PIN_ONEWIRE_WRITE_LOW(id)         RT_HW_PIN_ONEWIRE_NOINTERRUTS  RT_HW_PIN_DIR_WRITE_LOW(id)	                       	      RT_HW_PIN_ONEWIRE_INTERRUTS 
#define RT_HW_PIN_ONEWIRE_READ(id)                           	               RT_HW_PIN_DIR_READ(id)
//-------------------------------------------------------------------------------------------------
#endif
//=================================================================================================
