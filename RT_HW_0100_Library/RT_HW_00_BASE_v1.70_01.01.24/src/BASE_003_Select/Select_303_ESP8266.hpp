//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//										ESP8266
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=================================================================================================
//						Определение номеров пинов в мнемоники ESP8266
//=================================================================================================
enum {RT_HW_D0=16, RT_HW_D1=5,  RT_HW_D2=4,  RT_HW_D3=0,   RT_HW_D4=2, RT_HW_D5=14, RT_HW_D6=12, 
      RT_HW_D7=13, RT_HW_D8=15, RT_HW_D9=3,  RT_HW_D10=1,  RT_HW_A0=17,
      RT_HW_RX=3,  RT_HW_TX=1,  RT_HW_TX1=4, RT_HW_RX2=13, RT_HW_TX2=15};
//=================================================================================================						
//									1.Контроллер ESP8266 GENERIC
//=================================================================================================
#if !defined(RT_HW_BOARD_CODE) && (\
     defined(ARDUINO_ESP8266_GENERIC) || \
	 defined(ARDUINO_ESP8266_NODEMCU_ESP12) || defined(ARDUINO_ESP8266_NODEMCU_ESP12E))	 	
//-------------------------------------------------------------------------------------------------
#define 	RT_HW_BOARD_CODE  	10 								//--Идентификатор выбора платы;
//-------------------------------------------------------------------------------------------------
#define 	RT_HW_BOARD_QNT    	17								//--Количество пинов;	
#define 	RT_HW_BOARD_MEMORY	"FLASH=FS:(max)2Mb,OTA:(max)1019Kb; RAM=80Kb"//--Параметры памяти;
#define 	RT_HW_BOARD_FCPU   	80 								//--Частота процессора;	
#define 	RT_HW_BOARD_VCC    	3300								//--Значение Vсс процессора;
//-------------------------------------------------------------------------------------------------
#if  defined(ARDUINO_ESP8266_GENERIC)	
#define 	RT_HW_BOARD_NAME  	"ESP8266 Generic"     			//--Name board;		
//--------------------------------
#elif defined(ARDUINO_ESP8266_NODEMCU_ESP12)	
#define 	RT_HW_BOARD_NAME  	"NodeMCU 0.9 (ESP-12 Module)" 	//--Name board;
//--------------------------------
#elif defined(ARDUINO_ESP8266_NODEMCU_ESP12E)	
#define 	RT_HW_BOARD_NAME   	"NodeMCU 1.0 (ESP-12E Module)"  //--Name board;
//--------------------------------
#elif defined(ARDUINO_ESP8266_WEMOS_D1WROOM02)	
#define 	RT_HW_BOARD_NAME   	"LOLIN(WEMOS) D1 ESP-WROOM-02"  //--Name board;
//--------------------------------
#elif defined(ARDUINO_ESP8266_WEMOS_D1MINI)	
#define 	RT_HW_BOARD_NAME   	"LOLIN(WEMOS) D1 R2 & mini"  	//--Name board;
//--------------------------------
#elif defined(ARDUINO_SP8266_WEMOS_D1MINI)	
#define 	RT_HW_BOARD_NAME   	"LOLIN(WEMOS) D1 mini (clone)"  //--Name board;
//--------------------------------
#elif defined(ARDUINO_ESP8266_WEMOS_D1MINILITE)	
#define 	RT_HW_BOARD_NAME   	"LOLIN(WEMOS) D1 mini Lite"  	//--Name board;
//--------------------------------
#elif defined(ARDUINO_ESP8266_WEMOS_D1MINIPRO)	
#define 	RT_HW_BOARD_NAME   	"LOLIN(WEMOS) D1 mini Pro"  	//--Name board;
//--------------------------------
#elif defined(ARDUINO_ESP8266_WEMOS_D1R1)	
#define 	RT_HW_BOARD_NAME   	"LOLIN(WeMos) D1 R1"  			//--Name board;
//--------------------------------
#else
#define 	RT_HW_BOARD_NAME  	"Near of kin ESP8266 Generic)"  //--Name board;	
#endif
//------------------------------------------------------------------------------------------------
#define    	RT_HW_BOARD_ESP8266_GENERIC							//--Идентификатор типа платы;
#define  	RT_HW_CORE_ESP										//--Идентификатор CORE;
#define  	RT_HW_CORE_ESP8266									//--Идентификатор CORE;		
//-------------------------------------------------------------------------------------------------
#endif
//=================================================================================================
//								2.Контроллер ESP8266 ANON
//=================================================================================================	
#if !defined(RT_HW_BOARD_CODE) && (defined(ARDUINO_ARCH_ESP8266) || ESP8266)
//-------------------------------------------------------------------------------------------------
#define RT_HW_BOARD_CODE    	10 								//--Идентификатор выбор;
#define RT_HW_BOARD_QNT     	17								//--Количество пинов;	
#define RT_HW_BOARD_MEMORY	 	"FLASH=FS:(max)2Mb,OTA:(max)1019Kb; RAM=80Kb"//--Параметры памяти;
#define RT_HW_BOARD_FCPU   		80 								//--Частота процессора;	
#define RT_HW_BOARD_VCC     	3300							//--Значение Vсс процессора;
//-------------------------------------------------------------------------------------------------
#define RT_HW_BOARD_NAME     	"ESP8266 ANON"					//--Наименование платы;
//------------------------------------------------------------------------------------------------
#define RT_HW_BOARD_ESP8266_GENERIC								//--Идентификатор типа платы;
#define RT_HW_CORE_ESP											//--Идентификатор CORE;
#define RT_HW_CORE_ESP8266										//--Идентификатор CORE;		
//-------------------------------------------------------------------------------------------------
#endif
//=================================================================================================
