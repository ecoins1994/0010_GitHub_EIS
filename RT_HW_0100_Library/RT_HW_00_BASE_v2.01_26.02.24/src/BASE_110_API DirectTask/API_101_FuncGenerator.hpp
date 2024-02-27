//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//										1.ГЕНЕРАТОРЫ
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//							1.1.Генератор события по изменению фронта EN [F,C,B,H,D,N]
//	Вход: ago-рабочий регистр, EN-внешний вход, mode-режим работы.
//	Выход: возвращаемое значение bool;
//=================================================================================================
bool generatorChangeEN(uint8_t &ago, char mode, uint8_t EN=1){	
if(mode=='F') {if(ago!=EN) {ago=EN; if( EN) {return 1;}}}	//--Выделение заднего фронта;	
if(mode=='C') {if(ago!=EN) {ago=EN;          return 1;}}	//--Выделение изменения сигнала;	
if(mode=='R') {if(ago!=EN) {ago=EN; if(!EN) {return 1;}}}	//--Выделение переднего фронта;	
if(mode=='H') {								 return EN;}    //--По высокому уровню;
if(mode=='L') {								 return (!EN);} //--По низкому уровню;                
return 0;};
//=================================================================================================
//							1.2.Генератор событий ms
//	Вход: id-рабочая структура, EN-внешний вход, period-периодичность.
//	Выход: возвращаемое значение bool=id.event;
//		   id.event-событие; id.meander-меандр.
//=================================================================================================
bool generatorEvent(RT_HW_GENERATOR_EVENT_ID &id, uint16_t period, uint8_t EN=1){
id.event=0;
if(id.dir==0) {id.time=millis(); id.event=id.meander=1; id.dir++;}
if(id.dir==1) {if(EN) {id.dir++;} else {id.event=id.meander=0; id.time=RT_HW_MILLIS;}}
if(id.dir==2) {if(periodMs(id.time,period)) {id.event=1; if(EN) {id.meander=!id.meander;} else {id.meander=0;} id.dir=1;}} 
return id.event;}; 
//=================================================================================================
//							1.3.Генератор событий mcs
//	Вход: id-рабочая структура, EN-внешний вход, period-периодичность.
//	Выход: возвращаемое значение bool=id.event;
//		   id.event-событие; id.meander-меандр.
//=================================================================================================
bool generatorEventMcs(RT_HW_GENERATOR_EVENT_ID &id, uint32_t period, uint8_t EN=1){
id.event=0;
if(id.dir==0) {id.time=micros(); id.event=id.meander=1; id.dir++;}
if(id.dir==1) {if(EN) {id.dir++;} else {id.event=id.meander=0; id.time=RT_HW_MICROS;}}
if(id.dir==2) {if(periodMcs(id.time,period)) {id.event=1; if(EN) {id.meander=!id.meander;} else {id.meander=0;} id.dir=1;}} 
return id.event;}; 
 
//=================================================================================================
//							1.3.Генератор импульсов uint16_t
//	Вход: id-рабочая структура, EN-внешний вход, timeON-время включения в ms, timeOFF-время выключения в ms.
//	Выход: возвращаемое значение bool -генерируемый импульс.
//=================================================================================================  
bool  generatorPulse(RT_HW_GENERATOR_PULSE_ID &id, uint16_t timeON, uint16_t timeOFF, uint8_t EN=1){		//==Генератор импульсов (v16);
if(id.dir==0) {if(EN) {id.dir=3;} else {return 0;}}
if(id.dir==1) {if(RT_HW_MILLIS>=id.time) {id.time+=timeOFF; id.dir=2; return 0;} else {return 1;}}
if(id.dir==2) {if(RT_HW_MILLIS>=id.time) {id.dir=3;}}
if(id.dir==3) {if(EN) {id.time=millis()+timeON; 		id.dir=1; return 1;}
			   else 								   {id.dir=0; return 0;}}	   return 0;};
//=================================================================================================
//							1.4.Генератор импульсов uint32_t
//	Вход: id-рабочая структура, EN-внешний вход, timeON-время включения в ms, timeOFF-время выключения в ms.
//	Выход: возвращаемое значение bool -генерируемый импульс.
//================================================================================================= 
bool generatorPul32(RT_HW_GENERATOR_PULSE_ID &id, uint32_t timeON, uint32_t timeOFF, uint8_t EN=1){		//==Генератор импульсов (v32);		
if(id.dir==0) {id.dir=3;}
if(id.dir==1) {if((RT_HW_MILLIS-id.time)>= timeON) 			{id.dir=2; 	 return 0;} else {return 1;}}
if(id.dir==2) {if((RT_HW_MILLIS-id.time)>=(timeON+timeOFF)) {id.dir=3;}}
if(id.dir==3) {if(!EN) 		 {return 0;} id.time=RT_HW_MILLIS; 
			   if(timeON ==0){return 0;} 
			   if(timeOFF==0){return 1;}
			   id.dir=1; 	  return 1;}	return 0;}
