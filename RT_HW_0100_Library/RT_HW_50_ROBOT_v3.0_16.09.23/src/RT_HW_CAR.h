//=================================================================================================
//        		БИБЛИОТЕКА ДЛЯ УПРАВЛЕНИЯ CAR
// 
// ecoins (ecoins@mail.ru) 
//   2021.07.29: Полностью переработанная версия под библиотеку RT_HW_BASE.h; 
//   2022.10.14: Доработана под версию RT_HW_BASE.v.8.01
//=================================================================================================
#ifndef   RT_HW_CAR_h
#define   RT_HW_CAR_h

#include "RT_HW_BASE.h"					//--Подключение библиотеки RT_HW_BASE.h
#define   RT_HW_CAR_VER 	   20		//--Номер версии библиотеки;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							ФОРМАТ ВНЕШНИХ КОМАНД ПРОТОКОЛА RC Controller
// (приложения Android BlueTooth RC Controller и др.)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 'D' - стоп по остановке от пульта;
// 'S' - cтоп;
// 'F' - вперед;
// 'L' - влево;
// 'B' - назад;
// 'R' - вправо;
// 'G' - вперед-влево;
// 'I' - вперед-вправо;
// 'H' - назад-влево;
// 'J' - назад-вправо; 
// 'V' - включить  звуковой сигнал;
// 'v' - выключить звуковой сигнал;
// 'W' - включить  передние фары и форсаж;
// 'w' - выключить передние фары и форсаж.
// 'U' - включить  задние фары;
// 'u' - выключить задние фары;
// 'X' - включить  "Аварийку";
// 'x' - выключить "Аварийку"; и блокировку сонара.
// '0' - cкорость= 0%;
// '1' - cкорость=20%;
// '2' - cкорость=30%;
// '3' - cкорость=40%;
// '4' - cкорость=50%;
// '5' - cкорость=60%;
// '6' - cкорость=70%;
// '7' - cкорость=80%;
// '8' - cкорость=90%;
// '9' - cкорость=100%;
// 'q' - cкорость=100%; (используется в некоторых Android приложениях);
//-------------------------------------------------------------------------------------------------
// '#' - отсутствие связи (при первом включении);
// 'T' - ошибка по тайм-аут связи;
// 'E' - многократная повторяющаяся ошибка при приеме символа;  
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//						ФОРМАТ ПУЛЬТОВОЙ КОМАНДЫ УПРАВЛЕНИЯ 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// direct: 	bits.0-3=cmd(Команда); bits.4-7=speed(Скорость); bits.8-15=control(управление); 
// control:	bit.0=beep(Звуковой сигнал);
//         	bit.1=Передние фары;
// 		   	bit.2=Задние фары;
// 		   	bit.3=fault(Аварийка);
// 		 	bit.4=fast(Форсаж);
// 			bit.5=block(Блокировка движения);
// 			bit.6=ON(Разрешение управления);
// 			bit.7=link(Наличие связи);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//					СТРУКТУРА RT_HW_CAR_UART_RC
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
struct RT_HW_STRUCT_CAR_UART_RC{
uint8_t  custom=0;				//
uint8_t  dir=0;
uint8_t  uart=0;				//--Номер порта UART (0-8 аппаратный, 9 программный);
uint32_t speedUart=115200;		//--Скорость UART;
//-----------------------------------------------
uint8_t  extBlock=0;
//-----------------------------------------------
uint8_t  curVar;				//--Текущий принятый байт;
uint8_t  agoVar=250;			//--Предыдущий принятый байт;
char     sign;					//--Принятый байт в символьной форме; 
char	 signS='#';				//--Последний код команды управления (char);
//-----------------------------------------------
uint8_t  cmd=0;				    //--Код команды управления (uint8_t)
uint8_t  speed=0;			    //--Команда уставки скорости (0-10);	
uint8_t  control=0;				//--Управляющие и контрольные флаги;					
uint16_t direct=0;				//--Вектор управления;
//-----------------------------------------------
char	 cmdChar='#';			//--Код команды управления (char) (S,F,L,B,R,G,H,I,J,#,T);
//-----------------------------------------------
uint8_t  qnt;					//--Кол-во принятых байт;
uint8_t  idx;					//--Рабочий индекс;
uint8_t  bf;					//--Рабочий буфер;
//----------------------------------------------
uint8_t  fresh=5;
uint16_t timeOut=1000;			//--Тайм-аут на разрыв связи;
uint32_t timeBegin;				//--Рабочий регистр;
uint8_t  errCnt=0;				//--Кол-во ошибок;
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//					СТРУКТУРА RT_HW_CAR_DEVICE
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
struct RT_HW_STRUCT_CAR_MOTOR{
uint8_t  custom=0;				//--Флаг настройки параметров;
uint8_t  module=1;				//--Тип модуля (0=отключен; 1=EnA,EnB,IN1-4; 2=IN1-4; 
uint8_t  dir=0;					//--Этап основной программы управления;
uint8_t  step=0;				//--Этап встроенных функций;
//-------------------------------------------------------------------------------------------------
uint16_t direct=0;				//--Вектор управления;
//-------------------------------------------------------------------------------------------------
uint8_t  cmd=0;				    //--Команда управления (uint8_t) из вектора управления direct;
uint8_t  cmdSet;				//--Управляющая команда;
uint8_t  cmdCur;				//--Текущая команда;
uint8_t  idx;					//--Рабочий индекс;
//-------------------------------------------------------------------------------------------------
uint8_t  speed=0;			    //--Команда уставки скорости (0-10);	
uint16_t powerCmd;				//--Командная мощность (=273*speed[прим.:273=4095/15]);
uint16_t powerSet;				//--Управляющая мощность;
uint16_t powerCur;				//--Текущая мощность мотора базовая;
uint16_t powerTurn;				//--Текущая мощность мотора для поворота (уменьшенная мощность одного из двигателя);
uint16_t powerDelta;			//--Положительный разрыв между powerMax и powerMin; 
uint16_t powerMax=4000;			//--Максимально допустимая мощность на двигателе; 
uint16_t powerMin=1000;			//--Минимально  допустимая мощность на двигателе;
uint16_t powerSystem;			//--Максимальная мощность для текущей системной разрядности(RT_HW_Base.device.depth.sys)
//-------------------------------------------------------------------------------------------------
uint8_t  control=0;				//--Управляющие и контрольные флаги;					
bool     block;					//--Флаг "Блокировка";
bool     fast;					//--Флаг "Форсаж";
//-------------------------------------------------------------------------------------------------
uint16_t stepStop;				//--Шаг изменения мощности при команде STOP;
uint16_t stepDrive;				//--Шаг при изменении скорости;
uint8_t  portionTurn;			//--Доля мощности при повороте;
//-------------------------------------------------------------------------------------------------
uint32_t timeBegin;				//--Рабочий регистр;
uint16_t period=100;			//--Период;
//-------------------------------------------------------------------------------------------------
uint16_t in1=0,in2=0,in3=0,in4=0;
uint16_t EnA=0;
uint16_t EnB=0;
//-------------------------------------------------------------------------------------------------
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//							КЛАСС: RT_HW_CAR	
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class RT_HW_CAR{
public:
enum{nm_S=0,nm_F,nm_L,nm_B,nm_R,nm_G,nm_I,nm_H,nm_J};
enum{nm_Beep=0,nm_Front,nm_Back,nm_Fault,nm_Fast,nm_Block,nm_On,nm_Link};  
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	

//=================================================================================================
//						1.Получение команды из UART
//=================================================================================================
void getDirectFromUART_RC(RT_HW_STRUCT_CAR_UART_RC &id){ 	//++++Получение символа из UART, подготовка cmd,speed,control,direct;
				bitWrite(id.direct,13,id.extBlock); 					//--Запись      флага внешней блокировки;
//-------------------------------------------------------------------------------------------------
if(id.dir==0) {	if(!RT_HW_Base.uartCheckNum(id.uart)) {return;}			//--Проверка наличия ;
				RT_HW_Base.uartSetSpeed(id.speedUart,id.uart);			//--Установка скорости;
				RT_HW_Base.uartBegin(id.uart); 							//--Настройка UART;
				id.dir++;}				
//-------------------------------------------------------------------------------------------------
if(id.dir==1) {	if(RT_HW_Base.uartSerial(id.uart)) {
	                          id.timeBegin=millis(); id.dir++;} return;}//--Ожидание завершения настройки UART;
//-------------------------------------------------------------------------------------------------
if(id.dir==2) {	id.qnt=RT_HW_Base.uartAvailable(id.uart);			//--Получение кол-ва байтов в буфере UART;
//-------------------------------------------------------------------------------------------------
				//bitWrite(id.direct,13,id.extBlock); 					//--Запись      флага внешней блокировки;			
				if(id.qnt>0){
					for(id.idx=0; id.idx<id.qnt; id.idx++){				//--Цикл последовательного чтения байтов из буфера; 
						id.timeBegin=millis();							//--Сброс времени конроля тайм-аута;
					    id.curVar=RT_HW_Base.uartRead(id.uart); 		//--Чтение байта;
					 if(id.agoVar!=id.curVar) {id.agoVar=id.curVar;		//--Если новый код, то он обрабатывается;								
						id.sign=char(id.agoVar);						//--Преобразование в символ;
						if(id.sign!='S'){id.signS=id.sign;}				//--Сохранение последнего символа;
//------------------------------------------------------------------------		
						processingData_RC(id);
//------------------------------------------------------------------------	
						bitWrite(id.control,6,bitRead(id.control,7));   //--Запись      флага  "Пульт включен";				 
						bitWrite(id.control,5,id.extBlock); 			//--Запись      флага внешней блокировки;
//------------------------------------------------------------------------	
						bitClear(id.control,4);							//--Очистка флага "Форсаж"
						if(bitRead(id.control,1) && bitRead(id.control,2)){bitSet(id.control,4);}	//--Включение флага "Форсаж", если включены передние+задние.фары;
//------------------------------------------------------------------------	
						id.direct=((uint16_t)id.control<<8)| ((id.speed&0xF)<<4) | (id.cmd&0xF);    
				  //RT_HW_Base.consoleBegin();
				  //RT_HW_Base.consoleTest(String(F("qnt")),   id.qnt,   ';');
				  //RT_HW_Base.consoleTest(String(F(" sign")),   id.sign,   ';');
				  //RT_HW_Base.consoleTest(String(F(" signS")),  id.signS,  ';');
				  //RT_HW_Base.consoleTest(String(F(" cmd")),     id.cmd,    ';');
				  //RT_HW_Base.consoleTest(String(F(" speed")),  id.speed,  ';');
				  //RT_HW_Base.consoleTest(String(F(" control")),id.control,';','H');
				  //RT_HW_Base.consoleTest(String(F(" direct")),id.direct,'E','H');				  
//------------------------------------------------------------------------ 
							}}}				//--Обработка принятого символа;								
//------------------------------------------------------------------------
				else {
				if(RT_HW_Base.getPastMs(id.timeBegin)>id.timeOut){		//--Обработка превышения тайм-аута
                id.timeBegin=millis(); id.sign='T'; id.fresh=5;}}
//-------------------------------------------------------------------------------------------------								
				if((id.sign=='#')||(id.sign=='T')||(id.sign=='E')){resetDirect(id);}
}
//------------------------------------------------------------------------ 
}

//=================================================================================================
//						2.Обработка команды
//=================================================================================================
void processingData_RC   (RT_HW_STRUCT_CAR_UART_RC &id){ 	//++++Обработка символа из UART по протоколу RC;
id.fresh=1;
//---Проверка управляющих команд
				 bitSet(  id.control,7);			//--Установка наличия связи;
if(id.sign=='#'){bitClear(id.control,7); return;}	//--Сброс наличие связи;
if(id.sign=='T'){bitClear(id.control,7); return;}	//--Сброс наличие связи;
if(id.sign=='V'){bitSet  (id.control,0); return;}
if(id.sign=='v'){bitClear(id.control,0); return;}
if(id.sign=='W'){bitSet(  id.control,1); return;}
if(id.sign=='w'){bitClear(id.control,1); return;}
if(id.sign=='U'){bitSet(  id.control,2); return;}
if(id.sign=='u'){bitClear(id.control,2); return;}					
if(id.sign=='X'){bitSet(  id.control,3); return;}
if(id.sign=='x'){bitClear(id.control,3); return;}	
//----Проверка на код команды----------------------------------------------------------------------
if(id.sign=='T'){id.cmd=nm_S; return;} //--Обрыв связи;
if(id.sign=='S'){id.cmd=nm_S; return;}
if(id.sign=='F'){id.cmd=nm_F; return;}
if(id.sign=='L'){id.cmd=nm_L; return;}
if(id.sign=='B'){id.cmd=nm_B; return;}
if(id.sign=='R'){id.cmd=nm_R; return;}
if(id.sign=='G'){id.cmd=nm_G; return;}
if(id.sign=='I'){id.cmd=nm_I; return;}
if(id.sign=='H'){id.cmd=nm_H; return;}
if(id.sign=='J'){id.cmd=nm_J; return;}
if(id.sign=='#'){id.cmd=nm_S; return;}
//----Проверка на код скорости---------------------------------------------------------------------
if(id.sign=='0'){id.speed= 0; return;}
if(id.sign=='1'){id.speed= 2; return;}
if(id.sign=='2'){id.speed= 3; return;}
if(id.sign=='3'){id.speed= 4; return;}
if(id.sign=='4'){id.speed= 6; return;}
if(id.sign=='5'){id.speed= 7; return;}
if(id.sign=='6'){id.speed= 9; return;}
if(id.sign=='7'){id.speed=11; return;}
if(id.sign=='8'){id.speed=13; return;}
if(id.sign=='9'){id.speed=14; return;}
if(id.sign=='q'){id.speed=15; return;}
//----Обработка повторяющего ошибочного кода-------------------------------------------------------
if(++id.errCnt>3){id.errCnt=0; id.sign='E'; id.cmd=nm_S; id.fresh=0; return;}
//-------------------------------------------------------------------------------------------------
};	//++++END processingData_RC()==================================================================	
//=================================================================================================
//						3.Очистка вектора управления
//=================================================================================================

void resetDirect         (RT_HW_STRUCT_CAR_UART_RC &id){ 	//++++Сброс параметров=================
id.cmd=0; id.speed=0; id.control=0; id.direct=0;
};	//++++END resetDirect()========================================================================
//-------------------------------------------------------------------------------------------------
//=================================================================================================
//						4.Вычисление мощности для управления моторами
//=================================================================================================
void directMotor         (RT_HW_STRUCT_CAR_MOTOR &id){		
//------Извлечение параметров из director----------------------------------------------------------
id.cmd=    (uint8_t)( id.direct    &0xF);
id.speed=  (uint8_t)((id.direct>>4)&0xF);
id.control=(uint8_t)((id.direct>>8)&0xFF);
id.powerCmd=273*id.speed;
id.fast=bitRead(id.control,4);
id.block=bitRead(id.control,5);
id.cmdSet=id.cmd;											//--Установка управляющей команды;		
id.powerSet=map(id.powerCmd,0,4095,id.powerMin,id.powerMax); //--Установка управляющей мощности;
//------Обработка внешней блокировки---------------------------------------------------------------
if(id.block){id.cmdSet=nm_S;} 
//------Изменение мощности в режиме "Форсаж"-------------------------------------------------------
if((id.cmdSet!=nm_S)&&(id.fast)){id.powerCur=id.powerSet; id.cmdCur=id.cmdSet; id.step=0; return;} 
//------Плавные параметры управления---------------------------------------------------------------
directMotorSmooth(id);
id.powerTurn=((uint32_t)id.powerCur)*id.portionTurn/100;
if(id.powerTurn<id.powerMin){id.powerTurn=id.powerMin;}
};
//=================================================================================================
//						5.Расчет для плавного изменения мощности
//=================================================================================================
void directMotorSmooth   (RT_HW_STRUCT_CAR_MOTOR &id){		//++++Расчет плавного изменения скорости
//======Рассчитываем и устанавливаем необходимые параметры=========================================
if(id.step==0){id.step=1; return;}
//======Ускоренное снижение скорости до нуля=======================================================  
if(id.step==1){
if(id.powerCur> id.stepStop) {id.powerCur=id.powerCur-id.stepStop;} 
if(id.powerCur<=id.powerMin) {id.powerCur=0; id.cmdCur=nm_S;  id.step=2;}
return;} 
//======Ожидание если управляющая команда = "STOP"================================================= 
if(id.step==2){
if(id.cmdSet==nm_S){return;}
id.cmdCur=id.cmdSet;
id.powerCur=id.powerMin;
id.step=3; return;}  
//======Плавный вывод на заданную мощность с контролем изменения команды===========================
if(id.step==3){
//------Обработка при смене команды в процессе вывода на заданную мощность-------------------------
if(id.cmdCur!=id.cmdSet){
if(id.powerCur>id.stepStop) {id.powerCur=id.powerCur-id.stepStop;} 
if(id.powerCur<id.powerMin) {id.powerCur=0; id.cmdCur=nm_S;}
id.step=0; return;}	
//-----Плавный вывод-------------------------------------------------------------------------------
if(id.powerSet> id.powerCur){id.powerCur=id.powerCur+id.stepDrive; if(id.powerSet<id.powerCur){id.powerCur=id.powerSet;}}
if(id.powerSet< id.powerCur){id.powerCur=id.powerCur-id.stepDrive; if(id.powerSet>id.powerCur){id.powerCur=id.powerSet;}}
return;
}              
//-------------------------------------------------------------------------------------------------
};
//=================================================================================================
//						6.Вывод на управляющие выходы
//=================================================================================================
void directMotorOutput   (RT_HW_STRUCT_CAR_MOTOR &id){		//++++Вывод параметров на пины=========
//-------------------------------------------------------------------------------------------------
//						6.1. Тип модуля 1
//-------------------------------------------------------------------------------------------------
if(id.module==1){
if(id.cmdCur==nm_S){id.EnA=0;            id.in1=0; id.in2=0;  id.in3=0; id.in4=0; id.EnB=0;} 
if(id.cmdCur==nm_F){id.EnA=id.powerCur;  id.in1=1; id.in2=0;  id.in3=1; id.in4=0; id.EnB=id.powerCur;} 
if(id.cmdCur==nm_L){id.EnA=id.powerCur;  id.in1=1; id.in2=0;  id.in3=0; id.in4=1; id.EnB=id.powerCur;} 
if(id.cmdCur==nm_B){id.EnA=id.powerCur;  id.in1=0; id.in2=1;  id.in3=0; id.in4=1; id.EnB=id.powerCur;} 
if(id.cmdCur==nm_R){id.EnA=id.powerCur;  id.in1=0; id.in2=1;  id.in3=1; id.in4=0; id.EnB=id.powerCur;} 

if(id.cmdCur==nm_G){id.EnA=id.powerTurn; id.in1=1; id.in2=0;  id.in3=0; id.in4=1; id.EnB=id.powerCur;} 
if(id.cmdCur==nm_I){id.EnA=id.powerCur;  id.in1=1; id.in2=0;  id.in3=0; id.in4=1; id.EnB=id.powerTurn;} 
if(id.cmdCur==nm_H){id.EnA=id.powerCur;  id.in1=0; id.in2=1;  id.in3=1; id.in4=0; id.EnB=id.powerTurn;} 
if(id.cmdCur==nm_J){id.EnA=id.powerTurn; id.in1=0; id.in2=1;  id.in3=1; id.in4=0; id.EnB=id.powerCur;}
}
 //------------------------------------------------------------------------------------------------
//						6.2. Тип модуля 2
//-------------------------------------------------------------------------------------------------
if(id.module==2){id.EnA=0; id.EnB=0;
if(id.cmdCur==nm_S){id.in1=0; 			 id.in2=0; 			  id.in3=0; 		   id.in4=0;} 
if(id.cmdCur==nm_F){id.in1=id.powerCur;  id.in2=0;            id.in3=id.powerCur;  id.in4=0;} 
if(id.cmdCur==nm_L){id.in1=id.powerCur;  id.in2=0;            id.in3=0; 		   id.in4=id.powerCur;} 
if(id.cmdCur==nm_B){id.in1=0; 			 id.in2=id.powerCur;  id.in3=0; 		   id.in4=id.powerCur;} 
if(id.cmdCur==nm_R){id.in1=0; 			 id.in2=id.powerCur;  id.in3=id.powerCur;  id.in4=0;} 

if(id.cmdCur==nm_G){id.in1=id.powerTurn; id.in2=0;  		  id.in3=0; 		   id.in4=id.powerCur;} 
if(id.cmdCur==nm_I){id.in1=id.powerCur;  id.in2=0;            id.in3=0;            id.in4=id.powerTurn;} 
if(id.cmdCur==nm_H){id.in1=0;            id.in2=id.powerCur;  id.in3=id.powerTurn; id.in4=0;} 
if(id.cmdCur==nm_J){id.in1=0;            id.in2=id.powerTurn; id.in3=id.powerCur;  id.in4=0;}
} 
//-------------------------------------------------------------------------------------------------
};



uint8_t directPeriod     (RT_HW_STRUCT_CAR_MOTOR &id){		//++++Точный генератор событий=========
if(!id.period){return 1;} 
if((millis()-id.timeBegin)>=id.period){do{id.timeBegin+=id.period; if(id.timeBegin<id.period) {break;}} while(id.timeBegin<(millis()-id.period)); return 1;} return 0;};
};  //---END 
//==============  Конец класса ====================================================================
extern RT_HW_CAR RT_HW_Car; 	//--Создание объекта LCD типа HC595
//=================================================================================================
#endif //---RT_HW_CAR_h



