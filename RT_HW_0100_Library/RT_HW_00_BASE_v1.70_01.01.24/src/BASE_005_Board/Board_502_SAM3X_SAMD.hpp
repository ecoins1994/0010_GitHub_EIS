//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							1.Контроллер типа DUE
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if !defined(RT_HW_BOARD_SELECT) && defined(RT_HW_BOARD_SAM3X_DUE)						
#define      RT_HW_BOARD_SELECT 	             "BOARD SAM3X DUE"			//--Идентификатор выбора платы;
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_UART0													//--Разрешение работы с UART0;
#define RT_HW_PERMIT_UART1													//--Разрешение работы с UART1; 
#define RT_HW_PERMIT_UART2													//--Разрешение работы с UART2; 
#define RT_HW_PERMIT_UART3													//--Разрешение работы с UART3;  
#define RT_HW_PERMIT_I2C0													//--Разрешение работы с i2c0; 
#define RT_HW_PERMIT_SPI0													//--Разрешение работы с spi0;
//=================================================================================================
//--------------------------------Параметры UART---------------------------------------------------	
enum {RT_HW_UART0_RX=0,   RT_HW_UART0_TX=1,   RT_HW_UART0_DE=38,
	  RT_HW_UART1_RX=19,  RT_HW_UART1_TX=18,  RT_HW_UART1_DE=39, 
	  RT_HW_UART2_RX=17,  RT_HW_UART2_TX=16,  RT_HW_UART2_DE=40,
	  RT_HW_UART3_RX=15,  RT_HW_UART3_TX=14,  RT_HW_UART3_DE=41};
//--------------------------------Параметры I2C----------------------------------------------------
enum {RT_HW_I2C0_SDA=20,  RT_HW_I2C0_SCL=21}; 
//--------------------------------Параметры SPI----------------------------------------------------	
enum {RT_HW_SPI0_SCK=52,  RT_HW_SPI0_MISO=50,  RT_HW_SPI0_MOSI=51,  RT_HW_SPI0_SS=53};
//=================================================================================================
#define RT_HW_BOARD_CHECK_PIN				//--Разрешение проверки на допустимость использования пинов [функции checkPinXXX(uint8_t pin)];
//--------------------------------Доступные пины контроллера---------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_ALL[]	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,
										      16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,
										      32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,
										      48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,
										      64,65,66,67,68,69,70,71,							RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DIN[]	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,
										      16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,
										      32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,
										      48,49,50,51,52,53,								RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_ADC[]	={54,55,56,57,58,59,60,61,62,63,64,	RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_TCH[]	={													RT_HW_PGM_END};									
const uint8_t PROGMEM RT_HW_PGM_PIN_DOT[]	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,
										      16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,
										      32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,
										      48,49,50,51,52,53, 								RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_PWM[]	={ 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,44,45,46,		RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DAC[]	={67,												RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_INT[]	={ 2, 3,18,19,20,21,								RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_N5V[]	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,
										      16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,
										      32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,
										      48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,
										      64,65,66,67,68,69,70,71,							RT_HW_PGM_END};	
//=================================================================================================
//--------------------------------Параметры коммуникаций-------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_UHS[] 	={RT_HW_UART0_RX, RT_HW_UART0_TX,  RT_HW_UART0_DE,	//--UART0;
										      RT_HW_UART1_RX, RT_HW_UART1_TX,  RT_HW_UART1_DE,	//--UART1; 
											  RT_HW_UART2_RX, RT_HW_UART2_TX,  RT_HW_UART2_DE,	//--UART2; 
										      RT_HW_UART3_RX, RT_HW_UART3_TX,  RT_HW_UART3_DE,	//--UART3;										  
																		       RT_HW_PGM_END};
//-------------------------------------------------------------------------------------------------											  						
const uint8_t PROGMEM RT_HW_PGM_PIN_USS[]	={                                             };	//--UARTS:rx,tx,de; 
//--------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_I2C[]	={RT_HW_I2C0_SDA, RT_HW_I2C0_SCL,   RT_HW_PGM_END}; //--i2c:  sda,scl;
//--------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_SPI[]	={RT_HW_SPI0_SCK, RT_HW_SPI0_MISO,  RT_HW_SPI0_MOSI, RT_HW_SPI0_SS, RT_HW_PGM_END};	//--SPI:  sck,miso,mosi,ss
const uint8_t PROGMEM RT_HW_PGM_PIN_SPF[]	={			         			    RT_HW_PGM_END}; //--SPF: sck,miso,mosi,cs;	
const uint8_t PROGMEM RT_HW_PGM_PIN_SDC[]	={                                  RT_HW_PGM_END}; //--SDIO: DO,D1,D2,D3,SCK;	
const uint8_t PROGMEM RT_HW_PGM_PIN_SPN[]	={ 8, 9,10,11,						RT_HW_PGM_END}; //--SSPI: sck,miso,mosi,cs;	
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_ETH[]	={				                    RT_HW_PGM_END};	//--numSPI; cs,int,rst;
const uint8_t PROGMEM RT_HW_PGM_PIN_CAN[]	={								    RT_HW_PGM_END};	//--CAN:  rx,tx;
//--------------------------------Системные пины---------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_BRD[]	={10,13,8,54,5,	    				RT_HW_PGM_END};	//--Control,LED,Button,ADC,PWM,WS2812
//--------------------------------SPI пины cs------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_CSX[]	={46,47,48,49,	    				RT_HW_PGM_END};	//--SPI: cs0,cs1,cs2,cs3
//--------------------------------Дисплейные пины--------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_LC4[]	={27,255,26,25,24,23,22,			RT_HW_PGM_END};	//--RS,E2(RW),E1,D4-D7;
const uint8_t PROGMEM RT_HW_PGM_PIN_LC6[]	={28,255,29,30,32,32,33,34,35,36,37,RT_HW_PGM_END};	//--RS,E2(RW),E1,D0-D7;
const uint8_t PROGMEM RT_HW_PGM_PIN_TFT[]	={	    	            			RT_HW_PGM_END};	//--;
//--------------------------------Тестовые пины----------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_TST_DIS[]	={          	    				RT_HW_PGM_END};	//--Дискретные сигналы;
const uint8_t PROGMEM RT_HW_PGM_TST_ANL[]	={55,6,       						RT_HW_PGM_END};	//--Аналоговые сигналы: ADC1,PWM1;
const uint8_t PROGMEM RT_HW_PGM_TST_SRV[]	={12,           	   				RT_HW_PGM_END};	//--Servo1,Servo2;
const uint8_t PROGMEM RT_HW_PGM_TST_DEV[]	={7,4,3,2,           				RT_HW_PGM_END};	//--Устройства: 1-Wire,DHT22,HC-SR04.trig,HC-SR04.echo,
const uint8_t PROGMEM RT_HW_PGM_TST_URT[]	={1,2,            		   		    RT_HW_PGM_END};	//--UART: Nextion, ModBus;
//-------------------------------------------------------------------------------------------------
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
