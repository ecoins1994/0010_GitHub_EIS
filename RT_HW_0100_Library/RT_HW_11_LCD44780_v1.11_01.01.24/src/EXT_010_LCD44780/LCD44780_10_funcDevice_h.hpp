//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//									1.General fuictoin for direct device
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//									1.1.Device control clock generator
//=================================================================================================
void generatorDevice    (RT_HW_LCD44780_DEVICE_ID &id){ 
id.eventTick=id.eventSec=id.eventMin=0; 					
if(id.num==0){id.genState=4; return;}		//--Exit if the device is not assigned a number;
//-------------------------------------------------------------------------------------------------
if(RT_HW_Base.periodMs(id.timeBeginGen, id.periodGen)){
 if      (id.genState==1){id.genState=0;} 
 else {if(id.genState==0){id.genState=1;}}  
 id.eventTick=1;                                                          id.meanderTick=!id.meanderTick;	//--Generation of the tick   event and the meander;
 if(++id.cntTickSec>=(1000/id.periodGen)){id.cntTickSec=0; id.eventSec=1; id.meanderSec=!id.meanderSec;}; 	//--Generation of the second event and the meander;
 if(id.eventSec){if(++id.cntSecMin>=60)  {id.cntSecMin=0;  id.eventMin=1; id.meanderMin=!id.meanderMin;}};	//--Generation of the minite event and the meander; 
 if(id.eventMin){if((id.periodReboot>0)&&(++id.cntReboot>=id.periodReboot)){id.cntReboot=0; id.runReboot=1;}}//-Generate a periodic restart of the device;
 if(id.busy)    {if(++id.cntWatchDogBusy>(id.periodWatchDog/id.periodGen)) {id.cntWatchDogBusy=0; id.busy=0;}} else {id.cntWatchDogBusy=0;}} //--Watch-dog;
//---------------------------------------------------------------------------------------------------
};
//=================================================================================================
//									1.2.Clearing the Device Control Vector
//=================================================================================================
void clearDeviceID(RT_HW_LCD44780_DEVICE_ID &id){
id.meanderTick =id.meanderSec =id.meanderMin =1;	
id.cntTickSec=id.cntSecMin=id.cntReboot=id.cntWatchDogBusy=id.cnt=id.cntErr=0; 
id.codeErr=0;
id.busy=1; 	id.runReboot=id.readyDevice=0;
//-------------------------------------------------------------------------------------------------
id.agoEN=0; id.extEN=1;
id.extLight=1;
id.agoClear=id.extClear=0;
id.agoReset=id.extReset=id.runReset=0;
for(id.arrIdx=0; id.arrIdx < RT_HW_LCD44780_MAX_COLS; id.arrIdx++){id.arrData[id.arrIdx]=RT_HW_LCD44780_CODE_BLANK;} 
};
//=================================================================================================
//						              10.1.Pointer setting 
//                           (временная функция - надо будет её перенести в direct)
//=================================================================================================
void setPointID(RT_HW_LCD44780_DEVICE_ID *id){ptr[id->num]=id;}



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//									6.Array Data or send LCD
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//									6.1.arInit   -Сброс параметров управления массивом, заполнение '*';
//=================================================================================================
void    arrInit  (uint8_t num, uint8_t len=40){
 if(len>RT_HW_LCD44780_MAX_COLS){ptr[num]->arrLen=RT_HW_LCD44780_MAX_COLS;} 
 else							{ptr[num]->arrLen=len;} 					//--Размер записываемого массива;
 for(ptr[num]->arrIdx=0; (ptr[num]->arrIdx) < (ptr[num]->arrLen); ptr[num]->arrIdx++){ptr[num]->arrData[ptr[num]->arrIdx]='*';} //--Заполнение массива;
 ptr[num]->arrSize=0;		//--Размер записанного массива;
 ptr[num]->arrPackCnt=0;	//--Счетчик кол-ва отправляемых значений за одну транзакцию;
 ptr[num]->arrState=0;		//--Состояние при чтении: =0 -все прочитано; =1-есть данные; =2-есть данные и передан пакет=arrReadPackMax;  
 ptr[num]->arrIdx=0;		//--Индекс текущего значения массива; 
};
//=================================================================================================
//									6.2.arrClear -Сброс параметров и очистка массива пробелами;
//=================================================================================================
void    arrClear (uint8_t num){ 
 for(ptr[num]->arrIdx=0; (ptr[num]->arrIdx) < (ptr[num]->arrLen); ptr[num]->arrIdx++){ 	//--Clearing;
	 ptr[num]->arrData[ptr[num]->arrIdx]=' ';} 											//		array;
     ptr[num]->arrIdx=0;	//--Reset index;  
	 ptr[num]->arrDir=0;	//--Reset dir; 
};
//=================================================================================================
//									6.3.arrWrite -Запись в массив следующего значения;
//=================================================================================================
void    arrWrite (uint8_t num, uint8_t v8){   
 if(ptr[num]->arrIdx>=RT_HW_LCD44780_MAX_COLS){return;}  	//--Выход, если массив заполнен;
 ptr[num]->arrData[ptr[num]->arrIdx]=v8; 					//--Запись текущего значения;
 ptr[num]->arrIdx++;										//--Увеличение индекса;
 ptr[num]->arrSize++;										//--Увеличение размера записываемого массива;
};
//=================================================================================================
//									6.4.arrReset -Сброс индекса,arrDir и счетчика пакетов;
//=================================================================================================
void    arrReset (uint8_t num){
    ptr[num]->arrIdx=0; ptr[num]->arrPackCnt=0; ptr[num]->arrDir=0;}
