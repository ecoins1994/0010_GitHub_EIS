//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							1.Контроллер типа Generic ESP8266 Module
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if !defined(RT_HW_BOARD_SELECT) && defined(RT_HW_BOARD_ESP8266_GENERIC) 					
#define      RT_HW_BOARD_SELECT 	"BOARD ESP8266 GENERIC"	//--Идентификатор выбора платы;
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_UART0					//--Разрешение работы с UART0; 
#define RT_HW_PERMIT_UART1					//--Разрешение работы с UART1;  
#define RT_HW_PERMIT_SERIALS				//--Разрешение работы с SoftSerial;
enum {RT_HW_UARTS_RX=RT_HW_D3, RT_HW_UARTS_TX=RT_HW_D4, RT_HW_UARTS_DE=255}; //--D3,D4;
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_I2C0					//--Разрешение работы с i2c0; 
#define RT_HW_PERMIT_SPI0					//--Разрешение работы с spi0; 
//-------------------------------------------------------------------------------------------------
//							Разрешение создание объектов
//-------------------------------------------------------------------------------------------------
#define RT_HW_CREATE_UARTS  				//--Разрешение создание объекта SoftSerial;
//--------------------------------Параметры UART---------------------------------------------------	
enum {RT_HW_UART0_RX=RT_HW_RX,	RT_HW_UART0_TX=RT_HW_TX,   RT_HW_UART0_DE=255,
	  RT_HW_UART1_RX=255, 		RT_HW_UART1_TX=RT_HW_TX1,  RT_HW_UART1_DE=255, 
	  RT_HW_UART2_RX=RT_HW_RX2, RT_HW_UART2_TX=RT_HW_TX2,  RT_HW_UART2_DE=255};
