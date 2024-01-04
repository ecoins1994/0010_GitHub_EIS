#include "RT_HW_BASE.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//									КОНСТРУКТОР
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
RT_HW_BASE:: RT_HW_BASE(){
//=================================================================================================
//							1.Setting up the task sheduler
//=================================================================================================
shed.quick.qnt=5;		//--Number of operational tasks (period 10ms);
shed.fast.qnt=4;		//--Number of fast        tasks (period 25ms);
shed.slow.qnt=4;		//--Number of slow        tasks (period 250ms);
shed.back.qnt=5;   		//--Number of background  tasks (period 100ms);
shed.frdm.qnt=50; 		//--Number of free tasks (period loop() when there are no called tasks);
//=================================================================================================
//							2.Setting general parameters
//=================================================================================================
#if defined(RT_HW_ARCH_CODE) 
device.board.codeArch =(uint8_t)RT_HW_ARCH_CODE;	//--Код архитектуры MCU; 
#endif
#if defined(RT_HW_BOARD_CODE) 
device.board.codeBoard=(uint8_t)RT_HW_BOARD_CODE;	//--Код платы;
#endif
#if defined(RT_HW_BOARD_FCPU) 
device.board.freqCPU  =(uint16_t)RT_HW_BOARD_FCPU;	//--Частота CPU;
#endif
#if defined(RT_HW_BOARD_VCC) 
device.board.vccCPU   =(uint16_t)RT_HW_BOARD_VCC;	//--Vcc CPU;
#endif
#if defined(RT_HW_BOARD_CHECK_PIN)					//--Установка разрешение использования проверки допустимости пинов:
device.board.permitCheckPin=1;						//-> разрешено;
#else
device.board.permitCheckPin=0;						//-> не разрешено
#endif
//=================================================================================================
unixSetSystemTimeDate();			//--Получение параметра времени компиляции
unixGetSTAMP();						//--Получение unixTimе из текущей даты;
unixGetTotal();						//--Получение параметров времени;
//=================================================================================================
genRandom(6752,32);					//--Генератор случайного числа;
genMacAddr();						//--Генерация случайного MAC-адреса(buff.mac[6]);
//=================================================================================================
//							3.Setting up I/O devices
//=================================================================================================
#if defined(RT_HW_BOARD_DEPTH_SYS)
device.depth.sys=(uint8_t)RT_HW_BOARD_DEPTH_SYS;	//--System bit depth;	
#endif
#if defined(RT_HW_BOARD_DEPTH_PWM)       			//--PWM bit depth;
device.depth.pwm=(uint8_t)RT_HW_BOARD_DEPTH_PWM;	
#endif
#if defined(RT_HW_BOARD_DEPTH_DAC)       			//--DAC bit depth;
device.depth.dac=(uint8_t)RT_HW_BOARD_DEPTH_DAC;	
#endif
#if defined(RT_HW_BOARD_DEPTH_TCH)       			//--Touch bit depth;
device.depth.tch=(uint8_t)RT_HW_BOARD_DEPTH_TCH;	
#endif
#if defined(RT_HW_BOARD_DEPTH_ADC)       			//--ADC bit depth;
device.depth.adc=(uint8_t)RT_HW_BOARD_DEPTH_ADC;	
#endif
#if defined(RT_HW_BOARD_DRIFT_ADC)       			//--ADC drift of readings;
device.depth.adcDrift=(uint8_t)RT_HW_BOARD_DRIFT_ADC;	
#endif
#if defined(RT_HW_BOARD_NULL_ADC)       			//--ADC zero drift;
device.depth.adcNull=(uint8_t)RT_HW_BOARD_NULL_ADC;	
#endif
//=================================================================================================
//							4.1.Setting the ADC bit depth
//=================================================================================================
#if defined(RT_HW_ADC_PERMIT_SET_RESOLUTION) 
	analogReadResolution(device.depth.adc); 
#endif 
//=================================================================================================
//							4.2.Setting the PWM bit depth
//=================================================================================================
#if defined(RT_HW_PWM_PERMIT_SET_RESOLUTION)
	analogWriteResolution(device.depth.pwm); 
#endif  
//=================================================================================================
//							4.3 Setting the number of timers (used in ESP32)
//=================================================================================================
 
//=================================================================================================
//							4.4.M5Stack-Core-ESP32:: DAC setting to avoid buzzer sounds when turned on
//=================================================================================================
#if defined(RT_HW_BOARD_M5Stack_Core_ESP32) 
dacWrite(25,0);
#endif 
 //=================================================================================================
//								4.Parameter initialization for Link
//=================================================================================================
uartInitParamAll();		//--Установка и настройка пинов RX,TX по умолчанию;
i2cInitParamAll();		//--Установка и настройка пинов SCL,SDA для всех шин i2cx;
spiInitParamAll();		//--Установка и настройка пинов SCK,MISO,MOSI,SS для всех шин SPIx;
//=================================================================================================
//							4.Setting up Test Pins
//=================================================================================================
device.spi.cs0	  =readArrPGM(RT_HW_PGM_PIN_CSX_ID,0);	
device.spi.cs1    =readArrPGM(RT_HW_PGM_PIN_CSX_ID,1);
device.spi.cs2    =readArrPGM(RT_HW_PGM_PIN_CSX_ID,2);
device.spi.cs3    =readArrPGM(RT_HW_PGM_PIN_CSX_ID,3);
device.spi.cs4    =readArrPGM(RT_HW_PGM_PIN_CSX_ID,4);
device.spi.cs5    =readArrPGM(RT_HW_PGM_PIN_CSX_ID,5);
device.spi.cs6    =readArrPGM(RT_HW_PGM_PIN_CSX_ID,6);
device.spi.busETH =readArrPGM(RT_HW_PGM_PIN_ETH_ID,0);
device.spi.csETH  =readArrPGM(RT_HW_PGM_PIN_ETH_ID,1);
device.spi.intETH =readArrPGM(RT_HW_PGM_PIN_ETH_ID,2);
device.spi.busCAN =readArrPGM(RT_HW_PGM_PIN_CAN_ID,0);
device.spi.csCAN  =readArrPGM(RT_HW_PGM_PIN_CAN_ID,1);
device.spi.intCAN =readArrPGM(RT_HW_PGM_PIN_CAN_ID,2);
//-------------------------------------------------------------------------------------------------
device.pin.control=readArrPGM(RT_HW_PGM_PIN_BRD_ID,0);	
device.pin.led    =readArrPGM(RT_HW_PGM_PIN_BRD_ID,1);
device.pin.button =readArrPGM(RT_HW_PGM_PIN_BRD_ID,2);
device.pin.adc    =readArrPGM(RT_HW_PGM_PIN_BRD_ID,3);	
device.pin.pwm    =readArrPGM(RT_HW_PGM_PIN_BRD_ID,4);
device.pin.debug  =readArrPGM(RT_HW_PGM_PIN_BRD_ID,5);
device.pin.ws2812 =readArrPGM(RT_HW_PGM_PIN_BRD_ID,6);
//-------------------------------------------------------------------------------------------------
device.tft.bus    =readArrPGM(RT_HW_PGM_PIN_TFT_ID,0);	
device.tft.cs     =readArrPGM(RT_HW_PGM_PIN_TFT_ID,1);
device.tft.dc 	  =readArrPGM(RT_HW_PGM_PIN_TFT_ID,2);
device.tft.led    =readArrPGM(RT_HW_PGM_PIN_TFT_ID,3);	
//--------------------------------------------------------------------------------------------------
device.dev.oneWire=readArrPGM(RT_HW_PGM_TST_DEV_ID,0);	
device.dev.dht22  =readArrPGM(RT_HW_PGM_TST_DEV_ID,1);		
device.dev.sr04   =readArrPGM(RT_HW_PGM_TST_DEV_ID,2);
//--------------------------------------------------------------------------------------------------
device.uart.console=readArrPGM(RT_HW_PGM_TST_URT_ID,0);	
device.uart.modbus1=readArrPGM(RT_HW_PGM_TST_URT_ID,1);	
device.uart.modbus2=readArrPGM(RT_HW_PGM_TST_URT_ID,2);			
device.uart.nextion=readArrPGM(RT_HW_PGM_TST_URT_ID,3);	
device.uart.wifi   =readArrPGM(RT_HW_PGM_TST_URT_ID,4);	
device.uart.eth1   =readArrPGM(RT_HW_PGM_TST_URT_ID,5);	
device.uart.eth2   =readArrPGM(RT_HW_PGM_TST_URT_ID,6);
device.uart.device =readArrPGM(RT_HW_PGM_TST_URT_ID,7);	
//-------------------------------------------------------------------------------------------------
//  		3.2.Setting the field length when displaying pins
//-------------------------------------------------------------------------------------------------
mess.lenPin=3;
#if   defined(RT_HW_CORE_STM32)
mess.lenPin=4;
#endif
#if   defined(RT_HW_CORE_ESP8266)
mess.lenPin=3;
#endif	

//=================================================================================================
};	//--End RT_HW_BASE()	

//=================================================================================================
//							 CREATING EXTERNAL OBJECTS
//=================================================================================================
RT_HW_BASE RT_HW_Base;									
//-------------------------------------------------------------------------------------------------	