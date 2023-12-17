//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							1.Контроллер типа ESP32 Dev module [esp32.variant]
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if !defined(RT_HW_BOARD_SELECT)  && defined(ARDUINO_ESP32S3_DEV)
#define      RT_HW_BOARD_SELECT 			"BOARD ESP32S3 DEV"				//--Идентификатор выбора платы;
//-------------------------------------------------------------------------------------------------
#define RT_HW_BOARD_MEMORY  "FLASH=1310Kb; RAM=328Kb; Ext_FLASH=4/16Mb;"	//--Параметры памяти;												
#define RT_HW_PERMIT_UART0													//--Разрешение работы с UART0; 
#define RT_HW_PERMIT_UART1													//--Разрешение работы с UART1; 
#define RT_HW_PERMIT_UART2													//--Разрешение работы с UART2; 
//#define RT_HW_PERMIT_UARTB													//--Разрешение работы с внутренним BlueTooth;
//#define RT_HW_PERMIT_UARTSPP												//--Разрешение работы с внутренним BlueTooth;
#define RT_HW_PERMIT_I2C0													//--Разрешение работы с i2c0; 
#define RT_HW_PERMIT_I2C1													//--Разрешение работы с i2c1; 
#define RT_HW_PERMIT_SPI0													//--Разрешение работы с spi0 (clk=18,miso=19,mosi=23,cs=5); 
//#define RT_HW_PERMIT_SPI1	//--!!! Проблемы с core ESP32??? - !!!			//--Разрешение работы с spi1 (clk=14,miso=12,mosi=13,ss=15); 
#define RT_HW_PERMIT_DAC													//--Разрешение работы с DAC;
#define RT_HW_PERMIT_WS														//--Разрешение работы с WS2812;
#define RT_HW_PERMIT_HALL													//--Разрешение работы с датчиком Холла; 
//------Системные пины------------------------------------------------------------------------------
enum   {RT_HW_BOARD_CONTROL=12, RT_HW_BOARD_LED=26, RT_HW_BOARD_BUTTON=34, RT_HW_BOARD_WS=255};	//--Пины контроль,led,кнопка;
//------Параметры контроллера общие-------------------------------------------------------------------	
enum   {RT_HW_PIN_QNT_MAX=40,	RT_HW_FCPU=240, 	RT_HW_VCC=3300}; 
//-----Параметры UART------------------------------------------------------------------------------	
enum   {RT_HW_UART0_RX=3,   RT_HW_UART0_TX=1,
		RT_HW_UART1_RX=14,  RT_HW_UART1_TX=27,
		RT_HW_UART2_RX=16,  RT_HW_UART2_TX=17};
