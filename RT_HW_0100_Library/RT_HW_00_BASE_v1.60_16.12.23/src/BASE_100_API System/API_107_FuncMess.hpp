//#################################################################################################
//
//                       ФУНКЦИИ ДЛЯ РАБОТЫ С СООБЩЕНИЯМИ mess(для консоли)
//  mode:                             '0'  '1'  '2'  '3'  '4'  '5'  '6'  '7'  '8'  '9' 
//  RT_HW_ARR_BOOL_SIGN_1[] PROGMEM= {'1', '+', '*', '#', '|', '>', '+', '*', '+', 255};  
//  RT_HW_ARR_BOOL_SIGN_0[] PROGMEM= {'0', '-', ' ', ' ', '-', '<', '_', '_', ' ', ' '}; 
//			
//#################################################################################################
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                      	    	 1.КОНВЕРТИРОВАНИЕ ПЕРЕМЕННЫХ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//							1.1.Конвертирование v8 [mode:P,A,X,T,C,F,B,H,U,I,Z,z,0,1]
//=================================================================================================
void varToMess(RT_HW_STRUCT_MESS &id,  int8_t v, char suff='~', uint8_t size=0, char mode='Z', String head="~"){
	                                                  varToMess(id,(uint8_t)v,suff,size,mode,head);};
//=================================================================================================
void varToMess(RT_HW_STRUCT_MESS &id, uint8_t v, char suff='~', uint8_t size=0, char mode='Z', String head="~"){
messParamStore(id,suff,size,mode,head,'B');							//--Подготовка и сохранение параметров mess;
//-------------------------------------------------------------------------------------------------
if(mode=='P') {byteToPin(id,v);}				//--Номер(modePin=D),имя(modePin=T),имя+номер(modePin=A) пина;
if(mode=='A') {byteToAdr(id,v);}				//--Адрес i2c:modeAdr=D-DEC, modeAdr=H-HEX, modeAdr=A-DEC/HEX; 
if(mode=='X') {byteToLine(id,v);}								//--Линия BAR(0-100%)[линейный индикатор];
if(mode=='T') {byteToTime(id,v);}								//--Формат времени;
if(mode=='C') {byteToChar(id,v);} 								//--Символ в числовой форме;
//-------------------------------------------------------------------------------------------------
if(mode=='F') {varToBin(id,v,'F');}								//--Побитовый вид, впереди старший байт; 
if(mode=='B') {varToBin(id,v,'B');}								//--Побитовый вид, впереди младший байт; 			
if(mode=='H') {varToHex(id,v);}       							//--Шестнадцатеричный вывод в формате 0xFF;
if(mode=='h') {varToHex(id,v);}       							//--Шестнадцатеричный вывод в формате   FF;
//-------------------------------------------------------------------------------------------------
if(mode=='U') {id.str+=String(v);}								//--Формат uint8_t(0    - +255); 								
if(mode=='I') {id.str+=String(int8_t(v));}						//--Формат (int8_t(-128 - +127)); 	
if(mode=='Z') {id.str+=String(int8_t(v));}						//--Формат uint8_t(0    - +255) без форматирования;
if(mode=='z') {id.str+=String((uint8_t)v);}						//--Формат  int8_t(-128 - +127) без форматирования;
if(mode=='0') {id.str+=String((int8_t)v/1.0, 1);}				//--Формат  float без     знака  после точки
if(mode=='1') {id.str+=String((int8_t)v/10.0,1);}				//--Формат  float с одним знаком после точки
//-------------------------------------------------------------------------------------------------
messParamReStore(id);}											//--Сохранение параметров id; 
//=================================================================================================
//							1.2.Конвертирование v16 [mode:F,B,H,U,I,Z,z,0,1,2,3]
//=================================================================================================
void varToMess(RT_HW_STRUCT_MESS &id,uint16_t v, char suff='~', uint8_t size=0, char mode='Z', String head="~"){
	                                                  varToMess(id,(int16_t)v,suff,size,mode,head);};
