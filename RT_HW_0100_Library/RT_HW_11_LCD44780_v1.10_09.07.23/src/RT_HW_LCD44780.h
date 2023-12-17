//===================================================================================================
// 							   			LCD44780 for real time
// Output to multiple LCDs of type LCD44780 variables String, char, int16_t, float to display.
// Supports i2c(bit4),i2c(bit8),SPI(bit4),SPN(bit3),BUS4(7pins),BUS8(11pins) interfaces;
//---------------------------------------------------------------------------------------------------
//   1.If the length (len) of the displayed message is given, then the output is carried 
//     out within the specified length or until the end of the line.
//   2.If len=0, then the output is carried out to the end of the lines.
//   3.The message can be formatted (alig) within the specified length left ('L'), centered ('C'), right ('R').
//     This adds spaces to the message or cuts it off. 
//   4.If alig='N' (or other distinct character except 'L','C','R'), no formatting is performed. 
//     It should be borne in mind that a shorter message will not overwrite the previous longer message. 
//	 Therefore, it is recommended to explicitly set the formatting type or use the default formatting, 
//	 which in the library is 'L' (left).
//   5.There is a function to output a flickering character to the specified address.
//	 6.	
//
//  Libraries are developed taking into account the peculiarities of use in the FLProg visual programming system.
//-------------------------------------------------------------------------------------------------
//  ecoins@mail.ru 29.09.2019г.
//  update         10.06.2023г.  
//-------------------------------------------------------------------------------------------------
#ifndef RT_HW_LCD44780_h
#define RT_HW_LCD44780_h
#define RT_HW_LCD44780_VER 		 18							//--Library version number;
#include "RT_HW_BASE.h"										//--Connecting the base library;
#include "EXT_010_LCD44780/LCD44780_01_struct_defined.hpp"	//--Struct defined,enum,const in PROGMEM;
//-------------------------------------------------------------------------------------------------
//#define RT_HW_LCD44780_DEBUG
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                     			CONTROL CLASS LCD
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class RT_HW_LCD44780{
public:
//-------1.0.Object creation and constructor-------------------------------------------------------
RT_HW_LCD44780_HIVE 		hive;							//--General data for the work of the library;
RT_HW_LCD44780_DEVICE_ID *ptr[RT_HW_LCD44780_MAX_DEVICE+1];	//--Array of pointers to data objects RT_HW_LCD44780_DEVICE_ID;				
RT_HW_LCD44780_DEVICE_ID zN;								//--Data to copy to non-initialized pointers;
RT_HW_LCD44780(); 											//--Constructor;
#include "EXT_010_LCD44780/LCD44780_10_funcDevice_h.hpp"	//--API finctions direct LCD;
#include "EXT_010_LCD44780/LCD44780_20_funcLcd_h.hpp"		//--API finctions writre to LCD;	
//=================================================================================================
//									1.direct LCD
//=================================================================================================
void direct(RT_HW_LCD44780_DEVICE_ID &id){
generatorDevice(id);
//-------------------------------------------------------------------------------------------------
//									1.0.Waiting custom parameters device
//											(single execution)
//-------------------------------------------------------------------------------------------------
if(id.dir==0) {
clearDeviceID(id);														//--Clearing settings;
id.genState=2; 															//--Stop (reset) clock generators of external blocks;
if(id.custom==0){return;}												//--Waiting custom device;
//-------------------------Selecting a free number (1-15) of the index-----------------------------
if(hive.qnt>15)						  {id.codeErr=30; id.dir=5;return;}//--Exit by exceeding the maximum number of configured devices;
if(hive.qnt>RT_HW_LCD44780_MAX_DEVICE){id.codeErr=31; id.dir=5; return;}//--Exit by exceeding the maximum number of allowed    devices;
id.num=RT_HW_Base.setFistFreeDevice(hive.set,RT_HW_LCD44780_MAX_DEVICE);//--Setting       number  device;
if(id.num==0) 					      {id.codeErr=32; id.dir=5; return;}//--Exit if   all numbers are occupied;							
if(id.num>RT_HW_LCD44780_MAX_DEVICE)  {id.codeErr=33; id.dir=5; return;}//--Exit by exceeding the maximum number of allowed    devices;
hive.qnt++;																//--Increment the number  of busy devices;
ptr[id.num]=&id;														//--Setting pointer ID device; 
//-------------------------------------------------------------------------------------------------
id.chip=1; if((id.cols==40) && (id.rows==4)){id.chip=2;} 				//--Setting the number of chips for LCD (for 40x4=2);
id.dir=200; id.sizeDelay=500; id.pointDelay=10;} 						//--Go to continuation via delay(100ms);
//-------------------------------------------------------------------------------------------------
//									1.10.Begin init device
//-------------------------------------------------------------------------------------------------
if(id.dir==10){
id.genState=2;															//--Stop (reset) clock generators of external blocks;
clearDevice(id);   id.step=0; id.dir=20;}								//--Clearing settings and go to continuation;
//-------------------------------------------------------------------------------------------------
//									1.20.Init device(bus,adr,cs,pins)
//-------------------------------------------------------------------------------------------------
if(id.dir==20){
xxxInitDevice(id);	if(!id.link){return;}								//--Initting device;
if(id.status!=1){id.dir=200; id.pointDelay=10; id.sizeDelay=1000; return;}//--If 
id.cnt=id.cntErr=id.stepInit=0;	
if(id.mi=='I'){id.dir=30;} else {id.dir=50;}
}
//-------------------------------------------------------------------------------------------------
//									1.30.Find address device (for i2c)
//-------------------------------------------------------------------------------------------------
if(id.dir==30) {
xxxFindAdr(id);   	if(!id.link){return;}								//--Find adddress(for i2c)
//-------------------------------------------------------------------------------------------------
if(id.codeErr){
id.cnt=0; id.cntErr++;
if(id.cntErr<=3){id.pointDelay=id.dir; id.dir=200; id.sizeDelay=100+(250*id.cntErr);	return;}	
if(id.cntErr==3){id.pointDelay=id.dir; id.dir=200; id.sizeDelay=2000; 					return;}
				 id.pointDelay=10;     id.dir=200; id.sizeDelay=1000;  			  		return;}
//-------------------------------------------------------------------------------------------------
id.cnt++; id.cntErr=0;	
if(id.cnt<8){    id.pointDelay=id.dir; id.dir=200; id.sizeDelay=20; 					return;}
//-------------------------------------------------------------------------------------------------					
id.dir=50;}
//-------------------------------------------------------------------------------------------------
//									1.50.Init bus LCD
//-------------------------------------------------------------------------------------------------
if(id.dir==50){
initBusLcd(id);
if(id.err)    {id.dir=200; id.sizeDelay=1000; id.pointDelay=10; return;} 
if(!id.action){id.dir=60;}}
//-------------------------------------------------------------------------------------------------
//									1.60.Permit output LCD
//-------------------------------------------------------------------------------------------------
if(id.dir==60){
if(!id.extEN){return;}													//--Waiting for permission from external EN flag;
id.busy=0; id.genState=0;	
id.dir=90;}
//-------------------------------------------------------------------------------------------------
//									1.90.Main control loop
//-------------------------------------------------------------------------------------------------
if(id.dir==90){												
if(id.codeErr) {id.genState=2;  				id.dir=10; return;}	//--;
if(!id.extEN)  {id.genState=2; directClear(id); id.dir=60; return;}	//--Restart when device is turned off(EN=0);
if(id.agoReset!=id.extReset){id.agoReset=id.extReset; 									//--Restart on login reset(event);
             if(id.agoReset){id.genState=2;    	id.dir=10; return;}} 	//                            ....
if(id.runReset){id.genState=2; 				    id.dir=10; return;} 	//--Restart on restart timeout(period=0->restart disabled); 
return;}
//-------------------------------------------------------------------------------------------------
//									1.200.Fixed Delay
//-------------------------------------------------------------------------------------------------
if(id.dir==200){if(!RT_HW_Base.timeDelay(id.startDelay,id.workDelay,id.sizeDelay)){return;} id.dir=id.pointDelay; return;} 
//-------------------------------------------------------------------------------------------------
//									1.210.Stub for error handling when assigning a device number
//-------------------------------------------------------------------------------------------------
if(id.dir==5){return;}
};

//=================================================================================================
//									2.Clearing the lcd control vector (for the iniDeviceID function)
//=================================================================================================
void clearDevice(RT_HW_LCD44780_DEVICE_ID &id){
id.meanderTick =id.meanderSec =id.meanderMin =1;	
id.cntTickSec=id.cntSecMin=id.cntReboot=id.cntWatchDogBusy=0;//--Clearing counters;
id.busy=1; 
id.runReboot=id.readyDevice=id.runReset=id.codeErr=id.cnt=id.cntErr=0;
//-------------------------------------------------------------------------------------------------
id.agoEN=0; id.extEN=1;				//--Flags for parameter EN;
id.extLight=1;						//--Flags for parameter Light;
id.agoClear=id.extClear=0;			//--Flags for parameter Clear;
id.agoReset=id.extReset=0;			//--Flags for parameter Reboot;	
id.buff16=id.index=id.stepInit=0; 	//--Clearing registers;
for(id.arrIdx=0; id.arrIdx < RT_HW_LCD44780_MAX_COLS; id.arrIdx++){id.arrData[id.arrIdx]=RT_HW_LCD44780_CODE_BLANK;} //--Clearing array Data;
id.cnt=id.cntErr=0;
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 									2.Setting PARAM;
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//									2.1.Setting parameters for pins,bus4.
//=================================================================================================
void setParam4(RT_HW_LCD44780_DEVICE_ID &id, uint8_t pRS, uint8_t pE2, uint8_t pE1, uint8_t pD4,  uint8_t pD5, uint8_t pD6, uint8_t pD7){
if(id.custom){return;}
id.mi='4';
id.dvL.pin[0]=pRS; id.dvL.pin[1]=pE2; id.dvL.pin[2]=pE1;
id.dvL.pin[7]=pD4; id.dvL.pin[8]=pD5; id.dvL.pin[9]=pD6; id.dvL.pin[10]=pD7;
id.custom=1;};
//=================================================================================================
//									2.2.Setting parameters for pins,bus8.
//=================================================================================================
void setParam8(RT_HW_LCD44780_DEVICE_ID &id, uint8_t pRS, uint8_t pE2, uint8_t pE1, 
                uint8_t pD0, uint8_t pD1, uint8_t pD2, uint8_t pD3, uint8_t pD4, uint8_t pD5, uint8_t pD6, uint8_t pD7){
if(id.custom){return;}
id.mi='8';
id.dvL.pin[0]=pRS; id.dvL.pin[1]=pE2; id.dvL.pin[2]=pE1;
id.dvL.pin[3]=pD0; id.dvL.pin[4]=pD1; id.dvL.pin[5]=pD2; id.dvL.pin[6]=pD3;
id.dvL.pin[7]=pD4; id.dvL.pin[8]=pD5; id.dvL.pin[9]=pD6; id.dvL.pin[10]=pD7;
id.custom=1;};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//									4.Device INIT Functions.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//				  				 	4.1.Init Bus4
//=================================================================================================
void bs4InitDevice(RT_HW_STRUCT_LCD_DEV &id, uint8_t qntChip=1){
id.link=0;
if(id.custom!=0){return;} 
id.codeErr=0;
if(qntChip==2){id.permitE2=1;} else{id.permitE2=0;}
//-------------------------------------------------------------------------------------------------
                if(!RT_HW_Base.checkPinPGM(RT_HW_PGM_PIN_DOT_ID,id.pin[0])) {id.codeErr=52; id.custom=2; return;}	//--Checking pin number RS;
if(id.permitE2){if(!RT_HW_Base.checkPinPGM(RT_HW_PGM_PIN_DOT_ID,id.pin[1])) {id.codeErr=53; id.custom=3; return;}}	//--Checking pin number E2;  
                if(!RT_HW_Base.checkPinPGM(RT_HW_PGM_PIN_DOT_ID,id.pin[2])) {id.codeErr=54; id.custom=4; return;}	//--Checking pin number E1(E);
for(id.idx=7; id.idx<11; id.idx++){																					//--Checking pin number D4,D5,D6,D7;
                if(!RT_HW_Base.checkPinPGM(RT_HW_PGM_PIN_DOT_ID,id.pin[id.idx])){id.codeErr=59+id.idx; id.custom=9+id.idx; return;}}
//--------------------------------------------------------------------------------------------------
									digitalWrite(id.pin[0],0); 		pinMode(id.pin[0],OUTPUT);		//--Init pin RS;
if(id.permitE2){					digitalWrite(id.pin[1],0); 		pinMode(id.pin[1],OUTPUT);}		//--Init pin E2;	
									digitalWrite(id.pin[2],0); 		pinMode(id.pin[2],OUTPUT);		//--Init pin E1(E);
for(id.idx=7; id.idx<11; id.idx++){ digitalWrite(id.pin[id.idx],0); pinMode(id.pin[id.idx],OUTPUT);}//--Init pin D4,D5,D6,D7;
//-------------------------------------------------------------------------------------------------
if(id.speed>100){id.speed=100;} id.time=10-(id.speed/10);
id.custom=id.status=id.link=1;							//--Setting output parameters;
};
//=================================================================================================
//				  				 	4.2.Init Bus8
//=================================================================================================
void bs8InitDevice(RT_HW_STRUCT_LCD_DEV &id, uint8_t qntChip=1){
id.link=0;
if(id.custom!=0){return;} 
id.codeErr=0;
if(qntChip==2){id.permitE2=1;} else{id.permitE2=0;}
//-------------------------------------------------------------------------------------------------
                if(!RT_HW_Base.checkPinPGM(RT_HW_PGM_PIN_DOT_ID,id.pin[0])) {id.codeErr=52; id.custom=2; return;}	//--Checking pin number RS;
if(id.permitE2){if(!RT_HW_Base.checkPinPGM(RT_HW_PGM_PIN_DOT_ID,id.pin[1])) {id.codeErr=53; id.custom=3; return;}}	//--Checking pin number E2;
                if(!RT_HW_Base.checkPinPGM(RT_HW_PGM_PIN_DOT_ID,id.pin[2])) {id.codeErr=54; id.custom=4; return;}	//--Checking pin number E1(E);
for(id.idx=3; id.idx<11; id.idx++){																					//--Checking pin number D0-D7;
                if(!RT_HW_Base.checkPinPGM(RT_HW_PGM_PIN_DOT_ID,id.pin[id.idx])){id.codeErr=59+id.idx; id.custom=9+id.idx; return;}}
//--------------------------------------------------------------------------------------------------
									digitalWrite(id.pin[0],0); 		pinMode(id.pin[0],OUTPUT);		//--Init pin RS;
if(id.permitE2){					digitalWrite(id.pin[1],0); 		pinMode(id.pin[1],OUTPUT);}		//--Init pin E2;	
									digitalWrite(id.pin[2],0); 		pinMode(id.pin[2],OUTPUT);		//--Init pin E1(E);
for(id.idx=3; id.idx<11; id.idx++){ digitalWrite(id.pin[id.idx],0); pinMode(id.pin[id.idx],OUTPUT);}//--Init pin D0-D7;
//-------------------------------------------------------------------------------------------------
if(id.speed>100){id.speed=100;} id.time=10-(id.speed/10);
id.custom=id.status=id.link=1;							//--Setting output parameters;
};												 											 

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//									5.LCD INIT Functions.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//				  					5.1.Init bus LCD
//=================================================================================================
void initBusLcd(RT_HW_LCD44780_DEVICE_ID &id){
//-------------------------------------------------------------------------------------------------
//									5.1.0.Select depth bit bus
//-------------------------------------------------------------------------------------------------
if(id.stepInit==0){
id.action=1; id.err=0;
id.index=0;     id.stepInit=20;			//--Step to initialize a 4-bit bus;
if(id.mi=='8') {id.stepInit=50;}		//--Step to initialize a 8-bit bus; 
}	
//-------------------------------------------------------------------------------------------------
//									5.1.20. BUS=4, chip number=1;
//-------------------------------------------------------------------------------------------------
if(id.stepInit==20){ 
id.varSend =      pgm_read_byte(RT_HW_LCD44780_INIT_BUS4+(id.index*3));	
id.codeSend=(char)pgm_read_byte(RT_HW_LCD44780_INIT_BUS4+(id.index*3+1));
id.timeSend=      pgm_read_byte(RT_HW_LCD44780_INIT_BUS4+(id.index*3+2))*100;
//#ifdef RT_HW_LCD44780_DEBUG;
//RT_HW_Base.consoleTest(String(F("init bus=4,chip=1 num")),id.num,';'); 
//RT_HW_Base.consoleTest(String(F(" mi")),id.mi,';');
//RT_HW_Base.consoleTest(String(F(" index")),id.index,';');
//RT_HW_Base.consoleTest(String(F(" ")),id.varSend,',','H'); RT_HW_Base.consoleVar(id.codeSend,','); RT_HW_Base.consoleVar(id.timeSend,'E');
//#endif
id.stepInit=21;}
//-------------------------------------------------------------------------------------------------
if(id.stepInit==21){ 
deviceSend(id.num,1,id.varSend,id.codeSend,id.timeSend);			//--Send to chip=1; 					
if(!id.link)             								{return;}	//--Waiting send;
if(id.codeErr){id.err=1; 							 	 return;}	//--Exit by error;
if(++id.index<14) 		  		     	{id.stepInit=20; return;}	//--Serial transmission 13 values; 
//-------------------------------------------------------------------------------------------------
if(id.chip!=2){id.index=0; id.action=0;  id.stepInit=0;  return;}	//--Exit if LCD with one chips;
               id.index=0; 				 id.stepInit=30; return;};	//--Continuation if LCD with two chips;
//-------------------------------------------------------------------------------------------------
//									5.1.30. BUS=4, chip number=1;
//-------------------------------------------------------------------------------------------------
if(id.stepInit==30){	
id.varSend =      pgm_read_byte(RT_HW_LCD44780_INIT_BUS4+(id.index*3));
id.codeSend=(char)pgm_read_byte(RT_HW_LCD44780_INIT_BUS4+(id.index*3+1));
id.timeSend=      pgm_read_byte(RT_HW_LCD44780_INIT_BUS4+(id.index*3+2))*100;
//#ifdef RT_HW_LCD44780_DEBUG
//RT_HW_Base.consoleTest(String(F("init bus=4,chip=2 num")),id.num,';'); RT_HW_Base.consoleTest(String(F(" index")),id.index,';');
//RT_HW_Base.consoleTest(String(F(" ")),id.varSend,',','H'); RT_HW_Base.consoleVar(id.codeSend,','); RT_HW_Base.consoleVar(id.timeSend,'E');
//#endif
id.stepInit=31;}
//-------------------------------------------------------------------------------------------------
if(id.stepInit==31){ 
deviceSend(id.num,2,id.varSend,id.codeSend,id.timeSend);			//--Send to chip=1; 					
if(!id.link)             								{return;}		//--Waiting send;
if(id.codeErr){id.err=1; 							 	 return;}		//--Exit by error;
if(++id.index<14) 						{id.stepInit=30; return;}		//--Serial transmission 13 values; 
//-------------------------------------------------------------------------------------------------
			   id.index=0; id.action=0; id.stepInit=0; 	 return;}		//--Exit if LCD with two chips;
//-------------------------------------------------------------------------------------------------
//									5.1.50. BUS=8, chip number=1;
//-------------------------------------------------------------------------------------------------
if(id.stepInit==50){ 
id.varSend =      pgm_read_byte(RT_HW_LCD44780_INIT_BUS8+(id.index*3));	
id.codeSend=(char)pgm_read_byte(RT_HW_LCD44780_INIT_BUS8+(id.index*3+1));
id.timeSend=      pgm_read_byte(RT_HW_LCD44780_INIT_BUS8+(id.index*3+2))*100;
//#ifdef RT_HW_LCD44780_DEBUG
//RT_HW_Base.consoleTest(String(F("init bus=8,chip=1 num")),id.num,';'); RT_HW_Base.consoleTest(String(F(" index")),id.index,';');
//RT_HW_Base.consoleTest(String(F(" ")),id.varSend,',','H'); RT_HW_Base.consoleVar(id.codeSend,','); RT_HW_Base.consoleVar(id.timeSend,'E');
//#endif
id.stepInit=51;}
//-------------------------------------------------------------------------------------------------
if(id.stepInit==51){ 
deviceSend(id.num,1,id.varSend,id.codeSend,id.timeSend);			//--Send to chip=1; 					
if(!id.link)             								{return;}		//--Waiting send;
if(id.codeErr){id.err=1; 							 	 return;}		//--Exit by error;
if(++id.index<10) 					 	{id.stepInit=20; return;}		//--Serial transmission 13 values; 
//-------------------------------------------------------------------------------------------------
if(id.chip!=2){id.index=0; id.action=0;	 id.stepInit=0;	 return;}		//--Exit if LCD with one chips;
               id.index=0; 				 id.stepInit=60; return;};		//--Continuation if LCD with two chips;
//-------------------------------------------------------------------------------------------------
//									5.1.60. BUS=8, chip number=8;
//-------------------------------------------------------------------------------------------------
if(id.stepInit==60){	
id.varSend =      pgm_read_byte(RT_HW_LCD44780_INIT_BUS8+(id.index*3));	
id.codeSend=(char)pgm_read_byte(RT_HW_LCD44780_INIT_BUS8+(id.index*3+1));
id.timeSend=      pgm_read_byte(RT_HW_LCD44780_INIT_BUS8+(id.index*3+2))*100;
//#ifdef RT_HW_LCD44780_DEBUG
//RT_HW_Base.consoleTest(String(F("init bus=8,chip=2 num")),id.num,';'); RT_HW_Base.consoleTest(String(F(" index")),id.index,';');
//RT_HW_Base.consoleTest(String(F(" ")),id.varSend,',','H'); RT_HW_Base.consoleVar(id.codeSend,','); RT_HW_Base.consoleVar(id.timeSend,'E');
//#endif
id.step=61;}
//-------------------------------------------------------------------------------------------------
if(id.step==61){ 
deviceSend(id.num,2,id.varSend,id.codeSend,id.timeSend);			//--Send to chip=1; 					
if(!id.link)             								{return;}		//--Waiting send;
if(id.codeErr){id.err=1; 							 	 return;}		//--Exit by error;
if(++id.index<10) 					   {id.stepInit=60;  return;}		//--Serial transmission 13 values; 
//-------------------------------------------------------------------------------------------------
			   id.index=0; id.action=0;	id.stepInit=0;   return;}		//--Exit if LCD with two chips;
//-------------------------------------------------------------------------------------------------
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//									6.Device SEND Functions.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//									6.1.Preparing the output variable for sending
//=================================================================================================
void    dvSendPrepare(uint8_t num, uint8_t curChip, uint8_t var, char code){
//-------------------------------------------------------------------------------------------------
ptr[num]->chipSend=curChip;
ptr[num]->varSend=var;
ptr[num]->codeSend=code; 
//-------------------------------------------------------------------------------------------------
if(ptr[num]->codeSend=='D'){ptr[num]->cmdSend=1;} else{ptr[num]->cmdSend=0;}	//--Saving cmd;
//-------------------------------------------------------------------------------------------------
if(ptr[num]->chipSend==1)  {ptr[num]->pinSend=RT_HW_LCD44780_BIT_E;} 	//--E bit number selection for Lcd with single chip;
else 		               {ptr[num]->pinSend=RT_HW_LCD44780_BIT_RW;}	//--E bit number selection for Lcd with two chip;
//------------------------------------------------------------------------------------------------- 
ptr[num]->bffSend=ptr[num]->varSend & 0xf0; 							//--Preparing bits 7-4 for writing to Lcd;	
//-------------------------------------------------------------------------------------------------
if(ptr[num]->codeSend!='T'){
bitWrite(ptr[num]->bffSend,RT_HW_LCD44780_BIT_RS, ptr[num]->cmdSend);	//--Setting bit RS;
bitWrite(ptr[num]->bffSend,RT_HW_LCD44780_BIT_ON, ptr[num]->extLight);	//--Setting bit Led;	
bitSet  (ptr[num]->bffSend,ptr[num]->pinSend);    ptr[num]->arrSend[0]=ptr[num]->bffSend; //--Write a byte with the E=1 for the corresponding chip;
bitClear(ptr[num]->bffSend,ptr[num]->pinSend);    ptr[num]->arrSend[1]=ptr[num]->bffSend;}//--Write a byte with the E=0 for the corresponding chip;
//-------------------------------------------------------------------------------------------------
ptr[num]->bffSend=ptr[num]->varSend << 4;								//--Preparing bits 3-0 for writing to Lcd;		
//--------------------------------------------------------------------------------------------------
bitWrite(ptr[num]->bffSend,RT_HW_LCD44780_BIT_RS, ptr[num]->cmdSend);	//--Setting bit RS;
bitWrite(ptr[num]->bffSend,RT_HW_LCD44780_BIT_ON, ptr[num]->extLight);	//--Setting bit Led;	
bitSet  (ptr[num]->bffSend,ptr[num]->pinSend);    ptr[num]->arrSend[2]=ptr[num]->bffSend; //--Write a byte with the E=1 for the corresponding chip;
bitClear(ptr[num]->bffSend,ptr[num]->pinSend);    ptr[num]->arrSend[3]=ptr[num]->bffSend; //--Write a byte with the E=0 for the corresponding chip;
};
//=================================================================================================
//									6.2.Sending to LCD via interface
//=================================================================================================
//									1.1.Send data/instructions to LCD
// 1.code: =T sending tetrad(4 bit); =I sending instuction(byte); =D sending data(byte);
// 2.time: delay time after sending the command (default=0). Typically >0 when sending instructions; 
//================================================================================================= 
uint8_t deviceSend(uint8_t num, uint8_t curChip, uint8_t var, char code, uint16_t time=0){
if(!checkNum(num)) {ptr[num]->codeErr=0; ptr[num]->link=1; return 1;}
ptr[num]->link=0;
dvSendPrepare(num,curChip,var,code);
//-------------------------------------------------------------------------------------------------
if(ptr[num]->mi=='I') {dvSendi2c (num);}
if(ptr[num]->mi=='i') {dvSendi2c (num);}
if(ptr[num]->mi=='S') {dvSendSPI (num);}
if(ptr[num]->mi=='N') {dvSendSPN (num);}
if(ptr[num]->mi=='4') {dvSendBUS4(num);}
if(ptr[num]->mi=='8') {dvSendBUS8(num);}
if(!ptr[num]->link)   {return 0;}
//-------------------------------------------------------------------------------------------------
if(time>0){delayMicroseconds(time);}
return 1;};
//=================================================================================================
//									6.3.Sending to LCD via i2c
//=================================================================================================
void  dvSendi2c(uint8_t num){
if(ptr[num]->codeSend!='T'){RT_HW_Base.i2cWriteArr(ptr[num]->dvI,&ptr[num]->arrSend[0], 4);}
else                       {RT_HW_Base.i2cWriteArr(ptr[num]->dvI,&ptr[num]->arrSend[2], 2);} 
ptr[num]->codeErr=ptr[num]->dvI.codeErr;           
ptr[num]->link   =ptr[num]->dvI.link;};
//=================================================================================================
//									6.4.Sending to LCD via SPI
//=================================================================================================
void  dvSendSPI(uint8_t num){
if(ptr[num]->codeSend!='T'){RT_HW_Base.spiWrite(ptr[num]->dvS,ptr[num]->arrSend[0],1);
							RT_HW_Base.spiWrite(ptr[num]->dvS,ptr[num]->arrSend[1],1);
							RT_HW_Base.spiWrite(ptr[num]->dvS,ptr[num]->arrSend[2],1);
							RT_HW_Base.spiWrite(ptr[num]->dvS,ptr[num]->arrSend[3],1);}
else                       {RT_HW_Base.spiWrite(ptr[num]->dvS,ptr[num]->arrSend[2],1);
							RT_HW_Base.spiWrite(ptr[num]->dvS,ptr[num]->arrSend[3],1);} 
//-------------------------------------------------------------------------------------------------
ptr[num]->codeErr=ptr[num]->dvS.codeErr; 
ptr[num]->link   =ptr[num]->dvS.link;};
//=================================================================================================
//									6.5.Sending to LCD via SPN
//=================================================================================================
void  dvSendSPN(uint8_t num){
if(ptr[num]->codeSend!='T'){RT_HW_Base.spnWrite(ptr[num]->dvN,ptr[num]->arrSend[0],1);
							RT_HW_Base.spnWrite(ptr[num]->dvN,ptr[num]->arrSend[1],1);
							RT_HW_Base.spnWrite(ptr[num]->dvN,ptr[num]->arrSend[2],1);
							RT_HW_Base.spnWrite(ptr[num]->dvN,ptr[num]->arrSend[3],1);}
else                       {RT_HW_Base.spnWrite(ptr[num]->dvN,ptr[num]->arrSend[2],1);
							RT_HW_Base.spnWrite(ptr[num]->dvN,ptr[num]->arrSend[3],1);} 
//-------------------------------------------------------------------------------------------------
ptr[num]->codeErr=ptr[num]->dvN.codeErr; 
ptr[num]->link   =ptr[num]->dvN.link;};
//=================================================================================================
//									6.6.Sending to LCD via BUS4
//=================================================================================================
void  dvSendBUS4(uint8_t num){ 
if(ptr[num]->chipSend==1){ptr[num]->pinSend=ptr[num]->pin[2];} else {ptr[num]->pinSend=ptr[num]->pin[1];} 
if(ptr[num]->pinSend==255)  {ptr[num]->link=1; return;} 
ptr[num]->cmdSend=0; 
if(ptr[num]->codeSend=='D') {ptr[num]->cmdSend=1;} 
//--------------------------------------------------------------------------------------------------
															  digitalWrite(ptr[num]->pin[0],ptr[num]->cmdSend);	//--Write to pin RS;					
if(ptr[ptr[num]->num]->pin[1]!=255){		       			  digitalWrite(ptr[num]->pin[1],0);}				//--Write to pin E2(RW);
															  digitalWrite(ptr[num]->pin[2],0);					//--Reset pin E1(E);
//--------------------------------------------------------------------------------------------------
if(ptr[num]->codeSend!='T'){for(ptr[num]->idxSend=0; ptr[num]->idxSend<4;  ptr[num]->idxSend++) {digitalWrite(ptr[num]->pin[ptr[num]->idxSend+7],bitRead(ptr[num]->varSend,(ptr[num]->idxSend+4)));//--Write to pin Dx;
															  digitalWrite(ptr[num]->pinSend,1); digitalWrite(ptr[num]->pinSend,0);}}						//--Strob pinEN;
else                       {for(ptr[num]->idxSend=0; ptr[num]->idxSend<4;  ptr[num]->idxSend++) {digitalWrite(ptr[num]->pin[ptr[num]->idxSend],  bitRead(ptr[num]->varSend,(ptr[num]->idxSend)));	//--Write to pin Dx;
															  digitalWrite(ptr[num]->pinSend,1); digitalWrite(ptr[num]->pinSend,0);}}						//--Strob pinEN;											
//-------------------------------------------------------------------------------------------------
ptr[num]->codeErr=ptr[num]->dvL.codeErr; 
ptr[num]->link   =ptr[num]->dvL.link;};
//=================================================================================================
//									6.7.Sending to LCD via BUS8
//=================================================================================================
void  dvSendBUS8(uint8_t num){
if(ptr[num]->chipSend==1)  {ptr[num]->pinSend=ptr[num]->pin[2];} else {ptr[num]->pinSend=ptr[num]->pin[1];} 
if(ptr[num]->pinSend==255) {ptr[num]->codeErr=0; ptr[num]->link=1; return;} 
ptr[num]->cmdSend=0;     if(ptr[num]->codeSend=='D') {ptr[num]->cmdSend=1;} 
//--------------------------------------------------------------------------------------------------
															digitalWrite(ptr[num]->pin[0],ptr[num]->cmdSend);	//--Write to pin RS;					
if(ptr[num]->pin[1]!=255){		               				digitalWrite(ptr[num]->pin[1],0);}					//--Write to pin E2(RW);
															digitalWrite(ptr[num]->pin[2],0);					//--Reset pin E1(E);
//--------------------------------------------------------------------------------------------------
     for(ptr[num]->idx=0; ptr[num]->idx<8; ptr[num]->idx++){digitalWrite(ptr[num]->pin[ptr[num]->idxSend+3],bitRead(ptr[num]->varSend,(ptr[num]->idx))); 	//--Write to pin Dx;
															digitalWrite(ptr[num]->pinSend,1);	 digitalWrite(ptr[num]->pinSend,0);}//--Strob pinEN;											
//-------------------------------------------------------------------------------------------------
ptr[num]->codeErr=ptr[num]->dvL.codeErr; 
ptr[num]->link   =ptr[num]->dvL.link;};
//=================================================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//									7.Device Link Functions.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//									7.1.Getting Interface Device Parameters
//=================================================================================================
void getParamDevice(RT_HW_LCD44780_DEVICE_ID &id){
if(id.mi=='I'){id.custom=id.dvI.custom; id.codeErr=id.dvI.codeErr; id.status=id.dvI.status; id.link=id.dvI.link; return;}
if(id.mi=='i'){id.custom=id.dvI.custom; id.codeErr=id.dvI.codeErr; id.status=id.dvI.status; id.link=id.dvI.link; return;}
if(id.mi=='S'){id.custom=id.dvS.custom; id.codeErr=id.dvS.codeErr; id.status=id.dvS.status; id.link=id.dvS.link; return;}
if(id.mi=='N'){id.custom=id.dvN.custom; id.codeErr=id.dvN.codeErr; id.status=id.dvN.status; id.link=id.dvN.link; return;}
if(id.mi=='4'){id.custom=id.dvL.custom; id.codeErr=id.dvL.codeErr; id.status=id.dvL.status; id.link=id.dvL.link; return;}
if(id.mi=='8'){id.custom=id.dvL.custom; id.codeErr=id.dvL.codeErr; id.status=id.dvL.status; id.link=id.dvL.link; return;}
			   id.custom=0;             id.codeErr=0;              id.status=0;             id.link=1;           return;};
//=================================================================================================
//									7.2.Init Device.
//=================================================================================================
void xxxInitDevice(RT_HW_LCD44780_DEVICE_ID &id){
if(id.mi=='I'){RT_HW_Base.i2cInitDevice(id.dvI); 			getParamDevice(id); return;}
if(id.mi=='i'){RT_HW_Base.i2cInitDevice(id.dvI); 			getParamDevice(id); return;}
if(id.mi=='S'){RT_HW_Base.spiInitDevice(id.dvS); 			getParamDevice(id); return;}
if(id.mi=='N'){RT_HW_Base.spnInitDevice(id.dvN); 			getParamDevice(id); return;}
if(id.mi=='4'){           bs4InitDevice(id.dvL,id.chip);	getParamDevice(id); return;}
if(id.mi=='8'){           bs8InitDevice(id.dvL,id.chip);	getParamDevice(id); return;}
															getParamDevice(id); return;};
//=================================================================================================
//									7.3.Find Addres(for i2c).
//=================================================================================================
void xxxFindAdr(RT_HW_LCD44780_DEVICE_ID &id){
if(id.mi=='I'){RT_HW_Base.i2cFindAdr(id.dvI); 				getParamDevice(id); return;}	
if(id.mi=='i'){RT_HW_Base.i2cFindAdr(id.dvI); 				getParamDevice(id); return;}
if(id.mi=='S'){												id.link=1; 			return;}
if(id.mi=='N'){									 id.cnt=10; id.link=1; 			return;}
if(id.mi=='4'){									 id.cnt=10; id.link=1; 			return;}
if(id.mi=='8'){									 id.cnt=10; id.link=1; 			return;}
												 id.cnt=10; id.link=1; 			return;};
//=================================================================================================
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
};//==============  End of class ==================================================================
extern RT_HW_LCD44780 RT_HW_lcd44780; 						//--Creating an LCD type object
#endif
//=================================================================================================
