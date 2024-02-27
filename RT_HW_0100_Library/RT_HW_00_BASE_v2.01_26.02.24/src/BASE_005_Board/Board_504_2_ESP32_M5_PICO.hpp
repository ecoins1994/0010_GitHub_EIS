//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							1.Контроллер типа M5Stack-Core-ESP32
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if !defined(RT_HW_BOARD_SELECT) && defined(RT_HW_BOARD_M5Stack_Core_ESP32)
#define RT_HW_BOARD_SELECT 						 "BOARD M5Stack-Core-ESP32"	//--Идентификатор выбора платы;		
//-------------------------------------------------------------------------------------------------											
#define RT_HW_PERMIT_UART0													//--Разрешение работы с UART0; 
#define RT_HW_PERMIT_UART1													//--Разрешение работы с UART1; 
#define RT_HW_PERMIT_UART2													//--Разрешение работы с UART2; 
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_I2C0													//--Разрешение работы с i2c0;  
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_SPI0													//--Разрешение работы с spi0 (clk=18,miso=19,mosi=23,cs=5); 
//#define RT_HW_PERMIT_SPI1	//--!!! Проблемы с core ESP32??? - !!!			//--Разрешение работы с spi1 (clk=14,miso=12,mosi=13,ss=15); 
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_DAC													//--Разрешение работы с DAC;
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_HALL													//--Разрешение работы с HALL;
//#define RT_HW_PERMIT_WS													
//--------------------------------Параметры UART---------------------------------------------------	
enum   {RT_HW_UART0_RX=3,   RT_HW_UART0_TX=1,    RT_HW_UART0_DE=255,
        RT_HW_UART1_RX=23,  RT_HW_UART1_TX=33,   RT_HW_UART1_DE=255,
		RT_HW_UART2_RX=16,  RT_HW_UART2_TX=17,   RT_HW_UART2_DE=255};
//-----Параметры I2C-------------------------------------------------------------------------------	
enum   {RT_HW_I2C0_SDA=21,  RT_HW_I2C0_SCL=22}; 	
//-----Параметры SPI-------------------------------------------------------------------------------	
enum   {RT_HW_SPI0_SCK=18,  RT_HW_SPI0_MISO=19, RT_HW_SPI0_MOSI=23, RT_HW_SPI0_SS=2};
//=================================================================================================
#define RT_HW_BOARD_CHECK_PIN				//--Разрешение проверки на допустимость использования пинов [функции checkPinXXX(uint8_t pin)];
//--------------------------------Доступные пины контроллера---------------------------------------
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
//=================================================================================================
//--------------------------------Параметры коммуникаций-------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_UHS[] 	={RT_HW_UART0_RX, RT_HW_UART0_TX,  RT_HW_UART0_DE,	//--UART0;
										      RT_HW_UART1_RX, RT_HW_UART1_TX,  RT_HW_UART1_DE,	//--UART1; 
											  RT_HW_UART2_RX, RT_HW_UART2_TX,  RT_HW_UART2_DE,	//--UART2; 										  
																		       RT_HW_PGM_END};
