#include "RT_HW_BASE.h"	 
//#################################################################################################
//
//							 					I2C [.cpp]
//
// codeErr: 0-ok, 1-too much data; 2-Nack to send an address; 3-Nack for data transfer; 4-another error i2c; 
// 5-invalid controller;           6-invalid bus; 7-invalid address(>=254);
// 8-bus not configured as master; 9-another error;
//#################################################################################################

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							 	1.CREATING AN OBJECT i2c for MCU
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//										1.STM32
//=================================================================================================
#if !defined(RT_HW_MCU_CREATE_I2C) && defined(RT_HW_CORE_STM32)	
    #define  RT_HW_MCU_CREATE_I2C
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_I2C1) && defined(RT_HW_CREATE_I2C1)
TwoWire Wire1(RT_HW_I2C1_SDA, RT_HW_I2C1_SCL);
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_I2C2) && defined(RT_HW_CREATE_I2C2)
TwoWire Wire2(RT_HW_I2C2_SDA, RT_HW_I2C2_SCL);
#endif
//-------------------------------------------------------------------------------------------------
#endif
//=================================================================================================
//										2.RP2040
//=================================================================================================
#if !defined(RT_HW_MCU_CREATE_I2C) && defined(RT_HW_CORE_RP2040)	
    #define  RT_HW_MCU_CREATE_I2C
//--------------------------------------------------------------------------------------------------
#endif
//=================================================================================================
//										3.ESP32
//=================================================================================================
#if !defined(RT_HW_MCU_CREATE_I2C) &&  defined(RT_HW_CORE_ESP32)	
    #define  RT_HW_MCU_CREATE_I2C
//-------------------------------------------------------------------------------------------------
#endif
//=================================================================================================
//										4.ESP8266
//=================================================================================================
#if !defined(RT_HW_MCU_CREATE_I2C) && defined(RT_HW_CORE_ESP8266)	
    #define  RT_HW_MCU_CREATE_I2C
//-------------------------------------------------------------------------------------------------
#endif
//=================================================================================================
//										5.AVR
//=================================================================================================
#if !defined(RT_HW_MCU_CREATE_I2C) && defined(RT_HW_CORE_AVR)	
    #define  RT_HW_MCU_CREATE_I2C
//-------------------------------------------------------------------------------------------------
#endif
//=================================================================================================
//										9.Other MCU
//=================================================================================================
#if !defined(RT_HW_MCU_CREATE_I2C)	
     #define RT_HW_MCU_CREATE_I2C