void varToMess(RT_HW_STRUCT_MESS &id, int16_t v, char suff='~', uint8_t size=0, char mode='Z', String head="~"){
messParamStore(id,suff,size,mode,head,'W');							//--Подготовка и сохранение параметров id;
//-------------------------------------------------------------------------------------------------
if(mode=='F') {varToBin(id,v,'F');}								//--Побитовый вид, впереди старший байт; 
if(mode=='B') {varToBin(id,v,'B');}								//--Побитовый вид, впереди младший байт; 			
if(mode=='H') {varToHex(id,v);}       							//--Шестнадцатеричный вывод в формате 0xFFFF;
if(mode=='h') {varToHex(id,v);}       							//--Шестнадцатеричный вывод в формате   FFFFF;
//-------------------------------------------------------------------------------------------------
if(mode=='U') {id.str+=String((uint16_t)v);}					//--Формат uint16_t(0      - +65535); 								
if(mode=='I') {id.str+=String(v);}							    //--Формат  int16_t(-32768 - +32767)); 	
if(mode=='Z') {id.str+=String(uint16_t(v));}					//--Формат uint16_t(0      - +65535) без форматирования;
if(mode=='z') {id.str+=String(v);}								//--Формат  int16_t(-32768 - +32767) без форматирования;
if(mode=='0') {id.str+=String(((float)v)/1.0,      0);}			//--Формат  float без     знака  после точки;
if(mode=='1') {id.str+=String(((float)v)/10.0,     1);}			//--Формат  float с одним знаком после точки;
if(mode=='2') {id.str+=String(((float)v)/100.0,    2);}			//--Формат  float с двумя знаками после точки;
if(mode=='3') {id.str+=String(((float)v)/1000.0,   3);}			//--Формат  float с тремя знаками после точки;
if(mode=='4') {id.str+=String(((float)v)/10000.0,  4);}			//--Формат  float без     знака  после точки;
if(mode=='5') {id.str+=String(((float)v)/100000.0, 5);}			//--Формат  float с одним знаком после точки;
if(mode=='6') {id.str+=String(((float)v)/1000000.0,6);}			//--Формат  float с двумя знаками после точки;
//-------------------------------------------------------------------------------------------------
messParamReStore(id);};											//--Сохранение параметров id; 
//=================================================================================================
//							1.3.Конвертирование v32 [mode:F,B,H,U,I,Z,z,0,1,2,3]
//=================================================================================================	
void varToMess(RT_HW_STRUCT_MESS &id,uint32_t v, char suff='~', uint8_t size=0, char mode='Z', String head="~"){
	                                varToMess(id,(int32_t)v,suff,size,mode,head);};