//=================================================================================================
//									6.5.arrRead  -Чтение массива;
//=================================================================================================
void    arrRead  (uint8_t num){
//if((ptr[num]->arrIdx)>ptr[num]->arrLen){ptr[num]->arrDataCur='#';                                 ptr[num]->arrState=3; return;}  //--Выход по чтению за пределами записанных данных;
ptr[num]->arrDataCur=ptr[num]->arrData[ptr[num]->arrIdx];										                                  //--Чтение очередного значения;
if((ptr[num]->arrIdx)>=ptr[num]->arrSize){                                                        ptr[num]->arrState=0; return;}  //--Выход по чтению всех данных;
ptr[num]->arrPackCnt++; if((ptr[num]->arrPackCnt)>(ptr[num]->arrPackMax)){ptr[num]->arrPackCnt=0; ptr[num]->arrState=2; return;}  //--Выход по передаче пакета;
ptr[num]->arrIdx++;																	              ptr[num]->arrState=1; return;   //--Выход для продолжения чтения;
};
//=================================================================================================
//									6.6.arrData  -Получение последнего прочитанного значения;
//=================================================================================================
uint8_t arrData  (uint8_t num){return ptr[num]->arrDataCur;}																									
//=================================================================================================
//									6.7.arrState -Получение слова состояния;
//=================================================================================================
uint8_t arrState (uint8_t num){return ptr[num]->arrState;}																									
//=================================================================================================
//                                  6.88.arrSend  -Отправка массива в Lcd в позицию курсора;
//=================================================================================================
uint8_t arrSend  (uint8_t num, uint8_t curChip, uint8_t vCursor){	
 if(ptr[num]->arrDir==0){if(!deviceSend(num,curChip,vCursor,'I',RT_HW_LCD44780_TIME_CURSOR)){return 0;}  //--Вывод курсора; 
                                                                ptr[num]->arrSendOk=0; ptr[num]->arrDir++;}
 if(ptr[num]->arrDir==1){do{arrRead(num); if(arrState(num)>=3) {ptr[num]->arrSendOk=1; break;} 	//--Прочитаны все данные
                                          if(arrState(num)==0) {ptr[num]->arrSendOk=1; break;} 	//--Прочитаны все данные;
                                          if(arrState(num)==2) {ptr[num]->arrSendOk=0; break;} 	//--Очередной пакет отправлен;
                                          if(arrState(num)==1) {deviceSend(num,curChip,arrData(num),'D');}//--Отправка данных;
					       }while(1); 
						 
                         return ptr[num]->arrSendOk;}
return 1;};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//						              		10.Utilitues
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=================================================================================================
//						              10.2.Quick display cleaning
//=================================================================================================
void directClear    (RT_HW_LCD44780_DEVICE_ID &z){
              deviceSend(z.num,1,0b00000001,'I'); delayMicroseconds(40);  //--for chip=1;
if(z.chip==2){deviceSend(z.num,2,0b00000001,'I'); delayMicroseconds(40);} //--for chip=2;
};
//=================================================================================================
//						       		10.3.Convertation float to int32
//=================================================================================================
int32_t floatToInt(char formatVar, float var) {
 if(formatVar=='0') {return (int32_t)(var);}	
 if(formatVar=='1') {return (int32_t)(var*10);}	
 if(formatVar=='2') {return (int32_t)(var*100);}
 if(formatVar=='3') {return (int32_t)(var*1000);}
 if(formatVar=='4') {return (int32_t)(var*10000);}	
 if(formatVar=='5') {return (int32_t)(var*100000);}
 if(formatVar=='6') {return (int32_t)(var*1000000);}
                     return (int32_t)(var);
};	
//=================================================================================================
//						       		10.4.Getting character number from utf-8
//=================================================================================================
uint8_t convert   (uint8_t charH, uint8_t charL){
if(charH==0xD0) {if (charL==0x81) {return 0x40;}  if((charL>=0x90) && (charL<=0xBF)){return (charL-0x90);}};
if(charH==0xD1) {if (charL==0x91) {return 0x41;}  if((charL>=0x80) && (charL<=0x8F)){return (charL-0x50);}}; return charL;}; 
//=================================================================================================
//						       		10.5.Cursor address calculation
//=================================================================================================
uint8_t pointCursor(uint8_t num, uint8_t vCol, uint8_t vRow){ 
if(ptr[num]->cols<=8) {return (((vCol-1)+RT_HW_READ_BYTE_PGM(RT_HW_LCD44780_ROW_SET_8, (vRow-1)))|0x80);}
if(ptr[num]->cols<=16){return (((vCol-1)+RT_HW_READ_BYTE_PGM(RT_HW_LCD44780_ROW_SET_16,(vRow-1)))|0x80);}
if(ptr[num]->cols<=20){return (((vCol-1)+RT_HW_READ_BYTE_PGM(RT_HW_LCD44780_ROW_SET_20,(vRow-1)))|0x80);}
if(ptr[num]->cols<=40){return (((vCol-1)+RT_HW_READ_BYTE_PGM(RT_HW_LCD44780_ROW_SET_40,(vRow-1)))|0x80);}
return 0x80;}
//=================================================================================================
//						  			10.6.Getting the number of blank before the output field
//=================================================================================================
uint8_t getLenBegin(RT_HW_LCD44780_PARAM_ID &id){ 
id.buff=id.msLenHead+id.msLenVar+id.msLenSuff;
if(id.len<=id.buff){return 0;} if(id.alig=='C'){return(id.len-id.buff-(id.len-id.buff)/2);} 
                               if(id.alig=='R'){return(id.len-id.buff);} return 0;};  
