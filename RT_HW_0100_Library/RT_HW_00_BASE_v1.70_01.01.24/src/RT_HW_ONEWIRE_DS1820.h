#ifndef RT_HW_ONEWIRE_DS1820_h
#define RT_HW_ONEWIRE_DS1820_h
//-------------------------------------------------------------------------------------------------
#include "RT_HW_BASE.h"
#include "RT_HW_ONEWIRE.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class RT_HW_ONEWIRE_DS1820{
public:
RT_HW_ONEWIRE z;
RT_HW_STRUCT_DS1820_ID id;
//=================================================================================================
//                      Конструктор
//=================================================================================================
RT_HW_ONEWIRE_DS1820(){id.run=1; id.ok=0; id.fresh=1; id.vTemp=0.36; id.dir=0; id.pin=255;};

//=================================================================================================
//                      Работа c ds1820 (основная функция)
//=================================================================================================
void ds1820(){
if(id.dir==0) {  //===========Инициализация параметров и шины 1-Wire===============================
 id.step=0; id.stepDelay=0; id.idAddr=0;
 id.bf8=0; id.codeErr=0; id.okAddr=0; id.okData=0; 												//--Инициализация параметров;            
 if(!RT_HW_Base.checkPinPGM( RT_HW_PGM_PIN_DIN_ID,id.pin)) {id.codeErr=10; id.bf8=1; return;} 	//--Проверка пина на дискретный ввод;
 if(!RT_HW_Base.checkPinPGM( RT_HW_PGM_PIN_DOT_ID,id.pin)) {id.codeErr=11; id.bf8=1; return;} 	//--Проверка пина на дискретный вывод;  
 if(id.bf8==1){id.dirSetBack=5000;                   id.dirReturn=0;          id.dir=80; return;} //++ERR: возврат на полный повтор в dir=0 с  задержкой 5сек;  
 z.begin(id.pin);                                                                            	//--Инициализация шины 1-Wire;
 id.dir=10; 
 return;}                                                                          				//--Продолжение в следующий этап без задержки; 
if(id.dir==10){  //===========Ожидание внешней команды запуска=====================================
 if(!id.run){return;}                                                                         	//--Ожидание внешней команды запуска;
 id.run=0;  id.codeErr=0; id.okAddr=0; id.okData=0;                                           	//--Сброс run, инициализация параметров; 
 id.step=0;                                                               id.dir=11; return;} 	//--Продолжение в следующий этап без задержки;      
if(id.dir==11){  //===========Поиск адреса========================================================
 if(id.idAddr){id.dir=12; return;}                                                            	//--Если адрес уже установлен, то переход на следующий этап;
 search_addr();                                                                           		//--Вызов функции Поиска адреса;
 if(id.action) {return;}                                                                      	//--Ожидание завершения функции;
 if(id.err)    {id.codeErr=id.codeErrAddr; id.cntErr++;                                       	//++ERR: присвоение кода ошибки и увеличение счетчика Err;
                id.ok=0;  id.okErr=1;                                                         	//++ERR: сброс и установка флагов;
                id.dirSetBack=2000;              id.dirReturn=10;         id.dir=80; return;} 	//++ERR: возврат на ожидание run с задержкой; 
                id.idAddr=1;                                                                  	//--Установка флага получения адреса,   
 id.step=0;     id.dirSetBack=10;                id.dirReturn=12;         id.dir=80; return;} 	//--Продолжение в следующий этап  с задержкой;
if(id.dir==12){  //===========Измерение температыры===============================================
 measurement();                                                                           		//--Вызов функции измерения температуры;
 if(id.action) {return;}                                                                      	//--Ожидание завершения функции;
 if(id.err)    {id.codeErr=id.codeErrAddr; id.cntErr++;                                       	//++ERR: фиксация ошибки;
                id.ok=0;  id.okErr=1;                                                         	//++ERR: сброс и установка флагов;  
                id.idAddr=0; id.cntRptAddr=0; id.cntRptData=0;                                	//++ERR: очистка рабочих параметров;              
                id.dirSetBack=2000;              id.dirReturn=10;         id.dir=80; return;} 	//++ERR: возврат на ожидание run с задержкой;  
 id.vTemp=((float)id.raw/16.0); id.fresh=1;      id.cntOk++;                                  	//--Расчет температуры, увеличение счетчика;
                id.ok=1;   id.okErr=0;                                                        	//--Установка и сброс флагов;
 id.step=0;     id.dirSetBack=500;               id.dirReturn=10;         id.dir=80; return;} 	//--Возврат на ожидание run с задержкой; ;
//=================Задержка=dirSetback с возвратом на step=stepReturn=============================
 if(id.dir==80){if(RT_HW_Base.timeDelayMs(id.timeDelay,id.stepDelay,id.dirSetBack)){id.dir=id.dirReturn;} return;}
//-------------------------------------------------------------------------------------------------            
} //--END ds1820();