//=================================================================================================
void varToMess(RT_HW_STRUCT_MESS &id, int32_t v, char suff='~', uint8_t size=0, char mode='Z', String head="~"){	
messParamStore(id, suff,size,mode,head,'L');								//--Подготовка и сохранение параметров mess;
//-------------------------------------------------------------------------------------------------
if(mode=='F') {varToBin(id,v,'F');}								//--Побитовый вид, впереди старший байт; 
if(mode=='B') {varToBin(id,v,'B');}								//--Побитовый вид, впереди младший байт; 			
if(mode=='H') {varToHex(id,v);}       							//--Шестнадцатеричный вывод в формате 0xFFFFFFFF;
if(mode=='h') {varToHex(id,v);}       							//--Шестнадцатеричный вывод в формате   FFFFFFFF;
//-------------------------------------------------------------------------------------------------
if(mode=='U') {id.str+=String((uint32_t)v);}					//--Формат uint16_t(0-65535); 								
if(mode=='I') {id.str+=String(v);}								//--Формат  int16_t(-32768 - +32767)); 	
if(mode=='Z') {id.str+=String(uint32_t(v));}					//--Формат uint16_t(0-65535)         без форматирования;
if(mode=='z') {id.str+=String(v);}								//--Формат  int16_t(-32768 - +32767) без форматирования;
if(mode=='0') {id.str+=String(v/1.0,   1);}						//--Формат  float без     знака  после точки;
if(mode=='1') {id.str+=String(v/10.0,  1);}						//--Формат  float с одним знаком после точки;
if(mode=='2') {id.str+=String(v/100.0, 2);}						//--Формат  float с двумя знаками после точки;
if(mode=='3') {id.str+=String(v/1000.0,3);}						//--Формат  float с тремя знаками после точки;
//-------------------------------------------------------------------------------------------------
messParamReStore(id);};											//--Сохранение параметров id; 
//=================================================================================================
//							1.4.Конвертирование float [mode:0,1,2,3,Z]
//=================================================================================================
void varToMess(RT_HW_STRUCT_MESS &id,   float v, char suff='~', uint8_t size=0, char mode='2', String head="~"){
messParamStore(id,suff,size,mode,head,'F');						//--Подготовка и сохранение параметров mess;
//-------------------------------------------------------------------------------------------------			
if(mode=='0') {id.str+=String(v,0);}							//--Формат  float без     знака  после точки;
if(mode=='1') {id.str+=String(v,1);}							//--Формат  float с одним знаком после точки;
if(mode=='2') {id.str+=String(v,2);}							//--Формат  float с двумя знаками после точки;
if(mode=='3') {id.str+=String(v,3);}							//--Формат  float с тремя знаками после точки;
if(mode=='Z') {id.str+=String(v);}								//--Формат  float по умолчанию(оюычно два с знака после точки);	
messParamReStore(id);};											//--Сохранение параметров id; 
//=================================================================================================
//							1.5.Конвертирование переменной String [U,L,Z]
//=================================================================================================
void varToMess(RT_HW_STRUCT_MESS &id, String  v, char suff='~', uint8_t size=0, char mode='S', String head="~"){ 	
messParamStore(id,suff,size,mode,head,'S');							//--Подготовка и сохранение параметров mess;
//-------------------------------------------------------------------------------------------------	
id.str+=v; 														//--	
if(mode=='U') {id.str.toUpperCase();}							//--
if(mode=='L') {id.str.toLowerCase();}							//--
//-------------------------------------------------------------------------------------------------
messParamReStore(id);};											//--Сохранение параметров id; 
//=================================================================================================
//							1.6.Конвертирование переменной char
//=================================================================================================
void varToMess(RT_HW_STRUCT_MESS &id, char    v, char suff='~', uint8_t size=0, char mode='1', String head="~"){	
messParamStore(id,suff,size,mode,head,'C');							//--Подготовка и сохранение параметров mess;
//-------------------------------------------------------------------------------------------------	
id.str=String(v); 	
//-------------------------------------------------------------------------------------------------
messParamReStore(id);};											//--Сохранение параметров id;
//=================================================================================================
//							1.7.Конвертирование переменной bool
//=================================================================================================
void varToMess(RT_HW_STRUCT_MESS &id, bool    v, char suff='~', uint8_t size=0, char mode='1', String head="~"){
messParamStore(id,suff,size,mode,head,'R');							//--Подготовка и сохранение параметров mess;
//-------------------------------------------------------------------------------------------------	
//id.signBit=mode; 												//--Установка выбора выводимых символов;
messGetIndex(id);												//--Расчет mess.index;
 if(v){id.str =String((char)RT_HW_READ_BYTE_PGM(RT_HW_ARR_BOOL_SIGN_1,id.index));} 
 else {id.str+=String((char)RT_HW_READ_BYTE_PGM(RT_HW_ARR_BOOL_SIGN_0,id.index));}
messParamReStore(id);};											//--Сохранение параметров id; 


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                      			2.ФУНКЦИИ ФОРМАТИРОВАНИЯ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//							2.1.Сохранение параметров mess и предварительная обработка
//=================================================================================================
//--------------------------2.1.Сохранение параметров mess и предварительная обработка-------------
void messParamStore(RT_HW_STRUCT_MESS &id, char suff, uint8_t size, char mode, String head, char modeVar){
//id.agoAlig=id.alig; id.agoBlank=id.blank; id.agoSignBit=id.signBit;	//--Сохранение внешних параметров;
id.size=size; id.mode=mode; id.modeVar=modeVar;			//--Запись в mess параметров;
if((id.size==0) || (id.mode=='Z') || (id.mode=='z')){id.alig='N';} //--Корректировка alig;
//-------------------------------------------------------------------------------------------------	
if(head=="~"){id.str="";} else {id.str=head;}			//--Инициализация  строки;
//id.str="";
//-------------------------------------------------------------------------------------------------
messSuff(id,suff);}										//--Обработка суффикса;
//=================================================================================================
//							2.2.Завершающая обработка и восстановление параметров mess
//=================================================================================================
void messParamReStore(RT_HW_STRUCT_MESS &id){
//-------------------Вычисление длины текстового буфера,для String с учетом кодировки UTF-8'-------
const char * data=id.str.c_str(); 											//--Установка указателя на начало строки;
id.lenVar=0;
for(id.idx=0; id.idx<=160; id.idx++){id.bf8=data[id.idx]; id.qnt=id.idx;  
							         if((id.bf8=='\0') || (id.bf8==RT_HW_BREAK_CHAR) || (id.lenVar>=80)) {break;}
								     if((id.bf8=='\0') || (id.bf8==RT_HW_BREAK_CHAR)) {break;}									
						             if( id.bf8<0xC0) {id.lenVar++;}} 
//--------------------------------------------------------------------------------------------------
id.lenBegin=id.lenEnd=0;						//--Очистка параметров;
if(id.alig!='N'){
if(id.lenVar>=id.size){id.lenSuff=0;}			//--Запрет вывода суффикса, если не достаточный размер поля
if(id.lenVar> id.size){id.lenVar=id.size;}		//--Ограничение длины сообщения;
if(id.alig=='C'){id.lenBegin=id.size-(id.lenVar+id.lenSuff)-(id.size-(id.lenVar+id.lenSuff))/2; //--Кол-во передних заполнителей;
                 id.lenEnd  =id.size-(id.lenVar+id.lenSuff)-id.lenBegin;}	//--Кол-во задних   заполнителей;
if(id.alig=='R'){id.lenBegin=id.size-(id.lenVar+id.lenSuff);} 				//--Кол-во передних заполнителей;  
if(id.alig=='L'){id.lenEnd  =id.size-(id.lenVar+id.lenSuff);}  				//--Кол-во задних   заполнителей
}
//-------------------------------------------------------------------------------------------------
//id.alig=id.agoAlig; id.blank=id.agoBlank; id.signBit=id.agoSignBit;
messDefault(id);
};	
//=================================================================================================
//							2.3.Обработка суффикса
//================================================================================================= 
void messSuff(RT_HW_STRUCT_MESS &id, char suff='~'){
if(suff=='~'){id.lenSuff=0; id.lenCR=0; id.suff='~'; return;}
if(suff=='L'){id.lenSuff=0; id.lenCR=1; id.suff='~'; return;}				
if(suff=='E'){id.lenSuff=1; id.lenCR=1; id.suff=';'; return;} 	
              id.lenSuff=1; id.lenCR=0; id.suff=suff;};
