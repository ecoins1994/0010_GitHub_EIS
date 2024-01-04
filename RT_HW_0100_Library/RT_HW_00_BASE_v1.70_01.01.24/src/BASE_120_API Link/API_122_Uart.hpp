//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                        				API.h for UART
//=================================================================================================
// AVR  	- 1 UART, for MEGA2560 - UART;
// ESP8266  - 1 UART(Serial0) + 1 UART TX(Serial1);
// ESP32S   - 3 UART; 
// SAM3     - 4-UART;
// STM32F103C   - 3 UART;
// STM32F4x1Cx  - 3 UART;
// STM32F40703Vx - 6 UART;
// Raspberry Pi Pico - 2 UART.
//=================================================================================================
//	ecoins@mail.ru 12.05.2023г.
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++			

#define RT_HW_LINK_UART		//---FUNCTION CONNECTION DEFINER UART
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//										0.1.1Structures for UART
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//										0.General structure
//	bit.0-13-HardWareUart,	bit.14-SoftwareSerial, bit.15-BlueTooth; 
//=================================================================================================	
struct RT_HW_STRUCT_UART_RXTX{
uint16_t begin=0;	//--Initialization flags (set after Serialx.begin()); 
uint16_t ready=0;	//--Ready          flags  (set after checking if(Serialx);
uint16_t busy=0; 	//--UART    busy   flags;
};	
//=================================================================================================
//										0.1.2.Structure for USB
//=================================================================================================	
struct RT_HW_STRUCT_UART_USB {
uint32_t timeBegin; 
uint16_t dir=0;
uint8_t  cnt=0; 
uint8_t  bf8=0;
};
//=================================================================================================
//										0.1.3.Data object structure for UARTx 
//=================================================================================================	
struct RT_HW_STRUCT_UART     {
uint8_t  custom=0;				//--1.Setting option;
uint8_t  status=0;				//--2.Status bus: no init=0; Master=1; Slave=2;
uint8_t  codeErr=0;				//--3.Code error; 	
uint8_t  busy=0;  				//--4.busy bus;
//-------------------------------------------------------------------------------------------------
uint8_t  rx=255; 				//--Pin number RX;
uint8_t  tx=255;				//--Pin number TX;
uint8_t  de=255; 				//--Pin number DE for RS-485
uint8_t  dir=0;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
uint32_t speed=115200;			//--UART speed;
#if defined(SERIAL_8N1)
uint32_t config=SERIAL_8N1;		//--UART configuration;
#else 
uint32_t config=0x800001C;
#endif	
//-------------------------------------------------------------------------------------------------
uint8_t dataBit=8;				//--5,6,7,8
uint8_t stopBit=1;				//--1,2;
uint8_t parity=0;				//--0-None, 1- even; 2-odd;
};	
//=================================================================================================
//										0.1.4.Structure for Embedded BlueTooth (ESP32,RP2040)
//=================================================================================================	
struct RT_HW_STRUCT_BLUETOOTH{
uint8_t  custom=0;				//--1.Setting option;
uint8_t  status=0;				//--2.Status bus: no init=0; Master=1; Slave=2;
uint8_t  codeErr=0;				//--3.Code error; 
uint8_t  busy=0;  				//--4.busy bus;
//-------------------------------------------------------------------------------------------------
uint8_t  dir=0;
//-------------------------------------------------------------------------------------------------
uint32_t speed=115200;
String name="ESP32S BTH EIS";
};
//=================================================================================================
// 									0.2.1General object (busy ready flags)
//=================================================================================================
RT_HW_STRUCT_UART_RXTX uart;
//=================================================================================================
// 									0.2.2Object for USB object data
//=================================================================================================
RT_HW_STRUCT_UART_USB uartUSB;
//=================================================================================================
// 									0.2.3.Objects for given UARTx objects
//=================================================================================================
#if defined(RT_HW_PERMIT_UART0)
RT_HW_STRUCT_UART LinkUART0;
#endif
#if defined(RT_HW_PERMIT_UART1)
RT_HW_STRUCT_UART LinkUART1;
#endif
#if defined(RT_HW_PERMIT_UART2)
RT_HW_STRUCT_UART LinkUART2;
#endif
#if defined(RT_HW_PERMIT_UART3)
RT_HW_STRUCT_UART LinkUART3;
#endif
#if defined(RT_HW_PERMIT_UART4)
RT_HW_STRUCT_UART LinkUART4;
#endif
#if defined(RT_HW_PERMIT_UART5)
RT_HW_STRUCT_UART LinkUART5;
#endif
#if defined(RT_HW_PERMIT_UART6)
RT_HW_STRUCT_UART LinkUART6;
#endif
#if defined(RT_HW_PERMIT_UART7)
RT_HW_STRUCT_UART LinkUART7;
#endif
#if defined(RT_HW_PERMIT_UART8)
RT_HW_STRUCT_UART LinkUART8;
#endif
#if defined(RT_HW_PERMIT_UART9)
RT_HW_STRUCT_UART LinkUART9;
#endif
#if defined(RT_HW_PERMIT_UART10)
RT_HW_STRUCT_UART LinkUART10;
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UARTS)
RT_HW_STRUCT_UART LinkUARTS;
#endif
#if defined(RT_HW_PERMIT_UARTB)
RT_HW_STRUCT_BLUETOOTH LinkUARTB;
#endif

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                          		2. INIT PINS, PARAM
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//							+++++++ 2.1. Set Pins ++++++
//=================================================================================================
void	 uartSetPins(uint8_t bus){uartSetPins(uartGetPinRX(bus),uartGetPinTX(bus), bus);};
//-------------------------------------------------------------------------------------------------
void	 uartSetPins(uint8_t rx, uint8_t tx, uint8_t bus){
//=================================================================================================
//									2.1.1. AVR,SAM3X,SAMD21,ANON
//=================================================================================================
#if defined(RT_HW_CORE_AVR) || defined(RT_HW_CORE_SAM3X) || defined(RT_HW_CORE_SAMD21) || defined(RT_HW_CORE_ANON)
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART0)
if(bus==0){uartSetCodeErr(0,bus); if(tx || rx || bus){return;}};	//--To block warning C++;
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART1)
if(bus==1){uartSetCodeErr(0,bus); if(tx || rx || bus){return;}};	//--To block warning C++;
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART2)
if(bus==2){uartSetCodeErr(0,bus); if(tx || rx || bus){return;}};	//--To block warning C++;
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART3)
if(bus==3){uartSetCodeErr(0,bus); if(tx || rx || bus){return;}};	//--To block warning C++;
#endif
//--------------------------------------------------------------------------------------------------
uartSetCodeErr(64,bus);
if(bus==0){uartSetCodeErr(0,bus); if(tx || rx || bus){return;}};	//--To block warning C++. Exit by no bus AVR,SAMX,SAMD21,ANON;
#endif
//=================================================================================================
//									2.1.2. ESP8266
//=================================================================================================
#if defined(RT_HW_CORE_ESP8266)
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART0)	
if(bus==0){
if(rx==tx) {uartSetCodeErr(60,bus); return;}		//--Exit by mistake on rx=tx;
if(rx>=16) {uartSetCodeErr(61,bus); return;}		//--Exit by mistake on rx;
if(tx>=17) {uartSetCodeErr(62,bus); return;}		//--Exit by mistake on tx;
LinkUART0.rx=rx; LinkUART0.tx=rx;					//--Set pins rx,tx bus=0;
return;}											//--Successful Exit  bus=0;
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART1)	
if(bus==1) {
if(tx>=17) {uartSetCodeErr(62,bus); return;}		//--Exit by mistake on tx;
LinkUART1.tx=tx; 									//--Set pins tx bus=1;
return;}											//--Successful Exit  bus=1;
#endif
//-------------------------------------------------------------------------------------------------
uartSetCodeErr(64,bus);if(tx || rx || bus){return;};//--To block warning C++. Exit by no bus ESP8266;
#endif
//=================================================================================================
//									2.1.3. ESP32
//=================================================================================================
#if defined(RT_HW_CORE_ESP32)
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART0)
if(bus==0){
if(rx==tx) {uartSetCodeErr(60,bus); return;}	//--Exit by mistake on rx=tx;
if(rx>=34) {uartSetCodeErr(61,bus); return;}	//--Exit by mistake on rx;
if(tx>=34) {uartSetCodeErr(62,bus); return;}	//--Exit by mistake on tx;
LinkUART0.rx=rx; LinkUART0.tx=tx;				//--Set pins rx,tx bus=0;
return;}										//--Successful Exit  bus=0;
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART1)
if(bus==1){
if(rx==tx) {uartSetCodeErr(60,bus); return;}	//--Exit by mistake on rx=tx;
if(rx>=34) {uartSetCodeErr(61,bus); return;}	//--Exit by mistake on rx;
if(tx>=34) {uartSetCodeErr(62,bus); return;}	//--Exit by mistake on tx;
LinkUART1.rx=rx; LinkUART1.tx=tx;				//--Set pins rx,tx bus=0;
return;}										//--Successful Exit  bus=0;
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART2)
if(bus==2){
if(rx==tx) {uartSetCodeErr(60,bus); return;}	//--Exit by mistake on rx=tx;
if(rx>=34) {uartSetCodeErr(61,bus); return;}	//--Exit by mistake on rx;
if(tx>=34) {uartSetCodeErr(62,bus); return;}	//--Exit by mistake on tx;
LinkUART2.rx=rx; LinkUART2.tx=tx;				//--Set pins rx,tx bus=0;
return;}										//--Successful Exit  bus=0;
#endif
//-------------------------------------------------------------------------------------------------
uartSetCodeErr(64,bus);if(tx || rx || bus){return;};//--To block warning C++. Exit by no bus ESP32;
#endif
//=================================================================================================
//									2.1.4. RP2040
//=================================================================================================
#if defined(RT_HW_CORE_RP2040)
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART0)	
//----UART0->USB: pin chip 47,46
if(bus==0){;}
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART1)
//----UART1 (rx,tx): 1,0; 13,12; 17,16; 29,28;
if(bus==1){
if((rx==1) && (tx==0)) {LinkUART1.rx=rx; LinkUART1.tx=tx; return;} 
if((rx==13)&& (tx==12)){LinkUART1.rx=rx; LinkUART1.tx=tx; return;} 
if((rx==17)&& (tx==16)){LinkUART1.rx=rx; LinkUART1.tx=tx; return;}
if((rx==29)&& (tx==28)){LinkUART1.rx=rx; LinkUART1.tx=tx; return;}}
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART2)
//----UART2 (rx,tx): 5,4; 9,8; 21,20; 25,24; 
if(bus==2){
if((rx==5) && (tx==4)) {LinkUART2.rx=rx; LinkUART2.tx=tx; return;} 
if((rx==9) && (tx==8)) {LinkUART2.rx=rx; LinkUART2.tx=tx; return;} 
if((rx==21)&& (tx==20)){LinkUART2.rx=rx; LinkUART2.tx=tx; return;}
if((rx==25)&& (tx==24)){LinkUART2.rx=rx; LinkUART2.tx=tx; return;}}
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART3)
//----UART3 (rx,tx): other for PIO; 
if(bus==3){LinkUART3.rx=rx; LinkUART3.tx=tx; return;} 
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART4)
//----UART4 (rx,tx): other for PIO; 
if(bus==4){LinkUART4.rx=rx; LinkUART4.tx=tx; return;} 
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART5)
//----UART5 (rx,tx): other for PIO; 
if(bus==5){LinkUART5.rx=rx; LinkUART5.tx=tx; return;} 
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART6)
//----UART6 (rx,tx): other for PIO; 
if(bus==6){LinkUART6.rx=rx; LinkUART6.tx=tx; return;} 
#endif
//-------------------------------------------------------------------------------------------------
uartSetCodeErr(64,bus);if(tx || rx || bus){return;};//--To block warning C++. Exit by no bus RP2040;
#endif
//=================================================================================================
//									2.1.5. STM32
//=================================================================================================
#if defined(RT_HW_CORE_STM32)
//-------------------------------------------------------------------------------------------------
//									2.1.5.1.1.STM32F1C
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_CORE_STM32F1C)
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART0)
if(bus==0){if((rx==PA12)&& (tx==PA11)){LinkUART0.rx=rx; LinkUART0.tx=tx; return;}}
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART1)
if(bus==1){if((rx==PA10)&& (tx==PA9)) {LinkUART1.rx=rx; LinkUART1.tx=tx; return;}}
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART2)
if(bus==2){if((rx==PA3) && (tx==PA2)) {LinkUART2.rx=rx; LinkUART2.tx=tx; return;}}
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART3)
if(bus==3){if((rx==PB11)&& (tx==PB10)){LinkUART3.rx=rx; LinkUART3.tx=tx; return;}}
#endif
//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
//									2.1.1.2.STM32F1R
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_CORE_STM32F1R)
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART0)
if(bus==0){if((rx==PA12)&& (tx==PA11)){LinkUART0.rx=rx; LinkUART0.tx=tx; return;}}
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART1)
if(bus==1){if((rx==PA10)&& (tx==PA9)) {LinkUART1.rx=rx; LinkUART1.tx=tx; return;}}
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART2)
if(bus==2){if((rx==PA3) && (tx==PA2)) {LinkUART2.rx=rx; LinkUART2.tx=tx; return;}}
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART3)
if(bus==3){if((rx==PB11)&& (tx==PB10)){LinkUART3.rx=rx; LinkUART3.tx=tx; return;}}
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART4)
if(bus==4){if((rx==PC11)&& (tx==PC10)){LinkUART4.rx=rx; LinkUART4.tx=tx; return;}}
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART5)
if(bus==5){if((rx==PD2) && (tx==PC12)){LinkUART5.rx=rx; LinkUART5.tx=tx; return;}}
#endif
//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
//									2.1.1.3.STM32F1V
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_CORE_STM32F1V)
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART0)
if(bus==0){if((rx==PA12)&& (tx==PA11)){LinkUART0.rx=rx; LinkUART0.tx=tx; return;}}
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART1)
if(bus==1){if((rx==PA10)&& (tx==PA9)) {LinkUART1.rx=rx; LinkUART1.tx=tx; return;}}
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART2)
if(bus==2){if((rx==PA3) && (tx==PA2)) {LinkUART2.rx=rx; LinkUART2.tx=tx; return;}}
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART3)
if(bus==3){if((rx==PB11)&& (tx==PB10)){LinkUART3.rx=rx; LinkUART3.tx=tx; return;}}
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART4)
if(bus==4){if((rx==PC11)&& (tx==PC10)){LinkUART4.rx=rx; LinkUART4.tx=tx; return;}}
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART5)
if(bus==5){if((rx==PD2) && (tx==PC12)){LinkUART5.rx=rx; LinkUART5.tx=tx; return;}}
#endif
//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
//									2.1.2.1.STM32F4C
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_CORE_STM32F4C)
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART0)
if(bus==0){if((rx==PA12)&& (tx==PA11)){LinkUART0.rx=rx; LinkUART0.tx=tx; return;}}
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART1)
if(bus==1){if((rx==PA10)&& (tx==PA9)) {LinkUART1.rx=rx; LinkUART1.tx=tx; return;}}
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART2)
if(bus==2){if((rx==PA3) && (tx==PA2)) {LinkUART2.rx=rx; LinkUART2.tx=tx; return;}}
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART6)
if(bus==6){if((rx==PA12)&& (tx==PA11)){LinkUART6.rx=rx; LinkUART6.tx=tx; return;}}
#endif
//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
//									2.1.2.3.STM32F4V
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_CORE_STM32F4V)
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART0)
if(bus==0){if((rx==PA12)&& (tx==PA11)){LinkUART0.rx=rx; LinkUART0.tx=tx; return;}}
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART1)
if(bus==1){if((rx==PA10)&& (tx==PA9)) {LinkUART1.rx=rx; LinkUART1.tx=tx; return;}}
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART2)
if(bus==2){if((rx==PA3) && (tx==PA2)) {LinkUART2.rx=rx; LinkUART2.tx=tx; return;}}
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART3)
if(bus==3){if((rx==PD9) && (tx==PD8)) {LinkUART3.rx=rx; LinkUART3.tx=tx; return;}
		   if((rx==PB11)&& (tx==PB10)){LinkUART3.rx=rx; LinkUART3.tx=tx; return;}}
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART4)
if(bus==4){if((rx==PC11)&& (tx==PC10)){LinkUART4.rx=rx; LinkUART4.tx=tx; return;}}
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART5)
if(bus==5){if((rx==PD2) && (tx==PC12)){LinkUART5.rx=rx; LinkUART5.tx=tx; return;}}
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART6)
if(bus==6){if((rx==PC7) && (tx==PC6)) {LinkUART6.rx=rx; LinkUART6.tx=tx; return;}
		   if((rx==PA12)&& (tx==PA11)){LinkUART6.rx=rx; LinkUART6.tx=tx; return;}}