//-------------------------------------------------------------------------------------------------
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//									2.FUNCTION begin/endTransaction(), i2cSetClock
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//									2.1.i2cBeginTransmission(adr,bus)
//=================================================================================================
void     RT_HW_BASE:: i2cBeginTransmission(uint8_t adr, uint8_t bus){
if(i2cGetStatus(bus)!=1){return;};		//--Exit if bus is not master;
//-------------------------------------------------------------------------------------------------	
#if defined(RT_HW_PERMIT_I2C0)
if(bus==0){Wire.beginTransmission(adr);  return;};
#endif	
//-------------------------------------------------------------------------------------------------	
#if defined(RT_HW_PERMIT_I2C1)
if(bus==1){Wire1.beginTransmission(adr); return;};
#endif	
//-------------------------------------------------------------------------------------------------	
#if defined(RT_HW_PERMIT_I2C2)
if(bus==2){Wire2.beginTransmission(adr); return;};
#endif	
//-------------------------------------------------------------------------------------------------		
if(adr || bus) {return;}	//--For blocking warnings from C++;
};
//=================================================================================================
//									2.2.i2cEndTransmission(bus)
//=================================================================================================
uint8_t  RT_HW_BASE:: i2cEndTransmission(uint8_t bus){
if(i2cGetStatus(bus)!=1){return 5;};	//--Exit if bus is not master;
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_I2C0)
if(bus==0){return Wire.endTransmission();};
#endif	
//-------------------------------------------------------------------------------------------------	
#if defined(RT_HW_PERMIT_I2C1)
if(bus==1){return Wire1.endTransmission();};
#endif	
//-------------------------------------------------------------------------------------------------	
#if defined(RT_HW_PERMIT_I2C2)
if(bus==2){return Wire2.endTransmission();};
#endif
//-------------------------------------------------------------------------------------------------	
if(bus) {return 6;}		//--For blocking warnings from C++
return 6;}
//=================================================================================================
//						 			2.3.Set speed  bus i2c;
//=================================================================================================
void     RT_HW_BASE:: i2cSetClock(uint32_t speed,uint8_t bus){
if(speed==0){speed=RT_HW_I2C_SPEED;}
//-------------------------------------------------------------------------------------------------	
#if defined(RT_HW_PERMIT_I2C0) 
if(bus==0){Wire.setClock(speed);    return;}
#endif	
//-------------------------------------------------------------------------------------------------	
#if defined(RT_HW_PERMIT_I2C1)
if(bus==1){Wire1.setClock(speed); return;};
#endif
//-------------------------------------------------------------------------------------------------	
#if defined(RT_HW_PERMIT_I2C2)
if(bus==2){Wire2.setClock(speed); return;}
#endif	
//-------------------------------------------------------------------------------------------------	
if(speed || bus) {return;}		//--For blocking warnings from C++;
};
//=================================================================================================


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//									3.FUNCTION i2c() 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//									3.1.i2cFlush(bus)
//=================================================================================================
uint8_t  RT_HW_BASE:: i2cFlush(uint8_t bus){
//-------------------------------------------------------------------------------------------------	
#if defined(RT_HW_PERMIT_I2C0)
if(bus==0){Wire.flush(); return 1;}
#endif	
//-------------------------------------------------------------------------------------------------	
#if defined(RT_HW_PERMIT_I2C1)
if(bus==1){Wire1.flush(); return 1;}
#endif	
//-------------------------------------------------------------------------------------------------	
#if defined(RT_HW_PERMIT_I2C2)
if(bus==2){Wire2.flush(); return 1;}
#endif	
//-------------------------------------------------------------------------------------------------	
if(bus) {return 0;}		//--For blocking warnings from C++
return 0;
};
//=================================================================================================
//									3.2.i2cAvailable(bus)
//=================================================================================================
uint8_t  RT_HW_BASE:: i2cAvailable(uint8_t bus){
//-------------------------------------------------------------------------------------------------	
#if defined(RT_HW_PERMIT_I2C0)
if(bus==0){return Wire.available();};
#endif	
//-------------------------------------------------------------------------------------------------	
#if defined(RT_HW_PERMIT_I2C1)
if(bus==1){return Wire1.available();};
#endif	
//-------------------------------------------------------------------------------------------------	
#if defined(RT_HW_PERMIT_I2C2)
if(bus==2){return Wire2.available();};
#endif
//-------------------------------------------------------------------------------------------------				
if(bus) {return 0;}		//--For blocking warnings from C++;
return 0;}
//=================================================================================================
//									3.2.i2cRead(bus)
//=================================================================================================
uint8_t  RT_HW_BASE:: i2cRead(uint8_t bus){
//-------------------------------------------------------------------------------------------------	
#if defined(RT_HW_PERMIT_I2C0)
if(bus==0){return Wire.read();};
#endif	
//-------------------------------------------------------------------------------------------------	
#if defined(RT_HW_PERMIT_I2C1)
if(bus==1){return Wire1.read();};
#endif	
//-------------------------------------------------------------------------------------------------	
#if defined(RT_HW_PERMIT_I2C2)
if(bus==2){return Wire2.read();};
#endif
//-------------------------------------------------------------------------------------------------				
if(bus) {return 0;}		//--For blocking warnings from C++;
return 0;};
//=================================================================================================
//									3.3.1. i2cWrite(var,bus)
//=================================================================================================
void     RT_HW_BASE:: i2cWrite(uint8_t var, uint8_t bus){
//-------------------------------------------------------------------------------------------------	
#if defined(RT_HW_PERMIT_I2C0)
if(bus==0){Wire.write(var); return;};
#endif	
//-------------------------------------------------------------------------------------------------	
#if defined(RT_HW_PERMIT_I2C1)
if(bus==1){Wire1.write(var); return;};
#endif	
//-------------------------------------------------------------------------------------------------	
#if defined(RT_HW_PERMIT_I2C2)
if(bus==2){Wire2.write(var); return;};
#endif
//-------------------------------------------------------------------------------------------------		
if(bus || var) {return;}		//--For blocking warnings from C++;
};
//=================================================================================================
//									3.3.2. i2cWrite(*arr, qnt, bus)
//=================================================================================================
void     RT_HW_BASE:: i2cWrite(const uint8_t *arr, uint8_t qnt, uint8_t bus){	
 if(qnt>32){qnt=32;} for(uint8_t i=0; i<qnt; i++){i2cWrite(arr[i],bus);}};	
//=================================================================================================
//									3.3.3. i2cWrite(*arr, qnt, bus)
//=================================================================================================
void     RT_HW_BASE:: i2cWrite(const char    *arr, uint8_t qnt, uint8_t bus){	//++++Запись qnt символов------
 if(qnt>32){qnt=32;} for(uint8_t i=0; i<qnt; i++){i2cWrite(arr[i],bus);}};	
