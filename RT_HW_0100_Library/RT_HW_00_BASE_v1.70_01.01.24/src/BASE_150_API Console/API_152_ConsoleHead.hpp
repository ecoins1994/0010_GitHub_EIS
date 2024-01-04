#include "RT_HW_BASE.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							1. API console - системные параметры
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//							1.1.Вывод времени компиляции и основных параметров плат
//=================================================================================================
void  consoleBoardGeneral(){		
mess.alig='R'; mess.blank=' ';
consoleVar(String(F(__DATE__)));  consoleBlank(61);  consoleVar(String(F(__TIME__)),'L');
//-------------------------------------------------------------------------------------------------
consoleVar(String(F("Board IDE---->")),'~',0,'S');          	
#if defined(RT_HW_BOARD_NAME)
consoleVar(String(F(RT_HW_BOARD_NAME)),'/',0,'S'); 
#endif
consoleVar(device.board.codeBoard,';',0,'U');
//-------------------------------------------------------------------------------------------------
consoleBlank(2);
consoleVar(String(F(" Arch->")));           	
#if defined(RT_HW_ARCH_NAME)
consoleVar(String(F(RT_HW_ARCH_NAME)),'/');	
#endif
consoleVar(device.board.codeArch,';',0,'U'); 
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_CORE_NAME)
consoleBlank(2);
consoleVar(String(F(" Core->")));		   	
consoleVar(String(F(RT_HW_CORE_NAME)),';'); 
#endif
//-------------------------------------------------------------------------------------------------
consoleCR();
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_BOARD_SELECT)
consoleVar(String(F("Board select->")));	consoleVar(String(F(RT_HW_BOARD_SELECT)),';');
consoleTest(String(F(" Check pins")),device.board.permitCheckPin,'E');
#endif	
};	
//=================================================================================================
//							1.2.Вывод наименований используемых библиотек
//=================================================================================================
void  consoleUsingLibrary(){
consoleVar(String(F("RT_HW_BASE.h:")));  	 consoleBlank(10); consoleVar(String(F(RT_HW_BASE_VER_NAME)),'E');	
#ifdef RT_HW_ETHERNET_h
consoleVar(String(F("RT_HW_ETHERNET.h:"))); consoleBlank(5);  consoleVar(String(F(RT_HW_ETHERNET_VER_NAME)),'E');	
#endif
#ifdef RT_HW_ETHERNET_NTP_h
//consoleVar(String(F("RT_HW_ETHERNET_NTP.h:"))); consoleBlank(2);  consoleVar(String(F(RT_HW_ETHERNET_NTP_VER_NAME)),'E');	
#endif
};
//=================================================================================================
//							1.3.Вывод дополнительных параметров плат
//=================================================================================================
void  consoleBoardAdd(){
mess.alig='R';          mess.blank=' ';				//--Setting parameters;
//-------------------------------------------------------------------------------------------------
//							1.3.1.Вывод наименования текщей библиотеки 
//-------------------------------------------------------------------------------------------------
consoleVar(String(F("RT_HW_BASE.h->")));   consoleVar(String(F(RT_HW_BASE_VER_NAME)),'E');
//------Output of board parameters-----------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//							1.3.2.Вывод параметров платы(Частота,Vcc,память) 
//-------------------------------------------------------------------------------------------------
consoleVar(String(F("Fcpu="))); 	consoleVar(device.board.freqCPU);	consoleVar(String(F("mHz")),';'); 
consoleVar(String(F(" Vcc="))); 	consoleVar(float(device.board.vccCPU/1000.0),';'); 
#if defined(RT_HW_BOARD_MEMORY)
consoleVar(String(F(" Memory:: "))); consoleVar(String(F(RT_HW_BOARD_MEMORY)),'E');
#endif
//-------------------------------------------------------------------------------------------------
//							1.3.3.Вывод параметров устройств на плате(системное разрешение,ADC,Touch,PWM,DAC)
//-------------------------------------------------------------------------------------------------
mess.alig='R'; mess.blank=' ';
consoleTest(String(F("SYS.depth")),device.depth.sys,';'); consoleTest(String(F(" SYS.max")),uint16_t(maxBitDepth(device.depth.sys)),';');
if(device.depth.adc!=0){consoleTest(String(F(" ADC::depth,drift,null")),device.depth.adc,','); consoleVar(device.depth.adcDrift,','); consoleVar(device.depth.adcNull,';');}
if(device.depth.tch!=0){consoleTest(String(F(" Touch")),device.depth.tch,';');}
if(device.depth.pwm!=0){consoleTest(String(F(" PWM")),device.depth.pwm,';');}
if(device.depth.dac!=0){consoleTest(String(F(" DAC")),device.depth.dac,';');}
consoleCR();
//-------------------------------------------------------------------------------------------------
//							1.3.4.Вывод MAC-адреса Ethernet
//-------------------------------------------------------------------------------------------------
consoleTestArr(String(F("MAC addrres(Random)")),buff.mac,'E','H',6);
//-------------------------------------------------------------------------------------------------
//							1.3.4.Вывод ограничений и специфики плат (в основном для серии ESP32)
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_CORE_ESP8266)	
consoleVar(String(F("[Download requirement for pins->D3=1,D4=1,D8=0;]")),'E');
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_CORE_ESP32)
consoleVar(String(F("[Strapping pins 0,2,4,5,12,15; Connected to the integrated SPI flash pins 6,7,8.9.11; Boot fail if pulled high; Inpuu only pins >=34]")),'E');
consoleVar(String(F("[Download for pins->pin 0 pulled up; pin 1 - debug output at boot; pin 2 - connected to on-board Led; pin 3-  HIGH at boot;")),'E');
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_CORE_ESP32_C3)
consoleVar(String(F("[Download requirement for pins->pin3=1]")),'E');
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_CORE_ESP32_S2)
consoleVar(String(F("[Download requirement for pins->pin3=1,pin12=1. Note: pins 0,5,14,15=PWM; pins.1=debug;]")),'E');
#endif
//-------------------------------------------------------------------------------------------------
};
//=================================================================================================
//							1.4.Вывод доступных системных пинов
//=================================================================================================
void  consolePinsSystem(){		
mess.alig='R'; mess.blank=' ';
//-------------------------------------------------------------------------------------------------
console.arr[0]=device.pin.control; console.arr[1]=device.pin.led; console.arr[2]=device.pin.ws2812; console.arr[3]=device.pin.button;
console.arr[4]=device.pin.adc;     console.arr[5]=device.pin.pwm; console.arr[6]=device.pin.servo;  console.arr[7]=device.pin.debug;
console.bf8=0; for(console.idx=0; console.idx<2; console.idx++){if(console.arr[console.idx]!=255){console.bf8++;}}
if(console.bf8){consoleVar(String(F("System-->")));
				if(console.arr[0]!=255){consoleTest(String(F(" control")),console.arr[0],';','P');}
				if(console.arr[1]!=255){consoleTest(String(F(" Led")),    console.arr[1],';','P');}
				if(console.arr[2]!=255){consoleTest(String(F(" WS2812")), console.arr[2],';','P');}
				if(console.arr[3]!=255){consoleTest(String(F(" button")), console.arr[3],';','P');}
				if(console.arr[4]!=255){consoleTest(String(F(" ADC")),    console.arr[4],';','P');}
				if(console.arr[5]!=255){consoleTest(String(F(" PWM")),    console.arr[5],';','P');}
				if(console.arr[6]!=255){consoleTest(String(F(" Servo")),  console.arr[6],';','P');}	
				if(console.arr[7]!=255){consoleTest(String(F(" Debug")),  console.arr[7],';','P');}					
				consoleCR();}
//-------------------------------------------------------------------------------------------------
};
//=================================================================================================
//							1.5.Вывод доступных системных пинов CS для SPI
//=================================================================================================
void  consolePinsCS(){	
console.arr[0]=device.spi.cs0; console.arr[1]=device.spi.cs1; console.arr[2]=device.spi.cs2; console.arr[3]=device.spi.cs3;
console.arr[4]=device.spi.cs4; console.arr[5]=device.spi.cs5; console.arr[6]=device.spi.cs6; console.arr[7]=device.spi.cs7;
console.bf8=0; for(console.idx=0; console.idx<=7; console.idx++){if(console.arr[console.idx]!=255){console.bf8++;}}
if(console.bf8){consoleVar(String(F("SPI cs-->")));
				if(console.arr[0]!=255){consoleTest(String(F(" cs0")), console.arr[0],';','P');}
				if(console.arr[1]!=255){consoleTest(String(F(" cs1")), console.arr[1],';','P');}
				if(console.arr[2]!=255){consoleTest(String(F(" cs2")), console.arr[2],';','P');}
				if(console.arr[3]!=255){consoleTest(String(F(" cs3")), console.arr[3],';','P');}
				if(console.arr[4]!=255){consoleTest(String(F(" cs4")), console.arr[4],';','P');}
				if(console.arr[5]!=255){consoleTest(String(F(" cs5")), console.arr[5],';','P');}
				if(console.arr[6]!=255){consoleTest(String(F(" cs6")), console.arr[6],';','P');}
				if(console.arr[7]!=255){consoleTest(String(F(" cs7")), console.arr[7],';','P');}				
				consoleCR();}
//-------------------------------------------------------------------------------------------------
};	
//=================================================================================================
//							1.5.Вывод параметров диспетчера задач
//=================================================================================================
void  consoleShedulerParameters(){	
mess.alig='R'; mess.blank=' ';
consoleVar(String(F("Sheduler::qnt---->quick,fast,slow,back,frdm="))); 
console.arr[0]=shed.quick.qnt; console.arr[1]=shed.fast.qnt; console.arr[2]=shed.slow.qnt; console.arr[3]=shed.back.qnt; console.arr[4]=shed.frdm.qnt;
mess.alig='R';    consoleArr(console.arr,'E',4,'U',5);
consoleBlank(10); consoleVar(String(F("period->quick,fast,slow,back,frdm= 10, 25,250,100,loop()")),'E');
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							2. API console - PROGMEM output
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//							2.1.Вывод массивов с параметрами плат (из PROGMEM)
//=================================================================================================
void  consoleFromPGM(){
mess.alig='R'; mess.blank=' '; mess.modePin='T'; mess.modeAdr='A'; mess.qntBit=8; mess.signBit='1'; 
//-------------------------------------------------------------------------------------------------
for(console.idx=RT_HW_PGM_PIN_ALL_ID; console.idx<=RT_HW_PGM_PIN_N5V_ID; console.idx++){consoleArrPGM(console.idx);};
for(console.idx=RT_HW_PGM_PIN_UHS_ID; console.idx<=RT_HW_PGM_PIN_CAN_ID; console.idx++){consoleArrPGM(console.idx);};
for(console.idx=RT_HW_PGM_PIN_BRD_ID; console.idx<=RT_HW_PGM_PIN_TFT_ID; console.idx++){consoleArrPGM(console.idx);};
for(console.idx=RT_HW_PGM_TST_DIS_ID; console.idx<=RT_HW_PGM_TST_DEV_ID; console.idx++){consoleArrPGM(console.idx);};
consoleArrPGM(RT_HW_PGM_TST_URT_ID);
//-------------------------------------------------------------------------------------------------
};
//=================================================================================================
//							2.2.Вывод доступных пинов (T-текст,D-число,A-текст/число];
//=================================================================================================
void  consolePinsAll(){
static uint8_t idx;
//-------------------------------------------------------------------------------------------------
mess.alig='R'; mess.blank=' '; mess.modePin='T'; mess.modeAdr='A'; mess.qntBit=8; mess.signBit='1'; 
//-------------------------------------------------------------------------------------------------
for(idx=RT_HW_PGM_PIN_ALL_ID; idx<=RT_HW_PGM_PIN_N5V_ID; idx++){consoleArrPGM(idx);}
if(getLenPosPGM(RT_HW_PGM_PIN_N5V_ID)==0) {consoleVar(String(F("All pins tolerant to 5V")),'E');}	
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_CORE_ESP8266)	
mess.alig='R'; mess.modePin='D';
consoleHead(String(F("Name pins ESP8266")),'-',80);
consoleVar(String(F("[D0-D4]--------->16,5,4,0,2")),'E');
consoleVar(String(F("[D5-D8,--------->14,12,13,15")),'E');
consoleVar(String(F("[D9-D10,A0]----->3,1,17")),'E');
consoleVar(String(F("[RX,RX0,TX,TX0]->3,3,1,1,")),'E');
consoleVar(String(F("[TX1,RX2,TX2]--->2,3,15")),'E');
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_CORE_STM32)  //--STM32 is a single-core processor, so you can use temporary variables without conflict;
{uint8_t arr[16]; char reg; bool ok;
consoleHead(String(F("Name pins STM32")),'-',80);
mess.modePin='A';
for(uint8_t m=0; m<12; m++){reg='A'+ m; ok=0; 
 for(uint8_t i=0;i<16; i++){arr[i]=getNumPinSTM32(reg,i); if(arr[i]<254){ok=1;}}	
  if(ok){consoleChar('P'); consoleChar(char(reg)); consoleVar(String(F("[16]  ")));
    for(uint8_t j=0;j<16;j++){      
		consoleVar(arr[j],' ',9,'P'); 
		if((j==7) && (mess.modePin=='A')){consoleSuff('L'); consoleBlank(8);}
		if(j==15){consoleSuff('L');} 
}}}} 
#endif
//-------------------------------------------------------------------------------------------------
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								3.API console - тестовые пины
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//							3.1.Вывод тестовых пинов(ADC,PWM,Servo) и устройств на них(1-Wire,DHT22,HC-SR04)
//=================================================================================================
void  consolePinsTest(){		
mess.alig='R'; mess.blank=' ';
//-------------------------------------------------------------------------------------------------
console.arr[0]=device.pin.adc1; console.arr[1]=device.pin.pwm1; console.arr[2]=device.pin.servo1;
console.bf8=0; for(console.idx=0; console.idx<2; console.idx++){if(console.arr[console.idx]!=255){console.bf8++;}}
if(console.bf8){consoleVar(String(F("Add Pin->")));;
				if(console.arr[0]!=255){consoleTest(String(F(" ADC1")),  console.arr[0],';');}
				if(console.arr[1]!=255){consoleTest(String(F(" PWM1")),  console.arr[1],';');}
				if(console.arr[2]!=255){consoleTest(String(F(" Servo1")),console.arr[2],';');}
				consoleCR();}
//-------------------------------------------------------------------------------------------------
console.arr[0]=device.dev.oneWire; console.arr[1]=device.dev.dht22;  console.arr[2]=device.dev.sr04;
console.bf8=0; for(console.idx=0; console.idx<=2; console.idx++){if(console.arr[console.idx]!=255){console.bf8++;}}
if(console.bf8){consoleVar(String(F("Device-->"))); 
				if(console.arr[0]!=255){consoleTest(String(F(" 1-Wire")),      console.arr[0],';','P');}
				if(console.arr[1]!=255){consoleTest(String(F(" DHT-22")),	   console.arr[1],';','P');}
				if(console.arr[2]!=255){consoleTest(String(F(" HC-SR04.trig")),console.arr[2],';','P');}
				consoleCR();}
//-------------------------------------------------------------------------------------------------
};
//=================================================================================================
//							3.2.Вывод номеров UART для устройств
//=================================================================================================
void  consoleNumUART(){
console.arr[0]=device.uart.console; console.arr[1]=device.uart.modbus1; 
console.arr[2]=device.uart.modbus2; console.arr[3]=device.uart.nextion;
console.arr[4]=device.uart.wifi;    console.arr[5]=device.uart.eth1; 
console.arr[6]=device.uart.eth2;    console.arr[7]=device.uart.device;

console.bf8=0; for(console.idx=0; console.idx<=7; console.idx++){if(console.arr[console.idx]!=255){console.bf8++;}}
if(console.bf8){consoleVar(String(F("numUART->")));
                if(console.arr[0]!=255){
				if(console.arr[0]==210){consoleVar(String(F(" Console=USB")),';');}
				  else                 {consoleTest(String(F(" Console")),   console.arr[0],';','U');}}
                if(console.arr[1]!=255){consoleTest(String(F(" Modbus.1")),  console.arr[1],';','U');}
                if(console.arr[2]!=255){consoleTest(String(F(" Modbus.2")),  console.arr[2],';','U');}				
                if(console.arr[3]!=255){consoleTest(String(F(" Nextion")),   console.arr[3],';','U');}
                if(console.arr[4]!=255){consoleTest(String(F(" Wi-Fi")),     console.arr[4],';','U');}
                if(console.arr[5]!=255){consoleTest(String(F(" Ethernet.1")),console.arr[5],';','U');}
                if(console.arr[6]!=255){consoleTest(String(F(" Ethernet.2")),console.arr[6],';','U');}				
                if(console.arr[7]!=255){consoleTest(String(F(" Device")),    console.arr[7],';','U');}			
                consoleCR();}
//-------------------------------------------------------------------------------------------------
};				
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 								4.API console - вывод параметров интерфейсов
// 									(using interface header output functions)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//							4.1. Outputting interfaces to the console 
//================================================================================================= 
void consoleInterface(){
//-------------------------------------------------------------------------------------------------
//							4.1.1. i2c interface
//-------------------------------------------------------------------------------------------------
for(console.i=0; console.i<=6; console.i++){i2cHeadInterface(console.i);}
//-------------------------------------------------------------------------------------------------
//							4.1.2. SPI interface
//-------------------------------------------------------------------------------------------------	
for(console.i=0; console.i<=6; console.i++){spiHeadInterface(console.i);}
//-------------------------------------------------------------------------------------------------
//							4.1.3. SPN interface
//-------------------------------------------------------------------------------------------------	
spnHeadInterface();
//-------------------------------------------------------------------------------------------------
//							4.1.4. UART interface
//-------------------------------------------------------------------------------------------------
for(console.i=0; console.i<=15; console.i++){uartHeadInterface(console.i);}
uartHeadInterface(100);		//--UARTS;
uartHeadInterface(200);		//--UARTB;
//-------------------------------------------------------------------------------------------------
//							4.1.5. Messages on the UART interface
//-------------------------------------------------------------------------------------------------
#ifdef RT_HW_CORE_ESP8266
consoleVar(String(F("[UART  possible options are (1,3),(2,3) or (15,13);")),'L');
consoleVar(String(F(" Set Serial.pins(uint8_t tx, uint8_t rx) or Serial.swap(uint8_t tx_pin)")),'L');
consoleVar(String(F(" toggle between use of GPIO13/GPIO15 or GPIO3/GPIO(1/2)as RX and TX;")),'E');
consoleVar(String(F(" UART1 allows only TX on 2 if UART is not (2,3);]")),'E');	 
#endif
//-------------------------------------------------------------------------------------------------
//							4.1.6. Ethernet interface
//-------------------------------------------------------------------------------------------------
#ifdef RT_HW_PERMIT_ETH
mess.alig='R'; mess.blank=' '; mess.modePin='T';
if((device.spi.busETH!=255) && (device.spi.csETH!=255)){consoleTest(String(F("Ethernet: num SPI")),device.spi.busETH,';','U');
	                                                    consoleTest(String(F(" pin CS")),          device.spi.csETH, ';','P');
if( device.spi.intETH!=255)                            {consoleTest(String(F(" pin INT")),         device.spi.intETH,';','P');}	
											            consoleCR();}
#endif	
//-------------------------------------------------------------------------------------------------
//							4.1.7. CAN interface
//-------------------------------------------------------------------------------------------------
#ifdef RT_HW_PERMIT_CAN
mess.alig='R'; mess.blank=' '; mess.modePin='T';
if((device.spi.busCAN!=255) && (device.spi.csCAN!=255)){consoleTest(String(F("CAN:      num SPI")),device.spi.busCAN,';','U');
	                                                    consoleTest(String(F(" pin CS")),          device.spi.csCAN, ';','P');
if( device.spi.intCAN!=255)                            {consoleTest(String(F(" pin INT")),         device.spi.intCAN,';','P');}	
											            consoleCR();}
#endif
//-------------------------------------------------------------------------------------------------
//							4.1.8. TFT interface
//-------------------------------------------------------------------------------------------------
#ifdef RT_HW_PERMIT_TFT
mess.alig='R'; mess.blank=' '; mess.modePin='T';
if((readArrPGM(RT_HW_PGM_PIN_TFT_ID,0)!=255) && (readArrPGM(RT_HW_PGM_PIN_TFT_ID,1)!=255) && (readArrPGM(RT_HW_PGM_PIN_TFT_ID,2)!=255)){
                                                consoleTest(String(F("TFT:      num SPI")),readArrPGM(RT_HW_PGM_PIN_TFT_ID,0),';','U');
	                                            consoleTest(String(F(" pin CS")),          readArrPGM(RT_HW_PGM_PIN_TFT_ID,1),';','P');
	                                            consoleTest(String(F(" pin  DC")),         readArrPGM(RT_HW_PGM_PIN_TFT_ID,2),';','P');												
	if(readArrPGM(RT_HW_PGM_PIN_TFT_ID,0)!=255){consoleTest(String(F(" pin LED")),         readArrPGM(RT_HW_PGM_PIN_TFT_ID,3),';','P');}	
												consoleCR();}
#endif
//-------------------------------------------------------------------------------------------------
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 								5. API Console - HEADERS
// 						scan I2c buses, UART headers, i2c, SPI, SPN
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//							5.1. Output UART parameters
//=================================================================================================
void     uartHeadInterface(uint8_t num=0){								
if(!uartCheckNum(num))	{return;}	//--Checking for the presence of a UART;
if(!consoleRun())		{return;} 	//--Setting up the console with default options and waiting for it to be ready;
mess.alig='R'; mess.blank=' '; mess.modePin='T'; mess.modeAdr='A'; mess.qntBit=8; mess.signBit='1'; 
//--------------------------------------------------------------------------------------------------
console.arr[0]=uartGetPinRX(num); console.arr[1]=uartGetPinTX(num); console.arr[2]=uartGetPinDE(num);
//--------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART0) && defined(RT_HW_CORE_STM32)
if(num==0){consoleVar(String(F("UART0: USB:DP,DM=PA12,PA11")),'E'); return;}
#endif 
//--------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UART0) && defined(RT_HW_CORE_RP2040)
if(num==0){consoleVar(String(F("UART0: USB:DP,DM=47,46")),'E');    return;}
#endif 
//--------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_UARTB)
if(num==200){consoleVar(String(F("UARTB: Bluetooth name="))); consoleVar(uartGetNameBTH(),'E'); return;}
#endif 
//-------------------------------------------------------------------------------------------------
consoleVar(String(F("UART")));
if(num==100){consoleChar('S',':');} 
else        {consoleVar(num,':');}
//-------------------------------------------------------------------------------------------------
if(console.arr[2]<254)   {consoleVar(String(F(" RX,TX,DE="))); consoleArr(console.arr,';',mess.lenPin,'P',3);}
else 				     {consoleVar(String(F(" RX,TX   ="))); consoleArr(console.arr,';',mess.lenPin,'P',2); consoleBlank(mess.lenPin+1);}
if(uartGetStatus(num)==0){consoleVar(String(F(" No  init")),';');} 
else                     {consoleVar(String(F(" Yes init")),';');} 
                          consoleVar(String(F(" Speed=")));    consoleVar(uartGetSpeed(num),' ',7,'U');
						  consoleVar(uartGetDataBit(num));
						  consoleVar(uartGetParityChar(num));
						  consoleVar(uartGetStopBit(num));						  
					      consoleCR();
return;
};
//=================================================================================================
//							5.2. Output of i2c parameters
//=================================================================================================
void    i2cHeadInterface(uint8_t bus=0){							
#if defined(RT_HW_LINK_I2C)
//-------------------------------------------------------------------------------------------------
if(!i2cCheckBus(bus))			{return;}	//--Checking for the presence of the i2c bus;
consoleBegin();	if(!console.ok)	{return;} 	//--Configuring the console with default parameters and waiting for readiness;
mess.alig='R'; mess.blank=' '; mess.modePin='T'; mess.modeAdr='A'; mess.qntBit=8; mess.signBit='1'; 
consoleVar(String(F("I2C"))); consoleVar(bus);
consoleVar(String(F(" bus="))); consoleVar(bus,':');
consoleVar(String(F(" SDA,SCL="))); consoleVar(i2cGetPinSDA(bus),',',mess.lenPin,'P'); consoleVar(i2cGetPinSCL(bus),';',mess.lenPin,'P'); consoleBlank(5);
	 if(i2cGetStatus(bus)==0) {consoleVar(String(F("No init")),';');} 
	 if(i2cGetStatus(bus)==1) {consoleVar(String(F("Master ")),';');} 
	 if(i2cGetStatus(bus)==2) {consoleVar(String(F("Slave  ")),';');} 
consoleVar(String(F(" speed(kHz)="))); consoleVar((uint32_t)(i2cGetSpeed(bus)/1000),';');
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_CORE_ESP8266)
consoleVar(String(F(" [SDA,SCL any pin from D1-D10]")),';');
#endif
#if defined(RT_HW_CORE_ESP32_S2)  
consoleVar(String(F(" [SDA,SCL any pin <35]")),';');
#endif
#if defined(RT_HW_CORE_STM32)
//if(bus==0){consoleVar(String(F(" Select SDA,SCL: pin PB7,PB6 or PB9,PB8")),';');}  
//if(bus==1){consoleVar(String(F(" Select SDA,SCL: pin PB3,PB10")),';');} 
#endif 
//-------------------------------------------------------------------------------------------------
consoleCR();
//-------------------------------------------------------------------------------------------------
#endif
};							
//=================================================================================================
//							5.3. Scanning the i2c bus
//=================================================================================================
uint8_t i2cScanBus(RT_HW_STRUCT_I2C_DEV &id, uint8_t bus=0, uint8_t channel=0, uint32_t speed=0){							
#if defined(RT_HW_LINK_I2C)
if(!i2cCheckBus(bus)){return 0;}	//--Выход, если шина недоступна;
id.custom=0; i2cSetParam(id,255,bus,speed); id.channel=channel; id.agoChannel=255;
i2cInitDevice(id); if(!id.link){return 1;}
//-------------------------------------------------------------------------------------------------         
consoleBegin(); //if(!console.ok){return 1;}	//--Setting up the console with default options and waiting for it to be ready;
mess.alig='R'; mess.blank=' ';  mess.modePin='T'; 
consoleVar(String(F("I2C")));           consoleVar(bus,'~');
consoleVar(String(F(" bus=")));         consoleVar(bus,'~'); 
if((id.expander) && (id.channel>0) && (id.channel<=8)){consoleVar(String(F(" channel="))); consoleVar(id.channel,'~');}
consoleVar(String(F(": scan->")));
if(id.status==0) {consoleVar(String(F("No init")),'E'); 	return 1;} 
if(id.status==2) {consoleVar(String(F(" Slave")),'E');  	return 1;} 
if(id.status!=1) {consoleVar(String(F(" No Master")),'E');  return 1;}
id.idx=1; id.codeErr=0; id.cnt=0;
//-------------------------------------------------------------------------------------------------
do{if(id.idx>127){break;}
id.adr=id.idx; i2cFindAdr(id); 
if((id.codeErr==0) && (id.adr!=id.expander)){if(id.cnt>0){if((mess.modeAdr=='A') && (id.cnt==10)){consoleCR();}
					            else if((mess.modeAdr=='H') && (id.cnt==14)){consoleCR();}
					            else if((mess.modeAdr=='D') && (id.cnt==16)){consoleCR();}
						        else                                        {consoleChar(',');}}                                   
id.cnt++; consoleVar(id.idx,'~',0,'A'); }
id.idx++;}while(1);
if(id.cnt>0){consoleChar(';');} 
consoleTest(String(F(" qnt")),id.cnt,'E'); 	
//-------------------------------------------------------------------------------------------------
#endif
return 1;
};

