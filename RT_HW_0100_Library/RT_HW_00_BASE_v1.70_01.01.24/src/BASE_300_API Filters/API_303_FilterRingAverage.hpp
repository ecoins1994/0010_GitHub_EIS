//=================================================================================================
//   RT_HW_FILTER_RING_AVERAGE.h - бегущее среднее с кольцевым буфером;
//   Использованы идеи и алгоритмы https://alexgyver.ru/gyverfilters/
//-------------------------------------------------------------------------------------------------
/*
Фильтр бегущего среднего.
Алгоритм фильтра работает по принципу буфера, в котором для усреднения хранятся N последних измерений. 
При каждом вызове фильтра буфер сдвигается, в него добавляется новое значение и убирается самое старое,
 далее буфер усредняется по среднему арифметическому. 

При первых четырех вызовах(настраиваемый параметр) буфер заполняется только текущим принятым значением. 
Рекомендуется выбирать N четным. 		
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++				  
Фильтр быстрый. Ниже приведены замеры для N=32:
  Arduino Nano	    int16_t=44-48 мкс; float= 32 мкс;
  ESP32S       	    int16_t=2-4 мкс;   float=4-6 мкс;
  STM32F103C  	    int16_t=1-2 мкс;   float=4-5 мкс; 
  STM32F401CC 	    int16_t=1-2 мкс;   float=1-2 мкс;
  RaspBerry Pi Pico int16_t<1 мкс;     float=2 мкс;
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/ 
//=================================================================================================				  
#ifndef RT_HW_FILTER_RING_AVERAGE_h
#define RT_HW_FILTER_RING_AVERAGE_h
//-------------------------------------------------------------------------------------------------
template < typename TYPE, uint8_t vSize >
class RT_HW_FILTER_RING_AVERAGE{
//-------------------------------------------------------------------------------------------------
public:
TYPE    buff[vSize];//--Буфер для хранения фильтруемых значений;
TYPE    in,ago,vr; 	//--Входное значение, отфильтрованные значения до и после фильтрации;
int32_t sum;        //--Регистр накопления для усреднения;
uint8_t index=255;	//--Индекс движения по массиву;
uint8_t eql;   		//--Флаг совпадения последнего результата и элементов массива;
uint8_t cntReset=0; //--Счетчик для пропуска первых qntReset усреднений;
uint8_t qntReset=4; //--Кол-во первых пропусков измерений;
//-------------------------------------------------------------------------------------------------
TYPE filtered(TYPE val) {
if((index==255) || (cntReset<qntReset)){
    if(cntReset<qntReset) {cntReset++;}
	fill(val); in=val; ago=val; vr=val; eql=0; index=0; sum=0;
    for(index=0; index<vSize; index++){sum=sum+val;} index=0; return vr;} //--Заполнение буфера при первом вызове или по рестарту;															
//-------------------------------------------------------------------------------------------------
in=val; ago=vr;	                                       					      //--Сохранение предущего отфильтрованного значения;
//-------------------------------------------------------------------------------------------------
sum=sum-buff[index];     	//--Вычитаем старое значение;
        buff[index]=val;    //--Сохраняем новое;
sum=sum+buff[index];        //--Прибавляем новое;
vr=(TYPE)(sum/vSize);       //--Вычисляем новое;
if(++index>=vSize){index=0;}//--Изменение индекса на новую позицию;
return vr;}
//=================================================================================================
uint8_t getN()        {return vSize;}							//==Функция возвращает порядок фильтра;
void    reset()       {index=255;}								//==Функция подготавливаетfilter к сбросу функцию filtered();
void    fill(TYPE val){for(index=0; index<vSize; index++){buff[index]=val;};} 	//==Фyнкция заполнение буфера значениями val;
//-------------------------------------------------------------------------------------------------
uint8_t check(){												//==Установка eql (для внешних функций);																							
	            if(in!=ago)                     {eql=0; return eql;}    //--Выход со сбросом eql при новых входных данных;
				if(eql>=2)                      {       return eql;}    //--Выход при многократном совпадении; 
				if(eql==1)                      {eql=2; return eql;}    //--Изменение состояния совпадения от однократного к многократному; 
				if(index!=0)                    {       return eql;}	//--Ожидание возрата index в начало буфера для дальнейшей
				index=0; do{if(buff[index]!=in) {eql=0; return eql;} 	//--Проверка на совпадения
                if(++index>=vSize)   		    {       break;     }	//                 элементов массива;
					       }while(1);            eql=1; return eql;}	//--Установка  однократного совпадения;					       
//-------------------------------------------------------------------------------------------------
};
#endif

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++				  
#ifndef RT_HW_FILTER_RING_AVERAGE_FLOAT_h
#define RT_HW_FILTER_RING_AVERAGE_FLOAT_h
//-------------------------------------------------------------------------------------------------
template < uint8_t vSize >
class RT_HW_FILTER_RING_AVERAGE_FLOAT{
//-------------------------------------------------------------------------------------------------
public:
float   buff[vSize];//--Буфер для хранения фильтруемых значений;
float   in,ago,vr;  //--Входное значение, отфильтрованные значения до и после фильтрации;
float   sum;        //--Регистр накопления для усреднения;
uint8_t index=255;	//--Индекс движения по массиву;
uint8_t eql;   		//--Флаг совпадения последнего результата и элементов массива;
//-------------------------------------------------------------------------------------------------
float filtered(float val) {
if(index==255){fill(val); index=0; in=val; ago=val; vr=val; eql=0; sum=val*vSize; return vr;} //--Заполнение буфера при первом вызове или по рестарту;															
//-------------------------------------------------------------------------------------------------
in=val; ago=vr;	                                       					//--Сохранение предущего отфильтрованного значения;
//-------------------------------------------------------------------------------------------------
sum=sum-buff[index];     	//--Вычитаем старое значение;
        buff[index]=val;    //--Сохраняем новое;
sum=sum+buff[index];        //--Прибавляем новое;
vr=sum/vSize;               //--Вычисляем новое;
if(++index>=vSize){index=0;}//--Изменение индекса на новую позицию;
return vr;}
//=================================================================================================
uint8_t getN()        {return vSize;}							//==Функция возвращает порядок фильтра;
void    reset()       {index=255;}								//==Функция подготавки к сбросу функцию filtered();
void    fill(float val){for(index=0; index<vSize; index++){buff[index]=val;};} 	//==Фyнкция заполнение буфера значениями val;
//-------------------------------------------------------------------------------------------------
uint8_t check(){												//==Установка eql (для внешних функций);																							
	            if(in!=ago)                     {eql=0; return eql;}    //--Выход со сбросом eql при новых входных данных;
				if(eql>=2)                      {       return eql;}    //--Выход при многократном совпадении; 
				if(eql==1)                      {eql=2; return eql;}    //--Изменение состояния совпадения от однократного к многократному; 
				if(index!=0)                    {       return eql;}	//--Ожидание возрата index в начало буфера для дальнейшей
				index=0; do{if(buff[index]!=in) {eql=0; return eql;} 	//--Проверка на совпадения
                if(++index>=vSize)   		    {       break;     }	//                 элементов массива;
					       }while(1);            eql=1; return eql;}	//--Установка  однократного совпадения;					       
//-------------------------------------------------------------------------------------------------
};
#endif

