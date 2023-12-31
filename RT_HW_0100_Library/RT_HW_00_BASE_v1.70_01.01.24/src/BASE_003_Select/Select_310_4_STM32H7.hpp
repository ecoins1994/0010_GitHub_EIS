//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							 10.Контроллеры программной среды STM32duino (H7)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if !defined(RT_HW_BOARD_CODE) && defined(ARDUINO_WeActMiniH743VITX)	
#define      RT_HW_BOARD_CODE     120         								//--Идентификатор выбора платы c кодом платы;
#define      RT_HW_BOARD_NAME     "WeActMiniH743VITX"						//--Наименование платы;
#define      RT_HW_BOARD_MEMORY   "Flash=1024; SRAM=System(112+16+64)+Backup(4)Kb;" //--Параметры памяти; 
#define      RT_HW_BOARD_FCPU     480 										//--Частота процессора;	
#define      RT_HW_BOARD_VCC      3300										//--Значение Vсс процессора;
//-------------------------------------------------------------------------------------------------
#define      RT_HW_BOARD_WeActSTM32H7XXVxx  								//--Идентификатор типа платы;
#define      RT_HW_CORE_STM32												//--Идентификатор программной среды
#define      RT_HW_CORE_STM32H7V											//--Идентификатор программной среды
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							 10.Контроллеры программной среды STM32duino (H7)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if !defined(RT_HW_BOARD_CODE) && defined(ARDUINO_WeActMiniH750VBTX)			
#define      RT_HW_BOARD_CODE     121         								//--Идентификатор выбора платы c кодом платы;
#define      RT_HW_BOARD_NAME     "WeActMiniH750VBTX"						//--Наименование платы;
#define      RT_HW_BOARD_MEMORY   "Flash=1024; SRAM=System(112+16+64)+Backup(4)Kb;" //--Параметры памяти; 
#define      RT_HW_BOARD_FCPU     480 										//--Частота процессора;	
#define      RT_HW_BOARD_VCC      3300										//--Значение Vсс процессора;	
//-------------------------------------------------------------------------------------------------
#define      RT_HW_BOARD_WeActSTM32H7XXVxx 									//--Идентификатор типа платы;
#define      RT_HW_CORE_STM32												//--Идентификатор программной среды
#define      RT_HW_CORE_STM32H7V											//--Идентификатор программной среды
#endif
//=================================================================================================