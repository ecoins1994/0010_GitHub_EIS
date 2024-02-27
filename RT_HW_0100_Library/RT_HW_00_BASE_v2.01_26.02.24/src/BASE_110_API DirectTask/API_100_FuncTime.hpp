//=================================================================================================
//							      ТОЧНЫЕ ГЕНЕРАТОРЫ СОБЫТИЙ 
// Идея от https://alexgyver.ru/arduino-algorithms/
// timeBegin -время начала отсчета (определяется вне функции); 
// timeEnd   -время текущее;
// timeMax   -тайм-аут;
// Функция генерит событие с точным поддержанием периода и защитой от пропуска шага.
//=================================================================================================
uint8_t period   (uint32_t &timeBegin, uint32_t timeEnd, uint32_t vPeriod){ //==Точный генератор событий по двум временным точкам;
if(!vPeriod){return 1;}   //--Защита от нулевого значения периода;
if((timeEnd-timeBegin)>=vPeriod) 	{ do{timeBegin+=vPeriod; if(timeBegin<vPeriod) {break;}
										}while(timeBegin<(timeEnd-vPeriod)); 		return 1;}
																					return 0;}																				
//=================================================================================================
uint8_t periodMs (uint32_t &timeBegin,                   uint32_t vPeriod){ //==Точный генератор событий ms;
if(!vPeriod){return 1;}   //--Защита от нулевого значения периода;
if((RT_HW_MILLIS-timeBegin)>=vPeriod){do{timeBegin+=vPeriod; if(timeBegin<vPeriod) {break;}
										}while(timeBegin<(RT_HW_MILLIS-vPeriod)); 	return 1;} 
																					return 0;};
//=================================================================================================
uint8_t periodMcs(uint32_t &timeBegin,                   uint32_t vPeriod){ //==Точный генератор событий mcs;
if(!vPeriod){return 1;}   //--Защита от нулевого значения периода; 
if((RT_HW_MICROS-timeBegin)>=vPeriod){do{timeBegin+=vPeriod; if(timeBegin<vPeriod) {break;}
										} while(timeBegin<(RT_HW_MICROS-vPeriod)); 	return 1;} 
																					return 0;};	
//=================================================================================================
//							      РАСЧЕТ ПРОШЕДШЕГО ВРЕМЕНИ 
//  Перед вызовом необходимо установить параметры timeBegin, timeEnd;
//  К использованию рекомендуется getPastTime() вместо getPastMs(),getPastMcs().
//=================================================================================================
uint32_t getPastTime(uint32_t &timeBegin, uint32_t &timeEnd) {	//==Возврат прошедшего времени по двум временным точкам; 
if(timeEnd>=timeBegin) 		return (timeEnd-timeBegin);   	 else {return (0xFFFFFFFF-timeBegin+timeEnd);}}; 
//=================================================================================================
uint32_t getPastMs  (uint32_t &timeBegin){						//==Возврат прошед.времени в ms (millis()->timeBegin);
if(RT_HW_MILLIS>=timeBegin) return (RT_HW_MILLIS-timeBegin); else {return (0xFFFFFFFF-timeBegin+RT_HW_MILLIS);}};	
//=================================================================================================
uint32_t getPastMcs (uint32_t &timeBegin){						//==Возврат прошед.времени в mcs(micros()->timeBegin);
if(RT_HW_MICROS>=timeBegin) return (RT_HW_MICROS-timeBegin); else {return (0xFFFFFFFF-timeBegin+RT_HW_MICROS);}};			
//=================================================================================================
//								РАСЧЕТ ПРОШЕДШЕГО ВРЕМЕНИ внутри функций прерывания 
// Параметры следует определять следующим образом:
//   volatic uint32_t timeBegin, uint32_t timeEnd;
//=================================================================================================
uint32_t calcPastTime(uint32_t timeBegin, uint32_t timeEnd){
 if(timeEnd>=timeBegin){	return (timeEnd-timeBegin);} 	else {return (0xFFFFFFFF-timeBegin+timeEnd);}}; 
//=================================================================================================
//								ФУНКЦИИ ТАЙМ-АУТА (возвращает событие 0/1)
//  Перед вызовом необходимо установить параметры timeBegin, timeEnd; 
//  К использованию рекомендуется timeOut() вместо timeOutMs(),timeOutMcs().
//=================================================================================================
uint8_t timeOut   (uint32_t &timeBegin, uint32_t timeEnd, uint16_t timeMax){	//==Контроль времени тайм-аута по двум временным точкам; 
if(timeEnd  >=timeBegin){if((timeEnd  -timeBegin)>=timeMax)	{return 1;} else {return 0;}} 
			       else {if((timeBegin-timeEnd)  > timeMax) {return 1;} else {return 0;}}}; 