#endif
//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
//									2.1.2.4.STM32FH7V
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_CORE_STM32F4V)
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART0)
if(bus==0){if((rx==PA12)&& (tx==PA11)){LinkUART0.rx=rx; LinkUART0.tx=tx; return;}}
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART1)
if(bus==1){if((rx==PA10)&& (tx==PA9)) {LinkUART1.rx=rx; LinkUART1.tx=tx; return;}}
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART2)
if(bus==2){if((rx==PA3) && (tx==PA2)) {LinkUART2.rx=rx; LinkUART2.tx=tx; return;}}
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART3)
if(bus==3){if((rx==PD9) && (tx==PD8)) {LinkUART3.rx=rx; LinkUART3.tx=tx; return;}
		   if((rx==PB11)&& (tx==PB10)){LinkUART3.rx=rx; LinkUART3.tx=tx; return;}}
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART4)
if(bus==4){if((rx==PC11)&& (tx==PC10)){LinkUART4.rx=rx; LinkUART4.tx=tx; return;}}
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART5)
if(bus==5){if((rx==PD2) && (tx==PC12)){LinkUART5.rx=rx; LinkUART5.tx=tx; return;}}
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART6)
if(bus==6){if((rx==PC7) && (tx==PC6)) {LinkUART6.rx=rx; LinkUART6.tx=tx; return;}
		   if((rx==PA12)&& (tx==PA11)){LinkUART6.rx=rx; LinkUART6.tx=tx; return;}}