//--------------------------------Параметры I2C----------------------------------------------------
enum {RT_HW_I2C0_SDA=RT_HW_D2,  RT_HW_I2C0_SCL=RT_HW_D1}; 
//--------------------------------Параметры SPI----------------------------------------------------	
enum {RT_HW_SPI0_SCK=RT_HW_D5,  RT_HW_SPI0_MISO=RT_HW_D6,  RT_HW_SPI0_MOSI=RT_HW_D7,  RT_HW_SPI0_SS=RT_HW_D0};
//=================================================================================================
#define RT_HW_BOARD_CHECK_PIN				//--Разрешение проверки на допустимость использования пинов [функции checkPinXXX(uint8_t pin)];
//--------------------------------Доступные пины контроллера---------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_ALL[]	={RT_HW_D0, RT_HW_D1, RT_HW_D2, RT_HW_D3, RT_HW_D4, 
                                              RT_HW_D5, RT_HW_D6, RT_HW_D7, RT_HW_D8, RT_HW_D9, RT_HW_D10, RT_HW_A0, RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DIN[]	={255,      RT_HW_D1, RT_HW_D2, RT_HW_D3, RT_HW_D4, RT_HW_D5,
											  RT_HW_D6, RT_HW_D7, RT_HW_D8, RT_HW_D9, RT_HW_D10,RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_ADC[]	={RT_HW_A0,									        RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_TCH[]	={										            RT_HW_PGM_END};									
const uint8_t PROGMEM RT_HW_PGM_PIN_DOT[]	={RT_HW_D0, RT_HW_D1, RT_HW_D2, RT_HW_D3, RT_HW_D4,
                                              RT_HW_D5, RT_HW_D6, RT_HW_D7, RT_HW_D8,			RT_HW_PGM_END}; 
const uint8_t PROGMEM RT_HW_PGM_PIN_PWM[]	={255,      RT_HW_D1, RT_HW_D2, RT_HW_D3, RT_HW_D4,
                                              RT_HW_D5, RT_HW_D6, RT_HW_D7, RT_HW_D8,			RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DAC[]	={													RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_INT[]	={255,      RT_HW_D1, RT_HW_D2, RT_HW_D3, RT_HW_D4,
											  RT_HW_D5, RT_HW_D6, RT_HW_D7, RT_HW_D8,			RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_N5V[]	={RT_HW_D0, RT_HW_D1, RT_HW_D2, RT_HW_D3, RT_HW_D4,
											  RT_HW_D5, RT_HW_D6, RT_HW_D7, RT_HW_D8, RT_HW_D9, RT_HW_D10, RT_HW_A0, RT_HW_PGM_END};	
//=================================================================================================
//--------------------------------Параметры коммуникаций-------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_UHS[] 	={RT_HW_UART0_RX, RT_HW_UART0_TX,  RT_HW_UART0_DE,	//--UART0;
										      RT_HW_UART1_RX, RT_HW_UART1_TX,  RT_HW_UART1_DE,	//--UART1; 
											  RT_HW_UART2_RX, RT_HW_UART2_TX,  RT_HW_UART2_DE,	//--UART2; ;										  
																		       RT_HW_PGM_END};
//-------------------------------------------------------------------------------------------------											  						
const uint8_t PROGMEM RT_HW_PGM_PIN_USS[]	={RT_HW_UARTS_RX, RT_HW_UARTS_TX, RT_HW_UARTS_DE,RT_HW_PGM_END};	//--UARTS:rx,tx,de; 
//--------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_I2C[]	={RT_HW_I2C0_SDA, RT_HW_I2C0_SCL,   RT_HW_PGM_END}; //--i2c:  sda,scl;
//--------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_SPI[]	={RT_HW_SPI0_SCK, RT_HW_SPI0_MISO,  RT_HW_SPI0_MOSI, RT_HW_SPI0_SS, RT_HW_PGM_END};	//--SPI:  sck,miso,mosi,ss
const uint8_t PROGMEM RT_HW_PGM_PIN_SPF[]	={						         	RT_HW_PGM_END};  //--SPQ: sck,miso,mosi,cs;	
const uint8_t PROGMEM RT_HW_PGM_PIN_SDC[]	={				                    RT_HW_PGM_END};  //--SDIO: DO,D1,D2,D3,SCK;
const uint8_t PROGMEM RT_HW_PGM_PIN_SPN[]	={          						RT_HW_PGM_END};  //--SSPI: sck,miso,mosi,cs;		
//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_ETH[]	={				                    RT_HW_PGM_END};	//--numSPI; cs,int,rst;
const uint8_t PROGMEM RT_HW_PGM_PIN_CAN[]	={								    RT_HW_PGM_END};	//--CAN:  rx,tx;
//--------------------------------Системные пины---------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_BRD[]	={RT_HW_D0,RT_HW_D4,255,RT_HW_A0,255,RT_HW_PGM_END};	//--Control,LED,Button,ADC,PWM,WS2812
//--------------------------------SPI пины cs------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_CSX[]	={RT_HW_SPI0_SS,	    			RT_HW_PGM_END};	//--SPI: cs0,cs1,cs2,cs3
//--------------------------------Дисплейные пины--------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_LC4[]	={									RT_HW_PGM_END};	//--RS,E2(RW),E1,D4-D7;
const uint8_t PROGMEM RT_HW_PGM_PIN_LC6[]	={									RT_HW_PGM_END};	//--RS,E2(RW),E1,D0-D7;
const uint8_t PROGMEM RT_HW_PGM_PIN_TFT[]	={	    	            			RT_HW_PGM_END};	//--;
//--------------------------------Тестовые пины----------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_TST_DIS[]	={          	    				RT_HW_PGM_END};	//--Дискретные сигналы;
const uint8_t PROGMEM RT_HW_PGM_TST_ANL[]	={         						    RT_HW_PGM_END};	//--Аналоговые сигналы: ADC1,PWM1;
const uint8_t PROGMEM RT_HW_PGM_TST_SRV[]	={            	   				    RT_HW_PGM_END};	//--Servo1,Servo2;
const uint8_t PROGMEM RT_HW_PGM_TST_DEV[]	={RT_HW_D3,255,RT_HW_D8,           	RT_HW_PGM_END};	//--Устройства: 1-Wire,DHT22,HC-SR04.trig,HC-SR04.echo,
const uint8_t PROGMEM RT_HW_PGM_TST_URT[]	={2,99,           		   		    RT_HW_PGM_END};	//--UART: Nextion, ModBus;
//-------------------------------------------------------------------------------------------------
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
