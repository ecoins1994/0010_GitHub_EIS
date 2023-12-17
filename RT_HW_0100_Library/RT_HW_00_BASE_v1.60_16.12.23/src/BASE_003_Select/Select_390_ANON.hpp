
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							90.Контроллеры с не опознанной программной средой 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if !defined(RT_HW_BOARD_CODE)  								
//-------------------------------------------------------------------------------------------------
#define 	RT_HW_BOARD_CODE  	90 								//--Идентификатор выбора платы;
#define    	RT_HW_BOARD_VCC   	5000							//--Значение Vсс процессора;
//-------------------------------------------------------------------------------------------------
#define   	RT_HW_BOARD_NAME  	"Arduino ANON"     				//--Наименование платы;
#define     RT_HW_BOARD_QNT     20								//--Количество пинов;	
#define    	RT_HW_BOARD_MEMORY	"FLASH=32kB(Loader 0.5kB),RAM=2Kb,EEPROM=1Kb"//--Параметры памяти;
#define    	RT_HW_BOARD_FCPU   	16 								//--Частота процессора;	
//-------------------------------------------------------------------------------------------------
#define   	RT_HW_BOARD_ANON  									//--Идентификатор типа платы;
#define    	RT_HW_CORE_ANON										//--Идентификатор программной среды;
//-------------------------------------------------------------------------------------------------
#endif
//=================================================================================================