//=================================================================================================
//                      Функция поиска адреса
//  Возвращает: action,err,codeErr,okAddr,addr[],cntRpt
//  1.Если ok: action=0, err=0; полученные адрес addr[], контрольную сумму crc_addr, 
//    тип дисплея(новый/старый) typeMdf(0/1), ok_addr=1;
//  2.Иначе  : action=0, err=1; код ошибки codeErr;
//  3.В процесе работы: action=1, кол-во повторов cntRpt;
//=================================================================================================
void search_addr(){
if(id.step==0) {    //=========Подготовка параметров===============================================
  id.err=0; id.action=1; id.codeErrAddr=0; id.cntRptAddr=0; id.typeMdf=0;                     //--Подготовка параметров
  for(id.ix=0; id.ix<8; id.ix++){id.addr[id.ix]=0;} id.crcAddr=0x23;                          //--Очистка буфера+случайная CRC;
                                                                         id.step++; return;}  //--Продолжение в следующий этап без задержки;
if(id.step==1) {    //=========Сброс шины 1-Wire=================================================== 
 id.bf8=z.reset();                                                                           //--Сброс шины (=1 получен ответ от устройств);             
  if(id.bf8==0){id.codeErrAddr=20;                                                            //++ERR: присвоение кода ошибки; 
                if(++id.cntRptAddr>=id.maxRptAddr){id.action=0; id.err=1; id.step=0;  return;}//++ERR: ВЫХОД после maxRptAddr неудачных попыток; 
                id.stepSetBack=212;                id.stepReturn=1;       id.step=80; return;}//++ERR: возврат на повтор с задержкой;
                id.stepSetBack=11;                 id.stepReturn=2;       id.step=80; return;}//--Продолжение в следующий этап  с задержкой;  
if(id.step==2) {  //===========Поиск устройства на шине 1-Wire=====================================
  id.bf8=z.search(id.addr);                                                                   //--Поиск устройства (=1 успешный поиск);
  if(id.bf8==0){id.codeErrAddr=21;                                                            //++ERR: присвоение кода ошибки; 
                if(++id.cntRptAddr>=id.maxRptAddr){id.action=0; id.err=1; id.step=0;  return;}//++ERR: ВЫХОД после maxRptAddr неудачных попыток; 
                id.stepSetBack=216;                id.stepReturn=2;       id.step=80; return;}//++ERR: возврат на повтор с задержкой;                 
  id.step++;}                                                                                 //--Продолжение в следующий этап без задержки; 
if(id.step==3) {  //===========Обработка полученного адреса=======================================
  id.okAddr=1; id.bf8=0; id.crcAddr=z.crc8(id.addr,7);                                        //--Расчет контрольной суммы CRC8;  
  if(id.crcAddr==id.addr[7]){id.bf8=1;}                                                       //--Установка флага совпадения CRC8;
  if(id.bf8==0){id.codeErrAddr=22;                                                            //++ERR: присвоение кода ошибки; 
                if(++id.cntRptAddr>=id.maxRptAddr){id.action=0; id.err=1; id.step=0;  return;}//++ERR: ВЫХОД после maxRptAddr неудачных попыток;
                id.stepSetBack=218;                id.stepReturn=1;       id.step=80; return;}//++ERR: возврат на полный повтор в step=1 с  задержкой;                
//-------------------------------------------------------------------------------------------------
  id.bf8=id.addr[0]; id.typeMdf=0; if(id.bf8==0x10){id.typeMdf=1;}                            //--Сохранение типа сенсора:=1 старый;=0 новый;           
  id.okAddr=1; id.err=0; id.action=0; id.step=0; 
  return;}                                     //++УСПЕШНЫЙ ВЫХОД; 
//=================Задержка=stepSetBack с возвратом на step=stepReturn=============================
if(id.step==80){if(RT_HW_Base.timeDelayMs(id.timeDelay,id.stepDelay,id.stepSetBack)){id.step=id.stepReturn;} return;} 
} //--END search_addr();

