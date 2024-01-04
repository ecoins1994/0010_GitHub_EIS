//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							  	MCU Core STM32F4x1
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//								1.BLACKPILL F401CX
//=================================================================================================
#if !defined(RT_HW_BOARD_CODE) && (defined(ARDUINO_BLACKPILL_F401CC) || defined(ARDUINO_BLACKPILL_F401CE))
//-------------------------------------------------------------------------------------------------
#define 	RT_HW_BOARD_FCPU   	84									//--Freq MCU;	
#define 	RT_HW_BOARD_VCC   	3300								//--Vсс  MCU;
#define 	RT_HW_BOARD_QNT    	30									//--Number of pins;
#define 	RT_HW_BOARD_CODE   	131 								//--ID select board Arduino IDE;
#define     RT_HW_BOARD_BLACKPILL_F401CX							//--ID select board RT_HW_Base.h;
//--------------------------------------------------------------------------------------------------
#define     RT_HW_CORE_STM32										//--ID CORE General;
#define     RT_HW_CORE_STM32F4C										//--ID CORE Family;
//-------------------------------------------------------------------------------------------------
#if  		defined(ARDUINO_BLACKPILL_F401CC)	
#define 	RT_HW_BOARD_NAME  	"BlackPill F401CC"     				//--Name board;		
#define 	RT_HW_BOARD_MEMORY 	"FLASH:256Kb; OTP=512b; SRAM:64Kb;"	//--Memory;
//-------------------------------------------------------------------------------------------------
#elif		defined(ARDUINO_BLACKPILL_F401CE)	
#define 	RT_HW_BOARD_NAME  	"BlackPill F401CE"     				//--Name board;		
#define 	RT_HW_BOARD_MEMORY 	"FLASH:256Kb; OTP=512b; SRAM:64Kb;"	//--Memory;
//-------------------------------------------------------------------------------------------------
#else
#define 	RT_HW_BOARD_NAME  	"Near of kin BlackPill F401Cx"  	//--Name board;		
#define 	RT_HW_BOARD_MEMORY 	"FLASH:256Kb; OTP=512b; SRAM:64Kb;"	//--Memory;
//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
#endif 		//-------------------------------------------------------------------------------------
//=================================================================================================
//								2.GENERIC F401CXXX
//=================================================================================================
#if !defined(RT_HW_BOARD_CODE) && (\
	 defined(ARDUINO_GENERIC_F401CBUX) || defined(ARDUINO_GENERIC_F401CCUX) || defined(ARDUINO_GENERIC_F401CBYX) ||\
     defined(ARDUINO_GENERIC_F401CYXX) || defined(ARDUINO_GENERIC_F401CDUX) || defined(ARDUINO_GENERIC_F401CEUX) ||\
     defined(ARDUINO_GENERIC_F401CDYX) || defined(ARDUINO_GENERIC_F401CEYX) || defined(ARDUINO_GENERIC_F401CCFX))
