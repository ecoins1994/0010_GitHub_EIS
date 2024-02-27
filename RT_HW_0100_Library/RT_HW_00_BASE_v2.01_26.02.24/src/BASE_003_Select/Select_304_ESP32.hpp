//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								1.Контроллеры ESP32S
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//								1.1.Контроллер ESP32S
//=================================================================================================
#if !defined(RT_HW_BOARD_CODE) && (\
	 defined(ARDUINO_ESP32_DEV)	|| defined(ARDUINO_ESP32S_DEV_BTH_EIS) || defined(ARDUINO_TTGO_T1))
//-------------------------------------------------------------------------------------------------
#define 	RT_HW_BOARD_CODE   	11 								//--Идентификатор выбора платы;
//-------------------------------------------------------------------------------------------------
#define 	RT_HW_BOARD_MEMORY 	"FLASH=1310Kb; RAM=328Kb; Ext_FLASH=4/16Mb;"//--Параметры памяти;
#define 	RT_HW_BOARD_FCPU   	240								//--Частота процессора;	
#define 	RT_HW_BOARD_VCC   	3300							//--Значение Vсс процессора;
//-------------------------------------------------------------------------------------------------
#if  defined(ARDUINO_ESP32_DEV)	
#define 	RT_HW_BOARD_NAME  	"ESP32 Dev Module"     			//--Наименование платы;		
#define 	RT_HW_BOARD_QNT    	39								//--Количество пинов;
//--------------------------------
#elif defined(ARDUINO_ESP32S_DEV_BTH_EIS)	
#define 	RT_HW_BOARD_NAME  	"ESP32 Dev Module+BlueTooth)" 	//--Наименование платы;
#define 	RT_HW_BOARD_QNT   	39								//--Количество пинов;
#define     RT_HW_PERMIT_UARTB									//--Разрешение работы с внутренним BlueTooth;
#define     RT_HW_ESP32_PERMIT_UARTB							//--Разрешение создание объекта;
//--------------------------------
#elif defined(ARDUINO_TTGO_T1)	
#define 	RT_HW_BOARD_NAME  	"TTGO T1-DISPLAY)"  			//--Наименование платы;
#define 	RT_HW_BOARD_QNT   	24								//--Количество пинов;
//--------------------------------
#else
#define 	RT_HW_BOARD_NAME  	"Near of kin ESP32 Dev Module"  //--Наименование платы;	
#define 	RT_HW_BOARD_QNT    	20								//--Количество пинов;
#endif
//------------------------------------------------------------------------------------------------
#define    	RT_HW_BOARD_ESP32_DEV								//--Идентификатор типа платы;
#define  	RT_HW_CORE_ESP										//--Идентификатор CORE;
#define  	RT_HW_CORE_ESP32									//--Идентификатор CORE;	
#define  	RT_HW_CORE_ESP32S									//--Идентификатор CORE;		
//-------------------------------------------------------------------------------------------------
#endif	 
//=================================================================================================
//								2.M5Stack Core-ESP32
//=================================================================================================
#if !defined(RT_HW_BOARD_CODE) && (\
     defined(ARDUINO_M5Stack_Core_ESP32) || defined(ARDUINO_M5Stack_Core2))	
//-------------------------------------------------------------------------------------------------
#define 	RT_HW_BOARD_CODE   	12 								//--Идентификатор выбора платы;
//-------------------------------------------------------------------------------------------------
#define 	RT_HW_BOARD_MEMORY 	"FLASH=1310Kb; RAM=328Kb; Ext_FLASH=4/16Mb;"//--Параметры памяти;
#define 	RT_HW_BOARD_FCPU   	240								//--Частота процессора;	
#define 	RT_HW_BOARD_VCC   	3300							//--Значение Vсс процессора;
//-------------------------------------------------------------------------------------------------
#if  defined(ARDUINO_M5Stack_Core_ESP32)	
#define 	RT_HW_BOARD_NAME  	"M5Stack-Core-ESP32"     		//--Наименование платы;		
#define 	RT_HW_BOARD_QNT    	39								//--Количество пинов;
//--------------------------------
#elif defined(ARDUINO_M5Stack_Core2)	
#define 	RT_HW_BOARD_NAME  	"M5Stack-Core2)" 				//--Наименование платы;
#define 	RT_HW_BOARD_QNT   	39								//--Количество пинов;
//--------------------------------
#else
#define 	RT_HW_BOARD_NAME  	"Near of kin M5Stack-Core-ESP32 "//--Наименование платы;	
#define 	RT_HW_BOARD_QNT    	39								//--Количество пинов;
#endif
//------------------------------------------------------------------------------------------------
#define    	RT_HW_BOARD_ESP32_DEV								//--Идентификатор типа платы;
#define  	RT_HW_CORE_ESP										//--Идентификатор CORE;
#define  	RT_HW_CORE_ESP32									//--Идентификатор CORE;	
#define  	RT_HW_CORE_ESP32S									//--Идентификатор CORE;		
//-------------------------------------------------------------------------------------------------
#endif
//=================================================================================================
//								3.ESP32-PICO
//=================================================================================================
#if !defined(RT_HW_BOARD_CODE) && (\
     defined(ARDUINO_M5Stack_ATOM) || defined(ARDUINO_STAMP_PICO))	