//=================================================================================================
//                      Функция измерения
//=================================================================================================
void measurement(){
if(id.step==0) {  //===========Подготовка параметров===============================================
  id.err=0; id.action=1; id.cntRptData=0;                                                     //--Подготовка параметров                              
  for(id.ix=0; id.ix<9; id.ix++){id.data[id.ix]=0;} id.crcData=0x37;                          //--Очистка буфера+случайная CRC;
  id.step++; return;}                                                                                 //--Продолжение в следующий этап без задержки;      
if(id.step==1) {  //===========Сброс шины 1-Wire=================================================== 
 id.bf8=z.reset();                                                                            //--Сброс шины (=1 получен ответ от устройств); 
 if(id.bf8==0){id.codeErrData=30;                                                             //++ERR: присвоение кода ошибки; 
               if(++id.cntRptData>=id.maxRptData){id.action=0; id.err=1;  id.step=0;  return;}//++ERR: ВЫХОД после maxRptData неудачных попыток; 
               id.stepSetBack=52;                 id.stepReturn=id.step;  id.step=80; return;}//++ERR: возврат на повтор с задержкой;              
               id.stepSetBack=10;                 id.stepReturn=2;        id.step=80; return;}//--Продолжение в следующий этап  с задержкой;                                                  
if(id.step==2) { //============Команды "Пропуск адреса","Преобразование температуры"===============
  z.skip(); z.write(0x44,id.power);                                                           //--Команды 0xCC,0x44;
  id.stepSetBack=1000;                             id.stepReturn=3;        id.step=80; return;}//--Продолжение в следующий этап  с задержкой 800мс;                
if(id.step==3) { //============Сброс шины 1-Wire===================================================
  id.bf8=z.reset();                                                                           //--Сброс шины 1-Wire;
  if(id.bf8==0){id.codeErrData=31;                                                            //++ERR: присвоение кода ошибки; 
                if(++id.cntRptData>=id.maxRptData){id.action=0; id.err=1; id.step=0;  return;}//++ERR: ВЫХОД после maxRptData неудачных попыток; 
                id.stepSetBack=52;                 id.stepReturn=id.step; id.step=80; return;}//++ERR: возврат на повтор с задержкой;
                id.stepSetBack=10;                 id.stepReturn=4;       id.step=80; return;}//--Продолжение в следующий этап  с задержкой;   
if(id.step==4) { //=============Команды "Пропуск адреса" и "Чтение памяти"=========================
  z.skip(); z.write(0xBE,id.power);                                                           //--Команды "Пропуск адреса" и "Чтение памяти";
  for(id.ix=0; id.ix<9; id.ix++){id.data[id.ix]=z.read();} id.okData=1;                       //--Последовательнон чтение 9 байт;
                id.stepSetBack=10;                 id.stepReturn=5;       id.step=80; return;}//--Продолжение в следующий этап  с задержкой;
if(id.step==5) {  //===========Обработка полученных данных=========================================
  id.crcData=z.crc8(id.data,8); id.bf8=0;                                                     //--Расчет контрольной суммы;
  if(id.crcData==id.data[8])   {id.bf8=1;}                                                    //--Установка флага совпадения CRC8; 
  if(id.bf8==0){id.codeErr=32;                                                                //++ERR: присвоение кода ошибки; 
                if(++id.cntRptData>=id.maxRptData){id.action=0; id.err=1; id.step=0;  return;}//++ERR: ВЫХОД после maxRptData неудачных попыток;  
                id.stepSetBack=52;                 id.stepReturn=3;       id.step=80; return;}//++ERR: возврат на полный повтор в step=3 с  задержкой;  
//------------------------------Формирование температуры data[0,1,4,6,7----------------------------              
  id.depth=12;                                                                                //--Разрядность измерения;
  id.raw=(id.data[1] << 8) | id.data[0];                                                      //--Обработка первых 2-х байт;
  if(id.typeMdf){id.raw=id.raw<<3; if(id.data[7]==0x10){id.raw=(id.raw & 0xFFF0)+12-id.data[6];}}//--Расчет для старого сенсора (DS18S20); 
  else          {id.bf8=id.data[4] & 0x60;                                                    //--Расчет для новых сенсоров;
                      if(id.bf8==0x00){id.raw = id.raw & ~7; id.depth=9;}                     //    9 bit res, 93.75 ms;
                 else if(id.bf8==0x20){id.raw = id.raw & ~3; id.depth=10;}                    //   10 bit res, 187.5 ms;
                 else if(id.bf8==0x40){id.raw = id.raw & ~1; id.depth=11;}}                   //   11 bit res, 375   ms; default is 12 bit res, 750 ms;
  if((id.raw>2000) || (id.raw<(-640))){id.bf8=0;} else {id.bf8=1;}                            //--Контроль диапазона температуры (-40 - +125гр.С)
  if(id.bf8==0){id.codeErrData=33;                                                            //++ERR: присвоение кода ошибки;
                if(++id.cntRptData>id.maxRptData){id.action=0; id.err=1; id.step=0;  return;} //++ERR: ВЫХОД после maxRptData неудачных попыток; 
                id.stepSetBack=52;                id.stepReturn=1;       id.step=80; return;} //++ERR: возврат на полный повтор в step=1 с  задержкой; 
//-------------------------------------------------------------------------------------------------  
  id.step=0; id.err=0; id.action=0; return;}                                         //--Успешный выход; 
//=================Задержка=stepSetBack с возвратом на step=stepReturn=============================
if(id.step==80){if(RT_HW_Base.timeDelayMs(id.timeDelay,id.stepDelay,id.stepSetBack)){id.step=id.stepReturn;} return;} 
}  //--END measurement();

};
#endif