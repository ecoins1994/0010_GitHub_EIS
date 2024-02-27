//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							1.Контроллер типа STM32F103C
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if !defined(RT_HW_BOARD_SELECT) && defined(RT_HW_BOARD_STM32F103CXX)
//----------------------------------------------------------------------------------------------------
#define RT_HW_BOARD_SELECT	        "Board STM32F103XX" 
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_UART0					//--Разрешение работы с UART0;
#define RT_HW_PERMIT_UART1					//--Разрешение работы с UART1;
#define RT_HW_PERMIT_UART2					//--Разрешение работы с UART2;
#define RT_HW_PERMIT_UART3					//--Разрешение работы с UART3`````````````;
//-------------------------------------------------------------------------------------------------
//#define RT_HW_STM32_SERIAL2					//--Разрешение создания объекта UART2
//#define RT_HW_STM32_SERIAL3					//--Разрешение создания объекта UART3
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_I2C0					//--Разрешение работы с i2c0;
#define RT_HW_PERMIT_I2C1					//--Разрешение работы с i2c1;
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_SPI0					//--Разрешение работы с SPI0;
//#define RT_HW_PERMIT_SPI1					//--Разрешение работы с SPI1;
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_CAN					//--Разрешение работы с CAN;
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_DAC					//--Разрешение работы с DAC;
//-------------------------------------------------------------------------------------------------
//							Permission to cteate with Link
//-------------------------------------------------------------------------------------------------
//#define RT_HW_CREATE_UART1					//--Permission to create Serail1 for UART1;
#define RT_HW_CREATE_UART2					//--Permission to create Serail2 for UART2;
#define RT_HW_CREATE_UART3					//--Permission to create Serail3 for UART3;
//-------------------------------------------------------------------------------------------------
#define RT_HW_CREATE_I2C1					//--Permission to create Wire1 for i2c1;
///-------------------------------------------------------------------------------------------------
#define RT_HW_CREATE_SPI1					//--Permission to work with SPI

//=================================================================================================
//--------------------------------Параметры UART---------------------------------------------------	
enum {RT_HW_UART0_RX=PA12, RT_HW_UART0_TX=PA11, RT_HW_UART0_DE=255,
	  RT_HW_UART1_RX=PA10, RT_HW_UART1_TX=PA9,  RT_HW_UART1_DE=255, 
	  RT_HW_UART2_RX=PA3,  RT_HW_UART2_TX=PA2,  RT_HW_UART2_DE=255,
	  RT_HW_UART3_RX=PB11, RT_HW_UART3_TX=PB10, RT_HW_UART3_DE=255};
//--------------------------------Параметры I2C----------------------------------------------------
enum {RT_HW_I2C0_SDA=PB7,  RT_HW_I2C0_SCL=PB6,
      RT_HW_I2C1_SDA=PB11, RT_HW_I2C1_SCL=PB10}; 
//--------------------------------Параметры SPI----------------------------------------------------	
enum {RT_HW_SPI0_SCK=PA5,  RT_HW_SPI0_MISO=PA6,  RT_HW_SPI0_MOSI=PA7,  RT_HW_SPI0_SS=PA4,  
      RT_HW_SPI1_SCK=PB13, RT_HW_SPI1_MISO=PB14, RT_HW_SPI1_MOSI=PB15, RT_HW_SPI1_SS=PB12};
