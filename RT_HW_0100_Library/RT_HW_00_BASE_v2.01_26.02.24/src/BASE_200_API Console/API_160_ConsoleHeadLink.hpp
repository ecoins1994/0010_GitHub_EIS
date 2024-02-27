//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 								1. API Console - Заголовки
// 							         UART, i2c, SPI, SPN
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//							1.1. Output UART parameters
//=================================================================================================
void     uartHeadInterface(uint8_t num=0)
{								
#if defined(RT_HW_LINK_UART)
//-------------------------------------------------------------------------------------------------
//						Определение временных переменных;
//-------------------------------------------------------------------------------------------------
#if !defined(RT_HM_COREM)				//==Если контроллер не многоядерный;
  uint8_t  arr[3];
#endif
//-------------------------------------------------------------------------------------------------
if(!uartCheckNum(num))	{return;}	//--Checking for the presence of a UART;
if(!consoleRun())		{return;} 	//--Setting up the console with default options and waiting for it to be ready;
mess.alig='R'; mess.blank=' '; mess.modePin='T'; mess.modeAdr='A'; mess.qntBit=8; mess.signBit='1'; 
//--------------------------------------------------------------------------------------------------
	arr[0]=uartGetPinRX(num); arr[1]=uartGetPinTX(num); arr[2]=uartGetPinDE(num);	
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
  if(arr[2]<254)           {consoleVar(String(F(" RX,TX,DE="))); consoleArr(arr,';',mess.lenPin,'P',3);}
  else 				       {consoleVar(String(F(" RX,TX   ="))); consoleArr(arr,';',mess.lenPin,'P',2); consoleBlank(mess.lenPin+1);}
  if(uartGetStatus(num)==0){consoleVar(String(F(" No  init")),';');} 
  else                     {consoleVar(String(F(" Yes init")),';');} 
                            consoleVar(String(F(" Speed=")));    consoleVar(uartGetSpeed(num),' ',7,'U');
						  consoleVar(uartGetDataBit(num));
						  consoleVar(uartGetParityChar(num));
						  consoleVar(uartGetStopBit(num));						  
					      consoleCR();
return;
#endif
};

//=================================================================================================
//							1.2. Output of i2c parameters
//=================================================================================================
void    i2cHeadInterface(uint8_t bus=0)
{							
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
//							1.3. Output SPI parameters
//=================================================================================================
void     spiHeadInterface(uint8_t bus=0)
{
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
//							1.4. Output SPN parameters
//=================================================================================================
void     spnHeadInterface()
{	
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

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 								4.API console - вывод параметров интерфейсов
// 									(using interface header output functions)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=================================================================================================
//							4.1. Outputting interfaces to the console 
//================================================================================================= 
void consoleInterface()
{
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
{
#if !defined(RT_HM_COREM)				//==Если контроллер не многоядерный;
  uint8_t bf8,ba8; 
#endif
//-------------------------------------
mess.alig='R'; mess.blank=' '; mess.modePin='T';
bf8=vEthBus(0); ba8=vEthCS(0);
if((bf8!=255) && (ba8!=255)){consoleTest(String(F("Ethernet0: num SPI")),bf8,';','U');
	                         consoleTest(String(F(" pin CS")),           ba8, ';','P');
bf8=vEthINT(0); if(bf8!=255){consoleTest(String(F(" pin INT")),bf8,';','P');}	
bf8=vEthRST(0); if(bf8!=255){consoleTest(String(F(" pin RST")),bf8,';','P');}
consoleCR();}
}
#endif		
//-------------------------------------------------------------------------------------------------
//							4.1.7. CAN интерфейс
//-------------------------------------------------------------------------------------------------
#ifdef RT_HW_PERMIT_CAN
{
#if !defined(RT_HM_COREM)				//==Если контроллер не многоядерный;
  uint8_t bf8,ba8; 
#endif
//-------------------------------------
mess.alig='R'; mess.blank=' '; mess.modePin='T';
bf8=vCanBus(0); ba8=vCanCS(0);
if((bf8!=255) && (ba8!=255)){consoleTest(String(F("CAN:       num SPI")),bf8,';','U');
	                         consoleTest(String(F(" pin CS")),          ba8, ';','P');
							 consoleCR();}
}
#endif
//-------------------------------------------------------------------------------------------------
//							4.1.8. TFT интерфейс
//-------------------------------------------------------------------------------------------------
#ifdef RT_HW_PERMIT_TFT
{
#if !defined(RT_HM_COREM)				//==Если контроллер не многоядерный;
  uint8_t bf8,ba8,bd8; 
#endif
//-------------------------------------
  mess.alig='R'; mess.blank=' '; mess.modePin='T';
  bf8=vTftBus(0); ba8=vTftCS(0); bd8=vTftDC(0); 	
  if((bf8!=255) && (ba8!=255) && (bd8!=255)){consoleTest(String(F("TFT:       num SPI")),bf8,';','U');
											 consoleTest(String(F(" pin CS")),          ba8,';','P');
 										     consoleTest(String(F(" pin  DC")),         bd8,';','P');}												
  bf8=vTftLED(0); if(bf8!=255)              {consoleTest(String(F(" pin LED")),         bf8,';','P');}	
										     consoleCR();
}
#endif
//-------------------------------------------------------------------------------------------------
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
