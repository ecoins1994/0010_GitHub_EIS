//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							1.Контроллер типа ESP32 Dev module
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if !defined(RT_HW_BOARD_SELECT)  && defined(RT_HW_BOARD_ESP32_DEV)
#define      RT_HW_BOARD_SELECT 			"BOARD ESP32 Dev Module"		//--Идентификатор выбора платы;
//-------------------------------------------------------------------------------------------------
//							Permission to work with Link
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_UART0					//--Permission to work with UART0;
#define RT_HW_PERMIT_UART1					//--Permission to work with UART1;
#define RT_HW_PERMIT_UART2					//--Permission to work with UART2;
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_I2C0					//--Permission to work with i2c0;
#define RT_HW_PERMIT_I2C1					//--Permission to work with i2c1;
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_SPI0					//--Permission to work with SPI0;
#define RT_HW_PERMIT_SPI1					//--Permission to work with SPI1;
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_CAN					//--Permission to work with CAN;
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_DAC					//--Permission to work with DAC;
//-------------------------------------------------------------------------------------------------
//							Permission to work with SPECIAL function
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_HALL					//--Permission to work with CAN;
//#define RT_HW_PERMIT_WS					//--Permission to work with LED WS2812;
//-------------------------------------------------------------------------------------------------
//							Permission to cteate with Link
//-------------------------------------------------------------------------------------------------
#define RT_HW_CREATE_SPI1					//--Permission to work with SPI1;

//=================================================================================================
//									Pins for Link
//=================================================================================================												
//--------------------------------Параметры UART---------------------------------------------------	
enum {RT_HW_UART0_RX=3,   RT_HW_UART0_TX=1,   RT_HW_UART0_DE=255,
	  RT_HW_UART1_RX=14,  RT_HW_UART1_TX=27,  RT_HW_UART1_DE=255, 
	  RT_HW_UART2_RX=16,  RT_HW_UART2_TX=17,  RT_HW_UART2_DE=255};
//--------------------------------Параметры I2C----------------------------------------------------
enum {RT_HW_I2C0_SDA=21,  RT_HW_I2C0_SCL=22,
	  RT_HW_I2C1_SDA=33,  RT_HW_I2C1_SCL=32}; 
//--------------------------------Параметры SPI----------------------------------------------------	
enum {RT_HW_SPI0_SCK=18,  RT_HW_SPI0_MISO=19,  RT_HW_SPI0_MOSI=23,  RT_HW_SPI0_SS=5,
      RT_HW_SPI1_SCK=14,  RT_HW_SPI1_MISO=12,  RT_HW_SPI1_MOSI=13,  RT_HW_SPI1_SS=15};
//--------------------------------Параметры Ethernet-----------------------------------------------	
enum {RT_HW_ETH0_BUS=0,   RT_HW_ETH0_CS=5,     RT_HW_ETH0_INT=0,
      RT_HW_ETH1_BUS=255, RT_HW_ETH1_CS=255,   RT_HW_ETH1_INT=255};	 
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
const uint8_t PROGMEM RT_HW_PGM_PIN_I2C[]	={RT_HW_I2C0_SDA, RT_HW_I2C0_SCL,   
                                              RT_HW_I2C1_SDA, RT_HW_I2C1_SCL,  RT_HW_PGM_END}; //--i2c:  sda,scl;
//--------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_SPI[]	={RT_HW_SPI0_SCK, RT_HW_SPI0_MISO, RT_HW_SPI0_MOSI, RT_HW_SPI0_SS, //--SPI0: sck,miso,mosi,ss	
                                              RT_HW_SPI1_SCK, RT_HW_SPI1_MISO, RT_HW_SPI1_MOSI, RT_HW_SPI1_SS, //--SPI1: sck,miso,mosi,ss
																			   RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_SPF[]	={						           RT_HW_PGM_END};  //--SPQ: sck,miso,mosi,cs;	
const uint8_t PROGMEM RT_HW_PGM_PIN_SDC[]	={				                   RT_HW_PGM_END};  //--SDIO: DO,D1,D2,D3,SCK;
const uint8_t PROGMEM RT_HW_PGM_PIN_SPN[]	={          					   RT_HW_PGM_END};  //--SSPI: sck,miso,mosi,cs;	
//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_ETH[]	={RT_HW_ETH0_BUS,  RT_HW_ETH0_CS,  RT_HW_ETH0_INT, //--ETH0:0,bus, pins: cs,int;
											  RT_HW_ETH1_BUS,  RT_HW_ETH1_CS,  RT_HW_ETH1_INT, //--ETH1:0,bus, pins: cs,int;
																			   RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_CAN[]	={								   RT_HW_PGM_END};	//--CAN:     0,rx,tx;
//--------------------------------Системные пины---------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_BRD[]	={12,  2, 34,36,25,	    	       RT_HW_PGM_END};	//--Control,LED,Button,ADC,PWM,WS2812
//--------------------------------SPI пины cs------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_CSX[]	={ 5,  4, 15, 2,	    		   RT_HW_PGM_END};	//--SPI: cs0,cs1,cs2,cs3
//--------------------------------Дисплейные пины--------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_LC4[]	={								   RT_HW_PGM_END};	//--RS,E2(RW),E1,D4-D7;
const uint8_t PROGMEM RT_HW_PGM_PIN_LC6[]	={								   RT_HW_PGM_END};	//--RS,E2(RW),E1,D0-D7;
const uint8_t PROGMEM RT_HW_PGM_PIN_TFT[]	={	    	            		   RT_HW_PGM_END};	//--;
//--------------------------------Тестовые пины----------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_TST_DIS[]	={          	    			   RT_HW_PGM_END};	//--Дискретные сигналы;
const uint8_t PROGMEM RT_HW_PGM_TST_ANL[]	={39,26,       					   RT_HW_PGM_END};	//--Аналоговые сигналы: ADC1,PWM1;
const uint8_t PROGMEM RT_HW_PGM_TST_SRV[]	={12,           	   			   RT_HW_PGM_END};	//--Servo1,Servo2;
const uint8_t PROGMEM RT_HW_PGM_TST_DEV[]	={33, 14,13,           			   RT_HW_PGM_END};	//--Устройства: 1-Wire,DHT22,HC-SR04.trig,HC-SR04.echo,
const uint8_t PROGMEM RT_HW_PGM_TST_URT[]	={1,2,            		   		   RT_HW_PGM_END};	//--UART: ModBus, Nextion;
//-------------------------------------------------------------------------------------------------
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++