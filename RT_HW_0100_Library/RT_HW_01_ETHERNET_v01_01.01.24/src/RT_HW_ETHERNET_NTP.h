//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//						БИБЛИОТЕКА ДЛЯ РАБОТЫ С ETHERNET_NTP
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef  RT_HW_ETHERNET_NTP_h
#define  RT_HW_ETHERNET_NTP_h
//-------------------------------------------------------------------------------------------------
#include "RT_HW_BASE.h"										//--Подключение базовой библиотеки;
#include "flprogEthernet.h"           						//--Подключение библиотеки Ethernet FLProg; 
#define  RT_HW_ETHERNET_NTP_VER 		(uint8_t)102		//--Номер версии;
#define  RT_HW_ETHERNET_NTP_VER_NAME 	"1.0.2 01.01.2024"	//--Наименование версии;
//-------------------------------------------------------------------------------------------------
#define  RT_HW_ETHERNET_NTP_PACKET_SIZE 48	//--Размер принимаемого пакета;
//=================================================================================================
//                           	1.КЛАСС RT_HW_ETHERNET_NTP
//=================================================================================================
class RT_HW_ETHERNET_NTP{
public:
//-------------------------------------------------------------------------------------------------
//						1.1.Структуры
//------------------------------------------------------------------------------------------------- 
RT_HW_STRUCT_SHED_TASK	task;			//--1.1.Данные для функции вызова задачи      RT_HW_Base.directTask (RT_HW_STRUCT_SHED_TASK &id);
RT_HW_STRUCT_TIME 		checkDIR;		//--1.2.Данные для функции задержки в функции RT_HW_Base.checkDelayMS(RT_HW_STRUCT_TIME     &id);
//-------------------------------------------------------------------------------------------------
//						1.2.Параметры пользовательских настроек 
//-------------------------------------------------------------------------------------------------
uint32_t localPort     = 8888;          //--1.Определение порта для UDP пакетов (используется стандартный номер);
char     timeServer[20]="time.nist.gov";//--2.Имя NTP сервера - сервер точного времени;
uint32_t zone=3;						//--3.Используемый часовой пояс;
uint32_t periodWD    =5000;			    //--4.Тайм-аут ответа NTP сервер                       (default=5000->5сек);
uint32_t timeStoreDNS=600000; 			//--5.Время хранения DNS кэша                          (default=60000->10 минут);
uint32_t period      =5000;				//--6.Период вызова времени от сервера точного времени (default=5000->5сек);
//-------------------------------------------------------------------------------------------------
//						1.3.Получаемые от сервера данные времени
//-------------------------------------------------------------------------------------------------
uint32_t time1900;          			//--1.Время в сек от 01.01.1900г.;
uint32_t timeUNIX;          			//--2.Время в сек от от 01.01.1970г.;
uint32_t vr;							//--3.Рабочая переменная;
uint8_t  hour,min,sec;      			//--4.Время:часы,минуты,секунды;
uint8_t  day,month,year,firstYear;      //--5.Дата: день,месяц,год-две младших цифры, год -первые две старших цифры;
//-------------------------------------------------------------------------------------------------
//						1.4.Параметры управления
//-------------------------------------------------------------------------------------------------
uint8_t  custom=0;        				//--1.Флаг настройки параметров; 
uint8_t  dir=0, agoDir=255;				//--2.Этапы управляющей задачи;;
uint8_t  run=1;            				//--3.Флаг для старта запуска запроса;
uint8_t  ok;              				//--4.Device ok;
uint8_t  fresh;           				//--5.Флаг обновленных данных;
uint8_t  codeError;						//--6.Код ошибки;
uint8_t  stateETH;						//--7.Состояние Ethernet;
uint8_t  stateUDP;						//--8.Состояние UDP;
uint8_t  freshDir=255;           		//--9.Флаг изменения этапа direct();
//-------------------------------------------------------------------------------------------------
//						1.5.Параметры обмена с NTP-сервером
//-------------------------------------------------------------------------------------------------
uint8_t  cntLoopMess=0;					//--1.Счетчик периодичности выполнения вывода сообщений в циклах loop();
uint16_t cntRequest=0, cntResponse=0;   //--2.Счетчики запросов и ответов;
uint16_t getDataQnt=0;               	//--3.Кол-во принятых байт;
uint8_t  packetBuffer[RT_HW_ETHERNET_NTP_PACKET_SIZE]; 	//--4.Буфер для хранения входящих и исходящих пакетов;
//-------------------------------------------------------------------------------------------------
//						1.6.Рабочие параметры
//-------------------------------------------------------------------------------------------------  
uint16_t codeMess=0;					//--1.Код диагностического сообщения (биты);
uint16_t cntMess=0;						//--2.Счетчик выводимых сообщений;							
uint8_t  idx;							//--3.Рабочий индекс;
uint8_t  bf8;
uint32_t timeBegin,timeEnd;				//--3.Рабочие параметры для работы со временем;
//=================================================================================================
//                   	2.1.Функция: Управления обменом c NTP-сервером
//=================================================================================================
void  directNtpEth(FLProgWiznetInterface &eth, FLProgUdpClient &udp, uint8_t &expRun){
(void)eth; (void)udp;
//-------------------------------------------------------------------------------------------------
if(expRun>0)  {expRun=0; run=1;}
//-------------------------------------------------------------------------------------------------
//				1.250 Статическая задержка в ms
//-------------------------------------------------------------------------------------------------
if(dir==250) {if(RT_HW_Base.checkDelayMS(checkDIR)) {return;} dir=checkDIR.pointTime; return;}	//--Задержка в ms;
//-------------------------------------------------------------------------------------------------
//				1.000.Настройка параметров
//-------------------------------------------------------------------------------------------------
if(dir==0){
if(custom==0){return;}		//--Ожидание настройки параметров;										
bitSet(codeMess,0);			//--Вывод стартового сообщения;
checkDIR.pointTime=10;  checkDIR.sizeDelay=10;	dir=250;	return;}	//--Переход по результатам настройки после задержки (ms);
//-------------------------------------------------------------------------------------------------
//              1.010.Ожидание сигнала запуска
//-------------------------------------------------------------------------------------------------
if(dir==10){
if(!run)    {return;}     //--Ожидание запуска запроса;                                     
dir=20;      return;}
//-------------------------------------------------------------------------------------------------
//              1.020.Подготовка к запуску
//-------------------------------------------------------------------------------------------------
if(dir==20){
if(!eth.getStatus())	{dir=10; return;}    //--Выход при если Ethernet не подключен;
dir=30;}
//-------------------------------------------------------------------------------------------------
//            	1.020.Отправка запроса
// Состояние stateUDP: 0-ошибка; 1-успешно; 2-ожидание;
//-------------------------------------------------------------------------------------------------
if(dir==30){
if(!eth.getStatus()){bitSet(codeMess,1);  codeError=20;			dir=10;  return;}    //--Выход при если Ethernet не отвечает;
if(!eth.isReady())														{return;}	 //--Ожидание готовности; 
//-------------------------------------------------------------------------------------------------
			 udp.begin(localPort);            		//--Инициализация UDP (это надо делать всегда? ... надо проверить!!!);
   stateUDP= udp.beginPacket(timeServer, 123);   	//--Подсоединение к порту 123 NTP-сервера;
//-------------------------------------------------------------------------------------------------
if(stateUDP==0)		{bitSet(codeMess,2);; 			 codeError=50; 	dir=10;	 return;}	//--Выход по ошибке; 
if(stateUDP==2) 	{checkDIR.pointTime=30;	checkDIR.sizeDelay=100;	dir=250; return;}	//--При неготовности повтор этапа после задержки; 
if(stateUDP >2) 	{bitSet(codeMess,3);			 codeError=51; 	dir=10;	 return;}	//--Выход по неопределенному коду состояния; 
if(stateUDP==1) 	{												//--
//------------------Подготовка данных для отправки в  NTP-сервер-----------------------------------
for(idx=0; idx<RT_HW_ETHERNET_NTP_PACKET_SIZE; idx++){packetBuffer[idx]=0;} //--Очистка буфера;
packetBuffer[0]  = 0b11100011;             // LI, Version, Mode
packetBuffer[1]  = 0;                      // Stratum, or type of clock
packetBuffer[2]  = 6;                      // Polling Interval
packetBuffer[12] = 49;
packetBuffer[13] = 0x4E;
packetBuffer[14] = 49;
packetBuffer[15] = 52;
timeBegin=RT_HW_MILLIS;	 bitSet(codeMess,4);//--Фиксация времени начала подготовки ;	
}
//-------------------------------------------------------------------------------------------------
udp.write(packetBuffer, RT_HW_ETHERNET_NTP_PACKET_SIZE);						//--Отправка запроса;
if(!udp.endPacket()){bitSet(codeMess,5);			codeError=52;	dir=10;	 return;}	//--Выход по ошибке;                            
cntRequest++;     	 timeBegin=RT_HW_MILLIS;              								//--Обработка параметров		
checkDIR.pointTime=40; 	checkDIR.sizeDelay=1000;					dir=250; return;}	//--Возврат на проверку ответа через 10ms; 
//-------------------------------------------------------------------------------------------------
//           	1.030.Ожидание ответа
//-------------------------------------------------------------------------------------------------
if(dir==40){
//-------------------------------------------------------------------------------------------------
timeEnd=RT_HW_MILLIS;
if(RT_HW_Base.getPastTime(timeBegin, timeEnd)>periodWD){								//--Проверка   тайм-аута ответа;
checkDIR.pointTime=10;	checkDIR.sizeDelay=1000;  					dir=250; return;}	//  Переход по тайм-ауту; 
//-------------------------------------------------------------------------------------------------
   getDataQnt=udp.parsePacket(); 														//--Проверка размера принятой посылки;
if(getDataQnt>0)  	{												dir=50;  return;}	//--Переход на обработку ответа  при наличии данных (сколько принятых данных должно быть???);
checkDIR.pointTime=dir; checkDIR.sizeDelay=10; 						dir=250; return;}	//--Возврат на проверку ответа через 10ms; 
//-------------------------------------------------------------------------------------------------
//             1.040.Чтение ответа
//-------------------------------------------------------------------------------------------------
if(dir==50){ 
udp.read(packetBuffer,RT_HW_ETHERNET_NTP_PACKET_SIZE);                  		//--Чтение пакета. В байтах 40-43 находятся сведения о времени;
cntResponse++;                                         						//--Увеличение счетчика прочитанных пакетов;            
timeUNIX=(((uint32_t)packetBuffer[40]<<24) | ((uint32_t)packetBuffer[41]<<16) | ((uint16_t)packetBuffer[42]<<8) | packetBuffer[43]) - RT_HW_UNIX_CORRECTION_1900;                  
run=0;
fresh=1;                                                    	//--Установка флага обновленных данных;
bitSet(codeMess,7);                                             //--Ответ принят;
dir=10; return;}                                             	//--Возврат на новый запрос к серверу NTP;  
//-------------------------------------------------------------------------------------------------
};
//=================================================================================================
//                   	2.2.Функция: Вывод по изменению номера текущего этапа(для тестирования программного обеспечения);
//=================================================================================================
void checkDirNtpEth(){if(agoDir!=dir){agoDir=dir; RT_HW_Base.consoleTest(String(F("NTP->dir")),dir,'E','U');}};
//=================================================================================================
//                 		2.4.Функция вспомогательная: преамбула сообщений
//=================================================================================================
void messBefore(){
RT_HW_Base.consoleVar(String(F("NTP="))); 
RT_HW_Base.consoleVar(cntMess,' ',5,'U'); 
RT_HW_Base.consoleCurrentTime();
};
//=================================================================================================
//                 		2.4.Функция вспомогательная: пакеты
//=================================================================================================
void messPacket(){
RT_HW_Base.consoleTest(String(F("Packet")),cntRequest,'/'); RT_HW_Base.consoleVar(cntResponse,'.');};
//=================================================================================================
//                 		2.3.Функция: Вывод сообщений функции directNTP() (для тестирования оборудования и сервера NTP);
//=================================================================================================
void messNtpEth(){
if(codeMess==0)                  {return;} 		//--Ожидание номера сообщения;
if(!RT_HW_Base.console.ok)       {return;}
//-------------------------------------------------------------------------------------------------
RT_HW_Base.mess.alig='L';
//-------------------------------------------------------------------------------------------------
//					2.3.1.Вывод заголовка
//-------------------------------------------------------------------------------------------------
if(bitRead (codeMess,0)){ 
   bitClear(codeMess,0);
   RT_HW_Base.consoleHead(String(F("NTP-сервер точного времени")),'=');
   RT_HW_Base.consoleBlank(9); 
   RT_HW_Base.consoleCurrentTime();
   RT_HW_Base.consoleTest(String(F(" Watch-dog ответов(сек)")),(uint16_t)(periodWD/1000),'.');  RT_HW_Base.consoleCR();}  
//-------------------------------------------------------------------------------------------------
if(codeMess==0)                  {return;} 		//--Выход, если больше нет сообщений;
//-------------------------------------------------------------------------------------------------
//					2.3.2.Не готовность Ethernet
//-------------------------------------------------------------------------------------------------
if(bitRead (codeMess,1)){ 
   bitClear(codeMess,1);	cntMess++;         //--Увеличение счетчика выводимого сообщения; 
   messBefore(); RT_HW_Base.consoleVar(String(F(" Ошибка по неготовности Ethernet.state=0."))); RT_HW_Base.consoleCR();} 
//-------------------------------------------------------------------------------------------------
//					2.3.3.Не готовность UDP
//-------------------------------------------------------------------------------------------------
if(bitRead (codeMess,2)){ 
   bitClear(codeMess,2);	cntMess++;         //--Увеличение счетчика выводимого сообщения;	 
   messBefore(); RT_HW_Base.consoleTest(String(F(" Ошибка по неготовности UDP->statе")),stateUDP,'.','U'); RT_HW_Base.consoleCR();}  
//-------------------------------------------------------------------------------------------------
//					2.3.4.Неопреленное состояние state UDP
//-------------------------------------------------------------------------------------------------
if(bitRead (codeMess,3)){ 
   bitClear(codeMess,3);	cntMess++;         //--Увеличение счетчика выводимого сообщения;	 
   messBefore(); RT_HW_Base.consoleTest(String(F(" Ошибка по состоянию UDP->statе")), stateUDP,'.','U'); RT_HW_Base.consoleCR();} 
//-------------------------------------------------------------------------------------------------
//					2.3.5.Запрос NTP-сервер
//-------------------------------------------------------------------------------------------------
if(bitRead (codeMess,4)){ 
   bitClear(codeMess,4);	cntMess++;         //--Увеличение счетчика выводимого сообщения;	 
   messBefore(); RT_HW_Base.consoleVar(String(F(" Запрос->"))); messPacket(); RT_HW_Base.consoleCR();}  
//-------------------------------------------------------------------------------------------------
//					2.3.6.Ошибка отправки запроса
//-------------------------------------------------------------------------------------------------
if(bitRead (codeMess,5)){ 
   bitClear(codeMess,5);	cntMess++;         //--Увеличение счетчика выводимого сообщения;	 
   messBefore(); RT_HW_Base.consoleVar(String(F(" Ошибка при отправке запроса."))); RT_HW_Base.consoleCR();}  
//-------------------------------------------------------------------------------------------------
//					2.3.6.Ответ NTP-сервер
//-------------------------------------------------------------------------------------------------
if(bitRead (codeMess,7)){ 
   bitClear(codeMess,7);	cntMess++;         //--Увеличение счетчика выводимого сообщения;	 
   messBefore(); RT_HW_Base.consoleVar(String(F(" Ответ-->"))); messPacket(); 
   RT_HW_Base.consoleTest(String(F(" Greenwich +0: timeUNIX")),timeUNIX,'E');}
//-------------------------------------------------------------------------------------------------
codeMess=0; return;                  
};
//=================================================================================================
};  //---END class RT_HW_ETHERNET_NTP
#endif //---RT_HW_ETHERNET_h
//=================================================================================================