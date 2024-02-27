//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							1.Контроллер WeActSTM32H7XXVxx
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if !defined(RT_HW_BOARD_SELECT) && defined(RT_HW_BOARD_WeActSTM32H7XXVxx)
//-------------------------------------------------------------------------------------------------
#define      RT_HW_BOARD_SELECT	    "BOARD WeActSTM32H7XXVxx_12.11.2023"
//-------------------------------------------------------------------------------------------------
  #define RT_HW_PERMIT_UART0				//--Разрешение работы с UART0;
  #define RT_HW_PERMIT_UART1				//--Разрешение работы с UART1;
  #define RT_HW_PERMIT_UART2				//--Разрешение работы с UART2;
  #define RT_HW_PERMIT_UART3				//--Разрешение работы с UART3;
  #define RT_HW_PERMIT_UART4				//--Разрешение работы с UART4;
  #define RT_HW_PERMIT_UART5				//--Разрешение работы с UART5;
  #define RT_HW_PERMIT_UART6				//--Разрешение работы с UART6;
  #define RT_HW_PERMIT_UART7				//--Разрешение работы с UART7;
  #define RT_HW_PERMIT_UART8				//--Разрешение работы с UART8;
//-------------------------------------------------------------------------------------------------
  #define RT_HW_PERMIT_I2C0					//--Разрешение работы с i2c0;
  #define RT_HW_PERMIT_I2C1					//--Разрешение работы с i2c1;
//-------------------------------------------------------------------------------------------------
  #define RT_HW_PERMIT_SPI0					//--Разрешение работы с SPI0;
//#define RT_HW_PERMIT_SPI1					//--Разрешение работы с SPI1;
//#define RT_HW_PERMIT_SPI2					//--Разрешение работы с SPI1;
  #define RT_HW_PERMIT_SPI3					//--Разрешение работы с SPI3;
//-------------------------------------------------------------------------------------------------
  #define RT_HW_PERMIT_ETH					//--Разрешение работы с ETH;
//-------------------------------------------------------------------------------------------------
  #define RT_HW_PERMIT_CAN					//--Разрешение работы с CAN;
//-------------------------------------------------------------------------------------------------
  #define RT_HW_PERMIT_TFT					//--Разрешение работы с TFT;
//-------------------------------------------------------------------------------------------------
  #define RT_HW_PERMIT_DAC					//--Разрешение работы с DAC;
//-------------------------------------------------------------------------------------------------
//							Permission to cteate with Link
//-------------------------------------------------------------------------------------------------
  #define RT_HW_CREATE_UART1				//--Разрешение создания объекта UART1;
  #define RT_HW_CREATE_UART2				//--Разрешение создания объекта UART2;
  #define RT_HW_CREATE_UART3				//--Разрешение создания объекта UART3;
  #define RT_HW_CREATE_UART4				//--Разрешение создания объекта UART4;
  #define RT_HW_CREATE_UART5				//--Разрешение создания объекта UART5;
  #define RT_HW_CREATE_UART6				//--Разрешение создания объекта UART6;
  #define RT_HW_CREATE_UART7				//--Разрешение создания объекта UART7;
  #define RT_HW_CREATE_UART8				//--Разрешение создания объекта UART8;
//-------------------------------------------------------------------------------------------------
  #define RT_HW_CREATE_I2C1					//--Разрешение создания объекта i2c1;
//-------------------------------------------------------------------------------------------------
  #define RT_HW_CREATE_SPI1					//--Разрешение создания объекта SPI1;
  #define RT_HW_CREATE_SPI2					//--Разрешение создания объекта SPI1;
  #define RT_HW_CREATE_SPI3					//--Разрешение создания объекта SPI3;
//-------------------------------------------------------------------------------------------------
#ifndef PC2
#define PC2 PC_2
#endif
#ifndef PC3
#define PC3 PC_3
#endif

//=================================================================================================

