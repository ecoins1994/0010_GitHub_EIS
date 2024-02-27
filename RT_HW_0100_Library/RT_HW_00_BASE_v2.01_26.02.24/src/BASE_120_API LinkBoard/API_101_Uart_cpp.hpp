#include "RT_HW_BASE.h"	 
//#################################################################################################
//
//							 			UART [.cpp]
//
//#################################################################################################
#if defined(RT_HW_LINK_UART)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							 	1.СОЗДАНИЕ ОБЪЕКТОВ ДЛЯ выбранного КОНТРОЛЛЕРА
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//										1.1. CORE STM32
//=================================================================================================
#if !defined(RT_HW_MCU_CREATE_UART) && defined(RT_HW_CORE_STM32)	
    #define  RT_HW_MCU_CREATE_UART
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART1) && defined(RT_HW_CREATE_UART1)
HardwareSerial  		Serial1(RT_HW_UART1_RX,RT_HW_UART1_TX);
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART2) && defined(RT_HW_CREATE_UART2)
HardwareSerial  		Serial2(RT_HW_UART2_RX,RT_HW_UART2_TX);
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART3) && defined(RT_HW_CREATE_UART3)
HardwareSerial  		Serial3(RT_HW_UART3_RX,RT_HW_UART3_TX);
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART4) && defined(RT_HW_CREATE_UART4)
HardwareSerial  		Serial4(RT_HW_UART4_RX,RT_HW_UART4_TX);
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART5) && defined(RT_HW_CREATE_UART5)
HardwareSerial  		Serial5(RT_HW_UART5_RX,RT_HW_UART5_TX);
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART6) && defined(RT_HW_CREATE_UART6)
HardwareSerial  		Serial6(RT_HW_UART6_RX,RT_HW_UART6_TX);
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART7) && defined(RT_HW_CREATE_UART7)
HardwareSerial  		Serial7(RT_HW_UART7_RX,RT_HW_UART7_TX);
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART8) && defined(RT_HW_CREATE_UART8)
HardwareSerial  		Serial8(RT_HW_UART8_RX,RT_HW_UART8_TX);
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART9) && defined(RT_HW_CREATE_UART9)
HardwareSerial  		Serial9(RT_HW_UART9_RX,RT_HW_UART9_TX);
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART10) && defined(RT_HW_CREATE_UART10)
HardwareSerial  		Serial10(RT_HW_UART10_RX,RT_HW_UART10_TX);
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART11) && defined(RT_HW_CREATE_UART11)
HardwareSerial  		Serial11(RT_HW_UART11_RX,RT_HW_UART11_TX);
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART12) && defined(RT_HW_CREATE_UART12)
HardwareSerial  		Serial12(RT_HW_UART12_RX,RT_HW_UART12_TX);
#endif
//-------------------------------------------------------------------------------------------------
#endif
//=================================================================================================
//									1.2. CORE RP2040
//=================================================================================================
#if !defined(RT_HW_MCU_CREATE_UART) && defined(RT_HW_CORE_RP2040)	
    #define  RT_HW_MCU_CREATE_UART
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART3) && defined(RT_HW_CREATE_UART3)
SerialPIO  		Serial3(RT_HW_UART3_TX, RT_HW_UART3_RX,64);
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART4) && defined(RT_HW_CREATE_UART4)
SerialPIO 		Serial4(RT_HW_UART4_TX, RT_HW_UART4_RX,64);
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART5) && defined(RT_HW_CREATE_UART5)
SerialPIO  		Serial5(RT_HW_UART5_TX, RT_HW_UART5_RX,64);
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART6) && defined(RT_HW_CREATE_UART6)
SerialPIO 		Serial6(RT_HW_UART6_TX, RT_HW_UART6_RX,64);
#endif		
//-------------------------------------------------------------------------------------------------
#endif	
//=================================================================================================
//									1.3. CORE ESP32
// Примечание: создание объекта BluetoothSerial требует памяти (500kb)
//             независмо от использования/не использования BlueTooth
//=================================================================================================
#if !defined(RT_HW_MCU_CREATE_UART) && defined(RT_HW_CORE_ESP32)	
    #define  RT_HW_MCU_CREATE_UART
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UARTB) && defined(RT_HW_ESP32_PERMIT_UARTB) 	//--num=200; 
BluetoothSerial SerialB; 	//--Объект UARTB;
#endif
//-------------------------------------------------------------------------------------------------
#endif	
//=================================================================================================
//									1.4. CORE ESP8266
//=================================================================================================
#if !defined(RT_HW_MCU_CREATE_UART) && defined(RT_HW_CORE_ESP8266)	
    #define  RT_HW_MCU_CREATE_UART
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_CREATE_UART2) 
#define defined(RT_HW_PERMIT_UART2) && RT_HW_CREATE_UART2
HardwareSerial  Serial2(2); 
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UARTS) && defined(RT_HW_CREATE_UARTS) 	//--num=100;
SoftwareSerial SerialS(RT_HW_UARTS_RX, RT_HW_UARTS_TX); 		
#endif
//-------------------------------------------------------------------------------------------------
#endif	
//=================================================================================================
//									1.5. CORE AVR
//=================================================================================================
#if !defined(RT_HW_MCU_CREATE_UART) && defined(RT_HW_CORE_AVR)	
    #define  RT_HW_MCU_CREATE_UART
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UARTS) && defined(RT_HW_CREATE_UARTS) 	//--num=100;
  SoftwareSerial SerialS(RT_HW_UARTS_RX, RT_HW_UARTS_TX); 		