//=================================================================================================
uint8_t timeOutMs (uint32_t &timeBegin, uint16_t timeMax){						//==Контроль времени тайм-аута ms;
//-------------------------------------------------------------------------------------------------
#if !defined(RT_HM_COREM)				//==Если контроллер не многоядерный;
  uint32_t bf32;
#endif
//-------------------------------------------------------------------------------------------------
   bf32=RT_HW_MILLIS; 
if(bf32>=timeBegin){if((bf32-timeBegin)>=timeMax) {return 1;} else {return 0;}} 
	          else {if((timeBegin-bf32)> timeMax) {return 1;} else {return 0;}}}; 
//=================================================================================================
uint8_t timeOutMcs(uint32_t &timeBegin, uint16_t timeMax){						//==Возврат события по таймату в mcs;
//-------------------------------------------------------------------------------------------------
#if !defined(RT_HM_COREM)				//==Если контроллер не многоядерный;
  uint32_t bf32;
#endif
//-------------------------------------------------------------------------------------------------
   bf32=RT_HW_MICROS; 
if(bf32>=timeBegin){if((bf32-timeBegin)>=timeMax) {return 1;} else {return 0;}} 
		      else {if((timeBegin-bf32)> timeMax) {return 1;} else {return 0;}}};
//=================================================================================================
//								ФУНКЦИИ ЗАДЕРЖКИ ПО ВРЕМЕНИ (возвращает событие 0/1)
// struct RT_HW_STRUCT_TIME{                    
//  uint32_t startTime,curTime;		//--Переменные для работы со временем;
//  uint16_t sizeDelay;				//--Время задержки;
//  uint8_t  state=0;				//--Состояние функции (1 - ожидание завершение задержки);
//  uint8_t  pointTime; 			//--Точка возрата из функции(для пользовательского использования);
//};										 
//=================================================================================================
uint8_t checkDelay   (RT_HW_STRUCT_TIME &id, uint32_t sizeDelay, uint8_t vUnit=1){
if(vUnit){id.curTime=RT_HW_MILLIS;} else {id.curTime=RT_HW_MICROS;}
if(id.state==0){id.startTime=id.curTime; id.state=1;}
if(id.curTime >=id.startTime){if((id.curTime-id.startTime)           >  sizeDelay){id.state=0;}}
else                         {if((0xFFFFFFFF-id.startTime+id.curTime)>  sizeDelay){id.state=0;}}	return id.state;}
//-------------------------------------------------------------------------------------------------
uint8_t checkDelayMS   (RT_HW_STRUCT_TIME &id){
id.curTime=RT_HW_MILLIS;
if(id.state==0){id.startTime=id.curTime; id.state=1;}
if(id.curTime >=id.startTime){if((id.curTime-id.startTime)           >id.sizeDelay){id.state=0;}}
else                         {if((0xFFFFFFFF-id.startTime+id.curTime)>id.sizeDelay){id.state=0;}}	return id.state;}			
//-------------------------------------------------------------------------------------------------
uint8_t checkDelayUS   (RT_HW_STRUCT_TIME &id){id.curTime=RT_HW_MICROS;
if(id.state==0){id.startTime=id.curTime; id.state=1;}
if(id.curTime >=id.startTime){if((id.curTime-id.startTime)           >id.sizeDelay){id.state=0;}}
else                         {if((0xFFFFFFFF-id.startTime+id.curTime)>id.sizeDelay){id.state=0;}}	return id.state;}
//=================================================================================================
uint8_t timeDelay   (uint32_t &timeDelay, uint8_t &stepDelay, uint32_t period){ //==delay в ms;
if(stepDelay==0){timeDelay=RT_HW_MILLIS;          stepDelay=1;}
if(stepDelay==1){if(getPastMs(timeDelay)>period) {stepDelay=0; return 1;}}
return 0;}	
//=================================================================================================
uint8_t timeDelayMs (uint32_t &timeDelay, uint8_t &stepDelay, uint32_t period){ //==delay в ms;
if(stepDelay==0){timeDelay=RT_HW_MILLIS;          stepDelay=1;}
if(stepDelay==1){if(getPastMs(timeDelay)>period) {stepDelay=0; return 1;}}
return 0;}	
//=================================================================================================
uint8_t timeDelayMcs(uint32_t &timeDelay, uint8_t &stepDelay, uint32_t period){ //==delay в mcs;
if(stepDelay==0){timeDelay=RT_HW_MICROS;          stepDelay=1;}
if(stepDelay==1){if(getPastMcs(timeDelay)>period){stepDelay=0; return 1;}}
return 0;}	
//=================================================================================================
//								СЕРВИСНЫЕ ФУНКЦИИ
//=================================================================================================
//-------------------------------------------------------------------------------------------------
//					Конвертирует время в тики (для ускорения работы таких библиотек как RT_HW_HD44780, RT_HW_NEXTION & etc)
//-------------------------------------------------------------------------------------------------
uint8_t timeToTick(uint16_t time,  uint8_t tick=50){
if(tick==0){tick=1;}	
if((tick*255)>=time){return time/tick;}	else {return 255;}};
//=================================================================================================