//-------------------------------------------------------------------------------------------------											  						
const uint8_t PROGMEM RT_HW_PGM_PIN_USS[]	={                                 RT_HW_PGM_END};	//--UARTS:rx,tx,de; 
//--------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_I2C[]	={RT_HW_I2C0_SDA, RT_HW_I2C0_SCL,  RT_HW_PGM_END}; //--i2c:  sda,scl;
//--------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_SPI[]	={RT_HW_SPI0_SCK, RT_HW_SPI0_MISO, RT_HW_SPI0_MOSI, RT_HW_SPI0_SS, RT_HW_PGM_END};	//--SPI:  sck,miso,mosi,ss
const uint8_t PROGMEM RT_HW_PGM_PIN_SPF[]	={						         	RT_HW_PGM_END};  //--SPQ: sck,miso,mosi,cs;	
const uint8_t PROGMEM RT_HW_PGM_PIN_SDC[]	={				                    RT_HW_PGM_END};  //--SDIO: DO,D1,D2,D3,SCK;
const uint8_t PROGMEM RT_HW_PGM_PIN_SPN[]	={          						RT_HW_PGM_END};  //--SSPI: sck,miso,mosi,cs;	
//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_ETH[]	={				                    RT_HW_PGM_END};	//--numSPI; cs,int,rst;
const uint8_t PROGMEM RT_HW_PGM_PIN_CAN[]	={								    RT_HW_PGM_END};	//--CAN:  rx,tx;
//--------------------------------Системные пины---------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_BRD[]	={255, 255, 35,	    	    		RT_HW_PGM_END};	//--Control,LED,Button,ADC,PWM,WS2812
//--------------------------------SPI пины cs------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_CSX[]	={2, 5,255,26,	    			    RT_HW_PGM_END};	//--SPI: cs0,cs1,cs2,cs3
//--------------------------------Дисплейные пины--------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_LC4[]	={									RT_HW_PGM_END};	//--RS,E2(RW),E1,D4-D7;
const uint8_t PROGMEM RT_HW_PGM_PIN_LC6[]	={									RT_HW_PGM_END};	//--RS,E2(RW),E1,D0-D7;
const uint8_t PROGMEM RT_HW_PGM_PIN_TFT[]	={	    	            			RT_HW_PGM_END};	//--;
//--------------------------------Тестовые пины----------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_TST_DIS[]	={          	    				RT_HW_PGM_END};	//--Дискретные сигналы;
const uint8_t PROGMEM RT_HW_PGM_TST_ANL[]	={35,       						RT_HW_PGM_END};	//--Аналоговые сигналы: ADC1,PWM1;
const uint8_t PROGMEM RT_HW_PGM_TST_SRV[]	={           	   				    RT_HW_PGM_END};	//--Servo1,Servo2;
const uint8_t PROGMEM RT_HW_PGM_TST_DEV[]	={26,           				  	RT_HW_PGM_END};	//--Устройства: 1-Wire,DHT22,HC-SR04.trig,HC-SR04.echo,
const uint8_t PROGMEM RT_HW_PGM_TST_URT[]	={99,2,            		   		    RT_HW_PGM_END};	//--UART: ModBus, Nextion;
//-------------------------------------------------------------------------------------------------
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*
static const uint8_t TX = 1;
static const uint8_t RX = 3;

static const uint8_t TXD2 = 32;
static const uint8_t RXD2 = 26;

static const uint8_t SDA = 26;
static const uint8_t SCL = 32;

static const uint8_t G12 = 12;
static const uint8_t G19 = 19;
static const uint8_t G21 = 21;
static const uint8_t G22 = 22;
static const uint8_t G23 = 23;
static const uint8_t G25 = 25;
static const uint8_t G26 = 26;
static const uint8_t G27 = 27;
static const uint8_t G32 = 32;
static const uint8_t G33 = 33;
static const uint8_t G39 = 39;

static const uint8_t G9 = 9;
static const uint8_t G10 = 10;
static const uint8_t G37 = 37;
static const uint8_t G36 = 36;
static const uint8_t G0 = 0;

static const uint8_t DAC1 = 25;
static const uint8_t DAC2 = 26;

static const uint8_t ADC1 = 35;
static const uint8_t ADC2 = 36;

static const uint8_t SS    = 19;
static const uint8_t MOSI  = 33;
static const uint8_t MISO  = 23;
static const uint8_t SCK   = 22;


static const uint8_t TX = 1;
static const uint8_t RX = 3;

static const uint8_t SDA = 21;
static const uint8_t SCL = 22;

static const uint8_t G26 = 26;
static const uint8_t G36 = 36;
static const uint8_t G18 = 18;
static const uint8_t G19 = 19;
static const uint8_t G21 = 21;
static const uint8_t G22 = 22;
static const uint8_t G25 = 25;
static const uint8_t G1 = 1;
static const uint8_t G3 = 3;
static const uint8_t G0 = 0;

static const uint8_t G32 = 32;
static const uint8_t G33 = 33;

static const uint8_t SS    = 19;
static const uint8_t MOSI  = 26;
static const uint8_t MISO  = 36;
static const uint8_t SCK   = 18;