//-------------------------------------------------------------------------------------------------
#define 	RT_HW_BOARD_FCPU   	84									//--Freq MCU;	
#define 	RT_HW_BOARD_VCC   	3300								//--Vсс  MCU;
#define 	RT_HW_BOARD_QNT    	30									//--Number of pins;
#define 	RT_HW_BOARD_CODE   	132 								//--ID select board Arduino IDE;
#define     RT_HW_BOARD_GENERIC_F401CXXX 							//--ID select board RT_HW_Base.h;
//-------------------------------------------------------------------------------------------------
#define     RT_HW_CORE_STM32										//--ID CORE General;
#define     RT_HW_CORE_STM32F4C										//--ID CORE Family;
//-------------------------------------------------------------------------------------------------
#if			defined(ARDUINO_GENERIC_F401CBUX)	
#define 	RT_HW_BOARD_NAME  	"BlackPill F401CBUX"     			//--Name board;		
#define 	RT_HW_BOARD_MEMORY 	"FLASH:256Kb; OTP=512b; SRAM:64Kb;"	//--Memory;
//-------------------------------------------------------------------------------------------------
#elif		defined(ARDUINO_GENERIC_F401CCUX)	
#define 	RT_HW_BOARD_NAME  	"GENERIC F401CCUX"     				//--Name board;		
#define 	RT_HW_BOARD_MEMORY 	"FLASH:256Kb; OTP=512b; SRAM:64Kb;"	//--Memory;
//-------------------------------------------------------------------------------------------------
#elif		defined(ARDUINO_GENERIC_F401CBYX)	
#define 	RT_HW_BOARD_NAME  	"GENERIC F401CBYX"     				//--Name board;		
#define 	RT_HW_BOARD_MEMORY 	"FLASH:256Kb; OTP=512b; SRAM:64Kb;"	//--Memory;
//-------------------------------------------------------------------------------------------------
#elif		defined(ARDUINO_GENERIC_F401CBYX)	
#define 	RT_HW_BOARD_NAME  	"GENERIC F401CBYX"     				//--Name board;		
#define 	RT_HW_BOARD_MEMORY 	"FLASH:256Kb; OTP=512b; SRAM:64Kb;"	//--Memory;
//-------------------------------------------------------------------------------------------------
#elif		defined(ARDUINO_GENERIC_F401CYXX)	
#define 	RT_HW_BOARD_NAME  	"GENERIC F401CYXX"     				//--Name board;		
#define 	RT_HW_BOARD_MEMORY 	"FLASH:256Kb; OTP=512b; SRAM:64Kb;"	//--Memory;
//-------------------------------------------------------------------------------------------------
#elif		defined(ARDUINO_GENERIC_F401CDUX)	
#define 	RT_HW_BOARD_NAME  	"GENERIC F401CDUX"     				//--Name board;		
#define 	RT_HW_BOARD_MEMORY 	"FLASH:256Kb; OTP=512b; SRAM:64Kb;"	//--Memory;
//-------------------------------------------------------------------------------------------------
#elif		defined(ARDUINO_GENERIC_F401CEUX)	
#define 	RT_HW_BOARD_NAME  	"GENERIC F401CEUX"     				//--Name board;		
#define 	RT_HW_BOARD_MEMORY 	"FLASH:256Kb; OTP=512b; SRAM:64Kb;"	//--Memory;
//-------------------------------------------------------------------------------------------------
#elif		defined(ARDUINO_GENERIC_F401CDYX)	
#define 	RT_HW_BOARD_NAME  	"GENERIC F401CDYX"     				//--Name board;		
#define 	RT_HW_BOARD_MEMORY 	"FLASH:256Kb; OTP=512b; SRAM:64Kb;"	//--Memory;
//-------------------------------------------------------------------------------------------------
#elif		defined(ARDUINO_GENERIC_F401CEYX)	
#define 	RT_HW_BOARD_NAME  	"GENERIC F401CEYX"     				//--Name board;		
#define 	RT_HW_BOARD_MEMORY 	"FLASH:256Kb; OTP=512b; SRAM:64Kb;"	//--Memory;
//-------------------------------------------------------------------------------------------------
#elif		defined(ARDUINO_GENERIC_F401CCFX)	
#define 	RT_HW_BOARD_NAME  	"GENERIC F401CCFX"     				//--Name board;		
#define 	RT_HW_BOARD_MEMORY 	"FLASH:256Kb; OTP=512b; SRAM:64Kb;"	//--Memory;
//-------------------------------------------------------------------------------------------------
#else
#define 	RT_HW_BOARD_NAME  	"Near of kin STM32F401xxx"  		//--Name board;		
#define 	RT_HW_BOARD_MEMORY 	"FLASH:256Kb; OTP=512b; SRAM:64Kb;"	//--Memory;
//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
#endif		//-------------------------------------------------------------------------------------
//=================================================================================================
//								3.BLACKPILL F411CX
//=================================================================================================
#if !defined(RT_HW_BOARD_CODE) && (defined(ARDUINO_BLACKPILL_F411CE))
//-------------------------------------------------------------------------------------------------
#define 	RT_HW_BOARD_FCPU   	100									//--Freq MCU;	
#define 	RT_HW_BOARD_VCC   	3300								//--Vсс  MCU;
#define 	RT_HW_BOARD_QNT    	30									//--Number of pins;
#define 	RT_HW_BOARD_CODE   	133 								//--ID select board Arduino IDE;
#define     RT_HW_BOARD_BLACKPILL_F411CX 							//--ID select board RT_HW_Base.h;
//--------------------------------------------------------------------------------------------------
#define     RT_HW_CORE_STM32										//--ID CORE General;
#define     RT_HW_CORE_STM32F4C										//--ID CORE Family;
//-------------------------------------------------------------------------------------------------
#if  		defined(ARDUINO_BLACKPILL_F411CE)	
#define 	RT_HW_BOARD_NAME  	"BlackPill F411CE"     				//--Name board;		
#define 	RT_HW_BOARD_MEMORY 	"FLASH:512Kb; SRAM:128Kb;"			//--Memory;
//-------------------------------------------------------------------------------------------------
#else
#define 	RT_HW_BOARD_NAME  	"Near of kin BlackPill F411Cxx"  	//--Name board;		
#define 	RT_HW_BOARD_MEMORY 	"FLASH:512Kb; SRAM:128Kb;"			//--Memory;
//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
#endif		//-------------------------------------------------------------------------------------
//=================================================================================================
//								4.GENERIC F411Cxx
//=================================================================================================
#if !defined(RT_HW_BOARD_CODE) && (\
     defined(ARDUINO_BLACKPILL_F411CE) ||\
	 defined(ARDUINO_GENERIC_F411CCUX) || defined(ARDUINO_GENERIC_F411CCYX) ||\
     defined(ARDUINO_GENERIC_F411CEUX) || defined(ARDUINO_GENERIC_F411CEYX))