#endif
//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
uartSetCodeErr(64,bus);if(tx || rx || bus){return;};//--To block warning C++. Exit by no bus STM32;
#endif
//=================================================================================================
//									2.1.6. No CORE									
//=================================================================================================
uartSetCodeErr(65,bus);if(tx || rx || bus){return;};//--To block warning C++. Exit by no bus STM32;
};
//=================================================================================================
// 		    						2.2.For all UARTx pin number initialization RX,TX
//=================================================================================================
void    uartInitParamAll(){
for(uint8_t i=0; i<=12; i++){uartInitParam(i); uartSetPins(i);}	//--Установка и настройка пинов RX,TX по умолчанию;
uartInitParam(100);
uartInitParam(200);
};
//=================================================================================================
// 		    						2.3.Pin number initialization RX,TX
//=================================================================================================
void    uartInitParam (uint8_t num){
#if defined(RT_HW_PERMIT_UART0)							
if(num==0) {uartSetPinRX(readArrPGM(RT_HW_PGM_PIN_UHS_ID,0),num); //--set pin RX;
            uartSetPinTX(readArrPGM(RT_HW_PGM_PIN_UHS_ID,1),num); //--set pin TX;
			uartSetPinDE(readArrPGM(RT_HW_PGM_PIN_UHS_ID,2),num); //--set pin DE;			
return;}
#endif
//=================================================================================================
#if defined(RT_HW_PERMIT_UART1)							
if(num==1) {uartSetPinRX(readArrPGM(RT_HW_PGM_PIN_UHS_ID,3),num); //--set pin RX;
            uartSetPinTX(readArrPGM(RT_HW_PGM_PIN_UHS_ID,4),num); //--set pin TX;
			uartSetPinDE(readArrPGM(RT_HW_PGM_PIN_UHS_ID,5),1); //--set pin DE;
//--------------------------------------------------------------------------------------------------
// Temporary insert: 
//   FLProg modbus configures Serial1 for ESP32 with invalid pins which causes reboots 
//   when the program starts. We pre-configure the ESP32 with pins for controllers, for which, 
//   according to their description, it is permissible to use UART1.
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_CORE_ESP32) 	
uartBegin(1); 																												
#endif	
return;}
#endif
//=================================================================================================
#if defined(RT_HW_PERMIT_UART2)							
if(num==2) {uartSetPinRX(readArrPGM(RT_HW_PGM_PIN_UHS_ID,6),num); //--set pin RX;
            uartSetPinTX(readArrPGM(RT_HW_PGM_PIN_UHS_ID,7),num); //--set pin TX;
			uartSetPinDE(readArrPGM(RT_HW_PGM_PIN_UHS_ID,8),num); //--set pin DE;			
return;}
#endif
//=================================================================================================
#if defined(RT_HW_PERMIT_UART3)							
if(num==3) {uartSetPinRX(readArrPGM(RT_HW_PGM_PIN_UHS_ID,9), num); //--set pin RX;
            uartSetPinTX(readArrPGM(RT_HW_PGM_PIN_UHS_ID,10),num); //--set pin TX;
			uartSetPinDE(readArrPGM(RT_HW_PGM_PIN_UHS_ID,11),num); //--set pin DE;
return;}
#endif
//=================================================================================================
#if defined(RT_HW_PERMIT_UART4)							
if(num==4) {uartSetPinRX(readArrPGM(RT_HW_PGM_PIN_UHS_ID,12),num); //--set pin RX;
            uartSetPinTX(readArrPGM(RT_HW_PGM_PIN_UHS_ID,13),num); //--set pin TX;
			uartSetPinDE(readArrPGM(RT_HW_PGM_PIN_UHS_ID,14),num); //--set pin DE;
return;}
#endif
//=================================================================================================
#if defined(RT_HW_PERMIT_UART5)							
if(num==5) {uartSetPinRX(readArrPGM(RT_HW_PGM_PIN_UHS_ID,15),num); //--set pin RX;
            uartSetPinTX(readArrPGM(RT_HW_PGM_PIN_UHS_ID,16),num); //--set pin TX;
			uartSetPinDE(readArrPGM(RT_HW_PGM_PIN_UHS_ID,17),num); //--set pin DE;
return;}
#endif
//=================================================================================================
#if defined(RT_HW_PERMIT_UART6)							
if(num==6) {uartSetPinRX(readArrPGM(RT_HW_PGM_PIN_UHS_ID,18),num); //--set pin RX;
            uartSetPinTX(readArrPGM(RT_HW_PGM_PIN_UHS_ID,19),num); //--set pin TX;
			uartSetPinDE(readArrPGM(RT_HW_PGM_PIN_UHS_ID,20),num); //--set pin DE;
return;}
#endif
//=================================================================================================
#if defined(RT_HW_PERMIT_UART7)							
if(num==7) {uartSetPinRX(readArrPGM(RT_HW_PGM_PIN_UHS_ID,21),num); //--set pin RX;
            uartSetPinTX(readArrPGM(RT_HW_PGM_PIN_UHS_ID,22),num); //--set pin TX;
			uartSetPinDE(readArrPGM(RT_HW_PGM_PIN_UHS_ID,23),num); //--set pin DE;
return;}
#endif
//=================================================================================================
#if defined(RT_HW_PERMIT_UART8)							
if(num==8) {uartSetPinRX(readArrPGM(RT_HW_PGM_PIN_UHS_ID,24),num); //--set pin RX;
            uartSetPinTX(readArrPGM(RT_HW_PGM_PIN_UHS_ID,25),num); //--set pin TX;
			uartSetPinDE(readArrPGM(RT_HW_PGM_PIN_UHS_ID,26),num); //--set pin DE;
return;}
#endif
//=================================================================================================
#if defined(RT_HW_PERMIT_UART9)							
if(num==9) {uartSetPinRX(readArrPGM(RT_HW_PGM_PIN_UHS_ID,27),num); //--set pin RX;
            uartSetPinTX(readArrPGM(RT_HW_PGM_PIN_UHS_ID,28),num); //--set pin TX;
			uartSetPinDE(readArrPGM(RT_HW_PGM_PIN_UHS_ID,29),num); //--set pin DE;
return;}
#endif
//=================================================================================================
#if defined(RT_HW_PERMIT_UART10)							
if(num==10){uartSetPinRX(readArrPGM(RT_HW_PGM_PIN_UHS_ID,30),num); //--set pin RX;
            uartSetPinTX(readArrPGM(RT_HW_PGM_PIN_UHS_ID,31),num); //--set pin TX;
			uartSetPinDE(readArrPGM(RT_HW_PGM_PIN_UHS_ID,32),num); //--set pin DE;
return;}
#endif
//=================================================================================================
#if defined(RT_HW_PERMIT_UARTS)
if(num==100){uartSetPinRX(readArrPGM(RT_HW_PGM_PIN_USS_ID,0),num);
             uartSetPinTX(readArrPGM(RT_HW_PGM_PIN_USS_ID,1),num);
			 uartSetPinDE(readArrPGM(RT_HW_PGM_PIN_USS_ID,2),num); //--set pin DE;
return;}						
#endif
//=================================================================================================
#if defined(RT_HW_PERMIT_UARTB)					
if(num==200){return;}
#endif
if(num){return;} //--To block warning C++;
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                          		3.INIT DEVICE
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
// 		    						3.1. Set parameters
//=================================================================================================
void uartSetParam(RT_HW_STRUCT_UART_DEV &id){
if(id.custom==0){id.link=id.status=id.codeErr=0; id.custom=1;}}
//-------------------------------------------------------------------------------------------------
void uartSetParam(RT_HW_STRUCT_UART_DEV &id, uint8_t bus, uint32_t speed=0){
if(id.custom==0){id.link=id.status=id.codeErr=0; id.bus=bus; id.speed=speed; id.custom=1;}}
//=================================================================================================
// 		    						3.1. Init device with bus
//=================================================================================================
void  uartInitDevice(RT_HW_STRUCT_UART_DEV &id){
id.codeErr=id.link=0;
if(id.custom==0){id.codeErr=50; id.link=1; return;} 
if(id.status==1){				id.link=1; return;}
//------------------------------------------------------------------------------------------------
if(!uartCheckNum(id.bus))	 {id.codeErr=52; id.custom=2; return;}	//--Checking bus;
if(id.speed==0){id.speed=RT_HW_UART_SPEED;}				//--Normalisation speed;
uartSetSpeed(id.speed,id.bus);							//--SetSpeed;
//-------------------------------------------------------------------------------------------------
if(!uartBegin(id.bus))		{				              return;} 	//--Initting UART;
if( uartGetStatus(id.bus)!=1){id.codeErr=54; id.custom=4; return;}	//--Checking UART as Master;
//-------------------------------------------------------------------------------------------------
if(id.speed==0){id.speed=RT_HW_UART_SPEED;}				//--Normalisation speed;
id.custom=id.status=id.link=1;							//--Setting output parameters;
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                          		4.Write, Read byte, arr[]
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
;	

//=================================================================================================
// 		    						4.1. Write byte
//=================================================================================================
uint8_t uartWrite(RT_HW_STRUCT_UART_DEV &id, uint8_t var){
id.link=0;
//-------------------------------------------------------------------------------------------------
if(id.status!=1) {id.link=1; return 1;}	//--Exit if i2c is not Master;
//if(uartAvailableForWrite(id.bus)==0){    return;}
//if(uartSetBusy  (id.bus)==0) {           return;};//--Uart bus capture;
//-------------------------------------------------------------------------------------------------
id.codeErr=uartWrite(var,id.bus); 						//--Write byte;
if(id.codeErr==0){id.link=0;} else {id.link=1;}
//-------------------------------------------------------------------------------------------------
//i2cClearBusy(id.bus); 							//--i2c bus   release;	
//-------------------------------------------------------------------------------------------------
return id.link;};
//=================================================================================================
// 		    						4.1. Write byte
//=================================================================================================
void uartWriteArr(RT_HW_STRUCT_UART_DEV &id, uint8_t *arr, uint8_t qnt){
id.link=0;
//-------------------------------------------------------------------------------------------------
if(uartGetStatus(id.bus)!=1) {id.link=1; return;}	//--Exit if i2c is not Master;
if(uartAvailableForWrite(id.bus)<qnt){   return;}
//if(uartSetBusy  (id.bus)==0) {           return;};//--Uart bus capture;
//-------------------------------------------------------------------------------------------------
for(id.idx=0; id.idx<qnt; id.idx++){uartWrite(arr[id.idx],id.bus);} //--Write qnt bytes;
//-------------------------------------------------------------------------------------------------
//i2cClearBusy(id.bus); 							//--i2c bus   release;	
//-------------------------------------------------------------------------------------------------
id.link=1;};
//#################################################################################################
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//									10.API.ccp 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	
uint8_t  uartBegin  (uint8_t num=0);			//--UART initialization;		
void     uartEnd    (uint8_t num=0);			//--UART end;	
bool     uartSerial (uint8_t num=0);			//--UART readiness check;
uint16_t uartAvailable(uint8_t num=0);			//--Checking the input buffer;	
uint16_t uartAvailableForWrite(uint8_t num=0);	//--Checking the output buffer;
uint8_t  uartRead(uint8_t n);					//--Reading a byte from the input buffer;
uint8_t  uartWrite(uint8_t var, uint8_t bus);	//--Write a byte to the output buffer;
void     uartPrint(String str,  uint8_t bus);	//--String output (stub for RP2040);
//=================================================================================================
// 										10.1.Check UART flags
// 							[begin,ready flags set by uartBegin functions]
//=================================================================================================
bool     uartCheckNum  (uint8_t num=0){
#if defined(RT_HW_PERMIT_UART0)
if(num==0){return 1;}
#endif
#if defined(RT_HW_PERMIT_UART1)
if(num==1){return 1;}
#endif
#if defined(RT_HW_PERMIT_UART2)
if(num==2){return 1;}
#endif
#if defined(RT_HW_PERMIT_UART3)
if(num==3){return 1;}
#endif
#if defined(RT_HW_PERMIT_UART4)
if(num==4){return 1;}
#endif
#if defined(RT_HW_PERMIT_UART5)
if(num==5){return 1;}
#endif
#if defined(RT_HW_PERMIT_UART6)
if(num==6){return 1;}
#endif
#if defined(RT_HW_PERMIT_UART7)
if(num==7){return 1;}
#endif
#if defined(RT_HW_PERMIT_UART8)
if(num==8){return 1;}
#endif
#if defined(RT_HW_PERMIT_UART9)
if(num==9){return 1;}
#endif
#if defined(RT_HW_PERMIT_UART10)
if(num==10){return 1;}
#endif
//---------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UARTS)
if(num==100){return 1;}
#endif
#if defined(RT_HW_PERMIT_UARTB)
if(num==200){return 1;}
#endif
return 0;};
bool     uartCheckBegin(uint8_t num=0){
if(num==100){return bitRead(uart.begin,14);}
if(num==200){return bitRead(uart.begin,15);}										
if(num>=16) {return 0;}
	         return bitRead(uart.begin,num);
};
bool     uartCheckReady(uint8_t num=0){
if(num==100) return bitRead(uart.ready,14);
if(num==200) return bitRead(uart.ready,15);										
if(num>=16) {return 0;}
             return bitRead(uart.ready,num);
};	
bool     uartCheckBusy (uint8_t num=0){
if(num==100) return bitRead(uart.busy,14);
if(num==200) return bitRead(uart.busy,15);										
if(num>=16) {return 1;} 
			 return bitRead(uart.busy,num);
};	
uint16_t uartGetBegin(){
return uart.begin;}
uint16_t uartGetReady(){
return uart.ready;}	
uint16_t uartGetBusy() {
return  uart.busy;}	
char     uartGetParityChar(uint8_t num=0){
	if(uartGetParity(num)==0){return 'N';}
	if(uartGetParity(num)==1){return 'E';}	
	if(uartGetParity(num)==2){return 'O';}	
return 'X';};
//=================================================================================================
// 											10.2.Set UART flags
// 							[begin,ready flags set by uartBegin functions]					
//=================================================================================================
void     uartSetBegin(uint8_t num=0){
if(num==100){bitSet(uart.begin,14);}
if(num==200){bitSet(uart.begin,15);}										
if(num>=16) {return;}
	         bitSet(uart.begin,num);
};
void     uartSetReady(uint8_t num=0){
if(num==100){bitSet(uart.ready,14);}
if(num==200){bitSet(uart.ready,15);}										
if(num>=16) {return;}
	         bitSet(uart.ready,num);
};	
void     uartSetBusy (uint8_t num=0){
if(num==100){bitSet(uart.busy,14);}
if(num==200){bitSet(uart.busy,15);}										
if(num>=16) {return;}
	         bitSet(uart.busy,num);
};	
//=================================================================================================
// 											10.3.Clear UART flag busy			
//=================================================================================================	
void     uartClearBusy (uint8_t num=0){
if(num==100){bitClear(uart.busy,14);}
if(num==200){bitClear(uart.busy,15);}										
if(num>=16) {return;}
	         bitClear(uart.busy,num);
};
//=================================================================================================
// 											10.4.Setting status UART
//=================================================================================================
void     uartSetStatus (uint8_t status,   uint8_t num=0){
#if defined(RT_HW_PERMIT_UART0)	
if(num==0) {LinkUART0.status=status;}
#endif
#if defined(RT_HW_PERMIT_UART1)	
if(num==1) {LinkUART1.status=status;}
#endif
#if defined(RT_HW_PERMIT_UART2)	
if(num==2) {LinkUART2.status=status;}
#endif
#if defined(RT_HW_PERMIT_UART3)	
if(num==3) {LinkUART3.status=status;}
#endif
#if defined(RT_HW_PERMIT_UART4)	
if(num==4) {LinkUART4.status=status;}
#endif
#if defined(RT_HW_PERMIT_UART5)	
if(num==5) {LinkUART5.status=status;}
#endif
#if defined(RT_HW_PERMIT_UART6)	
if(num==6) {LinkUART6.status=status;}
#endif
#if defined(RT_HW_PERMIT_UART7)	
if(num==7) {LinkUART7.status=status;}
#endif
#if defined(RT_HW_PERMIT_UART8)	
if(num==8) {LinkUART8.status=status;}
#endif
#if defined(RT_HW_PERMIT_UART9)	
if(num==9) {LinkUART9.status=status;}
#endif
#if defined(RT_HW_PERMIT_UART10)	
if(num==10) {LinkUART10.status=status;}
#endif
//---------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UARTS)	
if(num==100) {LinkUARTS.status=status;}
#endif
#if defined(RT_HW_PERMIT_UARTB)	
if(num==200) {LinkUARTB.status=status;}
#endif
};
//=================================================================================================
// 											10.5.Getting status UART
//=================================================================================================
uint8_t  uartGetStatus (uint8_t num=0){
#if defined(RT_HW_PERMIT_UART0)	
if(num==0) {return LinkUART0.status;}
#endif
#if defined(RT_HW_PERMIT_UART1)	
if(num==1) {return LinkUART1.status;}
#endif
#if defined(RT_HW_PERMIT_UART2)	
if(num==2) {return LinkUART2.status;}
#endif
#if defined(RT_HW_PERMIT_UART3)	
if(num==3) {return LinkUART3.status;}
#endif
#if defined(RT_HW_PERMIT_UART4)	
if(num==4) {return LinkUART4.status;}
#endif
#if defined(RT_HW_PERMIT_UART5)	
if(num==5) {return LinkUART5.status;}
#endif
#if defined(RT_HW_PERMIT_UART6)	
if(num==6) {return LinkUART6.status;}
#endif
#if defined(RT_HW_PERMIT_UART7)	
if(num==7) {return LinkUART7.status;}
#endif
#if defined(RT_HW_PERMIT_UART8)	
if(num==8) {return LinkUART8.status;}
#endif
#if defined(RT_HW_PERMIT_UART9)	
if(num==9) {return LinkUART9.status;}
#endif
#if defined(RT_HW_PERMIT_UART10)	
if(num==10){return LinkUART10.status;}
#endif
//---------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UARTS)	
if(num==100){return LinkUARTS.status;}
#endif
#if defined(RT_HW_PERMIT_UARTB)	
if(num==200){return LinkUARTB.status;}
#endif
return 0;};


//=================================================================================================
// 											10.6.1.Setting config UART
//=================================================================================================
void     uartSetConfig(uint32_t config, uint8_t num=0){
#if defined(RT_HW_PERMIT_UART0)	
if(num==0) {LinkUART0.config=config;}
#endif
#if defined(RT_HW_PERMIT_UART1)	
if(num==1) {LinkUART1.config=config;}
#endif
#if defined(RT_HW_PERMIT_UART2)	
if(num==2) {LinkUART2.config=config;}
#endif
#if defined(RT_HW_PERMIT_UART3)	
if(num==3) {LinkUART3.config=config;}
#endif
#if defined(RT_HW_PERMIT_UART4)	
if(num==4) {LinkUART4.config=config;}
#endif
#if defined(RT_HW_PERMIT_UART5)	
if(num==5) {LinkUART5.config=config;}
#endif
#if defined(RT_HW_PERMIT_UART6)	
if(num==6) {LinkUART6.config=config;}
#endif
#if defined(RT_HW_PERMIT_UART7)	
if(num==7) {LinkUART7.config=config;}
#endif
#if defined(RT_HW_PERMIT_UART8)	
if(num==8) {LinkUART8.config=config;}
#endif
#if defined(RT_HW_PERMIT_UART9)	
if(num==9) {LinkUART9.config=config;}
#endif
#if defined(RT_HW_PERMIT_UART10)	
if(num==10) {LinkUART10.config=config;}
#endif
//---------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UARTS)	
if(num==100) {LinkUARTS.config=config;}
#endif
#if defined(RT_HW_PERMIT_UARTB)	
#endif
};
//=================================================================================================
// 											10.6.2.Setting dataBit
//=================================================================================================
void     uartSetDataBit(uint8_t vr, uint8_t num=0){
(void)vr;
if((vr!=5) && (vr!=6) && (vr!=7)  && (vr!=6)){vr=8;}	//--Нормализация кол-ва разрядов; 
#if defined(RT_HW_PERMIT_UART0)	
if(num==0) {LinkUART0.dataBit=vr;}
#endif
#if defined(RT_HW_PERMIT_UART1)	
if(num==1) {LinkUART1.dataBit=vr;}
#endif
#if defined(RT_HW_PERMIT_UART2)	
if(num==2) {LinkUART2.dataBit=vr;}
#endif
#if defined(RT_HW_PERMIT_UART3)	
if(num==3) {LinkUART3.dataBit=vr;}
#endif
#if defined(RT_HW_PERMIT_UART4)	
if(num==4) {LinkUART4.dataBit=vr;}
#endif
#if defined(RT_HW_PERMIT_UART5)	
if(num==5) {LinkUART5.dataBit=vr;}
#endif
#if defined(RT_HW_PERMIT_UART6)	
if(num==6) {LinkUART6.dataBit=vr;}
#endif
#if defined(RT_HW_PERMIT_UART7)	
if(num==7) {LinkUART7.dataBit=vr;}
#endif
#if defined(RT_HW_PERMIT_UART8)	
if(num==8) {LinkUART8.dataBit=vr;}
#endif
#if defined(RT_HW_PERMIT_UART9)	
if(num==9) {LinkUART9.dataBit=vr;}
#endif
#if defined(RT_HW_PERMIT_UART10)	
if(num==10) {LinkUART10.dataBit=vr;}
#endif
//---------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UARTS)	
if(num==100) {LinkUARTS.dataBit=vr;}
#endif
#if defined(RT_HW_PERMIT_UARTB)	
#endif
};
//=================================================================================================
// 											10.6.3.Setting stopBit
//=================================================================================================
void     uartSetStopBit(uint8_t vr, uint8_t num=0){
(void)vr;
if((vr!=1) && (vr!=2)){vr=2;}	//--Нормализация кол-ва стоповых битов; 
#if defined(RT_HW_PERMIT_UART0)	
if(num==0) {LinkUART0.stopBit=vr;}
#endif
#if defined(RT_HW_PERMIT_UART1)	
if(num==1) {LinkUART1.stopBit=vr;}
#endif
#if defined(RT_HW_PERMIT_UART2)	
if(num==2) {LinkUART2.stopBit=vr;}
#endif
#if defined(RT_HW_PERMIT_UART3)	
if(num==3) {LinkUART3.stopBit=vr;}
#endif
#if defined(RT_HW_PERMIT_UART4)	
if(num==4) {LinkUART4.stopBit=vr;}
#endif
#if defined(RT_HW_PERMIT_UART5)	
if(num==5) {LinkUART5.stopBit=vr;}
#endif
#if defined(RT_HW_PERMIT_UART6)	
if(num==6) {LinkUART6.stopBit=vr;}
#endif
#if defined(RT_HW_PERMIT_UART7)	
if(num==7) {LinkUART7.stopBit=vr;}
#endif
#if defined(RT_HW_PERMIT_UART8)	
if(num==8) {LinkUART8.stopBit=vr;}
#endif
#if defined(RT_HW_PERMIT_UART9)	
if(num==9) {LinkUART9.stopBit=vr;}
#endif
#if defined(RT_HW_PERMIT_UART10)	
if(num==10) {LinkUART10.stopBit=vr;}
#endif
//---------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UARTS)	
if(num==100) {LinkUARTS.stopBit=vr;}
#endif
#if defined(RT_HW_PERMIT_UARTB)	
#endif
};
//=================================================================================================
// 											10.6.3.Setting stopBit
//=================================================================================================
void     uartSetParity (uint8_t vr, uint8_t num=0){
(void)vr; (void)num;
if((vr!=1) && (vr!=2)){vr=2;}			//--Нормализация кол-ва стоповых битов; 
#if defined(RT_HW_PERMIT_UART0)	
if(num==0) {LinkUART0.parity=vr;}
#endif
#if defined(RT_HW_PERMIT_UART1)	
if(num==1) {LinkUART1.parity=vr;}
#endif
#if defined(RT_HW_PERMIT_UART2)	
if(num==2) {LinkUART2.parity=vr;}
#endif
#if defined(RT_HW_PERMIT_UART3)	
if(num==3) {LinkUART3.parity=vr;}
#endif
#if defined(RT_HW_PERMIT_UART4)	
if(num==4) {LinkUART4.parity=vr;}
#endif
#if defined(RT_HW_PERMIT_UART5)	
if(num==5) {LinkUART5.parity=vr;}
#endif
#if defined(RT_HW_PERMIT_UART6)	
if(num==6) {LinkUART6.parity=vr;}
#endif
#if defined(RT_HW_PERMIT_UART7)	
if(num==7) {LinkUART7.parity=vr;}
#endif
#if defined(RT_HW_PERMIT_UART8)	
if(num==8) {LinkUART8.parity=vr;}
#endif
#if defined(RT_HW_PERMIT_UART9)	
if(num==9) {LinkUART9.parity=vr;}
#endif
#if defined(RT_HW_PERMIT_UART10)	
if(num==10){LinkUART10.parity=vr;}
#endif
//---------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UARTS)	
if(num==100){LinkUARTS.parity=vr;}
#endif
#if defined(RT_HW_PERMIT_UARTB)	
#endif
};
//=================================================================================================
// 											1.7.1.Getting config UART
//=================================================================================================
uint32_t uartGetConfig(uint8_t num=0){	
(void)num;
#if defined(RT_HW_PERMIT_UART0)	
if(num==0) {return LinkUART0.config;}
#endif
#if defined(RT_HW_PERMIT_UART1)	
if(num==1) {return LinkUART1.config;}
#endif
#if defined(RT_HW_PERMIT_UART2)	
if(num==2) {return LinkUART2.config;}
#endif
#if defined(RT_HW_PERMIT_UART3)	
if(num==3) {return LinkUART3.config;}
#endif
#if defined(RT_HW_PERMIT_UART4)	
if(num==4) {return LinkUART4.config;}
#endif
#if defined(RT_HW_PERMIT_UART5)	
if(num==5) {return LinkUART5.config;}
#endif
#if defined(RT_HW_PERMIT_UART6)	
if(num==6) {return LinkUART6.config;}
#endif
#if defined(RT_HW_PERMIT_UART7)	
if(num==7) {return LinkUART7.config;}
#endif
#if defined(RT_HW_PERMIT_UART8)	
if(num==8) {return LinkUART8.config;}
#endif
#if defined(RT_HW_PERMIT_UART9)	
if(num==9) {return LinkUART9.config;}
#endif
#if defined(RT_HW_PERMIT_UART10)	
if(num==10){return LinkUART10.config;}
#endif
//---------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UARTS)	
if(num==100) {return LinkUARTS.config;}
#endif
#if defined(RT_HW_PERMIT_UARTB)	
if(num==200) {return 0x800001C;}
#endif
return 0x800001C;};
//=================================================================================================
// 											1.7.2.Getting dataBit UART
//=================================================================================================
uint8_t uartGetDataBit(uint8_t num=0){	
(void)num;
#if defined(RT_HW_PERMIT_UART0)	
if(num==0) {return LinkUART0.dataBit;}
#endif
#if defined(RT_HW_PERMIT_UART1)	
if(num==1) {return LinkUART1.dataBit;}
#endif
#if defined(RT_HW_PERMIT_UART2)	
if(num==2) {return LinkUART2.dataBit;}
#endif
#if defined(RT_HW_PERMIT_UART3)	
if(num==3) {return LinkUART3.dataBit;}
#endif
#if defined(RT_HW_PERMIT_UART4)	
if(num==4) {return LinkUART4.dataBit;}
#endif
#if defined(RT_HW_PERMIT_UART5)	
if(num==5) {return LinkUART5.dataBit;}
#endif
#if defined(RT_HW_PERMIT_UART6)	
if(num==6) {return LinkUART6.dataBit;}
#endif
#if defined(RT_HW_PERMIT_UART7)	
if(num==7) {return LinkUART7.dataBit;}
#endif
#if defined(RT_HW_PERMIT_UART8)	
if(num==8) {return LinkUART8.dataBit;}
#endif
#if defined(RT_HW_PERMIT_UART9)	
if(num==9) {return LinkUART9.dataBit;}
#endif
#if defined(RT_HW_PERMIT_UART10)	
if(num==10){return LinkUART10.dataBit;}
#endif
//---------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UARTS)	
if(num==100) {return LinkUARTS.dataBit;}
#endif
#if defined(RT_HW_PERMIT_UARTB)	
if(num==200) {return 8;}
#endif
return 8;};
//=================================================================================================
// 											1.7.3.Getting parity UART
//=================================================================================================
uint8_t uartGetParity(uint8_t num=0){	
(void)num;
#if defined(RT_HW_PERMIT_UART0)	
if(num==0) {return LinkUART0.parity;}
#endif
#if defined(RT_HW_PERMIT_UART1)	
if(num==1) {return LinkUART1.parity;}
#endif
#if defined(RT_HW_PERMIT_UART2)	
if(num==2) {return LinkUART2.parity;}
#endif
#if defined(RT_HW_PERMIT_UART3)	
if(num==3) {return LinkUART3.parity;}
#endif
#if defined(RT_HW_PERMIT_UART4)	
if(num==4) {return LinkUART4.parity;}
#endif
#if defined(RT_HW_PERMIT_UART5)	
if(num==5) {return LinkUART5.parity;}
#endif
#if defined(RT_HW_PERMIT_UART6)	
if(num==6) {return LinkUART6.parity;}
#endif
#if defined(RT_HW_PERMIT_UART7)	
if(num==7) {return LinkUART7.parity;}
#endif
#if defined(RT_HW_PERMIT_UART8)	
if(num==8) {return LinkUART8.parity;}
#endif
#if defined(RT_HW_PERMIT_UART9)	
if(num==9) {return LinkUART9.parity;}
#endif
#if defined(RT_HW_PERMIT_UART10)	
if(num==10){return LinkUART10.parity;}
#endif
//---------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UARTS)	
if(num==100) {return LinkUARTS.parity;}
#endif
#if defined(RT_HW_PERMIT_UARTB)	
if(num==200) {return 0;}
#endif
return 8;};
//=================================================================================================
// 											1.7.3.Getting stopBt UART
//=================================================================================================
uint8_t uartGetStopBit(uint8_t num=0){	
(void)num;
#if defined(RT_HW_PERMIT_UART0)	
if(num==0) {return LinkUART0.stopBit;}
#endif
#if defined(RT_HW_PERMIT_UART1)	
if(num==1) {return LinkUART1.stopBit;}
#endif
#if defined(RT_HW_PERMIT_UART2)	
if(num==2) {return LinkUART2.stopBit;}
#endif
#if defined(RT_HW_PERMIT_UART3)	
if(num==3) {return LinkUART3.stopBit;}
#endif
#if defined(RT_HW_PERMIT_UART4)	
if(num==4) {return LinkUART4.stopBit;}
#endif
#if defined(RT_HW_PERMIT_UART5)	
if(num==5) {return LinkUART5.stopBit;}
#endif
#if defined(RT_HW_PERMIT_UART6)	
if(num==6) {return LinkUART6.stopBit;}
#endif
#if defined(RT_HW_PERMIT_UART7)	
if(num==7) {return LinkUART7.stopBit;}
#endif
#if defined(RT_HW_PERMIT_UART8)	
if(num==8) {return LinkUART8.stopBit;}
#endif
#if defined(RT_HW_PERMIT_UART9)	
if(num==9) {return LinkUART9.stopBit;}
#endif
#if defined(RT_HW_PERMIT_UART10)	
if(num==10){return LinkUART10.stopBit;}
#endif
//---------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UARTS)	
if(num==100) {return LinkUARTS.stopBit;}
#endif
#if defined(RT_HW_PERMIT_UARTB)	
if(num==200) {return 1;}
#endif
return 1;};



//=================================================================================================
// 		    								1.8.Writting the name BlueTooth
//=================================================================================================
void     uartSetNameBTH(String name){
#if defined(RT_HW_PERMIT_UARTB)		
LinkUARTB.name=name; return;			
#endif		
name=" ";};
//=================================================================================================
// 		    								1.9.Reading the name BlueTooth
//=================================================================================================
String   uartGetNameBTH(){
#if defined(RT_HW_PERMIT_UARTB)		
return LinkUARTB.name;			
#endif		 
return String(F("No UARTB"));}
//=================================================================================================
// 											1.10.Set speed UART
//=================================================================================================
void     uartSetSpeed (uint32_t speed,  uint8_t num=0){
(void)speed; (void)num;
#if defined(RT_HW_PERMIT_UART0)	
if(num==0) {LinkUART0.speed=speed;}
#endif
#if defined(RT_HW_PERMIT_UART1)	
if(num==1) {LinkUART1.speed=speed;}
#endif
#if defined(RT_HW_PERMIT_UART2)	
if(num==2) {LinkUART2.speed=speed;}
#endif
#if defined(RT_HW_PERMIT_UART3)	
if(num==3) {LinkUART3.speed=speed;}
#endif
#if defined(RT_HW_PERMIT_UART4)	
if(num==4) {LinkUART4.speed=speed;}
#endif
#if defined(RT_HW_PERMIT_UART5)	
if(num==5) {LinkUART5.speed=speed;}
#endif
#if defined(RT_HW_PERMIT_UART6)	
if(num==6) {LinkUART6.speed=speed;}
#endif
#if defined(RT_HW_PERMIT_UART7)	
if(num==7) {LinkUART7.speed=speed;}
#endif
#if defined(RT_HW_PERMIT_UART8)	
if(num==8) {LinkUART8.speed=speed;}
#endif
#if defined(RT_HW_PERMIT_UART9)	
if(num==9) {LinkUART9.speed=speed;}
#endif
#if defined(RT_HW_PERMIT_UART10)	
if(num==10){LinkUART10.speed=speed;}
#endif
//---------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UARTS)	
if(num==100) {LinkUARTS.speed=speed;}
#endif
#if defined(RT_HW_PERMIT_UARTB)	
if(num==200) {LinkUARTB.speed=speed;}
#endif
if(num || speed){return;}; //--To block warning C++;
};
//=================================================================================================
// 											1.11.Read speed UART
//=================================================================================================
uint32_t uartGetSpeed (uint8_t num=0){
(void)num;
#if defined(RT_HW_PERMIT_UART0)	
if(num==0) {return LinkUART0.speed;}
#endif
#if defined(RT_HW_PERMIT_UART1)	
if(num==1) {return LinkUART1.speed;}
#endif
#if defined(RT_HW_PERMIT_UART2)	
if(num==2) {return LinkUART2.speed;}
#endif
#if defined(RT_HW_PERMIT_UART3)	
if(num==3) {return LinkUART3.speed;}
#endif
#if defined(RT_HW_PERMIT_UART4)	
if(num==4) {return LinkUART4.speed;}
#endif
#if defined(RT_HW_PERMIT_UART5)	
if(num==5) {return LinkUART5.speed;}
#endif
#if defined(RT_HW_PERMIT_UART6)	
if(num==6) {return LinkUART6.speed;}
#endif
#if defined(RT_HW_PERMIT_UART7)	
if(num==7) {return LinkUART7.speed;}
#endif
#if defined(RT_HW_PERMIT_UART8)	
if(num==8) {return LinkUART8.speed;}
#endif
#if defined(RT_HW_PERMIT_UART9)	
if(num==9) {return LinkUART9.speed;}
#endif
#if defined(RT_HW_PERMIT_UART10)	
if(num==10) {return LinkUART10.speed;}
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UARTS)	
if(num==100) {return LinkUARTS.speed;}
#endif
#if defined(RT_HW_PERMIT_UARTB)	
if(num==200) {return (uint32_t)115200;}
#endif
if(num){return (uint32_t)115200;}; //--To block warning C++;
        return (uint32_t)115200;};
