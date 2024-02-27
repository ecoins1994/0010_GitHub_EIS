//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//            					BMP180 (Sensor Temperatute, Pressure)
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  ecoins (ecoins@mail.ru) 
//  21.05.2023: Begin version
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef RT_HW_BMP180_h
#define RT_HW_BMP180_h
#define RT_HW_BMP180_VER 	10		//--Library version number;
#include "RT_HW_BASE.h"				//--Connecting the base library;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
struct RT_HW_BMP180_DEV{
RT_HW_STRUCT_I2C_DEV dvI;
//-------------------------------------------------------------------------------------------------
char     mi='I';					//--0.Mode interface;
uint8_t  custom=0;					//--1.Setting option;	
uint8_t  status=0;					//--2.Status device: =0 no init; =1 Master.MCU->Slave.device; =2 Slave;
uint8_t  link=0;					//--3.Completed transaction flag;
uint8_t  codeErr=0;					//--4.Code error;
//--------------------------------------------------------------------------------------------------
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
uint8_t  run=0,runPress,runTemp;	//--14.Command run;
uint8_t  ok=0,okPress,okTemp;		//--15.Device ok;
uint8_t  fresh,freshTemp,freshPress;//--16.Fresh data;
uint8_t  permitTemp=1,permitPress=1;//--17.Permit parameteres;
//--------------------------------------------------------------------------------------------------
float    vTemp, vHum, vPress;		//--18.Measured values;		    
//--------------------------------------------------------------------------------------------------
uint8_t  idx,idx1;					//--Index;
uint8_t  bf8;						//--Buffer for reading byte;
uint8_t  arr[10];              		//--Buffer for temporary data storage;
//-------------------------------------------------------------------------------------------------
uint8_t  OverPress=1;					//--Pressure output rate: 0,1,2,3;
uint8_t  timeMeter;						//--Max time meter;
//-------------------------------------------------------------------------------------------------
uint32_t temp;							//--Working register;
uint8_t  cmd;							//--Working register;
uint8_t  chipID;						//--Chip ID from the sensor;
int16_t  AC1,AC2,AC3,VB1,VB2,MB,MC,MD;	
uint16_t AC4,AC5,AC6; 			
float    c3,c4,b1;				
float    c5,c6,mc,md,x0,x1,x2,y0,y1,y2,p0,p1,p2;
float    tu,a;
float    pu,s,x,y,zu;
//-------------------------------------------------------------------------------------------------
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                            		CLASS BMP180
//=================================================================================================
class RT_HW_BMP180{
public:
//=================================================================================================
//									1.Device management
//=================================================================================================
void direct(RT_HW_BMP180_DEV &id, uint8_t &runPress){
     direct(id, id.runTemp, runPress);}
//-------------------------------------------------------------------------------------------------
void direct(RT_HW_BMP180_DEV &id, uint8_t &runTemp, uint8_t &runPress){
//-------------------------------------------------------------------------------------------------
if(runTemp>0) {                   id.run=1; id.runTemp =1; runTemp=5;} 
if(runPress>0){if(id.permitPress){id.run=1; id.runPress=1; runPress=5;}};
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
if(id.dir==30){if(id.runTemp){id.runTemp=0; id.step=0;  id.dir=31;} else {id.dir=50;}}
//-------------------------------------------------------------------------------------------------
if(id.dir==31){
processTemp(id);	
if(id.err){		id.pointDelay=0;	id.sizeDelay=1000;	id.dir=200; return;} 
if(!id.action){	id.step=0; 								id.dir=50;  return;}}
//-------------------------------------------------------------------------------------------------
//									1.50.Calling the process(Hum) function
//-------------------------------------------------------------------------------------------------
if(id.dir==50){if(id.runPress && id.okTemp)	{id.runPress=0; id.step=0; id.dir=51;} else {id.dir=60;}}
//-------------------------------------------------------------------------------------------------
if(id.dir==51){ 
processPress(id);
if(id.err){		id.pointDelay=0;	id.sizeDelay=1000;	id.dir=200; return;} 
if(!id.action){	id.step=0; 								id.dir=60;  return;}}
//-------------------------------------------------------------------------------------------------
if(id.dir==60){	id.dir=90;}
//-------------------------------------------------------------------------------------------------
//									1.90.End device management 
//-------------------------------------------------------------------------------------------------
if(id.dir==90){
id.ok=1;
if(id.okTemp)                    {id.ok=1;} else {id.ok=0;}
if(id.permitPress){if(id.okPress){id.ok=1;} else {id.ok=0;}}
if(id.freshTemp || id.freshPress){id.fresh=1;} else {id.fresh=0;} id.freshTemp=id.freshPress=0;
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
void init(RT_HW_BMP180_DEV &id){
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
//									3.30.Reading chip ID.
//-------------------------------------------------------------------------------------------------
if(id.step==30){
xxxREAD(id,0xD0);	if(checkTransaction(id)){return;}	//--if link ok:: pointDelay=step; step=200; After 3fd error: err=1; step=0; return;
//-------------------------------------------------------------------------------------------------
id.chipID=id.bf8;
if(id.chipID!=0x55){id.codeErr=id.step; id.err=1; id.step=0; return;}//--Exit by wrong chip code;;
id.pointDelay=40; 	id.sizeDelay=10; 		 return;}	
//-------------------------------------------------------------------------------------------------
//									3.40.Reading settings	
//-------------------------------------------------------------------------------------------------
if(id.step==40){
xxxREADArr(id,0xAA,6);	if(checkTransaction(id)){return;}
//-------------------------------------------------------------------------------------------------
id.AC1=((int16_t)(id.arr[0]<<8)) | id.arr[1];
id.AC2=((int16_t)(id.arr[2]<<8)) | id.arr[3];
id.AC3=((int16_t)(id.arr[4]<<8)) | id.arr[5];	
id.pointDelay=41; 	id.sizeDelay=10; 		 return;}	
//-------------------------------------------------------------------------------------------------
if(id.step==41){
xxxREADArr(id,0xB0,6);	if(checkTransaction(id)){return;}
//-------------------------------------------------------------------------------------------------				
id.AC4=((uint16_t)(id.arr[0]<<8)) | id.arr[1]; 
id.AC5=((uint16_t)(id.arr[2]<<8)) | id.arr[3];
id.AC6=((uint16_t)(id.arr[4]<<8)) | id.arr[5];
id.pointDelay=42; 	id.sizeDelay=10; 		 return;}	 
//-------------------------------------------------------------------------------------------------
if(id.step==42){
xxxREADArr(id,0xB6,10);	if(checkTransaction(id)){return;}
//-------------------------------------------------------------------------------------------------			
id.VB1=((int16_t)(id.arr[0]<<8)) | id.arr[1]; 
id.VB2=((int16_t)(id.arr[2]<<8)) | id.arr[3];
id.MB= ((int16_t)(id.arr[4]<<8)) | id.arr[5]; 
id.MC= ((int16_t)(id.arr[6]<<8)) | id.arr[7];
id.MD= ((int16_t)(id.arr[8]<<8)) | id.arr[9];		
id.pointDelay=50; 	id.sizeDelay=10; 		 return;}	
//-------------------------------------------------------------------------------------------------
//									3.50.Result Calculations
//-------------------------------------------------------------------------------------------------
if(id.step==50){
 id.c3 = 160.0 * pow(2,-15) * id.AC3;       id.c4 = pow(10,-3) * pow(2,-15) * id.AC4;
 id.b1 = pow(160,2) * pow(2,-30) * id.VB1;  id.c5 = (pow(2,-15) / 160) * id.AC5;
//------------------------------------------------------------------------------------------------- 
 id.c6 = id.AC6; id.mc = (pow(2,11) / pow(160,2)) * id.MC;  id.md = id.MD / 160.0;
 id.x0 = id.AC1; id.x1 = 160.0 * pow(2,-13) * id.AC2;       id.x2 = pow(160,2) * pow(2,-25) * id.VB2;
//------------------------------------------------------------------------------------------------- 
 id.y0 = id.c4 * pow(2,15);        id.y1 = id.c4 * id.c3;                   id.y2 = id.c4 * id.b1;
 id.p0 = (3791.0 - 8.0) / 1600.0;  id.p1 = 1.0 - 7357.0 * pow(2,-20); id.p2 = 3038.0 * 100.0 * pow(2,-36);			   
id.step=60;}
//-------------------------------------------------------------------------------------------------
if(id.step==60){id.step=90;}
//-------------------------------------------------------------------------------------------------
//									2.90.End device init
//-------------------------------------------------------------------------------------------------
if(id.step==90){id.err=id.action=id.step=0; return;}	
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//									2.200.Fixed Delay
//-------------------------------------------------------------------------------------------------
if(id.step==200){if(!RT_HW_Base.timeDelay(id.startDelay,id.workDelay,id.sizeDelay)){return;} id.step=id.pointDelay;}
};	//====END init()===============================================================================

//=================================================================================================
//									3.Device Process(Temp)
//=================================================================================================
void processTemp(RT_HW_BMP180_DEV &id){
//-------------------------------------------------------------------------------------------------
//									3.0.Setting parameters with continue after 50 ms
//-------------------------------------------------------------------------------------------------
if(id.step==0) {	
id.cnt=id.cntErr=id.err=0; id.action=1; id.pointDelay=10; id.sizeDelay=50; id.step=200; return;}
//-------------------------------------------------------------------------------------------------
//									3.10. Start measurement	
//-------------------------------------------------------------------------------------------------
if(id.step==10){id.arr[0]=0xF4; id.arr[1]=0x2E; id.timeMeter=5; id.step=11;}
//-------------------------------------------------------------------------------------------------
if(id.step==11) {
xxxWriteArr(id,2);		if(checkTransaction(id)){return;}	//--if link ok:: pointDelay=step; step=200; After 3fd error: err=1; step=0; return;
id.pointDelay=20;    id.sizeDelay=id.timeMeter;  return;} 
//-------------------------------------------------------------------------------------------------
//									3.20. Getting measurement results	
//-------------------------------------------------------------------------------------------------					
if(id.step==20) {
xxxREADArr(id,0xF6,2);	if(checkTransaction(id)){return;}
id.pointDelay=30;		id.sizeDelay=10;		 return;}
//-------------------------------------------------------------------------------------------------
//									3.30.Reading chip ID.
//-------------------------------------------------------------------------------------------------
if(id.step==30){
xxxREAD(id,0xD0);		if(checkTransaction(id)){return;}
//-------------------------------------------------------------------------------------------------												
if(id.chipID!=id.bf8){id.codeErr=id.step; id.err=1; id.step=0; return;}//--Exit by wrong chip code;;
//--------------------------------------------------------------------------------------------------
id.pointDelay=50;		id.sizeDelay=10;  		 return;}
//-------------------------------------------------------------------------------------------------
//									3.50. Results processing
//-------------------------------------------------------------------------------------------------
if(id.step==50){
id.tu = (id.arr[0] * 256.0) + id.arr[1];
//example from http://wmrx00.sourceforge.net/Arduino/BMP085-Calcs.pdf  tu = 0x69EC;
id.a = id.c5 * (id.tu - id.c6);
id.vTemp = id.a + (id.mc / (id.a + id.md));
id.step=60;}
//-------------------------------------------------------------------------------------------------
if(id.step==60){id.step=90;}
//-------------------------------------------------------------------------------------------------
//									3.90.End device process	
//-------------------------------------------------------------------------------------------------
if(id.step==90){id.freshTemp=id.okTemp=1; id.err=id.action=0; id.step=0; return;}
//-------------------------------------------------------------------------------------------------
//									3.200.Dynamic Delay
//-------------------------------------------------------------------------------------------------
if(id.step==200){if(!RT_HW_Base.timeDelay(id.startDelay,id.workDelay,id.sizeDelay)){return;} id.step=id.pointDelay;}
};	//====END meterTemp()===============================================================================

//=================================================================================================
//									4.Device Process(Press)
//=================================================================================================
void processPress(RT_HW_BMP180_DEV &id){
//-------------------------------------------------------------------------------------------------
//									4.0.Setting parameters with continue after 50 ms
//-------------------------------------------------------------------------------------------------
if(id.step==0) {	
id.cnt=id.cntErr=id.err=0; id.action=1; id.pointDelay=10; id.sizeDelay=50; id.step=200; return;}
//-------------------------------------------------------------------------------------------------
//									4.10. Start measurement	
//-------------------------------------------------------------------------------------------------
if(id.step==10){
					id.arr[0]=0xF4;			  			//--REG_CONTROL=0xF4
					id.arr[1]=0x34; id.timeMeter=5; 	//--CMND_PRESS_0=0x34						   
if(id.OverPress==1){id.arr[1]=0x74; id.timeMeter=8;}	//--CMND_PRESS_1=0x74
if(id.OverPress==2){id.arr[1]=0xB4; id.timeMeter=14;}	//--CMND_PRESS_2=0xB4
if(id.OverPress==3){id.arr[1]=0xF4; id.timeMeter=26;}	//--CMND_PRESS_3=0xF4	
id.step=11;}
//-------------------------------------------------------------------------------------------------
if(id.step==11){
xxxWriteArr(id,2);		if(checkTransaction(id)){return;}	//--if link ok:: pointDelay=step; step=200; After 3fd error: err=1; step=0; return;
id.pointDelay=20;   id.sizeDelay=id.timeMeter; 	 return;}
//-------------------------------------------------------------------------------------------------
//									4.20. Getting measurement results	
//-------------------------------------------------------------------------------------------------					
if(id.step==20) {
xxxREADArr(id,0xF6,3);	if(checkTransaction(id)){return;} 
id.pointDelay=50;	id.sizeDelay=10;  			 return;}
//-------------------------------------------------------------------------------------------------
//									4.30.Reading chip ID.
//-------------------------------------------------------------------------------------------------
if(id.step==30){
xxxREAD(id,0xD0);		if(checkTransaction(id)){return;}
//-------------------------------------------------------------------------------------------------												
if(id.chipID!=id.bf8){id.codeErr=id.step; id.err=1; id.step=0; return;}//--Exit by wrong chip code;;
//-------------------------------------------------------------------------------------------------
id.pointDelay=50;	id.sizeDelay=10;  		 	 return;}
//-------------------------------------------------------------------------------------------------
//									4.50. Results processing
//-------------------------------------------------------------------------------------------------
if(id.step==50){
id.pu = (id.arr[0] * 256.0) + id.arr[1] + (id.arr[2]/256.0);
//example from http://wmrx00.sourceforge.net/Arduino/BMP085-Calcs.pdf, pu = 0x982FC0;	
//pu = (0x98 * 256.0) + 0x2F + (0xC0/256.0);		
id.s = id.vTemp - 25.0;
id.x = (id.x2 * pow(id.s,2)) + (id.x1 * id.s) + id.x0;
id.y = (id.y2 * pow(id.s,2)) + (id.y1 * id.s) + id.y0;
id.zu= (id.pu - id.x) / id.y;
id.vPress = (id.p2 * pow(id.zu,2)) + (id.p1 * id.zu) + id.p0;
id.step=60;}
//-------------------------------------------------------------------------------------------------
if(id.step==60){id.step=90;}
//-------------------------------------------------------------------------------------------------
//									4.90.End device process	
//-------------------------------------------------------------------------------------------------
if(id.step==90){id.freshPress=id.okPress=1; id.err=id.action=0; id.step=0; return;}
//-------------------------------------------------------------------------------------------------
//									4.200.Dynamic Delay
//-------------------------------------------------------------------------------------------------
if(id.step==200){if(!RT_HW_Base.timeDelay(id.startDelay,id.workDelay,id.sizeDelay)){return;} id.step=id.pointDelay;}
};	//====END meterPress()===============================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//									7.Device Link Functions.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//									7.0.Function error check.
//=================================================================================================
uint8_t checkTransaction(RT_HW_BMP180_DEV &id){
if(!id.link) {return 1;}
id.pointDelay=id.step; id.step=200;
if(id.codeErr!=0){id.sizeDelay=40+(10*id.cntErr); id.cntErr++; 
                  if(id.cntErr>3){id.codeErr=id.pointDelay; id.err=1; id.step=0;} 
				  return 1;}
id.cntErr=0; return 0;};
//=================================================================================================
//									7.1.Getting Interface Device Parameters
//=================================================================================================
void getParamDevice(RT_HW_BMP180_DEV &id){
if(id.mi=='I'){id.custom=id.dvI.custom; id.codeErr=id.dvI.codeErr; id.status=id.dvI.status; id.link=id.dvI.link; id.bf8=id.dvI.bf8; return;}
               id.custom=0;             id.codeErr=0;              id.status=0;             id.link=1;           id.bf8=0;          return;};
//=================================================================================================
//									7.3.Init Device.
//=================================================================================================
void xxxInitDevice(RT_HW_BMP180_DEV &id){
if(id.mi=='I'){RT_HW_Base.i2cInitDevice(id.dvI); 				getParamDevice(id); return;}		
getParamDevice(id);};
//=================================================================================================
//									7.2.Find address Device.
//=================================================================================================
void xxxFindAdr(RT_HW_BMP180_DEV &id){
if(id.mi=='I'){RT_HW_Base.i2cFindAdr(id.dvI); 					getParamDevice(id); return;}	
getParamDevice(id);};
//=================================================================================================
//									7.4.Wtite byte to register.
//=================================================================================================
void xxxWriteArr(RT_HW_BMP180_DEV &id, uint8_t qnt){	
if(id.mi=='I'){RT_HW_Base.i2cWriteArr(id.dvI,id.arr,qnt); 	 	getParamDevice(id); return;}
getParamDevice(id);};
//=================================================================================================
//									7.5.Read byte from register.
//=================================================================================================
void xxxREAD(RT_HW_BMP180_DEV &id, uint8_t reg){
if(id.mi=='I'){RT_HW_Base.i2cREAD(id.dvI,reg); 			 		getParamDevice(id); return;}		
getParamDevice(id);};
//=================================================================================================
//									7.6.Read bytes from register.
//=================================================================================================
void xxxREADArr(RT_HW_BMP180_DEV &id, uint8_t reg, uint8_t qnt){	
//-------------------------------------------------------------------------------------------------
if(id.mi=='I'){RT_HW_Base.i2cREADArr(id.dvI,reg,id.arr,qnt);	getParamDevice(id); return;}
getParamDevice(id);};
//=================================================================================================
//									7.10.Get byte.
//=================================================================================================
//void xxxGetByte(RT_HW_BMP180_DEV &id){	
//if(id.mi=='I'){RT_HW_Base.i2cGetByte(id.dvI); 					getParamDevice(id); return;};
//getParamDevice(id);};
//=================================================================================================
//									7.11.Get bytes.
//=================================================================================================
//void xxxGetBytes(RT_HW_BMP180_DEV &id, uint8_t qnt){	
//if(id.mi=='I'){RT_HW_Base.i2cGetBytes(id.dvI,id.arr,qnt); 		getParamDevice(id); return;};
//getParamDevice(id);};
//=================================================================================================
//=================================================================================================
//									5.9.Read bytes from register.
//=================================================================================================
void debugCoeff(RT_HW_BMP180_DEV &id){
id.bf8=0;
/*
RT_HW_Base.consoleTest(String(F(" T->AC1")),id.AC1,';');
RT_HW_Base.consoleTest(String(F(" AC2")),id.AC2,';');
RT_HW_Base.consoleTest(String(F(" AC3")),id.AC3,';');
RT_HW_Base.consoleTest(String(F(" AC4")),id.AC4,';');
RT_HW_Base.consoleTest(String(F(" AC5")),id.AC5,';');
RT_HW_Base.consoleTest(String(F(" AC6")),id.AC6,'E');

RT_HW_Base.consoleTest(String(F(" VB1")),id.VB1,';');
RT_HW_Base.consoleTest(String(F(" VB2")),id.VB2,';');
RT_HW_Base.consoleTest(String(F(" MB")),id.MB,';');
RT_HW_Base.consoleTest(String(F(" MC")),id.MC,';');
RT_HW_Base.consoleTest(String(F(" MD")),id.MD,'E');

RT_HW_Base.consoleTest(String(F(" c3")),id.c3,';');
RT_HW_Base.consoleTest(String(F(" c4")),id.c4,';');
RT_HW_Base.consoleTest(String(F(" c5")),id.c5,';');
RT_HW_Base.consoleTest(String(F(" b1")),id.b1,'E');

RT_HW_Base.consoleTest(String(F(" c6")),id.c6,';');
RT_HW_Base.consoleTest(String(F(" mc")),id.mc,';');
RT_HW_Base.consoleTest(String(F(" md")),id.md,';');
RT_HW_Base.consoleTest(String(F(" x0")),id.x0,';');
RT_HW_Base.consoleTest(String(F(" x1")),id.x1,';');
RT_HW_Base.consoleTest(String(F(" x2")),id.x2,'E');

RT_HW_Base.consoleTest(String(F(" y0")),id.y0,';');
RT_HW_Base.consoleTest(String(F(" y1")),id.y1,';');
RT_HW_Base.consoleTest(String(F(" y2")),id.y2,';');
RT_HW_Base.consoleTest(String(F(" p0")),id.p0,';');
RT_HW_Base.consoleTest(String(F(" p1")),id.p1,';');
RT_HW_Base.consoleTest(String(F(" p2")),id.p2,'E');
*/
};
//=================================================================================================
};	//++++END class RT_HW_BMP180===================================================================
extern RT_HW_BMP180 RT_HW_bmp180;	//--Create an object
#endif
//=================================================================================================
