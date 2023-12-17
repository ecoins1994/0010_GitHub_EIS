//#include "RT_HW_BASE.h"
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
//								2.КОДИРОВЩИКИ, ДЕШИФРАТОРЫ
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//================================================================================================= 
//							 2.1.Кодировщик числа в номер бита
//================================================================================================= 
uint8_t  coder8 (uint8_t  v) {if((v==0) || (v>8)) {return 0;} uint8_t  dc=0; bitSet(dc,(v-1)); return dc;};  //-- 8-разрядный;
uint16_t coder16(uint16_t v) {if((v==0) || (v>16)){return 0;} uint16_t dc=0; bitSet(dc,(v-1)); return dc;};  //--16-разрядный;
//=================================================================================================
//							2.2.Дешифраторы
//=================================================================================================
uint8_t  dc8 (uint8_t v){if((v>0) && (v<= 8)){return (uint8_t)1 <<(v-1);} return 0;} //-- 8-разрядный дешифратор;
uint16_t dc16(uint8_t v){if((v>0) && (v<=16)){return (uint16_t)1<<(v-1);} return 0;} //--16-разрядный дешифратор;
uint32_t dc24(uint8_t v){if((v>0) && (v<=24)){return (uint32_t)1<<(v-1);} return 0;} //--24-разрядный дешифратор;
uint32_t dc32(uint8_t v){if((v>0) && (v<=32)){return (uint32_t)1<<(v-1);} return 0;} //--32-разрядный дешифратор;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//										3.СЧЕТЧИКИ
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//							 3.1.СБРОС СЧЕТЧИКА 
//=================================================================================================
void counterReset(RT_HW_COUNTER_ID &id){
id.step=1; id.top=100; id.bottom=0; id.begin=0;          
id.cnt=id.begin; id.direct=0; id.var=0; id.reset=0;}
//-------------------------------------------------------------------------------------------------
void counterReset(RT_HW_COUNTER_ID &id,int16_t top, int16_t bottom, int16_t step, int16_t begin=0){
id.begin=begin; id.step=step; id.top=top; id.bottom=bottom; id.begin=begin;
id.cnt=id.begin; id.direct=0;  id.var=0; id.reset=0;}
//=================================================================================================
//							3.2.СЧЕТЧИК ПИЛА
//=================================================================================================
int16_t counterS(RT_HW_COUNTER_ID &id, uint8_t EN=1){
if(EN){
if( id.step>=0){if(id.cnt==id.top)   {id.var=id.bottom;} 
                else                 {id.var+=id.step; if(id.var>id.top)    {id.var=id.top;}}}
else           {if(id.cnt==id.bottom){id.cnt=id.top;} 
                else                 {id.var+=id.step; if(id.var<id.bottom) {id.var=id.bottom;}}}
id.cnt=(int16_t)id.var;} 
return id.cnt;};				
//=================================================================================================
//							3.3.СЧЕТЧИК ТРЕУГОЛЬНИК
//=================================================================================================
int16_t counterT(RT_HW_COUNTER_ID &id, uint8_t EN=1){
if(EN){
//-------------------------------------------------------------------------------------------------
if(id.step>=0){if(id.cnt==id.top)   {id.direct=1;} 
               if(id.cnt==id.bottom){id.direct=0;}
//-------------------------------------------------------------------------------------------------
			   if(id.direct==0){id.var+=id.step; if(id.var>id.top)    {id.var=id.top;}}
               else            {id.var-=id.step; if(id.var<id.bottom) {id.var=id.bottom;}}}
//-------------------------------------------------------------------------------------------------
else          {if(id.cnt==id.top)   {id.direct=0;} 
               if(id.cnt==id.bottom){id.direct=1;}
//-------------------------------------------------------------------------------------------------
			   if(id.direct==0){id.var+=id.step; if(id.var<id.bottom) {id.var=id.bottom;}}
			   if(id.direct==1){id.var-=id.step; if(id.var>id.top)    {id.var=id.top;}}}
id.cnt=(int16_t)id.var;} 
return id.cnt;};
//=================================================================================================
//							3.4.СЧЕТЧИК ЛИМИТ
//=================================================================================================
int16_t counterL(RT_HW_COUNTER_ID &id, uint8_t EN=1) {
if(EN){
if(id.step>=0) {if(id.cnt<id.top)   {id.var=id.cnt; id.var+=id.step; if(id.var>id.top)    {id.var=id.top;}}}
else           {if(id.cnt>id.bottom){id.var=id.cnt; id.var+=id.step; if(id.var<id.bottom) {id.var=id.bottom;}}}
id.cnt=(int16_t)id.var;} 
return id.cnt;};
//=================================================================================================
//							3.5.СЧЕТЧИК РЕВЕРСИВНЫЙ
//=================================================================================================
int16_t counterR(RT_HW_COUNTER_ID &id, uint8_t ENP=1, uint8_t ENM=0){
if(ENP){
if(id.step>=0) {id.var+=id.step; if(id.var>id.top)    {id.var=id.top;}}
else           {id.var+=id.step; if(id.var<id.bottom) {id.var=id.bottom;}}
id.cnt=(int16_t)id.var; return id.cnt;};
if(ENM){
if(id.step>=0) {id.var-=id.step; if(id.var<id.bottom) {id.var=id.bottom;}}
else           {id.var-=id.step; if(id.var>id.top)    {id.var=id.top; }}}
id.cnt=(int16_t)id.var; return id.cnt;};
//=================================================================================================
// if((v>0) && (v<=8))  {dc=0; bitSet(dc,(v-1));} else dc=0;  //--8-разрядный дешифратор
//uint8_t  dc8 (uint8_t  v){if((v>0) && (v<= 8)){uint8_t  dc=0; bitSet(dc,(v-1)); return dc;} return 0;} //-- 8-разрядный дешифратор;
//uint16_t dc16(uint16_t v){if((v>0) && (v<=16)){uint16_t dc=0; bitSet(dc,(v-1)); return dc;} return 0;} //--16-разрядный дешифратор;