//-----Параметры I2C------------------------------------------------------------------------------	
enum   {RT_HW_I2C0_SDA=21,  RT_HW_I2C0_SCL=22,  RT_HW_I2C1_SDA=33,  RT_HW_I2C1_SCL=32};  //--В действительности будет sda=32, scl=33;	
//-----Параметры SPI------------------------------------------------------------------------------	
enum   {RT_HW_SPI0_SCK=18,  RT_HW_SPI0_MISO=19, RT_HW_SPI0_MOSI=23, RT_HW_SPI0_SS=5};
//-----Системные параметры-------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_SYS_PAR[]  	={12,			   	RT_HW_PGM_END};  //--SYS->depth;
const uint8_t PROGMEM RT_HW_PGM_SYS_ADC[]  	={12,20,9,			RT_HW_PGM_END};  //--ADC->depth,drift,null;
const uint8_t PROGMEM RT_HW_PGM_SYS_TCH[]  	={8,  				RT_HW_PGM_END};  //--TCH->depth,drift,null; 
const uint8_t PROGMEM RT_HW_PGM_SYS_PWM[]  	={12,10,			RT_HW_PGM_END};  //--PWM->depth,freq; 
const uint8_t PROGMEM RT_HW_PGM_SYS_DAC[]  	={8,				RT_HW_PGM_END};  //--DAC->depth; 
//-----Системные пины и параметры коммуникаций------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_BRD[]	={RT_HW_BOARD_CONTROL, RT_HW_BOARD_LED, RT_HW_BOARD_BUTTON, RT_HW_BOARD_WS, RT_HW_PGM_END};  //--Пины->control,led,button,WS2812; 
const uint8_t PROGMEM RT_HW_PGM_PIN_I2C[] 	={RT_HW_I2C0_SDA, RT_HW_I2C0_SCL,  RT_HW_I2C1_SDA, RT_HW_I2C1_SCL,	RT_HW_PGM_END}; 
const uint8_t PROGMEM RT_HW_PGM_PIN_ICS[]	={	    												 			RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_SPI[] 	={RT_HW_SPI0_SCK, RT_HW_SPI0_MISO, RT_HW_SPI0_MOSI, RT_HW_SPI0_SS, 	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_SPN[]	={ 														 			RT_HW_PGM_END}; 
const uint8_t PROGMEM RT_HW_PGM_PIN_UHS[] 	={RT_HW_UART0_RX, RT_HW_UART0_TX,
											  RT_HW_UART1_RX, RT_HW_UART1_TX,
											  RT_HW_UART2_RX, RT_HW_UART2_TX,   RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_USS[] 	={				 					RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_CAN[] 	={				 		    		RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_BTH[] 	={'B','L','E',				 		RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_ETH[] 	={  								RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_WFI[] 	={192,  							RT_HW_PGM_END};
//=================================================================================================
#define RT_HW_BOARD_CHECK_PIN				//--Разрешение проверки на допустимость использования пинов [функции checkPinXXX(uint8_t pin)];
//-----Доступные пины контроллера------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_ALL[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,
										      20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,39,	 	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DIN[] 	={ 0, 1, 2, 3, 4, 5,12,13,14,15,16,17,18,19,
											  20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,39, 	  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_ADC[] 	={36,39,32,33,34,35, 	  		  							  	RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_TCH[] 	={ 4, 0, 2,15,13,12,14,27,33,32,							  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DOT[] 	={ 0, 1, 2, 3, 4, 5,12,13,14,15,16,17,18,19,
										      20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,				  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_PWM[] 	={ 0, 1, 2, 3, 4, 5,12,13,14,15,16,17,18,19,
										      20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,			 	  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DAC[] 	={25,26,													  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_INT[] 	={ 0, 1, 2, 3, 4, 5,12,13,14,15,16,17,18,19,
										      20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,39,     	RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_N5V[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,
										      20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,39,     	RT_HW_PGM_END};	
//-----Тестовые пины и адреса------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_DBG[]  	={13,  			    RT_HW_PGM_END};	//--Пины debug1,debug2,debug3;	
const uint8_t PROGMEM RT_HW_PGM_PIN_OUT[] 	={25,       		RT_HW_PGM_END};	//--Пины PWM0,PWM1,Servo1,Servo2;
const uint8_t PROGMEM RT_HW_PGM_PIN_INP[] 	={36, 39, 35,    	RT_HW_PGM_END};	//--Пины A0,A1,btn1,btn2,TCH0,TCH1;
const uint8_t PROGMEM RT_HW_PGM_PIN_DCT[] 	={25, 26,           RT_HW_PGM_END};	//--Пины DAC0,DAC1;
const uint8_t PROGMEM RT_HW_PGM_PIN_DEV[] 	={33,13,255, 32, 	RT_HW_PGM_END};	//--DS1820,DHT,HC-SR04(Echo,Trig);
const uint8_t PROGMEM RT_HW_PGM_PIN_CSS[] 	={ 5,  4, 15, 2,	RT_HW_PGM_END};	//--CS SPI:595,LCD,NRF,DEVl 	
const uint8_t PROGMEM RT_HW_PGM_PIN_LC6[]  	={					RT_HW_PGM_END};	// Пины для подключения LCD по 4-х битной шине;
const uint8_t PROGMEM RT_HW_PGM_PIN_TFT[]  	={0,26,32,33,255,	RT_HW_PGM_END};	//--Пины(дополнительные[]  TFT дисплея(SPI[] -CS,R/S,LED,RST,TOUCH;
const uint8_t PROGMEM RT_HW_PGM_PIN_URT[] 	={99, 2, 			RT_HW_PGM_END};	//--UART: ModBus, Nextion 	
const uint8_t PROGMEM RT_HW_PGM_ADR_I2C[]  	={39,62,32,33,		RT_HW_PGM_END};	// lcd1,lcd2,mcp1,mcp2;
//-------------------------------------------------------------------------------------------------
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							2.Контроллер типа ESP32 Dev module BlueTooth [esp32.variant]
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if !defined(RT_HW_BOARD_SELECT)  && defined(BOARD_BPI_PICO_W_S3)
#define      RT_HW_BOARD_SELECT 			"BOARD ESP32S3 BananaPi PicoW"	//--Идентификатор выбора платы;
//-------------------------------------------------------------------------------------------------
#define RT_HW_BOARD_MEMORY  "FLASH=1310Kb; RAM=328Kb; Ext_FLASH=4/16Mb;"	//--Параметры памяти;												
#define RT_HW_PERMIT_UART0													//--Разрешение работы с UART0; 
#define RT_HW_PERMIT_UART1													//--Разрешение работы с UART1; 
#define RT_HW_PERMIT_UART2													//--Разрешение работы с UART2; 
//#define RT_HW_PERMIT_UARTB													//--Разрешение работы с внутренним BlueTooth;
#define RT_HW_PERMIT_I2C0													//--Разрешение работы с i2c0; 
#define RT_HW_PERMIT_I2C1													//--Разрешение работы с i2c1; 
#define RT_HW_PERMIT_SPI0													//--Разрешение работы с spi0 (clk=18,miso=19,mosi=23,cs=5); 
//#define RT_HW_PERMIT_SPI1	//--!!! Проблемы с core ESP32??? - !!!			//--Разрешение работы с spi1 (clk=14,miso=12,mosi=13,ss=15); 
#define RT_HW_PERMIT_DAC													//--Разрешение работы с DAC;
#define RT_HW_PERMIT_WS														//--Разрешение работы с WS2812;
#define RT_HW_PERMIT_HALL													//--Разрешение работы с датчиком Холла; 
//------Системные пины------------------------------------------------------------------------------
enum   {RT_HW_BOARD_CONTROL=12, RT_HW_BOARD_LED=26, RT_HW_BOARD_BUTTON=34, RT_HW_BOARD_WS=255};	//--Пины контроль,led,кнопка;
//------Параметры контроллера общие-------------------------------------------------------------------	
enum   {RT_HW_PIN_QNT_MAX=40,	RT_HW_FCPU=240, 	RT_HW_VCC=3300}; 
//-----Параметры UART------------------------------------------------------------------------------	
enum   {RT_HW_UART0_RX=3,   RT_HW_UART0_TX=1,
		RT_HW_UART1_RX=14,  RT_HW_UART1_TX=27,
		RT_HW_UART2_RX=16,  RT_HW_UART2_TX=17};
//-----Параметры I2C------------------------------------------------------------------------------	
enum   {RT_HW_I2C0_SDA=21,  RT_HW_I2C0_SCL=22,  RT_HW_I2C1_SDA=33,  RT_HW_I2C1_SCL=32};  //--В действительности будет sda=32, scl=33;	
//-----Параметры SPI------------------------------------------------------------------------------	
enum   {RT_HW_SPI0_SCK=18,  RT_HW_SPI0_MISO=19, RT_HW_SPI0_MOSI=23, RT_HW_SPI0_SS=5};
//-----Системные параметры-------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_SYS_PAR[]  	={12,			   	RT_HW_PGM_END};  //--SYS->depth;
const uint8_t PROGMEM RT_HW_PGM_SYS_ADC[]  	={12,20,9,			RT_HW_PGM_END};  //--ADC->depth,drift,null;
const uint8_t PROGMEM RT_HW_PGM_SYS_TCH[]  	={8,  				RT_HW_PGM_END};  //--TCH->depth,drift,null; 
const uint8_t PROGMEM RT_HW_PGM_SYS_PWM[]  	={12,10,			RT_HW_PGM_END};  //--PWM->depth,freq; 
const uint8_t PROGMEM RT_HW_PGM_SYS_DAC[]  	={8,				RT_HW_PGM_END};  //--DAC->depth; 
//-----Системные пины и параметры коммуникаций------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_BRD[]	={RT_HW_BOARD_CONTROL, RT_HW_BOARD_LED, RT_HW_BOARD_BUTTON, RT_HW_BOARD_WS, RT_HW_PGM_END};  //--Пины->control,led,button,WS2812; 
const uint8_t PROGMEM RT_HW_PGM_PIN_I2C[] 	={RT_HW_I2C0_SDA, RT_HW_I2C0_SCL,  RT_HW_I2C1_SDA, RT_HW_I2C1_SCL,	RT_HW_PGM_END}; 
const uint8_t PROGMEM RT_HW_PGM_PIN_ICS[]	={	    												 			RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_SPI[] 	={RT_HW_SPI0_SCK, RT_HW_SPI0_MISO, RT_HW_SPI0_MOSI, RT_HW_SPI0_SS, 	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_SPN[]	={ 														 			RT_HW_PGM_END}; 
const uint8_t PROGMEM RT_HW_PGM_PIN_UHS[] 	={RT_HW_UART0_RX, RT_HW_UART0_TX,
											  RT_HW_UART1_RX, RT_HW_UART1_TX,
											  RT_HW_UART2_RX, RT_HW_UART2_TX,   RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_USS[] 	={				 					RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_CAN[] 	={				 		    		RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_BTH[] 	={'B','L','E',				 		RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_ETH[] 	={  								RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_WFI[] 	={192,  							RT_HW_PGM_END};
//-----Доступные пины контроллера------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_ALL[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,
										      20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,39,	 	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DIN[] 	={ 0, 1, 2, 3, 4, 5,12,13,14,15,16,17,18,19,
											  20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,39, 	  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_ADC[] 	={36,39,32,33,34,35, 	  		  							  	RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_TCH[] 	={ 4, 0, 2,15,13,12,14,27,33,32,							  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DOT[] 	={ 0, 1, 2, 3, 4, 5,12,13,14,15,16,17,18,19,
										      20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,				  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_PWM[] 	={ 0, 1, 2, 3, 4, 5,12,13,14,15,16,17,18,19,
										      20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,			 	  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DAC[] 	={25,26,													  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_INT[] 	={ 0, 1, 2, 3, 4, 5,12,13,14,15,16,17,18,19,
										      20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,39,     	RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_N5V[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,
										      20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,39,     	RT_HW_PGM_END};	
//-----Тестовые пины и адреса------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_DBG[]  	={13,  			    RT_HW_PGM_END};	//--debug1,debug2,debug3,timeDebug;	
const uint8_t PROGMEM RT_HW_PGM_PIN_OUT[] 	={25,       		RT_HW_PGM_END};	//--PWM0, PWM1, LED1,LED2;
const uint8_t PROGMEM RT_HW_PGM_PIN_INP[] 	={36, 39, 35,    	RT_HW_PGM_END};	//--Пины A0,A1,btn1,btn2,TCH0,TCH1;
const uint8_t PROGMEM RT_HW_PGM_PIN_DCT[] 	={25, 26,           RT_HW_PGM_END};	//--DAC0,DAC1,TCH0,TCH1;
const uint8_t PROGMEM RT_HW_PGM_PIN_DEV[] 	={33,13,255, 32, 	RT_HW_PGM_END};	//--DS1820,DHT,HC-SR04(Echo,Trig);
const uint8_t PROGMEM RT_HW_PGM_PIN_CSS[] 	={ 5,  4, 15, 2,	RT_HW_PGM_END};	//--CS SPI:595,LCD,NRF,DEVl 	
const uint8_t PROGMEM RT_HW_PGM_PIN_LC6[]  	={					RT_HW_PGM_END};	// Пины для подключения LCD по 4-х битной шине;
const uint8_t PROGMEM RT_HW_PGM_PIN_TFT[]  	={0,26,32,33,255,	RT_HW_PGM_END};	//--Пины(дополнительные[]  TFT дисплея(SPI[] -CS,R/S,LED,RST,TOUCH;
const uint8_t PROGMEM RT_HW_PGM_PIN_URT[] 	={99, 2, 			RT_HW_PGM_END};	//--UART: ModBus, Nextion 	
const uint8_t PROGMEM RT_HW_PGM_ADR_I2C[]  	={39,62,32,33,		RT_HW_PGM_END};	// lcd1,lcd2,mcp1,mcp2;
//-------------------------------------------------------------------------------------------------
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							3.Контроллер типа LOLIN32 [d32.variant]
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if !defined(RT_HW_BOARD_SELECT) && defined(RT_HW_BOARD_LOLIN_D32)
#define RT_HW_BOARD_SELECT 					     "BOARD LOLIN D32"			//--Идентификатор выбора платы
//-------------------------------------------------------------------------------------------------
#define RT_HW_BOARD_MEMORY  "FLASH=1310Kb; RAM=328Kb; Ext_FLASH=4/16Mb;"	//--Параметры памяти;												
#define RT_HW_PERMIT_UART0													//--Разрешение работы с UART0; 
#define RT_HW_PERMIT_UART1													//--Разрешение работы с UART1; 
#define RT_HW_PERMIT_UART2													//--Разрешение работы с UART2; 
#define RT_HW_PERMIT_I2C0													//--Разрешение работы с i2c0; 
#define RT_HW_PERMIT_I2C1													//--Разрешение работы с i2c1; 
#define RT_HW_PERMIT_SPI0													//--Разрешение работы с spi0 (clk=18,miso=19,mosi=23,cs=5);  
//#define RT_HW_PERMIT_SPI1	//--!!! Проблемы с core ESP32??? !!!			//--Разрешение работы с spi1 (clk=14,miso=12,mosi=13,ss=15); 
#define RT_HW_PERMIT_DAC													//--Разрешение работы с DAC;
#define RT_HW_PERMIT_WS														//--Разрешение работы с WS2812;
#define RT_HW_PERMIT_HALL													//--Разрешение работы с датчиком Холла; 
//------Системные пины------------------------------------------------------------------------------
enum   {RT_HW_BOARD_CONTROL=12, RT_HW_BOARD_LED=26, RT_HW_BOARD_BUTTON=34, RT_HW_BOARD_WS=255};	//--Пины контроль,led,кнопка;
//------Параметры контроллера общие----------------------------------------------------------------	
enum{RT_HW_PIN_QNT_MAX=40,	RT_HW_FCPU=240, 	RT_HW_VCC=3300}; 
//-----Параметры UART------------------------------------------------------------------------------	
enum   {RT_HW_UART0_RX=3,   RT_HW_UART0_TX=1,
		RT_HW_UART1_RX=33,  RT_HW_UART1_TX=32,
		RT_HW_UART2_RX=16,  RT_HW_UART2_TX=17};
//-----Параметры I2C------------------------------------------------------------------------------	
enum   {RT_HW_I2C0_SDA=21,  RT_HW_I2C0_SCL=22,  RT_HW_I2C1_SDA=33,  RT_HW_I2C1_SCL=32};  //--В действительности будет sda=32, scl=33;	
//-----Параметры SPI------------------------------------------------------------------------------	
enum   {RT_HW_SPI0_SCK=18, RT_HW_SPI0_MISO=19,  RT_HW_SPI0_MOSI=23, RT_HW_SPI0_SS=5,  
        RT_HW_SPI1_SCK=14, RT_HW_SPI1_MISO=12,  RT_HW_SPI1_MOSI=13, RT_HW_SPI1_SS=15};
//-----Системные параметры-------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_SYS_PAR[] 	={12,			   	RT_HW_PGM_END};  //--SYS->depth; 
const uint8_t PROGMEM RT_HW_PGM_SYS_ADC[] 	={12,20,9,			RT_HW_PGM_END};  //--ADC->depth,drift,null;
const uint8_t PROGMEM RT_HW_PGM_SYS_TCH[] 	={8,  				RT_HW_PGM_END};  //--TCH->depth,drift,null; 
const uint8_t PROGMEM RT_HW_PGM_SYS_PWM[] 	={12,10,			RT_HW_PGM_END};  //--PWM->depth,freq; 
const uint8_t PROGMEM RT_HW_PGM_SYS_DAC[] 	={8,				RT_HW_PGM_END};  //--DAC->depth; 
//-----Системные пины и параметры коммуникаций------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_BRD[]	={RT_HW_BOARD_CONTROL, RT_HW_BOARD_LED, RT_HW_BOARD_BUTTON, RT_HW_BOARD_WS, RT_HW_PGM_END};  //--Пины->control,led,button,WS2812; 
const uint8_t PROGMEM RT_HW_PGM_PIN_I2C[] 	={RT_HW_I2C0_SDA, RT_HW_I2C0_SCL,  RT_HW_I2C1_SDA, RT_HW_I2C1_SCL, 	RT_HW_PGM_END}; 
const uint8_t PROGMEM RT_HW_PGM_PIN_ICS[]	={	    														 	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_SPI[] 	={RT_HW_SPI0_SCK, RT_HW_SPI0_MISO, RT_HW_SPI0_MOSI, RT_HW_SPI0_SS, 	
											  RT_HW_SPI1_SCK, RT_HW_SPI1_MISO, RT_HW_SPI1_MOSI, RT_HW_SPI1_SS, 	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_SPN[]	={ 																	RT_HW_PGM_END};//--Пины SOFT SPI: sck,miso,mosi,ss; 
const uint8_t PROGMEM RT_HW_PGM_PIN_UHS[] 	={RT_HW_UART0_RX, RT_HW_UART0_TX, 
											  RT_HW_UART1_RX, RT_HW_UART1_TX,
											  RT_HW_UART2_RX, RT_HW_UART2_TX,   							    RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_USS[] 	={				 					RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_CAN[] 	={				 		    		RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_BTH[] 	={'B','L','E',				 		RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_ETH[] 	={  								RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_WFI[] 	={192,  							RT_HW_PGM_END};
//-----Доступные пины контроллера------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_ALL[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,
										      20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,39,		RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DIN[] 	={ 0, 1, 2, 3, 4, 5,12,13,14,15,16,17,18,19,
										      20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,39, 	  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_ADC[] 	={36,39,32,33,34,35, 	  		  							  	RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_TCH[] 	={ 4, 0, 2,15,13,12,14,27,33,32,							  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DOT[] 	={ 0, 1, 2, 3, 4, 5,12,13,14,15,16,17,18,19,
										      20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,				  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_PWM[] 	={ 0, 1, 2, 3, 4, 5,12,13,14,15,16,17,18,19,
										      20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,			 	  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DAC[] 	={25,26,													  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_INT[] 	={ 0, 1, 2, 3, 4, 5,12,13,14,15,16,17,18,19,
										      20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,39,     	RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_N5V[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,
										      20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,39,     	RT_HW_PGM_END};	
//-----Тестовые пины и адреса------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_DBG[]  	={13,  			    RT_HW_PGM_END};	//--debug1,debug2,debug3,timeDebug;	
const uint8_t PROGMEM RT_HW_PGM_PIN_OUT[] 	={25,       		RT_HW_PGM_END};	//--PWM0, PWM1, LED1,LED2;
const uint8_t PROGMEM RT_HW_PGM_PIN_INP[] 	={36, 39, 35,    	RT_HW_PGM_END};	//--Пины A0,A1,btn1,btn2,TCH0,TCH1;
const uint8_t PROGMEM RT_HW_PGM_PIN_DCT[] 	={25, 26,           RT_HW_PGM_END};	//--DAC0,DAC1,TCH0,TCH1;
const uint8_t PROGMEM RT_HW_PGM_PIN_DEV[] 	={33,13,255, 32, 	RT_HW_PGM_END};	//--DS1820,DHT,HC-SR04(Echo,Trig);
const uint8_t PROGMEM RT_HW_PGM_PIN_CSS[] 	={ 5,  4, 15, 2,	RT_HW_PGM_END};	//--CS SPI:595,LCD,NRF,DEVl 	
const uint8_t PROGMEM RT_HW_PGM_PIN_LC6[]  	={					RT_HW_PGM_END};	// Пины для подключения LCD по 4-х битной шине;
const uint8_t PROGMEM RT_HW_PGM_PIN_TFT[]  	={0,26,32,33,255,	RT_HW_PGM_END};	//--Пины(дополнительные[]  TFT дисплея(SPI[] -CS,R/S,LED,RST,TOUCH;
const uint8_t PROGMEM RT_HW_PGM_PIN_URT[] 	={99, 2, 			RT_HW_PGM_END};	//--UART: ModBus, Nextion 	
const uint8_t PROGMEM RT_HW_PGM_ADR_I2C[]  	={39,62,32,33,		RT_HW_PGM_END};	// lcd1,lcd2,mcp1,mcp2;
//-------------------------------------------------------------------------------------------------
#endif

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							4.Контроллер типа WEMOS D1MIMI ESP32 [d1_mini32.variant]
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if !defined(RT_HW_BOARD_SELECT) && defined(RT_HW_BOARD_D1_MINI32)
#define RT_HW_BOARD_SELECT 						 "BOARD_D1_MINI32"			//--Идентификатор выбора платы;
//-------------------------------------------------------------------------------------------------
#define RT_HW_BOARD_MEMORY  "FLASH=1310Kb; RAM=328Kb; Ext_FLASH=4/16Mb;"	//--Параметры памяти;													
#define RT_HW_PERMIT_UART0													//--Разрешение работы с UART0; 
#define RT_HW_PERMIT_UART1													//--Разрешение работы с UART1; 
#define RT_HW_PERMIT_UART2													//--Разрешение работы с UART2; 
#define RT_HW_PERMIT_I2C0													//--Разрешение работы с i2c0; 
#define RT_HW_PERMIT_I2C1													//--Разрешение работы с i2c1; 
#define RT_HW_PERMIT_SPI0													//--Разрешение работы с spi0 (clk=18,miso=19,mosi=23,cs=5);  
//#define RT_HW_PERMIT_SPI1	//--!!! Проблемы с core ESP32??? !!!			//--Разрешение работы с spi1 (clk=14,miso=12,mosi=13,ss=15); 
#define RT_HW_PERMIT_DAC													//--Разрешение работы с DAC;
#define RT_HW_PERMIT_WS														//--Разрешение работы с WS2812;
#define RT_HW_PERMIT_HALL													//--Разрешение работы с датчиком Холла; 
//=================================================================================================										 
//------Системные пины------------------------------------------------------------------------------
enum    {RT_HW_BOARD_CONTROL=12, RT_HW_BOARD_LED=26, RT_HW_BOARD_BUTTON=34, RT_HW_BOARD_WS=255};	//--Пины контроль,led,кнопка;
//------Параметры контроллера общие-------------------------------------------------------------------	
enum{RT_HW_PIN_QNT_MAX=40,	RT_HW_FCPU=240, 	RT_HW_VCC=3300}; 
//-----Параметры UART------------------------------------------------------------------------------	
enum   {RT_HW_UART0_RX=3,   RT_HW_UART0_TX=1,
		RT_HW_UART1_RX=33,  RT_HW_UART1_TX=32,
		RT_HW_UART2_RX=16,  RT_HW_UART2_TX=17};
//-----Параметры I2C------------------------------------------------------------------------------	
enum   {RT_HW_I2C0_SDA=21,  RT_HW_I2C0_SCL=22,  RT_HW_I2C1_SDA=33,  RT_HW_I2C1_SCL=32};  //--В действительности будет sda=32, scl=33;	
//-----Параметры SPI------------------------------------------------------------------------------	
enum   {RT_HW_SPI0_SCK=18,  RT_HW_SPI0_MISO=19, RT_HW_SPI0_MOSI=23, RT_HW_SPI0_SS=5,  
        RT_HW_SPI1_SCK=14,  RT_HW_SPI1_MISO=12, RT_HW_SPI1_MOSI=13, RT_HW_SPI1_SS=15};
//-----Системные параметры-------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_SYS_PAR[]  	={12,			   	RT_HW_PGM_END};  //--SYS->depth; 
const uint8_t PROGMEM RT_HW_PGM_SYS_ADC[]  	={12,20,9,			RT_HW_PGM_END};  //--ADC->depth,drift,null;
const uint8_t PROGMEM RT_HW_PGM_SYS_TCH[]  	={8,  				RT_HW_PGM_END};  //--TCH->depth,drift,null; 
const uint8_t PROGMEM RT_HW_PGM_SYS_PWM[]  	={12,10,			RT_HW_PGM_END};  //--PWM->depth,freq; 
const uint8_t PROGMEM RT_HW_PGM_SYS_DAC[]  	={8,				RT_HW_PGM_END};  //--DAC->depth; 
//-----Системные пины и параметры коммуникаций------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_BRD[]	={RT_HW_BOARD_CONTROL, RT_HW_BOARD_LED, RT_HW_BOARD_BUTTON, RT_HW_BOARD_WS, RT_HW_PGM_END};  //--Пины->control,led,button,WS2812; 
const uint8_t PROGMEM RT_HW_PGM_PIN_I2C[] 	={RT_HW_I2C0_SDA, RT_HW_I2C0_SCL,  RT_HW_I2C1_SDA, RT_HW_I2C1_SCL, 	RT_HW_PGM_END}; 
const uint8_t PROGMEM RT_HW_PGM_PIN_ICS[]	={	    															RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_SPI[] 	={RT_HW_SPI0_SCK, RT_HW_SPI0_MISO, RT_HW_SPI0_MOSI, RT_HW_SPI0_SS, 	
											  RT_HW_SPI1_SCK, RT_HW_SPI1_MISO, RT_HW_SPI1_MOSI, RT_HW_SPI1_SS,	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_SPN[]	={ 																	RT_HW_PGM_END}; 
const uint8_t PROGMEM RT_HW_PGM_PIN_UHS[] 	={RT_HW_UART0_RX, RT_HW_UART0_TX,
											  RT_HW_UART1_RX, RT_HW_UART1_TX,
										      RT_HW_UART2_RX, RT_HW_UART2_TX,   RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_USS[] 	={				 					RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_CAN[] 	={				 		    		RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_BTH[] 	={'B','L','E',				 		RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_ETH[] 	={  								RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_WFI[] 	={192,  							RT_HW_PGM_END};
//-----Доступные пины контроллера------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_ALL[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,
										      20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,39,		RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DIN[] 	={ 0, 1, 2, 3, 4, 5,12,13,14,15,16,17,18,19,
										      20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,39, 	  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_ADC[] 	={36,39,32,33,34,35, 	  		  							  	RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_TCH[] 	={ 4, 0, 2,15,13,12,14,27,33,32,							  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DOT[] 	={ 0, 1, 2, 3, 4, 5,12,13,14,15,16,17,18,19,
										      20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,				  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_PWM[] 	={ 0, 1, 2, 3, 4, 5,12,13,14,15,16,17,18,19,
										      20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,			 	  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DAC[] 	={25,26,													  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_INT[] 	={ 0, 1, 2, 3, 4, 5,12,13,14,15,16,17,18,19,
										      20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,39,     	RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_N5V[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,
										      20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,39,     	RT_HW_PGM_END};	
//-----Тестовые пины и адреса------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_DBG[]  	={13,  			    RT_HW_PGM_END};	//--debug1,debug2,debug3,timeDebug;	
const uint8_t PROGMEM RT_HW_PGM_PIN_OUT[] 	={25,       		RT_HW_PGM_END};	//--PWM0, PWM1, LED1,LED2;
const uint8_t PROGMEM RT_HW_PGM_PIN_INP[] 	={36, 39, 35,    	RT_HW_PGM_END};	//--Пины A0,A1,btn1,btn2,TCH0,TCH1;
const uint8_t PROGMEM RT_HW_PGM_PIN_DCT[] 	={25, 26,           RT_HW_PGM_END};	//--DAC0,DAC1,TCH0,TCH1;
const uint8_t PROGMEM RT_HW_PGM_PIN_DEV[] 	={33,13,255, 32, 	RT_HW_PGM_END};	//--DS1820,DHT,HC-SR04(Echo,Trig);
const uint8_t PROGMEM RT_HW_PGM_PIN_CSS[] 	={ 5,  4, 15, 2,	RT_HW_PGM_END};	//--CS SPI:595,LCD,NRF,DEVl 	
const uint8_t PROGMEM RT_HW_PGM_PIN_LC6[]  	={					RT_HW_PGM_END};	//--Пины для подключения LCD по 4-х битной шине;
const uint8_t PROGMEM RT_HW_PGM_PIN_TFT[]  	={0,26,32,33,255,	RT_HW_PGM_END};	//--Пины(дополнительные[]  TFT дисплея(SPI[] -CS,R/S,LED,RST,TOUCH;
const uint8_t PROGMEM RT_HW_PGM_PIN_URT[] 	={99, 2, 			RT_HW_PGM_END};	//--UART: ModBus, Nextion 	
const uint8_t PROGMEM RT_HW_PGM_ADR_I2C[]  	={39,62,32,33,		RT_HW_PGM_END};	//--lcd1,lcd2,mcp1,mcp2;
//-------------------------------------------------------------------------------------------------
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							9.Контроллер типа ESP32 Unknow [esp32.variant]
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if !defined(RT_HW_BOARD_SELECT)  && defined(RT_HW_BOARD_ESP32_UNKNOW)
#define      RT_HW_BOARD_SELECT 			"Board ESP32 Unknow [near ESP32 Dev]"				//--Идентификатор выбора платы;
//-------------------------------------------------------------------------------------------------
#define RT_HW_BOARD_MEMORY  "FLASH=1310Kb; RAM=328Kb; Ext_FLASH=4/16Mb;"	//--Параметры памяти;												
#define RT_HW_PERMIT_UART0													//--Разрешение работы с UART0; 
//#define RT_HW_PERMIT_UART1													//--Разрешение работы с UART1; 
//#define RT_HW_PERMIT_UART2													//--Разрешение работы с UART2; 
//#define RT_HW_PERMIT_I2C0													//--Разрешение работы с i2c0; 
//#define RT_HW_PERMIT_I2C1													//--Разрешение работы с i2c1; 
//#define RT_HW_PERMIT_SPI0													//--Разрешение работы с spi0 (clk=18,miso=19,mosi=23,cs=5); 
//#define RT_HW_PERMIT_SPI1	//--!!! Проблемы с core ESP32??? - !!!			//--Разрешение работы с spi1 (clk=14,miso=12,mosi=13,ss=15); 
#define RT_HW_PERMIT_DAC													//--Разрешение работы с DAC;
#define RT_HW_PERMIT_HALL													//--Разрешение работы с датчикаом Холла; 
//------Системные пины------------------------------------------------------------------------------
enum   {RT_HW_BOARD_CONTROL=12, RT_HW_BOARD_LED=26, RT_HW_BOARD_BUTTON=34, RT_HW_BOARD_WS=255};	//--Пины контроль,led,кнопка;
//------Параметры контроллера общие-------------------------------------------------------------------	
enum   {RT_HW_PIN_QNT_MAX=40,	RT_HW_FCPU=240, 	RT_HW_VCC=3300}; 
//-----Параметры UART------------------------------------------------------------------------------	
enum   {RT_HW_UART0_RX=3,   RT_HW_UART0_TX=1,
		RT_HW_UART1_RX=33,  RT_HW_UART1_TX=32,
		RT_HW_UART2_RX=16,  RT_HW_UART2_TX=17};
//-----Параметры I2C------------------------------------------------------------------------------	
enum   {RT_HW_I2C0_SDA=21,  RT_HW_I2C0_SCL=22,  RT_HW_I2C1_SDA=33,  RT_HW_I2C1_SCL=32};  //--В действительности будет sda=32, scl=33;	
//-----Параметры SPI------------------------------------------------------------------------------	
enum   {RT_HW_SPI0_SCK=18,  RT_HW_SPI0_MISO=19, RT_HW_SPI0_MOSI=23, RT_HW_SPI0_SS=5,  
        RT_HW_SPI1_SCK=14,  RT_HW_SPI1_MISO=12, RT_HW_SPI1_MOSI=13, RT_HW_SPI1_SS=15};
//-----Системные параметры-------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_SYS_PAR[]  	={12,			   	RT_HW_PGM_END};  //--SYS->depth;
const uint8_t PROGMEM RT_HW_PGM_SYS_ADC[]  	={12,20,9,			RT_HW_PGM_END};  //--ADC->depth,drift,null;
const uint8_t PROGMEM RT_HW_PGM_SYS_TCH[]  	={8,  				RT_HW_PGM_END};  //--TCH->depth,drift,null; 
const uint8_t PROGMEM RT_HW_PGM_SYS_PWM[]  	={12,10,			RT_HW_PGM_END};  //--PWM->depth,freq; 
const uint8_t PROGMEM RT_HW_PGM_SYS_DAC[]  	={8,				RT_HW_PGM_END};  //--DAC->depth; 
//-----Системные пины и параметры коммуникаций------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_BRD[]	={RT_HW_BOARD_CONTROL, RT_HW_BOARD_LED, RT_HW_BOARD_BUTTON, RT_HW_BOARD_WS, RT_HW_PGM_END};  //--Пины->control,led,button,WS2812; 
const uint8_t PROGMEM RT_HW_PGM_PIN_I2C[] 	={RT_HW_I2C0_SDA, RT_HW_I2C0_SCL,  RT_HW_I2C1_SDA, RT_HW_I2C1_SCL, RT_HW_PGM_END}; 
const uint8_t PROGMEM RT_HW_PGM_PIN_ICS[]	={	    												 RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_SPI[] 	={RT_HW_SPI0_SCK, RT_HW_SPI0_MISO, RT_HW_SPI0_MOSI, RT_HW_SPI0_SS, 	
											  RT_HW_SPI1_SCK, RT_HW_SPI1_MISO, RT_HW_SPI1_MOSI, RT_HW_SPI1_SS,	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_SPN[]	={ 														 RT_HW_PGM_END}; 
const uint8_t PROGMEM RT_HW_PGM_PIN_UHS[] 	={RT_HW_UART0_RX, RT_HW_UART0_TX,
											  RT_HW_UART1_RX, RT_HW_UART1_TX,
											  RT_HW_UART2_RX, RT_HW_UART2_TX,   RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_USS[] 	={				 					RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_CAN[] 	={				 		    		RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_BTH[] 	={'B','L','E',				 		RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_ETH[] 	={  								RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_WFI[] 	={192,  							RT_HW_PGM_END};
//-----Доступные пины контроллера------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_ALL[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,
										      20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,39,	 	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DIN[] 	={ 0, 1, 2, 3, 4, 5,12,13,14,15,16,17,18,19,
											  20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,39, 	  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_ADC[] 	={36,39,32,33,34,35, 	  		  							  	RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_TCH[] 	={ 4, 0, 2,15,13,12,14,27,33,32,							  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DOT[] 	={ 0, 1, 2, 3, 4, 5,12,13,14,15,16,17,18,19,
										      20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,				  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_PWM[] 	={ 0, 1, 2, 3, 4, 5,12,13,14,15,16,17,18,19,
										      20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,			 	  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DAC[] 	={25,26,													  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_INT[] 	={ 0, 1, 2, 3, 4, 5,12,13,14,15,16,17,18,19,
										      20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,39,     	RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_N5V[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,
										      20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,39,     	RT_HW_PGM_END};	
//-----Тестовые пины и адреса------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_DBG[]  	={13,  			    RT_HW_PGM_END};	//--debug1,debug2,debug3,timeDebug;	
const uint8_t PROGMEM RT_HW_PGM_PIN_OUT[] 	={25,       		RT_HW_PGM_END};	//--PWM0, PWM1, LED1,LED2;
const uint8_t PROGMEM RT_HW_PGM_PIN_INP[] 	={36, 39, 35,    	RT_HW_PGM_END};	//--A0,A1,btn1,btn2;
const uint8_t PROGMEM RT_HW_PGM_PIN_DCT[] 	={25, 26,           RT_HW_PGM_END};	//--DAC0,DAC1,TCH0,TCH1;
const uint8_t PROGMEM RT_HW_PGM_PIN_DEV[] 	={33,13,255, 32, 	RT_HW_PGM_END};	//--DS1820,DHT,HC-SR04(Echo,Trig);
const uint8_t PROGMEM RT_HW_PGM_PIN_CSS[] 	={ 5,  4, 15, 2,	RT_HW_PGM_END};	//--CS SPI:595,LCD,NRF,DEVl 	
const uint8_t PROGMEM RT_HW_PGM_PIN_LC6[]  	={					RT_HW_PGM_END};	// Пины для подключения LCD по 4-х битной шине;
const uint8_t PROGMEM RT_HW_PGM_PIN_TFT[]  	={0,26,32,33,255,	RT_HW_PGM_END};	//--Пины(дополнительные[]  TFT дисплея(SPI[] -CS,R/S,LED,RST,TOUCH;
const uint8_t PROGMEM RT_HW_PGM_PIN_URT[] 	={99, 2, 			RT_HW_PGM_END};	//--UART: ModBus, Nextion 	
const uint8_t PROGMEM RT_HW_PGM_ADR_I2C[]  	={39,62,32,33,		RT_HW_PGM_END};	// lcd1,lcd2,mcp1,mcp2;
//-------------------------------------------------------------------------------------------------
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							5.Контроллер типа ESP32 TTGO T-Display   [ttgo-t1/variant (подобранный аналог[] ]
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if !defined(RT_HW_BOARD_SELECT) && defined(RT_HW_BOARD_TTGO_T1)
#define       RT_HW_BOARD_SELECT 			     "BOARD TTGO T-Display"		//--Идентификатор выбора платы
//-------------------------------------------------------------------------------------------------
#define RT_HW_BOARD_MEMORY  "FLASH=1310Kb; RAM=328Kb; Ext_FLASH=4/16Mb;"	//--Параметры памяти;												
#define RT_HW_PERMIT_UART0													//--Разрешение работы с UART0; 
#define RT_HW_PERMIT_UART1													//--Разрешение работы с UART1; 
#define RT_HW_PERMIT_UART2													//--Разрешение работы с UART2; 
#define RT_HW_PERMIT_I2C0													//--Разрешение работы с i2c0; 
#define RT_HW_PERMIT_SPI0													//--Разрешение работы с spi0 (clk=18,miso=19,mosi=23,cs=5);
//#define RT_HW_PERMIT_SPI1	//--!!! Проблемы с core ESP32??? - !!!			//--Разрешение работы с spi1 (clk=14,miso=12,mosi=13,ss=15);
#define RT_HW_PERMIT_DAC													//--Разрешение работы с DAC;
#define RT_HW_PERMIT_WS														//--Разрешение работы с WS2812;
#define RT_HW_PERMIT_HALL													//--Разрешение работы с датчиком Холла; 
//------Системные пины------------------------------------------------------------------------------
enum    {RT_HW_BOARD_CONTROL=12, RT_HW_BOARD_LED=5, RT_HW_BOARD_BUTTON=34, RT_HW_BOARD_WS=255};	//--Пины контроль,led,кнопка;
//------Параметры контроллера общие-------------------------------------------------------------------	
enum   {RT_HW_PIN_QNT_MAX=40,	RT_HW_FCPU=240, 	RT_HW_VCC=3300}; 
//-----Параметры UART------------------------------------------------------------------------------	
enum   {RT_HW_UART0_RX=3,   RT_HW_UART0_TX=1,
		RT_HW_UART1_RX=33,  RT_HW_UART1_TX=32,
		RT_HW_UART2_RX=16,  RT_HW_UART2_TX=17};
//-----Параметры I2C------------------------------------------------------------------------------	
enum   {RT_HW_I2C0_SDA=21,  RT_HW_I2C0_SCL=22,  RT_HW_I2C0_MODE_FM=RT_HW_I2C_MODE_FM}; 	
//-----Параметры SPI------------------------------------------------------------------------------	
enum   {RT_HW_SPI0_SCK=18,  RT_HW_SPI0_MISO=19, RT_HW_SPI0_MOSI=23, RT_HW_SPI0_SS=255};
//-----Системные параметры-------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_SYS_PAR[]  	={12,			   	RT_HW_PGM_END};  //--SYS->depth;
const uint8_t PROGMEM RT_HW_PGM_SYS_ADC[]  	={12,20,9,			RT_HW_PGM_END};  //--ADC->depth,drift,null;
const uint8_t PROGMEM RT_HW_PGM_SYS_TCH[]  	={8,  				RT_HW_PGM_END};  //--TCH->depth,drift,null; 
const uint8_t PROGMEM RT_HW_PGM_SYS_PWM[]  	={12,10,			RT_HW_PGM_END};  //--PWM->depth,freq; 
const uint8_t PROGMEM RT_HW_PGM_SYS_DAC[]  	={8,				RT_HW_PGM_END};  //--DAC->depth; 
//-----Системные пины и параметры коммуникаций------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_BRD[]	={RT_HW_BOARD_CONTROL, RT_HW_BOARD_LED, RT_HW_BOARD_BUTTON, RT_HW_BOARD_WS, RT_HW_PGM_END};  //--Пины->control,led,button,WS2812; 
const uint8_t PROGMEM RT_HW_PGM_PIN_I2C[] 	={RT_HW_I2C0_SDA,  RT_HW_I2C0_SCL,  RT_HW_PGM_END}; 
const uint8_t PROGMEM RT_HW_PGM_PIN_ICS[]	={	    													RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_SPI[] 	={RT_HW_SPI0_SCK,  RT_HW_SPI0_MISO, RT_HW_SPI0_MOSI, RT_HW_SPI0_SS,	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_SPN[]	={ 														 	RT_HW_PGM_END}; 
const uint8_t PROGMEM RT_HW_PGM_PIN_UHS[] 	={RT_HW_UART0_RX, RT_HW_UART0_TX,  						
											  RT_HW_UART1_RX, RT_HW_UART1_TX,
											  RT_HW_UART2_RX, RT_HW_UART2_TX,							RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_USS[] 	={				 											RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_CAN[] 	={				 		    		RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_BTH[] 	={'B','L','E',				 		RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_ETH[] 	={  								RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_WFI[] 	={192,  							RT_HW_PGM_END};
//-----Доступные пины контроллера------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_ALL[] 	={ 0, 2, 5,12,   14,15,16,17,18,19,21,22,25,26,27,32,33,35,36,37,38,39,RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DIN[] 	={ 0, 2, 5,12,   14,15,16,17,18,19,21,22,25,26,27,32,33,35,36,37,38,39,RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_ADC[] 	={ 0,36,39,32,33, 2,15,14,12,27,25,26,                                 RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_TCH[] 	={ 0, 2,15,14,12,14,27,33,32,	                                       RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DOT[] 	={ 0, 2, 5,12,13,14,15,16,17,18,19,21,22,25,26,27,32,33,	           RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_PWM[] 	={ 0, 2, 5,12,13,14,15,16,17,18,19,21,22,25,26,27,32,33,	           RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DAC[] 	={25,26,												               RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_INT[] 	={ 0, 2, 5,12,13,14,15,16,17,18,19,21,22,25,26,27,32,33,35,            RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_N5V[] 	={ 0, 2, 5,12,13,14,15,16,17,18,19,21,22,25,26,27,32,33,35,36,37,38,39,RT_HW_PGM_END};	
//-----Тестовые пины и адреса------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_DBG[] 	={15,4,  	  	    RT_HW_PGM_END};	//--debug1,debug2,debug3;	
const uint8_t PROGMEM RT_HW_PGM_PIN_OUT[] 	={			  		RT_HW_PGM_END};	//--PWM0, PWM1, led, dev;
const uint8_t PROGMEM RT_HW_PGM_PIN_INP[] 	={36,255, 0,35,		RT_HW_PGM_END};	//--A0,A1,btn1,btn2;
const uint8_t PROGMEM RT_HW_PGM_PIN_DCT[] 	={25,26,            RT_HW_PGM_END};	//--DAC0,DAC1,TCH0;
const uint8_t PROGMEM RT_HW_PGM_PIN_DEV[] 	={				 	RT_HW_PGM_END};	//--DS1820,DHT,HC-SR04(Echo,Trig);
const uint8_t PROGMEM RT_HW_PGM_PIN_CSS[] 	={			 	    RT_HW_PGM_END};	//--CS SPI:595,LCD,NRF,DEVl 	
const uint8_t PROGMEM RT_HW_PGM_PIN_LC6[]  	={					RT_HW_PGM_END};	//--Пины для подключения LCD по 4-х битной шине;
const uint8_t PROGMEM RT_HW_PGM_PIN_TFT[]   ={5,16,14,23,		RT_HW_PGM_END};	//--Пины(дополнительные[]  TFT дисплея(SPI[] -CS,R/S,LED,RST;
const uint8_t PROGMEM RT_HW_PGM_PIN_URT[] 	={99, 2, 			RT_HW_PGM_END};	//--UART: ModBus, Nextion 		
const uint8_t PROGMEM RT_HW_PGM_ADR_I2C[]  	={39,62,32,33,		RT_HW_PGM_END};	//--lcd1,lcd2,mcp1,mcp2;
//-------------------------------------------------------------------------------------------------
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
