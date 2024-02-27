//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//            					BME280 (Sensor Temperatute, Humidity, Pressure)
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  ecoins (ecoins@mail.ru) 
//  21.05.2023: Begin version
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef RT_HW_BME280_h
#define RT_HW_BME280_h
#define RT_HW_BME280_VER 	10	//--Library version number;
#include "RT_HW_BASE.h"			//--Connecting the base library;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
struct RT_HW_BME280_DEV{
RT_HW_STRUCT_I2C_DEV dvI;			//--Data for i2c;
RT_HW_STRUCT_SPI_DEV dvS;			//--Data for SPI;
RT_HW_STRUCT_SPN_DEV dvN;			//--Data for SPN;
//-------------------------------------------------------------------------------------------------
char     mi='I';					//--0.Mode interface;
uint8_t  custom=0;					//--1.Setting option;	
uint8_t  status=0;					//--2.Status device: =0 no init; =1 Master.MCU->Slave.device; =2 Slave;
uint8_t  link=0;					//--3.Completed transaction flag;
uint8_t  codeErr=0;					//--4.Code error;
//-------------------------------------------------------------------------------------------------
uint8_t  dir;						//--5.Working  dir for direct();
uint8_t  step;						//--6.Working step for add function;
//-------------------------------------------------------------------------------------------------
uint8_t  cnt,cntErr;				//--8.Counters;
uint8_t  err:1,action:1;			//--9.Working flags;
//-------------------------------------------------------------------------------------------------
uint8_t  workDelay=0;				//--10.Working register; 
uint8_t  pointDelay;				//--11.Return point from a function;
uint16_t sizeDelay;					//--12.Size delay;	
uint32_t startDelay;		    	//--13.Working register;
//-------------------------------------------------------------------------------------------------
uint8_t  run=0,runPress,runTemp,runHum;			//--14.Command run;
uint8_t  ok=0, okTemp,  okHum,  okPress;		//--15.Device ok;
uint8_t  fresh,freshTemp,freshHum,freshPress;	//--16.Fresh data;
uint8_t  permitTemp=1,permitHum=1,permitPress=1;//--17.Permit parameteres;
//--------------------------------------------------------------------------------------------------
float    vTemp, vHum, vPress;		//--18.Measured values;		    
//--------------------------------------------------------------------------------------------------
uint8_t  idx,idx1;					//--Index;
uint8_t  bf8;						//--Buffer for reading byte;
uint8_t  arr[10];              		//--Buffer for temporary data storage;
//----Determining the value of the sensor parameters (can be changed by the user)------------------
uint8_t  mode   =0b011;		//--Режимы работы:  =00      sleep->no operation, all registers available, lowest power consumption, selected after startup;
                            //                  =01 & 10 forced mode->performs one measurement, saves the results and returns to sleep mode;
							//				    =11      normal mode-> constant measurement cycle and inactive periods;
uint8_t  t_sb   =0b000;		//--Period between temperature measurements->=000:0.5ms; =001:62.5ms; =010:125ms; =011:250ms; =100:500ms; =101:1000ms; =110:10ms; =111:20ms;
uint8_t  filter	=0b001;		//--Filter coefficient: 
//												=000 =filter disabled;
							//                  =001 =2;
							//                  =010 =4;
							//                  =011 =8;
							//                  =101 =16;							
uint8_t  osrs_t	 =0b001;	//--Temperature data oversampling (averaging) coefficient=16; With the filter enabled, ADC resolution = 20 bits.);
uint8_t  osrs_h	 =0b001;	//--Coefficient of oversampling (averaging) of moisture data =16; ADC resolution=16bit.);
uint8_t  osrs_p	 =0b001;	//--Coefficient of oversampling (averaging) of pressure data =16; With the filter enabled, ADC resolution = 20 bits.);
uint8_t  spi3w_en=0b000;	//--SPI operation mode: =0 - four-wire; \u003d 1 - three-wire;
uint8_t  modeChip=0;		//--Sensor code identified from the device;Идентифицируемый из устройства код сенсора; 
//-------------------------------------------------------------------------------------------------
uint8_t  chipID;			//--Chip ID from the sensor;
int32_t  t_fine;
int32_t  t_fine_adjust=0;
uint8_t  bfVar;				
//----Сoefficientes--------------------------------------------------------------------------------
uint16_t dig_T1; int16_t dig_T2, dig_T3;	
uint8_t  dig_H1; int16_t dig_H2; uint8_t dig_H3; int16_t dig_H4, dig_H5; int8_t dig_H6;
uint16_t dig_P1; int16_t dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;
//-------------------------------------------------------------------------------------------------
int32_t  adc_T, Tv, adc_H, adc_P; 
uint32_t Hv;
int32_t  var1, var2, var3, var4, var5;
int64_t  pVar1,pVar2,pP;
//-------------------------------------------------------------------------------------------------
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=================================================================================================
//                            		CLASS BME280
//=================================================================================================
class RT_HW_BME280{
public:
//=================================================================================================
//									0.2. Setting parameters for SPI.
//=================================================================================================
void setParamS(RT_HW_BME280_DEV &id, uint8_t cs, uint8_t bus=0, uint32_t speed=0){
if(id.custom){return;}
id.mi='S';
id.dvS.cs=cs; 
id.dvS.bus=bus; 
if(speed<1000) {id.dvS.speed=RT_HW_Base.spiGetSpeed(bus);} else {id.dvS.speed=speed;}
id.custom=1;};
//=================================================================================================
//									0.3.Setting parameters for SPN.
//=================================================================================================
void setParamN(RT_HW_BME280_DEV &id,uint8_t sck, uint8_t miso, uint8_t cs, uint8_t speed=0){
if(id.custom){return;}
id.mi='N';
id.dvN.userRX=1; 
id.dvN.userTX=0;
id.dvN.sck=sck; id.dvN.miso=miso; id.dvN.mosi=255; id.dvN.cs=cs; id.dvN.speed=speed; 
id.custom=1;};
//=================================================================================================
//									1. Direct sensor.
//=================================================================================================
void direct(RT_HW_BME280_DEV &id, uint8_t &runPress){
     direct(id, id.runTemp, id.runHum, runPress);}
//-------------------------------------------------------------------------------------------------
void direct(RT_HW_BME280_DEV &id, uint8_t &runTemp, uint8_t &runPress){
     direct(id, runTemp, id.runHum, runPress);}
//-------------------------------------------------------------------------------------------------
void direct(RT_HW_BME280_DEV &id, uint8_t &runTemp, uint8_t &runHum, uint8_t &runPress){
//-------------------------------------------------------------------------------------------------
if(runTemp>0) {                   id.run=1; id.runTemp =1;  runTemp=5;} 
if(runHum>0)  {if(id.permitHum)  {id.run=1; id.runHum=1; 	runPress=5;}}
if(runPress>0){if(id.permitPress){id.run=1; id.runPress=1;	runPress=5;}};
//-------------------------------------------------------------------------------------------------
//									1.0.Setting parameters
//-------------------------------------------------------------------------------------------------
if(id.dir==0) {	
getParamDevice(id);
id.step=id.workDelay=0; id.ok=0; id.fresh=1; id.vTemp=0.1; id.vPress=0.3;
if(id.custom==0){return;} 								id.dir=10;} 
//-------------------------------------------------------------------------------------------------
//									1.10.Calling the init function
//-------------------------------------------------------------------------------------------------
if(id.dir==10){
if(!id.run){return;}
init(id);  
if(id.err){		id.pointDelay=0;	id.sizeDelay=1000; 	id.dir=200;  return;} 
if(!id.action){	id.step=0; 								id.dir=20;}}
//-------------------------------------------------------------------------------------------------
//									1.20.Waiting to run
//-------------------------------------------------------------------------------------------------
if(id.dir==20){
if(!id.run){return;} id.run=0; 							id.dir=30;}
//-------------------------------------------------------------------------------------------------
//									1.30.Calling the process(Temp) function
//-------------------------------------------------------------------------------------------------
if(id.dir==30){if(id.runTemp){id.runTemp=0; id.step=0; id.dir=31;} else {id.dir=40;}}
//-------------------------------------------------------------------------------------------------
if(id.dir==31){
processTemp(id);
if(id.err){		id.pointDelay=0;	id.sizeDelay=1000;	id.dir=200; return;} 
if(!id.action){	id.step=0; 								id.dir=40;  return;}}
//-------------------------------------------------------------------------------------------------
//									1.40.Calling the process(Hum) function
//-------------------------------------------------------------------------------------------------
if(id.dir==40){if(id.runHum && id.okTemp){id.runHum=0;  id.step=0; id.dir=41;} else {id.dir=50;}}
//-------------------------------------------------------------------------------------------------
if(id.dir==41){
processHum(id);
if(id.err){		id.pointDelay=0;	id.sizeDelay=1000;	id.dir=200; return;} 
if(!id.action){	id.step=0; 								id.dir=50;  return;}}
//-------------------------------------------------------------------------------------------------
//									1.40.Calling the process(Press) function
//-------------------------------------------------------------------------------------------------
if(id.dir==50){if(id.runPress && id.okTemp)	{id.runPress=0;id.step=0; id.dir=51;} else {id.dir=60;}}
//-------------------------------------------------------------------------------------------------
if(id.dir==51){
processPress(id);
if(id.err)    {id.dir=200; id.sizeDelay=1000; id.pointDelay=0; return;} 
if(!id.action){id.dir=50;  id.step=0;}}
//-------------------------------------------------------------------------------------------------
if(id.dir==60){	id.dir=90;}
//-------------------------------------------------------------------------------------------------
//									1.90.End device management 
//-------------------------------------------------------------------------------------------------
if(id.dir==90){
id.ok=1;
if(id.okTemp)                  {id.ok=1;} else {id.ok=0;}
if(id.permitHum){  if(id.okHum){id.ok=1;} else {id.ok=0;}}
if(id.permitPress){if(id.okHum){id.ok=1;} else {id.ok=0;}}
if(id.freshTemp || id.freshHum || id.freshPress){id.fresh=1;} else {id.fresh=0;} id.freshTemp=id.freshHum=id.freshPress=0;
id.pointDelay=20; id.sizeDelay=50;id.dir=200; return;}
//-------------------------------------------------------------------------------------------------
//									1.200.Dynamic Delay
//-------------------------------------------------------------------------------------------------
if(id.dir==200){
if(!RT_HW_Base.timeDelay(id.startDelay,id.workDelay,id.sizeDelay)){return;} id.dir=id.pointDelay;}	
//-------------------------------------------------------------------------------------------------
};	//====END direct()=============================================================================

//=================================================================================================
//									2.Device initialization
//=================================================================================================
void init(RT_HW_BME280_DEV &id){
//-------------------------------------------------------------------------------------------------
//									2.0.Setting parameters with continue after 50 ms	
//-------------------------------------------------------------------------------------------------
if(id.step==0){
id.cnt=id.cntErr=id.err=0; id.action=1; 
id.pointDelay=10; id.sizeDelay=50; id.step=200; return;}
//-------------------------------------------------------------------------------------------------
//									2.10.Device initialization	
//-------------------------------------------------------------------------------------------------
if(id.step==10) {	
xxxInitDevice(id);	if(!id.link)	{return;}
if(id.status!=1){id.err=1; id.step=0;return;} 
id.cnt=id.cntErr=0; 
if(id.mi=='I')  {id.step=20;} else {id.step=30;}}	
//-------------------------------------------------------------------------------------------------
//									2.20.Address search		
//-------------------------------------------------------------------------------------------------
if(id.step==20) {
xxxFindAdr(id);   	if(!id.link){return;}	
//-------------------------------------------------------------------------------------------------
if(id.codeErr){
id.cnt=0; id.cntErr++;
if(id.cntErr<=3){id.pointDelay=id.step;	id.sizeDelay=100+(250*id.cntErr); id.step=200; return;}	
if(id.cntErr==3){id.pointDelay=id.step; id.sizeDelay=2000; 				  id.step=200; return;}
				 id.codeErr=id.step;    id.err=1; 						  id.step=0;   return;}
//-------------------------------------------------------------------------------------------------
id.cnt++; id.cntErr=0;	
if(id.cnt<5){   id.pointDelay=id.step; 	id.sizeDelay=50;	id.step=200; return;}				
				id.pointDelay=30;	  	id.sizeDelay=10;	id.step=200; return;}
//-------------------------------------------------------------------------------------------------
//									2.30.Reading chip ID.
//-------------------------------------------------------------------------------------------------
if(id.step==30){
xxxREAD(id,0xD0);	if(checkTransaction(id)){return;} 	//--pointDelay=step; if ok->to continue(step=200) or after 3fd error err=1; step=0);
//-------------------------------------------------------------------------------------------------
id.chipID=id.bf8;											//--Storing chipID;
	 if(id.chipID==0x56) {id.modeChip=1; id.permitHum=0;} 	//--Sensor BMP280;
else if(id.chipID==0x57) {id.modeChip=1; id.permitHum=0;} 	//--Sensor BMP280;
else if(id.chipID==0x58) {id.modeChip=1; id.permitHum=0;} 	//--Sensor BMP280
else if(id.chipID==0x60) {id.modeChip=2;             	} 	//--Sensor BME280
else 	                 {id.modeChip=0; id.codeErr=150; id.err=1; return;}	//--Exit by wrong chip code;;
id.pointDelay=35;	id.sizeDelay=10;  		return;}
//-------------------------------------------------------------------------------------------------
//									2.35. Soft reset device [0xB6->reg=0xE0]	
//-------------------------------------------------------------------------------------------------
if(id.step==35){id.arr[0]=0xE0; id.arr[1]=0xB6; id.step=36;}
//-------------------------------------------------------------------------------------------------
if(id.step==36){
xxxWriteArr(id,2);	if(checkTransaction(id)){return;}
id.pointDelay=40;	id.sizeDelay=10;  		 return;}
//-------------------------------------------------------------------------------------------------
//									2.40.Reading settings for temperature.	
//-------------------------------------------------------------------------------------------------
if(id.step==40){if(id.permitTemp){id.step=41;} else{id.step=50;}}
//-------------------------------------------------------------------------------------------------
if(id.step==41){
xxxREADArr(id,0x88,6);	if(checkTransaction(id)){return;}			
//-------------------------------------------------------------------------------------------------
id.dig_T1 =(id.arr[1]<<8) | id.arr[0];
id.dig_T2 =(id.arr[3]<<8) | id.arr[2];
id.dig_T3 =(id.arr[5]<<8) | id.arr[4];	
id.sizeDelay=10;		id.pointDelay=50;		 return;}; 
//-------------------------------------------------------------------------------------------------
//									2.50.Reading settings for pressure.	
//-------------------------------------------------------------------------------------------------
if(id.step==50){if(id.permitPress){id.step=51;} else{id.step=60;}}
//-------------------------------------------------------------------------------------------------
if(id.step==51){
xxxREADArr(id,0x8E,6);	if(checkTransaction(id)){return;}				
//-------------------------------------------------------------------------------------------------
id.dig_P1 =(id.arr[1]<< 8) | id.arr[0];
id.dig_P2 =(id.arr[3]<< 8) | id.arr[2];
id.dig_P3 =(id.arr[5]<< 8) | id.arr[4];		
id.sizeDelay=10;		id.pointDelay=52;		 return;};
//-------------------------------------------------------------------------------------------------
if(id.step==52){
xxxREADArr(id,0x94,6);	if(checkTransaction(id)){return;}
//-------------------------------------------------------------------------------------------------
id.dig_P4 =(id.arr[1]<< 8) | id.arr[0];
id.dig_P5 =(id.arr[3]<< 8) | id.arr[2];
id.dig_P6 =(id.arr[5]<< 8) | id.arr[4];		
id.sizeDelay=10;  		id.pointDelay=53;		 return;};
//--------------------------------------------------------------------------------------------------
if(id.step==53){
xxxREADArr(id,0x94,6);	if(checkTransaction(id)){return;} 			
//-------------------------------------------------------------------------------------------------
id.dig_P7 =(id.arr[1]<< 8) | id.arr[0];
id.dig_P8 =(id.arr[3]<< 8) | id.arr[2];
id.dig_P9 =(id.arr[5]<< 8) | id.arr[4];		
id.sizeDelay=10; 		id.pointDelay=60; 		 return;};
//-------------------------------------------------------------------------------------------------
//									2.60.Reading settings for humidity.	
//-------------------------------------------------------------------------------------------------
if(id.step==60){if(id.permitPress){id.step=61;} else{id.step=70;}}
//-------------------------------------------------------------------------------------------------
if(id.step==61){
xxxREAD(id,0xA1);	if(checkTransaction(id)){return;} 				
//-------------------------------------------------------------------------------------------------
id.dig_H1=id.bf8;		
id.sizeDelay=10;  		id.pointDelay=62; 		 return;};
//--------------------------------------------------------------------------------------------------
if(id.step==62){
xxxREADArr(id,0xE1,7);	if(checkTransaction(id)){return;}			 
//-------------------------------------------------------------------------------------------------
id.dig_H2 =(id.arr[1]<<8) | id.arr[0];
id.dig_H3 = id.arr[2]<<8;
id.dig_H4 =(id.arr[3]<<4) |(id.arr[4] &0x0F);
id.dig_H5 =(id.arr[5]<<4) |((id.arr[4]>>4) & 0x0F);
id.dig_H6 = id.arr[6];			
id.sizeDelay=10;  		id.pointDelay=70; 		 return;};
//-------------------------------------------------------------------------------------------------
//									2.70.Settings CTRL_HUM.	
//-------------------------------------------------------------------------------------------------
if(id.step==70){id.bf8=id.osrs_h & 0b00000111; id.arr[0]=0xF2; id.arr[1]=id.osrs_h & 0b00000111; id.step=71;}
//-------------------------------------------------------------------------------------------------
if(id.step==71){
xxxWriteArr(id,2);		if(checkTransaction(id)){return;}
id.sizeDelay=10;  		id.pointDelay=75;		 return;};
//-------------------------------------------------------------------------------------------------
//									2.75.Settings CONFIG.	
//-------------------------------------------------------------------------------------------------
if(id.step==75){id.arr[0]=0xF5; id.arr[1]=(id.t_sb   << 5) | (id.filter << 2) | id.spi3w_en; id.step=76;}
//-------------------------------------------------------------------------------------------------
if(id.step==76){
xxxWriteArr(id,2);		if(checkTransaction(id)){return;}							
id.sizeDelay=10; 		id.pointDelay=80;		 return;};
//-------------------------------------------------------------------------------------------------
//									2.80.Settings CTRL_MEAS.	
//-------------------------------------------------------------------------------------------------
if(id.step==80){id.arr[0]=0xF4; id.arr[1]=(id.osrs_t << 5) | (id.osrs_p << 2) | id.mode; id.step=81;}
//-------------------------------------------------------------------------------------------------
if(id.step==81){
xxxWriteArr(id,2);		if(checkTransaction(id)){return;}								
id.sizeDelay=10;  		id.pointDelay=85;		 return;};
//-------------------------------------------------------------------------------------------------
//									2.85.Control reading chip ID	
//-------------------------------------------------------------------------------------------------
if(id.step==85){
xxxREAD(id,0xD0);		if(checkTransaction(id)){return;}	
//-------------------------------------------------------------------------------------------------
if(id.chipID!=id.bf8){id.step=0; id.codeErr=91; id.err=1;  return;}
id.sizeDelay=10;  		id.pointDelay=86; 		 return;};
//-------------------------------------------------------------------------------------------------
if(id.step==86){id.step=90;}
//-------------------------------------------------------------------------------------------------
//									2.90.End device init
//-------------------------------------------------------------------------------------------------
if(id.step==90){
/*
if(!RT_HW_Base.console.ok){return;}	
	Serial.print(F("dig_T1="));  Serial.print(id.dig_T1);
	Serial.print(F(" dig_T2=")); Serial.print(id.dig_T2);
	Serial.print(F(" dig_T3=")); Serial.print(id.dig_T3);
	Serial.println();
	
    Serial.print(F("dig_P1="));  Serial.print(id.dig_P1);
	Serial.print(F(" dig_P2=")); Serial.print(id.dig_P2);
	Serial.print(F(" dig_P3=")); Serial.print(id.dig_P3);
	Serial.print(F(" dig_P4=")); Serial.print(id.dig_P4);
	Serial.print(F(" dig_P5=")); Serial.print(id.dig_P5);
	Serial.print(F(" dig_P6=")); Serial.print(id.dig_P6);
	Serial.println();

    Serial.print(F("dig_H1="));  Serial.print(id.dig_H1);
	Serial.print(F(" dig_H2=")); Serial.print(id.dig_H2);
	Serial.print(F(" dig_H3=")); Serial.print(id.dig_H3);
	Serial.print(F(" dig_H4=")); Serial.print(id.dig_H4);
	Serial.print(F(" dig_H5=")); Serial.print(id.dig_H5);
	Serial.print(F(" dig_H6=")); Serial.print(id.dig_H6);
	Serial.println();
	
	Serial.print(F(" chipID(HEX)=")); Serial.println(id.chipID,HEX);
*/
//-------------------------------
id.err=id.action=id.step=0; return;}
//-------------------------------------------------------------------------------------------------
//									2.200.Dynamic Delay
//-------------------------------------------------------------------------------------------------
if(id.step==200){if(!RT_HW_Base.timeDelay(id.startDelay,id.workDelay,id.sizeDelay)){return;} id.step=id.pointDelay;}
};	//====END init()===============================================================================

//=================================================================================================
//									3.Device Process(Temp)
//=================================================================================================
void processTemp(RT_HW_BME280_DEV &id){
//-------------------------------------------------------------------------------------------------
//									3.0.Setting parameters with continue after 50 ms
//-------------------------------------------------------------------------------------------------
if(id.step==0) {	
id.cnt=id.cntErr=id.err=0; id.action=1; id.pointDelay=10; id.sizeDelay=50; id.step=200; return;}
//-------------------------------------------------------------------------------------------------
//									3.10. Start measurement	
//-------------------------------------------------------------------------------------------------
if(id.step==10){
xxxREADArr(id,0xFA,3);	if(checkTransaction(id)){return;}							
id.pointDelay=20; id.sizeDelay=10; id.cntErr=0;  return;}	
//-------------------------------------------------------------------------------------------------
//									3.20. Control reading chipID & store adc_T 	
//-------------------------------------------------------------------------------------------------
if(id.step==20){
xxxREAD(id,0xD0);	if(checkTransaction(id)){return;}							
if(id.chipID!=id.bf8){id.codeErr=21; id.err=1;  id.step=0;  return;}
//-------------------------------------------------------------------------------------------------
id.adc_T  =(uint32_t)id.arr[0] << 12;
id.adc_T |=(uint32_t)id.arr[1] <<  4;
id.adc_T |=(         id.arr[2] >>  4) & 0x0F;
//-------------------------------------------------------------------------------------------------
id.pointDelay=30;   	id.sizeDelay=10;  		  return;}
//-------------------------------------------------------------------------------------------------
//									3.30. Temperature calculation	
//-------------------------------------------------------------------------------------------------
if(id.step==30){
id.var1 = (int32_t)((id.adc_T / 8) - ((int32_t)id.dig_T1 * 2));
id.var1 = (id.var1 * ((int32_t)id.dig_T2)) / 2048;
id.var2 = (int32_t)((id.adc_T / 16) - ((int32_t)id.dig_T1));
id.var2 = (((id.var2 * id.var2) / 4096) * ((int32_t)id.dig_T3)) / 16384;
id.t_fine = id.var1 + id.var2 + id.t_fine_adjust;
id.Tv = (id.t_fine * 5 + 128) / 256;
id.vTemp=(float)id.Tv / 100;
id.step=40;}
//-------------------------------------------------------------------------------------------------
if(id.step==40){id.step=90;}
//-------------------------------------------------------------------------------------------------
//									3.90.End device process	
//-------------------------------------------------------------------------------------------------
if(id.step==90){id.freshTemp=id.okTemp=1; id.err=id.action=0; id.step=0; return;}
//-------------------------------------------------------------------------------------------------
//									3.200.Dynamic Delay
//-------------------------------------------------------------------------------------------------
if(id.step==200){if(!RT_HW_Base.timeDelay(id.startDelay,id.workDelay,id.sizeDelay)){return;} id.step=id.pointDelay;}
};	//++++END meterTemp()==========================================================================	

//=================================================================================================
//									4.Device Process(Hum)
//=================================================================================================
void processHum(RT_HW_BME280_DEV &id){
//-------------------------------------------------------------------------------------------------
//									4.0.Setting parameters with continue after 50 ms
//-------------------------------------------------------------------------------------------------
if(id.step==0) {	
id.cnt=id.cntErr=id.err=0; id.action=1;
id.pointDelay=10; id.step=200; id.sizeDelay=50;}
//-------------------------------------------------------------------------------------------------
//									4.10. Start measurement	
//-------------------------------------------------------------------------------------------------
if(id.step==10){
xxxREADArr(id,0xFD,2);	if(checkTransaction(id)){return;}						
id.pointDelay=20;   	id.sizeDelay=10; 		 return;}	
//-------------------------------------------------------------------------------------------------
//									4.20. Control reading chipID & store adc_H 	
//-------------------------------------------------------------------------------------------------
if(id.step==20){
xxxREAD(id,0xD0);	if(checkTransaction(id)){return;}						
if(id.chipID!=id.bf8){id.codeErr=21; id.err=1; id.step=0;  return;}
//-------------------------------------------------------------------------------------------------
id.adc_H  =(uint32_t)id.arr[0] << 8;
id.adc_H |=(uint32_t)id.arr[1]; 
if(id.adc_H==0x8000) {id.codeErr=22; id.err=1; id.step=0;  return;}
//-------------------------------------------------------------------------------------------------
id.pointDelay=30;   	id.sizeDelay=10; 		  return;}
//-------------------------------------------------------------------------------------------------
//									4.30. Humidity calculation	
//-------------------------------------------------------------------------------------------------
if(id.step==30){
id.var1 = id.t_fine - ((int32_t)76800);
id.var2 = (int32_t)(id.adc_H * 16384);
id.var3 = (int32_t)(((int32_t)id.dig_H4) * 1048576);
id.var4 = ((int32_t)id.dig_H5) * id.var1;
id.var5 = (((id.var2 - id.var3) - id.var4) + (int32_t)16384) / 32768;
id.var2 = (id.var1 * ((int32_t)id.dig_H6)) / 1024;
id.var3 = (id.var1 * ((int32_t)id.dig_H3)) / 2048;
id.var4 = ((id.var2 * (id.var3 + (int32_t)32768)) / 1024) + (int32_t)2097152;
id.var2 = ((id.var4 * ((int32_t)id.dig_H2)) + 8192) / 16384;
id.var3 = id.var5 * id.var2;
id.var4 = ((id.var3 / 32768) * (id.var3 / 32768)) / 128;
id.var5 = id.var3 - ((id.var4 * ((int32_t)id.dig_H1)) / 16);
id.var5 = (id.var5 < 0 ? 0 : id.var5);
id.var5 = (id.var5 > 419430400 ? 419430400 : id.var5);
id.Hv = (uint32_t)(id.var5 / 4096);
id.vHum=(float)id.Hv / 1024.0;
//-------------------------------------------------------------------------------------------------
id.freshHum=id.okHum=1; id.err=id.action=0; id.step=0; return;}	
//-------------------------------------------------------------------------------------------------
//									4.200.Fixed Delay.
//-------------------------------------------------------------------------------------------------
if(id.step==200){if(!RT_HW_Base.timeDelay(id.startDelay,id.workDelay,id.sizeDelay)){return;} id.step=id.pointDelay;}
};	//++++END meterTemp()==========================================================================	

//=================================================================================================
//									5.Meter sensor Press
//=================================================================================================
void processPress(RT_HW_BME280_DEV &id){
//-------------------------------------------------------------------------------------------------
//									5.0.Setting parameters with continue after 50 ms
//-------------------------------------------------------------------------------------------------
if(id.step==0) {	
id.cnt=id.cntErr=id.err=0; id.action=1; id.pointDelay=10; id.sizeDelay=50; id.step=200; return;}
//-------------------------------------------------------------------------------------------------
//									5.10. Start measurement	
//-------------------------------------------------------------------------------------------------
if(id.step==10){
xxxREADArr(id,0xF7,3);	if(checkTransaction(id)){return;}						
id.pointDelay=20;   	id.sizeDelay=10;  		 return;}	
//-------------------------------------------------------------------------------------------------
//									5.20. Control reading chipID & store adc_P 	
//-------------------------------------------------------------------------------------------------
if(id.step==20){
xxxREAD(id,0xD0);	if(checkTransaction(id)){return;}						
if(id.chipID!=id.bf8){id.codeErr=21; id.err=1; id.step=0;  return;}
//-------------------------------------------------------------------------------------------------
id.adc_P  = (uint32_t)id.arr[0] << 12;
id.adc_P |= (uint32_t)id.arr[1] << 4;
id.adc_P |= (         id.arr[2] >> 4) & 0x0F;
//-------------------------------------------------------------------------------------------------
id.pointDelay=30;   id.sizeDelay=10;  		  	 return;}
//-------------------------------------------------------------------------------------------------
//									5.30. Pressure calculation	
//-------------------------------------------------------------------------------------------------
if(id.step==30){
	id.pVar1 = ((int64_t)id.t_fine) - 128000;
	id.pVar2 =  id.pVar1 *   id.pVar1 * (int64_t)id.dig_P6;
	id.pVar2 =  id.pVar2 + ((id.pVar1 * (int64_t)id.dig_P5)<<17);
	id.pVar2 =  id.pVar2 + (((int64_t)id.dig_P4)<<35);
	id.pVar1 =((id.pVar1 *   id.pVar1 * (int64_t)id.dig_P3)>>8) + ((id.pVar1 * (int64_t)id.dig_P2)<<12);
	id.pVar1 =(((((int64_t)1)<<47)+id.pVar1))*((int64_t)id.dig_P1)>>33;
	if(id.pVar1 == 0){id.codeErr=30; id.err=1;  return;}
	id.pP = 1048576 - id.adc_P;
	id.pP = (((id.pP << 31) - id.pVar2)*3125)/id.pVar1;
	id.pVar1 = (((int64_t)id.dig_P9) * (id.pP >> 13) * (id.pP >> 13)) >> 25;
	id.pVar2 = (((int64_t)id.dig_P8) *  id.pP)>> 19;
	id.pP    = ((id.pP + id.pVar1 + id.pVar2) >> 8) + (((int64_t)id.dig_P7)<<4);
	id.pP    = id.pP >> 8; // /256
	id.vPress= id.pP/100.0;
//-------------------------------------------------------------------------------------------------
id.freshPress=id.okPress=1; id.err=id.action=0; id.step=0; return;}	
//-------------------------------------------------------------------------------------------------
//									5.200.Fixed Delay.
//-------------------------------------------------------------------------------------------------
if(id.step==200){
if(!RT_HW_Base.timeDelay(id.startDelay,id.workDelay,id.sizeDelay)){return;} id.step=id.pointDelay;}
};	//++++END meterPress()==========================================================================	

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//									7.Device Link Functions.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//									7.0.Function error check.
//=================================================================================================
uint8_t checkTransaction(RT_HW_BME280_DEV &id){
if(!id.link) {return 1;}
id.pointDelay=id.step; id.step=200;
if(id.codeErr!=0){id.sizeDelay=40+(10*id.cntErr); id.cntErr++; 
                  if(id.cntErr>3){id.codeErr=id.pointDelay; id.err=1; id.step=0;} 
				  return 1;}
id.cntErr=0; return 0;};
//=================================================================================================
//									7.1.Getting Interface Device Parameters
//=================================================================================================
void getParamDevice(RT_HW_BME280_DEV &id){
if(id.mi=='I'){id.custom=id.dvI.custom; id.codeErr=id.dvI.codeErr; id.status=id.dvI.status; id.link=id.dvI.link; id.bf8=id.dvI.bf8; return;}
if(id.mi=='S'){id.custom=id.dvS.custom; id.codeErr=id.dvS.codeErr; id.status=id.dvS.status; id.link=id.dvS.link; id.bf8=(uint8_t)id.dvS.bf32;return;}
if(id.mi=='N'){id.custom=id.dvN.custom; id.codeErr=id.dvN.codeErr; id.status=id.dvN.status; id.link=id.dvN.link; id.bf8=(uint8_t)id.dvN.bf32;return;}
               id.custom=0;             id.codeErr=0;              id.status=0;             id.link=1;           id.bf8=0;          return;};
//=================================================================================================
//									7.3.Init Device.
//=================================================================================================
void xxxInitDevice(RT_HW_BME280_DEV &id){
if(id.mi=='I'){RT_HW_Base.i2cInitDevice(id.dvI); 			getParamDevice(id); return;}	
if(id.mi=='S'){RT_HW_Base.spiInitDevice(id.dvS); 			getParamDevice(id); return;}	
if(id.mi=='N'){RT_HW_Base.spnInitDevice(id.dvN); 			getParamDevice(id); return;}	
getParamDevice(id);};
//=================================================================================================
//									5.2.Find address Device.
//=================================================================================================
void xxxFindAdr(RT_HW_BME280_DEV &id){
if(id.mi=='I'){RT_HW_Base.i2cFindAdr(id.dvI); 				getParamDevice(id); return;}	
if(id.mi=='S'){id.codeErr=0; id.link=1; id.bf8=0; 								return;}	
if(id.mi=='N'){id.codeErr=0; id.link=1; id.bf8=0; 								return;}
getParamDevice(id);};
//=================================================================================================
//									5.3.Wtite byte to register.
//=================================================================================================
void xxxWriteArr(RT_HW_BME280_DEV &id, uint8_t qnt){	
if(id.mi=='I'){RT_HW_Base.i2cWriteArr(id.dvI,id.arr,qnt); 	getParamDevice(id); return;}
if(id.mi=='S'){RT_HW_Base.spiWriteArr(id.dvS,id.arr,qnt); 	getParamDevice(id); return;}
if(id.mi=='N'){RT_HW_Base.spnWriteArr(id.dvN,id.arr,qnt); 	getParamDevice(id); return;}
getParamDevice(id);};
//=================================================================================================
//									5.4.Read byte from register.
//=================================================================================================
void xxxREAD(RT_HW_BME280_DEV &id, uint8_t reg){
if(id.mi=='I'){RT_HW_Base.i2cREAD(id.dvI,reg); 				getParamDevice(id); return;}		
if(id.mi=='S'){RT_HW_Base.spiREAD(id.dvS,reg); 			 	getParamDevice(id); return;}
if(id.mi=='N'){RT_HW_Base.spnREAD(id.dvN,reg); 			 	getParamDevice(id); return;}
getParamDevice(id);};
//=================================================================================================
//									5.4.Read bytes from register.
//=================================================================================================
void xxxREADArr(RT_HW_BME280_DEV &id, uint8_t reg, uint8_t qnt){	
//-------------------------------------------------------------------------------------------------
if(id.mi=='I'){RT_HW_Base.i2cREADArr(id.dvI,reg,id.arr,qnt);getParamDevice(id); return;}
if(id.mi=='S'){RT_HW_Base.spiREADArr(id.dvS,reg,id.arr,qnt);getParamDevice(id); return;}
if(id.mi=='N'){RT_HW_Base.spnREADArr(id.dvN,reg,id.arr,qnt);getParamDevice(id); return;}
getParamDevice(id);};
//=================================================================================================	
};	//++++END CLASS BME280=========================================================================
extern RT_HW_BME280 RT_HW_bme280;	//--Create an object
#endif
//=================================================================================================	