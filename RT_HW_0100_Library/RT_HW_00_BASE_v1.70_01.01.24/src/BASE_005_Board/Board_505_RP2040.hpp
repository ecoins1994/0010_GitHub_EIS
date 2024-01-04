//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							 1.Контроллер типа Raspberry Pi Pico
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if !defined(RT_HW_BOARD_SELECT) && defined(RT_HW_BOARD_RP2040)	
#define      RT_HW_BOARD_SELECT 	             "BOARD RP2040 v2.4" 		//--Идентификатор выбора платы
//-------------------------------------------------------------------------------------------------
//							Permission to work with Link
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_UART0					//--Permission to work with UART0;
#define RT_HW_PERMIT_UART1					//--Permission to work with UART1;
#define RT_HW_PERMIT_UART2					//--Permission to work with UART2;
#define RT_HW_PERMIT_UART3   				//--Permission to work with UART3;
#define RT_HW_PERMIT_UART4				    //--Permission to work with UART4;
#define RT_HW_PERMIT_UART5  				//--Permission to work with UART5;
#define RT_HW_PERMIT_UART6			    	//--Permission to work with UART6;
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_I2C0					//--Permission to work with i2c0;
#define RT_HW_PERMIT_I2C1					//--Permission to work with i2c1;
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_SPI0					//--Permission to work with SPI0;
#define RT_HW_PERMIT_SPI1					//--Permission to work with SPI1;
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_ETH					//--Permission to work with ETH;
#define RT_HW_PERMIT_CAN					//--Permission to work with CAN;
#define RT_HW_PERMIT_TFT					//--Permission to work with TFT;
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_DAC					//--Permission to work with DAC;
//-------------------------------------------------------------------------------------------------
//							Permission to cteate with Link
//-------------------------------------------------------------------------------------------------
#define RT_HW_CREATE_UART3   				//--Permission to create Serail3 for UART3;
#define RT_HW_CREATE_UART4  				//--Permission to create Serial4 for UART4;
#define RT_HW_CREATE_UART5   				//--Permission to create Serail3 for UART5;
#define RT_HW_CREATE_UART6  				//--Permission to create Serial4 for UART6;
//=================================================================================================
//--------------------------------Параметры UART---------------------------------------------------	
enum {RT_HW_UART0_RX=47,  RT_HW_UART0_TX=46,  RT_HW_UART0_DE=255,
	  RT_HW_UART1_RX=1,   RT_HW_UART1_TX=0,   RT_HW_UART1_DE=255, 
	  RT_HW_UART2_RX=9,   RT_HW_UART2_TX=8,   RT_HW_UART2_DE=255,
	  RT_HW_UART3_RX=13,  RT_HW_UART3_TX=12,  RT_HW_UART3_DE=255,	  
	  RT_HW_UART4_RX=15,  RT_HW_UART4_TX=14,  RT_HW_UART4_DE=255,
	  RT_HW_UART5_RX=7,   RT_HW_UART5_TX=6,   RT_HW_UART5_DE=255,	  
	  RT_HW_UART6_RX=27,  RT_HW_UART6_TX=26,  RT_HW_UART6_DE=255};
//--------------------------------Параметры I2C----------------------------------------------------
enum {RT_HW_I2C0_SDA=4,   RT_HW_I2C0_SCL=5,
      RT_HW_I2C1_SDA=26,  RT_HW_I2C1_SCL=27}; 
//--------------------------------Параметры SPI----------------------------------------------------	
enum {RT_HW_SPI0_SCK=18,  RT_HW_SPI0_MISO=16,  RT_HW_SPI0_MOSI=19, RT_HW_SPI0_SS=17, 
	  RT_HW_SPI1_SCK=14,  RT_HW_SPI1_MISO=12,  RT_HW_SPI1_MOSI=15, RT_HW_SPI1_SS=13};