//=================================================================================================
//									3.4. i2cRequestFrom(*arr, qnt, bus)
//=================================================================================================
uint8_t  RT_HW_BASE:: i2cRequestFrom(uint8_t qnt,  uint8_t adr, uint8_t bus, uint8_t sendStop){
//-------------------------------------------------------------------------------------------------	
#if defined(RT_HW_PERMIT_I2C0)
if(bus==0){return Wire.requestFrom(adr,qnt,(uint8_t)sendStop);};
#endif	
//-------------------------------------------------------------------------------------------------	
#if defined(RT_HW_PERMIT_I2C1)
if(bus==1){return Wire1.requestFrom(adr,qnt,(uint8_t)sendStop);};
#endif	
//-------------------------------------------------------------------------------------------------	
#if defined(RT_HW_PERMIT_I2C2)
if(bus==2){return Wire2.requestFrom(adr,qnt,(uint8_t)sendStop);};
#endif	
//-------------------------------------------------------------------------------------------------	
if(bus || qnt || adr || sendStop) {return 0;}		//--For blocking warnings from C++;
return 0;}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//										4.INIT bus i2c;
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//						        	4.1 INIT bus i2c as MASTER
//=================================================================================================
uint8_t  RT_HW_BASE:: i2cBegin(uint8_t bus){
//-------------------------------------------------------------------------------------------------
i2cClearCodeErr(bus);								//--Cleaning code error;
if(i2cGetStatus(bus)==1){return 1;} 				//--Exit if bus is already Master;
if(i2cSetBusy(bus)==0)	{return 0;}					//--Bus capture or exit if the bus is busy;
//=================================================================================================
//									4.1.1.STM32
//=================================================================================================
#if defined(RT_HW_CORE_STM32) 
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_I2C0)	
if(bus==0){
Wire.setSDA(i2cGetPinSDA(bus));						//--Setting pins SDA;		
Wire.setSCL(i2cGetPinSCL(bus));						//--Setting pins SCL;		
Wire.begin();										//--Init as Master bus=0;
Wire.setClock(i2cGetSpeed(bus));;					//--Setting speed default;	
i2cSetStatus(1,bus);								//--Setting status=Master;
i2cClearBusy(bus); 									//--Bus release; 
return 1;}											//--Successful Exit bus=0;
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_I2C1)	
if(bus==1){
Wire1.setSDA(i2cGetPinSDA(bus));					//--Setting pins SDA;		
Wire1.setSCL(i2cGetPinSCL(bus));					//--Setting pins SCL;		
Wire1.begin();										//--Init as Master bus=1;
Wire1.setClock(i2cGetSpeed(bus));;					//--Setting speed default;	
i2cSetStatus(1,bus);								//--Setting status=Master;
i2cClearBusy(bus); 									//--Bus release; 
return 1;}											//--Successful Exit bus=1;
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_I2C2)	
if(bus==0){
Wire2.setSDA(i2cGetPinSDA(bus));					//--Setting pins SDA;		
Wire2.setSCL(i2cGetPinSCL(bus));					//--Setting pins SCL;		
Wire2.begin();										//--Init as Master bus=2;
Wire2.setClock(i2cGetSpeed(bus));;					//--Setting speed default;	
i2cSetStatus(1,bus);								//--Setting status=Master;
i2cClearBusy(bus); 									//--Bus release; 
return 1;}											//--Successful Exit bus=2;
#endif
//-------------------------------------------------------------------------------------------------
i2cSetCodeErr(70,bus);								//--Setting error "No bus";
i2cClearBusy(bus); 									//--Bus release;
return 1;											//--Exit by mistake;
#endif
//=================================================================================================
//									4.1.2.RP2040
//=================================================================================================
#if defined(RT_HW_CORE_RP2040) 
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_I2C0)	
if(bus==0){
Wire.setSDA(i2cGetPinSDA(bus));						//--Setting pins SDA;	
Wire.setSCL(i2cGetPinSCL(bus));						//--Setting pins SCL;			
Wire.begin();										//--Init as Master bus=0;
Wire.setClock(i2cGetSpeed(bus));;					//--Setting speed default;	
i2cSetStatus(1,bus);								//--Setting status=Master;
i2cClearBusy(bus);									//--Bus release; 
return 1;}											//--Successful Exit bus=0;
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_I2C1)	
if(bus==1){
Wire1.setSDA(i2cGetPinSDA(bus));					//--Setting pins SDA;		
Wire1.setSCL(i2cGetPinSCL(bus));					//--Setting pins SCL;			
Wire1.begin();										//--Init as Master bus=1;
Wire1.setClock(i2cGetSpeed(bus));;					//--Setting speed default;	
i2cSetStatus(1,bus);								//--Setting status=Master;
i2cClearBusy(bus); 									//--Bus release; 
return 1;}											//--Successful Exit bus=1;
#endif
//-------------------------------------------------------------------------------------------------
i2cSetCodeErr(70,bus);								//--Setting error "No bus";
i2cClearBusy(bus); 									//--Bus release;
return 1;											//--Exit by mistake;
#endif
//=================================================================================================
//									4.1.3.ESP32
//=================================================================================================
#if defined(RT_HW_CORE_ESP32) 
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_I2C0)
if(bus==0){
Wire.setPins(i2cGetPinSDA(bus),i2cGetPinSCL(bus));	//-Setting pins SDA, SCL;
Wire.begin();										//--Init as Master bus=0;	
Wire.setClock(i2cGetSpeed(bus));;					//--Setting speed default;	
Wire.setTimeOut(50); 								//--Setting time limit for one transaction;
i2cSetStatus(1,bus);								//--Setting status=Master;
i2cClearBusy(bus);									//--Bus release;
return 1;}											//--Successful Exit bus=0;
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_I2C1)
if(bus==1){
Wire1.setPins(i2cGetPinSDA(bus),i2cGetPinSCL(bus));//-Setting pins SDA, SCL;
Wire1.begin();									//--Init as Master bus=1;
Wire1.setClock(i2cGetSpeed(bus));;				//--Setting speed default;		
Wire1.setTimeOut(50); 							//--Setting time limit for one transaction;	
i2cSetStatus(1,bus);								//--Setting status=Master;
i2cClearBusy(bus);									//--Bus release;
return 1;}											//--Successful Exit bus=1;
#endif
//-------------------------------------------------------------------------------------------------
i2cSetCodeErr(70,bus);								//--Setting error "No bus";
i2cClearBusy(bus); 									//--Bus release;
return 1;											//--Exit by mistake; 									//--Bus release;
#endif
//=================================================================================================
//									4.1.2.ESP8266
//=================================================================================================
#if defined(RT_HW_CORE_ESP8266)
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_I2C0)	
if(bus==0){
Wire.begin(i2cGetPinSDA(bus),i2cGetPinSCL(bus));	//--Init as Master bus=0 with setting pins SDA, SCL;
Wire.setClock(i2cGetSpeed(bus));;					//--Setting speed default;	
Wire.setClockStretchLimit(260);						//--Setting time limit for one transaction;
i2cSetStatus(1,bus);								//--Setting status=Master;
i2cClearBusy(bus); 									//--Bus release;
return 1;}											//--Successful Exit bus=0;
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_I2C1)	
if(bus==1){
Wire1.begin(i2cGetPinSDA(bus),i2cGetPinSCL(bus));	//--Init as Master bus=0 with setting pins SDA, SCL;
Wire1.setClock(i2cGetSpeed(bus));					//--Setting speed default;	
Wire1.setClockStretchLimit(260);					//--Setting time limit for one transaction;
i2cSetStatus(1,bus);								//--Setting status=Master;
i2cClearBusy(bus); 									//--Bus release;
return 1;}											//--Successful Exit bus=1;
#endif
//-------------------------------------------------------------------------------------------------
i2cSetCodeErr(70,bus);								//--Setting error "No bus";
i2cClearBusy(bus); 									//--Bus release;
return 1;											//--Exit by mistake;
#endif

