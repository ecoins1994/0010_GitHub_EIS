//=================================================================================================
//									1.Сlock generator
// output: run =0-wait; =1-output; =2-output for change; =3-clear;
//uint8_t getGenState(uint8_t num){
//if(!checkNum(num)){return 4;} 
//else              {return ptr[num]->genState;}};
//=================================================================================================
void LcdGenerator (RT_HW_LCD44780_PARAM_ID &id){
id.run=0;
if(!checkNum(id.num)){id.extGen=4;}							//--Checking if the device number is valid;
else                 {id.extGen=ptr[id.num]->genState;}		//--Getting the value from the main extention generator;
//-------------------------------------------------------------------------------------------------
if(id.agoGen==id.extGen){return;}							//--Exit if there are no generator changes;
id.agoGen=id.extGen;										//--Fixing the value of the generator;		
if(id.agoGen>=2){id.agoBit=id.first=0; id.cntEN=id.cntLimit=id.cntTask=0; id.agoEN=id.extEN;}
//-------------------------------------------------------------------------------------------------
//									1.2.Handler for EN=1
//-------------------------------------------------------------------------------------------------
if( id.extEN){
 if(id.agoEN!=id.extEN){id.agoEN=id.extEN; id.first=0; id.cntEN=0;} //--Fixing the change with resetting the delay counter;
 if(id.first==0){if(++id.cntEN>5){id.first=1; id.run=1;}  return;}}	//--Delay after EN=1, in order to resolve conflict with another pin;
//-------------------------------------------------------------------------------------------------
//									1.3.Handler for EN=0
//-------------------------------------------------------------------------------------------------
if(!id.extEN){
 if(id.agoEN!=id.extEN){id.agoEN=id.extEN;    id.run=3; return;}}	//--Unconditional start of field clearing;
//-------------------------------------------------------------------------------------------------
//									1.3.1.Field flicker
//------------------------------------------------------------------------------------------------- 
if(id.modeBlink==0){id.cntBlink=0; id.blink=0;}
if(id.modeBlink==1){++id.cntBlink; 
    if(id.cntBlink>=id.periodBlink){	
	id.cntBlink=0; id.blink=!id.blink; if(id.blink){id.run=3;} else{id.run=1;}} return;}
//-------------------------------------------------------------------------------------------------
//									1.3.2.Variable output
//------------------------------------------------------------------------------------------------- 
if(id.modeTask=='C'){if(++id.cntLimit>=id.periodLimit){id.cntLimit=0;				 id.run=2;} return;} //--Output at change variable;
if(id.modeTask=='P'){if(++id.cntTask >=id.periodTask) {id.cntTask =0; 				 id.run=1;} return;} //--Output periodic;
if(id.modeTask=='T'){if(++id.cntTask >=id.periodTask) {id.cntTask =0; 				 id.run=2;} return;} //--Output periodic at change variable; 
if(id.modeTask=='A'){if(++id.cntLimit>=id.periodLimit){id.cntLimit=0;                id.run=2;}          //--Output at change variable or periodic;
                     if(++id.cntTask >=id.periodTask) {id.cntTask =0; id.cntLimit=0; id.run=1;} return;}        
//-------------------------------------------------------------------------------------------------
}; 	//++++END LcdGenerator()-----------------------------------------------------------------------

