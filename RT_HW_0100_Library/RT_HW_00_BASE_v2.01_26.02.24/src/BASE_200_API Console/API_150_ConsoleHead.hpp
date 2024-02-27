//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								API console - Вывод системных параметров
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//							1. Вывод времени компиляции и основных параметров плат
//=================================================================================================
void  consoleBoardGeneral(){		
  mess.alig='R'; mess.blank=' ';
  consoleCurrentDate();  			  consoleBlank(64);  consoleCurrentTime('L');          
  //consoleVar(String(F(__DATE__)));  consoleBlank(61);  consoleVar(String(F(__TIME__)),'L');
//-------------------------------------------------------------------------------------------------
  consoleVar(String(F("RT_HW_BASE.h->")));   vVerName();   	consoleVar(mess.str,';');		consoleBlank(1);
  consoleTest(String(F("ID")),  board.id, ';','H');  						             	consoleBlank(1);
  consoleCR();
//-------------------------------------------------------------------------------------------------
  consoleVar(String(F("Board IDE---->"))); 	vBoardName();	consoleVar(mess.str,'/',0,'S'); consoleBlank(1);
  consoleVar(vBoardCode(),';',0,'U');
//-------------------------------------------------------------------------------------------------
  consoleBlank(2);
  consoleVar(String(F("Arch->")));   		vArchName();  	consoleVar(mess.str,'/',0,'S'); consoleBlank(1);
  consoleVar(vArchCode(),';',0,'U'); 
//-------------------------------------------------------------------------------------------------
  consoleBlank(2);
  consoleVar(String(F("Core->")));   		vCoreName();  	consoleVar(mess.str,';'); 		consoleBlank(1);
//-------------------------------------------------------------------------------------------------
  consoleCR();
//-------------------------------------------------------------------------------------------------
  consoleVar(String(F("Board select->")));	vBoardSelect(); consoleVar(mess.str,'E');
};	
//=================================================================================================
//							2. Вывод наименований используемых библиотек
//=================================================================================================
void  consoleUsingLibrary(){
  consoleVar(String(F("RT_HW_BASE.h:")));  	      consoleBlank(5); consoleVar(String(F(RT_HW_BASE_VER_NAME)),'E');	
#ifdef RT_HW_ETHERNET_h
//consoleVar(String(F("RT_HW_ETHERNET.h:"))); 	  consoleBlank(5); consoleVar(String(F(RT_HW_ETHERNET_VER_NAME)),'E');	
#endif
#ifdef RT_HW_ETHERNET_NTP_h
//consoleVar(String(F("RT_HW_ETHERNET_NTP.h:"))); consoleBlank(2); consoleVar(String(F(RT_HW_ETHERNET_NTP_VER_NAME)),'E');	
#endif
};
//=================================================================================================
//							3. Вывод дополнительных параметров плат
//=================================================================================================
void  consoleBoardAdd(){
mess.alig='R';          mess.blank=' ';		
consoleVar(String(F("Fcpu="))); consoleVar(vFCPU());	consoleVar(String(F("mHz")),';'); 
consoleVar(String(F(" Vcc="))); 						consoleVar(float(vVcc()/1000.0),';'); 
consoleVar(String(F(" Memory:: "))); vBoardMemory();    consoleVar(mess.str,'E');
};
//=================================================================================================
//							4. Вывод параметров устройств на плате(системное разрешение,ADC,Touch,PWM,DAC)
//=================================================================================================
void  consoleBoardDepth(){
  mess.alig='R'; mess.blank=' ';
  consoleTest(String(F("SYS.depth")),board.depth,';'); consoleTest(String(F(" SYS.max")),uint16_t(maxBitDepth(board.depth)),';');
  consoleTest(String(F(" ADC::depth,drift,null")),device.adc.depth,','); consoleVar(device.adc.driftVar,','); consoleVar(device.adc.driftNull,';');
#if defined(RT_HW_BASE_PERMIT_TCH)
  consoleTest(String(F(" Touch")),device.tch.depth,';');
#endif
  consoleTest(String(F(" PWM")), device.pwm.depth,';');
#if defined(RT_HW_BASE_PERMIT_DAC)
  consoleTest(String(F(" DAC")), device.dac.depth,';');
#endif
consoleCR();
};
//-------------------------------------------------------------------------------------------------
//							5. Вывод ограничений и специфики плат (в основном для серии ESP32)
//-------------------------------------------------------------------------------------------------
void  consoleBoardSpecific(){
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
//							6. Вывод доступных системных пинов
//=================================================================================================
void  consolePinsSystem()
{		
mess.alig='R'; mess.blank=' ';
//-------------------------------------------------------------------------------------------------
//						Определение временных переменных;
//-------------------------------------------------------------------------------------------------
#if !defined(RT_HM_COREM)				//==Если контроллер не многоядерный;
  uint8_t arr[10];
  uint8_t i;
  uint8_t bf8; 
#endif
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
  arr[0]=vPinControl(); arr[1]=vPinLed(); arr[2]=vPinWS2812(); arr[3]=vPinButton();
  arr[4]=vPinADC();     arr[5]=vPinPWM(); arr[6]=vPinDebug();
  bf8=0; for(i=0; i<7; i++){if(arr[i]!=255){bf8++;}}
  if(bf8)
	{
	consoleVar(String(F("System-->")));
	if(arr[0]!=255){consoleTest(String(F(" control")),arr[0],';','P');}
	if(arr[1]!=255){consoleTest(String(F(" Led")),    arr[1],';','P');}
	if(arr[2]!=255){consoleTest(String(F(" WS2812")), arr[2],';','P');}
	if(arr[3]!=255){consoleTest(String(F(" button")), arr[3],';','P');}
	if(arr[4]!=255){consoleTest(String(F(" ADC")),    arr[4],';','P');}
	if(arr[5]!=255){consoleTest(String(F(" PWM")),    arr[5],';','P');}
	if(arr[6]!=255){consoleTest(String(F(" Debug")),  arr[6],';','P');}					
	consoleCR();
	}
//-------------------------------------------------------------------------------------------------
};
//=================================================================================================
//							7. Вывод доступных системных пинов CS для SPI
//=================================================================================================
void  consolePinsCS(){	
//-------------------------------------------------------------------------------------------------
//						Определение временных переменных;
//-------------------------------------------------------------------------------------------------
#if !defined(RT_HM_COREM)				//==Если контроллер не многоядерный;
  uint8_t arr[10];
  uint8_t i;
  uint8_t bf8; 
#endif
//-------------------------------------------------------------------------------------------------
  arr[0]=vSpiCS0(); arr[1]=vSpiCS1(); arr[2]=vSpiCS2(); arr[3]=vSpiCS3();
  arr[4]=vSpiCS4(); arr[5]=vSpiCS5(); arr[6]=vSpiCS6(); arr[7]=vSpiCS7();
  bf8=0; for(i=0; i<=7; i++){if(arr[i]!=255){bf8++;}}
  if(bf8)
	{
	consoleVar(String(F("SPI cs-->")));
	if(arr[0]!=255){consoleTest(String(F(" cs0")), arr[0],';','P');}
	if(arr[1]!=255){consoleTest(String(F(" cs1")), arr[1],';','P');}
	if(arr[2]!=255){consoleTest(String(F(" cs2")), arr[2],';','P');}
	if(arr[3]!=255){consoleTest(String(F(" cs3")), arr[3],';','P');}
	if(arr[4]!=255){consoleTest(String(F(" cs4")), arr[4],';','P');}
	if(arr[5]!=255){consoleTest(String(F(" cs5")), arr[5],';','P');}
	if(arr[6]!=255){consoleTest(String(F(" cs6")), arr[6],';','P');}
	if(arr[7]!=255){consoleTest(String(F(" cs7")), arr[7],';','P');}				
	consoleCR();
	}
//-------------------------------------------------------------------------------------------------
};	
//=================================================================================================
//							8. Вывод параметров диспетчера задач
//=================================================================================================
void  consoleShedulerParameters()
{
//-------------------------------------------------------------------------------------------------
//						Определение временных переменных;
//-------------------------------------------------------------------------------------------------
#if !defined(RT_HM_COREM)				//==Если контроллер не многоядерный;
  uint8_t arr[6];
#endif
//-------------------------------------------------------------------------------------------------	
  mess.alig='R'; mess.blank=' ';
  consoleVar(String(F("Sheduler::qnt---->tick,quick,fast,slow,back,frdm="))); 
  arr[0]=shed.tick.qnt; arr[1]=shed.quick.qnt;  arr[2]=shed.fast.qnt;  
  arr[3]=shed.slow.qnt; arr[4]=shed.back.qnt;   arr[5]=shed.frdm.qnt;
  consoleArr(arr,'E',4,'U',6);
  consoleBlank(10); 
  consoleVar(String(F("period->tick,quick,fast,slow,back,frdm(ms)=  1, 10, 25,250,100,loop()")),'E');
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							2. API console - PROGMEM output
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//							2.1. Вывод массивов с параметрами плат (из PROGMEM)
//=================================================================================================
void  consoleFromPGM()
{ 
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
//							2.2. Вывод доступных пинов (T-текст,D-число,A-текст/число];
//=================================================================================================
void  consolePinsAll()
{
//-------------------------------------------------------------------------------------------------
//						Определение временных переменных;
//-------------------------------------------------------------------------------------------------
#if !defined(RT_HM_COREM)				//==Если контроллер не многоядерный;
  uint8_t i;
#endif
//-------------------------------------------------------------------------------------------------
mess.alig='R'; mess.blank=' '; mess.modePin='T'; mess.modeAdr='A'; mess.qntBit=8; mess.signBit='1'; 
//-------------------------------------------------------------------------------------------------
  for(i=RT_HW_PGM_PIN_ALL_ID; i<=RT_HW_PGM_PIN_N5V_ID; i++){consoleArrPGM(i);}
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
{
#if !defined(RT_HM_COREM)				//==Если контроллер не многоядерный;
  uint8_t j,m;
  uint8_t chr;
  uint8_t bf8; 
  uint8_t arr[16];
#endif	
//-----------------------------	
  consoleHead(String(F("Name pins STM32")),'-',80);
  mess.modePin='A';
  for(m=0; m<12; m++){chr='A'+ m; bf8=0; 
   for(i=0; i<16; i++){arr[i]=getNumPinSTM32(chr,i); if(arr[i]<254){bf8=1;}}	
    if(bf8){consoleChar('P'); consoleChar(chr); consoleVar(String(F("[16]  ")));
     for(j=0; j<16; j++){      
	  consoleVar(arr[j],' ',9,'P'); 
		if((j==7) && (mess.modePin=='A')){consoleSuff('L'); consoleBlank(8);}
		if(j==15){consoleSuff('L');} 
  }}}
} 
#endif
//-------------------------------------------------------------------------------------------------
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								3. API console - тестовые пины
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//							3.1.Вывод тестовых пинов(ADC,PWM,Servo) и устройств на них(1-Wire,DHT22,HC-SR04)
//=================================================================================================
void  consolePinsTest()
{		
//-------------------------------------------------------------------------------------------------
//						Определение временных переменных;
//-------------------------------------------------------------------------------------------------
#if !defined(RT_HM_COREM)				//==Если контроллер не многоядерный;
  uint8_t arr[3];
  uint8_t i;
  uint8_t bf8; 
#endif
mess.alig='R'; mess.blank=' ';
//-------------------------------------------------------------------------------------------------
  arr[0]=vPinADC1(); arr[1]=vPinPWM1(); arr[2]=vPinServo1(); arr[3]=vPinServo2();
  bf8=0; for(i=0; i<2; i++){if(arr[i]!=255){bf8++;}}
  if(bf8)
  {
   consoleVar(String(F("Board pin->")));;
   if(arr[0]!=255){consoleTest(String(F(" ADC1")),  arr[0],';');}
   if(arr[1]!=255){consoleTest(String(F(" PWM1")),  arr[1],';');}
   if(arr[2]!=255){consoleTest(String(F(" Servo1")),arr[2],';');}
   consoleCR();
  }
//-------------------------------------------------------------------------------------------------
   arr[0]=vPinOneWire(); arr[1]=vPinDHT22();  arr[2]=vPinSR04();;
   bf8=0; for(i=0; i<=2; i++){if(arr[i]!=255){bf8++;}}
   if(bf8)
   {
	consoleVar(String(F("Device   ->"))); 
	if(arr[0]!=255){consoleTest(String(F(" 1-Wire")),       arr[0],';','P');}
	if(arr[1]!=255){consoleTest(String(F(" DHT-22")),	    arr[1],';','P');}
	if(arr[2]!=255){consoleTest(String(F(" HC-SR04.trig")), arr[2],';','P');}
	consoleCR();}
//-------------------------------------------------------------------------------------------------
};
//=================================================================================================
//							3.2. Вывод номеров UART для устройств
//=================================================================================================
void  consoleNumUART()
{
//-------------------------------------------------------------------------------------------------
//						Определение временных переменных;
//-------------------------------------------------------------------------------------------------
#if !defined(RT_HM_COREM)				//==Если контроллер не многоядерный;
  uint8_t arr[8];
  uint8_t i;
  uint8_t bf8; 
#endif
//-------------------------------------------------------------------------------------------------
  arr[0]=vUartConsole(); arr[1]=vUartModBus1();  arr[2]=vUartModBus2(); arr[3]=vUartNextion();
  arr[4]=vUartWiFi();    arr[5]=vUartNum5();     arr[6]=vUartNum6();    arr[7]=vUartNum7();  
  bf8=0; for(i=0; i<=7; i++){if(arr[i]!=255){bf8++;}}
if(bf8)
	{
	consoleVar(String(F("numUART  ->")));
    if(arr[0]!=255){if(arr[0]==210){consoleVar(String(F(" Console=USB")),';');}
				    else                {consoleTest(String(F(" Console")),   arr[0],';','U');}}
    if(arr[1]!=255){consoleTest(String(F(" Modbus.1")),  arr[1],';','U');}
    if(arr[2]!=255){consoleTest(String(F(" Modbus.2")),  arr[2],';','U');}				
    if(arr[3]!=255){consoleTest(String(F(" Nextion")),   arr[3],';','U');}    
	if(arr[4]!=255){consoleTest(String(F(" Wi-Fi")),     arr[4],';','U');}
    if(arr[5]!=255){consoleTest(String(F(" Ethernet.1")),arr[5],';','U');}
    if(arr[6]!=255){consoleTest(String(F(" Ethernet.2")),arr[6],';','U');}				
    if(arr[7]!=255){consoleTest(String(F(" Device")),    arr[7],';','U');}			
    consoleCR();
	}
//-------------------------------------------------------------------------------------------------
};				
//=================================================================================================