//=================================================================================================
#define RT_HW_BOARD_CHECK_PIN				//--Разрешение проверки на допустимость использования пинов [функции checkPinXXX(uint8_t pin)];
//--------------------------------Доступные пины контроллера---------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_ALL[] 	={PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PA8,PA9,PA10,PA11,PA12,PA13,PA14,PA15,
											  PB0,PB1,PB2,PB3,PB4,PB5,PB6,PB7,PB8,PB9,PB10,PB11,PB12,PB13,PB14,PB15,
										      255,255,255,255,255,255,255,255,255,255, 255, 255, 255,PC13,PC14,PC15, RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DIN[] 	={PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PA8,PA9,PA10,PA11,PA12, 255, 255,PA15,
										      PB0,PB1,255,PB3,PB4,PB5,PB6,PB7,PB8,PB9,PB10,PB11,PB12,PB13,PB14,PB15, RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_ADC[] 	={PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PA8,PB0,PB1,		  					 RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_TCH[] 	={						 												 RT_HW_PGM_END};									
const uint8_t PROGMEM RT_HW_PGM_PIN_DOT[] 	={PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PA8,PA9,PA10,PA11,PA12, 255, 255,PA15,
										      PB0,PB1,255,PB3,PB4,PB5,PB6,PB7,PB8,PB9,PB10,PB11,PB12,PB13,PB14,PB15,
										      255,255,255,255,255,255,255,255,255,255, 255, 255, 255,PC13,PC14,PC15,RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_PWM[] 	={PA0,PA1,PA2,PA3,PA6,PA7,PA8,PA9,PA10,PB0,PB1,PB6,PB7,PB8,PB9,			RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DAC[] 	={																		RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_INT[] 	={PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PA8,PA9,PA10,PA11,PA12,PA13, 255, 255,
										      PB0,PB1,255,PB3,PB4,PB5,PB6,PB7,PB8,PB9,PB10,PB11,PB12,PB13,PB14,PB15,RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_N5V[] 	={PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PB0,PB1,PB5,PC13,PC14,PC15,			RT_HW_PGM_END};	
//=================================================================================================
//--------------------------------Коммуникационные пины--------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_UHS[] 	={RT_HW_UART0_RX, RT_HW_UART0_TX,  RT_HW_UART0_DE,	//--UART0;
										      RT_HW_UART1_RX, RT_HW_UART1_TX,  RT_HW_UART1_DE,	//--UART1; 
											  RT_HW_UART2_RX, RT_HW_UART2_TX,  RT_HW_UART2_DE,	//--UART2; 
										      RT_HW_UART3_RX, RT_HW_UART3_TX,  RT_HW_UART3_DE,	//--UART3;
										                                       RT_HW_PGM_END};
//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_USS[]	={                                 RT_HW_PGM_END};	//--UARTS; 
//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_I2C[]	={RT_HW_I2C0_SDA, RT_HW_I2C0_SCL,					//--I2C0;
                                              RT_HW_I2C1_SDA, RT_HW_I2C1_SCL,  RT_HW_PGM_END};  //--i2C1;
//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_SPI[]	={RT_HW_SPI0_SCK, RT_HW_SPI0_MISO, RT_HW_SPI0_MOSI, RT_HW_SPI0_SS, //--SPI0;	
                                              RT_HW_SPI1_SCK, RT_HW_SPI1_MISO, RT_HW_SPI1_MOSI, RT_HW_SPI1_SS,
																			   RT_HW_PGM_END};	//--SPI1:  sck,miso,mosi,ss
const uint8_t PROGMEM RT_HW_PGM_PIN_SPF[]	={PB0,PB1,PB2,         			   RT_HW_PGM_END};  //--SPQ: sck,miso,mosi,cs;	
const uint8_t PROGMEM RT_HW_PGM_PIN_SDC[]	={PA4,PA5,PA6,PA7,PA8,             RT_HW_PGM_END};  //--SDIO: DO,D1,D2,D3,SCK;
const uint8_t PROGMEM RT_HW_PGM_PIN_SPN[]	={          					   RT_HW_PGM_END};  //--SSPI: sck,miso,mosi,cs;		
//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_ETH[]	={				                   RT_HW_PGM_END};	//--numSPI; cs,int,rst;
const uint8_t PROGMEM RT_HW_PGM_PIN_CAN[]	={								   RT_HW_PGM_END};	//--CAN:  rx,tx;
//--------------------------------Системные пины---------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_BRD[]	={PB5,PC13,PA0,PA1,PB1,	    	   RT_HW_PGM_END};	//--Control,LED,Button,ADC,PWM,WS2812
//--------------------------------SPI пины cs------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_CSX[]	={PB12,PB13,PB14,PB15,	    	   RT_HW_PGM_END};	//--SPI: cs0,cs1,cs2,cs3
//--------------------------------Дисплейные пины--------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_LC4[]	={								   RT_HW_PGM_END};	//--RS,E2(RW),E1,D4-D7;
const uint8_t PROGMEM RT_HW_PGM_PIN_LC6[]	={								   RT_HW_PGM_END};	//--RS,E2(RW),E1,D0-D7;
const uint8_t PROGMEM RT_HW_PGM_PIN_TFT[]	={	    	            		   RT_HW_PGM_END};	//--numSPI; cs,dc,rst,led; t.cs,t.int; sd.cs;
//--------------------------------Тестовые пины----------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_TST_DIS[]	={          	    			   RT_HW_PGM_END};	//--Дискретные сигналы;
const uint8_t PROGMEM RT_HW_PGM_TST_ANL[]	={255,PB10,       				   RT_HW_PGM_END};	//--Аналоговые сигналы: ADC1,PWM1;
const uint8_t PROGMEM RT_HW_PGM_TST_SRV[]	={            	   				   RT_HW_PGM_END};	//--Servo1,Servo2;
const uint8_t PROGMEM RT_HW_PGM_TST_DEV[]	={PB8, PB9, PA8,            	   RT_HW_PGM_END};	//--Устройства: 1-Wire,DHT22,HC-SR04.trig,HC-SR04.echo;
const uint8_t PROGMEM RT_HW_PGM_TST_URT[]	={1,2,            		   		   RT_HW_PGM_END};	//--UART: Nextion, ModBus;								   
//-------------------------------------------------------------------------------------------------
#endif

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							2.Контроллер типа STM32F103R
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if !defined(RT_HW_BOARD_SELECT) && defined(RT_HW_BOARD_GENERIC_F103RETx) 
//-------------------------------------------------------------------------------------------------
#define RT_HW_BOARD_SELECT          "Board GENERIC F103RETX"
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_UART0					//--Разрешение работы с UART0;
#define RT_HW_PERMIT_UART1					//--Разрешение работы с UART1;
#define RT_HW_PERMIT_UART2					//--Разрешение работы с UART2;
#define RT_HW_PERMIT_UART3					//--Разрешение работы с UART3;
#define RT_HW_PERMIT_UART4					//--Разрешение работы с UART4;
#define RT_HW_PERMIT_UART5					//--Разрешение работы с UART5;
//-------------------------------------------------------------------------------------------------
#define RT_HW_STM32_SERIAL2					//--Разрешение создания объекта UART2
#define RT_HW_STM32_SERIAL3					//--Разрешение создания объекта UART3
#define RT_HW_STM32_SERIAL4					//--Разрешение создания объекта UART4
#define RT_HW_STM32_SERIAL5					//--Разрешение создания объекта UART5
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_I2C0					//--Разрешение работы с i2c0;
#define RT_HW_PERMIT_I2C1					//--Разрешение работы с i2c1;
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_SPI0					//--Разрешение работы с SPI0;
//#define RT_HW_PERMIT_SPI1					//--Разрешение работы с SPI1;
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_CAN					//--Разрешение работы с CAN;
//-------------------------------------------------------------------------------------------------
#define RT_HW_PERMIT_DAC					//--Разрешение работы с DAC;
//=================================================================================================
//--------------------------------Параметры UART---------------------------------------------------	
enum {RT_HW_UART0_RX=PA12, RT_HW_UART0_TX=PA11, RT_HW_UART0_DE=255,
	  RT_HW_UART1_RX=PA10, RT_HW_UART1_TX=PA9,  RT_HW_UART1_DE=255, 
	  RT_HW_UART2_RX=PA3,  RT_HW_UART2_TX=PA2,  RT_HW_UART2_DE=255,
	  RT_HW_UART3_RX=PD9,  RT_HW_UART3_TX=PD8,  RT_HW_UART3_DE=255,
	  RT_HW_UART4_RX=PC11, RT_HW_UART4_TX=PC10, RT_HW_UART4_DE=255,
      RT_HW_UART5_RX=PD2,  RT_HW_UART5_TX=PC12, RT_HW_UART5_DE=255};		
//--------------------------------Параметры I2C----------------------------------------------------
enum {RT_HW_I2C0_SDA=PB7,  RT_HW_I2C0_SCL=PB6,
      RT_HW_I2C1_SDA=PB11, RT_HW_I2C1_SCL=PB10}; 
//--------------------------------Параметры SPI----------------------------------------------------	
enum {RT_HW_SPI0_SCK=PA5,  RT_HW_SPI0_MISO=PA6,  RT_HW_SPI0_MOSI=PA7,  RT_HW_SPI0_SS=PA4,  
      RT_HW_SPI1_SCK=PB13, RT_HW_SPI1_MISO=PB14, RT_HW_SPI1_MOSI=PB15, RT_HW_SPI1_SS=PB12};
//=================================================================================================
#define RT_HW_BOARD_CHECK_PIN				//--Разрешение проверки на допустимость использования пинов [функции checkPinXXX(uint8_t pin)];
//-------------------------------Доступные пины контроллера----------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_ALL[] 	={PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PA8,PA9,PA10,PA11,PA12,PA13,PA14,PA15,
											  PB0,PB1,PB2,PB3,PB4,PB5,PB6,PB7,PB8,PB9,PB10,PB11,PB12,PB13,PB14,PB15,
											  PC0,PC1,PC2,PC3,PC4,PC5,PC6,PC7,PC8,PC9,PC10,PC11,PC12,PC13,PC14,PC15,
										          PD2,											 					RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DIN[] 	={PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PA8,PA9,PA10,PA11,PA12,255,255,PA15,
											  PB0,PB1,255,PB3,PB4,PB5,PB6,PB7,PB8,PB9,PB10,PB11,PB12,PB13,PB14,PB15,
										      PC0,PC1,PC2,PC3,PC4,PC5,PC6,PC7,PC8,PC9,PC10,PC11,PC12,PC13,PC14,PC15,
										      255,255,PD2,											 				RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_ADC[] 	={PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PA8,PB0,PB1,PC0,PC1,PC2,PC3,PC4,PC5,  RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_TCH[] 	={						 												RT_HW_PGM_END};									
const uint8_t PROGMEM RT_HW_PGM_PIN_DOT[] 	={PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PA8,PA9,PA10,PA11,PA12, 255, 255,PA15,
										      PB0,PB1,255,PB3,PB4,PB5,PB6,PB7,PB8,PB9,PB10,PB11,PB12,PB13,PB14,PB15,
										      PC0,PC1,PC2,PC3,PC4,PC5,PC6,PC7,PC8,PC9,PC10,PC11,PC12,PC13,PC14,PC15,
										      255,255,PD2,											 				RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_PWM[] 	={PA0,PA1,PA2,PA3,PA6,PA7,PA8,PA9,PA10,PB0,PB1,PB6,PB7,PB8,PB9,			RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DAC[] 	={PA3,PA4,																RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_INT[] 	={PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PA8,PA9,PA10,PA11,PA12,PA13, 255, 255,
										      PB0,PB1,255,PB3,PB4,PB5,PB6,PB7,PB8,PB9,PB10,PB11,PB12,PB13,PB14,PB15,RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_N5V[] 	={PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PB0,PB1,PB5,PC4,PC5,PB0,PB1,PB5,
										      PC13,PC14,PC15,														RT_HW_PGM_END};

//=================================================================================================
//--------------------------------Коммуникационные пины--------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_UHS[] 	={RT_HW_UART0_RX, RT_HW_UART0_TX,  RT_HW_UART0_DE,	//--UART0;
										      RT_HW_UART1_RX, RT_HW_UART1_TX,  RT_HW_UART1_DE,	//--UART1; 
											  RT_HW_UART2_RX, RT_HW_UART2_TX,  RT_HW_UART2_DE,	//--UART2; 
										      RT_HW_UART3_RX, RT_HW_UART3_TX,  RT_HW_UART3_DE,	//--UART3;
										      RT_HW_UART4_RX, RT_HW_UART4_TX,  RT_HW_UART4_DE,	//--UART4; 
											  RT_HW_UART5_RX, RT_HW_UART5_TX,  RT_HW_UART5_DE,	//--UART5;												  
																		       RT_HW_PGM_END};
//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_USS[]	={                                 RT_HW_PGM_END};	//--UARTS; 
//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_I2C[]	={RT_HW_I2C0_SDA, RT_HW_I2C0_SCL,					//--I2C0;
                                              RT_HW_I2C1_SDA, RT_HW_I2C1_SCL,  RT_HW_PGM_END};  //--i2C1;
//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_SPI[]	={RT_HW_SPI0_SCK, RT_HW_SPI0_MISO, RT_HW_SPI0_MOSI, RT_HW_SPI0_SS, //--SPI0;	
                                              RT_HW_SPI1_SCK, RT_HW_SPI1_MISO, RT_HW_SPI1_MOSI, RT_HW_SPI1_SS,
																			   RT_HW_PGM_END};	//--SPI1:  sck,miso,mosi,ss
const uint8_t PROGMEM RT_HW_PGM_PIN_SPF[]	={PB0,PB1,PB2,         			   RT_HW_PGM_END};  //--SPQ: sck,miso,mosi,cs;	
const uint8_t PROGMEM RT_HW_PGM_PIN_SDC[]	={PA4,PA5,PA6,PA7,PA8,             RT_HW_PGM_END};  //--SDIO: DO,D1,D2,D3,SCK;
const uint8_t PROGMEM RT_HW_PGM_PIN_SPN[]	={          					   RT_HW_PGM_END};  //--SSPI: sck,miso,mosi,cs;	
const uint8_t PROGMEM RT_HW_PGM_PIN_SPN[]	={          					   RT_HW_PGM_END};  //--SSPI: sck,miso,mosi,cs;	
//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_ETH[]	={0,PC2,PC3,PC4,				   RT_HW_PGM_END};	//--numSPI; cs,int,rst;
const uint8_t PROGMEM RT_HW_PGM_PIN_CAN[]	={90,255,PD1,PD2,				   RT_HW_PGM_END};	//--numSPI; cs,rx,tx;
//--------------------------------Системные пины---------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_BRD[]	={PE5,PA1,PA0,PC0,PB6,	    	   RT_HW_PGM_END};	//--Control,LED,Button,ADC,PWM,WS2812
//--------------------------------SPI пины cs------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_CSX[]	={PD3,PD4,PD5,PD6,	    		   RT_HW_PGM_END};	//--SPI: cs0,cs1,cs2,cs3
//--------------------------------Дисплейные пины--------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_LC4[]	={								   RT_HW_PGM_END};	//--RS,E2(RW),E1,D4-D7;
const uint8_t PROGMEM RT_HW_PGM_PIN_LC6[]	={								   RT_HW_PGM_END};	//--RS,E2(RW),E1,D0-D7;
const uint8_t PROGMEM RT_HW_PGM_PIN_TFT[]	={0,PB12,PC5,255,PC5,255,255,255, RT_HW_PGM_END};	//--numSPI; cs,dc,rst,led; t.cs,t.int; sd.cs;
//--------------------------------Тестовые пины----------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_TST_DIS[]	={          	    			   RT_HW_PGM_END};	//--Дискретные сигналы;
const uint8_t PROGMEM RT_HW_PGM_TST_ANL[]	={PC1,PB7,       				   RT_HW_PGM_END};	//--Аналоговые сигналы: ADC1,PWM1;
const uint8_t PROGMEM RT_HW_PGM_TST_SRV[]	={            	   				   RT_HW_PGM_END};	//--Servo1,Servo2;
const uint8_t PROGMEM RT_HW_PGM_TST_DEV[]	={PE11,PE12,PE13,           	   RT_HW_PGM_END};	//--Устройства: 1-Wire,DHT22,HC-SR04.trig,HC-SR04.echo,
const uint8_t PROGMEM RT_HW_PGM_TST_URT[]	={1,2,            		   		   RT_HW_PGM_END};	//--UART: Nextion, ModBus;
//-------------------------------------------------------------------------------------------------
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							3.Контроллер типа STM32F103V
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if !defined(RT_HW_BOARD_SELECT) &&  defined(RT_HW_BOARD_Generic_F103VETx) 
//-------------------------------------------------------------------------------------------------
#define RT_HW_BOARD_SELECT	         "Board GENERIC F103VETX"
//-------------------------------------------------------------------------------------------------
#define RT_HW_BOARD_MEMORY 	  "FLASH=512b; RAM=128Kb;"						//--Параметры памяти;
#define RT_HW_PERMIT_UART0
#define RT_HW_PERMIT_UART1
#define RT_HW_PERMIT_UART2
#define RT_HW_PERMIT_UART3


//#define RT_HW_PERMIT_UART4
//#define RT_HW_PERMIT_UART5
#define RT_HW_PERMIT_CAN
#define RT_HW_PERMIT_I2C0
#define RT_HW_PERMIT_I2C1
#define RT_HW_PERMIT_SPI0
#define RT_HW_PERMIT_SPI1	
#define RT_HW_PERMIT_DAC													//--Разрешение работы с DAC;
//------Системные пины-----------------------------------------------------------------------------
enum  {RT_HW_BOARD_CONTROL=PC2,RT_HW_BOARD_LED=PB12,RT_HW_BOARD_BUTTON=PA0, RT_HW_BOARD_WS=255};//--Пины контроль,led,кнопка;
//------Параметры контроллера общие----------------------------------------------------------------	
enum{RT_HW_PIN_QNT_MAX=80,	RT_HW_FCPU=72, 		RT_HW_VCC=3300};
//-----Параметры UART------------------------------------------------------------------------------	
enum   {RT_HW_UART0_RX=PA12, RT_HW_UART0_TX=PA11,
		RT_HW_UART1_RX=PA10, RT_HW_UART1_TX=PA9,  RT_HW_UART2_RX=PA3, RT_HW_UART2_TX=PA2, 
		RT_HW_UART3_RX=PB11, RT_HW_UART3_TX=PB10, RT_HW_UART4_RX=PC11,RT_HW_UART4_TX=PC10,
        RT_HW_UART5_RX=PD2,  RT_HW_UART5_TX=PC12};
//-----Параметры CAN------------------------------------------------------------------------------	
enum   {RT_HW_CAN_RX=PD0,    RT_HW_CAN_TX=PD1};	
//-----Параметры I2C------------------------------------------------------------------------------	
enum   {RT_HW_I2C0_SDA=PB9,  RT_HW_I2C0_SCL=PB9,  RT_HW_I2C0_MODE_FM=RT_HW_I2C_MODE_FM,
        RT_HW_I2C1_SDA=PB11, RT_HW_I2C1_SCL=PB10, RT_HW_I2C1_MODE_FM=RT_HW_I2C_MODE_FM}; 
//-----Параметры SPI------------------------------------------------------------------------------	
enum   {RT_HW_SPI0_SCK=PA5,  RT_HW_SPI0_MISO=PA6, RT_HW_SPI0_MOSI=PA7,  RT_HW_SPI0_SS=PA4,  
        RT_HW_SPI1_SCK=PB13, RT_HW_SPI1_MISO=PB14,RT_HW_SPI1_MOSI=PB15, RT_HW_SPI1_SS=PB12};
//-----Системные параметры-------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_SYS_PAR[]  ={12,			   	RT_HW_PGM_END};  //--SYS->depth;
const uint8_t PROGMEM RT_HW_PGM_SYS_ADC[]  ={12,4,3,			RT_HW_PGM_END};  //--ADC->depth,drift,null;
const uint8_t PROGMEM RT_HW_PGM_SYS_TCH[]  ={  				RT_HW_PGM_END};  //--TCH->depth,drift,null; 
const uint8_t PROGMEM RT_HW_PGM_SYS_PWM[]  ={16,10,			RT_HW_PGM_END};  //--PWM->depth,freq; 
const uint8_t PROGMEM RT_HW_PGM_SYS_DAC[]  ={					RT_HW_PGM_END};  //--DAC->depth; 
//-----Системные пины и параметры коммуникаций------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_BRD[]  	={RT_HW_BOARD_CONTROL, RT_HW_BOARD_LED, RT_HW_BOARD_BUTTON, RT_HW_BOARD_WS, RT_HW_PGM_END};  //--Пины->control,led,button,WS2812; 
const uint8_t PROGMEM RT_HW_PGM_PIN_I2C[] 	={RT_HW_I2C0_SDA, RT_HW_I2C0_SCL, 
                                              RT_HW_I2C1_SDA, RT_HW_I2C1_SCL,  RT_HW_PGM_END}; //--adr,SDA,SCL,mode; 
const uint8_t PROGMEM RT_HW_PGM_PIN_ICS[]	={	    															RT_HW_PGM_END};
//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_SPI[] 	={RT_HW_SPI0_SCK, RT_HW_SPI0_MISO, RT_HW_SPI0_MOSI, RT_HW_SPI0_SS,
											  RT_HW_SPI1_SCK, RT_HW_SPI1_MISO, RT_HW_SPI1_MOSI, RT_HW_SPI1_SS,	RT_HW_PGM_END}; 	
const uint8_t PROGMEM RT_HW_PGM_PIN_SPF[]	={PB0,PB1,PB2,         			   RT_HW_PGM_END};  //--SPQ: sck,miso,mosi,cs;	
const uint8_t PROGMEM RT_HW_PGM_PIN_SDC[]	={PA4,PA5,PA6,PA7,PA8,             RT_HW_PGM_END};  //--SDIO: DO,D1,D2,D3,SCK;
const uint8_t PROGMEM RT_HW_PGM_PIN_SPN[]	={          					   RT_HW_PGM_END};  //--SSPI: sck,miso,mosi,cs;	
//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_UHS[] 	={RT_HW_UART0_RX, RT_HW_UART0_TX, 
											  RT_HW_UART1_RX, RT_HW_UART1_TX, 
											  RT_HW_UART2_RX, RT_HW_UART2_TX, 
											  RT_HW_UART3_RX, RT_HW_UART3_TX, 
											  RT_HW_UART4_RX, RT_HW_UART4_TX,
											  RT_HW_UART5_RX, RT_HW_UART5_TX,           RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_USS[] 	={				 							RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_CAN[] 	={RT_HW_CAN_RX,   RT_HW_CAN_TX, 			RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_BTH[] 	={				 							RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_ETH[] 	={											RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_WFI[] 	={											RT_HW_PGM_END};
//=================================================================================================
#define RT_HW_BOARD_CHECK_PIN				//--Разрешение проверки на допустимость использования пинов [функции checkPinXXX(uint8_t pin)];
//-----Доступные пины контроллера------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_ALL[] 	={PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PA8,PA9,PA10,PA11,PA12,PA13,PA14,PA15,
										      PB0,PB1,PB2,PB3,PB4,PB5,PB6,PB7,PB8,PB9,PB10,PB11,PB12,PB13,PB14,PB15,
										      PC0,PC1,PC2,PC3,PC4,PC5,PC6,PC7,PC8,PC9,PC10,PC11,PC12,PC13,PC14,PC15,
										      PD0,PD1,PD2,PD3,PD4,PD5,PD6,PD7,PD8,PD9,PD10,PD11,PD12,PD13,PD14,PD15,
										      PE0,PE1,PE2,PE3,PE4,PE5,PE6,PE7,PE8,PE9,PE10,PE11,PE12,PE13,PE14,PE15,RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DIN[] 	={PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PA8,PA9,PA10,PA11,PA12, 255, 255,PA15,
										      PB0,PB1,255,PB3,PB4,PB5,PB6,PB7,PB8,PB9,PB10,PB11,PB12,PB13,PB14,PB15,
											  PC0,PC1,PC2,PC3,PC4,PC5,PC6,PC7,PC8,PC9,PC10,PC11,PC12,PC13,PC14,PC15,
											  PD0,PD1,PD2,PD3,PD4,PD5,PD6,PD7,PD8,PD9,PD10,PD11,PD12,PD13,PD14,PD15,
										      PE0,PE1,PE2,PE3,PE4,PE5,PE6,PE7,PE8,PE9,PE10,PE11,PE12,PE13,PE14,PE15,RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_ADC[] 	={PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PA8,PB0,PB1,PC0,PC1,PC2,PC3,PC4,PC5,  RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_TCH[] 	={						 												RT_HW_PGM_END};									
const uint8_t PROGMEM RT_HW_PGM_PIN_DOT[] 	={PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PA8,PA9,PA10,PA11,PA12, 255, 255,PA15,
											  PB0,PB1,255,PB3,PB4,PB5,PB6,PB7,PB8,PB9,PB10,PB11,PB12,PB13,PB14,PB15,
											  PC0,PC1,PC2,PC3,PC4,PC5,PC6,PC7,PC8,PC9,PC10,PC11,PC12,PC13,PC14,PC15,
											  PD0,PD1,PD2,PD3,PD4,PD5,PD6,PD7,PD8,PD9,PD10,PD11,PD12,PD13,PD14,PD15,
											  PE0,PE1,PE2,PE3,PE4,PE5,PE6,PE7,PE8,PE9,PE10,PE11,PE12,PE13,PE14,PE15,RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_PWM[] 	={PA0,PA1,PA2,PA3,PA6,PA7,PA8,PA9,PA10,PB0,PB1,PB6,PB7,PB8,PB9,			RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DAC[] 	={PA3,PA4,																RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_INT[] 	={PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PA8,PA9,PA10,PA11,PA12, 255, 255,PA15,
											  PB0,PB1,255,PB3,PB4,PB5,PB6,PB7,PB8,PB9,PB10,PB11,PB12,PB13,PB14,PB15,
											  PC0,PC1,PC2,PC3,PC4,PC5,PC6,PC7,PC8,PC9,PC10,PC11,PC12,PC13,PC14,PC15,
											  PD0,PD1,PD2,PD3,PD4,PD5,PD6,PD7,PD8,PD9,PD10,PD11,PD12,PD13,PD14,PD15,
											  PE0,PE1,PE2,PE3,PE4,PE5,PE6,PE7,PE8,PE9,PE10,PE11,PE12,PE13,PE14,PE15,RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_N5V[] 	={PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PB0,PB1,PB5,PC4,PC5,PB0,PB1,PB5,
											  PC13,PC14,PC15,														RT_HW_PGM_END};	
//-----Тестовые пины и адреса------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_DBG[]  	={						RT_HW_PGM_END};	//--Пины debug1,debug2,debug3;	
const uint8_t PROGMEM RT_HW_PGM_PIN_OUT[] 	={PB0, 255,PA4,			RT_HW_PGM_END};	//--Пины PWM0,PWM1,Servo1,Servo2;
const uint8_t PROGMEM RT_HW_PGM_PIN_INP[] 	={PA1,255, PA0,			RT_HW_PGM_END};	//--Пины A0,A1,btn1,btn2,TCH0,TCH1;
const uint8_t PROGMEM RT_HW_PGM_PIN_DCT[] 	={         				RT_HW_PGM_END};	//--Пины DAC0,DAC1;
const uint8_t PROGMEM RT_HW_PGM_PIN_DEV[] 	={PB8, PB9, PA8, 	    RT_HW_PGM_END};	//--Пины DS1820,DHT22,HC-SR04.trig
const uint8_t PROGMEM RT_HW_PGM_PIN_CSS[] 	={PB12,PB13,PB14,PB15,	RT_HW_PGM_END};	//--Пины CS SPI:595,LCD,NRF,DEVl 	
const uint8_t PROGMEM RT_HW_PGM_PIN_LC6[]  	={						RT_HW_PGM_END};	//--Пины для подключения LCD по 4-х битной шине;
const uint8_t PROGMEM RT_HW_PGM_PIN_TFT[]  	={						RT_HW_PGM_END};	//--Пины(дополнительные[]  TFT дисплея(SPI[] ;
const uint8_t PROGMEM RT_HW_PGM_PIN_URT[] 	={ 1, 2, 				RT_HW_PGM_END};	//--UART: ModBus, Nextion 
const uint8_t PROGMEM RT_HW_PGM_ADR_I2C[]  	={63,62,32,33,			RT_HW_PGM_END};	//--i2c: lcd1,lcd2,mcp1,mcp2;		
//-------------------------------------------------------------------------------------------------
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++