//=================================================================================================
//								2.Preparing a numerical variable with Head
//=================================================================================================
void LcdPreparData(RT_HW_LCD44780_PARAM_ID &id, const char *head){
//-------------------------------------------------------------------------------------------------
arrReset(id.num);   														//--Reset parameters output array;
if(id.cmdRun==3){for(id.idx=0; id.idx<id.len; id.idx++){arrWrite(id.num,' ');} arrReset(id.num); return;} //--Clearing output array;
//-------------------------------Расчет длины поля заголовка и суффикса----------------------------
if(id.msLenHead==255){id.xSrc=0; if(!(getCharLcdPGM(head,id.xSrc)=='~')){	//--Heading Sizing;
	                 id.msLenHead=getLenPGM(head,id.len);} else{id.msLenHead=0;}} 
if(id.suff=='~')     {id.msLenSuff=0;} else{id.msLenSuff=1;}				//--Suffix Sizing;
//-------------------------------Расчет длины поля переменной--------------------------------------
id.msLenVar=0;
if(id.formatVar=='I'){id.msLenVar=String(id.agoVar).length();}
if(id.formatVar=='U'){if(id.agoVar>=0){id.msLenVar=String(id.agoVar).length();} else{id.msLenVar=String((uint32_t)(-id.agoVar)).length();}}
if(id.formatVar=='0'){id.msLenVar=String(id.agoVar).length();}
if(id.formatVar=='1'){id.msLenVar=String((float)id.agoVar/10.0,1).length();}
if(id.formatVar=='2'){id.msLenVar=String((float)id.agoVar/100.0,2).length();}
if(id.formatVar=='3'){id.msLenVar=String((float)id.agoVar/1000.0,3).length();}
if(id.formatVar=='4'){id.msLenVar=String((float)id.agoVar/10000.0,4).length();}
if(id.formatVar=='T'){id.msLenVar=2;}
if(id.formatVar=='H'){if(id.modeVar=='B'){id.msLenVar=2;} if(id.modeVar=='W'){id.msLenVar=4;} if(id.modeVar=='L'){id.msLenVar=8;}}
if(id.formatVar=='#'){if(id.modeVar=='B'){id.msLenVar=8;} if(id.modeVar=='W'){id.msLenVar=16;}}
if(id.formatVar=='*'){if(id.modeVar=='B'){id.msLenVar=8;} if(id.modeVar=='W'){id.msLenVar=16;}}
if(id.formatVar=='='){id.msLenVar=4;}
if(id.formatVar=='-'){id.msLenVar=4;}
//if(id.formatVar=='X'){id.msLenVar=(id.agoVar&0xFFFF)*(id.len-id.msLenSuff)/100;} 		
//---------------------------------------------------------------------------------------------------
   if(( id.msLenHead+id.msLenVar+id.msLenSuff)> id.len){id.msLenSuff=0;}	                        //--Suffix     length normalization;
do{if(((id.msLenHead+id.msLenVar)<=id.len) ||(id.msLenHead==0)){break;} id.msLenHead--;} while(1);	//--Heading    length normalization;		   
do{if(((id.msLenVar)<=id.len) ||(id.msLenVar==0))              {break;} id.msLenVar--;}  while(1);	//--Variabling length normalization;
//----------------------------------Расчет Begin и End заполнителей----------------------------------
id.msLenBegin=getLenBegin(id);	 id.msLenEnd=getLenEnd(id); 		
//---------------------------------------------------------------------------------------------------
if(id.msLenBegin>0){          for(id.idx=0; id.idx<id.msLenBegin; id.idx++){arrWrite(id.num,' ');}}	//--Write to array blank before Head;  																																		//--Очистка индекса для getCharLcdPGM();
if(id.msLenHead>0) {id.xSrc=0;for(id.idx=0; id.idx<id.msLenHead;  id.idx++){arrWrite(id.num,getCharLcdPGM(head,id.xSrc));}} //--Write to array Head; 
//------------------------------------------Запись переменной----------------------------------------
if(id.msLenVar>0){
String bs;
if(id.formatVar=='I'){bs=String(id.agoVar);}
if(id.formatVar=='U'){if(id.agoVar>=0){bs=String(id.agoVar);} else{bs=String(-id.agoVar);}}
if(id.formatVar=='0'){bs=String(id.agoVar);}
if(id.formatVar=='1'){bs=String((float)id.agoVar/10.0,1);}
if(id.formatVar=='2'){bs=String((float)id.agoVar/100.0,2);}
if(id.formatVar=='3'){bs=String((float)id.agoVar/1000.0,3);}
if(id.formatVar=='4'){bs=String((float)id.agoVar/10000.0,4);}
if(id.formatVar=='T'){bs=String(id.agoVar); if(id.agoVar<=9) {bs="0"+bs;}}
if(id.formatVar=='H'){if(id.modeVar=='B'){bs=String((id.agoVar&0xFF),      HEX); bs.toUpperCase(); uint8_t bl=bs.length(); if(bl==1){bs="0"+bs;}} 
                      if(id.modeVar=='W'){bs=String((id.agoVar&0xFFFF),    HEX); bs.toUpperCase(); uint8_t bl=bs.length(); if(bl==1){bs="000"+bs;} if(bl==2){bs="00"+bs;} if(bl==3){bs=String("0")+bs;}}
                      if(id.modeVar=='L'){bs=String((id.agoVar&0xFFFFFFFF),HEX); bs.toUpperCase(); uint8_t bl=bs.length(); if(bl<8){for(id.idx=0; id.idx<(8-bl);id.idx++){bs=String("0")+bs;}}}} 
if(id.formatVar=='#'){if(id.modeVar=='B'){uint8_t  buff=id.agoVar&0xFF;   for(id.idx=0; id.idx<8;  id.idx++){bs=bs+getSignBit(buff,7-id.idx);}}
                      if(id.modeVar=='W'){uint16_t buff=id.agoVar&0xFFFF; for(id.idx=0; id.idx<16; id.idx++){bs=bs+getSignBit(buff,15-id.idx);}}}
if(id.formatVar=='*'){if(id.modeVar=='B'){uint8_t  buff=id.agoVar&0xFF;   for(id.idx=0; id.idx<8;  id.idx++){bs=bs+getSignBit(buff,id.idx);}}
                      if(id.modeVar=='W'){uint16_t buff=id.agoVar&0xFFFF; for(id.idx=0; id.idx<16; id.idx++){bs=bs+getSignBit(buff,id.idx);}}}
if(id.formatVar=='='){                    uint8_t  buff=id.agoVar&0xF;    for(id.idx=0; id.idx<4;  id.idx++){bs=bs+getSignBit(buff,4-id.idx);}}
if(id.formatVar=='-'){                    uint8_t  buff=id.agoVar&0xF;    for(id.idx=0; id.idx<4;  id.idx++){bs=bs+getSignBit(buff,id.idx);}}											 
for(id.idx=0; id.idx<id.msLenVar; id.idx++){arrWrite(id.num,bs.charAt(id.idx));}
}
//----------------------------------Запись суффикса и End заполнителей-----------------------------
if(id.msLenSuff>0) {arrWrite(id.num,id.suff);}															//--Write to array suffix; 
if(id.msLenEnd>0)  {          for(id.idx=0; id.idx<id.msLenEnd;   id.idx++){arrWrite(id.num,' ');}}		//--Write to array blank after variable; 
//-------------------------------------------------------------------------------------------------
arrReset(id.num);   																					//--Reset parameters output array;
};
//=================================================================================================
//								3.Preparing a String
//=================================================================================================
void LcdPreparStr (RT_HW_LCD44780_PARAM_ID &id, String var){
arrReset(id.num);   																					//--Reset parameters output array;
if(id.cmdRun==3){for(id.idx=0; id.idx<id.len; id.idx++){arrWrite(id.num,' ');} arrReset(id.num);return;}//--Clearing output array;
id.msLenHead=id.msLenVar=id.msLenSuff=0;  									
id.xSrc=0;if(!(getCharLcdSTR(var,id.xSrc)=='~')){id.msLenVar=getLenSTR(var,id.len);}else{id.msLenVar=0;}//--Variable    size calculation;
id.msLenBegin=getLenBegin(id);	 																		//--Begin blank size calculation;
id.msLenEnd=getLenEnd(id); 																				//--End   blank size calculation;		
if(id.msLenBegin>0){for(id.idx=0; id.idx<id.msLenBegin; id.idx++){arrWrite(id.num,' ');}}				//--Write to array blank before variable; 																																		//--Очистка индекса для getCharLcdPGM();
if(id.msLenVar>0){id.xSrc=0;for(id.idx=0; id.idx<id.msLenVar; id.idx++){arrWrite(id.num,getCharLcdSTR(var,id.xSrc));}}//--Write to array variable; 
if(id.msLenEnd>0)  {for(id.idx=0; id.idx<id.msLenEnd;   id.idx++){arrWrite(id.num,' ');}}				//--//--Write to array blank after variable; 
arrReset(id.num);  																						//--Reset parameters output array;
}; 	//++++END LcdPreparData()----------------------------------------------------------------------
//=================================================================================================
//								3.Preparing a Bra
//=================================================================================================
void LcdPreparBar (RT_HW_LCD44780_PARAM_ID &id){
arrReset(id.num);    																					//--Reset parameters output array;
if(id.cmdRun==3){for(id.idx=0; id.idx<id.len; id.idx++){arrWrite(id.num,' ');} arrReset(id.num);return;}//--Clearing output array;
id.msLenHead=0; 
if(id.suff=='~') {id.msLenSuff=0;} else{id.msLenSuff=1;}												//--Suffix size calculation;
if(id.agoVar>100){id.buff=100;}    else{id.buff=id.agoVar;}												//--Ограничение переменной 100%ж
id.msLenVar=(id.buff*(id.len-id.msLenSuff))/100;														//--Расчет длины линии
id.msLenBegin=getLenBegin(id); 																			//--Расчет Begin-заполнителей;	
id.msLenEnd=getLenEnd(id); 																				//--Расчет End-заполнителей;																																				//--Очистка индекса для getCharLcdPGM();
if(id.msLenBegin>0){for(id.idx=0; id.idx<id.msLenBegin; id.idx++){arrWrite(id.num,' ');}}				//--Запись Begin-заполнителей;
if(id.msLenVar>0)  {for(id.idx=0; id.idx<id.msLenVar;   id.idx++){arrWrite(id.num,id.formatVar);}}		//--Запись переменной;
if(id.msLenSuff>0) {                                              arrWrite(id.num,id.suff);}			//--Запись суффикса;
if(id.msLenEnd>0)  {for(id.idx=0; id.idx<id.msLenEnd;   id.idx++){arrWrite(id.num,' ');}}				//--Запись End-заполнителей;
arrReset(id.num);  																				    	//--Сброс массива вывода;
}; 	//++++END LcdPreparData()----------------------------------------------------------------------


