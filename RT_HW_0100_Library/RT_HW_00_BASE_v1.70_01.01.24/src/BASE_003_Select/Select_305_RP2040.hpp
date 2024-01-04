
//#define      RT_HW_CORE_PI_PICO_2											//--Идентификатор программной среды
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								9.Контроллеры программной среды RASPBERRIY PI
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if !defined(RT_HW_BOARD_CODE) && (\
     defined(ARDUINO_RASPBERRY_PI_PICO) || defined(ARDUINO_ADAFRUIT_KB2040_RP2040) || \
	 ARDUINO_RASPBERRY_PI_PICO_W        || defined(ARDUINO_ARCH_RASPBERRY_PI))
//-------------------------------------------------------------------------------------------------
#define 	RT_HW_BOARD_CODE   	50 								//--Идентификатор выбора платы;
//-------------------------------------------------------------------------------------------------
#define 	RT_HW_BOARD_MEMORY 	"FLASH=2000kB; RAM=264Kb"       //--Параметры памяти;
#define 	RT_HW_BOARD_FCPU   	133								//--Частота процессора;	
#define 	RT_HW_BOARD_VCC   	3300							//--Значение Vсс процессора;
//-------------------------------------------------------------------------------------------------
#if  defined(ARDUINO_RASPBERRY_PI_PICO)	
#define 	RT_HW_BOARD_NAME  	"Rasberry Pi Pico"     			//--Наименование платы;		
#define 	RT_HW_BOARD_QNT    	30								//--Количество пинов;
#define    	RT_HW_BOARD_RP2040									//--Идентификатор типа платы;
//--------------------------------
#elif defined(ARDUINO_RASPBERRY_PI_PICO_W)	
#define 	RT_HW_BOARD_NAME  	"Rasberry Pi Pico" 				//--Наименование платы;
#define 	RT_HW_BOARD_QNT   	30								//--Количество пинов;
#define     RT_HW_PERMIT_UARTW	
#define    	RT_HW_BOARD_RP2040_W								//--Идентификатор типа платы;
//--------------------------------
#elif defined(ARDUINO_ADAFRUIT_KB2040_RP2040)	
#define 	RT_HW_BOARD_NAME  	"Rasberry Pi Pico Zero)" 	    //--Наименование платы;
#define 	RT_HW_BOARD_QNT   	20								//--Количество пинов;
#define    	RT_HW_BOARD_RP2040									//--Идентификатор типа платы;
//--------------------------------
#else
#define 	RT_HW_BOARD_NAME  	"Near of kin Rasberry Pi Pico"  //--Наименование платы;	
#define 	RT_HW_BOARD_QNT    	30								//--Количество пинов;
#define    	RT_HW_BOARD_RP2040									//--Идентификатор типа платы;
#endif
//------------------------------------------------------------------------------------------------
#define  	RT_HW_CORE_RP2040									//--Идентификатор CORE;	
//-------------------------------------------------------------------------------------------------
#endif
//=================================================================================================