//-------------------------------------------------------------------------------------------------
#define 	RT_HW_BOARD_CODE   	12 								//--Идентификатор выбора платы;
//-------------------------------------------------------------------------------------------------
#define 	RT_HW_BOARD_MEMORY 	"FLASH=1310Kb; RAM=328Kb; Ext_FLASH=4/16Mb;"//--Параметры памяти;
#define 	RT_HW_BOARD_FCPU   	240								//--Частота процессора;	
#define 	RT_HW_BOARD_VCC   	3300							//--Значение Vсс процессора;
//-------------------------------------------------------------------------------------------------
#if  defined(ARDUINO_M5Stack_ATOM)	
#define 	RT_HW_BOARD_NAME  	"M5Stack-ATOM"     				//--Наименование платы;		
#define 	RT_HW_BOARD_QNT    	14								//--Количество пинов;
#define    	RT_HW_BOARD_ESP32_ATOM								//--Идентификатор типа платы;
//--------------------------------
#elif defined(ARDUINO_STAMP_PICO)	
#define 	RT_HW_BOARD_NAME  	"ESP32S STAMP-PICO" 			//--Наименование платы;
#define 	RT_HW_BOARD_QNT   	25								//--Количество пинов;
#define    	RT_HW_BOARD_ESP32_PICO								//--Идентификатор типа платы;
//--------------------------------
#else
#define 	RT_HW_BOARD_NAME  	"Near of kin ESP32 STAMP-PICO"	//--Наименование платы;	
#define 	RT_HW_BOARD_QNT    	25								//--Количество пинов;
#define    	RT_HW_BOARD_ESP32_PICO								//--Идентификатор типа платы;
#endif
//------------------------------------------------------------------------------------------------
#define  	RT_HW_CORE_ESP										//--Идентификатор CORE;
#define  	RT_HW_CORE_ESP32									//--Идентификатор CORE;	
#define  	RT_HW_CORE_ESP32PICO								//--Идентификатор CORE;		
//-------------------------------------------------------------------------------------------------
#endif
//=================================================================================================
//								4.ESP32C3
//=================================================================================================
#if !defined(RT_HW_BOARD_CODE) && (\
     defined(ARDUINO_ESP32C3_DEV) || \
	 defined(ARDUINO_ESP32C3_STAMP_C3_EIS)       || defined(ARDUINO_ESP32C3_STAMP_C3U_EIS) || \
	 defined(ARDUINO_ESP32C3_TTGO_T_OI_PLUS_EIS) || \
	 defined(ARDUINO_ESP32C3_LUATOS_USB_EIS)     || defined(ARDUINO_ESP32C3_LUATOS_CLASSIC_EIS))
