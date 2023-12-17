//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//            			СЕНСОР  DHT22
/*
Описание для FLProg(параметры времени запуска определяются самим блоком FLProg).
---------------------------------------------------------------------------------------------------
DHT21,DHT22 - датчик температуры и влажности.
Поддерживается "горячее" подключение, ошибочные измерения отфильтровываются.
Основные параметры:
  1. Пользовательский номер пина[plug=OFF].
  2. Режим измерения - периодический[plug=ON], по переднему фронту eN 
                       или в каждом цикле[default=периодический].
  3. Пользовательский период измерения[plug=OFF,default=2200ms].
  4. Период измерения [default=2200ms].
Дополнительные параметры:
 1. "Количество повторов при ошибке измерения".
     После нескольких ошибочных измерений, выходные значения сбрасываются->
	                                              fresh=1;ok=0; T=-0.1; H=0.1. 
  2.Блокировка прерываний[default=OFF] - для контроллеров с внутренним работающим WiFi 
                                    снижает вероятность ошибочных измерений.
Входы:
  1. Номер пина [plug=ON].
  2. EN - разрешение работы блока [plug=OFF].
  3. eN - запуск измерения по переднему фронту [для режима измерения по переднему фронту].
Выходы:
  1. ok - флаг готовности устройства [plug=ON].
  2. T - температура (в градусах C).
  3. H - влажность (0-100%). 
  4. fresh - флаг готовности измерений(событие) [plug=OFF].
---------------------------------------------------------------------------------------------------
Особенности измерения: 
   Цикл измерения составляет менее 6мс. 
   В цикле измерения контроллер реагирует только на аппаратные прерывания, 
   время обработки которых не должны превышать 30-50мкс. 
   Большее время приводит к ошибочным измерениям. 
   Единичные ошибочные измерения (до qntMax default=3) отбрасываются.
---------------------------------------------------------------------------------------------------
Рекомендации для FLProg: 
1.Использовать "Диспетчер задач". 
2.Блок устанавливать на плате, управляемой "Диспетчером задач" как одна из задач
                                                 (медленная,быстрая фоновая и т.д.).
3.Если "Диспетчер задач" не используется, обеспечить регулярный вызов блока 
                                                    не реже периода измерения.
---------------------------------------------------------------------------------------------------
ecoins@mail.ru 01.10.2022. 
---------------------------------------------------------------------------------------------------

*/
// 1.Линия сенсора: притягивается к земле (600mсs); переводится в режим чтения; последовательно принимается 83 изменения линии.
//	 Если нет линия не меняется более 90mcs - фиксируется ошибка с кодом 2.
//    FALLING, RISING и FALLING - это стартовый бит, затем 40 бит: 
// 2. Проверяется контрольная сумма ---> codeErr=3.
// 3. Проверяется диапазон (температура -50.0/+125.0 градусов по Цельсию, влажность 0/100.0 %);
// 4. При отсутствии ошибок запоминаются полученные результаты и при необходимости взводится флаг изменившихся данных (id.fresh);
// 5. После  ошибочных чтений, превышающих maxQntErr, результатам T и H присваивается DHTx_NAN_INT
// Коды ошибок: 
// (=0)-нет ошибок;(=201)-пин не настроен(=255);(=202)-пин без функции DI;(=203) пин нет функции DO;
// (=100-184)-ошибка по тайм-ауту 90msc импульсов с данными;
// (=205)-ошибка контрольной суммы; (=206)-измеренные показания за пределами диапазонов измерений;
//  ecoins (ecoins@mail.ru) 
//  22.10.2022: Begin version
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//-------------------------------------------------------------------------------------------------
#ifndef RT_HW_DHT22_h
#define RT_HW_DHT22_h
#define RT_HW_DHT22_VER 			10		//--Номер версии библиотеки;
#include "RT_HW_BASE.h"						//--Подключение базовой библиотеки;
//-------------------------------------------------------------------------------------------------
#define RT_HW_DHT22_DELAY_ERR   	500 	//--Базовая задержка при повторов после ошибки;
#define RT_HW_DHT22_DELAY_ERR_MIN	500		//--Минимальный период при ошибках;
#define RT_HW_DHT22_DELAY_ERR_MAX	2500	//--Максимальный период при ошибках;
#define RT_HW_DHT22_TIME_SENSOR     800		//--Время цикла измерения внутри сенсора после запуска измерения;
//#define RT_HW_DHT22_DEBUG
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                     КЛАСС УПРАВЛЕНИЯ DHT22
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class RT_HW_DHT22{
public:
//-----------------Основные параметры управления---------------------------------------------------
uint8_t  custom=0;				//--Состояние настройки ID;  
//----------------Перенастраиваемые параметры пользователем----------------------------------------
uint8_t  pin=255;				//--Текущий номер пина;
//----------------Основные переменные управления измерением----------------------------------------
uint8_t  run=0, cmdRun=0;       //--Флаг для внешнего запуска измерений;
uint8_t  ddr=0;					//--Этапы основной программы управления устройствами;
uint8_t  step;					//--Управление этапами управления в функциях измерения;
//----------------Выходные параметры---------------------------------------------------------------
uint8_t  fresh=1;				//--Флаг "свежих" данных;
uint8_t  ok=0;					//--Флаг "Устройство в норме;
uint8_t  codeErr, err;			//--Код ошибки при обмене;
//----------------Дополнительные переменные управления измерением----------------------------------
uint8_t  initDevice=0, action;	//--Рабочие флаги;
uint8_t  cntErr=0;				//--Счетчик повторных ошибок;
uint16_t cntMeterOk=0,cntMeterErr=0;
//----------------Параметры для функци timeDelay()[и также используются функцией i2cFindAdr()]-----
uint32_t startDelay;		    //--Рабочий регистр;
uint8_t  workDelay=0;			//--Рабочий регистр; 
uint8_t  pointDelay;			//--Точка возврата из функции;
uint16_t sizeDelay;				//--Задержка для функции();
//----------------Буферные рабочие переменные (поддержка релевантности)----------------------------
uint8_t  blockInterrupts=0;     //--Блокировка прерываний при измерении (меняется внешней функцией);
uint8_t  permitInterrupts=0;	//--Разрешение блокировки (вычисляемая);
uint8_t  modeDelay=1;			//--"Жесткая" задержка(=1) после импульса запуска;
//-------------------------------------------------------------------------------------------------
uint32_t stratTime,lastReadTime;
//-------------------------------------------------------------------------------------------------
word rawH=0; 
word rawT=0; 
word data=0; 
int16_t  vT;     uint16_t vH;
RT_HW_PIN_DIR_ID idPin;
float    vTemp=2.0, vHum=10.0;			//--Измеренные значения;
//=================================================================================================
//						1.Настройка и инициализация параметров устройства
//=================================================================================================
void setParam(uint8_t vPin=255){if(custom==0){custom=1; pin=vPin; ddr=0;}}
//=================================================================================================
//						2.Управление устройством
//=================================================================================================
void direct(){
if(run){cmdRun=1;} 
//-------------------------------Инициализация параметров------------------------------------------
if(ddr==0) {
#if defined(RT_HW_CORE_ESP)
 if(blockInterrupts==0){permitInterrupts=1;}	//--Установка флага разрешения прерываний(при ESP=ok & blockInterrupts=0);
#endif
//-------------------------------------
workDelay=ok=err=codeErr=cntErr=initDevice=0; 
if(permitInterrupts){vTemp=-0.10; vHum=20.10;} 
                else{vTemp=-0.20; vHum=20.20;} fresh=1;								//--Инициализация параметров;	
if(pin==255)														{codeErr=10;}	//--Выход, если пин не настроен;
if(codeErr==0){if(!RT_HW_Base.checkPinPGM(RT_HW_PGM_PIN_DIN_ID,pin)){codeErr=11;}}	//--Выход по ошибке, если пин нe DI;
if(codeErr==0){if(!RT_HW_Base.checkPinPGM(RT_HW_PGM_PIN_DOT_ID,pin)){codeErr=12;}}	//--Выход по ошибке, если пин нe DI;		
if(codeErr==0)														{initDevice=1;}	//--Установка флага инициализациия устройства;
ddr=90; sizeDelay=50; pointDelay=10;} 		//--Переход в рабочий режим через 50ms;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++			  
//----------------------Ожидание команды cmdRun(запуск измерения)----------------------------------
if(ddr==10){	
if(!cmdRun)    {return;} cmdRun=0;		//--Ожидание команды запуска; 
if(!initDevice){return;} 				//--Выход если устройство не настроено;
step=0; ddr=30;}				//--Переход на измерение;	
//--------------------------Измерение--------------------------------------------------------------
if(ddr==30){	
meter();		   						//--Вызов функции измерения;
if(err)   {vTemp=-0.30; vHum=18.30; ddr=90; sizeDelay=1000; pointDelay=10; return;} //--Дейстdия по ошибке;														
if(action){return;}  					//--Ожидание завершения измерения;
sizeDelay=500; pointDelay=10; ddr=90;}	//--Переход на ожидание run через задержку 500ms;;		
//-----------------------Фиксированная задержка----------------------------------------------------
if(ddr==90){if(!RT_HW_Base.timeDelay(startDelay,workDelay,sizeDelay)){return;} ddr=pointDelay;}
//-------------------------------------------------------------------------------------------------
}; //--End direct();
//=================================================================================================
//						3.Измерение параметров
//=================================================================================================
void meter(){
//-------------------------------------------------------------------------------------------------
if(step==0) {workDelay=err=codeErr=cntErr=0; action=1; step=10;}	//--Подготовка параметров;
//-------------------------------------------------------------------------------------------------																
if(step==10){ 
digitalWrite(pin,LOW); pinMode(pin,OUTPUT); 	//--Притягивание линии устройства к земле;
delayMicroseconds(1200);							//--Удерживание  пина в низком состояния для завершения измерения в сенсоре;
digitalWrite(pin, HIGH); 						//--Переключение пина на прием данных;
pinMode(pin, INPUT);  																			
step=20;}										//--Переход на измерение;
//-------------------------------------------------------------------------------------------------											
if(step==20){
if(permitInterrupts){noInterrupts();}			//--По условию запрет прерываний;
//----------------------------------------------------------------------------------
//	          Цикл фиксации 83 входных импульсов (первые три -стартовых импульса):
//1.cначала FALLING, RISING и FALLING фронт для стартового бита
//2.затем 40 бит: НАРАЩИВАЮЩИЙСЯ и затем СПАДАЮЩИЙ фронт на бит
//  Для упрощения кода принимаем любое значение HIGH или LOW, если оно не превышает 100 мкс.
//-----------------------------------------------------------------------------------			
static int8_t   idx;
RT_HW_PIN_DIR_SET_ID(idPin,pin);	//--Для ESP32
codeErr=0;
for(idx=-3; idx<2*40; idx++){
	static uint8_t  age;
	uint32_t startTime = micros();
	do{age=(uint32_t)(micros()-startTime); 
	   if(age>90){codeErr=20+idx; if(permitInterrupts){interrupts();} break;} //--При превышения тайм-аута установливается кода ошибки;	
	  } 
	 //while(digitalRead(pin)         ==(idx & 1) ? HIGH : LOW );
	   while(RT_HW_PIN_DIR_READ(idPin)==(idx & 1) ? HIGH : LOW);//--Для ESP32;
	if(codeErr){break;}
	if((idx>=0) && (idx&1)){data<<=1; if(age>30) {data|=1;}}	//--Фиксация значения(>30mcs это 1)
	if(idx==31) {rawH=data;}				//--Фиксация данных по влажности;
	if(idx==63) {rawT=data; data = 0;}		//--Фиксация данных по температуре;
} //--Завершение цикла for()			 
if(permitInterrupts){interrupts();}   		//--Восстановление прерывания;  
//---------------------------------------------------------------------------------
if(codeErr==0){if((uint8_t)(((uint8_t)rawH)+(rawH>>8)+((uint8_t)rawT)+(rawT>>8))!= data){codeErr=200;}}		//--Проверка на контрольную сумму;
if(codeErr==0){if(rawT & 0x8000 ){vT=-(int16_t)(rawT & 0x7FFF);} else {vT=rawT;} vH=rawH;}	//--Обработка результатов измерения;		       
if(codeErr==0){if(vH>1000){codeErr=201;}}	//--Проверка допустимости диапазона влажности;
if(codeErr==0){if(vT<-500){codeErr=202;}}	//--Проверка допустимости диапазона температуры снизу; 
if(codeErr==0){if(vT>1250){codeErr=203;}}	//--Проверка допустимости диапазона температуры сверху;			   
//--------------------------------------------------------------------------------------------------
#if defined(RT_HW_DHT22_DEBUG)
if(codeErr==0){RT_HW_Base.consoleTest(String(F("DHT22.ok  rawT")), rawT,';','U');
               RT_HW_Base.consoleTest(String(F(" rawH")), rawH,'E','U');}
else          {RT_HW_Base.consoleTest(String(F("DHT22.err rawT")), rawT,';','U');
               RT_HW_Base.consoleTest(String(F(" rawH")), rawH,';','U');
               RT_HW_Base.consoleTest(String(F(" err")), codeErr,';','U');
                RT_HW_Base.consoleTest(String(F(" cntErr")),   cntErr,';','U');
				RT_HW_Base.consoleTest(String(F(" pin")),   pin,'E','P');
				
				}	               
#endif
//-------------------------------------------------------------------------------------------------
if(codeErr==0){cntMeterOk++;} else {cntMeterErr++;}
//RT_HW_Base.consoleTest("DHT22 cntOk",cntMeterOk,';');
//RT_HW_Base.consoleTest(" cntErr",cntErr,';');
//RT_HW_Base.consoleTest(" codeErr",codeErr,'E','U');
if(codeErr==0){ok=fresh=1; vTemp=vT/10.0; vHum=vH/10.0;  action=0;  step=0; return;} //--Выход при успешном завершении;
               step=85; pointDelay=10;												 //--При ошибке переход на динамическую задержку;
}	//---------------------------------------------------------------------------------------------- 
//=================================================================================================
if(step==85){	//++++Динамическая задержка--------------------------------------------------------
if(++cntErr>3){cntErr=3; codeErr=82; err=1; fresh=1; ok=0; vTemp=2.10; vHum=10.10; return;} 
sizeDelay=1000+cntErr*500;  step=90;}
//-------------------------------------------------------------------------------------------------
if(step==90){	//++++Фиксированная задержка-------------------------------------------------------
if(!RT_HW_Base.timeDelay(startDelay,workDelay,sizeDelay)){return;} step=pointDelay;}
//-------------------------------------------------------------------------------------------------
};	//++++END meter()==============================================================================
//=================================================================================================
};	//++++END class RT_HW_DHT22====================================================================
#endif
//=================================================================================================
