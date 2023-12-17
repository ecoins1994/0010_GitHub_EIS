//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//            						MCP23x17
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  ecoins (ecoins@mail.ru) 
//  21.05.2023: Begin version
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//-------------------------------------------------------------------------------------------------
#ifndef RT_HW_MCP23x17_h
#define RT_HW_MCP23x17_h
#define RT_HW_MCP23x17_VER 		 10		//--Library version number;
#include "RT_HW_BASE.h"					//--Connecting the base library;
//-------------------------------------------------------------------------------------------------
#define RT_HW_MCP23x17_DELAY_ERR  50 	//--;
#define RT_HW_MCP23x17_SIZE_BUFF   6	//--Size buffer;
#define RT_HW_MCP23x17_IODIRA	0x00	//--Pin direction register A: =0x00(default) - all output, 0xff - all input;
#define RT_HW_MCP23x17_IODIRB	0x01	//--Pin direction register B: =0x00(default) - all output, 0xff - all input;
#define RT_HW_MCP23x17_IPOLA	0x02	//--Pin inversion register A: =0x00(default) - all direct, 0xff - all inverted;
#define RT_HW_MCP23x17_IPOLB	0x03	//--Pin inversion register B: =0x00(default) - all direct, 0xff - all inverted;
#define RT_HW_MCP23x17_GPPUA	0x0C	//--Register input pull-up register A resistors 100kΩ: =0x00(default) - not pulled up, 0xff - all pulled up;
#define RT_HW_MCP23x17_GPPUB	0x0D	//--Register input pull-up register A resistors 100kΩ: =0x00(default) - not pulled up, 0xff - all pulled up;
#define RT_HW_MCP23x17_GPIOA	0x12	//--Pin output register A;
#define RT_HW_MCP23x17_GPIOB	0x13	//--Pin output register B;
#define RT_HW_MCP23x17_IOCON    0x0A	//--Configuration register;  

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
struct RT_HW_MCP23x17_DEV{
RT_HW_STRUCT_I2C_DEV dvI;
RT_HW_STRUCT_SPI_DEV dvS;
RT_HW_STRUCT_SPN_DEV dvN;
//-------------------------------------------------------------------------------------------------
char     mi='I';				//--0.Mode interface;
uint8_t  custom=0;				//--1.Setting option;	
uint8_t  status=0;				//--2.Status device: =0 no init; =1 Master.MCU->Slave.device; =2 Slave;
uint8_t  link=0;				//--3.Completed transaction flag;
uint8_t  codeErr=0;				//--4.Code error;	
//--------------------------------------------------------------------------------------------------
uint8_t  dir=0;					//--5.Working  dir for direct();
uint8_t  step;					//--6.Working step for add function;
uint8_t  runOut=1,runIn=1;    	//--7.1.Flags to start reading;
uint8_t  invOut=0,invIn=0; 		//--7.2.Flags I/O inversion;
uint8_t  ok;					//--7.3.Device ok;
uint8_t  fresh;					//--7.4.Fresh data;
//-------------------------------------------------------------------------------------------------
uint8_t  cnt,cntErr;			//--8.Counters;
uint8_t  err:1,action:1;		//--9.Working flags;
//-------------------------------------------------------------------------------------------------
uint8_t  workDelay=0;			//--10.Working register; 
uint8_t  pointDelay;			//--11.Return point from a function;
uint16_t sizeDelay;				//--12.Size delay;	
uint32_t startDelay;		   	//--13.Working register;
//-------------------------------------------------------------------------------------------------
uint8_t  permitOutA=0,  permitOutB=0; 	//--Output permission for registers A,B;
uint8_t  permitInA=0,   permitInB=0;	//--Input  permission for registers A,B;
uint8_t  cnfgA=0xFF,    cnfgB=0xFF;		//--Depth bit configuration of registers A,B (0-output, 1-input);
uint8_t  cnfgIPOLA=0x00,cnfgIPOLB=0x00;	//--Depth bit configuration of register  A,B inversion configuration (0-no inversion,1-inversion);
uint8_t  cnfgGPPUA=0xFF,cnfgGPPUB=0xFF;	//--Depth bit configuration of register  A,B pull-ups (0-no pull-up, 1-internal resistor 100k to Vcc);
//-------------------------------------------------------------------------------------------------
uint8_t  inA=0,   inB=0; 		//--Registers for reading from registers A,B;
uint8_t  outA,outB; 			//--Registers for writing to   registers A,B;
uint8_t  extA,extB; 			//--Registers of external values for writing to registers A,B;
uint8_t  inAgoA=255,inAgoB=255; //--Registers of storage of the previous values of output registers A,B;
//-------------------------------------------------------------------------------------------------
uint8_t  bf8;					//--Buffer for reading byte;
uint8_t  arr[8];              	//--Buffer for temporary data storage
//uint8_t  var;
//-------------------------------------------------------------------------------------------------
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                            		CLASS MCP23x17
//=================================================================================================
class RT_HW_MCP23x17{
public:
//=================================================================================================
//									2. Direct device.
//=================================================================================================
void direct(RT_HW_MCP23x17_DEV &id, uint8_t runIn, uint8_t &runOut){
//-------------------------------------------------------------------------------------------------
if(runOut==2){runOut=0; 
              if(id.permitOutA){if(id.outA!=id.extA){id.outA=id.extA; runOut=5; id.runOut=1;}}; 
			  if(id.permitOutB){if(id.outB!=id.extB){id.outB=id.extB; runOut=5; id.runOut=1;}}}; 
if(runOut==1){                      id.outA=id.extA; id.outB=id.extB; runOut=5; id.runOut=1;}  
//-------------------------------------------------------------------------------------------------
if(runIn>0)  {                                       runIn=0;  id.runIn=1;}
//-------------------------------------------------------------------------------------------------
//									2.0. Initting parameters. Continue after 50 ms.
//--Register bit direction: =1-input, =0-output;
//--Input modes:=0 invert & pull up to Vcc; =1 invert; =2 - pull-up to Vcc; =3-as is;
//-------------------------------------------------------------------------------------------------
if(id.dir==0) {	
getParamDevice(id);
id.step=id.workDelay=0; id.ok=0;  
//-------------------------------------------------------------------------------------------------
id.permitInA=id.permitInB=id.permitOutA=id.permitOutB=0;
if(id.cnfgA!=0){id.permitInA=1;} if(id.cnfgA!=0xFF){id.permitOutA=1;} //--Depth bit configuration of registers A (0-output, 1-input);
if(id.cnfgB!=0){id.permitInB=1;} if(id.cnfgB!=0xFF){id.permitOutB=1;} //--Depth bit configuration of registers B (0-output, 1-input); 
//-------------------------------------------------------------------------------------------------
if(id.custom==0){return;} 								id.dir=10;} 
//-------------------------------------------------------------------------------------------------
//									2.10.Waiting run before init()
//-------------------------------------------------------------------------------------------------
if(id.dir==10){
if(id.runOut || id.runIn){
	id.step=0; id.dir=20;} else {return;}} 
//-------------------------------------------------------------------------------------------------
//									2.20.Init device.
//-------------------------------------------------------------------------------------------------
if(id.dir==20){
init(id);  
if(id.err)    {id.dir=200; id.sizeDelay=1000; id.pointDelay=0; return;} 
if(!id.action){id.dir=30;  id.step=0;}}
//-------------------------------------------------------------------------------------------------
//									2.30.Waiting run after init()
//-------------------------------------------------------------------------------------------------
if(id.dir==30){
if(id.runOut || id.runIn){
	id.step=0; id.dir=40;} else {return;}} 
//-------------------------------------------------------------------------------------------------
//									2.40.Process Output.
//-------------------------------------------------------------------------------------------------
if(id.dir==40){
if(id.runOut)				{id.runOut=0; id.step=0; id.dir=41;} else {id.dir=50;}}
//-------------------------------------------------------------------------------------------------
if(id.dir==41){
outputAB(id);
//RT_HW_Base.consoleTest("***dir.31.1.MCP23x17 err",id.err,';');
//RT_HW_Base.consoleTest(" codeErr",id.codeErr);
if(id.err)    {id.dir=200; id.sizeDelay=1000; id.pointDelay=0; return;} 
if(!id.action){id.dir=50;  id.step=0;}}
//-------------------------------------------------------------------------------------------------
//									2.40.Process Intput.
//-------------------------------------------------------------------------------------------------
if(id.dir==50){
if(id.runIn)					{id.runIn=0;  id.step=0; id.dir=51;} else {id.dir=90;}}
//-------------------------------------------------------------------------------------------------
if(id.dir==51){
inputAB(id);
if(id.err)    {id.dir=200; id.sizeDelay=1000; id.pointDelay=0; return;} 
if(!id.action){id.dir=90;  id.step=0;}}
//-------------------------------------------------------------------------------------------------
//									2.90.Successful exit
//-------------------------------------------------------------------------------------------------
if(id.dir==90){
id.runOut=id.runIn=0;
//RT_HW_Base.consoleTest("***dir.90.MCP23x17 err",id.err,';');
//RT_HW_Base.consoleTest(" codeErr",id.codeErr);
id.ok=1;
id.dir=30; return;}
//-------------------------------------------------------------------------------------------------
//									2.200.Fixed Delay.
//-------------------------------------------------------------------------------------------------
if(id.dir==200){
if(!RT_HW_Base.timeDelay(id.startDelay,id.workDelay,id.sizeDelay)){return;} id.dir=id.pointDelay;}	
//-------------------------------------------------------------------------------------------------
};	
//=================================================================================================
//									3.Init device
//=================================================================================================
void init(RT_HW_MCP23x17_DEV &id){
if(id.step==0) {	
id.cnt=id.cntErr=id.err=0; id.action=1; 
id.pointDelay=10; id.sizeDelay=50; id.step=200; return;}
//-------------------------------------------------------------------------------------------------
//									3.10. Initting device.	
//-------------------------------------------------------------------------------------------------
if(id.step==10) {	
xxxInitDevice(id);	if(!id.link)	{return;}
if(id.status!=1){id.err=1; id.step=0;return;} 
id.cnt=id.cntErr=0; 
if(id.mi=='I')  {id.step=20;} else {id.step=30;}}
//-------------------------------------------------------------------------------------------------
//									3.20. Finding address device		
//-------------------------------------------------------------------------------------------------
if(id.step==20){
xxxFindAdr(id);   	if(!id.link){return;}	
//-------------------------------------------------------------------------------------------------
if(id.codeErr){
id.cnt=0; id.cntErr++;
if(id.cntErr<=3){id.pointDelay=id.step; id.step=200; id.sizeDelay=100+(250*id.cntErr);	return;}	
if(id.cntErr==3){id.pointDelay=id.step; id.step=200; id.sizeDelay=2000; 				return;}
				 id.codeErr=id.step;    id.step=0; 	 id.err=1; 			  		  	  	return;}
//-------------------------------------------------------------------------------------------------
id.cnt++; id.cntErr=0;	
if(id.cnt<3){    id.pointDelay=id.step; id.step=200; id.sizeDelay=40; 					return;}
//-------------------------------------------------------------------------------------------------					
				 id.pointDelay=30;      id.step=200; id.sizeDelay=10;  					return;}
//-------------------------------------------------------------------------------------------------
//									3.30. Setting I/O;		
//-------------------------------------------------------------------------------------------------
if(id.step==30){id.step=31;
id.arr[0]=RT_HW_MCP23x17_IODIRA; id.arr[1]=id.cnfgA; id.arr[2]=id.cnfgB; id.arr[3]=id.cnfgIPOLA; id.arr[4]=id.cnfgIPOLB;}
//-------------------------------------------------------------------------------------------------
if(id.step==31){
xxxWrireArr(id,5);		if(checkTransaction(id)){return;}  	//--Exit to continue or to End+err (step=200);
id.sizeDelay=10;   		id.pointDelay=40;		 return;}
//-------------------------------------------------------------------------------------------------
//									3.40. Setting I/O;		
//-------------------------------------------------------------------------------------------------
if(id.step==40){id.step=41; 
id.arr[0]=RT_HW_MCP23x17_GPPUA; id.arr[1]=id.cnfgGPPUA; id.arr[2]=id.cnfgGPPUB;}
//-------------------------------------------------------------------------------------------------
if(id.step==41){
xxxWrireArr(id,3);		if(checkTransaction(id)){return;}  	//--Exit to continue or to End+err (step=200);
id.sizeDelay=10;   		id.pointDelay=90;		 return;}
//-------------------------------------------------------------------------------------------------
//									3.90. Exit		
//-------------------------------------------------------------------------------------------------
if(id.step==90){
id.action=0; id.step=0; return;}
//-------------------------------------------------------------------------------------------------
//									3.200.Fixed Delay
//-------------------------------------------------------------------------------------------------
if(id.step==200){if(!RT_HW_Base.timeDelay(id.startDelay,id.workDelay,id.sizeDelay)){return;} id.step=id.pointDelay;}
//-------------------------------------------------------------------------------------------------
};
//=================================================================================================
//									4. Reading input A,B
//=================================================================================================
void inputAB(RT_HW_MCP23x17_DEV &id){
//-------------------------------------------------------------------------------------------------
//									4.0. Initting parameters.
//-------------------------------------------------------------------------------------------------
if(id.step==0) {	
id.cnt=id.cntErr=id.err=0; id.action=1;
id.step=10;}
//-------------------------------------------------------------------------------------------------
//									4.10.Select mode input
//-------------------------------------------------------------------------------------------------
if(id.step==10){				   id.step=90;
if( id.permitInA &&  id.permitInB){id.step=20;}	//--Input A & B;
if( id.permitInA && !id.permitInB){id.step=30;}	//--Input A;
if(!id.permitInA &&  id.permitInB){id.step=40;}	//--Input B;              	   
}
//-------------------------------------------------------------------------------------------------
//									4.20.Read A,B
//-------------------------------------------------------------------------------------------------
if(id.step==20){
xxxREADArr(id, RT_HW_MCP23x17_GPIOA,2);	if(checkTransaction(id)){return;}							
id.inA=id.arr[0]; if(id.invIn){id.inA=id.inA^0xFF;}
id.inB=id.arr[1]; if(id.invIn){id.inB=id.inB^0xFF;}

id.step=90;}
//-------------------------------------------------------------------------------------------------
//									4.30.Read A
//-------------------------------------------------------------------------------------------------
if(id.step==30){
xxxREADArr(id, RT_HW_MCP23x17_GPIOA,1);	if(checkTransaction(id)){return;}							
id.inA=id.arr[0]; if(id.invIn){id.inA=id.inA^0xFF;}
id.step=90;}
//-------------------------------------------------------------------------------------------------
//									4.40.Read B
//-------------------------------------------------------------------------------------------------
if(id.step==40){
xxxREADArr(id, RT_HW_MCP23x17_GPIOB,1);	if(checkTransaction(id)){return;}							
id.inB=id.arr[0]; if(id.invIn){id.inB=id.inB^0xFF;}
id.step=90;}
//-------------------------------------------------------------------------------------------------
//									4.90.Successful exit
//-------------------------------------------------------------------------------------------------
if(id.step==90){
if(id.inAgoA!=id.inA){id.inAgoA=id.inA; id.fresh=1;}
if(id.inAgoB!=id.inB){id.inAgoB=id.inB; id.fresh=1;}
id.err=id.action=0; id.step=0; return;}	
//-------------------------------------------------------------------------------------------------
//									4.200.Fixed Delay.
//-------------------------------------------------------------------------------------------------
if(id.step==200){
if(!RT_HW_Base.timeDelay(id.startDelay,id.workDelay,id.sizeDelay)){return;} id.step=id.pointDelay;}
};
//=================================================================================================
//									5. Output A,B
//=================================================================================================
void outputAB(RT_HW_MCP23x17_DEV &id){
//-------------------------------------------------------------------------------------------------
//									5.0. Initting parameters.
//-------------------------------------------------------------------------------------------------
if(id.step==0) {	
id.cnt=id.cntErr=id.err=0; id.action=1;
id.step=10;}
//-------------------------------------------------------------------------------------------------
//									5.10.Select mode output
//-------------------------------------------------------------------------------------------------
if(id.step==10){				   id.step=90;
if( id.permitOutA &&  id.permitOutB){id.step=20;}	//--Output A & B;
if( id.permitOutA && !id.permitOutB){id.step=30;}	//--Output A;
if(!id.permitOutA &&  id.permitOutB){id.step=40;}	//--Output B;              	   
}
//-------------------------------------------------------------------------------------------------
//									5.20.Output A,B
//-------------------------------------------------------------------------------------------------
if(id.step==20){id.step=21;
id.arr[0]=RT_HW_MCP23x17_GPIOA; 
id.arr[1]=id.outA; if(id.invOut){id.arr[1]=id.arr[1]^0xFF;}
id.arr[2]=id.outB; if(id.invOut){id.arr[2]=id.arr[2]^0xFF;}
}
//-------------------------------------------------------------------------------------------------
if(id.step==21){
xxxWrireArr(id,3);	if(checkTransaction(id)){return;}							
id.step=90;}
//-------------------------------------------------------------------------------------------------
//									5.30.Output A
//-------------------------------------------------------------------------------------------------
if(id.step==30){id.step=21;
id.arr[0]=RT_HW_MCP23x17_GPIOA; 
id.arr[1]=id.outA; if(id.invOut){id.arr[1]=id.arr[1]^0xFF;}
}
//-------------------------------------------------------------------------------------------------
if(id.step==31){
xxxWrireArr(id,2);	if(checkTransaction(id)){return;}							
id.step=90;}
//-------------------------------------------------------------------------------------------------
//									5.40.Output B
//-------------------------------------------------------------------------------------------------
if(id.step==40){id.step=21;
id.arr[0]=RT_HW_MCP23x17_GPIOB; 
id.arr[1]=id.outB; if(id.invOut){id.arr[1]=id.arr[1]^0xFF;}
}
//-------------------------------------------------------------------------------------------------
if(id.step==41){
xxxWrireArr(id,2);	if(checkTransaction(id)){return;}							
id.step=90;}
//-------------------------------------------------------------------------------------------------
//									5.90.Successful exit
//-------------------------------------------------------------------------------------------------
if(id.step==90){
id.err=id.action=0; id.step=0; return;}	
//-------------------------------------------------------------------------------------------------
//									5.200.Fixed Delay.
//-------------------------------------------------------------------------------------------------
if(id.step==200){
if(!RT_HW_Base.timeDelay(id.startDelay,id.workDelay,id.sizeDelay)){return;} id.step=id.pointDelay;}
};
//=================================================================================================
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//									7.Device Link Functions.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//									7.0.Function error check.
//=================================================================================================
uint8_t checkTransaction(RT_HW_MCP23x17_DEV &id){
if(!id.link) {return 1;}
id.pointDelay=id.step; id.step=200;
if(id.codeErr!=0){id.sizeDelay=40+(10*id.cntErr); id.cntErr++; 
                  if(id.cntErr>3){id.codeErr=id.pointDelay; id.err=1; id.step=0;} 
				  return 1;}
id.cntErr=0; return 0;};
//=================================================================================================
//									7.1.Getting Interface Device Parameters
//=================================================================================================
void getParamDevice(RT_HW_MCP23x17_DEV &id){
if(id.mi=='I'){id.custom=id.dvI.custom; id.codeErr=id.dvI.codeErr; id.status=id.dvI.status; id.link=id.dvI.link; id.bf8=id.dvI.bf8;          return;}
if(id.mi=='S'){id.custom=id.dvS.custom; id.codeErr=id.dvS.codeErr; id.status=id.dvS.status; id.link=id.dvS.link; id.bf8=(uint8_t)id.dvS.bf32;return;}
if(id.mi=='N'){id.custom=id.dvN.custom; id.codeErr=id.dvN.codeErr; id.status=id.dvN.status; id.link=id.dvN.link; id.bf8=(uint8_t)id.dvN.bf32;return;}
			   id.custom=0;             id.codeErr=0;              id.status=0;             id.link=1;           id.bf8=0;                   return;};
//=================================================================================================
//									7.3.Init Device.
//=================================================================================================
void xxxInitDevice(RT_HW_MCP23x17_DEV &id){
if(id.mi=='I'){RT_HW_Base.i2cInitDevice(id.dvI); 			getParamDevice(id); return;}	
if(id.mi=='S'){RT_HW_Base.spiInitDevice(id.dvS); 			getParamDevice(id); 
RT_HW_Base.consoleTest(String("MCP23x17 Init SPI cs"),id.dvS.cs,';','P');
RT_HW_Base.consoleTest(String(" custom"),id.dvS.custom,';');
RT_HW_Base.consoleTest(String(" status"),id.dvS.status,';');
RT_HW_Base.consoleTest(String(" link"),id.dvS.link,'E');
return;}	
if(id.mi=='N'){RT_HW_Base.spnInitDevice(id.dvN); 			getParamDevice(id); return;}	
getParamDevice(id);};
//=================================================================================================
//									7.4.Find address Device.
//=================================================================================================
void xxxFindAdr(RT_HW_MCP23x17_DEV &id){
if(id.mi=='I'){RT_HW_Base.i2cFindAdr(id.dvI); 				getParamDevice(id); return;}	
if(id.mi=='S'){id.codeErr=0; id.status=0; id.link=1; id.bf8=0; 					return;}	
if(id.mi=='N'){id.codeErr=0; id.status=0; id.link=1; id.bf8=0;					return;}
getParamDevice(id);};
//=================================================================================================
//									7.5.Wtite byte to register.
//=================================================================================================
void xxxWrireArr(RT_HW_MCP23x17_DEV &id, uint8_t qnt){	
if(id.mi=='I'){RT_HW_Base.i2cWriteArr(id.dvI,id.arr,qnt); 	getParamDevice(id); return;}
if(id.mi=='S'){RT_HW_Base.spiWriteArr(id.dvS,id.arr,qnt); 	getParamDevice(id); return;}
if(id.mi=='N'){RT_HW_Base.spnWriteArr(id.dvN,id.arr,qnt); 	getParamDevice(id); return;}
getParamDevice(id);};
//=================================================================================================
//									7.6.Read byte from register.
//=================================================================================================
void xxxREAD(RT_HW_MCP23x17_DEV &id, uint8_t reg){
if(id.mi=='I'){RT_HW_Base.i2cREAD(id.dvI,reg); 				getParamDevice(id); return;}		
if(id.mi=='S'){RT_HW_Base.spiREAD(id.dvS,reg); 				getParamDevice(id); return;}
if(id.mi=='N'){RT_HW_Base.spnREAD(id.dvN,reg); 				getParamDevice(id); return;}
getParamDevice(id);};
//=================================================================================================
//									7.7.Read bytes from register.
//=================================================================================================
void xxxREADArr(RT_HW_MCP23x17_DEV &id, uint8_t reg, uint8_t qnt){	
if(id.mi=='I'){RT_HW_Base.i2cREADArr(id.dvI,reg,id.arr,qnt); getParamDevice(id); return;}
if(id.mi=='S'){RT_HW_Base.spiREADArr(id.dvS,reg,id.arr,qnt); getParamDevice(id); return;}
if(id.mi=='N'){RT_HW_Base.spnREADArr(id.dvN,reg,id.arr,qnt); getParamDevice(id); return;}
getParamDevice(id);};
//=================================================================================================	
//=================================================================================================
};		//++++END CLASS RT_HW_MCP23x17()
//=================================================================================================
extern RT_HW_MCP23x17 	RT_HW_mcp23x17; 						//--Create an object RT_HW_mcp23x17; 						
#endif
//=================================================================================================