//=================================================================================================
// 											1.12.Set pin RX
//=================================================================================================
void     uartSetPinRX(uint8_t rx, uint8_t num=0){
(void)rx; (void)num;
#if defined(RT_HW_PERMIT_UART0)	
if(num==0) {LinkUART0.rx=rx;}
#endif
#if defined(RT_HW_PERMIT_UART1)	
if(num==1) {LinkUART1.rx=rx;}
#endif
#if defined(RT_HW_PERMIT_UART2)	
if(num==2) {LinkUART2.rx=rx;}
#endif
#if defined(RT_HW_PERMIT_UART3)	
if(num==3) {LinkUART3.rx=rx;}
#endif
#if defined(RT_HW_PERMIT_UART4)	
if(num==4) {LinkUART4.rx=rx;}
#endif
#if defined(RT_HW_PERMIT_UART5)	
if(num==5) {LinkUART5.rx=rx;}
#endif
#if defined(RT_HW_PERMIT_UART6)	
if(num==6) {LinkUART6.rx=rx;}
#endif
#if defined(RT_HW_PERMIT_UART7)	
if(num==7) {LinkUART7.rx=rx;}
#endif
#if defined(RT_HW_PERMIT_UART8)	
if(num==8) {LinkUART8.rx=rx;}
#endif
#if defined(RT_HW_PERMIT_UART9)	
if(num==9) {LinkUART9.rx=rx;}
#endif
#if defined(RT_HW_PERMIT_UART10)	
if(num==10) {LinkUART10.rx=rx;}
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UARTS)	
if(num==100) {LinkUARTS.rx=rx;}
#endif
#if defined(RT_HW_PERMIT_UARTB)	
#endif
};
//=================================================================================================
// 											1.13.Set pin TX 
//=================================================================================================
void     uartSetPinTX(uint8_t tx, uint8_t num=0){
#if defined(RT_HW_PERMIT_UART0)	
if(num==0) {LinkUART0.tx=tx;}
#endif
#if defined(RT_HW_PERMIT_UART1)	
if(num==1) {LinkUART1.tx=tx;}
#endif
#if defined(RT_HW_PERMIT_UART2)	
if(num==2) {LinkUART2.tx=tx;}
#endif
#if defined(RT_HW_PERMIT_UART3)	
if(num==3) {LinkUART3.tx=tx;}
#endif
#if defined(RT_HW_PERMIT_UART4)	
if(num==4) {LinkUART4.tx=tx;}
#endif
#if defined(RT_HW_PERMIT_UART5)	
if(num==5) {LinkUART5.tx=tx;}
#endif
#if defined(RT_HW_PERMIT_UART6)	
if(num==6) {LinkUART6.tx=tx;}
#endif
#if defined(RT_HW_PERMIT_UART7)	
if(num==7) {LinkUART7.tx=tx;}
#endif
#if defined(RT_HW_PERMIT_UART8)	
if(num==8) {LinkUART8.tx=tx;}
#endif
#if defined(RT_HW_PERMIT_UART9)	
if(num==9) {LinkUART9.tx=tx;}
#endif
#if defined(RT_HW_PERMIT_UART10)	
if(num==10) {LinkUART10.tx=tx;}
#endif
//---------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UARTS)	
if(num==100) {LinkUARTS.tx=tx;}
#endif
#if defined(RT_HW_PERMIT_UARTB)	
#endif
if(num || tx){return;}; //--To block warning C++;
};
//=================================================================================================
// 											1.14.Set pin DE 
//=================================================================================================
void     uartSetPinDE(uint8_t de, uint8_t num=0){
#if defined(RT_HW_PERMIT_UART0)	
if(num==0) {LinkUART0.de=de;}
#endif
#if defined(RT_HW_PERMIT_UART1)	
if(num==1) {LinkUART1.de=de;}
#endif
#if defined(RT_HW_PERMIT_UART2)	
if(num==2) {LinkUART2.de=de;}
#endif
#if defined(RT_HW_PERMIT_UART3)	
if(num==3) {LinkUART3.de=de;}
#endif
#if defined(RT_HW_PERMIT_UART4)	
if(num==4) {LinkUART4.de=de;}
#endif
#if defined(RT_HW_PERMIT_UART5)	
if(num==5) {LinkUART5.de=de;}
#endif
#if defined(RT_HW_PERMIT_UART6)	
if(num==6) {LinkUART6.de=de;}
#endif
#if defined(RT_HW_PERMIT_UART7)	
if(num==7) {LinkUART7.de=de;}
#endif
#if defined(RT_HW_PERMIT_UART8)	
if(num==8) {LinkUART8.de=de;}
#endif
#if defined(RT_HW_PERMIT_UART9)	
if(num==9) {LinkUART9.de=de;}
#endif
#if defined(RT_HW_PERMIT_UART10)	
if(num==10) {LinkUART10.de=de;}
#endif
//---------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UARTS)	
if(num==100) {LinkUARTS.de=de;}
#endif
#if defined(RT_HW_PERMIT_UARTB)	
#endif
if(num || de){return;}; //--To block warning C++;
};
//=================================================================================================
// 											1.15.Get pin RX 
//=================================================================================================
uint8_t  uartGetPinRX(uint8_t num=0){
#if defined(RT_HW_PERMIT_UART0)	
if(num==0) {return LinkUART0.rx;}
#endif
#if defined(RT_HW_PERMIT_UART1)	
if(num==1) {return LinkUART1.rx;}
#endif
#if defined(RT_HW_PERMIT_UART2)	
if(num==2) {return LinkUART2.rx;}
#endif
#if defined(RT_HW_PERMIT_UART3)	
if(num==3) {return LinkUART3.rx;}
#endif
#if defined(RT_HW_PERMIT_UART4)	
if(num==4) {return LinkUART4.rx;}
#endif
#if defined(RT_HW_PERMIT_UART5)	
if(num==5) {return LinkUART5.rx;}
#endif
#if defined(RT_HW_PERMIT_UART6)	
if(num==6) {return LinkUART6.rx;}
#endif
#if defined(RT_HW_PERMIT_UART7)	
if(num==7) {return LinkUART7.rx;}
#endif
#if defined(RT_HW_PERMIT_UART8)	
if(num==8) {return LinkUART8.rx;}
#endif
#if defined(RT_HW_PERMIT_UART9)	
if(num==9) {return LinkUART9.rx;}
#endif
#if defined(RT_HW_PERMIT_UART10)	
if(num==10) {return LinkUART10.rx;}
#endif
//---------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UARTS)	
if(num==100){return LinkUARTS.rx;}
#endif
#if defined(RT_HW_PERMIT_UARTB)	
#endif
if(num){return 255;}; //--To block warning C++;
return 255;};
//=================================================================================================
// 											1.16.Get pin TX 
//=================================================================================================
uint8_t  uartGetPinTX(uint8_t num=0){
#if defined(RT_HW_PERMIT_UART0)	
if(num==0) {return LinkUART0.tx;}
#endif
#if defined(RT_HW_PERMIT_UART1)	
if(num==1) {return LinkUART1.tx;}
#endif
#if defined(RT_HW_PERMIT_UART2)	
if(num==2) {return LinkUART2.tx;}
#endif
#if defined(RT_HW_PERMIT_UART3)	
if(num==3) {return LinkUART3.tx;}
#endif
#if defined(RT_HW_PERMIT_UART4)	
if(num==4) {return LinkUART4.tx;}
#endif
#if defined(RT_HW_PERMIT_UART5)	
if(num==5) {return LinkUART5.tx;}
#endif
#if defined(RT_HW_PERMIT_UART6)	
if(num==6) {return LinkUART6.tx;}
#endif
#if defined(RT_HW_PERMIT_UART7)	
if(num==7) {return LinkUART7.tx;}
#endif
#if defined(RT_HW_PERMIT_UART8)	
if(num==8) {return LinkUART8.tx;}
#endif
#if defined(RT_HW_PERMIT_UART9)	
if(num==9) {return LinkUART9.tx;}
#endif
#if defined(RT_HW_PERMIT_UART10)	
if(num==10) {return LinkUART10.tx;}
#endif
//---------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UARTS)	
if(num==100){return LinkUARTS.tx;}
#endif
#if defined(RT_HW_PERMIT_UARTB)	
#endif
if(num){return 255;}; //--To block warning C++;
return 255;};
//=================================================================================================
// 											1.14.Get pin DE 
//=================================================================================================
uint8_t  uartGetPinDE(uint8_t num=0){
#if defined(RT_HW_PERMIT_UART0)	
if(num==0) {return LinkUART0.de;}
#endif
#if defined(RT_HW_PERMIT_UART1)	
if(num==1) {return LinkUART1.de;}
#endif
#if defined(RT_HW_PERMIT_UART2)	
if(num==2) {return LinkUART2.de;}
#endif
#if defined(RT_HW_PERMIT_UART3)	
if(num==3) {return LinkUART3.de;}
#endif
#if defined(RT_HW_PERMIT_UART4)	
if(num==4) {return LinkUART4.de;}
#endif
#if defined(RT_HW_PERMIT_UART5)	
if(num==5) {return LinkUART5.de;}
#endif
#if defined(RT_HW_PERMIT_UART6)	
if(num==6) {return LinkUART6.de;}
#endif
#if defined(RT_HW_PERMIT_UART7)	
if(num==7) {return LinkUART7.de;}
#endif
#if defined(RT_HW_PERMIT_UART8)	
if(num==8) {return LinkUART8.de;}
#endif
#if defined(RT_HW_PERMIT_UART9)	
if(num==9) {return LinkUART9.de;}
#endif
#if defined(RT_HW_PERMIT_UART10)	
if(num==10) {return LinkUART10.de;}
#endif
//---------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UARTS)	
if(num==100) {return LinkUARTS.de;}
#endif
#if defined(RT_HW_PERMIT_UARTB)	
#endif
if(num){return 255;}; //--To block warning C++;
return 255;};