//=================================================================================================
//--------------------------------Доступные пины контроллера---------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_ALL[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,
											  16,17,18,19,20,21,22,23,24,25,26,27,28,29,		RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DIN[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,
											  16,17,18,19,20,21,22,23,24,25,26,27,28,29,		RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_ADC[] 	={26,27,28,29,   									RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_TCH[] 	={													RT_HW_PGM_END};									
const uint8_t PROGMEM RT_HW_PGM_PIN_DOT[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,
											  16,17,18,19,20,21,22,23,24,25,26,27,28,29,	    RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_PWM[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,
											  16,17,18,19,20,21,22,23,24,25,26,27,28,29,		RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DAC[] 	={													RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_INT[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,
											  16,17,18,19,20,21,22,23,24,25, 26,27,28,29,		RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_N5V[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,
											  16,17,18,19,20,21,22,23,24,25,26,27,28,29,		RT_HW_PGM_END};
//=================================================================================================
//--------------------------------Параметры коммуникаций-------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_UHS[] 	={RT_HW_UART0_RX, RT_HW_UART0_TX,  RT_HW_UART0_DE,	//--UART0;
										      RT_HW_UART1_RX, RT_HW_UART1_TX,  RT_HW_UART1_DE,	//--UART1; 
											  RT_HW_UART2_RX, RT_HW_UART2_TX,  RT_HW_UART2_DE,	//--UART2; 	
											  RT_HW_UART3_RX, RT_HW_UART3_TX,  RT_HW_UART3_DE,	//--UART3;
											  RT_HW_UART4_RX, RT_HW_UART4_TX,  RT_HW_UART4_DE,	//--UART4; 
											  RT_HW_UART5_RX, RT_HW_UART5_TX,  RT_HW_UART5_DE,	//--UART5;
											  RT_HW_UART6_RX, RT_HW_UART6_TX,  RT_HW_UART6_DE,	//--UART6; 											  
																		       RT_HW_PGM_END};
//-------------------------------------------------------------------------------------------------											  						
const uint8_t PROGMEM RT_HW_PGM_PIN_USS[]	={                                  RT_HW_PGM_END};	//--UARTS:rx,tx,de; 
//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_I2C[]	={RT_HW_I2C0_SDA, RT_HW_I2C0_SCL,   
                                              RT_HW_I2C1_SDA, RT_HW_I2C1_SCL,   RT_HW_PGM_END}; //--i2c:  sda,scl;
//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_SPI[]	={RT_HW_SPI0_SCK, RT_HW_SPI0_MISO,  RT_HW_SPI0_MOSI, RT_HW_SPI0_SS, 
                                              RT_HW_SPI1_SCK, RT_HW_SPI1_MISO,  RT_HW_SPI1_MOSI, RT_HW_SPI1_SS,
                                                                                RT_HW_PGM_END};	//--SPI:  sck,miso,mosi,ss
const uint8_t PROGMEM RT_HW_PGM_PIN_SPF[]	={			         				RT_HW_PGM_END};  //--SPQ: sck,miso,mosi,cs;	
const uint8_t PROGMEM RT_HW_PGM_PIN_SDC[]	={				                    RT_HW_PGM_END};  //--SDIO: DO,D1,D2,D3,SCK;
const uint8_t PROGMEM RT_HW_PGM_PIN_SPN[]	={									RT_HW_PGM_END};  //--SSPI: sck,miso,mosi,cs;		
//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_ETH[]	={0,21,23,				            RT_HW_PGM_END};	//--Ethernet: busSPI, cs,int;
const uint8_t PROGMEM RT_HW_PGM_PIN_CAN[]	={0,22,24,							RT_HW_PGM_END};	//--CAN:      busSPI, cs,int;
//--------------------------------Системные пины---------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_BRD[]	={28,25,26,27,7,	    			RT_HW_PGM_END};	//--Control,LED,Button,ADC,PWM,WS2812
//--------------------------------SPI пины cs------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_CSX[]	={17,20,21,22,28,29,   	    		RT_HW_PGM_END};	//--SPI: cs0,cs1,cs2,cs3,cs4,cs5,cs6
//--------------------------------Дисплейные пины--------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_LC4[]	={                          		RT_HW_PGM_END};	//--RS,E2(RW),E1,D4-D7;
const uint8_t PROGMEM RT_HW_PGM_PIN_LC6[]	={                                  RT_HW_PGM_END};	//--RS,E2(RW),E1,D0-D7;
const uint8_t PROGMEM RT_HW_PGM_PIN_TFT[]	={0,28,25,255,	    	            RT_HW_PGM_END};	//--TFT:  busSPI,cs,DC,LED;
//--------------------------------Тестовые пины----------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_TST_DIS[]	={          	    				RT_HW_PGM_END};	//--Дискретные сигналы;
const uint8_t PROGMEM RT_HW_PGM_TST_ANL[]	={27,       						RT_HW_PGM_END};	//--Аналоговые сигналы: ADC1,PWM1;
const uint8_t PROGMEM RT_HW_PGM_TST_SRV[]	={           	   				    RT_HW_PGM_END};	//--Servo1,Servo2;
const uint8_t PROGMEM RT_HW_PGM_TST_DEV[]	={10,255,11,           				RT_HW_PGM_END};	//--Устройства: 1-Wire,DHT22,HC-SR04.trig,HC-SR04.echo,
const uint8_t PROGMEM RT_HW_PGM_TST_URT[]	={210,1,2,3,4,5,6,            		RT_HW_PGM_END};	//--UART: Консоль,Modbus1,ModBus2,Nextion,Wi-Fi,Eth1,Eth2;
//-------------------------------------------------------------------------------------------------
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							 2.Контроллер типа Raspberry Pi Pico-W
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if !defined(RT_HW_BOARD_SELECT) && defined(RT_HW_BOARD_RP2040_W)	
#define      RT_HW_BOARD_SELECT 	             "BOARD RP2040 W" 		//--Идентификатор выбора платы
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_UART0					//--Разрешение работы с UART0; 
#define RT_HW_PERMIT_UART1					//--Разрешение работы с UART1; 
#define RT_HW_PERMIT_UART2					//--Разрешение работы с UART2; 	
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_I2C0					//--Разрешение работы с i2c0; 
#define RT_HW_PERMIT_I2C1					//--Разрешение работы с i2c1;
#define RT_HW_PERMIT_SPI0					//--Разрешение работы с spi0;
#define RT_HW_PERMIT_SPI1					//--Разрешение работы с spi1;
/*
// LEDs
#define PIN_LED        (32u)

// Serial
#define PIN_SERIAL1_TX (0u)
#define PIN_SERIAL1_RX (1u)

#define PIN_SERIAL2_TX (8u)
#define PIN_SERIAL2_RX (9u)

// SPI
#define PIN_SPI0_MISO  (16u)
#define PIN_SPI0_MOSI  (19u)
#define PIN_SPI0_SCK   (18u)
#define PIN_SPI0_SS    (17u)

#define PIN_SPI1_MISO  (12u)
#define PIN_SPI1_MOSI  (15u)
#define PIN_SPI1_SCK   (14u)
#define PIN_SPI1_SS    (13u)

// Wire
#define PIN_WIRE0_SDA  (4u)
#define PIN_WIRE0_SCL  (5u)

#define PIN_WIRE1_SDA  (26u)
#define PIN_WIRE1_SCL  (27u)

#define SERIAL_HOWMANY (3u)
#define SPI_HOWMANY    (2u)
#define WIRE_HOWMANY   (2u)
*/

//=================================================================================================
//--------------------------------Параметры UART---------------------------------------------------	
enum {RT_HW_UART0_RX=1,   RT_HW_UART0_TX=0,   RT_HW_UART0_DE=255,
	  RT_HW_UART1_RX=1,   RT_HW_UART1_TX=0,   RT_HW_UART1_DE=255, 
	  RT_HW_UART2_RX=9,   RT_HW_UART2_TX=8,   RT_HW_UART2_DE=255};
//--------------------------------Параметры I2C----------------------------------------------------
enum {RT_HW_I2C0_SDA=20,  RT_HW_I2C0_SCL=21,
      RT_HW_I2C1_SDA=14,  RT_HW_I2C1_SCL=15}; 
//--------------------------------Параметры SPI----------------------------------------------------	
enum {RT_HW_SPI0_SCK=2,  RT_HW_SPI0_MISO=4,  RT_HW_SPI0_MOSI=3,  RT_HW_SPI0_SS=5, 
	  RT_HW_SPI1_SCK=10, RT_HW_SPI1_MISO=12, RT_HW_SPI1_MOSI=11, RT_HW_SPI1_SS=13};
//=================================================================================================
#define RT_HW_BOARD_CHECK_PIN				//--Разрешение проверки на допустимость использования пинов [функции checkPinXXX(uint8_t pin)];
//--------------------------------Доступные пины контроллера---------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_ALL[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,
											  16,17,18,19,20,21,22,23,24,25,26,27,28,29,		RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DIN[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,
											  16,17,18,19,20,21,22,23,24,25,26,27,28,29,		RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_ADC[] 	={26,27,28,29,   									RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_TCH[] 	={													RT_HW_PGM_END};									
const uint8_t PROGMEM RT_HW_PGM_PIN_DOT[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,
											  16,17,18,19,20,21,22,23,24,25,26,27,28,29,	    RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_PWM[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,
											  16,17,18,19,20,21,22,23,24,25,26,27,28,29,		RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DAC[] 	={													RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_INT[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,
											  16,17,18,19,20,21,22,23,24,25, 26,27,28,29,		RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_N5V[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,
											  16,17,18,19,20,21,22,23,24,25,26,27,28,29,		RT_HW_PGM_END};
//=================================================================================================
//--------------------------------Параметры коммуникаций-------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_UHS[] 	={RT_HW_UART0_RX, RT_HW_UART0_TX,  RT_HW_UART0_DE,	//--UART0;
										      RT_HW_UART1_RX, RT_HW_UART1_TX,  RT_HW_UART1_DE,	//--UART1; 
											  RT_HW_UART2_RX, RT_HW_UART2_TX,  RT_HW_UART2_DE,	//--UART2; 										  
																		       RT_HW_PGM_END};
//-------------------------------------------------------------------------------------------------											  						
const uint8_t PROGMEM RT_HW_PGM_PIN_USS[]	={                                  RT_HW_PGM_END};	//--UARTS:rx,tx,de; 
//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_I2C[]	={RT_HW_I2C0_SDA, RT_HW_I2C0_SCL,   
                                              RT_HW_I2C1_SDA, RT_HW_I2C1_SCL,   RT_HW_PGM_END}; //--i2c:  sda,scl;
//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_SPI[]	={RT_HW_SPI0_SCK, RT_HW_SPI0_MISO,  RT_HW_SPI0_MOSI, RT_HW_SPI0_SS, 
                                              RT_HW_SPI1_SCK, RT_HW_SPI1_MISO,  RT_HW_SPI1_MOSI, RT_HW_SPI1_SS,
                                                                                RT_HW_PGM_END};	//--SPI:  sck,miso,mosi,ss
const uint8_t PROGMEM RT_HW_PGM_PIN_SPF[]	={			         				RT_HW_PGM_END}; //--SPQ: sck,miso,mosi,cs;	
const uint8_t PROGMEM RT_HW_PGM_PIN_SDC[]	={				                    RT_HW_PGM_END}; //--SDIO: DO,D1,D2,D3,SCK;
const uint8_t PROGMEM RT_HW_PGM_PIN_SPN[]	={									RT_HW_PGM_END}; //--SSPI: sck,miso,mosi,cs;		
//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_ETH[]	={				                    RT_HW_PGM_END};	//--numSPI; cs,int,rst;
const uint8_t PROGMEM RT_HW_PGM_PIN_CAN[]	={								    RT_HW_PGM_END};	//--CAN:  rx,tx;
//--------------------------------Системные пины---------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_BRD[]	={28,255,22,26,27,	    			RT_HW_PGM_END};	//--Control,LED,Button,ADC,PWM,WS2812
//--------------------------------SPI пины cs------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_CSX[]	={ 5, 6, 7,19,13,16,17,18,	    	RT_HW_PGM_END};	//--SPI: cs0,cs1,cs2,cs3
//--------------------------------Дисплейные пины--------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_LC4[]	={27,255,26,25,24,23,22,			RT_HW_PGM_END};	//--RS,E2(RW),E1,D4-D7;
const uint8_t PROGMEM RT_HW_PGM_PIN_LC6[]	={28,255,29,30,32,32,33,34,35,36,37,RT_HW_PGM_END};	//--RS,E2(RW),E1,D0-D7;
const uint8_t PROGMEM RT_HW_PGM_PIN_TFT[]	={	    	            			RT_HW_PGM_END};	//--;
//--------------------------------Тестовые пины----------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_TST_DIS[]	={          	    				RT_HW_PGM_END};	//--Дискретные сигналы;
const uint8_t PROGMEM RT_HW_PGM_TST_ANL[]	={27,       						RT_HW_PGM_END};	//--Аналоговые сигналы: ADC1,PWM1;
const uint8_t PROGMEM RT_HW_PGM_TST_SRV[]	={           	   				    RT_HW_PGM_END};	//--Servo1,Servo2;
const uint8_t PROGMEM RT_HW_PGM_TST_DEV[]	={17,255,18,           				RT_HW_PGM_END};	//--Устройства: 1-Wire,DHT22,HC-SR04.trig,HC-SR04.echo,
const uint8_t PROGMEM RT_HW_PGM_TST_URT[]	={1,2,            		   		    RT_HW_PGM_END};	//--UART: Nextion, ModBus;
//-------------------------------------------------------------------------------------------------
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