//=================================================================================================
//			         				4.Customizing the output field block
//-------------------------------------------------------------------------------------------------
// modeVar:   mode   var: B(uint8_t),W(int16_t),L(int32_t),F(float),S(String),C(char),R(bit),T(text from PROGMEM),G(blink);
// formatVar: format var: U-unsigned integer[B,W,L];  I-signed integer[B,W,L], 0,1,2,3-number of decimal places for Float[0,1,2,3];
// modeTask:  mode  task: C(by changing the variable), P(periodically), T(periodically with changes),
//						  A(by change or periodically),S(extEN 0->1),   F(once), N(Off);
// alig: field alignment: L(Left), C(Center),R(Rigth), N(Off);
// suff:     suffix:      char output after the data. If '~' - the suffix is not output;
// periodLimit: limitation(ms/tick) by task call time[for C,P,T,A];
// periodTask:  period(ms/tick) of task call;
//=================================================================================================
void initLcdID  (RT_HW_LCD44780_PARAM_ID &id, uint8_t num, char modeVar, char formatVar, char modeTask, char alig, char suff, uint16_t periodLimit, uint16_t periodTask, uint8_t col, uint8_t row, uint8_t len=0){
if( id.custom)		{return;}						//--Exit if block ID is initialized;
if(!checkNum(num))	{return;}						//--Control for the admissibility of the device number;
id.num=num;											//--Saving device number;
id.modeVar=modeVar;									//--Saving the type of a variable;
id.formatVar=formatVar;								//--Saving the format of a variable;
id.modeTask=modeTask;								//--Saving the mode task;
id.alig=alig;										//--Saving the field alignment type;
id.suff=suff;										//--Saving the suffix;
id.periodGen=ptr[id.num]->periodGen;				//--Saving the tick period (from the master
id.periodTask =timeToTick(periodTask, id.periodGen);//--Calculating task periodicity in ticks;
id.periodLimit=timeToTick(periodLimit,id.periodGen);//--Calculation of the task call time limit in ticks;                   
id.periodBlink=timeToTick(        500,id.periodGen);//--Calculation of the flickering period of the field in ticks;
id.cntBlink=id.modeBlink=id.blink=0;
//----------------------------------------------------------------------------------------------------
if(col>ptr[id.num]->cols) {id.col=ptr[id.num]->cols;} else{id.col=col;}	//--Saving the number of colums with range limitation;
if(row>ptr[id.num]->rows) {id.row=ptr[id.num]->rows;} else{id.row=row;}	//--Saving the number of rows   with range limitation;
id.vCursor=pointCursor(id.num,id.col,id.row);                       	//--Saving the cursor position control code;
id.curChip=1; if((ptr[id.num]->chip==2)&&(id.row>2)){id.curChip=2;}		//--Setting the chip number of the output field (two chips for 40x4 displays);
//----------------------------------------------------------------------------------------------------
id.buff=ptr[id.num]->cols-id.col+1; 									//--Setting the maximum length of a valid field;
if((len==0)||(len>id.buff)){id.len=id.buff;}		  else{id.len=len;}	//--Setting the field length;
//----------------------------------------------------------------------------------------------------
id.first=id.flicker=0; 													//--Setting Initial Values;
id.custom=1;}															//--Completion of setup;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//			         					5.FUNCTION LCD OUTPUT INITIALIZATION
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void initBlinkID(RT_HW_LCD44780_PARAM_ID &id,uint8_t n,                                      uint16_t pTsk,uint8_t col,uint8_t row){initLcdID(id,n,'F','N','P','N','~', 50,pTsk,col,row);};	
void initBitID  (RT_HW_LCD44780_PARAM_ID &id,uint8_t n,                                      uint8_t col,uint8_t row)              {initLcdID(id,n,'R','N','C','L','~', 50,2500,col,row);};	
void initCharID (RT_HW_LCD44780_PARAM_ID &id,uint8_t n,                                      uint8_t col,uint8_t row)              {initLcdID(id,n,'L','N','C','N','~',100,2500,col,row);};	
void initTimeID (RT_HW_LCD44780_PARAM_ID &id,uint8_t n,                  char sff,           uint8_t col,uint8_t row,uint8_t len=0){initLcdID(id,n,'B','T','C','R',sff,500,2500,col,row,len);}
void initTextID (RT_HW_LCD44780_PARAM_ID &id,uint8_t n,         char alg,                    uint8_t col,uint8_t row,uint8_t len=0){initLcdID(id,n,'T','N','C',alg,'~',500,2500,col,row,len);};			
void initByteID (RT_HW_LCD44780_PARAM_ID &id,uint8_t n,char frm,char alg,char sff,           uint8_t col,uint8_t row,uint8_t len=0){initLcdID(id,n,'B',frm,'C',alg,sff,100,2500,col,row,len);}