//=================================================================================================
// 											1.15.Set code error
//=================================================================================================
void     uartSetCodeErr (uint8_t codeErr,  uint8_t num=0){
#if defined(RT_HW_PERMIT_UART0)	
if(num==0) {LinkUART0.codeErr=codeErr;}
#endif
#if defined(RT_HW_PERMIT_UART1)	
if(num==1) {LinkUART1.codeErr=codeErr;}
#endif
#if defined(RT_HW_PERMIT_UART2)	
if(num==2) {LinkUART2.codeErr=codeErr;}
#endif
#if defined(RT_HW_PERMIT_UART3)	
if(num==3) {LinkUART3.codeErr=codeErr;}
#endif
#if defined(RT_HW_PERMIT_UART4)	
if(num==4) {LinkUART4.codeErr=codeErr;}
#endif
#if defined(RT_HW_PERMIT_UART5)	
if(num==5) {LinkUART5.codeErr=codeErr;}
#endif
#if defined(RT_HW_PERMIT_UART6)	
if(num==6) {LinkUART6.codeErr=codeErr;}
#endif
#if defined(RT_HW_PERMIT_UART7)	
if(num==7) {LinkUART7.codeErr=codeErr;}
#endif
#if defined(RT_HW_PERMIT_UART8)	
if(num==8) {LinkUART8.codeErr=codeErr;}
#endif
#if defined(RT_HW_PERMIT_UART9)	
if(num==9) {LinkUART9.codeErr=codeErr;}
#endif
#if defined(RT_HW_PERMIT_UART10)	
if(num==10){LinkUART10.codeErr=codeErr;}
#endif
//---------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UARTS)	
if(num==100) {LinkUARTS.codeErr=codeErr;}
#endif
#if defined(RT_HW_PERMIT_UARTB)	
if(num==200) {LinkUARTB.codeErr=codeErr;}
#endif
if(num || codeErr){return;}; //--To block warning C++;
};
//=================================================================================================
// 											1.16.Get code error
//=================================================================================================
uint8_t uartGetCodeErr (uint8_t num=0){
#if defined(RT_HW_PERMIT_UART0)	
if(num==0) {return LinkUART0.codeErr;}
#endif
#if defined(RT_HW_PERMIT_UART1)	
if(num==1) {return LinkUART1.codeErr;}
#endif
#if defined(RT_HW_PERMIT_UART2)	
if(num==2) {return LinkUART2.codeErr;}
#endif
#if defined(RT_HW_PERMIT_UART3)	
if(num==3) {return LinkUART3.codeErr;}
#endif
#if defined(RT_HW_PERMIT_UART4)	
if(num==4) {return LinkUART4.codeErr;}
#endif
#if defined(RT_HW_PERMIT_UART5)	
if(num==5) {return LinkUART5.codeErr;}
#endif
#if defined(RT_HW_PERMIT_UART6)	
if(num==6) {return LinkUART6.codeErr;}
#endif
#if defined(RT_HW_PERMIT_UART7)	
if(num==7) {return LinkUART7.codeErr;}
#endif
#if defined(RT_HW_PERMIT_UART8)	
if(num==8) {return LinkUART8.codeErr;}
#endif
#if defined(RT_HW_PERMIT_UART9)	
if(num==9) {return LinkUART9.codeErr;}
#endif
#if defined(RT_HW_PERMIT_UART10)	
if(num==10) {return LinkUART10.codeErr;}
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UARTS)	
if(num==100) {return LinkUARTS.codeErr;}
#endif
#if defined(RT_HW_PERMIT_UARTB)	
if(num==200) {return 0;}
#endif
if(num){return 0;}; //--To block warning C++;
        return 0;};