//=================================================================================================
//							1.5.Генератор импульсов uint32_t
//	Вход: id-рабочая структура, timeON-время включения в ms, timeOFF-время выключения в ms.
//	Выход: возвращаемое значение bool -генерируемый импульс.
//================================================================================================= 
bool generatorPul32mcs(RT_HW_GENERATOR_PULSE_ID &id, uint32_t timeON, uint32_t timeOFF, uint8_t EN=1){		//==Генератор импульсов (v32);		
if(id.dir==0) {id.dir=3;}
if(id.dir==1) {if((RT_HW_MICROS-id.time)>= timeON) 			{id.dir=2; 	 return 0;} else {return 1;}}
if(id.dir==2) {if((RT_HW_MICROS-id.time)>=(timeON+timeOFF)) {id.dir=3;}}
if(id.dir==3) {if(!EN) 		 {return 0;} id.time=micros(); 
			   if(timeON ==0){return 0;} 
			   if(timeOFF==0){return 1;}
			   id.dir=1; 	  return 1;}	return 0;}
//=================================================================================================
//							1.6.Генератор PWW(период ms, скважность)
//	Вход: id-рабочая структура, timeON-время включения в ms, timeOFF-время выключения в ms.
//	Выход: возвращаемое значение bool -генерируемый импульс.
//================================================================================================= 			   
bool generatorPWM  (RT_HW_GENERATOR_PWM_ID   &id, uint32_t period, uint8_t wprc, uint8_t EN=1){ 			//==Генератор PWM;
if(id.dir==0) {id.dir=3;}
if(id.dir==1) {if((RT_HW_MILLIS-id.time)>= id.timeON) 	 {id.dir=2; 	 return 0;} else {return 1;}}
if(id.dir==2) {if((RT_HW_MILLIS-id.time)>=(id.timeFULL)) {id.dir=3;}}
if(id.dir==3) {if(!EN) 		    {return 0;} id.time=RT_HW_MILLIS; 
			   if(period==0)    {return 0;}			   
			   if(wprc==0) 	    {return 0;} 
			   if(wprc>=100) 	{return 1;} 
			   id.timeFULL=period; 			  
			   id.timeON=(((uint32_t)period*wprc)/100); 
			   id.dir=1; return 1;}		return 0;}
//=================================================================================================
//							1.7.Генератор PWW (период mcs, скважность)
//	Вход: id-рабочая структура, timeON-время включения в mсs, timeOFF-время выключения в ms.
//	Выход: возвращаемое значение bool -генерируемый импульс.
//================================================================================================= 			   
bool generatorPWMmcs  (RT_HW_GENERATOR_PWM_ID   &id, uint32_t period, uint8_t wprc, uint8_t EN=1){ 			//==Генератор PWM;
if(id.dir==0) {id.dir=3;}
if(id.dir==1) {if((RT_HW_MICROS-id.time)>= id.timeON) 	 {id.dir=2; 	 return 0;} else {return 1;}}
if(id.dir==2) {if((RT_HW_MICROS-id.time)>=(id.timeFULL)) {id.dir=3;}}
if(id.dir==3) {if(!EN) 		    {return 0;} id.time=RT_HW_MICROS; 
			   if(period==0)    {return 0;}			   
			   if(wprc==0) 	    {return 0;} 
			   if(wprc>=100) 	{return 1;} 
			   id.timeFULL=period; 			  
			   id.timeON=(((uint32_t)period*wprc)/100); 
			   id.dir=1; return 1;}		return 0;}
