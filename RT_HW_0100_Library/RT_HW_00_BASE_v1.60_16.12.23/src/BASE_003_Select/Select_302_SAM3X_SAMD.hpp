//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//										1.ARCH SAM3X8E
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//								1.1.Arduino DUE
//=================================================================================================
#if	!defined(RT_HW_BOARD_CODE) && (defined(ARDUINO_SAM_DUE))	
//-------------------------------------------------------------------------------------------------
#define RT_HW_BOARD_CODE       	5 								//--Идентификатор выбора платы;
//-------------------------------------------------------------------------------------------------
#define    RT_HW_BOARD_NAME     "Arduino DUE" 					//--Наименование платы;
#define    RT_HW_BOARD_QNT      64								//--Количество пинов;	
#define    RT_HW_BOARD_MEMORY	"FLASH=512Kb,RAM=64kB+32kB"		//--Параметры памяти;
#define    RT_HW_BOARD_FCPU     84 								//--Частота процессора;	
#define    RT_HW_BOARD_VCC      3300							//--Значение Vсс процессора;
#define    RT_HW_BOARD_SAM3X_DUE									//--Идентификатор типа платы;
#define    RT_HW_CORE_SAM3X										//--Идентификатор программной среды;
//--------------------------------------------------------------------------------------------------
#endif
//=================================================================================================
//								1.2.Arduino SAM3X8E ANON
//=================================================================================================
#if	!defined(RT_HW_BOARD_CODE) && (defined(__SAM3X8E__))	
//-------------------------------------------------------------------------------------------------
#define RT_HW_BOARD_CODE       	6 								//--Идентификатор выбора платы;
//-------------------------------------------------------------------------------------------------
#define    RT_HW_BOARD_NAME     "Arduino SAM3X8E ANON" 			//--Наименование платы;
#define    RT_HW_BOARD_QNT      64								//--Количество пинов;	
#define    RT_HW_BOARD_MEMORY	"FLASH=512Kb,RAM=64kB+32kB"		//--Параметры памяти;
#define    RT_HW_BOARD_FCPU     84 								//--Частота процессора;	
#define    RT_HW_BOARD_VCC      3300							//--Значение Vсс процессора;
#define    RT_HW_BOARD_SAM3X_DUE									//--Идентификатор типа платы;
#define    RT_HW_CORE_SAM3X										//--Идентификатор программной среды;
//--------------------------------------------------------------------------------------------------
#endif

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//												2.ARCH SAMD
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=================================================================================================
//											2.1.SAMD21
//=================================================================================================
/*
#if !defined(RT_HW_BOARD_CODE) && (\
     defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRZERO) || \
     defined(ARDUINO_SAMD_MKRWIFI1010)|| defined(ARDUINO_SAMD_NANO_33_IOT) || \
	 defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300)  || defined(ARDUINO_SAMD_MKRWAN1310)   || \
	 defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500)   || defined(ARDUINO_SAMD_MKRVIDOR4000) || \
	 defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS)                       || \
	 defined(__SAMD21E18A__) || defined(__SAMD21G18A__)                    || \
	 defined(__SAMD51__)     || defined(__SAMD51J20A__) || \
	 defined(__SAMD51J19A__) || defined(__SAMD51G19A__) || defined(__SAMD51P19A__))
//-------------------------------------------------------------------------------------------------
#define RT_HW_BOARD_CODE       	7 								//--Идентификатор выбора платы;
//-------------------------------------------------------------------------------------------------
#define    RT_HW_BOARD_NAME     "Arduino SAMD21" 				//--Наименование платы;
#define    RT_HW_BOARD_QNT      64								//--Количество пинов;	
#define    RT_HW_BOARD_MEMORY	"FLASH=xxxKb,RAM=6xxkB"			//--Параметры памяти;
#define    RT_HW_BOARD_FCPU     84 								//--Частота процессора;	
#define    RT_HW_BOARD_VCC      3300							//--Значение Vсс процессора;
#define    RT_HW_BOARD_SAMD21									//--Идентификатор типа платы;
#define    RT_HW_CORE_SAMD										//--Идентификатор программной среды;
//-------------------------------------------------------------------------------------------------
#endif
*/

