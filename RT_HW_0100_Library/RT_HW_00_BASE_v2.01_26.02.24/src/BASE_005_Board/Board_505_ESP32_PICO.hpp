//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							1.Контроллер типа STAMP-PICO [m5stack_stamp_pico]
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if !defined(RT_HW_BOARD_SELECT) && defined(RT_HW_BOARD_STAMP_PICO)
#define RT_HW_BOARD_SELECT 						 "BOARD STAMP-PICO"	//--Идентификатор выбора платы;		
//-------------------------------------------------------------------------------------------------
#define RT_HW_BOARD_MEMORY  "FLASH=1310Kb; RAM=328Kb; Ext_FLASH=4/16Mb;"	//--Параметры памяти;												
#define RT_HW_PERMIT_UART0													//--Разрешение работы с UART0; 
#define RT_HW_PERMIT_UART1													//--Разрешение работы с UART1;
//#define RT_HW_PERMIT_UART2													//--Разрешение работы с UART2; 
#define RT_HW_PERMIT_I2C0													//--Разрешение работы с i2c0; 
#define RT_HW_PERMIT_SPI0													//--Разрешение работы с spi0 (clk=18,miso=19,mosi=23,cs=5); 
#define RT_HW_PERMIT_DAC													//--Разрешение работы с DAC;
#define RT_HW_PERMIT_WS														//--Разрешение работы с WS2812;
//------Системные пины-----------------------------------------------------------------------------
enum   {RT_HW_BOARD_CONTROL=255, RT_HW_BOARD_LED=27, RT_HW_BOARD_BUTTON=39, RT_HW_BOARD_WS=27};	//--Пины контроль,led,кнопка;
//------Параметры контроллера общие----------------------------------------------------------------	
enum   {RT_HW_PIN_QNT_MAX=13,	RT_HW_FCPU=160, 	RT_HW_VCC=3300}; 
//-----Параметры UART------------------------------------------------------------------------------	
enum   {RT_HW_UART0_RX=3,    RT_HW_UART0_TX=1, 
        RT_HW_UART1_RX=32,   RT_HW_UART1_TX=33,
		RT_HW_UART2_RX=255,  RT_HW_UART2_TX=255};