*/
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							2.Контроллер типа M5Stack-ATOM 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if !defined(RT_HW_BOARD_SELECT) && defined(RT_HW_BOARD_ESP32_ATOM)
#define RT_HW_BOARD_SELECT 						 "BOARD M5Stack-ATOM"	//--Идентификатор выбора платы;		
//-------------------------------------------------------------------------------------------------											
#define RT_HW_PERMIT_UART0													//--Разрешение работы с UART0; 
#define RT_HW_PERMIT_UART1													//--Разрешение работы с UART1; 
#define RT_HW_PERMIT_UART2													//--Разрешение работы с UART2; 
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_I2C0													//--Разрешение работы с i2c0;  
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_SPI0													//--Разрешение работы с spi0; 
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_DAC													//--Разрешение работы с DAC;
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_WS													
//--------------------------------Параметры UART---------------------------------------------------	
enum   {RT_HW_UART0_RX=3,   RT_HW_UART0_TX=1,     RT_HW_UART0_DE=255, 
       // RT_HW_UART1_RX=25,  RT_HW_UART1_TX=21,    RT_HW_UART1_DE=255,
        RT_HW_UART1_RX=26,  RT_HW_UART1_TX=32,    RT_HW_UART1_DE=255,
		RT_HW_UART2_RX=26,  RT_HW_UART2_TX=32,    RT_HW_UART2_DE=255};
//-----Параметры I2C-------------------------------------------------------------------------------	
enum   {RT_HW_I2C0_SDA=26,  RT_HW_I2C0_SCL=32}; 	
//-----Параметры SPI-------------------------------------------------------------------------------	
enum   {RT_HW_SPI0_SCK=22,  RT_HW_SPI0_MISO=19, RT_HW_SPI0_MOSI=23, RT_HW_SPI0_SS=33};
//=================================================================================================
#define RT_HW_BOARD_CHECK_PIN				//--Разрешение проверки на допустимость использования пинов [функции checkPinXXX(uint8_t pin)];
//--------------------------------Доступные пины контроллера---------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_ALL[] 	={ 0, 1, 3,12,19,21,22,23,25,26,27,32,33,34,39, RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DIN[] 	={ 0,      12,19,21,22,23,25,26,27,32,33,34,39, RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_ADC[] 	={                                 32,33, 	    RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_TCH[] 	={                                 32,33,	    RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DOT[] 	={         12,19,21,22,23,25,26,27,32,33,	    RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_PWM[] 	={         12,19,21,22,23,25,26,27,32,33,	    RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DAC[] 	={                        25,26,			    RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_INT[] 	={ 0, 1, 3,12,19,21,22,23,25,26,27,32,33,34,    RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_N5V[] 	={ 0, 1, 3,12,19,21,22,23,25,26,27,32,33,34,39, RT_HW_PGM_END};	
//=================================================================================================
//--------------------------------Параметры коммуникаций-------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_UHS[] 	={RT_HW_UART0_RX, RT_HW_UART0_TX,  RT_HW_UART0_DE,	//--UART0;
										      RT_HW_UART1_RX, RT_HW_UART1_TX,  RT_HW_UART1_DE,	//--UART1; 
											  RT_HW_UART2_RX, RT_HW_UART2_TX,  RT_HW_UART2_DE,	//--UART2; 										  
																		       RT_HW_PGM_END};
