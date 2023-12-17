//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//            			SENSOR MAX6675
//  ecoins (ecoins@mail.ru) 
//  22.10.2022: Begin version
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//-------------------------------------------------------------------------------------------------
#ifndef RT_HW_MAX6675_h
#define RT_HW_MAX6675_h
#define RT_HW_MAX6675_VER 	10	//--Library version number;
#include "RT_HW_BASE.h"			//--Connecting the base library;
/*
The MAX6675 performs cold-junction compensation and digitizes the signal from a type-K thermocouple.
The data is output in a 12-bit resolution, SPI™-compatible, read-only format.
This converter resolves temperatures to 0.25°C, allows readings as high as +1024°C, 
and exhibits thermocouple accuracy of 8LSBs for temperatures ranging from 0°C to +700°C. 
 
The MAX6675 includes signal-conditioning hardware to convert the thermocouple’s signal into 
a voltage compatible with the input channels of the ADC. 
The T+ and T- inputs connect to internal circuitry that reduces the introduction 
of noise errors from the thermocouple wires.
Before converting the thermoelectric voltages into equivalent temperature values, it is necessary 
to compensate for the difference between the thermocouple cold-junction side (MAX6675 ambient temperature) 
and a 0°C virtual reference. 
For a type-K thermocouple, the voltage changes by 41µV/°C, which approximates the thermocouple 
characteristic with the following linear equation:  VOUT = (41µV / °C) ✕ (TR - TAMB)
*/ 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							1.1.Structute for MAX6675 (SPI)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
struct RT_HW_MAX6675_DEV{ 
RT_HW_STRUCT_SPI_DEV dvS;
RT_HW_STRUCT_SPN_DEV dvN;
//-------------------------------------------------------------------------------------------------
char     mi='x';				//--0.Mode interface;
uint8_t  custom=0;				//--1.Setting option;	
uint8_t  status=0;				//--2.Status device: =0 no init; =1 Master.MCU->Slave.device; =2 Slave;
uint8_t  link=0;				//--3.Completed transaction flag;
uint8_t  codeErr=0;				//--4.Code error;
//--------------------------------------------------------------------------------------------------;
uint8_t  dir;					//--5.Working  dir for direct();
uint8_t  step;					//--6.Working step for add function;
//-------------------------------------------------------------------------------------------------
uint8_t  cnt,cntErr;			//--8.Counters;
uint8_t  err:1,action:1;		//--9.Working flags;
//-------------------------------------------------------------------------------------------------
uint8_t  workDelay=0;			//--10.Working register; 
uint8_t  pointDelay;			//--11.Return point from a function;
uint16_t sizeDelay;				//--12.Size delay;	
uint32_t startDelay;		    //--13.Working register;
//-------------------------------------------------------------------------------------------------
uint8_t  run;					//--14.Command run;
uint8_t  ok;					//--15.Device ok;
uint8_t  fresh;					//--16.Fresh data;
//-------------------------------------------------------------------------------------------------
uint16_t rawData;				//--Register for reading data;
//-------------------------------------------------------------------------------------------------
float    vTemp;					//--Measured values;	    
//-------------------------------------------------------------------------------------------------
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                     			2.Class direct MAX6675 (SPI)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class RT_HW_MAX6675{
public:
//=================================================================================================
//									1.Device management
//=================================================================================================
void direct(RT_HW_MAX6675_DEV &id, uint8_t &run){
//-------------------------------------------------------------------------------------------------
if(run>0){id.run=1; run=5;}
//-------------------------------------------------------------------------------------------------
//									1.0.Setting parameters
//-------------------------------------------------------------------------------------------------
if(id.dir==0) {	
getParamDevice(id);
id.step=id.workDelay=0; id.ok=0; id.fresh=1; id.vTemp=0.1;
if(id.custom==0){return;} 								id.dir=10;} 
//-------------------------------------------------------------------------------------------------
//									1.10.Calling the init function
//-------------------------------------------------------------------------------------------------
if(id.dir==10){
if(!id.run)      				 {return;} 
xxxInitDevice(id);	if(!id.link) {return;}
if(id.status!=1){id.codeErr=10; id.dir=200; id.sizeDelay=500; id.pointDelay=0;  return;}
id.dir=20;}
//-------------------------------------------------------------------------------------------------
//									1.20.Waiting to run
//-------------------------------------------------------------------------------------------------
if(id.dir==20){
if(!id.run) {return;} id.run=0; id.cntErr=id.codeErr=0; id.dir=30;}
//-------------------------------------------------------------------------------------------------
//									1.30.Reading data.
//-------------------------------------------------------------------------------------------------
if(id.dir==30){
xxxRead(id);		if(!id.link) {return;}
id.dir=50; return;}		
//-------------------------------------------------------------------------------------------------
//									1.50. Results processing
//-------------------------------------------------------------------------------------------------
if(id.dir==50){
//-------------------------------------------------------------------------------------------------
if(!id.codeErr) {if(id.rawData==0xffff)   {id.codeErr=71;}}			//--Sensor is not connected;
if(!id.codeErr) {if(id.rawData==0) 	      {id.codeErr=72;}}			//--Incorrect measurement;
if(!id.codeErr) {if(bitRead(id.rawData,2)){id.codeErr=73;}}			//--Thermocouple break;														 
if(id.codeErr){ id.dir=200; id.pointDelay=30;  id.sizeDelay=500+(250*id.cntErr); id.cntErr++; 
				if(id.cntErr>3){id.codeErr=74; id.err=1; id.dir=0;} return;}
//-------------------------------------------------------------------------------------------------
id.vTemp=(float)(id.rawData>>3)*0.25;
//-------------------------------------------------------------------------------------------------
id.dir=90; return;}
//-------------------------------------------------------------------------------------------------
//									4.90. Exit process.	
//-------------------------------------------------------------------------------------------------
if(id.dir==90){id.fresh=id.ok=1; id.dir=20; return;}
//-------------------------------------------------------------------------------------------------
//									4.200.Fixed Delay
//-------------------------------------------------------------------------------------------------
if(id.dir==200){if(!RT_HW_Base.timeDelay(id.startDelay,id.workDelay,id.sizeDelay)){return;} id.dir=id.pointDelay;}
};	//====END meter()===============================================================================


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//									7.Device Link Functions.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//									7.1.Getting Interface Device Parameters
//=================================================================================================
void getParamDevice(RT_HW_MAX6675_DEV &id){
if(id.mi=='S'){id.custom=id.dvS.custom; id.codeErr=id.dvS.codeErr; id.status=id.dvS.status; id.link=id.dvS.link; id.rawData=(uint16_t)id.dvS.bf32; return;}
if(id.mi=='N'){id.custom=id.dvN.custom; id.codeErr=id.dvN.codeErr; id.status=id.dvN.status; id.link=id.dvN.link; id.rawData=(uint16_t)id.dvN.bf32; return;}
               id.custom=0;             id.codeErr=0;              id.status=0;             id.link=1;           id.rawData=0;                     return;};
//=================================================================================================
//									7.4.Init Device.
//=================================================================================================
void xxxInitDevice(RT_HW_MAX6675_DEV &id){
if(id.mi=='S'){RT_HW_Base.spiInitDevice(id.dvS); getParamDevice(id); return;}
if(id.mi=='N'){RT_HW_Base.spnInitDevice(id.dvN); getParamDevice(id); return;}
getParamDevice(id);};
//=================================================================================================
//									7.7.Read from register v16.
//=================================================================================================
void xxxRead(RT_HW_MAX6675_DEV &id){
if(id.mi=='S'){RT_HW_Base.spiRead(id.dvS,2); 	getParamDevice(id); return;}
if(id.mi=='N'){RT_HW_Base.spnRead(id.dvN,2); 	getParamDevice(id); return;}
getParamDevice(id);};
//=================================================================================================
};	//++++END Class MAX6675========================================================================
//=================================================================================================
extern RT_HW_MAX6675 	RT_HW_max6675; 						//--Create an object RT_HW_max6675;
//=================================================================================================
#endif
//=================================================================================================