//=================================================================================================
//							2.4.Получение индекса таблицы RT_HW_ARR_BOOL_SIGN_x
//=================================================================================================
void messGetIndex(RT_HW_STRUCT_MESS &id){
	id.index=(uint8_t)id.signBit; if(id.index<48){id.index=48;} id.index=id.index-48; if(id.index>9){id.index=1;}};
//=================================================================================================
//							2.5.Установка параметров default
//=================================================================================================
void messDefault(){messDefault(mess);};
void messDefault(RT_HW_STRUCT_MESS &id){
id.alig='L'; id.signBit='1'; id.hexShort=0; id.qntBit=8; 
//mess.modePin='A'; mess.modeAdr='A';
//mess.mode='Z';	 			
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//						    3.Доп.функции для форматов BIN,HEX,BAR,Time,Char,Pin,Adr.i2c
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//								3.1.Конвертирование var->строковый BIN
//=================================================================================================
void varToBin  (RT_HW_STRUCT_MESS &id, uint32_t v, char vOrder='F'){
//-----Определение индекса таблицы с символами для отображения 0/1---------------------------------
messGetIndex(id);
//-----Определение длины поля выводимого поля------------------------------------------------------
id.qnt=0; 
if(id.modeVar=='B'){id.qnt=8;} 
if(id.modeVar=='W'){id.qnt=16;} 
if(id.modeVar=='L'){id.qnt=32;}
if(id.qnt==0){return;}
//-----Реверс переменной---------------------------------------------------------------------------
if(vOrder=='B'){if(id.modeVar=='B'){v=reverseV8 ((uint8_t) (v&0xFF));}
				if(id.modeVar=='W'){v=reverseV16((uint16_t)(v&0xFFFF));}
				if(id.modeVar=='L'){v=reverseV32((uint32_t)(v));}} 
//-------------------------------------------------------------------------------------------------
if(id.index==0){id.str=String('b');} 
for(id.idx=1; id.idx<=id.qnt; id.idx++) {
 if(bitRead(v,(id.qnt-id.idx))){id.str+=String((char)RT_HW_READ_BYTE_PGM(RT_HW_ARR_BOOL_SIGN_1,id.index));} 
 else                          {id.str+=String((char)RT_HW_READ_BYTE_PGM(RT_HW_ARR_BOOL_SIGN_0,id.index));}} 
};
//=================================================================================================
//								3.2.Конвертирование var->строковый BIN
//=================================================================================================
void varToHex  (RT_HW_STRUCT_MESS &id, uint32_t v){
if(id.modeVar=='B'){id.str=String(v,HEX);           id.str.toUpperCase(); 
                    if(v<=0xF){id.str="0"+id.str;}}
//--------------------------------------------------------------------------------------------------
if(id.modeVar=='W'){id.str=String((uint16_t)v,HEX); id.str.toUpperCase(); id.bf8=id.str.length(); 
                    for(id.idx=id.bf8; id.idx<4; id.idx++){id.str="0"+id.str;}}
//--------------------------------------------------------------------------------------------------
if(id.modeVar=='L'){id.str=String((uint32_t)v,HEX); id.str.toUpperCase(); id.bf8=id.str.length(); 
                    for(id.idx=id.bf8; id.idx<8; id.idx++){id.str="0"+id.str;}}
//--------------------------------------------------------------------------------------------------
if(id.mode=='H'){id.str="0x"+id.str;}     //--Шестнадцатеричный вывод в формате 0xFF,0xFFFF,0xFFFFFFFF;
};
//=================================================================================================
//								3.3.Конвертирование v8(0-100%)->строку типа BAR(полоса)
//=================================================================================================
void byteToLine(RT_HW_STRUCT_MESS &id, uint8_t v){ 	
//-----Определение индекса таблицы с символами для отображения 0/1---------------------------------
messGetIndex(id); 
//-----Расчет длины линии--------------------------------------------------------------------------
if(v>100){id.qnt=100;} else{id.qnt=v;}
id.qnt=((uint16_t)id.qnt*id.qntBit)/100;
if((v>0) && (id.qnt==0)){id.qnt=1;}
//-----Формирование строки-------------------------------------------------------------------------
for(id.idx=0; id.idx<id.qnt; id.idx++){id.str+=String((char)RT_HW_READ_BYTE_PGM(RT_HW_ARR_BOOL_SIGN_1,id.index));}} ;
//=================================================================================================
//								3.4.Конвертирование v8 в формат времени
//=================================================================================================
void byteToTime(RT_HW_STRUCT_MESS &id, uint8_t v){
id.str=String(v); if(v<10) {id.str=String("0")+id.str;}};
//=================================================================================================
//								3.5.Конвертирование char в число
//=================================================================================================
void byteToChar(RT_HW_STRUCT_MESS &id, uint8_t v){id.str=String(char(v));};
//=================================================================================================
//								3.6.Формирование имени/номера пина (T,A,D)
//=================================================================================================
void byteToPin(RT_HW_STRUCT_MESS &id, uint8_t v){
//-------------------------------------------------------------------------------------------------
if(id.size<3) {id.size=3;}
#if defined(RT_HW_CORE_STM32)	
if(id.modePin=='T') {if(id.size<5) {id.size=5;} id.alig='L'; id.str=getNamePin(v);                 return;}
if(id.modePin=='A') {if(id.size<9) {id.size=9;} id.alig='L'; id.str=getNamePin(v)+String('['); 
	                 if(v<254){id.str+=String(v);} else{id.str+=String('*');} id.str+=String(']'); return;}
if(id.modePin=='D') {if(v<254){id.str+=String(v);} else{id.str+=String('*');}                      return;}                    
id.str+=String('*'); return;
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_CORE_ESP8266)
if(id.modePin=='T') {if(id.size<3) {id.size=3;} id.str=getNamePin(v)+" "; return;}
if(id.modePin=='A') {if(id.size<7) {id.size=7;} id.str=getNamePin(v)+String('['); 
                     if(v<254){id.str+=String(v);} else{id.str+=String('*');} id.str+=String(']'); return;}
if(id.modePin=='D') {if(v<254){id.str+=String(v);} else{id.str+=String('*');} return;}                    
id.str+=String('*'); return;
#endif
//-------------------------------------------------------------------------------------------------
if(v<254){id.str+=String(v);} else{id.str= String(' ')+String('*');} return; //--Вывод для всех контроллеров кроме STM32,ESP8266; 	 		 		  
};
//=================================================================================================
//								3.7.Формирование имени адреса i2c (H,A,D)
//=================================================================================================
void byteToAdr(RT_HW_STRUCT_MESS &id, uint8_t v){
//-------------------------------------------------------------------------------------------------
if((id.modeAdr=='H') || (id.modeAdr=='A')){id.str+=String("0x"); if(v<0x0F) {id.str+=String("0");} id.str+=String(v,HEX); 
                      if(id.modeAdr=='A') {id.str+=String('/')+String(v);}  return;} 
//-------------------------------------------------------------------------------------------------
id.str=String(v); return;};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//						    		4.СЕРВИСНЫЕ ФУНКЦИИ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void messDebug(){messDebug(mess);};
void messDebug(RT_HW_STRUCT_MESS &id){
Serial.print(String(F("Debug->")));
Serial.print(String(F("qnt=")));    		Serial.print(String(id.qnt)); 
Serial.print(String(F("; alig=")));    		Serial.print(String(id.alig));  		
Serial.print(String(F("; mode=")));    		Serial.print(String(id.mode));		
Serial.print(String(F("; modeVar="))); 		Serial.print(String(id.modeVar));
Serial.print(String(F("; suff=")));    		Serial.print(String(id.suff));    		
Serial.print(String(F("; LEN->begin=")));	Serial.print(String(id.lenBegin));
Serial.print(String(F(",var=")));      		Serial.print(String(id.lenVar));
Serial.print(String(F(",end=")));       	Serial.print(String(id.lenVar));
Serial.print(String(F(",suff="))); 	    	Serial.print(String(id.lenSuff));
Serial.print(String(F(",cr=")));   			Serial.print(String(id.lenCR)); 
Serial.print(String(F("; str=")));   		Serial.print(String(id.str));
Serial.println(String(F(";")));
};