//-------------------------------------------------------------------------------------------------
#define 	RT_HW_BOARD_CODE   	13 									//--Идентификатор выбора платы;
//-------------------------------------------------------------------------------------------------
#define 	RT_HW_BOARD_MEMORY 	"FLASH=1310Kb; RAM=328Kb; Ext_FLASH=4/16Mb;"//--Параметры памяти;
#define 	RT_HW_BOARD_FCPU   	160									//--Частота процессора;	
#define 	RT_HW_BOARD_VCC   	3300								//--Значение Vсс процессора;
//--------------------------------
#if   defined(ARDUINO_ESP32C3_DEV)      	
#define   	RT_HW_BOARD_NAME  	"ESP32C3 Dev Module"    			//--Наименование платы;
#define    	RT_HW_BOARD_ESP32C3_DEV									//--Идентификатор типа платы
#define 	RT_HW_BOARD_QNT    	24									//--Количество пинов;
//--------------------------------
#elif defined(ARDUINO_ESP32C3_STAMP_C3_EIS)
#define   	RT_HW_BOARD_NAME  	"ESP32C3 STAMP-C3 EIS"   			//--Наименование платы;
#define   	RT_HW_BOARD_ESP32C3_STAMP_C3_EIS						//--Идентификатор типа платы;
#define 	RT_HW_BOARD_QNT    	24									//--Количество пинов;
//--------------------------------
#elif defined(ARDUINO_ESP32C3_STAMP_C3U_EIS) 	
#define   	RT_HW_BOARD_NAME  	"ESP32C3 STAMP-C3U EIS"   			//--Наименование платы;
#define   	RT_HW_BOARD_ESP32C3_STAMP_C3U_EIS						//--Идентификатор типа платы;
#define 	RT_HW_BOARD_QNT    	24									//--Количество пинов;
//-------------------------------
#elif defined(ARDUINO_ESP32C3_TTGO_T_OI_PLUS_EIS)	
#define   	RT_HW_BOARD_NAME  	"ESP32C3 TTGO T-OI PLUS"        	//--Наименование платы;
#define   	RT_HW_BOARD_ESP32C3_TTGO_T_OI_PLUS_EIS                 	//--Идентификатор типа платы;
#define 	RT_HW_BOARD_QNT    	24									//--Количество пинов;
//--------------------------------
#elif defined(ARDUINO_ESP32C3_LUATOS_USB_EIS)	
#define   	RT_HW_BOARD_NAME  	"ESP32C3 LuatOS USB EIS"
#define  	RT_HW_BOARD_ESP32C3_LUATOS_USB_EIS						//--Идентификатор типа платы;
#define 	RT_HW_BOARD_QNT    	26									//--Количество пинов;
//--------------------------------
#elif defined(ARDUINO_ESP32C3_LUATOS_CLASSIC_EIS)	
#define   	RT_HW_BOARD_NAME    "ESP32C3 LuatOS Classic EIS"       	//--Наименование платы;
#define   	RT_HW_BOARD_ESP32C3_LUATOS_CLASSIC_EIS					//--Идентификатор типа платы;
#define 	RT_HW_BOARD_QNT    	26									//--Количество пинов;
//--------------------------------
#else
#define   	RT_HW_BOARD_NAME  	"Near of kin ESP32C3 Dev Module"    //--Наименование платы;
#define  	RT_HW_BOARD_ESP32C3_DEV									//--Идентификатор типа платы
#define 	RT_HW_BOARD_QNT    	39									//--Количество пинов;
#endif
//------------------------------------------------------------------------------------------------
#define  	RT_HW_CORE_ESP											//--Идентификатор CORE;
#define  	RT_HW_CORE_ESP32										//--Идентификатор CORE;	
#define  	RT_HW_CORE_ESP32C3										//--Идентификатор CORE;		
//-------------------------------------------------------------------------------------------------
#endif
//=================================================================================================
//								5.ESP32S2
//=================================================================================================
#if !defined(RT_HW_BOARD_CODE) && (\
     defined(ARDUINO_ESP32S2_DEV) || defined(ARDUINO_LOLIN_S2_PRO) || defined(ARDUINO_LOLIN_S2_MINI))
//-------------------------------------------------------------------------------------------------
#define 	RT_HW_BOARD_CODE   	15 									//--Идентификатор выбора платы;
//-------------------------------------------------------------------------------------------------
#define 	RT_HW_BOARD_MEMORY 	"FLASH=1310Kb; RAM=328Kb; Ext_FLASH=4/16Mb;"//--Параметры памяти;
#define 	RT_HW_BOARD_FCPU   	160									//--Частота процессора;	
#define 	RT_HW_BOARD_VCC   	3300								//--Значение Vсс процессора;
//--------------------------------
#if   defined(ARDUINO_ESP32S2_DEV)      	
#define   	RT_HW_BOARD_NAME  	"ESP32S2 Dev Module"    			//--Наименование платы;
#define    	RT_HW_BOARD_ESP32S2_DEV									//--Идентификатор типа платы
#define 	RT_HW_BOARD_QNT    	43									//--Количество пинов;
//--------------------------------
#elif defined(ARDUINO_LOLIN_S2_PRO)
#define   	RT_HW_BOARD_NAME  	"LOLIN S2 PRO"   					//--Наименование платы;
#define   	RT_HW_BOARD_LOLIN_S2_PRO								//--Идентификатор типа платы;
#define 	RT_HW_BOARD_QNT    	43									//--Количество пинов;
//--------------------------------
#elif defined(ARDUINO_LOLIN_S2_MINI)	
#define   	RT_HW_BOARD_NAME    "LOLIN S2 MINI"      		 		//--Наименование платы;
#define   	RT_HW_BOARD_LOLIN_S2_MINI								//--Идентификатор типа платы;
#define 	RT_HW_BOARD_QNT    	43									//--Количество пинов;
//--------------------------------
#else
#define   	RT_HW_BOARD_NAME  	"Near of kin ESP32C3 Dev Module"    //--Наименование платы;
#define  	RT_HW_BOARD_ESP32C3_DEV									//--Идентификатор типа платы
#define 	RT_HW_BOARD_QNT    	43									//--Количество пинов;
#endif
//------------------------------------------------------------------------------------------------
#define  	RT_HW_CORE_ESP											//--Идентификатор CORE;
#define  	RT_HW_CORE_ESP32										//--Идентификатор CORE;	
#define  	RT_HW_CORE_ESP32S2										//--Идентификатор CORE;		
//-------------------------------------------------------------------------------------------------
#endif
//=================================================================================================
//								6.ESP32S3
//=================================================================================================
#if !defined(RT_HW_BOARD_CODE) && (\
     defined(ARDUINO_ESP32S3_DEV) || defined(ARDUINO_BANANA_PI_PICO_W_S3))		