//=================================================================================================
//						  			10.7.Getting the number of blank after the output field
//=================================================================================================
uint8_t getLenEnd  (RT_HW_LCD44780_PARAM_ID &id){
id.buff=id.msLenHead+id.msLenVar+id.msLenSuff;
if(id.len<=id.buff){return 0;} if(id.alig=='C'){return(id.len-id.buff-getLenBegin(id));} 
                               if(id.alig=='L'){return(id.len-id.buff);} return 0;};  
//=================================================================================================
//						  10.8.Getting the code char from PROGMEM utf-8 
//=================================================================================================
uint8_t getCodeCharLcdPGM(uint8_t code){
	return pgm_read_byte(RT_HW_LCD44780_CONVERT_RUS+code);};
//=================================================================================================
//						  10.9.Getting the len text for String (utf-8)
//=================================================================================================
uint8_t getLenSTR(String &str,     uint8_t lenMax){							
uint8_t buff,j,len; if(lenMax==0) {lenMax=80;} j=len=0;
while (1) {buff=str[j];	         if(buff>=0xC0) {j++; buff=str[j];}  j++;	
           if((buff==0) || (buff==RT_HW_BREAK_CHAR) || (len>lenMax) || (j>160)) {break;} 
		   if(buff>=0xC0) {j++;} //buff=str(j);
		   len++;} 		   
		   //len++;} 
return len;}
//=================================================================================================
//						  10.10.Getting the len text for Text PROGMEM (utf-8)
//=================================================================================================
uint8_t getLenPGM(const char *text,uint8_t lenMax){	
	uint8_t buff,j,len; if(lenMax==0) {lenMax=80;} j=len=0;
while (1) {buff=pgm_read_byte(text+j);	j++;
		   if((buff==0) || (buff==RT_HW_BREAK_CHAR) || (len>lenMax) || (j>160)) {break;}
		   if(buff>=0xC0) {j++;} //buff=pgm_read_byte(text+j);
		   len++;} 
return len;}
//=================================================================================================
//						  10.11.Getting the following String code (utf-8) in Lcd format
//=================================================================================================
uint8_t getCharLcdSTR(String str,       uint8_t &xSrc){	
uint8_t buff1=str[xSrc]; uint8_t buff2=0; xSrc++; 
if(buff1>=0xC0){buff2=str[xSrc]; xSrc++; return getCodeCharLcdPGM(convert(buff1,buff2));} else {return buff1;}}
//=================================================================================================
//						  10.12.Getting the following Text of PROGMEM code (utf-8) in Lcd format
//=================================================================================================
uint8_t getCharLcdPGM(const char *text, uint8_t &xSrc){
uint8_t buff1=pgm_read_byte(text+xSrc);; uint8_t buff2=0; xSrc++;
if(buff1>=0xC0) {buff2=pgm_read_byte(text+xSrc); xSrc++; return getCodeCharLcdPGM(convert(buff1,buff2));} 
else            {return buff1;}}
//=================================================================================================
//						  10.13.Getting String for bit
//=================================================================================================
String  getSignBit    (uint16_t var, uint8_t idx){if(bitRead(var,idx)) {return String("+");} else {return String("-");}} 
//=================================================================================================
//						  10.14.Getting char fo bit by number code table character to display the bit
//=================================================================================================
char    getSignBitCode(uint8_t code, uint8_t v){
if(v){return (char)RT_HW_READ_BYTE_PGM(RT_HW_ARR_BOOL_SIGN_1,code);} 
else {return (char)RT_HW_READ_BYTE_PGM(RT_HW_ARR_BOOL_SIGN_0,code);}};
//=================================================================================================
//=================================================================================================
uint8_t checkNum (uint8_t num){if((num!=0) && (num<=hive.qnt)){return 1;} else{return 0;}}  //--Check number device;		
uint8_t getBusy  (uint8_t num){if(ptr[num]->busy){return 0;} ptr[num]->busy=1; return 1;}	//--Device capture;  		
void    clearBusy(uint8_t num){ptr[num]->busy=0; ptr[num]->cntWatchDogBusy=0;}//--Release device with watchdog reset;
//=================================================================================================
uint8_t getCols  (uint8_t code){return code/10;};				//--Getting the number of columns (format type 204);
uint8_t getRows  (uint8_t code){return (code-((code/10)*10));};	//--Getting the number of rows    (format type 204);
//=================================================================================================
uint8_t timeToTick(uint16_t time, uint8_t tick){if((tick*255)>=time){return time/tick;} else {return 255;}};//--Convert time(ms) to ticks(50ms);
uint8_t getGenState(uint8_t num){if(!checkNum(num)){return 4;} else {return ptr[num]->genState;}}; 			//--Getting display state;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