void initWordID (RT_HW_LCD44780_PARAM_ID &id,uint8_t n,char frm,char alg,char sff,           uint8_t col,uint8_t row,uint8_t len=0){initLcdID(id,n,'W',frm,'C',alg,sff,200,2500,col,row,len);}
void initLongID (RT_HW_LCD44780_PARAM_ID &id,uint8_t n,char frm,char alg,char sff,           uint8_t col,uint8_t row,uint8_t len=0){initLcdID(id,n,'L',frm,'C',alg,sff,250,2500,col,row,len);}
void initFloatID(RT_HW_LCD44780_PARAM_ID &id,uint8_t n,char frm,char alg,char sff,           uint8_t col,uint8_t row,uint8_t len=0){initLcdID(id,n,'F',frm,'C',alg,sff,500,2500,col,row,len);}		 
void initStrID  (RT_HW_LCD44780_PARAM_ID &id,uint8_t n,         char alg,                    uint8_t col,uint8_t row,uint8_t len=0){initLcdID(id,n,'S','N','C',alg,'~',500,5000,col,row,len);}	
void initBarID  (RT_HW_LCD44780_PARAM_ID &id,uint8_t n,char frm,char alg,char sff,           uint8_t col,uint8_t row,uint8_t len=0){initLcdID(id,n,'X',frm,'C',alg,sff,100,5000,col,row,len);}	


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//						              		6.OUTPUT to LCD
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=================================================================================================
//						       			6.1.Blinking character output
//=================================================================================================
void LcdBlink(RT_HW_LCD44780_PARAM_ID &id,              char sign0=' ', char sign1='*'){
LcdGenerator(id);
if(id.dir==0) {if(id.run==0){return;} if(!id.custom){return;} id.cmdRun=id.run; id.dir++;}	//--Waiting for permission to output;
if(id.dir==1) {if(!getBusy(id.num)){return;} 							id.dir=30; 			//--Waiting for LCD release;
			   if(id.cmdRun==3){id.buff=RT_HW_LCD44780_BLANK; 			id.dir=20;}			//--Switching to clearing the field;
			   if(id.cmdRun==1){             							id.dir=10;}			//--Switching to unconditional output;
			   if(id.dir==1)   {		 								id.dir=30;} 		//--Switching  to output completion;
			   id.cmdRun=0;}																//--Reset cmdRun;											
if(id.dir==10){if(id.agoBit){id.buff=sign1;} else{id.buff=sign0;} id.agoBit=!id.agoBit; id.dir=20;} //--Select char and swtitching at change; 	
if(id.dir==20){if(deviceSend(id.num,id.curChip,id.vCursor,'I',RT_HW_LCD44780_TIME_CURSOR)){id.dir++;} return;}	//--Setting cursor; 
if(id.dir==21){if(!deviceSend(id.num,id.curChip,id.buff,'D'))      {return;} id.dir=30;}	//--Output char for blink;	
if(id.dir==30){clearBusy(id.num); id.run=0; id.dir=0; return;} 								//--Bus release and jump to start;
};
//=================================================================================================
//						       			6.2.Bit as character output
//=================================================================================================
void LcdBit  (RT_HW_LCD44780_PARAM_ID &id, uint8_t var, char sign0='-', char sign1='+'){
LcdGenerator(id); 
if(id.dir==0) {if(id.run==0){return;} if(!id.custom){return;} id.cmdRun=id.run; id.dir++;}	//--Waiting for permission to output;
if(id.dir==1) {if(!getBusy(id.num)){return;} 							id.dir=30; 			//--Waiting for LCD release;;
			   if(id.cmdRun==3){id.buff=RT_HW_LCD44780_BLANK; 			id.dir=20;} 		//--Switching to clearing the field;
			   if(id.cmdRun==1){            		            		id.dir=10;} 		//--Switching to unconditional output;
               if(id.cmdRun==2){if(id.agoBit!=var){             		id.dir=10;}}		//--Switching to unconditional output;			   
			   if(id.dir==1)   {		 								id.dir=30;} 		//--Switching  to output completion;
			   id.cmdRun=0;}																//--Reset cmdRun;											
if(id.dir==10){id.agoBit=var; if(id.agoBit==0){id.buff=sign0;} else{id.buff=sign1;} id.dir=20;}//--Select char for bit;		
if(id.dir==20){if(deviceSend(id.num,id.curChip,id.vCursor,'I',RT_HW_LCD44780_TIME_CURSOR)){id.dir++;} return;}	//--Setting cursor;  
if(id.dir==21){if(!deviceSend(id.num,id.curChip,id.buff,'D'))      {return;} id.dir=30;}	//--Output char;	
if(id.dir==30){clearBusy(id.num); id.run=0; id.dir=0; return;} 								//--Bus release and jump to start;
};
//=================================================================================================
//						       			6.3.Character output
//=================================================================================================
void LcdChar (RT_HW_LCD44780_PARAM_ID &id, char    var){
LcdGenerator(id); 
if(id.dir==0) {if(id.run==0){return;} if(!id.custom){return;} id.cmdRun=id.run; id.dir++;}	//--Waiting for permission to output;
if(id.dir==1) {if(!getBusy(id.num)){return;} 							id.dir=30; 			//--Waiting for LCD release;
			   if(id.cmdRun==3){id.buff=RT_HW_LCD44780_BLANK; 			id.dir=20;}			//--Switching to clearing the field;
			   if(id.cmdRun==1){                   						id.dir=10;} 		//--Switching to unconditional output;
			   if(id.cmdRun==2){if(id.agoVar!=var){			 			id.dir=10;}}		//--Switching to output on variable change;
			   if(id.dir==1)   {		 								id.dir=30;} 		//--Switching to output completion;	
			   id.cmdRun=0;}																//--Reset cmdRun;			   											
if(id.dir==10){id.agoVar=var; 											id.dir=20;}			//--Saving the output character; 	
if(id.dir==20){if(deviceSend(id.num,id.curChip,id.vCursor,'I',RT_HW_LCD44780_TIME_CURSOR)){id.dir++;} return;}	//--Setting cursor; 
if(id.dir==21){if(!deviceSend(id.num,id.curChip,(uint8_t)id.agoVar,'D')){return;}id.dir=30;}//-Output char;	
if(id.dir==30){clearBusy(id.num); id.run=0;                               id.dir=0; return;}//--Bus release and jump to start;
};
//=================================================================================================
//						       			6.4.Text output
//=================================================================================================
void LcdText (RT_HW_LCD44780_PARAM_ID &id, const char *head){
LcdGenerator(id); 
if(id.dir==0) {if(id.run==0){return;} if(!id.custom){return;} id.cmdRun=id.run; id.dir++;}	//--Waiting for permission to output;
if(id.dir==1) {if(!getBusy(id.num)){return;} 							  id.dir=30; 		//--Waiting for LCD release;
			   if(id.cmdRun==3){arrInit(id.num,id.len); arrClear(id.num); id.dir=20;} 		//--Switching to clearing the field;
			   if(id.cmdRun==1){arrInit(id.num,id.len);             	  id.dir=10;} 		//--Switching to unconditional output;
			   if(id.dir==1)   {		 								  id.dir=30;} 		//--Switching  to output completion;	
			   id.cmdRun=0;}														  		//--Reset cmdRun;	
if(id.dir==10){LcdPreparData(id,head);                                    id.dir=20;} 		//--Switching to output array generation;
if(id.dir==20){if(!(arrSend(id.num,id.curChip,id.vCursor))){return;}      id.dir=30;} 		//--OUTPUT array to LCD with cursor;
if(id.dir==30){clearBusy(id.num); id.run=0;                               id.dir=0; return;}//--Bus release and jump to start;
};
//=================================================================================================
//						       			6.5.Integer Variable output with Head
//										  v8,v16,v32(mode=U,I,H,1,2,3,#,*)
//=================================================================================================
void LcdVar  (RT_HW_LCD44780_PARAM_ID &id, const char *head, int32_t var){
LcdGenerator(id); 
if(id.dir==0) {if(id.run==0){return;} if(!id.custom){return;} id.cmdRun=id.run; id.dir++;}	//--Waiting for permission to output;
if(id.dir==1) {if(!getBusy(id.num)){return;} id.dir=30;   									//--Waiting for LCD release;
               if(id.cmdRun==3){arrInit(id.num,id.len); arrClear(id.num); id.dir=10;}  		//--Switching to clearing the field;		   
               if(id.cmdRun==1){arrInit(id.num,id.len); id.agoVar=var;    id.dir=10;}		//--Switching to unconditional output;
               if(id.cmdRun==2){if(id.agoVar!=var){id.agoVar=var; arrInit(id.num,id.len);id.dir=10;}}//Sw.to output on variable change;
			   if(id.dir==1)   {		 								  id.dir=30;} 		//--Switching to output completion;	
			   id.cmdRun=0;}														  		//--Reset cmdRun;
if(id.dir==10){LcdPreparData(id,head);  							      id.dir=20;return;}//--Switching to output array generation;
if(id.dir==20){if(!(arrSend(id.num,id.curChip,id.vCursor))){return;}      id.dir=30;} 		//--OUTPUT array to LCD with cursor;
if(id.dir==30){clearBusy(id.num);       id.run=0;                         id.dir=0; return;}//--Bus release and jump to start;
};
//=================================================================================================
//						       			6.6.Float Variable output with Head
//=================================================================================================
void LcdFloat(RT_HW_LCD44780_PARAM_ID &id, const char *head, float var){
LcdGenerator(id);
if(id.dir==0) {if(id.run==0){return;} if(!id.custom){return;} id.cmdRun=id.run; id.dir++;}	//--Waiting for permission to output;
if(id.dir==1) {if(!getBusy(id.num)){return;} id.dir=30;   									//--Waiting for LCD release;
               if(id.cmdRun==3){arrInit(id.num,id.len); arrClear(id.num); id.dir=20;}; 		//--Switching to clearing the field;		   
               if(id.cmdRun==1){arrInit(id.num,id.len); id.agoVar=floatToInt(id.formatVar,var); id.dir=10;} //--Switching to unconditional output;
               if(id.cmdRun==2){if(id.agoVar!=floatToInt(id.formatVar,var)){				//--Switching to output on variable change;
				                arrInit(id.num,id.len); id.agoVar=floatToInt(id.formatVar,var); id.dir=10;}}
			   if(id.dir==1)   {		 								  id.dir=30;} 		//--Switching  to output completion;	
			   id.cmdRun=0;}														  		//--Reset cmdRun;								
if(id.dir==10){LcdPreparData(id,head);  							      id.dir=20;return;}//--Switching to output array generation;
if(id.dir==20){if(!(arrSend(id.num,id.curChip,id.vCursor))){return;}      id.dir=30;}		//--OUTPUT array to LCD with cursor;
if(id.dir==30){clearBusy(id.num);       id.run=0;                         id.dir=0; return;}//--Bus release and jump to start;
};
//=================================================================================================
//						       			6.7.String Variable output
//=================================================================================================
void LcdStr  (RT_HW_LCD44780_PARAM_ID &id, String &agoVar,  String var){
LcdGenerator(id);
if(id.dir==0) {if(id.run==0){return;} if(!id.custom){return;} id.cmdRun=id.run; id.dir++;} 	//--Waiting for permission to output;
if(id.dir==1) {if(!getBusy(id.num)){return;} id.dir=30;   									//--Waiting for LCD release;
               if(id.cmdRun==3){arrInit(id.num,id.len); arrClear(id.num); id.dir=20;}; 		//--Switching to clearing the field;		   
               if(id.cmdRun==1){arrInit(id.num,id.len); agoVar=var;       id.dir=10;}  		//--Switching to unconditional output;
               if(id.cmdRun==2){if(agoVar!=var){arrInit(id.num,id.len); agoVar=var; id.dir=10;}}//--Sw.   to output on variable change;
			   if(id.dir==1)   {		 								  id.dir=30;}  		//--Switching to output completion;	
			   id.cmdRun=0;}														  		//--Reset cmdRun;	
if(id.dir==10){LcdPreparStr(id,var);  							          id.dir=20;return;}//--Switching to output array generation;
if(id.dir==20){if(!(arrSend(id.num,id.curChip,id.vCursor))){return;}      id.dir=30;}		//--OUTPUT array to LCD with cursor;
if(id.dir==30){clearBusy(id.num);       id.run=0;                         id.dir=0; return;}//--Bus release and jump to start;
};
//=================================================================================================
//						       			6.8.Variable 0-100 output was BAR
//=================================================================================================
void LcdBar  (RT_HW_LCD44780_PARAM_ID &id,                 int32_t var){
LcdGenerator(id);
if(id.dir==0) {if(id.run==0){return;} if(!id.custom){return;} id.cmdRun=id.run; id.dir++;} 	//--Waiting for permission to output;
if(id.dir==1) {if(!getBusy(id.num)){return;} id.dir=30;   									//--Waiting for LCD release;
               if(id.cmdRun==3){arrInit(id.num,id.len); arrClear(id.num); id.dir=20;}; 		//--Switching to clearing the field;		   
               if(id.cmdRun==1){arrInit(id.num,id.len); id.agoVar=var;    id.dir=10;}  		//--Switching to unconditional output;
               if(id.cmdRun==2){if(id.agoVar!=var){id.agoVar=var;arrInit(id.num,id.len);id.dir=10;}}//-Sw.to output on variable change;
			   if(id.dir==1)   {		 								  id.dir=30;} 		//--Switching to output completion;	
			   id.cmdRun=0;}														  		//--Reset cmdRun;	
if(id.dir==10){LcdPreparBar(id);  							      		  id.dir=20;return;}//--Switching to output array generation;
if(id.dir==20){if(!(arrSend(id.num,id.curChip,id.vCursor))){return;}      id.dir=30;}		//--OUTPUT array to LCD with cursor;
if(id.dir==30){clearBusy(id.num);       id.run=0; id.dir=0; return;} 						//--Bus release and jump to start;
};
//=================================================================================================
//						       			6.9.Var,Float output wthout HEAD
//=================================================================================================
void LcdVAR  (RT_HW_LCD44780_PARAM_ID &id, int32_t var){LcdVar  (id,RT_HW_LCD44780_HEAD,var);};//++Вывод v8,v16,v32 без заголовка;
void LcdFLOAT(RT_HW_LCD44780_PARAM_ID &id, float   var){LcdFloat(id,RT_HW_LCD44780_HEAD,var);};//++Вывод float(mode=1,2,3) без заголовка;
//=================================================================================================