//=================================================================================================
//							1.8.Генератор событий с делителем
//================================================================================================= 
bool generatorFront(RT_HW_GENERATOR_FRONT_ID &id, char mode, uint8_t divide, uint8_t EN=1){
id.event=0;
if(EN){if(generatorChangeEN(id.ago,mode,EN)) {
if(++id.cnt > divide) {id.cnt=1; id.event=1; if(id.meander) {id.meander=0;} else {id.meander=1;}}}}
				 else {id.event=id.meander=0;}
return id.event; 	
};	
//=================================================================================================
//							1.9.Генератор (пачки)пачек импульсов
//================================================================================================= 
bool generatorGroup(RT_HW_GENERATOR_GROUP_ID &id, uint16_t period, uint16_t periodFULL, uint8_t qnt, uint8_t EN=1){	
if(id.dir==0) {id.ago=0; id.dir++;}
if(id.dir==1) {id.meander=id.cnt=0;
			   if(periodFULL==0) {id.dir=2;} else   {id.time=RT_HW_MILLIS; id.dir=3;}}
if(id.dir==2) {if(generatorChangeEN(id.ago,'F',EN)) {id.time=RT_HW_MILLIS; id.dir=4;}} //--Обработка задержки
if(id.dir==3) {if(getPastMs(id.time)>periodFULL)    {id.dir=4;}} //     по времени при EN=1;
if(id.dir==4) {if(id.cnt>=qnt) {id.dir=1; id.meander=0;} else {id.dir++;}}
if(id.dir==5) {id.time=RT_HW_MILLIS; id.meander=1; id.dir++;}
if(id.dir==6) {if(getPastMs(id.time)>=period) {id.meander=0; id.time=RT_HW_MILLIS; id.dir++; }}
if(id.dir==7) {if(getPastMs(id.time)>=period) {++id.cnt; id.dir=4;}}
return id.meander;};
//=================================================================================================
//							1.10.Генератор задач с таймером
//================================================================================================= 
uint8_t generatorTask (RT_HW_GENERATOR_TASK_ID  &id, uint16_t period, uint8_t qnt, uint8_t EN=1){ 			
// id.event-номер задачи как событие, id.cnt-последний номер задачи; возвращает id.event;
if(EN){
if(periodMs(id.time,period)) {
if(++id.cnt > qnt) {id.cnt=1;} id.event=id.cnt; } else {id.event=0;};}
else {id.event=id.cnt=0;}
return id.event;}

//=================================================================================================
//							1.11.Генератор задач автономный
//================================================================================================= 
uint8_t generatorTask (uint8_t &cnt, uint8_t qnt, uint8_t EN=1){ 											
if(EN){if(++cnt > qnt) {cnt=1;} return cnt;} else {return 0;}}
//=================================================================================================
//							1.12.Защита от дребезга байта
//=================================================================================================
bool chatterV8(RT_HW_CHAT_V8_ID &id, uint8_t var, uint16_t period){
if(id.dir==0) {if(id.ago!=var){id.timeBegin=RT_HW_MILLIS; id.dir++;}               return id.ago;}
if(id.dir==1) {if((getPastMs  (id.timeBegin)< period) && (id.ago==var)) {id.dir=0; return id.ago;} 
			   if( getPastMs  (id.timeBegin)> period)     {id.ago=var;	 id.dir=0; return id.ago;}}
																				   return id.ago;};
bool chatterV8(RT_HW_CHAT_V8_ID &id, uint8_t var){
if(id.dir==0) {if(id.ago!=var){id.timeBegin=RT_HW_MILLIS; id.dir++;}                    return id.ago;}
if(id.dir==1) {if((getPastMs  (id.timeBegin)< (id.period)) && (id.ago==var)) {id.dir=0; return id.ago;} 
			   if( getPastMs  (id.timeBegin)>= id.period)     {id.ago=var;	  id.dir=0; return id.ago;}}
																					    return id.ago;};
//=================================================================================================
//						   1.13.Генератор событий с делителем (без структуры) bit::2-ago veN, 0-event, 1-meander;
//================================================================================================= 
void generatorDivider(uint8_t &state, uint8_t &cnt, uint8_t divider, bool v){
state&=0xFE; if(bitRead(state,2)!=v) {bitWrite(state,2,v);  if(v){if(++cnt>divider) {cnt=1; state|=1; state^=2;}}}};
void generatorDivider(uint8_t &state, int16_t &cnt, int16_t divider, bool v){
state&=0xFE; if(bitRead(state,2)!=v) {bitWrite(state,2,v);  if(v){if(++cnt>divider) {cnt=1; state|=1; state^=2;}}}};	
void generatorDivider(uint8_t &state, uint8_t &cnt, uint8_t divider){state&=0xFE; if(++cnt>divider) {cnt=1; state|=1; state^=2;}};
void generatorDivider(uint8_t &state, int16_t &cnt, int16_t divider){state&=0xFE; if(++cnt>divider) {cnt=1; state|=1; state^=2;}};

