//=================================================================================================
//										1.Диспетчер задач c внешней структурой
//=================================================================================================
void sheduler(RT_HW_STRUCT_SHED &id){
id.ready=1; 
id.event=0; id.quick.num=id.fast.num=id.slow.num=id.back.num=id.frdm.num=0; id.eventSec=0;			//--Сброс парметров;
                                                           ++id.cntCycle;   id.control^=1; 			//--Контрольный сигнал loop();														   
//-------------------------------------------------------------------------------------------------
if(period(id.timeStart1, micros(),1000 )) {id.run^=(1<<4);   id.event^=(1<<4);   id.blink1^=1;}    	//--Оператив. задача,blink10  10ms;
if(period(id.timeStart10,micros(),10000)) {id.run^=1;        id.event^=1;        id.blink10^=1;    	//--Оператив. задача,blink10  10ms;
 if(++id.workSec>=100){id.workSec=0;  																//--Обработка секундных событий;
  id.cntSec++;  																					//--Счетчик секунд (Мотосекунды проекта);
  id.eventSec=1; id.blinkSec^=1;	 																//--Обработка секундных событий и меандра;
  id.cycle=id.cntCycle;   id.cntCycle=0;  id.smallCycle =(uint16_t)round(((float)id.cycle)/1000);	//--Обработка быстродействия loop();
  if(id.isLoop1){																					//--Обработка 
  id.cycle1=id.cntCycle1; id.freshSec1=1; 															//--Дваж
                                          id.smallCycle1=(uint16_t)round(((float)id.cycle1)/1000);}	//            быстродействия loop1();
  }}	//--Project performance;
//-------------------------------------------------------------------------------------------------
if(period(id.timeStart25,RT_HW_MILLIS,25)){id.run^=(1<<1); id.event^=(1<<1); id.blink25^=1;   		//--Fast task,blink25  25ms;
                                                           if(!id.blink25)  {id.blink50^=1;}   		//            blink50  50ms;	
 if(++id.cnt250 >=10){id.cnt250=0;         id.run^=(1<<2); id.event^=(1<<2); id.blink250^=1;  		//--Slow task,blink25  25ms;	
                                                           if(!id.blink250) {id.blink500^=1;}}  	//            blink500 500ms;
 if(++id.cnt100 >= 4){id.cnt100=0;	 	   id.run^=(1<<3); id.event^=(1<<3); id.blink100^=1;} 		//--Back task,blink100 100ms;
}	
//-------------------------------------------------------------------------------------------------
  if(id.isLoop1){if(++id.frdm1.cnt  >id.frdm1.qnt) {id.frdm1.cnt =1;} id.frdm1.num =id.frdm1.cnt;}		//--Генератор номера свободной задачи для loop1(); 
//-------------------------------------------------------------------------------------------------
//											Обработка вызова задач 
//-------------------------------------------------------------------------------------------------
if(id.run){
if(bitRead(id.run,4))   {if(++id.tick.cnt >id.tick.qnt) {id.tick.cnt =1;} id.tick.num=id.tick.cnt;   bitClear(id.run,4); return;}
if(bitRead(id.run,0))   {if(++id.quick.cnt>id.quick.qnt){id.quick.cnt=1;} id.quick.num=id.quick.cnt; bitClear(id.run,0); return;}
if(bitRead(id.run,1))   {if(++id.fast.cnt >id.fast.qnt) {id.fast.cnt =1;} id.fast.num =id.fast.cnt;  bitClear(id.run,1); return;}
if(bitRead(id.run,2))   {if(++id.slow.cnt >id.slow.qnt) {id.slow.cnt =1;} id.slow.num =id.slow.cnt;  bitClear(id.run,2); return;}
if(bitRead(id.run,3))   {if(++id.back.cnt >id.back.qnt) {id.back.cnt =1;} id.back.num =id.back.cnt;  bitClear(id.run,3); return;}
}
//-------------------------------------------------------------------------------------------------
else{id.event^=(1<<4);  if(++id.frdm.cnt  >id.frdm.qnt) {id.frdm.cnt =1;} id.frdm.num =id.frdm.cnt;                      
														 if(!id.isLoop1){ id.frdm1.num=id.frdm.num;}	//--Для совместимости проектов без loop1();							
																														 return;}
};
//=================================================================================================
//										2.Диспетчер задач со структурой из библиотеки
//=================================================================================================
void sheduler(){sheduler(shed);}
/*
shed.ready=1; //--Флаг запуска диспетчера;
shed.event=0; shed.quick.num=shed.fast.num=shed.slow.num=shed.back.num=shed.frdm.num=0; shed.eventSec=0;//--Сброс парметров;
                                                                      ++shed.cntCycle; shed.control^=1; //--Контрольный сигнал loop();
//-------------------------------------------------------------------------------------------------
if(period(shed.timeStart10,micros(),10000))  {shed.run^=1;   shed.event^=1;   shed.blink10^=1;    		//--Оператив. задача,blink10  10ms; 
 if(++shed.workSec>=100){																			//--Обработка секундных событий;
  shed.workSec=0;  shed.cntSec++; shed.eventSec=1; shed.blinkSec^=1;	 		
  shed.cntSec++;  																				//--Время работы проекта в сек [Мотосекунды]; 
  shed.cycle=shed.cntCycle; shed.cntCycle=0;  shed.smallCycle=(uint16_t)round(((float)shed.cycle)/1000);  //--Быстродействие проекта на ядре 0;
  shed.cycle=shed.cntCycle; shed.cntCycle=0;  shed.smallCycle=(uint16_t)round(((float)shed.cycle)/1000);  //--Быстродействие проекта на ядре 0;																										
																										}}//--Быстродействие проекта;
//-------------------------------------------------------------------------------------------------
if(period(shed.timeStart25,RT_HW_MILLIS,25)) {shed.run^=(1<<1); shed.event^=(1<<1); shed.blink25^=1;   	//--Быстрая   задача,blink25  25ms;
                                                                 if(!shed.blink25) {shed.blink50^=1;}   //--                 blink50  50ms;	
 if(++shed.cnt250 >=10){shed.cnt250=0;        shed.run^=(1<<2); shed.event^=(1<<2); shed.blink250^=1;  	//--Медленная задача,blink25  25ms;	
                                                                 if(!shed.blink250){shed.blink500^=1;}} //                   blink500 500ms;
 if(++shed.cnt100 >= 4){shed.cnt100=0;	 	  shed.run^=(1<<3); shed.event^=(1<<3); shed.blink100^=1;} 	//--Фоновая   задача,blink100 100ms;
}	
//------------------------------------Обработка вызова задач--------------------------------------- 
if(shed.run){
if(bitRead(shed.run,0))   {if(++shed.quick.cnt>shed.quick.qnt){shed.quick.cnt=1;} shed.quick.num=shed.quick.cnt; bitClear(shed.run,0); return;}
if(bitRead(shed.run,1))   {if(++shed.fast.cnt >shed.fast.qnt) {shed.fast.cnt =1;} shed.fast.num =shed.fast.cnt;  bitClear(shed.run,1); return;}
if(bitRead(shed.run,2))   {if(++shed.slow.cnt >shed.slow.qnt) {shed.slow.cnt =1;} shed.slow.num =shed.slow.cnt;  bitClear(shed.run,2); return;}
if(bitRead(shed.run,3))   {if(++shed.back.cnt >shed.back.qnt) {shed.back.cnt =1;} shed.back.num =shed.back.cnt;  bitClear(shed.run,3); return;}
}
else{shed.event^=(1<<4);  if(++shed.frdm.cnt  >shed.frdm.qnt) {shed.frdm.cnt =1;} shed.frdm.num =shed.frdm.cnt;                        return;}
};
*/
//=================================================================================================