//=================================================================================================


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ESP32->M5STACK:
// setRxTimeout устанавливает таймаут, по истечении которого будет вызван обратный вызов onReceive 
//  (после получения данных он ждет это время бездействия UART rx для вызова обратного вызова fnc)
// параметр symbol_timeout определяет порог тайм-аута в периодах символа uart. 
// Установка таймаута символа 0 отключает обратный вызов по таймауту.
// Настройка максимального тайм-аута рассчитывается IDF автоматически. 
// Если установлено выше максимального значения, оно игнорируется, 
//                                             и на Serial0 печатается ошибка (проверьте консоль).
// Примеры: максимум для 11-битного символа — 92 (SERIAL_8N2, SERIAL_8E1, SERIAL_8O1 и т. д.), 
//          максимум для 10-битного символа — 101 (SERIAL_8N1).
// Приме:   symbols_timeout=1 определяет тайм-аут, равный времени передачи одного символа (~11 бит) 
//                                                               на текущей скорости передачи данных.
//          Для скорости 9600 бод, SERIAL_8N1 (10-битный символ) и symbol_timeout = 3 
//                                                       тайм-аут будет 3 / (9600 / 10) = 3,125 мс;
//-------------------------------------------------------------------------------------------------
// ESP32->M5STACK:
// onReceive установит обратный вызов, который будет вызываться всякий раз, 
//              когда происходит прерывание UART (UART_INTR_RXFIFO_FULL или UART_INTR_RXFIFO_TOUT).
// Прерывание UART_INTR_RXFIFO_FULL срабатывает при получении UART_FULL_THRESH_DEFAULT байтов 
//                                                      (по умолчанию в IDF определено 120 байтов).
// Прерывание UART_INTR_RXFIFO_TOUT срабатывает при передаче символов UART_TOUT_THRESH_DEFAULT без приема 
//                                                      (по умолчанию в IDF определено 10 символов).
// Параметр onlyOnTimeout будет определять, как будет вести себя onReceive:
// По умолчанию: true -- Обратный вызов будет вызван только тогда, когда произойдет тайм-аут RX.
//                       Весь поток байтов будет сразу готов к чтению функцией обратного вызова.
//                       Эта опция может привести к переполнению Rx в зависимости от размера буфера Rx 
//                                                   и количества байтов, полученных в потоковой передаче.
//               false --Обратный вызов будет вызван, когда FIFO достигнет 120 байт, а также по тайм-ауту RX.
//                       Поток непереданных байтов будет "разбит" на блоки по 120 байт при каждом обратном вызове.
//                       Этот параметр позволяет избежать любого вида переполнения Rx, 
//                                       но оставляет работу по повторной сборке пакетов UART приложению.
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	