//--------------------------------Параметры UART---------------------------------------------------	
enum {RT_HW_UART0_RX=PA12, RT_HW_UART0_TX=PA11, RT_HW_UART0_DE=255,
	  RT_HW_UART1_RX=PA10, RT_HW_UART1_TX=PA9,  RT_HW_UART1_DE=255, 
	  RT_HW_UART2_RX=PA3,  RT_HW_UART2_TX=PA2,  RT_HW_UART2_DE=255,
	  RT_HW_UART3_RX=PD9,  RT_HW_UART3_TX=PD8,  RT_HW_UART3_DE=PB14,
	  RT_HW_UART4_RX=PA1,  RT_HW_UART4_TX=PA0,  RT_HW_UART4_DE=PB15,
	  RT_HW_UART5_RX=PB12, RT_HW_UART5_TX=PB15, RT_HW_UART5_DE=255,		
	  RT_HW_UART6_RX=PC7,  RT_HW_UART6_TX=PC6,  RT_HW_UART6_DE=255,
	  RT_HW_UART7_RX=PE7,  RT_HW_UART7_TX=PE8,  RT_HW_UART7_DE=255,	  
	  RT_HW_UART8_RX=PE0,  RT_HW_UART8_TX=PE1,  RT_HW_UART8_DE=255	  
	  };
//--------------------------------Параметры I2C----------------------------------------------------
enum {RT_HW_I2C0_SDA=PB9,  RT_HW_I2C0_SCL=PB8,
      RT_HW_I2C1_SDA=PB11, RT_HW_I2C1_SCL=PB10}; 
//--------------------------------Параметры SPI----------------------------------------------------	
enum {
	//RT_HW_SPI0_SCK=PB13, RT_HW_SPI0_MISO=PB14, RT_HW_SPI0_MOSI=PB15, RT_HW_SPI0_SS=PB12,
	  RT_HW_SPI0_SCK=PB3,  RT_HW_SPI0_MISO=PB4,  RT_HW_SPI0_MOSI=PD7,  RT_HW_SPI0_SS=PD6,	  
      RT_HW_SPI1_SCK=255,  RT_HW_SPI1_MISO=255,  RT_HW_SPI1_MOSI=255,  RT_HW_SPI1_SS=255,
      RT_HW_SPI2_SCK=255,  RT_HW_SPI2_MISO=255,  RT_HW_SPI2_MOSI=255,  RT_HW_SPI2_SS=255,
      RT_HW_SPI3_SCK=PE12, RT_HW_SPI3_MISO=PE5,  RT_HW_SPI3_MOSI=PE14, RT_HW_SPI3_SS=PE11,
      RT_HW_SPI4_SCK=255,  RT_HW_SPI4_MISO=255,  RT_HW_SPI4_MOSI=255,  RT_HW_SPI4_SS=255,
      RT_HW_SPI5_SCK=255,  RT_HW_SPI5_MISO=255,  RT_HW_SPI5_MOSI=255,  RT_HW_SPI5_SS=255
	//RT_HW_SPI3_SCK=PB3,  RT_HW_SPI1_MISO=PB4,  RT_HW_SPI1_MOSI=PB5,  RT_HW_SPI1_SS=PA15
	  };