//=================================================================================================
//					Функция управления запуском на выполнение внешних функций
//							(сенсоры, расширители и пр.)
// Параметры настройки в структуре RT_HW_STRUCT_SHED_TASK:
//	(uint8_t)periodLimit - ограничение частоты вызова в циклах вхождения в функцию [режимы С,A]; default=5;
//  (uint16_t)periodTask - период вызова в мс [режимы P,T,A] default=1000;
//  Режимы запуска: 
//	 'C'-запуск по внешним условиям(например изменения входных параметров для расширителя) 
//       с ограничением частоты вызова[periodLimit];
//   'P'-периодический безусловный запуск;       
//   'T'-периодический запуск по внешним условиям(как в режиме 'C')
//	 'A'-запуск по внешним условиям(как в режиме'C') или периодически 
//       (обычно с большим периодом для повышения устойчивости проекта); 		
//   'Q'-запуск в каждом цикле по внешним условиям (для быстрых процессов и для тестирования);
//   'E'-запуск в каждом цикле. Может быть использован для управления через вход EN, 
//       в т.ч. для периодического вызова события=1 на входе EN;
//   'F'-однократное выполнение. Для повтора можно установить id.first=1;
//   'N'-запуск отключен;
//  Вход:
//  run-может устанавливаться внешней функцией. run=5 - означает, что функция запущена на выполнение;
//  Выходы
//  run-  =0 нет запуска; 
//        =1 безусловный запуск; 
//        =2 будет запуск по проверке вншней функции (например по изменению выводимого параметра);
//=================================================================================================
void setTaskID  (RT_HW_STRUCT_SHED_TASK &id, char mode, uint16_t period=1000, uint16_t Period=2500){
id.custom=1; id.mode=mode; id.period=period; id.Period=Period;}	
//=================================================================================================
uint8_t directTask (RT_HW_STRUCT_SHED_TASK &id){
//-------------------------------------------------------------------------------------------------
if(id.run==5)   {id.cntLimit=0; id.timeBegin=id.TimeBegin=millis();} id.run=0;//-Сброс параметров времени внешней функцией и сброс параметра run;
if(id.mode=='N'){id.run=0;   return id.run;}					//--Pежим "Отключено";
if(!id.extEN)   {id.run=0;   id.first=1; return id.run;}		//--Блокировка по входу EN=0, выход run=0;
//--------------------------------------------------------------------------------------------------
if(id.first==1) {id.first=0; id.agoEN=id.extEN; id.cntLimit=0;	//--Инициализация и сброс параметров; 
				 if(id.period<2){id.period=2;}					//--Нормализация периода [P,T,A];                 
				 id.cntLimit=0; id.timeBegin=millis(); 			//--Нормализация периода [P,T,A];				 
			     id.run=1;   return id.run;} 					//--Выход run=1; 
//-------------------------------------------------------------------------------------------------
if(id.mode=='F'){            return id.run;} 					//--Выполняется однократно по first=1;
if(id.mode=='E'){id.run=1;   return id.run;} 					//--Выполняется в каждом цикле;
if(id.mode=='Q'){id.run=2;   return id.run;} 					//--Выполняется в каждом цикле при изменении во внешней функции;
//-------------------------------------------------------------------------------------------------
if(id.mode=='C'){if(++id.cntLimit>=id.periodLimit){id.cntLimit=0; 				id.run=2;}   return id.run;}	//--По изменению во внешней функции;
if(id.mode=='P'){if(++id.cntLimit>=id.periodLimit){id.cntLimit=0; 
                 if(getPastMs(id.timeBegin)>id.period){id.timeBegin=millis();	id.run=1;}}  return id.run;}	//--Периодический безусловный запуск;
if(id.mode=='T'){if(++id.cntLimit>=id.periodLimit){id.cntLimit=0; 
                 if(getPastMs(id.timeBegin)>id.period){id.timeBegin=millis();	id.run=2;}}  return id.run;}	//--Периодический запуск по изменению во внешней функции; 
if(id.mode=='A'){if(++id.cntLimit<id.periodLimit)                                           {return id.run;} 	//--По изменению во внешней функции или периодическии;
				 id.cntLimit=0;																					//--
				 if(id.period==0)                                              {id.run=2;    return id.run;} 	//--При period==0              по изменению во внешней функции;
				 if(getPastMs(id.timeBegin)>id.period){id.timeBegin=millis();	id.run=2;    return id.run;}	//--При period>0  периодически по изменению во внешней функции;
				 if(id.Period==0)                                              {id.run=1;    return id.run;} 	//--При Period==0 выполнение;
				 if(getPastMs(id.TimeBegin)>id.Period){id.TimeBegin=millis();	id.run=1;    return id.run;}	//--При Period>0  периодически выполнение;
				}
//-------------------------------------------------------------------------------------------------
return id.run;
};	//++++END directTask 
//=================================================================================================