/*
//=================================================================================================
//							+++++++ 2.1. Set Pins ++++++
//=================================================================================================
void     uartSetPinsX (uint8_t rx, uint8_t tx,  uint8_t num=0){
#if defined(RT_HW_BASE_CORE_AVR)

#endif
//====================================For other ARCH===============================================
#if defined(RT_HW_PERMIT_UART0)	
if(num==0) {LinkUART0.rx=rx; LinkUART0.tx=tx;}
#endif
#if defined(RT_HW_PERMIT_UART1)	
if(num==1) {LinkUART1.rx=rx; LinkUART1.tx=tx;}
#endif
#if defined(RT_HW_PERMIT_UART2)	
if(num==2) {LinkUART2.rx=rx; LinkUART2.tx=tx;}
#endif
#if defined(RT_HW_PERMIT_UART3)	
if(num==3) {LinkUART3.rx=rx; LinkUART3.tx=tx;}
#endif
#if defined(RT_HW_PERMIT_UART4)	
if(num==4) {LinkUART4.rx=rx; LinkUART4.tx=tx;}
#endif
#if defined(RT_HW_PERMIT_UART5)	
if(num==5) {LinkUART5.rx=rx; LinkUART5.tx=tx;}
#endif
#if defined(RT_HW_PERMIT_UART6)	
if(num==6) {LinkUART6.rx=rx; LinkUART6.tx=tx;}
#endif
#if defined(RT_HW_PERMIT_UART7)	
if(num==7) {LinkUART7.rx=rx; LinkUART7.tx=tx;}
#endif
#if defined(RT_HW_PERMIT_UART8)	
if(num==8) {LinkUART8.rx=rx; LinkUART8.tx=tx;}
#endif
#if defined(RT_HW_PERMIT_UART9)	
if(num==9) {LinkUART9.rx=rx; LinkUART9.tx=tx;}
#endif
#if defined(RT_HW_PERMIT_UART10)	
if(num==10){LinkUART10.rx=rx; LinkUART10.tx=tx;}
#endif
//---------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UARTS)	
if(num==100) {LinkUARTS.rx=rx; LinkUARTS.tx=tx;}
#endif
#if defined(RT_HW_PERMIT_UARTB)	
if(num==200) {;}
#endif
if(num || rx || tx){return;}; //--To block warning C++;
};
*/