//#################################################################################################
//                       5.ФУНКЦИИ ДЛЯ РАБОТЫ со строковыми переменными
//								(требуют доработки)
//#################################################################################################
uint8_t getNumberVal(uint32_t var, char mode, uint8_t len, uint8_t n){	//==Получение цифры из var(форматы mode=D,H,B) ее номеру(1:10) (начиная со старшей позиции);
uint32_t buff32=0;
if((n>len) || (n>10)) n=0; 
if(mode=='B') {buff32=(var>>(len-n))&1;}
if(mode=='H') {buff32=(var>>(len-n)*4)&0xf;}
if(mode=='D') {n=len-n+1; while(n!=0) {buff32=var; var/=10; buff32=buff32-(var*10); n--;};}
//if(buff32<=9) {buff32=buff32 +'0';} else {buff32=buff32-10+(upper ? 'A' : 'a') ;}
return (uint8_t)buff32;};
uint8_t getLenVal   (char mode, int32_t var){			                //==Получение кол-ва знаков в числе с оcнованиями 10,16,2 (DEC(I,U),HEX,BIN):
uint32_t v, buff; uint8_t len=0; uint8_t bs;
if(mode=='I') {if(var<0) {v=-var;} else {v=var;}	
								buff=bs=10;  len=1; for(int8_t i=0;i<10;i++) {if(v<buff){break;} buff=buff*bs; len++;} if(var<0) {len++;}} 
if(mode=='U') {v=(uint32_t)var; buff=bs=10;  len=1; for(int8_t i=0;i<10;i++) {if(v<buff){break;} buff=buff*bs; len++;}} 
if(mode=='H') {v=(uint32_t)var;	buff=bs=0xF; len=1; for(int8_t i=0;i<10;i++) {if(v<buff){break;} buff=buff*bs; len++;}} 
return len;};
//=================================================================================================
int16_t getNumberFromString(String var, uint8_t n, char separator) {	//==Получение числа int16 из строки с разделителями(DEBUG !!!);
//--n позиция в строке начиная с 1. Если значения нет или =0, возвращает -32768;
int16_t x; int16_t findPoint; uint8_t startPoint,endPoint, len,i; String s;
 startPoint=endPoint=findPoint=0;  s=var; len=var.length();
 x=-32768;
 if(n==0) {return x;} i=1;
 do{if(i>n) break;
    if(startPoint>len) break;
	findPoint=var.indexOf(separator, startPoint);   
	if (findPoint==-1) {endPoint=len;} else {endPoint=findPoint;}
	if (n==i) {s=var.substring(startPoint,endPoint); s.trim(); if(s=="") {break;} x=s.toInt(); break;}  
	if (findPoint==-1)  break;
	startPoint=findPoint+1;	i++; 	
   } while (1);
return x;}	
//=================================================================================================
String  getTextFromString  (String var, uint8_t n, char separator) {  	//==Получение текст (через разделители) из строки (DEBUG !!!);
//--n позиция в строке начиная с 1. Если значения нет или пробел, возвращает один пробел;
int16_t findPoint; 
uint8_t startPoint=0; 
uint8_t endPoint=0;
String x="";
String s=var; 
uint8_t len=var.length(); 									//--Длина строки;
uint8_t index=0;
do{if(index>n) {break;}
    if(startPoint>len) {break;}
	findPoint=var.indexOf(separator, startPoint);   
	if (findPoint==-1) {endPoint=len;} else {endPoint=findPoint;}
	if (n==index) {s=var.substring(startPoint,endPoint); s.trim(); 
				   if(s=="") {break;} 
				   x=s;       break;}  
	if (findPoint==-1)  {break;}
	startPoint=findPoint+1;	index++; 	
   } while (1);
return x;}
//=================================================================================================
/*
// получить число под индексом idx в списке list с разделителем div
int16_t getNumberFromStringnumFromList(char* list, int idx, char div) {
    uint8_t count = 0;
    char* p = list;
    while (1) {
        if (count++ == idx) return atoi(p);
        p = strchr(p, div);
        if (!p++) break;
    }
    return 0;
}
*/
//=================================================================================================