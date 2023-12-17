//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//   RT_HW_FILTER_MEDIAN_3.h - быстрый медианный фильтр 3-го порядка.
//   Использованы идеи,алгоритмы,описания https://alexgyver.ru/gyverfilters/
//-------------------------------------------------------------------------------------------------
// Медианный фильтр находит среднее значение не усредняя, а выбирая его из представленных. 
// Алгоритм для медианы 3-го порядка (выбор из трёх значений) предложенный Андреем Степановым  
// занимает одну строку кода и выполняется быстрее аналогичных за счёт меньшего количества сравнений:
// middle=a < b) ? ((b < c) ? b : ((c < a) ? a : c)) : ((a < c) ? a : ((c < b) ? b : c));
//--------------------------------------------------------------------------------------------------
//   Алгорим работы фильтра [filter(val)]
//   1.При первом вызове или после сброса(reset()) буфер заполняется входным принятым значением.
//	 3.Далее входные данные сортируются в порядке возрастания.
//   4.Выбирается серединный результат (медиана). 
//--------------------------------------------------------------------------------------------------
//   Доступные значения:
//     buff[]-буфер фильтруемых значений.
//     in -последнее входное значение; 
//     ago-предыдущее отфильтрованное значение; 
//     vr -последнее отфильтрованное  значение;
//     index-текущий индекса (указывает на выбанное значение);
//     size -значение порядка фильтра. Равен 3.
//     eql  -признак совпадения входных данных c со всеми элементами массива.
//           =0 не совпадают; =1 - совпали в 1-й раз; =2 совпали подряд мнокократно.
//           eql устанавливается отдельной функцией check(), которая вызывается после фильтрации.
//================================= API ===========================================================
//   RT_HW_FILTER_MEDIAN_3<TYPE> filter; - Создание c объекта с назначенным именем. 
//                                         Пример: RT_HW_FILTER_MEDIAN_3<int16_t> filter;
//   filtered(val) - Вызов функции фильтрации с передачей нового значения переменной val.
//                   Возвращает отфильтрованное значение vr. 
//                   При первом вызове или после функции сброса (reset()) заполняет буфер,;
//   reset()       - Подготавливает к сбросу функцию filtered();
//   fiil(val)     - Заполнение буфера значением val;
//================================= Быстродействие ==============================================
//  Arduino Nano	  int16_t=8 мкс; float=20 мкс;
//  Arduino Mega	  int16_t=8 мкс; float= 
//  ESP8266     	  int16_t=8 мкс; float= 
//  ESP32S       	  int16_t=2 мкс; float=3 мкс;
//  STM32F103C  	  int16_t=2 мкс; float=6 мкс; 
//  STM32F401CC 	  int16_t<1 мкс; float<2 мкс;
//  RaspBerry Pi Pico int16_t<1 мкс; float=2 мкс; 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++				  
#ifndef RT_HW_FILTER_MEDIAN_3_h
#define RT_HW_FILTER_MEDIAN_3_h
#include "RT_HW_BASE.h"
//-------------------------------------------------------------------------------------------------
template < typename TYPE >
class RT_HW_FILTER_MEDIAN_3{
private:
uint8_t flt_N=3;	//--Порядок фильтра;
uint8_t i;			//--Рабочий индекс;
//-------------------------------------------------------------------------------------------------
public:
TYPE    buff[3];    //--Буфер для хранения фильтруемых значений;
TYPE    in,ago,vr;  //--Входное значение, отфильтрованные значения до и после фильтрации;
uint8_t index=255;	//--Индекс движения по массиву;
uint8_t eql=0;   	//--Флаг совпадения последнего результата и элементов массива;
//=================================================================================================-
TYPE filtered(TYPE val) {	                 					//==Функция фильтрации;
if(index==255){fill(val); index=2; in=val; ago=val; vr=val; return vr;} //--Заполнение буфера при первом вызове или по рестарту;																
//-------------------------------------------------------------------------------------------------
in=val; ago=vr;	                                    			//--Сохранение предущего отфильтрованного значения;
//-------------------------------------------------------------------------------------------------
buff[index]=val;												//--Сохранение входного значения по текущему индексу;
vr=RT_HW_MIDLE(buff[0],buff[1],buff[2]);	   					//--Выбор нового значения после фильтра;
if(++index>=flt_N){index=0;}                                		//--Изменение индекса на новую позицию;
return vr;}                                    					//--Выход;
//=================================================================================================
uint8_t getN()                          {return flt_N;}			//==Функция возвращает порядок фильтра;
void    reset()       {index=255;}								//==Функция подготовки к сбросу функцию filtered();
void    fill(TYPE val){for(i=0; i<3; i++){buff[i]=val;};} 		//==Фyнкция заполнение буфера значениями val;
uint8_t check(){												//==Установка eql (для внешних функций);																							
	            if(in!=ago)             {eql=0; return eql;}    //--Выход со сбросом eql при новых входных данных;
				if(eql>=2)              {       return eql;}    //--Выход при многократном совпадении; 
				if(eql==1)              {eql=2; return eql;}    //--Изменение состояния совпадения от однократного к многократному; 
				if(index!=0)            {       return eql;}	//--Ожидание возрата index в начало буфера для дальнейшей
				i=0; do{if(buff[i]!=in) {eql=0; return eql;} 	//--Проверка на совпадения
                if(++i>=flt_N)   		{       break;     }	//                 элементов
					   }while(1);                              	//                     массива;
						                 eql=1; return eql;}	//--Установка  однократного совпадения;					       
//-------------------------------------------------------------------------------------------------
};
#endif