//-------------------------------------------------------------------------------------------------
#define 	RT_HW_BOARD_CODE   	16 									//--Идентификатор выбора платы;
//-------------------------------------------------------------------------------------------------
#define 	RT_HW_BOARD_MEMORY 	"FLASH=1310Kb; RAM=328Kb; Ext_FLASH=4/16Mb;"//--Параметры памяти;
#define 	RT_HW_BOARD_FCPU   	240									//--Частота процессора;	
#define 	RT_HW_BOARD_VCC   	3300								//--Значение Vсс процессора;
//--------------------------------
#if   defined(ARDUINO_ESP32S3_DEV)      	
#define   	RT_HW_BOARD_NAME  	"ESP32S3 Dev Module"    			//--Наименование платы;
#define    	RT_HW_BOARD_ESP32S3_DEV									//--Идентификатор типа платы
#define 	RT_HW_BOARD_QNT    	40									//--Количество пинов;
//--------------------------------
#elif defined(ARDUINO_BANANA_PI_PICO_W_S3)	
#define   	RT_HW_BOARD_NAME    "ESP32S3 BANANA PI PICO-W"          //--Наименование платы;
#define   	RT_HW_BOARD_BANANA_PI_PICO_W_S3							//--Идентификатор типа платы;
#define 	RT_HW_BOARD_QNT    	20									//--Количество пинов;
//--------------------------------
#else
#define   	RT_HW_BOARD_NAME  	"Near of kin ESP32S3 Dev Module"    //--Наименование платы;
#define  	RT_HW_BOARD_ESP32S3_DEV									//--Идентификатор типа платы
#define 	RT_HW_BOARD_QNT    	24									//--Количество пинов;
#endif
//------------------------------------------------------------------------------------------------
#define  	RT_HW_CORE_ESP											//--Идентификатор CORE;
#define  	RT_HW_CORE_ESP32										//--Идентификатор CORE;	
#define  	RT_HW_CORE_ESP32S3										//--Идентификатор CORE;		
//-------------------------------------------------------------------------------------------------
#endif
//=================================================================================================
//								2.Контроллер ESP32 ANON
//=================================================================================================	
#if !defined(RT_HW_BOARD_CODE) && (defined(ARDUINO_ARCH_ESP32) || defined(ESP32))
//-------------------------------------------------------------------------------------------------
#define 	RT_HW_BOARD_CODE   	19 								//--Идентификатор выбора платы;
//-------------------------------------------------------------------------------------------------
#define 	RT_HW_BOARD_MEMORY 	"FLASH=1310Kb; RAM=328Kb; Ext_FLASH=4/16Mb;"//--Параметры памяти;
#define 	RT_HW_BOARD_FCPU   	240								//--Частота процессора;	
#define 	RT_HW_BOARD_VCC   	3300							//--Значение Vсс процессора;
//-------------------------------------------------------------------------------------------------
#define 	RT_HW_BOARD_NAME  	"ESP32S ANON"     				//--Наименование платы;		
#define 	RT_HW_BOARD_QNT    	39								//--Количество пинов;
//------------------------------------------------------------------------------------------------
#define    	RT_HW_BOARD_ESP32_DEV								//--Идентификатор типа платы;
//-------------------------------------------------------------------------------------------------
#define  	RT_HW_CORE_ESP										//--Идентификатор CORE;
#define  	RT_HW_CORE_ESP32									//--Идентификатор CORE;	
#define  	RT_HW_CORE_ESP32S									//--Идентификатор CORE;		
//-------------------------------------------------------------------------------------------------
#endif
//=================================================================================================