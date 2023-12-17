#include "RT_HW_CAR_UDP.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	
//							Настройка вектора id
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void RT_HW_CAR_UDP::  setID(RT_HW_STRUCT_CAR_UDP &id){
if(id.custom) {return;}	
if(id.speedUart<1000) {if(id.uart==100) {id.speedUart=9600;} else {id.speedUart=115200;}}
id.custom=1;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	
//							Получение символа и обработка;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void RT_HW_CAR_UDP:: getPackage(RT_HW_STRUCT_CAR_UDP &id){
if(id.step==0) {if(id.custom!=1) {return;} 								//--Ожидание настройки устройства;
				id.code=0; id.sign='T'; vectorCar(id);					//--Инициализация параметров CAR;			    
				if(!RT_HW_Base.uartCheckNum(id.uart)) {return;}			//--Проверка наличия ;
				RT_HW_Base.uartSetSpeed (id.speedUart, id.uart);		//--Установка скорости;
				RT_HW_Base.uartBegin(id.uart); id.step++;}				//--Настройка UART;				
if(id.step==1) {if(RT_HW_Base.uartSerial(id.uart)) {id.step++;} return;}//--Ожидание завершения настройки UART;
if(id.step==2) {uint8_t qnt=RT_HW_Base.uartAvailable(id.uart);			//--Получение кол-ва байтов в буфере UART;
				if(qnt>0){for(uint8_t i=0; i<qnt; i++){					//--Цикл последовательного чтения байтов из буфера; 
					id.timeStart=millis();								//--Сброс времени конроля тайм-аута;
					uint8_t val=RT_HW_Base.uartRead(id.uart); 			//--Чтение байта;
					if(id.code!=val) {									//--Если новый код, то он обрабатывается;	
						id.code=val;									//--Сохранение нового кода;
						id.sign=char(id.code);							//--Преобразование в символ;
						vectorCar(id);									//--Обработка принятого символа;								
				  }
				return;}}
				if(RT_HW_Base.getPastMs(id.timeStart)>id.timeOut){		//--Обработка превышения тайм-аута
				   id.timeStart=millis(); id.sign='T';vectorCar(id);}	//        по приходу байта из UART;
				 	//--end for() 
}}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	
//							Настройка вектора id
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void RT_HW_CAR_UDP:: vectorCar(RT_HW_STRUCT_CAR_UDP &id){
bool err=0;
//--Установка флагов "Связь есть" и "Пульт включен";
	bitSet(id.direct,15); //--Установка флага "Связь есть";
	bitSet(id.direct,14); //--Установка флага "Пульт включен"
switch (id.sign) {
 case 'T': id.code=0; id.direct=0; id.speed=0;	 	break;	//--Ошибка по тайм-аут связи;
 case 'D': id.code=0; id.direct=0; id.speed=0;	 	break;	//--Стоп по остановке от пульта;
 case 'S': bitWrite(id.direct,0,0); bitWrite(id.direct,1,0); bitWrite(id.direct,2,0); bitWrite(id.direct,3,0); 	break;	//--Стоп
 case 'F': bitWrite(id.direct,0,1); bitWrite(id.direct,1,0); bitWrite(id.direct,2,0); bitWrite(id.direct,3,0); 	break;	//--Вперед
 case 'L': bitWrite(id.direct,0,0); bitWrite(id.direct,1,1); bitWrite(id.direct,2,0); bitWrite(id.direct,3,0); 	break;	//--Влево
 case 'B': bitWrite(id.direct,0,0); bitWrite(id.direct,1,0); bitWrite(id.direct,2,1); bitWrite(id.direct,3,0); 	break;	//--Назад
 case 'R': bitWrite(id.direct,0,0); bitWrite(id.direct,1,0); bitWrite(id.direct,2,0); bitWrite(id.direct,3,1); 	break;	//--Вправо
 case 'G': bitWrite(id.direct,1,1); bitWrite(id.direct,1,1); bitWrite(id.direct,2,0); bitWrite(id.direct,3,0); 	break;	//--Вперед-влево
 case 'I': bitWrite(id.direct,1,1); bitWrite(id.direct,1,0); bitWrite(id.direct,2,0); bitWrite(id.direct,3,1); 	break;	//--Вперед-вправо
 case 'H': bitWrite(id.direct,1,0); bitWrite(id.direct,1,1); bitWrite(id.direct,2,1); bitWrite(id.direct,3,0); 	break;	//--Назад-влево
 case 'J': bitWrite(id.direct,1,0); bitWrite(id.direct,1,0); bitWrite(id.direct,2,1); bitWrite(id.direct,3,1); 	break;	//--Назад-вправо 
 case 'V': bitWrite(id.direct,4,1);																			  	break;	//--Звук включить
 case 'v': bitWrite(id.direct,4,0);																				break;	//--Звук выключить
 case 'W': bitWrite(id.direct,5,1);	bitWrite(id.direct,13,1); 													break;	//--Вкл. передние фары и форсаж.
 case 'w': bitWrite(id.direct,5,0);	bitWrite(id.direct,13,0);													break;	//--Выкл.передние фары и форсаж.
 case 'U': bitWrite(id.direct,6,1);																				break;	//--Задние фары включить
 case 'u': bitWrite(id.direct,6,0);																				break;	//--Задние фары выключить
 case 'X': bitWrite(id.direct,7,1);	bitWrite(id.direct,12,1); 													break;	//--Вкл. Аварийку и блокировку сонара.
 case 'x': bitWrite(id.direct,7,0);	bitWrite(id.direct,12,0); 													break;	//--Выкл.Аварийку и блокировку сонара.

 case '0': id.speed = 0;	 		break;	//--Скорость  0%
 case '1': id.speed =20; 			break;	//--Скорость 20%
 case '2': id.speed =30; 			break;	//--Скорость 30%
 case '3': id.speed =40; 			break;	//--Скорость 40%
 case '4': id.speed =50; 			break;	//--Скорость 50%
 case '5': id.speed =60; 			break;	//--Скорость 60%
 case '6': id.speed =70; 			break;	//--Скорость 70%
 case '7': id.speed =80;			break;	//--Скорость 80%
 case '8': id.speed =90; 			break;	//--Скорость 90%
 case '9': id.speed=100; 			break;	//--Скорость 100%
 case 'q': id.speed=100; 			break;	//--Скорость 100%

 default:  err=1;					break;	//--Ошибочный код;
}
//--Обработка повторяющего ошибочного кода
if(err) {id.sign='#'; if(++id.errCnt>3) {id.errCnt=0; id.sign='E'; id.code=0; id.direct=0; id.speed=0;}}
else	{id.errCnt=0;}
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	
RT_HW_CAR_UDP RT_HW_car_UDP;//--Создание внешнего объекта	
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