//-------------------------------------------------------------------------------------------------
#define 	RT_HW_BOARD_FCPU   	100									//--Freq MCU;	
#define 	RT_HW_BOARD_VCC   	3300								//--Vсс  MCU;
#define 	RT_HW_BOARD_QNT    	30									//--Number of pins;
#define 	RT_HW_BOARD_CODE   	134 								//--ID select board Arduino IDE;
#define     RT_HW_BOARD_GENERIC_F411CXXX 							//--ID select board RT_HW_Base.h;
//-------------------------------------------------------------------------------------------------
#define     RT_HW_CORE_STM32										//--ID CORE General;
#define     RT_HW_CORE_STM32F4C										//--ID CORE Family;
//-------------------------------------------------------------------------------------------------
#if  		defined(ARDUINO_BLACKPILL_F411CE)	
#define 	RT_HW_BOARD_NAME  	"BlackPill F411CE"     				//--Name board;		
#define 	RT_HW_BOARD_MEMORY 	"FLASH:512Kb; SRAM:128Kb;"			//--Memory;
//-------------------------------------------------------------------------------------------------
#elif		defined(ARDUINO_GENERIC_F411CCUX)	
#define 	RT_HW_BOARD_NAME  	"GENERIC F411CCUX"     				//--Name board;		
#define 	RT_HW_BOARD_MEMORY 	"FLASH:512Kb; SRAM:128Kb;"			//--Memory;
//-------------------------------------------------------------------------------------------------
#elif		defined(ARDUINO_GENERIC_F411CCYX)	
#define 	RT_HW_BOARD_NAME  	"GENERIC F411CCYX"     				//--Name board;		
#define 	RT_HW_BOARD_MEMORY 	"FLASH:512Kb; SRAM:128Kb;"			//--Memory;
//-------------------------------------------------------------------------------------------------
#elif		defined(ARDUINO_GENERIC_F411CEUX)	
#define 	RT_HW_BOARD_NAME  	"GENERIC F411CEUX"     				//--Name board;		
#define 	RT_HW_BOARD_MEMORY 	"FLASH:512Kb; SRAM:128Kb;"			//--Memory;
//-------------------------------------------------------------------------------------------------
#elif		defined(ARDUINO_GENERIC_F411CEUX)	
#define 	RT_HW_BOARD_NAME  	"GENERIC F411CEUX"     				//--Name board;		
#define 	RT_HW_BOARD_MEMORY 	"FLASH:512Kb; SRAM:128Kb;"			//--Memory;
//-------------------------------------------------------------------------------------------------
#else
#define 	RT_HW_BOARD_NAME  	"Near of kin STM32F411Cxx"  		//--Name board;		
#define 	RT_HW_BOARD_MEMORY 	"FLASH:512Kb; SRAM:128Kb;"			//--Memory;
//-------------------------------------------------------------------------------------------------
#endif
//-------------------------------------------------------------------------------------------------
#endif 		//-------------------------------------------------------------------------------------
//=================================================================================================
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++							  