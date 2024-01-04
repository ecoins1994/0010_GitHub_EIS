//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//						             RT_HW_BASE.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef   RT_HW_BASE_h
#define   RT_HW_BASE_h
//=================================================================================================
#define   RT_HW_BASE_VER 		 (uint8_t)170				//--����� ������;
#define   RT_HW_BASE_VER_NAME 	"1.7.0 01.01.2024"			//--������������ ������;
//=================================================================================================
//								1.Macros,enum, arrays in PROGMEM
//=================================================================================================
#include "BASE_001_Common/COM_101_defined_param.hpp"		//--�������;
#include "BASE_001_Common/COM_102_enum_array.hpp"			//--������������(enum),������� � PROGMEM;
//=================================================================================================
//								2.C�������� ��������
//=================================================================================================
#include "BASE_002_Struct/Struct_201_System.hpp"			//--��������� ������;
#include "BASE_002_Struct/Struct_202_Sheduler.hpp"			//--��������� �����, ���������� ������� �����;
#include "BASE_002_Struct/Struct_205_Generator.hpp"			//--����������, ��������, �����������;
#include "BASE_002_Struct/Struct_210_Pins.hpp"				//--����;
//=================================================================================================
//								3.����� ����
//							[AVR,SAM,SAMD21,ESP8266,ESP32,RP2040,STM32,ANON]
//=================================================================================================
#include "BASE_003_Select/Select_301_AVR.hpp"				//--Select a board AVR;
#include "BASE_003_Select/Select_302_SAM3X_SAMD.hpp"		//--Select a board SAMX,SAMD;
#include "BASE_003_Select/Select_303_ESP8266.hpp"			//--Select a board ESP8266;
#include "BASE_003_Select/Select_304_ESP32.hpp"				//--Select a board ESP32;
#include "BASE_003_Select/Select_305_RP2040.hpp"			//--Select a board Raspberry Pi Pico;
#include "BASE_003_Select/Select_310_1_STM32F1.hpp"			//--Select a board STM32F1;
#include "BASE_003_Select/Select_310_2_STM32F4x1.hpp"		//--Select a board STM32F4x1;
#include "BASE_003_Select/Select_310_3_STM32F4x7.hpp"		//--Select a board STM32F4x7;
#include "BASE_003_Select/Select_310_4_STM32H7.hpp"			//--Select a board STM32H7;
#include "BASE_003_Select/Select_390_ANON.hpp"				//--Select a board for the �ore ANON;
//=================================================================================================
//								4.�������� CORE ��� ������������ MCU 
//							[AVR,SAM,SAMD21,ESP8266,ESP32,RP2040,STM32,ANON]
//=================================================================================================
#include "BASE_004_Core/CORE_401_AVR.hpp"					//--CORE AVR;
#include "BASE_004_Core/CORE_402_SAM3X.hpp"					//--CORE SAM;
#include "BASE_004_Core/CORE_403_ESP8266.hpp"				//--CORE ESP8266;
#include "BASE_004_Core/CORE_404_ESP32.hpp"					//--CORE ESP32;
#include "BASE_004_Core/CORE_405_RP2040.hpp"				//--CORE Raspberry Pi Pico;
#include "BASE_004_Core/CORE_410_STM32.hpp"					//--CORE STM32;
#include "BASE_004_Core/CORE_490_ANON.hpp"					//--CORE ANON;
#include "BASE_004_Core/CORE_491_ADD_DEFINE.hpp"			//--CORE Add define;
//=================================================================================================
//								5.�������� �������������� ����
//							[AVR,SAM,SAMD21,ESP8266,ESP32,RP2040,STM32,ANON]
//=========================================================	========================================
#include  "BASE_005_Board/Board_501_AVR.hpp"	    		//--Board AVR;
#include  "BASE_005_Board/Board_502_SAM3X_SAMD.hpp"			//--Board SAMX,SAMD;
#include  "BASE_005_Board/Board_503_ESP8266.hpp"			//--Board ESP8266;
#include  "BASE_005_Board/Board_504_1_ESP32S.hpp"			//--Board ESP32S;
#include  "BASE_005_Board/Board_504_2_ESP32_M5_PICO.hpp"	//--Board_M5Stack;
#include  "BASE_005_Board/Board_504_3_ESP32C3.hpp"			//--Board ESP32_C3;
#include  "BASE_005_Board/Board_504_4_ESP32S2.hpp"			//--Board ESP32S2;
#include  "BASE_005_Board/Board_504_5_ESP32S3.hpp"			//--Board ESP32S3;
#include  "BASE_005_Board/Board_505_RP2040.hpp"				//--Board RP2040(Raspberry Pi Pico);
#include  "BASE_005_Board/Board_510_1_STM32F103X.hpp"		//--Board STM32F103X;
#include  "BASE_005_Board/Board_510_2_STM32F4x1X.hpp"		//--Board STM32F4x1X;
#include  "BASE_005_Board/Board_510_3_STM32F4x7X.hpp"		//--Board STM32F4x7X;
#include  "BASE_005_Board/Board_510_4_STM32H7.hpp"			//--Board STM32H7;
#include  "BASE_005_Board/Board_590_ANON.hpp"				//--Board ANON (always last  of the list);
//=================================================================================================
//								6.��������� ������ ��� ����� � ���������������� ������� 
//                                  (���������� ��������� �� CORE � Board)
//=================================================================================================
#include "BASE_002_Struct/Struct_220_Link.hpp"				//--������� ���������;
//=================================================================================================
//								7.�������������� ������������ ����������
//=================================================================================================
#include "RT_HW_ONEWIRE.h"	//--����������� ���  ������ � 1-Wire;
//=================================================================================================
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//									�����   RT_HW_BASE.h
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class RT_HW_BASE{
public:
//-------------------------------------------------------------------------------------------------
RT_HW_STRUCT_MESS		mess;								//--��������� ��� ��������� ��������� (������������ � �.�. � ��������);
RT_HW_STRUCT_BUFF		buff;								//--��������� ��������;
RT_HW_STRUCT_SHED		shed;								//--��������� ����������;
RT_HW_STRUCT_UNIX_ID    unixID;								//--����� � ������� UNIX;
RT_HW_STRUCT_DEVICE 	device;								//--��������� ��� ������������ ����������� ��������� (����, cs � �.�.);
RT_HW_STRUCT_CONSOLE	console;							//--������ ��� ������ � ��������;
RT_HW_STRUCT_I2C_DEV    dvi2c;								//--����������������� ���������� i2c;
uint8_t                 vInit=0;							//--���� �������������� ����������(������� ��� ������������ MCU);
//uint8_t                 customETH=0;							//--���� �������������� Ethernet;
//void clb0(CallBack fName){;};

//-------------------------------------API general-------------------------------------------------
#include "BASE_100_API System/API_101_FuncMain.hpp"			//--API ������� ��������;
#include "BASE_100_API System/API_102_FuncNamePin.hpp"		//--API ������� ��� ������ � ������� � ������� �����(� �.�. STM32,ESP8266)
#include "BASE_100_API System/API_103_FuncTime.hpp"			//--API ������� ��� ������ �� ��������;
#include "BASE_100_API System/API_105_FuncGen.hpp"			//--API ������� ��� ������ � ������������, ����������, �������������;
#include "BASE_100_API System/API_106_FuncAdd.hpp"			//--API ������� ��������������;
#include "BASE_100_API System/API_107_FuncMess.hpp"			//--API ������� ��� ������������ ����������;
#include "BASE_100_API System/API_110_FuncEthernet.hpp"		//--API ������� ��� Ethernet,Wi-Fi;
#include "BASE_100_API System/API_111_Sheduler.hpp"			//--API ������� ��� ����������, ���������� ������� �����;
#include "BASE_100_API System/API_120_UnixTime.hpp"			//--API ������� ��� ������� � UNIX-�������;
//-------------------------------------API for FLProg----------------------------------------------
#include "BASE_101_API FLProg/API_101_Utilites.hpp"			//--API ������ ��� ������ � FLProg;
//-------------------------------------API communication-------------------------------------------
#include "BASE_120_API Link/API_121_Pins.hpp"				//--API ��� ������ � ������;
#include "BASE_120_API Link/API_122_Uart.hpp"				//--API ��� ������ � UART;
#include "BASE_120_API Link/API_123_I2C.hpp"				//--API ��� ������ � i2c;
#include "BASE_120_API Link/API_124_SPI.hpp"				//--API ��� ������ � SPI;
#include "BASE_120_API Link/API_127_SPN.hpp"				//--API ��� ������ � SPN;
#include "BASE_120_API Link/API_128_CAN.hpp"				//--API ��� ������ � CAN;
//-------------------------------------API ModBus--------------------------------------------------

//-------------------------------------API console-------------------------------------------------
#include "BASE_150_API Console/API_151_ConsoleFunc.hpp"		//--API ������� ������� ��� �����  � ��������; 
#include "BASE_150_API Console/API_152_ConsoleHead.hpp"		//--API ������� ������ ���������� �� �������;
//-------------------------------------------------------------------------------------------------
RT_HW_BASE();												//--�����������;
private:
};  //---END CLASS RT_HW_BASE.h====================================================================
extern RT_HW_BASE 				RT_HW_Base; 				//--External reference to the RT_HW_Base object;
//=================================================================================================
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//										���������� �������
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//void cns(String v, char x=''){RT_HW_Base.consoleBegin(); if(RT_HW_Base.console.ok){return;}};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//										������ ��� ������ � ���������
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "BASE_300_API Filters/API_301_FilterMedian3.hpp"	//--API ��������� ������ 3-�� ������� (����� �������);
#include "BASE_300_API Filters/API_302_FilterMedian.hpp"	//--API ��������� ������ n-�� �������;
#include "BASE_300_API Filters/API_303_FilterRingAverage.hpp"//-API ������ �������� �������� � ��������� �������;
#include "BASE_300_API Filters/API_304_FilterCritical.hpp"	//--API ������ ����������� ��������;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//										������ ��� ������ � ��������������� ���������
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//#include "BASE_400_API Func/API_100_Class_UnixTime.hpp"		//--API ������ � �������� UNIX;

//-------------------------------------------------------------------------------------------------
#endif //---RT_HW_BASE_h===========================================================================
//-------------------------------------------------------------------------------------------------