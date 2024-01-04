//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								1.Контроллеры программной среды AVR
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//								1.1.Arduino AVR Mega2560
//=================================================================================================
#if !defined(RT_HW_BOARD_CODE) && ( \
     defined(__AVR_ATmega2560__) || defined(__AVR_ATmega2561__) || defined(__AVR_ATmega1280__) || \
     defined(__AVR_ATmega1281__) || defined(__AVR_ATmega640__)  || defined(__AVR_ATmega641__)  || \
     defined(ARDUINO_AVR_MEGA2560))
//-------------------------------------------------------------------------------------------------
#define RT_HW_BOARD_CODE       	1 								//--Идентификатор выбора платы;
//-------------------------------------------------------------------------------------------------
#if  defined(ARDUINO_AVR_MEGA2560)	
#define 	RT_HW_BOARD_NAME  	"Arduino Mega 2560"     		//--Наименование платы;
#else
#define     RT_HW_BOARD_NAME   	"Arduino Mega 2560/other"     	//--Наименование платы;	
#endif
//------------------------------------------------------------------------------------------------
#define    	RT_HW_BOARD_AVR_MEGA2560							//--Идентификатор типа платы;
#define    	RT_HW_CORE_AVR										//--Идентификатор CORE;
//------------------------------------------------------------------------------------------------
#define     RT_HW_BOARD_QNT     64							    //--Количество пинов;
#define    	RT_HW_BOARD_MEMORY	"FLASH=256Kb,RAM=8Kb,EEPROM=4Kb;"	//--Параметры памяти;
#define    	RT_HW_BOARD_FCPU   	16 								//--Частота процессора;	
#define    	RT_HW_BOARD_VCC    	5000							//--Значение Vсс процессора;
//-----Корректировка для PROGMEM для RAM>64kB;----------------------------------------------------
#if defined(RT_HW_BOARD_AVR_MEGA2560)	
//  #ifdef  PROGMEM											
//  #undef  PROGMEM													
//  #endif													
//#define PROGMEM __attribute__(( section(".progmem.data") ))
#endif
//-------------------------------------------------------------------------------------------------
#endif
//=================================================================================================
//								1.2.Arduino AVR UNO,Nano,PRO, MINI
//=================================================================================================
#if !defined(RT_HW_BOARD_CODE) && (\
     defined(ARDUINO_AVR_FIO)   || defined(ARDUINO_AVR_BT)     || defined(ARDUINO_AVR_LILYPAD)|| \
     defined(ARDUINO_AVR_NG)    || defined(ARDUINO_AVR_UNO_WIFI_DEV_ED)                       || \
	 defined(ARDUINO_AVR_ETHERNET)                        || defined(ARDUINO_AVR_DUEMILANOVE) || \
	 defined(ARDUINO_AVR_UNO)   || defined(ARDUINO_AVR_NANO)   || defined(ARDUINO_AVR_PRO)    || \
	 defined(ARDUINO_AVR_MINI))
//-------------------------------------------------------------------------------------------------
#define RT_HW_BOARD_CODE       	2 								//--Идентификатор выбор;
#define    	RT_HW_BOARD_VCC    	5000							//--Значение Vсс процессора;
//-------------------------------------------------------------------------------------------------
#if   defined(ARDUINO_AVR_UNO)	
#define   	RT_HW_BOARD_NAME  	"Arduino UNO(ATmega328)"     	//--Наименование платы;
#define     RT_HW_BOARD_QNT     20								//--Количество пинов;	
#define    	RT_HW_BOARD_MEMORY	"FLASH=32kB(Loader 0.5kB),RAM=2Kb,EEPROM=1Kb"//--Параметры памяти;
#define    	RT_HW_BOARD_FCPU   	16 								//--Частота процессора;	
//--------------------------------
#elif defined(ARDUINO_AVR_NANO)	
#define   	RT_HW_BOARD_NAME  	"Arduino Nano(ATmega328)"     	//--Наименование платы;
#define     RT_HW_BOARD_QNT     22								//--Количество пинов;
#define    	RT_HW_BOARD_MEMORY	"FLASH=32kB(Loader 2kB),RAM=2Kb,EEPROM=1Kb" //--Параметры памяти;
#define    	RT_HW_BOARD_FCPU   	16 								//--Частота процессора;
//--------------------------------
#elif defined(ARDUINO_AVR_MINI)	
#define   	RT_HW_BOARD_NAME  	"Arduino Mini (ATmega328)"     	//--Наименование платы;
#define     RT_HW_BOARD_QNT     22								//--Количество пинов;
#define    	RT_HW_BOARD_MEMORY	"FLASH=32kB(Loader 2kB),RAM=2Kb,EEPROM=1Kb" //--Параметры памяти;
#define    	RT_HW_BOARD_FCPU   	16 								//--Частота процессора;

//--------------------------------
#elif defined(ARDUINO_AVR_PRO)	
#define   	RT_HW_BOARD_NAME  	"Arduino Pro(ATmega168)"     	//--Наименование платы;
#define     RT_HW_BOARD_QNT     20								//--Количество пинов;
#define    	RT_HW_BOARD_MEMORY	"FLASH=16kB(Loader 2kB),RAM=512b" //--Параметры памяти;
#define    	RT_HW_BOARD_FCPU   	8 								//--Частота процессора;
//--------------------------------
#else
#define   	RT_HW_BOARD_NAME  	"Near of kin Arduino UNO(ATmega328)"   //--Наименование платы;
#define     RT_HW_BOARD_QNT     20								//--Количество пинов;	
#define    	RT_HW_BOARD_MEMORY	"FLASH=32kB(Loader 0.5kB),RAM=2Kb,EEPROM=1Kb"//--Параметры памяти;
#define    	RT_HW_BOARD_FCPU   	16 								//--Частота процессора;
#endif
//------------------------------------------------------------------------------------------------
#define     RT_HW_BOARD_AVR_NANO								//--Идентификатор типа платы
#define   	RT_HW_CORE_AVR										//--Идентификатор CORE;
//-------------------------------------------------------------------------------------------------
#endif
//=================================================================================================
//								1.3.Arduino AVR ANON
//=================================================================================================
#if !defined(RT_HW_BOARD_CODE) && defined(__AVR__)								
//-------------------------------------------------------------------------------------------------
#define RT_HW_BOARD_CODE       	3 								//--Идентификатор выбора платы;
#define    	RT_HW_BOARD_VCC     5000							//--Значение Vсс процессора;
//-------------------------------------------------------------------------------------------------
#define  	RT_HW_BOARD_NAME    "AVR ANON[near of kin Arduno Uno]" //--Наименование платы;
#define  	RT_HW_BOARD_QNT       20							//--Количество пинов;
#define    	RT_HW_BOARD_MEMORY	"FLASH=32Kb,RAM=2Kb,EEPROM=1Kb"	//--Параметры памяти;
#define    	RT_HW_BOARD_FCPU    16 								//--Частота процессора;	
//--------------------------------------------------------------------------------------------------
#define    	RT_HW_BOARD_AVR_ANON								//--Идентификатор типа платы;
#define    	RT_HW_CORE_AVR										//--Идентификатор программной среды;
//--------------------------------------------------------------------------------------------------
#endif
//=================================================================================================