//=================================================================================================
//									4.1.1.AVR,SAM3X,SAMD21,ANON
//=================================================================================================
#if defined(RT_HW_CORE_AVR) || defined(RT_HW_CORE_SAM3X) || defined(RT_HW_CORE_SAMD21) || defined(RT_HW_CORE_ANON)
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_PERMIT_I2C0)	
if(bus==0){
Wire.begin(); 										//--Init as Master bus=0;
i2cSetStatus(1,bus);								//--Setting status=Master;
i2cClearBusy(bus);									//--Bus release;
return  1;}											//--Successful Exit bus=0;
#endif
//-------------------------------------------------------------------------------------------------
i2cSetCodeErr(70,bus);								//--Setting error "No bus";
i2cClearBusy(bus); 									//--Bus release;
return 1;											//--Exit by mistake;
#endif
//=================================================================================================
//									4.1.6. No CORE									
//=================================================================================================
i2cSetCodeErr(65,bus);								//--Setting codeErr=No CORE;
i2cClearBusy(bus);									//--Bus release; 
return 1;											//--Exit by mistake;
}; 
//=================================================================================================


//#################################################################################################
//
//							 					I2C [.cpp]
//
// codeErr: 0-ok, 1-too much data; 2-Nack to send an address; 3-Nack for data transfer; 4-another error i2c; 
// 5-invalid controller;           6-invalid bus; 7-invalid address(>=254);
// 8-bus not configured as master; 9-another error;
//#################################################################################################
//Wire1 Wire1x;		//--Create an object	