//=================================================================================================
#define RT_HW_BOARD_CHECK_PIN				//--Разрешение проверки на допустимость использования пинов [функции checkPinXXX(uint8_t pin)];
//--------------------------------Доступные пины контроллера---------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_ALL[] 	={PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PA8,PA9,PA10,PA11,PA12, 255, 255,PA15,
											  PB0,PB1,255,PB3,PB4,PB5,PB6,PB7,PB8,PB9,PB10,PB11,PB12,PB13,PB14,PB15,
										      PC0,PC1,PC2,PC3,PC4,PC5,PC6,PC7,PC8,PC9,PC10,PC11,PC12,PC13, 255, 255,
										      PD0,PD1,PD2,PD3,PD4,PD5,PD6,PD7,PD8,PD9,PD10,PD11,PD12,PD13,PD14,PD15,
										      PE0,PE1,PE2,PE3,PE4,PE5,PE6,PE7,PE8,PE9,PE10,PE11,PE12,PE13,PE14,PE15, 
																										RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DIN[] 	={PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PA8,PA9,PA10,PA11,PA12, 255, 255,PA15,
										      PB0,PB1,255,PB3,PB4,PB5,PB6,PB7,PB8,PB9,PB10,PB11,PB12,PB13,PB14,PB15,
										      PC0,PC1,PC2,PC3,PC4,PC5,PC6,PC7,PC8,PC9,PC10,PC11,PC12,PC13, 255, 255,
										      PD0,PD1,PD2,PD3,PD4,PD5,PD6,PD7,PD8,PD9,PD10,PD11,PD12,PD13,PD14,PD15,
										      PE0,PE1,PE2,PE3,PE4,PE5,PE6,PE7,PE8,PE9,PE10,PE11,PE12,PE13,PE14,PE15, 
																										RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_ADC[] 	={PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PB0,PB1,PC0, PC1, PC2, PC3, PC4, PC5,  
																										RT_HW_PGM_END};									
const uint8_t PROGMEM RT_HW_PGM_PIN_TCH[] 	={															RT_HW_PGM_END};	
const uint8_t PROGMEM RT_HW_PGM_PIN_DOT[] 	={PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PA8,PA9,PA10,PA11,PA12, 255, 255,PA15,
										      PB0,PB1,255,PB3,PB4,PB5,PB6,PB7,PB8,PB9,PB10,PB11,PB12,PB13,PB14,PB15,
										      PC0,PC1,PC2,PC3,PC4,PC5,PC6,PC7,PC8,PC9,PC10,PC11,PC12,PC13, 255, 255,
										      PD0,PD1,PD2,PD3,PD4,PD5,PD6,PD7,PD8,PD9,PD10,PD11,PD12,PD13,PD14,PD15,
                                              PE0,PE1,PE2,PE3,PE4,PE5,PE6,PE7,PE8,PE9,PE10,PE11,PE12,PE13,PE14,PE15,
																										RT_HW_PGM_END}; 
const uint8_t PROGMEM RT_HW_PGM_PIN_PWM[]   ={PA0,PA1,PA2,PA3,255,PA5,PA6,PA7,PA8,PA9,PA10,PA11, 255, 255, 255, 255,
										      PB0,PB1,255,PB3,PB4,PB5,PB6,PB7,PB8,PB9,PB10, 255, 255,PB13,PB14,PB15,
																										RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_DAC[]   ={PA4,PA5, 													RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_INT[] 	={PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PA8,PA9,PA10,PA11,PA12, 255, 255,PA15,
										      PB0,PB1,255,PB3,PB4,PB5,PB6,PB7,PB8,PB9,PB10,PB11,PB12,PB13,PB14,PB15,
										      PC0,PC1,PC2,PC3,PC4,PC5,PC6,PC7,PC8,PC9,PC10,PC11,PC12,PC13, 255, 255,
										      PD0,PD1,PD2,PD3,PD4,PD5,PD6,PD7,PD8,PD9,PD10,PD11,PD12,PD13,PD14,PD15,
										      PE0,PE1,PE2,PE3,PE4,PE5,PE6,PE7,PE8,PE9,PE10,PE11,PE12,PE13,PE14,PE15,
																										RT_HW_PGM_END};
const uint8_t PROGMEM RT_HW_PGM_PIN_N5V[]	={PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PA8,PA9,PA10,PA11,PA12, 255, 255,PA15,
											  PC0,PC1,PC2,PB3,PB4,PB5,PB6,PB7,PB8,PB9,PB10,PB11,PB12,PB13,PB14,PB15,
										      PC0,PC1,PC2,PC3,PC4,PC5,PC6,PC7,PC8,PC9,PC10,PC11,PC12,PC13, 255, 255,
										      PD0,PD1,PD2,PD3,PD4,PD5,PD6,PD7,PD8,PD9,PD10,PD11,PD12,PD13,PD14,PD15,
										      PE0,PE1,PE2,PE3,PE4,PE5,PE6,PE7,PE8,PE9,PE10,PE11,PE12,PE13,PE14,PE15,
																										RT_HW_PGM_END};	
//=================================================================================================
//--------------------------------Коммуникационные пины--------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_UHS[] 	={RT_HW_UART0_RX, RT_HW_UART0_TX,  RT_HW_UART0_DE,	//--UART0;
										      RT_HW_UART1_RX, RT_HW_UART1_TX,  RT_HW_UART1_DE,	//--UART1; 
											  RT_HW_UART2_RX, RT_HW_UART2_TX,  RT_HW_UART2_DE,	//--UART2; 
										      RT_HW_UART3_RX, RT_HW_UART3_TX,  RT_HW_UART3_DE,	//--UART3;
										      RT_HW_UART4_RX, RT_HW_UART4_TX,  RT_HW_UART4_DE,	//--UART4; 
											  RT_HW_UART5_RX, RT_HW_UART5_TX,  RT_HW_UART5_DE,	//--UART5;	
											  RT_HW_UART6_RX, RT_HW_UART6_TX,  RT_HW_UART6_DE,	//--UART6;											  
											  RT_HW_UART7_RX, RT_HW_UART7_TX,  RT_HW_UART7_DE,	//--UART7;	
											  RT_HW_UART8_RX, RT_HW_UART8_TX,  RT_HW_UART8_DE,	//--UART8;																			       																			   
																			   RT_HW_PGM_END};
//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_USS[]	={                                 RT_HW_PGM_END};	//--UARTS; 
//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_I2C[]	={RT_HW_I2C0_SDA, RT_HW_I2C0_SCL,					//--I2C0;
                                              RT_HW_I2C1_SDA, RT_HW_I2C1_SCL,  RT_HW_PGM_END};  //--i2C1;
//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_SPI[]	={RT_HW_SPI0_SCK, RT_HW_SPI0_MISO, RT_HW_SPI0_MOSI, RT_HW_SPI0_SS, //--SPI0;	
                                              RT_HW_SPI1_SCK, RT_HW_SPI1_MISO, RT_HW_SPI1_MOSI, RT_HW_SPI1_SS,
                                              RT_HW_SPI2_SCK, RT_HW_SPI2_MISO, RT_HW_SPI2_MOSI, RT_HW_SPI2_SS,
                                              RT_HW_SPI3_SCK, RT_HW_SPI3_MISO, RT_HW_SPI3_MOSI, RT_HW_SPI3_SS,
                                              RT_HW_SPI4_SCK, RT_HW_SPI4_MISO, RT_HW_SPI4_MOSI, RT_HW_SPI4_SS,											  
																			   RT_HW_PGM_END};	//--SPIx:  sck,miso,mosi,ss
