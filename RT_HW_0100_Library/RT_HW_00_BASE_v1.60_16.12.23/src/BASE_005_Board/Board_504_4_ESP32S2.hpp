//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							1.Контроллер типа ESP32S2 Dev module
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if !defined(RT_HW_BOARD_SELECT)  && defined(RT_HW_BOARD_ESP32S2_DEV)
#define      RT_HW_BOARD_SELECT 			      "BOARD ESP32S2 DEV"		//--Идентификатор выбора платы;
//-------------------------------------------------------------------------------------------------											
#define RT_HW_PERMIT_UART0													//--Разрешение работы с UART0; 
//#define RT_HW_PERMIT_UART1													//--Разрешение работы с UART1; 
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_I2C0													//--Разрешение работы с i2c0; 
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_SPI0													//--Разрешение работы с spi0;
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_DAC													//--Разрешение работы с DAC;
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_WS													
//--------------------------------Параметры UART---------------------------------------------------	
enum {RT_HW_UART0_RX=33,  RT_HW_UART0_TX=38,   RT_HW_UART0_DE=255};
//--------------------------------Параметры I2C----------------------------------------------------
enum {RT_HW_I2C0_SDA=8,   RT_HW_I2C0_SCL=9}; 
//--------------------------------Параметры SPI----------------------------------------------------	
enum {RT_HW_SPI0_SCK=36,  RT_HW_SPI0_MISO=37,  RT_HW_SPI0_MOSI=35,  RT_HW_SPI0_SS=34};
//=================================================================================================
#define RT_HW_BOARD_CHECK_PIN				//--Разрешение проверки на допустимость использования пинов [функции checkPinXXX(uint8_t pin)];
//--------------------------------Доступные пины контроллера---------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_ALL[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,
										      20,21, 				  33,34,35,36,39,40,41,42,43,44,45,  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DIN[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,
										      20,21, 				  33,34,35,36,39,40,41,42,43,44,45,  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_ADC[] 	={     1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14, 	            RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_TCH[] 	={     1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14, 	            RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_DOT[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,
										      20,21, 				  33,34,35,36,39,40,41,42,43,44,45,  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_PWM[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,
										      20,21, 				  33,34,35,36,39,40,41,42,43,44,45,  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DAC[] 	={17,18,													  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_INT[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,
										      20,21, 				  33,34,35,36,39,40,41,42,43,44,45,  	RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_N5V[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,
										      20,21, 				  33,34,35,36,39,40,41,42,43,44,45,  	RT_HW_PGM_END};	
//=================================================================================================
//--------------------------------Параметры коммуникаций-------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_UHS[] 	={RT_HW_UART0_RX, RT_HW_UART0_TX,  RT_HW_UART0_DE, RT_HW_PGM_END};
//-------------------------------------------------------------------------------------------------											  						
const uint8_t PROGMEM RT_HW_PGM_PIN_USS[]	={                                 RT_HW_PGM_END}; //--UARTS:rx,tx,de; 
//--------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_I2C[]	={RT_HW_I2C0_SDA, RT_HW_I2C0_SCL,  RT_HW_PGM_END}; //--i2c:  sda,scl;
//--------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_SPI[]	={RT_HW_SPI0_SCK, RT_HW_SPI0_MISO, RT_HW_SPI0_MOSI, RT_HW_SPI0_SS, RT_HW_PGM_END};	//--SPI:  sck,miso,mosi,ss
const uint8_t PROGMEM RT_HW_PGM_PIN_SPF[]	={						         	RT_HW_PGM_END}; //--SPF: sck,miso,mosi,cs;	
const uint8_t PROGMEM RT_HW_PGM_PIN_SDC[]	={				                    RT_HW_PGM_END}; //--SDIO: DO,D1,D2,D3,SCK;
const uint8_t PROGMEM RT_HW_PGM_PIN_SPN[]	={          						RT_HW_PGM_END}; //--SSPI: sck,miso,mosi,cs;	
//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_ETH[]	={				                    RT_HW_PGM_END};	//--numSPI; cs,int,rst;
const uint8_t PROGMEM RT_HW_PGM_PIN_CAN[]	={								    RT_HW_PGM_END};	//--CAN:  rx,tx;
//--------------------------------Системные пины---------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_BRD[]	={13, 18, 14,36,      	    	    RT_HW_PGM_END};	//--Control,LED,Button,ADC,PWM,WS2812
//--------------------------------SPI пины cs------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_CSX[]	={ 5,  4, 15, 2,	    			RT_HW_PGM_END};	//--SPI: cs0,cs1,cs2,cs3
//--------------------------------Дисплейные пины--------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_LC4[]	={									RT_HW_PGM_END};	//--RS,E2(RW),E1,D4-D7;
const uint8_t PROGMEM RT_HW_PGM_PIN_LC6[]	={									RT_HW_PGM_END};	//--RS,E2(RW),E1,D0-D7;
const uint8_t PROGMEM RT_HW_PGM_PIN_TFT[]	={	    	            			RT_HW_PGM_END};	//--;
//--------------------------------Тестовые пины----------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_TST_DIS[]	={          	    				RT_HW_PGM_END};	//--Дискретные сигналы;
const uint8_t PROGMEM RT_HW_PGM_TST_ANL[]	={39,       						RT_HW_PGM_END};	//--Аналоговые сигналы: ADC1,PWM1;
const uint8_t PROGMEM RT_HW_PGM_TST_SRV[]	={           	   				    RT_HW_PGM_END};	//--Servo1,Servo2;
const uint8_t PROGMEM RT_HW_PGM_TST_DEV[]	={33, 13,32,           				RT_HW_PGM_END};	//--Устройства: 1-Wire,DHT22,HC-SR04.trig,HC-SR04.echo,
const uint8_t PROGMEM RT_HW_PGM_TST_URT[]	={1,2,            		   		    RT_HW_PGM_END};	//--UART: ModBus, Nextion;
//-------------------------------------------------------------------------------------------------
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							2.Контроллер типа ESP32S2 LOLIN S2 PRO
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if !defined(RT_HW_BOARD_SELECT)  && defined(ARDUINO_LOLIN_S2_PRO)
#define      RT_HW_BOARD_SELECT 			  "BOARD LOLIN S2 PRO"			//--Идентификатор выбора платы;
//-------------------------------------------------------------------------------------------------											
#define RT_HW_PERMIT_UART0													//--Разрешение работы с UART0; 
//#define RT_HW_PERMIT_UART1												//--Разрешение работы с UART1; 
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_I2C0													//--Разрешение работы с i2c0; 
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_SPI0													//--Разрешение работы с spi0;
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_DAC													//--Разрешение работы с DAC;
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_WS													
//--------------------------------Параметры UART---------------------------------------------------	
enum {RT_HW_UART0_RX=33,  RT_HW_UART0_TX=38,   RT_HW_UART0_DE=255};
//--------------------------------Параметры I2C----------------------------------------------------
enum {RT_HW_I2C0_SDA=8,   RT_HW_I2C0_SCL=9}; 
//--------------------------------Параметры SPI----------------------------------------------------	
enum {RT_HW_SPI0_SCK=36,  RT_HW_SPI0_MISO=37,  RT_HW_SPI0_MOSI=35,  RT_HW_SPI0_SS=34};
//=================================================================================================
#define RT_HW_BOARD_CHECK_PIN				//--Разрешение проверки на допустимость использования пинов [функции checkPinXXX(uint8_t pin)];
//--------------------------------Доступные пины контроллера---------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_ALL[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,
										      20,21, 				  33,34,35,36,39,40,41,42,43,44,45,  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DIN[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,
										      20,21, 				  33,34,35,36,39,40,41,42,43,44,45,  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_ADC[] 	={     1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14, 	            RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_TCH[] 	={     1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14, 	            RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_DOT[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,
										      20,21, 				  33,34,35,36,39,40,41,42,43,44,45,  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_PWM[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,
										      20,21, 				  33,34,35,36,39,40,41,42,43,44,45,  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DAC[] 	={17,18,													  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_INT[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,
										      20,21, 				  33,34,35,36,39,40,41,42,43,44,45,  	RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_N5V[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,
										      20,21, 				  33,34,35,36,39,40,41,42,43,44,45,  	RT_HW_PGM_END};	
//=================================================================================================
//--------------------------------Параметры коммуникаций-------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_UHS[] 	={RT_HW_UART0_RX, RT_HW_UART0_TX,  RT_HW_UART0_DE, RT_HW_PGM_END};
//-------------------------------------------------------------------------------------------------											  						
const uint8_t PROGMEM RT_HW_PGM_PIN_USS[]	={                                 RT_HW_PGM_END}; //--UARTS:rx,tx,de; 
//--------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_I2C[]	={RT_HW_I2C0_SDA, RT_HW_I2C0_SCL,  RT_HW_PGM_END}; //--i2c:  sda,scl;
//--------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_SPI[]	={RT_HW_SPI0_SCK, RT_HW_SPI0_MISO, RT_HW_SPI0_MOSI, RT_HW_SPI0_SS, RT_HW_PGM_END};	//--SPI:  sck,miso,mosi,ss
const uint8_t PROGMEM RT_HW_PGM_PIN_SPF[]	={						         	RT_HW_PGM_END}; //--SPF: sck,miso,mosi,cs;	
const uint8_t PROGMEM RT_HW_PGM_PIN_SDC[]	={				                    RT_HW_PGM_END}; //--SDIO: DO,D1,D2,D3,SCK;
const uint8_t PROGMEM RT_HW_PGM_PIN_SPN[]	={          						RT_HW_PGM_END}; //--SSPI: sck,miso,mosi,cs;	
//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_ETH[]	={				                    RT_HW_PGM_END};	//--numSPI; cs,int,rst;
const uint8_t PROGMEM RT_HW_PGM_PIN_CAN[]	={								    RT_HW_PGM_END};	//--CAN:  rx,tx;
//--------------------------------Системные пины---------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_BRD[]	={13, 18, 14,36,      	    	    RT_HW_PGM_END};	//--Control,LED,Button,ADC,PWM,WS2812
//--------------------------------SPI пины cs------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_CSX[]	={ 5,  4, 15, 2,	    			RT_HW_PGM_END};	//--SPI: cs0,cs1,cs2,cs3
//--------------------------------Дисплейные пины--------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_LC4[]	={									RT_HW_PGM_END};	//--RS,E2(RW),E1,D4-D7;
const uint8_t PROGMEM RT_HW_PGM_PIN_LC6[]	={									RT_HW_PGM_END};	//--RS,E2(RW),E1,D0-D7;
const uint8_t PROGMEM RT_HW_PGM_PIN_TFT[]	={	    	            			RT_HW_PGM_END};	//--;
//--------------------------------Тестовые пины----------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_TST_DIS[]	={          	    				RT_HW_PGM_END};	//--Дискретные сигналы;
const uint8_t PROGMEM RT_HW_PGM_TST_ANL[]	={39,       						RT_HW_PGM_END};	//--Аналоговые сигналы: ADC1,PWM1;
const uint8_t PROGMEM RT_HW_PGM_TST_SRV[]	={           	   				    RT_HW_PGM_END};	//--Servo1,Servo2;
const uint8_t PROGMEM RT_HW_PGM_TST_DEV[]	={33, 13,32,           				RT_HW_PGM_END};	//--Устройства: 1-Wire,DHT22,HC-SR04.trig,HC-SR04.echo,
const uint8_t PROGMEM RT_HW_PGM_TST_URT[]	={1,2,            		   		    RT_HW_PGM_END};	//--UART: ModBus, Nextion;
//-------------------------------------------------------------------------------------------------
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							3.Контроллер типа ESP32 LOLIN S2 MINI [esp32.variant]
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if !defined(RT_HW_BOARD_SELECT)  && defined(RT_HW_BOARD_LOLIN_S2_MINI)
#define      RT_HW_BOARD_SELECT 			      "BOARD LOLIN S2 MINI"		//--Идентификатор выбора платы;
//-------------------------------------------------------------------------------------------------											
#define RT_HW_PERMIT_UART0													//--Разрешение работы с UART0; 
//#define RT_HW_PERMIT_UART1												//--Разрешение работы с UART1; 
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_I2C0													//--Разрешение работы с i2c0; 
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_SPI0													//--Разрешение работы с spi0;
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_DAC													//--Разрешение работы с DAC;
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_WS													
//--------------------------------Параметры UART---------------------------------------------------	
enum {RT_HW_UART0_RX=33,  RT_HW_UART0_TX=38,   RT_HW_UART0_DE=255};
//--------------------------------Параметры I2C----------------------------------------------------
enum {RT_HW_I2C0_SDA=8,   RT_HW_I2C0_SCL=9}; 
//--------------------------------Параметры SPI----------------------------------------------------	
enum {RT_HW_SPI0_SCK=36,  RT_HW_SPI0_MISO=37,  RT_HW_SPI0_MOSI=35,  RT_HW_SPI0_SS=34};
//=================================================================================================
#define RT_HW_BOARD_CHECK_PIN				//--Разрешение проверки на допустимость использования пинов [функции checkPinXXX(uint8_t pin)];
//--------------------------------Доступные пины контроллера---------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_ALL[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,
										      20,21, 				  33,34,35,36,39,40,41,42,43,44,45,  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DIN[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,
										      20,21, 				  33,34,35,36,39,40,41,42,43,44,45,  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_ADC[] 	={     1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14, 	            RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_TCH[] 	={     1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14, 	            RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_DOT[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,
										      20,21, 				  33,34,35,36,39,40,41,42,43,44,45,  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_PWM[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,
										      20,21, 				  33,34,35,36,39,40,41,42,43,44,45,  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DAC[] 	={17,18,													  	RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_INT[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,
										      20,21, 				  33,34,35,36,39,40,41,42,43,44,45,  	RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_N5V[] 	={ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,
										      20,21, 				  33,34,35,36,39,40,41,42,43,44,45,  	RT_HW_PGM_END};	
//=================================================================================================
//--------------------------------Параметры коммуникаций-------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_UHS[] 	={RT_HW_UART0_RX, RT_HW_UART0_TX,  RT_HW_UART0_DE, RT_HW_PGM_END};
//-------------------------------------------------------------------------------------------------											  						
const uint8_t PROGMEM RT_HW_PGM_PIN_USS[]	={                                 RT_HW_PGM_END}; //--UARTS:rx,tx,de; 
//--------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_I2C[]	={RT_HW_I2C0_SDA, RT_HW_I2C0_SCL,  RT_HW_PGM_END}; //--i2c:  sda,scl;
//--------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_SPI[]	={RT_HW_SPI0_SCK, RT_HW_SPI0_MISO, RT_HW_SPI0_MOSI, RT_HW_SPI0_SS, RT_HW_PGM_END};	//--SPI:  sck,miso,mosi,ss
const uint8_t PROGMEM RT_HW_PGM_PIN_SPF[]	={						         	RT_HW_PGM_END}; //--SPF: sck,miso,mosi,cs;	
const uint8_t PROGMEM RT_HW_PGM_PIN_SDC[]	={				                    RT_HW_PGM_END}; //--SDIO: DO,D1,D2,D3,SCK;
const uint8_t PROGMEM RT_HW_PGM_PIN_SPN[]	={          						RT_HW_PGM_END}; //--SSPI: sck,miso,mosi,cs;	
//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_ETH[]	={				                    RT_HW_PGM_END};	//--numSPI; cs,int,rst;
const uint8_t PROGMEM RT_HW_PGM_PIN_CAN[]	={								    RT_HW_PGM_END};	//--CAN:  rx,tx;
//--------------------------------Системные пины---------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_BRD[]	={13, 18, 14,36,      	    	    RT_HW_PGM_END};	//--Control,LED,Button,ADC,PWM,WS2812
//--------------------------------SPI пины cs------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_CSX[]	={ 5,  4, 15, 2,	    			RT_HW_PGM_END};	//--SPI: cs0,cs1,cs2,cs3
//--------------------------------Дисплейные пины--------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_LC4[]	={									RT_HW_PGM_END};	//--RS,E2(RW),E1,D4-D7;
const uint8_t PROGMEM RT_HW_PGM_PIN_LC6[]	={									RT_HW_PGM_END};	//--RS,E2(RW),E1,D0-D7;
const uint8_t PROGMEM RT_HW_PGM_PIN_TFT[]	={	    	            			RT_HW_PGM_END};	//--;
//--------------------------------Тестовые пины----------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_TST_DIS[]	={          	    				RT_HW_PGM_END};	//--Дискретные сигналы;
const uint8_t PROGMEM RT_HW_PGM_TST_ANL[]	={39,       						RT_HW_PGM_END};	//--Аналоговые сигналы: ADC1,PWM1;
const uint8_t PROGMEM RT_HW_PGM_TST_SRV[]	={           	   				    RT_HW_PGM_END};	//--Servo1,Servo2;
const uint8_t PROGMEM RT_HW_PGM_TST_DEV[]	={33, 13,32,           				RT_HW_PGM_END};	//--Устройства: 1-Wire,DHT22,HC-SR04.trig,HC-SR04.echo,
const uint8_t PROGMEM RT_HW_PGM_TST_URT[]	={1,2,            		   		    RT_HW_PGM_END};	//--UART: ModBus, Nextion;
//-------------------------------------------------------------------------------------------------
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++