//-------------------------------------------------------------------------------------------------											  						
const uint8_t PROGMEM RT_HW_PGM_PIN_USS[]	={                                 RT_HW_PGM_END};	//--UARTS:rx,tx,de; 
//--------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_I2C[]	={RT_HW_I2C0_SDA, RT_HW_I2C0_SCL,  RT_HW_PGM_END};  //--i2c:  sda,scl;
//--------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_SPI[]	={RT_HW_SPI0_SCK, RT_HW_SPI0_MISO, RT_HW_SPI0_MOSI, RT_HW_SPI0_SS, RT_HW_PGM_END};	//--SPI:  sck,miso,mosi,ss
const uint8_t PROGMEM RT_HW_PGM_PIN_SPF[]	={						         	RT_HW_PGM_END};  //--SPQ: sck,miso,mosi,cs;	
const uint8_t PROGMEM RT_HW_PGM_PIN_SDC[]	={				                    RT_HW_PGM_END};  //--SDIO: DO,D1,D2,D3,SCK;
const uint8_t PROGMEM RT_HW_PGM_PIN_SPN[]	={          						RT_HW_PGM_END};  //--SSPI: sck,miso,mosi,cs;	
//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_ETH[]	={				                    RT_HW_PGM_END};	//--numSPI; cs,int,rst;
const uint8_t PROGMEM RT_HW_PGM_PIN_CAN[]	={								    RT_HW_PGM_END};	//--CAN:  rx,tx;
//--------------------------------Системные пины---------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_BRD[]	={255, 255, 35,	    	    		RT_HW_PGM_END};	//--Control,LED,Button,ADC,PWM,WS2812
//--------------------------------SPI пины cs------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_CSX[]	={2, 5,255,26,	    			    RT_HW_PGM_END};	//--SPI: cs0,cs1,cs2,cs3
//--------------------------------Дисплейные пины--------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_LC4[]	={									RT_HW_PGM_END};	//--RS,E2(RW),E1,D4-D7;
const uint8_t PROGMEM RT_HW_PGM_PIN_LC6[]	={									RT_HW_PGM_END};	//--RS,E2(RW),E1,D0-D7;
const uint8_t PROGMEM RT_HW_PGM_PIN_TFT[]	={	    	            			RT_HW_PGM_END};	//--;
//--------------------------------Тестовые пины----------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_TST_DIS[]	={          	    				RT_HW_PGM_END};	//--Дискретные сигналы;
const uint8_t PROGMEM RT_HW_PGM_TST_ANL[]	={35,       						RT_HW_PGM_END};	//--Аналоговые сигналы: ADC1,PWM1;
const uint8_t PROGMEM RT_HW_PGM_TST_SRV[]	={           	   				    RT_HW_PGM_END};	//--Servo1,Servo2;
const uint8_t PROGMEM RT_HW_PGM_TST_DEV[]	={26,           				  	RT_HW_PGM_END};	//--Устройства: 1-Wire,DHT22,HC-SR04.trig,HC-SR04.echo,
const uint8_t PROGMEM RT_HW_PGM_TST_URT[]	={99,2,            		   		    RT_HW_PGM_END};	//--UART: ModBus, Nextion;
//-------------------------------------------------------------------------------------------------
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							3.Контроллер типа STAMP-PICO
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if !defined(RT_HW_BOARD_SELECT) && defined(RT_HW_BOARD_STAMP_PICO)
#define RT_HW_BOARD_SELECT 						 "BOARD STAMP-PICO"			//--Идентификатор выбора платы;		
//-------------------------------------------------------------------------------------------------											
#define RT_HW_PERMIT_UART0													//--Разрешение работы с UART0; 
#define RT_HW_PERMIT_UART1													//--Разрешение работы с UART1; 
#define RT_HW_PERMIT_UART2													//--Разрешение работы с UART2; 
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_I2C0													//--Разрешение работы с i2c0;  
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_SPI0													//--Разрешение работы с spi0; 
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_DAC													//--Разрешение работы с DAC;
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_WS													
//--------------------------------Параметры UART---------------------------------------------------	
enum   {RT_HW_UART0_RX=3,   RT_HW_UART0_TX=1,     RT_HW_UART0_DE=255, 
        RT_HW_UART1_RX=25,  RT_HW_UART1_TX=21,    RT_HW_UART1_DE=255,
		RT_HW_UART2_RX=26,  RT_HW_UART2_TX=32,    RT_HW_UART2_DE=255};