#endif
//-------------------------------------------------------------------------------------------------
#endif
//=================================================================================================
//									1.9.CORE Не опознанные
//=================================================================================================
#if !defined(RT_HW_MCU_CREATE_UART)	
     #define RT_HW_MCU_CREATE_UART
//-------------------------------------------------------------------------------------------------
#endif
//=================================================================================================

//=================================================================================================	


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//										API.cpp UART
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//										1.Инициализация UART;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//						        1.1.Инициализация UARTn как MASTER
//void begin(unsigned long baud, uint32_t config=SERIAL_8N1, int8_t rxPin=-1, int8_t txPin=-1, 
//           bool invert=false, unsigned long timeout_ms = 20000UL, uint8_t rxfifo_full_thrhd = 112);
//=================================================================================================	
uint8_t  RT_HW_BASE:: uartBegin(uint8_t n){
//-------------------------------------------------------------------------------------------------
uartSetCodeErr(0,n);							//--Сброс кода ошибки;
if(uartGetStatus(n)==1){return 1;} 				//--Выход, если UARTn уже настроен как Master;
//if(uartSetBusy(n)==0)	{return 0;}				//--Захват UARTn или выход, если UARTn занят;
Serial.println("1.uartBegin");
//==================================================================================================
//											1.1.0. UART0
//==================================================================================================
#if defined(RT_HW_PERMIT_UART0)	
//--------------------------------------------------------------------------------------------------
//								1.1.0.1. UART0 && (ESP32S || ESP32S2 || defined(RT_HW_CORE_ESP32S3
//--------------------------------------------------------------------------------------------------
#if defined(RT_HW_CORE_ESP32S) || defined(RT_HW_CORE_ESP32S2) || defined(RT_HW_CORE_ESP32S3)
if(n==0){if(uartGetStatus(n)==0){uartSetStatus(1,n); Serial.begin(uartGetSpeed(n),uartGetConfig(n),(int8_t)uartGetPinRX(n),(int8_t)uartGetPinTX(n), false, 20000UL, 112);}  return 1;}
#endif
//--------------------------------------------------------------------------------------------------
//								1.1.0.2. UART0 && (ESP32-C3)
//--------------------------------------------------------------------------------------------------
#if defined(RT_HW_CORE_ESP32C3)
if(n==0){if(uartGetStatus(n)==0){uartSetStatus(1,n); Serial.begin(uartGetSpeed(n));}  return 1;}
#endif
//--------------------------------------------------------------------------------------------------
//								1.1.0.3. UART0 && (RP2040)
//--------------------------------------------------------------------------------------------------
#if defined(RT_HW_CORE_RP2040)
if(n==0){if(uartGetStatus(n)==0){uartSetStatus(1,n); Serial.begin(uartGetSpeed(n));}  return 1;}
#endif
//--------------------------------------------------------------------------------------------------
//								1.1.0.4.UART0 && (ANON)
//--------------------------------------------------------------------------------------------------
if(n==0){if(uartGetStatus(n)==0){uartSetStatus(1,n); Serial.begin(uartGetSpeed(n));} return 1;}
#endif	
//==================================================================================================
//										 1.1.1.UART1
//==================================================================================================
#if defined(RT_HW_PERMIT_UART1)
//--------------------------------------------------------------------------------------------------
//								1.1.1.1. UART1 && (ESP32S || ESP32S2 || defined(RT_HW_CORE_ESP32S3
//--------------------------------------------------------------------------------------------------
#if defined(RT_HW_CORE_ESP32S) || defined(RT_HW_CORE_ESP32S2) || defined(RT_HW_CORE_ESP32S3)
if(n==1){if(uartGetStatus(n)==0){uartSetStatus(1,n); Serial1.begin(uartGetSpeed(n),uartGetConfig(n),(int8_t)uartGetPinRX(n),(int8_t)uartGetPinTX(n), false, 20000UL, 112);}  return 1;}
#endif
//--------------------------------------------------------------------------------------------------
//								1.1.1.2. UART1 && (ESP32-C3)
//--------------------------------------------------------------------------------------------------
#if defined(RT_HW_CORE_ESP32C3)
if(n==1){if(uartGetStatus(n)==0){uartSetStatus(1,n); Serial1.begin(uartGetSpeed(n),uartGetConfig(n),(int8_t)uartGetPinRX(n),(int8_t)uartGetPinTX(n),false, 20000UL, 112);}  return 1;}
#endif
//--------------------------------------------------------------------------------------------------
//								1.1.1.3. UART1 && (Other)
//--------------------------------------------------------------------------------------------------
if(n==1){if(uartGetStatus(n)==0){uartSetStatus(1,n); Serial1.begin(uartGetSpeed(n));} 
return 1;}
#endif	
//==================================================================================================
//										 1.2.UART2
//==================================================================================================
#if defined(RT_HW_PERMIT_UART2)
//--------------------------------------------------------------------------------------------------
//								1.1.2.1. UART1 && (ESP32S || ESP32S2 || defined(RT_HW_CORE_ESP32S3
//--------------------------------------------------------------------------------------------------
#if defined(RT_HW_CORE_ESP32S) || defined(RT_HW_CORE_ESP32S2) || defined(RT_HW_CORE_ESP32S3)
if(n==2){if(uartGetStatus(n)==0){uartSetStatus(1,n); Serial2.begin(uartGetSpeed(n),uartGetConfig(n),(int8_t)uartGetPinRX(n),(int8_t)uartGetPinTX(n), false, 20000UL, 112);}  return 1;}
#endif
//--------------------------------------------------------------------------------------------------
//								1.1.2.2. UART1 && другие MCU
//--------------------------------------------------------------------------------------------------
if(n==2){if(uartGetStatus(n)==0){uartSetStatus(1,n); Serial2.begin(uartGetSpeed(n));} return 1;}
#endif	
//==================================================================================================
//										 1.3.UART3
//==================================================================================================
#if	defined(RT_HW_PERMIT_UART3)
if(n==3){if(uartGetStatus(n)==0){uartSetStatus(1,n); Serial3.begin(uartGetSpeed(n));} return 1;}
#endif
//==================================================================================================
//										 1.4.UART4
//==================================================================================================
#if	defined(RT_HW_PERMIT_UART4)
if(n==4){if(uartGetStatus(n)==0){uartSetStatus(1,n); Serial4.begin(uartGetSpeed(n));} return 1;}
#endif	
//==================================================================================================
//										 1.5.UART5
//==================================================================================================
#if	defined(RT_HW_PERMIT_UART5)
if(n==5){if(uartGetStatus(n)==0){uartSetStatus(1,n); Serial5.begin(uartGetSpeed(n));} return 1;}
#endif
//==================================================================================================
//										 1.6.UART6
//==================================================================================================
#if	defined(RT_HW_PERMIT_UART6)
if(n==6){if(uartGetStatus(n)==0){uartSetStatus(1,n); Serial6.begin(uartGetSpeed(n));} return 1;}
#endif
//==================================================================================================
//										 1.7.UART7
//==================================================================================================
#if	defined(RT_HW_PERMIT_UART7)
if(n==7){if(uartGetStatus(n)==0){uartSetStatus(1,n); Serial7.begin(uartGetSpeed(n));} return 1;}
#endif
//==================================================================================================
//										 1.8.UART8
//==================================================================================================
#if	defined(RT_HW_PERMIT_UART8)
if(n==8){if(uartGetStatus(n)==0){uartSetStatus(1,n); Serial8.begin(uartGetSpeed(n));} return 1;}
#endif
//==================================================================================================
//										 1.100.UARTS(SoftwareSerial)
//==================================================================================================
#if	defined(RT_HW_PERMIT_UARTS)
if(n==100){if(uartGetStatus(n)==0){uartSetStatus(1,n); SerialS.begin(uartGetSpeed(n));} return 1;}
#endif
//==================================================================================================
//										 1.200.UART200(BlueTooth)
//==================================================================================================
#if	defined(RT_HW_PERMIT_UARTB)
if(n==200){if(uartGetStatus(n)==0){uartSetStatus(1,n); SerialB.begin(LinkUARTB.name);} return 1;}
#endif			
//--------------------------------------------------------------------------------------------------
return 1;};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
// 										2.Отключение UARTn
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
void RT_HW_BASE:: uartEnd(uint8_t n){
(void)n;
#if defined(RT_HW_PERMIT_UART0)
if(n==0){uartSetStatus(0,n); Serial.end();   	return;}
#endif	
#if defined(RT_HW_PERMIT_UART1) 
if(n==1){uartSetStatus(0,n); Serial1.end();  	return;}
#endif		
#if defined(RT_HW_PERMIT_UART2)
if(n==2){uartSetStatus(0,n); Serial2.end();  	return;}
#endif	
#if defined(RT_HW_PERMIT_UART3)
if(n==3){uartSetStatus(0,n); Serial3.end();  	return;}
#endif
#if defined(RT_HW_PERMIT_UART4)
if(n==4){uartSetStatus(0,n); Serial4.end();  	return;}
#endif	
#if defined(RT_HW_PERMIT_UART5)
if(n==5){uartSetStatus(0,n); Serial5.end();  	return;}
#endif
#if defined(RT_HW_PERMIT_UART6)
if(n==6){uartSetStatus(0,n); Serial6.end();  	return;}
#endif
#if defined(RT_HW_PERMIT_UART7)
if(n==7){uartSetStatus(0,n); Serial7.end();  	return;}
#endif
#if defined(RT_HW_PERMIT_UART8)
if(n==1){uartSetStatus(0,n); Serial8.end();  	return;}
#endif
//--------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UARTS)
if(n==100){uartSetStatus(0,n); SerialS.end();	return;}
#endif
#if defined(RT_HW_PERMIT_UARTB)
if(n==200){uartSetStatus(0,n); SerialB.end();  	return;}
#endif			
};	

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
// 								3.Проверка подключения устройства (Serial)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 		
bool     RT_HW_BASE:: uartSerial (uint8_t n){
//==================================================================================================
//										3.0. UART0
//==================================================================================================
#if defined(RT_HW_PERMIT_UART0)
//--------------------------------------------------------------------------------------------------
//										3.0.1. UART0 && (ESP32-C3)
//--------------------------------------------------------------------------------------------------
#if defined(RT_HW_CORE_ESP32C3)
if(n==0){
if(uartUSB.dir==4) {return 1;}
if(uartUSB.dir==0) {uartUSB.timeBegin=millis()+500;	 uartUSB.dir++;  return 0;}
if(uartUSB.dir==1) {if(millis()<(uartUSB.timeBegin))              	{return 0;} 				    
					if(!Serial)									  	{return 0;}	//--Проверка готовности USB;
					uartUSB.timeBegin=millis();
					uartUSB.dir++;									 return 0;} //--Переход на технологическую паузу;
if(uartUSB.dir==2) {if((millis()-uartUSB.timeBegin)<20) 	      	{return 0;} //--Пауза 20мс;
                    bitSet(uart.ready,0);            uartUSB.dir=4;  return 0;} //--Установка флага готовности и переход на завершение;
//				    bitSet(uart.ready,0); 			 uartUSB.dir=4;  return 1;}
}
//--------------------------------------------------------------------------------------------------
//										3.0.2. UART0 && (STM32)
//--------------------------------------------------------------------------------------------------
#elif defined(RT_HW_CORE_STM32) && defined (USBCON) && defined(USBD_USE_CDC) 
if(n==0){
if(uartUSB.dir==4) {return 1;}	
if(uartUSB.dir==0) {if(++uartUSB.cnt>20) {uartUSB.cnt=5;} 
                    uartUSB.timeBegin=millis()+200+(100*uartUSB.cnt);  	uartUSB.dir++;	return 0;}
if(uartUSB.dir==1) {if(millis()<uartUSB.timeBegin)									   {return 0;}
					if(CDC_connected()){uartUSB.timeBegin=millis()+20;  uartUSB.dir++; 	return 0;}					
																		uartUSB.dir=0;  return 0;}
if(uartUSB.dir==2) {if(millis()<uartUSB.timeBegin)									   {return 0;} 				    
														 uartUSB.cnt++; uartUSB.dir++;	return 0;}
if(uartUSB.dir==3) {bitSet(uart.ready,0); Serial.flush();               uartUSB.dir=4;	return 1;} 
}
//--------------------------------------------------------------------------------------------------
//										3.0.3. UART0 && (RP2040)
//--------------------------------------------------------------------------------------------------
#elif defined(RT_HW_CORE_RP2040)
if(n==0){
if(uartUSB.dir==4) {if(Serial){return 1;} 		else{uartUSB.dir=0;  return 0;}}	
if(uartUSB.dir==0) {uartUSB.cnt++; 
                    uartUSB.timeBegin=millis()+500;  uartUSB.dir++;	 return 0;}
if(uartUSB.dir==1) {if(millis()<uartUSB.timeBegin)	{				 return 0;}
					uartUSB.cnt++;;
					if(!Serial)              		{uartUSB.dir=0;	 return 0;}
					uartUSB.timeBegin=millis()+1000; uartUSB.dir++;  return 0;}
if(uartUSB.dir==1) {if(millis()<uartUSB.timeBegin)					{return 0;} 				    
					if(!Serial)              		{uartUSB.dir=0;  return 0;}
					uartUSB.cnt++;					 
													 uartUSB.dir=0;  return 0;}
if(uartUSB.dir==2) {uartUSB.cnt++;
					bitSet(uart.ready,0); Serial.flush(); uartUSB.dir=4;	 return 1;} 
}
//--------------------------------------------------------------------------------------------------
//										3.0.4. UART0 && (other)
//--------------------------------------------------------------------------------------------------
#else		
if(n==0){if(Serial) {bitSet(uart.ready,n); 	return 1;} else {return 0;}}
#endif
//-----------------------------------------------------------------------------------------------
#endif
//==================================================================================================
//										3.1.  UART1-UART8
//==================================================================================================
#if defined(RT_HW_PERMIT_UART1)
if(n==1){if(Serial1){bitSet(uart.ready,n); 	return 1;}}
#endif		
#if defined(RT_HW_PERMIT_UART2)
if(n==2){if(Serial2){bitSet(uart.ready,n); 	return 1;}}
#endif	
#if defined(RT_HW_PERMIT_UART3)
if(n==3){if(Serial3){bitSet(uart.ready,n); 	return 1;}}
#endif
#if defined(RT_HW_PERMIT_UART4)
if(n==4){if(Serial4){bitSet(uart.ready,n); 	return 1;}}
#endif	
#if defined(RT_HW_PERMIT_UART5)
if(n==5){if(Serial5){bitSet(uart.ready,n); 	return 1;}}
#endif
#if defined(RT_HW_PERMIT_UART6)
if(n==6){if(Serial6){bitSet(uart.ready,n); 	return 1;}}
#endif
#if defined(RT_HW_PERMIT_UART7)
if(n==7){if(Serial7){bitSet(uart.ready,n); 	return 1;}}
#endif
#if defined(RT_HW_PERMIT_UART8)
if(n==8){if(Serial8){bitSet(uart.ready,n); 	return 1;}}
#endif
//==================================================================================================
//										3.100  UARTS (SoftwareSerial)
//==================================================================================================
#if defined(RT_HW_PERMIT_UARTS)
if(n==100){if(SerialS){bitSet(uart.ready,n); return 1;}}
#endif
//==================================================================================================
//										3.200  UARTB (BlueTooth)
//==================================================================================================
#if defined(RT_HW_PERMIT_UARTB)
if(n==200){if(SerialB){bitSet(uart.ready,n); return 1;}}
#endif		
return 0;	
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
// 										4.Проверка входного буфера UARTn
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
uint16_t RT_HW_BASE:: uartAvailable(uint8_t n){
//==================================================================================================
//										4.0. UART0-UART8
//==================================================================================================
#if defined(RT_HW_PERMIT_UART0)
if(n==0){return Serial.available();}
#endif	
#if defined(RT_HW_PERMIT_UART1) && !defined(RT_HW_BLOCK_UART1_READ) //---У ESP8266 Serail1 работает только на выход;
if(n==1){return Serial1.available();}
#endif		
#if defined(RT_HW_PERMIT_UART2)
if(n==2){return Serial2.available();}
#endif	
#if defined(RT_HW_PERMIT_UART3)
if(n==3){return Serial3.available();}
#endif
#if defined(RT_HW_PERMIT_UART4)
if(n==4){return Serial4.available();}
#endif	
#if defined(RT_HW_PERMIT_UART5)
if(n==5){return Serial5.available();}
#endif
#if defined(RT_HW_PERMIT_UART6)
if(n==6){return Serial6.available();}
#endif
#if defined(RT_HW_PERMIT_UART7)
if(n==7){return Serial7.available();}
#endif
#if defined(RT_HW_PERMIT_UART8)
if(n==8){return Serial8.available();}
#endif
//==================================================================================================
//										4.100  UARTS (SoftwareSerial)
//==================================================================================================
#if defined(RT_HW_PERMIT_UARTS)
if(n==100){return SerialS.available();}
#endif
//==================================================================================================
//										4.200  UARTB (BlueTooth)
//==================================================================================================
#if defined(RT_HW_PERMIT_UARTB)
if(n==200){return SerialB.available();}
#endif		
return 	0;	
};	
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
// 										5.Проверка выходного буфера UARTn
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
uint16_t RT_HW_BASE:: uartAvailableForWrite(uint8_t n){												
//==================================================================================================
//										5.0. UART0-UART8
//==================================================================================================
#if defined(RT_HW_PERMIT_UART0)
if(n==0){return Serial.availableForWrite();}
#endif	
#if defined(RT_HW_PERMIT_UART1)
if(n==1){return Serial1.availableForWrite();}
#endif		
#if defined(RT_HW_PERMIT_UART2)
if(n==2){return Serial2.availableForWrite();}
#endif	
#if defined(RT_HW_PERMIT_UART3)
if(n==3){return Serial3.availableForWrite();}
#endif
#if defined(RT_HW_PERMIT_UART4)
if(n==4){return Serial4.availableForWrite();}
#endif	
#if defined(RT_HW_PERMIT_UART5)
if(n==5){return Serial5.availableForWrite();}
#endif
#if defined(RT_HW_PERMIT_UART6)
if(n==6){return Serial6.availableForWrite();}
#endif
#if defined(RT_HW_PERMIT_UART7)
if(n==7){return Serial7.availableForWrite();}
#endif
#if defined(RT_HW_PERMIT_UART8)
if(n==8){return Serial8.availableForWrite();}
#endif
//==================================================================================================
//										5.100  UARTS (SoftwareSerial)
//==================================================================================================
#if defined(RT_HW_PERMIT_UARTS)
//if(n==9){return SerialS.availableForWrite();}		//--Не везде эта функция реализована
#endif
#if defined(RT_HW_PERMIT_UARTB)
if(n==10){return SerialB.availableForWrite();}
#endif
//==================================================================================================
//										5.200  UARTB (BlueTooth)
//==================================================================================================
if(n) {return 63;}
return 	63;};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
// 										6.Чтение байта из UARTn
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
uint8_t  RT_HW_BASE:: uartRead(uint8_t n){
//==================================================================================================
//										6.0. UART0-UART8
//==================================================================================================
#if defined(RT_HW_PERMIT_UART0)
if(n==0){return Serial.read();}
#endif	
#if defined(RT_HW_PERMIT_UART1) && !defined(RT_HW_BLOCK_UART1_READ) //---У ESP8266 Serail1 работает только на выход;
if(n==1){return Serial1.read();}
#endif		
#if defined(RT_HW_PERMIT_UART2) 
if(n==2){return Serial2.read();}
#endif	
#if defined(RT_HW_PERMIT_UART3)
if(n==3){return Serial3.read();}
#endif
#if defined(RT_HW_PERMIT_UART4)
if(n==4){return Serial4.read();}
#endif	
#if defined(RT_HW_PERMIT_UART5)
if(n==5){return Serial5.read();}
#endif
#if defined(RT_HW_PERMIT_UART6)
if(n==6){return Serial6.read();}
#endif
#if defined(RT_HW_PERMIT_UART7)
if(n==7){return Serial7.read();}
#endif
#if defined(RT_HW_PERMIT_UART8)
if(n==8){return Serial8.read();}
#endif
//==================================================================================================
//										6.100  UARTS (SoftwareSerial)
//==================================================================================================
#if defined(RT_HW_PERMIT_UARTS)
if(n==100){return SerialS.read();}
#endif
//==================================================================================================
//										6.200  UARTB (BlueTooth)
//==================================================================================================
#if defined(RT_HW_PERMIT_UARTB)
if(n==200){return SerialB.read();}
#endif		
return 	0;	
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
// 										7.Запись байта в UARTn
//	Примечание: для UART0.RP2040 реализована "заплатка!!!  (см. также радел 8)
//              Следует отслеживать новые версии CORE RP2040 и со временем отказаться от "заплатки". 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
uint8_t  RT_HW_BASE:: uartWrite(uint8_t val, uint8_t n){
//==================================================================================================
//										 7.0.UART0
//==================================================================================================
#if defined(RT_HW_PERMIT_UART0)
//--------------------------------------------------------------------------------------------------
//										7.0.1.UART0 & (RP2040)
//--------------------------------------------------------------------------------------------------
#if defined(RT_HW_CORE_RP2040)
//if(n==0){
//return Serial.print(val);
//Serial.print(val);
//return;
///}
#endif
//--------------------------------------------------------------------------------------------------
//										7.0.2.UART0 & (Other)
//--------------------------------------------------------------------------------------------------
if(n==0){Serial.write(val); return 1;}
//--------------------------------------------------------------------------------------------------
#endif	
//==================================================================================================
//										 7.1.UART1-UART8
//==================================================================================================
#if defined(RT_HW_PERMIT_UART1)
if(n==1){Serial1.write(val); return 1;}
#endif		
#if defined(RT_HW_PERMIT_UART2)
if(n==2){Serial2.write(val); return 1;}
#endif	
#if defined(RT_HW_PERMIT_UART3)
if(n==3){Serial3.write(val); return 1;}
#endif
#if defined(RT_HW_PERMIT_UART4)
if(n==4){Serial4.write(val); return 1;}
#endif	
#if defined(RT_HW_PERMIT_UART5)
if(n==5){Serial5.write(val); return 1;}
#endif
#if defined(RT_HW_PERMIT_UART6)
if(n==6){Serial6.write(val); return 1;}
#endif
#if defined(RT_HW_PERMIT_UART7)
if(n==7){Serial7.write(val); return 1;}
#endif
#if defined(RT_HW_PERMIT_UART8)
if(n==8){Serial8.write(val); return 1;}
#endif
//==================================================================================================
//										7.100  UARTS (SoftwareSerial)
//==================================================================================================
#if defined(RT_HW_PERMIT_UARTS)
if(n==100){SerialS.write(val); return 1;}
#endif
//==================================================================================================
//										7.200  UARTB (BlueTooth)
//==================================================================================================
#if defined(RT_HW_PERMIT_UARTB)
if(n==200){SerialB.write(val); return 1;}
#endif			
if(val) {return 1;}
return 1;}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
// 										8. Вывод print() 
//  Примечание: это временная "заплатка" для совместимости с CORE RP2040 
//              Следует отслеживать новые версии CORE RP2040 и со временем отказаться от "заплатки". 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
void     RT_HW_BASE:: uartPrint( String str,uint8_t n){
//==================================================================================================
//										8.0. UART0-UART8
//==================================================================================================
#if defined(RT_HW_PERMIT_UART0)
if(n==0){Serial.print(str);}
#endif	
#if defined(RT_HW_PERMIT_UART1)
if(n==1){Serial1.print(str);}
#endif		
#if defined(RT_HW_PERMIT_UART2)
if(n==2){Serial2.print(str);}
#endif	
#if defined(RT_HW_PERMIT_UART3)
if(n==3){Serial3.print(str);}
#endif
#if defined(RT_HW_PERMIT_UART4)
if(n==4){Serial4.print(str);}
#endif	
#if defined(RT_HW_PERMIT_UART5)
if(n==5){Serial5.print(str);}
#endif
#if defined(RT_HW_PERMIT_UART6)
if(n==6){Serial6.print(str);}
#endif
#if defined(RT_HW_PERMIT_UART7)
if(n==7){Serial7.print(str);}
#endif
#if defined(RT_HW_PERMIT_UART8)
if(n==8){Serial8.print(str);}
#endif
//==================================================================================================
//										8.100  UARTS (SoftwareSerial)
//==================================================================================================
#if defined(RT_HW_PERMIT_UARTS)
if(n==100){SerialS.print(str);}
#endif
//==================================================================================================
//										8.200  UARTB (BlueTooth)
//==================================================================================================
#if defined(RT_HW_PERMIT_UARTB)
if(n==200){SerialB.print(str);}
#endif		
};
//=================================================================================================
//#################################################################################################
#endif  // if defined(RT_HW_LINK_UART)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++