//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_SPN[]	={          					   RT_HW_PGM_END};  //--SSPI: sck,miso,mosi,cs;	
//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_SPF[]	={  0,PD6,			               	RT_HW_PGM_END};  //--SPF: numSPI; cs;	
const uint8_t PROGMEM RT_HW_PGM_PIN_SDC[]	={PC8,PC9,PC10,PC11,PC12,          	RT_HW_PGM_END};  //--SDIO: DO,D1,D2,D3,SW,SCK;	
//-------------------------------------------------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_ETH[]	={0,PD5,PE8,				       	RT_HW_PGM_END};	//--ETH: numSPI; cs,int;
const uint8_t PROGMEM RT_HW_PGM_PIN_CAN[]	={0,PD3,PE15,				       	RT_HW_PGM_END};	//--CAN: numSPI; cs,int; [MCP2515]
//--------------------------------Системные пины---------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_BRD[]	={PE2,PE3,PC13,PC0,PB5,PB6,	       	RT_HW_PGM_END};	//--Control,LED,Button,ADC,PWM,WS2812
//--------------------------------SPI пины cs------------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_CSX[]	={PD10,PD11,PD12,	    		   	RT_HW_PGM_END};	//--SPI: cs0,cs1,cs2,cs3,cs4,cs5,cs6,cs7;
//--------------------------------Дисплейные пины--------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_PIN_LC4[]	={								   	RT_HW_PGM_END};	//--RS,E2(RW),E1,D4-D7;
const uint8_t PROGMEM RT_HW_PGM_PIN_LC6[]	={								   	RT_HW_PGM_END};	//--RS,E2(RW),E1,D0-D7;
const uint8_t PROGMEM RT_HW_PGM_PIN_TFT[]	={3,PE11,PE13,PE10,            	   	RT_HW_PGM_END};	//--TFT: numSPI; cs,dc,led,rst;
//--------------------------------Тестовые пины----------------------------------------------------
const uint8_t PROGMEM RT_HW_PGM_TST_DIS[]	={          	    			   	RT_HW_PGM_END};	//--Дискретные сигналы;
const uint8_t PROGMEM RT_HW_PGM_TST_ANL[]	={      				           	RT_HW_PGM_END};	//--Аналоговые сигналы: ADC1,PWM1;
const uint8_t PROGMEM RT_HW_PGM_TST_SRV[]	={            	   				   	RT_HW_PGM_END};	//--Servo1,Servo2;
const uint8_t PROGMEM RT_HW_PGM_TST_DEV[]	={PB6,PE4,PB7,                     	RT_HW_PGM_END};	//--Устройства: 1-Wire,DHT22,SR04.trig,SR04.echo;
const uint8_t PROGMEM RT_HW_PGM_TST_URT[]	={210,1,2,3,4,5,6,            		RT_HW_PGM_END};	//--UART: Консоль,Modbus1,ModBus2,Nextion,Wi-Fi,Eth1,Eth2;
//-------------------------------------------------------------------------------------------------
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