//-----Параметры I2C-------------------------------------------------------------------------------	
enum   {RT_HW_I2C0_SDA=26,  RT_HW_I2C0_SCL=32}; 	
//-----Параметры SPI-------------------------------------------------------------------------------	
enum   {RT_HW_SPI0_SCK=22,  RT_HW_SPI0_MISO=19, RT_HW_SPI0_MOSI=23, RT_HW_SPI0_SS=33};
//=================================================================================================
#define RT_HW_BOARD_CHECK_PIN				//--Разрешение проверки на допустимость использования пинов [функции checkPinXXX(uint8_t pin)];
//--------------------------------Доступные пины контроллера---------------------------------------
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
//=================================================================================================
//--------------------------------Параметры коммуникаций-------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_UHS[] 	={RT_HW_UART0_RX, RT_HW_UART0_TX,  RT_HW_UART0_DE,	//--UART0;
										      RT_HW_UART1_RX, RT_HW_UART1_TX,  RT_HW_UART1_DE,	//--UART1; 
											  RT_HW_UART2_RX, RT_HW_UART2_TX,  RT_HW_UART2_DE,	//--UART2; 										  
																		       RT_HW_PGM_END};
//-------------------------------------------------------------------------------------------------											  						
const uint8_t PROGMEM RT_HW_PGM_PIN_USS[]	={                                 RT_HW_PGM_END};	//--UARTS:rx,tx,de; 
//--------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_I2C[]	={RT_HW_I2C0_SDA, RT_HW_I2C0_SCL,  RT_HW_PGM_END}; //--i2c:  sda,scl;
//--------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_SPI[]	={RT_HW_SPI0_SCK, RT_HW_SPI0_MISO, RT_HW_SPI0_MOSI, RT_HW_SPI0_SS, RT_HW_PGM_END};	//--SPI:  sck,miso,mosi,ss
const uint8_t PROGMEM RT_HW_PGM_PIN_SPF[]	={						         	RT_HW_PGM_END};  //--SPQ: sck,miso,mosi,cs;	
const uint8_t PROGMEM RT_HW_PGM_PIN_SDC[]	={				                    RT_HW_PGM_END};  //--SDIO: DO,D1,D2,D3,SCK;
const uint8_t PROGMEM RT_HW_PGM_PIN_SPN[]	={          						RT_HW_PGM_END};  //--SSPI: sck,miso,mosi,cs;	
//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_ETH[]	={				                    RT_HW_PGM_END};	//--numSPI; cs,int,rst;
const uint8_t PROGMEM RT_HW_PGM_PIN_CAN[]	={								    RT_HW_PGM_END};	//--CAN:  rx,tx;
//--------------------------------Системные пины---------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_BRD[]	={255, 255, 35,	    	    		RT_HW_PGM_END};	//--Control,LED,Button,ADC,PWM,WS2812
//--------------------------------SPI пины cs------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_CSX[]	={2, 5,255,26,	    			    RT_HW_PGM_END};	//--SPI: cs0,cs1,cs2,cs3
//--------------------------------Дисплейные пины--------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_LC4[]	={									RT_HW_PGM_END};	//--RS,E2(RW),E1,D4-D7;
const uint8_t PROGMEM RT_HW_PGM_PIN_LC6[]	={									RT_HW_PGM_END};	//--RS,E2(RW),E1,D0-D7;
const uint8_t PROGMEM RT_HW_PGM_PIN_TFT[]	={	    	            			RT_HW_PGM_END};	//--;
//--------------------------------Тестовые пины----------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_TST_DIS[]	={          	    				RT_HW_PGM_END};	//--Дискретные сигналы;
const uint8_t PROGMEM RT_HW_PGM_TST_ANL[]	={35,       						RT_HW_PGM_END};	//--Аналоговые сигналы: ADC1,PWM1;
const uint8_t PROGMEM RT_HW_PGM_TST_SRV[]	={           	   				    RT_HW_PGM_END};	//--Servo1,Servo2;
const uint8_t PROGMEM RT_HW_PGM_TST_DEV[]	={26,           				  	RT_HW_PGM_END};	//--Устройства: 1-Wire,DHT22,HC-SR04.trig,HC-SR04.echo,
const uint8_t PROGMEM RT_HW_PGM_TST_URT[]	={99,2,            		   		    RT_HW_PGM_END};	//--UART: ModBus, Nextion;
//-------------------------------------------------------------------------------------------------
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++