//=================================================================================================
//						   1.14.Генератор бегущей единицы
//struct RT_HW_GENERATOR_RUN1{                    
// uint32_t startTime,curTime;		//--Переменные для работы со временем;
// uint32_t period;					//--Период;
// int32_t  cnt;					//--Счетчик;
// uint8_t  dir; 					//--Рабочий номер этапа;
// uint8_t  modeTime=0; 			//--Тип времени:  =0-micros, =1-millis;
// uint8_t  modeGen=0; 				//--Тип счетчика: =0-Saw,    =1-Trig;
// uint8_t  direct=0;				//--Направление счета;

//uint16_t sizeDelay;			//--Время задержки;
//uint8_t  state=0;				//--Состояние функции (1 - ожидание завершение задержки);
//uint8_t  pointTime; 			//--Точка возрата из функции(для пользовательского использования);
//};
//if(!period){return 1;}   
//if((timeEnd-timeBegin)>=period){do{timeBegin+=period; if(timeBegin<period) {break;}} while(timeBegin<(timeEnd-period)); return 1;} return 0;};
//uint8_t period   (uint32_t &timeBegin, uint32_t timeEnd, uint32_t period){ //==Точный генератор событий по двум временным точкам;
//if(!period){return 1;}   
//if((timeEnd-timeBegin)>=period){do{timeBegin+=period; if(timeBegin<period) {break;}} while(timeBegin<(timeEnd-period)); return 1;} return 0;};

//================================================================================================= 
void generatorRun(RT_HW_GENERATOR_RUN_ID &id, uint32_t vPeriod){ //==Точный генератор событий по двум временным точкам;
id.event=1;
if(id.dir==0){
if(vPeriod==0)  {id.cnt=id.dc=0; return;} 
id.period=vPeriod;
if(id.modeTime){id.timeBegin=millis();} else {id.timeBegin=micros();}
id.dir++;}
//-------------------------------------------------------------------------------------------------
if(id.dir==1){
if(id.modeTime)  {id.timeEnd=millis();} else {id.timeEnd=micros();}	
if(period(id.timeBegin,id.timeEnd,id.period)){id.dir++;}}
//-------------------------------------------------------------------------------------------------
if(id.dir==2){
if(id.modeTime){id.timeBegin=millis();} else {id.timeBegin=micros();}
if(id.modeGen=='S') {if(++id.cnt>id.top){id.cnt=0;}}
else                {if(id.cnt==id.top) {id.direct=1;} 
                     if(id.cnt==0)      {id.direct=0;}
//-------------------------------------------------------------------------------------------------
			         if(id.direct==0){id.cnt++; if(id.cnt>id.top){id.cnt=id.top;}}
                     else            {id.cnt--; if(id.cnt<0)     {id.cnt=0;     }}}
//-------------------------------------------------------------------------------------------------
id.event=1; id.dir=1;
if(id.top<=8) {id.dc=dc8(uint8_t(id.cnt));   return;}
if(id.top<=16){id.dc=dc16(uint16_t(id.cnt)); return;}
if(id.top<=24){id.dc=dc24(uint32_t(id.cnt)); return;}
if(id.top<=32){id.dc=dc32(uint32_t(id.cnt)); return;}
//-------------------------------------------------------------------------------------------------
}	
//-------------------------------------------------------------------------------------------------
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//								2.ГЕНЕРАТОРЫ СЛУЧАЙНЫХ ЧИСЕЛ
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//						   2.1.Генератор случайных чисел.
//=================================================================================================
uint32_t genRandom(uint8_t depth=32, uint16_t base=0){
//-------------------------------------------------------------------------------------------------
#if !defined(RT_HM_COREM)				//==Если контроллер не многоядерный;
  uint32_t bf32;
#endif
//-------------------------------------------------------------------------------------------------
bf32=base + board.id + vArchCode() + vBoardCode() +RT_HW_MICROS; // + unixID.timeUNIX;	//--Здесь могут быть дополнительные компоненты (например температура процессора);
bf32=bf32*1103515245 + 12345678;  										//--Линейный метод;
if((depth!=8) && (depth!=16) && (depth!=24) && (depth!=32)) {depth=8;}	//--Нормализация разрядности depth;
if(depth ==8){return ((bf32>>24) % 0xFF);}    							//--Вернуть значение в диапазоне 0-255;
if(depth==16){return (board.id=(bf32>>16) % 0xFFFF);}   				//--Вернуть значение в диапазоне 0-65535;
if(depth==24){return ((bf32>> 8) % 0xFFFFFF);}							//--Вернуть значение в диапазоне 0-16777215;
if(depth==32){return   bf32;}     										//--Вернуть значение в диапазоне 0-4294967295;
			  return   bf32;};											//--Неопределенный случай; 
//=================================================================================================