//=================================================================================================


/*
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//										ДОПОЛНИТЕЛЬНЫЕ ФУНКЦИИ
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=================================================================================================
//					Проверка на изменения значения с сохранением в буферe
//-------------------------------------------------------------------------------------------------
bool checkChangeVar(int8_t   &ago, int8_t   val) {if(ago!=val) {ago=val;  return 1;} return 0;}
bool checkChangeVar(uint8_t  &ago, uint8_t  val) {if(ago!=val) {ago=val;  return 1;} return 0;}
bool checkChangeVar( int16_t &ago, int16_t  val) {if(ago!=val) {ago=val;  return 1;} return 0;}
bool checkChangeVar(uint16_t &ago, uint16_t val) {if(ago!=val) {ago=val;  return 1;} return 0;}
bool checkChangeVar(int32_t  &ago, int32_t  val) {if(ago!=val) {ago=val;  return 1;} return 0;}
bool checkChangeVar(uint32_t &ago, uint32_t val) {if(ago!=val) {ago=val;  return 1;} return 0;}
bool checkChangeVar(String   &ago, String   val) {if(ago!=val) {ago=val;  return 1;} return 0;}
bool checkChangeVar(float    &ago, float    val) {if(ago!=val) {ago=val;  return 1;} return 0;}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//=================================================================================================
//					Ограничение переменных установленными границами mode[L,A,N]
// mode: 
// 'A' - всегда;
// 'L' - Если верхняя граница !=0 для верхней границы и если нижняя граница !=0 для нижней границы;
//-------------------------------------------------------------------------------------------------
uint8_t limitationVar(uint8_t  cur, uint8_t highLimit, uint8_t lowLimit, char mode='L'){
if(mode=='L'){if((highLimit!=0) && (cur>highLimit)){cur=highLimit;} if((lowLimit !=0) && (cur<lowLimit)) {cur=lowLimit;}	return cur;}
if(mode=='A'){                   if(cur>highLimit) {cur=highLimit;}                    if(cur<lowLimit)  {cur=lowLimit;}	return cur;}
return cur;}
//--------------------------------------------------------------------------------------------------
int16_t limitationVar(int16_t  cur, int16_t highLimit, int16_t lowLimit, char mode='L'){
if(mode=='L'){if((highLimit!=0) && (cur>highLimit)){cur=highLimit;} if((lowLimit !=0) && (cur<lowLimit)) {cur=lowLimit;}	return cur;}
if(mode=='A'){                   if(cur>highLimit) {cur=highLimit;}                    if(cur<lowLimit)  {cur=lowLimit;}	return cur;}
return cur;}
//-------------------------------------------------------------------------------------------------
int32_t limitationVar(int32_t  cur, int32_t highLimit, int32_t lowLimit, char mode='L'){
if(mode=='L'){if((highLimit!=0) && (cur>highLimit)){cur=highLimit;} if((lowLimit !=0) && (cur<lowLimit)) {cur=lowLimit;}	return cur;}
if(mode=='A'){                   if(cur>highLimit) {cur=highLimit;}                    if(cur<lowLimit)  {cur=lowLimit;}	return cur;}
return cur;}
//-------------------------------------------------------------------------------------------------
float limitationVar(float  cur, float highLimit, float lowLimit, char mode='L'){
if(mode=='L'){if((highLimit!=0) && (cur>highLimit)){cur=highLimit;} if((lowLimit !=0) && (cur<lowLimit)) {cur=lowLimit;}	return cur;}
if(mode=='A'){                   if(cur>highLimit) {cur=highLimit;}                    if(cur<lowLimit)  {cur=lowLimit;}	return cur;}
return cur;}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//=================================================================================================
//							//==Расчет CRC8 (Dallas Semiconductor 8 bit CRC);
//=================================================================================================
uint8_t crc8(const uint8_t* addr,  uint8_t len){											
uint8_t crc = 0;
while (len--) {crc = *addr++ ^ crc;  crc = pgm_read_byte(RT_HW_PGM_TABLE_CRC8_2X16 + (crc & 0x0f)) ^ pgm_read_byte(RT_HW_PGM_TABLE_CRC8_2X16 + 16 + ((crc >> 4) & 0x0f));}
return crc;}
//=================================================================================================
//							Расчет CRC16;
//=================================================================================================
uint16_t crc16(const uint8_t* input, uint16_t len, uint16_t crc){								
  static const uint8_t oddparity[16] ={ 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0 };
  for (uint16_t i=0; i<len; i++) {uint16_t cdata = input[i]; cdata = (cdata ^ crc) & 0xff; crc >>= 8;
                                  if (oddparity[cdata & 0x0F] ^ oddparity[cdata >> 4]) {crc ^= 0xC001;}
								  cdata <<= 6; crc ^= cdata; cdata <<= 1; crc ^= cdata; }
return crc;}
//=================================================================================================
//								Проверка CRC16
//=================================================================================================
bool check_crc16(const uint8_t* input, uint16_t len, const uint8_t* inverted_crc, uint16_t crc){
 crc = ~crc16(input, len, crc); return (crc & 0xFF) == inverted_crc[0] && (crc >> 8) == inverted_crc[1];}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/