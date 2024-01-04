//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//						5.Software environment Raspberry Pi Pico (RP2040)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//----------------------0.Software environment identification--------------------------------------
#if !defined(RT_HW_CORE_DEFINED) && defined(RT_HW_CORE_RP2040)
#define RT_HW_CORE_DEFINED           					//--Software environment identifier;
//----------------------1.Main settings------------------------------------------------------------
#define RT_HW_ARCH_CODE        		40					//--Architecture code;
#define RT_HW_ARCH_NAME  "Raspberry Pi Pico" 			//--Architecture name;
#define RT_HW_CORE_NAME  "Raspberry Pi Pico"			//--Software environment name;
#define RT_HW_PERMIT_CORE1								//--Permit CORE1
//-------------------------------------------------------------------------------------------------
#define RT_HW_IRAM_ATTR									//--Attribute for compatibility with ESP8266;
//----------------------2.Options for analog pin parameters----------------------------------------
#define RT_HW_ADC_PERMIT_SET_RESOLUTION					//--ADC permission change permission;
#define RT_HW_PWM_PERMIT_SET_RESOLUTION					//--PWM permission change permission;
#define RT_HW_BOARD_DEPTH_SYS  		12					//--System bit depth;
#define RT_HW_BOARD_DEPTH_PWM  		12					//--PWM bit depth;
#define RT_HW_FREQ_PWM              1000         		//--PWM frequency default;
#define RT_HW_BOARD_DEPTH_ADC  		12					//--ADC bit depth;
#define RT_HW_BOARD_DRIFT_ADC  		16					//--ADC drift of indications;
#define RT_HW_BOARD_NULL_ADC  		8					//--ADC drift of null;
//----------------------3.Shared Libraries---------------------------------------------------------
#include <avr/pgmspace.h>								//--For PROGMEM;
#include "pico/stdlib.h"								//--SDK
//----------------------4.Options for timers-------------------------------------------------------
//----------------------5.Options for UART---------------------------------------------------------
#define RT_HW_UART_SPEED		115200					//--Speed UART; 
//----------------------6.Options for i2c----------------------------------------------------------
#include <Wire.h>										//--include  library  i2c;
#define RT_HW_I2C_SPEED          	400000UL			//--Speed default for i2c;
//----------------------7.Options for SPI----------------------------------------------------------
#include <SPI.h>										//--include  library  SPI;
#define RT_HW_SPI_SPEED				4000000UL			//--Speed default for SPI; 
#define RT_HW_SPN_DELAY				1					//--Delay(ns) for direct pins:: 0=0;1=600;2=650;3=700;4=850;5=900;
//----------------------8.Options for CAN----------------------------------------------------------
//----------------------9.Options for Wi-Fi--------------------------------------------------------
//----------------------20.Макросы для работы c пинами через функции WIRING------------------------ 
#define RT_HW_PIN_MODE_INPUT  				 INPUT				//--Дискретный вход;
#define RT_HW_PIN_MODE_OUTPUT  				 OUTPUT				//--Дискретный выход;
#define RT_HW_PIN_MODE_INPUT_PULLUP  		 INPUT_PULLUP 		//--Дискретный вход с подтяжкой к +Vcc;
//----------------------21.Макросы для совместимости с STM32---------------------------------------
#define RT_HW_PIN_MODE_INPUT_FLOATING  		 INPUT				//--Дискретный вход - аналог INPUT;
#define RT_HW_PIN_MODE_INPUT_PULLDOWN  		 INPUT_PULLDOWN		//--Дискретный вход с подтяжкой к GND;
#define RT_HW_PIN_MODE_INPUT_ANALOG  		 INPUT				//--Аналоговый вход;
#define RT_HW_PIN_MODE_OUTPUT_OPEN_DRAIN  	 OUTPUT				//--Дискретный выход с открытым выходом;
#define RT_HW_PIN_MODE_OUTPUT_PWM			 OUTPUT				//--ШИМ выход;
#define RT_HW_PIN_MODE_OUTPUT_PWM_OPEN_DRAIN OUTPUT				//--ШИМ выход с открытым коллектором;
//----------------------22.Basic variable size and structure for GPIO------------------------------
#define RT_HW_DATE_TYPE 		    uint32_t			//--The type of the base variable for direct pin control;
struct  RT_HW_PIN_DIR_ID {uint8_t pin=255; uint8_t dir=0; uint8_t bit; char mode='N';};
//----------------------11.Built-in control functions GPIO-----------------------------------------
//----------------------23.Macros for direct control of pins---------------------------------------
#define RT_HW_PIN_DIR_SET_ID(id,p) 	    		id.pin=p; 
#define RT_HW_PIN_DIR_MODE_INPUT(id)        	pinMode(id.pin,INPUT); 				
#define RT_HW_PIN_DIR_MODE_PULLUP(id) 	    	pinMode(id.pin,INPUT_PULLUP);
#define RT_HW_PIN_DIR_MODE_OUTPUT(id) 	    	pinMode(id.pin,OUTPUT);
#define RT_HW_PIN_DIR_READ(id)           		digitalRead(id.pin) 
#define RT_HW_PIN_DIR_WRITE(id,val) 			digitalWrite(id.pin,val);
#define RT_HW_PIN_DIR_WRITE_LOW(id)        	    digitalWrite(id.pin,0);
#define RT_HW_PIN_DIR_WRITE_HIGH(id)            digitalWrite(id.pin,1);
//----------------------25.Макросы для 1-Wire------------------------------------------------------
struct  RT_HW_PIN_ONEWIRE_ID {uint32_t pin;};  
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