//=================================================================================================
//							5.3x. Scanning the i2c bus
//=================================================================================================
uint8_t i2cScanBus(uint8_t bus=0, uint32_t speed=0){							
#if defined(RT_HW_LINK_I2C)
if(!i2cCheckBus(bus)){consoleVar(String(F("I2C"))); consoleVar(bus,'~'); consoleVar(String(F(" No Bus")),'E'); return 0;}	//--Выход, если шина недоступна;
dvi2c.custom=0;
if(dvi2c.custom==0){i2cSetParam(dvi2c,255,bus,speed);} 
i2cInitDevice(dvi2c);
//-------------------------------------------------------------------------------------------------         
consoleBegin(); //if(!console.ok){return 1;}	//--Setting up the console with default options and waiting for it to be ready;
mess.alig='R'; mess.blank=' ';  mess.modePin='T'; 
consoleVar(String(F("I2C")));           consoleVar(bus,'~');
consoleVar(String(F(" bus=")));         consoleVar(bus,':'); 
consoleVar(String(F(" scan->")));
if(dvi2c.status==0) {consoleVar(String(F("No init")),'E'); return 1;} 
if(dvi2c.status==2) {consoleVar(String(F(" Slave")),'E');  return 1;} 
if(dvi2c.status!=1) {consoleVar(String(F(" No Master")),'E');   return 1;}
dvi2c.idx=1;   dvi2c.codeErr=0; dvi2c.cnt=0;
//-------------------------------------------------------------------------------------------------
do{if(dvi2c.idx>127){break;}
dvi2c.adr=dvi2c.idx; i2cFindAdr(dvi2c); 
if(dvi2c.codeErr==0){if(dvi2c.cnt>0){if((mess.modeAdr=='A') && (dvi2c.cnt==10)){consoleCR();}
					            else if((mess.modeAdr=='H') && (dvi2c.cnt==14)){consoleCR();}
					            else if((mess.modeAdr=='D') && (dvi2c.cnt==16)){consoleCR();}
						        else                                           {consoleChar(',');}}                                   
dvi2c.cnt++; consoleVar(dvi2c.idx,'~',0,'A'); }
dvi2c.idx++;}while(1);
if(dvi2c.cnt>0){consoleChar(';');} 
consoleTest(String(F(" qnt")),dvi2c.cnt,'E'); 	
//-------------------------------------------------------------------------------------------------
#endif
return 1;
};
//=================================================================================================
//							5.4. Output SPI parameters
//=================================================================================================
void     spiHeadInterface(uint8_t bus=0){
#if defined(RT_HW_LINK_SPI)
//-------------------------------------------------------------------------------------------------
if(!spiCheckBus(bus))			{return;}	//--Checking for the presence of the SPI bus;
consoleBegin();	if(!console.ok)	{return;} 	//--Setting up the console with default options and waiting for it to be ready;
mess.alig='R'; mess.blank=' '; mess.modePin='T'; mess.modeAdr='A'; mess.qntBit=8; mess.signBit='1'; 
uint8_t arr[4]; arr[0]=spiGetPinSCK(bus); arr[1]=spiGetPinMISO(bus); arr[2]=spiGetPinMOSI(bus); arr[3]=spiGetPinSS(bus); 
consoleVar(String(F("SPI")));                consoleVar(bus);
consoleVar(String(F(" bus=")));              consoleVar(bus,':');
consoleVar(String(F(" SCK,MISO,MOSI,SS="))); consoleArr(arr,';',mess.lenPin,'P',4);
     if(spiGetStatus(bus)==1){consoleVar(String(F("  Master")),';');}
else if(spiGetStatus(bus)==2){consoleVar(String(F("   Slave")),';');}
else			             {consoleVar(String(F(" No init")),';');}
consoleVar(String(F(" speed(kHz)="))); consoleVar(uint32_t(spiGetSpeed(bus)/1000),';');
consoleCR();
//-------------------------------------------------------------------------------------------------
#endif
};
//=================================================================================================
//							5.5. Output SPN parameters
//=================================================================================================
void     spnHeadInterface(){	
#if defined(RT_HW_LINK_SPN)
//-------------------------------------------------------------------------------------------------
consoleBegin();	if(!console.ok)	{return;}	//--Setting up the console with default options and waiting for it to be ready;
mess.alig='R'; mess.blank=' '; mess.modePin='T'; mess.modeAdr='A'; mess.qntBit=8; mess.signBit='1'; 
if(readArrPGM(RT_HW_PGM_PIN_SPN_ID,0)==255){return;} 	//--check pin sck;
if(readArrPGM(RT_HW_PGM_PIN_SPN_ID,3)==255){return;}	//--check pin cs;
consoleVar(String(F("SPN"))); 
consoleVar(String(F(" pins->SCK,MISO,MOSI,CS="))); 
consoleVar(readArrPGM(RT_HW_PGM_PIN_SPN_ID,0),',',0,'P'); 
consoleVar(readArrPGM(RT_HW_PGM_PIN_SPN_ID,1),',',0,'P'); 
consoleVar(readArrPGM(RT_HW_PGM_PIN_SPN_ID,2),',',0,'P'); 
consoleVar(readArrPGM(RT_HW_PGM_PIN_SPN_ID,3),';',0,'P');
consoleCR();
//-------------------------------------------------------------------------------------------------
#endif
};	
//=================================================================================================

