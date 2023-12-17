//*************************************************************************************************
//							1.Контроллеры тип Seeeduino XIAO M0 [XIAO_m0.variant]
//*************************************************************************************************
#if !defined(RT_HW_BOARD_SELECT) && defined(RT_HW_BOARD_SEEED_XIAO_M0)	
#define      RT_HW_BOARD_SELECT 		    "BOARD SEEED XIAO M"		//--Идентификатор выбора платы;
#define RT_HW_BOARD_MEMORY   "FLASH=256Kb; RAM=32Kb;"					//--Параметры памяти;
#define RT_HW_PERMIT_UART0
#define RT_HW_PERMIT_UART1
#define RT_HW_PERMIT_I2C0	
#define RT_HW_PERMIT_SPI0
#define RT_HW_PERMIT_DAC												//--Разрешение работы с DAC;
//=================================================================================================
//------Системные пины------------------------------------------------------------------------------
enum   {RT_HW_BOARD_CONTROL=3, RT_HW_BOARD_LED=13, RT_HW_BOARD_BUTTON=255, RT_HW_BOARD_WS=255};	//--Пины контроль,led,кнопка;
//------Параметры контроллера общие-------------------------------------------------------------------	
enum{RT_HW_PIN_QNT_MAX=14, RT_HW_FCPU=48, 	  RT_HW_VCC=3300};
//-----Параметры UART------------------------------------------------------------------------------	
enum   {RT_HW_UART0_RX=255, RT_HW_UART0_TX=255, RT_HW_UART1_RX=7,  RT_HW_UART1_TX=6};
//-----Параметры I2C------------------------------------------------------------------------------	
enum   {RT_HW_I2C0_SDA=4,  RT_HW_I2C0_SCL=5,  RT_HW_I2C0_MODE_FM=RT_HW_I2C_MODE_FM}; 
//-----Параметры SPI------------------------------------------------------------------------------	
enum   {RT_HW_SPI0_SCK=8,  RT_HW_SPI0_MISO=9, RT_HW_SPI0_MOSI=10, RT_HW_SPI0_SS=255};
//-----Системные параметры-------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_SYS_PAR[]   ={12,			   	RT_HW_PGM_END};  //--SYS->depth;
const uint8_t PROGMEM RT_HW_PGM_SYS_ADC[]	={12,15,10,			RT_HW_PGM_END};  //--ADC->depth,drift,null;
const uint8_t PROGMEM RT_HW_PGM_SYS_TCH[]  	={  				RT_HW_PGM_END};  //--TCH->depth,drift,null; 
const uint8_t PROGMEM RT_HW_PGM_SYS_PWM[]  	={12,10,			RT_HW_PGM_END};  //--PWM->depth,freq; 
const uint8_t PROGMEM RT_HW_PGM_SYS_DAC[]  	={10,				RT_HW_PGM_END};  //--DAC->depth; 
//-----Системные пины и параметры коммуникаций------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_BRD[] 	={RT_HW_BOARD_CONTROL, RT_HW_BOARD_LED, RT_HW_BOARD_BUTTON, RT_HW_BOARD_WS, RT_HW_PGM_END};  //--Пины->control,led,button,WS2812; 
const uint8_t PROGMEM RT_HW_PGM_PIN_I2C[] 	={RT_HW_I2C0_SDA,   RT_HW_I2C0_SCL,	    			                  RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_ICS[]	={	    															  RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_SPI[] 	={RT_HW_SPI0_SCK,   RT_HW_SPI0_MISO, RT_HW_SPI0_MOSI, RT_HW_SPI0_SS,  RT_HW_PGM_END}; 
const uint8_t PROGMEM RT_HW_PGM_PIN_SPN[]	={ 																	  RT_HW_PGM_END}; 
//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_SPQ[]	={			         			    RT_HW_PGM_END};  //--SPQ: sck,miso,mosi,cs;	
const uint8_t PROGMEM RT_HW_PGM_PIN_SDC[]	={                                  RT_HW_PGM_END};  //--SDIO: DO,D1,D2,D3,SCK;	
//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_UHS[] 	={RT_HW_UART0_RX,   RT_HW_UART0_TX,	 RT_HW_UART1_RX,  RT_HW_UART1_TX, RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_USS[] 	={					RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_CAN[] 	={					RT_HW_PGM_END};		
const uint8_t PROGMEM RT_HW_PGM_PIN_BTH[] 	={					RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_ETH[] 	={					RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_WFI[] 	={					RT_HW_PGM_END};	
//=================================================================================================
#define RT_HW_BOARD_CHECK_PIN				//--Разрешение проверки на допустимость использования пинов [функции checkPinXXX(uint8_t pin)];
//-----Доступные пины контроллера------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_ALL[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DIN[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_ADC[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,   		RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_TCH[] 	={												RT_HW_PGM_END};									
const uint8_t PROGMEM RT_HW_PGM_PIN_DOT[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_PWM[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DAC[] 	={ 0,											RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_INT[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,	RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_N5V[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,	RT_HW_PGM_END};	
//-----Тестовые пины и адреса------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_DBG[]  	={					RT_HW_PGM_END};	//--debug1,debug2,debug3;	
const uint8_t PROGMEM RT_HW_PGM_PIN_OUT[] 	={2,      			RT_HW_PGM_END};	//--Пины PWM0,PWM1,Servo1,Servo2;							                  
const uint8_t PROGMEM RT_HW_PGM_PIN_INP[] 	={1,         		RT_HW_PGM_END};	//--Пины A0,A1,btn1,btn2,TCH0,TCH1;
const uint8_t PROGMEM RT_HW_PGM_PIN_DCT[] 	={0,          		RT_HW_PGM_END};	//--Пины DAC0,DAC1;
const uint8_t PROGMEM RT_HW_PGM_PIN_DEV[] 	={					RT_HW_PGM_END};	//--Пины DS1820,DHT22,HC-SR04.trig;
const uint8_t PROGMEM RT_HW_PGM_PIN_CSS[] 	={2,3,				RT_HW_PGM_END};	//--Пины CS SPI:595,LCD,NRF,DEVl; 	
const uint8_t PROGMEM RT_HW_PGM_PIN_LC6[]  	={  				RT_HW_PGM_END};	//--Пины для подключения LCD по 4-х битной шине;
const uint8_t PROGMEM RT_HW_PGM_PIN_TFT[]  	={   		     	RT_HW_PGM_END};	//--Пины(дополнительные[]  TFT дисплея(SPI[] -CS,R/S,LED,RST,TOUCH;
const uint8_t PROGMEM RT_HW_PGM_PIN_URT[]  ={ 1, 2, 			RT_HW_PGM_END};	//--UART: ModBus, Nextion 
const uint8_t PROGMEM RT_HW_PGM_ADR_I2C[]  	={39,62,32,33,		RT_HW_PGM_END};	//--lcd1,lcd2,mcp1,mcp2;
//-------------------------------------------------------------------------------------------------
#endif

//*************************************************************************************************
//							1.Контроллеры типа Seeeduino Z0 M0 [arduino_zero.variant]
//*************************************************************************************************
#if !defined(RT_HW_BOARD_SELECT) && defined(RT_HW_BOARD_SEEED_ZERO)	
#define      RT_HW_BOARD_SELECT 		    "Board Seeed Zero(SAMD21 mini)"		//--Идентификатор выбора платы;
#define RT_HW_BOARD_MEMORY   "FLASH=256Kb; RAM=32Kb;"					//--Параметры памяти;
#define RT_HW_PERMIT_UART0
#define RT_HW_PERMIT_UART1
#define RT_HW_PERMIT_I2C0	
#define RT_HW_PERMIT_SPI0
#define RT_HW_PERMIT_DAC												//--Разрешение работы с DAC;
//=================================================================================================
//------Системные пины------------------------------------------------------------------------------
enum   {RT_HW_BOARD_CONTROL=10, RT_HW_BOARD_LED=13, RT_HW_BOARD_BUTTON=12, RT_HW_BOARD_WS=255};	//--Пины контроль,led,кнопка;
//------Параметры контроллера общие-------------------------------------------------------------------	
enum{RT_HW_PIN_QNT_MAX=26, RT_HW_FCPU=48, 	  RT_HW_VCC=3300};
//-----Параметры UART------------------------------------------------------------------------------	
enum   {RT_HW_UART0_RX=255, RT_HW_UART0_TX=255, RT_HW_UART1_RX=0,  RT_HW_UART1_TX=1};
//-----Параметры I2C------------------------------------------------------------------------------	
enum   {RT_HW_I2C0_SDA=20,  RT_HW_I2C0_SCL=21,  RT_HW_I2C0_MODE_FM=RT_HW_I2C_MODE_FM}; 
//-----Параметры SPI------------------------------------------------------------------------------	
enum   {RT_HW_SPI0_SCK=24,  RT_HW_SPI0_MISO=22, RT_HW_SPI0_MOSI=23, RT_HW_SPI0_SS=255};
//-----Системные параметры-------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_SYS_PAR[]   ={12,			   	RT_HW_PGM_END};  //--SYS->depth;
const uint8_t PROGMEM RT_HW_PGM_SYS_ADC[]	={12,15,10,			RT_HW_PGM_END};  //--ADC->depth,drift,null;
const uint8_t PROGMEM RT_HW_PGM_SYS_TCH[]  	={  				RT_HW_PGM_END};  //--TCH->depth,drift,null; 
const uint8_t PROGMEM RT_HW_PGM_SYS_PWM[]  	={12,10,			RT_HW_PGM_END};  //--PWM->depth,freq; 
const uint8_t PROGMEM RT_HW_PGM_SYS_DAC[]  	={10,				RT_HW_PGM_END};  //--DAC->depth; 
//-----Системные пины и параметры коммуникаций------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_BRD[] 	={RT_HW_BOARD_CONTROL, RT_HW_BOARD_LED, RT_HW_BOARD_BUTTON, RT_HW_BOARD_WS, RT_HW_PGM_END};  //--Пины->control,led,button,WS2812; 
const uint8_t PROGMEM RT_HW_PGM_PIN_I2C[] 	={RT_HW_I2C0_SDA,  RT_HW_I2C0_SCL,	    			                  RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_ICS[]	={	    															  RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_SPI[] 	={RT_HW_SPI0_SCK,  RT_HW_SPI0_MOSI,  RT_HW_SPI0_MISO, RT_HW_SPI0_SS,  RT_HW_PGM_END}; 
const uint8_t PROGMEM RT_HW_PGM_PIN_SPN[]	={ 																	  RT_HW_PGM_END}; 
//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_SPQ[]	={			         			    RT_HW_PGM_END};  //--SPQ: sck,miso,mosi,cs;	
const uint8_t PROGMEM RT_HW_PGM_PIN_SDC[]	={                                  RT_HW_PGM_END};  //--SDIO: DO,D1,D2,D3,SCK;	
//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_UHS[] 	={255,   			255,	 		 RT_HW_UART1_RX,  RT_HW_UART1_TX, RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_USS[] 	={					RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_CAN[] 	={					RT_HW_PGM_END};		
const uint8_t PROGMEM RT_HW_PGM_PIN_BTH[] 	={					RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_ETH[] 	={					RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_WFI[] 	={					RT_HW_PGM_END};	
//-----Доступные пины контроллера------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_ALL[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,
											  14,15,16,17,18,19,
											  20,21,22,23,24,     27,28,29,30,31,38,			RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DIN[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,		RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_ADC[] 	={14,15,16,17,18,19,   								RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_TCH[] 	={													RT_HW_PGM_END};									
const uint8_t PROGMEM RT_HW_PGM_PIN_DOT[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,		RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_PWM[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,		RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DAC[] 	={14,												RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_INT[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,		RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_N5V[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,
											  14,16,17,18,19,20,21,22,23,24,     27,28,29,30,31,RT_HW_PGM_END};	
//-----Тестовые пины и адреса------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_DBG[]  	={					RT_HW_PGM_END};	//--Пины debug1,debug2,debug3;	
const uint8_t PROGMEM RT_HW_PGM_PIN_OUT[] 	={4,5,2,3,      	RT_HW_PGM_END};	//--Пины PWM0,PWM1,Servo1,Servo2;							                  
const uint8_t PROGMEM RT_HW_PGM_PIN_INP[] 	={15,16,12,11,      RT_HW_PGM_END};	//--Пины A0,A1,btn1,btn2,TCH0,TCH1;
const uint8_t PROGMEM RT_HW_PGM_PIN_DCT[] 	={14,          		RT_HW_PGM_END};	//--Пины DAC0,DAC1;
const uint8_t PROGMEM RT_HW_PGM_PIN_DEV[] 	={					RT_HW_PGM_END};	//--Пины DS1820,DHT22,HC-SR04.trig;
const uint8_t PROGMEM RT_HW_PGM_PIN_CSS[] 	={6,7,8,9,			RT_HW_PGM_END};	//--Пины CS SPI:595,LCD,NRF,DEVl; 	
const uint8_t PROGMEM RT_HW_PGM_PIN_LC6[]  	={  				RT_HW_PGM_END};	//--Пины для подключения LCD по 4-х битной шине;
const uint8_t PROGMEM RT_HW_PGM_PIN_TFT[]  	={   		     	RT_HW_PGM_END};	//--Пины(дополнительные[]  TFT дисплея(SPI[] -CS,R/S,LED,RST,TOUCH;
const uint8_t PROGMEM RT_HW_PGM_PIN_URT[]   ={ 1, 2, 			RT_HW_PGM_END};	//--UART: ModBus, Nextion 
const uint8_t PROGMEM RT_HW_PGM_ADR_I2C[]  	={39,62,32,33,		RT_HW_PGM_END};	//--lcd1,lcd2,mcp1,mcp2;
//-------------------------------------------------------------------------------------------------
#endif
//=================================================================================================