//enum   {RT_HW_UART0_RX=3,   RT_HW_UART0_TX=1, 
//		RT_HW_UART2_RX=25,   RT_HW_UART2_TX=21};
//-----Параметры I2C-------------------------------------------------------------------------------	
enum   {RT_HW_I2C0_SDA=26,  RT_HW_I2C0_SCL=32,  RT_HW_I2C0_MODE_FM=RT_HW_I2C_MODE_FM}; 	
//-----Параметры SPI-------------------------------------------------------------------------------	
enum   {RT_HW_SPI0_SCK=18,  RT_HW_SPI0_MISO=36, RT_HW_SPI0_MOSI=26, RT_HW_SPI0_SS=19};
//-----Системные параметры-------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_SYS_PAR[]  	={12,			   	RT_HW_PGM_END};  //--SYS->depth;
const uint8_t PROGMEM RT_HW_PGM_SYS_ADC[]  	={12,20,9,			RT_HW_PGM_END};  //--ADC->depth,drift,null;
const uint8_t PROGMEM RT_HW_PGM_SYS_TCH[]  	={8,  				RT_HW_PGM_END};  //--TCH->depth,drift,null; 
const uint8_t PROGMEM RT_HW_PGM_SYS_PWM[]  	={12,10,			RT_HW_PGM_END};  //--PWM->depth,freq; 
const uint8_t PROGMEM RT_HW_PGM_SYS_DAC[]  	={8,				RT_HW_PGM_END};  //--DAC->depth; 
//-----Системные пины и параметры коммуникаций------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_BRD[]	={RT_HW_BOARD_CONTROL, RT_HW_BOARD_LED, RT_HW_BOARD_BUTTON, RT_HW_BOARD_WS, RT_HW_PGM_END};  //--Пины->control,led,button,WS2812; 
const uint8_t PROGMEM RT_HW_PGM_PIN_I2C[] 	={RT_HW_I2C0_SDA, RT_HW_I2C0_SCL,  							RT_HW_PGM_END}; 
const uint8_t PROGMEM RT_HW_PGM_PIN_ICS[]	={	    													RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_SPI[] 	={RT_HW_SPI0_SCK, RT_HW_SPI0_MISO,  RT_HW_SPI0_MOSI, RT_HW_SPI0_SS, RT_HW_PGM_END};  
const uint8_t PROGMEM RT_HW_PGM_PIN_SPN[]	={ 															RT_HW_PGM_END}; 
//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_SPQ[]	={          					   RT_HW_PGM_END};  //--SPQ: sck,miso,mosi,cs;	
const uint8_t PROGMEM RT_HW_PGM_PIN_SDC[]	={          					   RT_HW_PGM_END};  //--SDIO: DO,D1,D2,D3,SCK;
//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_UHS[] 	={RT_HW_UART0_RX, RT_HW_UART0_TX, 
											  RT_HW_UART1_RX, RT_HW_UART1_TX,
											  RT_HW_UART2_RX, RT_HW_UART2_TX,   						RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_USS[] 	={				 					RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_CAN[] 	={				 		    		RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_BTH[] 	={'B','L','E',				 		RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_ETH[] 	={  								RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_WFI[] 	={192,  							RT_HW_PGM_END};
//=================================================================================================
#define RT_HW_BOARD_CHECK_PIN				//--Разрешение проверки на допустимость использования пинов [функции checkPinXXX(uint8_t pin)];
//-----Доступные пины контроллера------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_ALL[] 	={ 0, 1, 3, 18,19,21,22,25,26,32,33,36,	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DIN[] 	={ 0, 1, 3, 18,19,21,22,25,26,32,33,36,	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_ADC[] 	={							  32,33,36,	RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_TCH[] 	={ 								     	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DOT[] 	={ 0, 1, 3, 18,19,21,22,25,26,32,33,  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_PWM[] 	={             19,21,22,25,26,32,33,	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DAC[] 	={						25,26,			RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_INT[] 	={ 0, 1, 3, 18,19,21,22,25,26,32,33,36,	RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_N5V[] 	={ 0, 1, 3, 18,19,21,22,25,26,32,33,36,	RT_HW_PGM_END};	
//-----Тестовые пины и адреса------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_DBG[]  	={					RT_HW_PGM_END};	//--Пины debug1,debug2,debug3;	
const uint8_t PROGMEM RT_HW_PGM_PIN_OUT[] 	={255,255,27,		RT_HW_PGM_END};	//--Пины PWM0,PWM1,Servo1,Servo2;
const uint8_t PROGMEM RT_HW_PGM_PIN_INP[] 	={255,255,39,		RT_HW_PGM_END};	//--Пины A0,A1,btn1,btn2,TCH0,TCH1;
const uint8_t PROGMEM RT_HW_PGM_PIN_DCT[] 	={                  RT_HW_PGM_END};	//--Пины DAC0,DAC1;
const uint8_t PROGMEM RT_HW_PGM_PIN_DEV[] 	={  			    RT_HW_PGM_END};	//--Пины DS1820,DHT22,HC-SR04.trig;
const uint8_t PROGMEM RT_HW_PGM_PIN_CSS[] 	={33,21,25,			RT_HW_PGM_END};	//--Пины CS SPI:595,LCD,NRF,SD; 	
const uint8_t PROGMEM RT_HW_PGM_PIN_LC6[]  	={					RT_HW_PGM_END};	//--Пины для подключения LCD по 4-х битной шине;
const uint8_t PROGMEM RT_HW_PGM_PIN_TFT[]  	={					RT_HW_PGM_END};	//--Пины(дополнительные[]  TFT дисплея(SPI[] -CS,R/S,LED,RST;
const uint8_t PROGMEM RT_HW_PGM_PIN_URT[] 	={99, 1, 			RT_HW_PGM_END};	//--UART: ModBus, Nextion 	
const uint8_t PROGMEM RT_HW_PGM_ADR_I2C[]  	={39,62,32,33,		RT_HW_PGM_END};	// lcd1,lcd2,mcp1,mcp2;
//-------------------------------------------------------------------------------------------------
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


