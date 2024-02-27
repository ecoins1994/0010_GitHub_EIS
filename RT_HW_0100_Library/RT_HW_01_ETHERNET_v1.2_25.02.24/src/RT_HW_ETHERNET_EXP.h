//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//						БИБЛИОТЕКА ДЛЯ РАБОТЫ C ETHERNET	
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef  RT_HW_ETHERNET_EXP_h
#define  RT_HW_ETHERNET_EXP_h
//-------------------------------------------------------------------------------------------------
#include "RT_HW_BASE.h"									//--Подключение базовой библиотеки;
#include "flprogEthernet.h"           					//--Подключение библиотеки Ethernet FLProg; 
#define   RT_HW_ETHERNET_DEV_VER 		 (uint8_t)102		//--Номер версии;
#define   RT_HW_ETHERNET_DEVER_NAME 	"1.0.2 01.01.2024"	//--Наименование версии;

//=================================================================================================
//                            1.КЛАСС расширения  "flprogEthernet.h" (возможно уйдет в flprogEthernet.h);
//=================================================================================================
class   RT_HW_ETHERNET_EXP{
public:
//-------------------------------------------------------------------------------------------------
//						1.1.Структуры
//-------------------------------------------------------------------------------------------------
RT_HW_STRUCT_TIME 		checkDIR;		//--1.1.Данные для функции задержки в функции RT_HW_Base.checkDelayMS(RT_HW_STRUCT_TIME     &id);
//-------------------------------------------------------------------------------------------------
//						1.2.Параметры пользовательских настроек 
//-------------------------------------------------------------------------------------------------
uint8_t  pinCS =255;  					//--Пин CS         (уже имеется в библиотеке "flprogEthernet.h" - потом можно убрать);
uint8_t  spiBUS=255;  					//--Номер шины SPI (уже имеется в библиотеке "flprogEthernet.h" - потом можно убрать);
uint8_t  pinRST=255, permitPinRST=0;	//--Пин сброса 	  (RST) и разрешение на его использование;
uint8_t  pinINT=255, permitPinINT=0;	//--Пин прерывания(INT) и разрешение на его использование;
uint8_t  mac[6]={0x78, 0xAC, 0xC0, 0x2C, 0x3E, 0x44}; //--MAC-адрес по умолчанию;
IPAddress ip={0,0,0,0};
//-------------------------------------------------------------------------------------------------
//						1.3.Данные получаемые от устройства Ethernet 
//-------------------------------------------------------------------------------------------------
uint8_t  chip=3;						//--Код   чипа        "flprogEthernet.h";
uint8_t  status=255;   					//--Cостояние статуса "flprogEthernet.h";
uint8_t  codeError=0;					//--Код ошибки        "flprogEthernet.h";
uint8_t  isReady=255;					//--Флаг готовности   "flprogEthernet.h"; 
uint8_t  isConnect=0; 					//--Состояние подключ."flprogEthernet.h";
uint8_t  statusError=0;					//--Код ошибок        "RT_HW_ETHERNET_EXP";
//-------------------------------------------------------------------------------------------------
//						1.4.Параметры управления
//-------------------------------------------------------------------------------------------------
uint8_t  dir=0, agoDir=255;				//--4.1.Этапы управляющей задачи;;
uint8_t  custom=0;      				//--4.2.Флаг настройки параметров; 
uint16_t stateError=0;					//--4.3.Побитовые флаги ошибок;
//-------------------------------------------------------------------------------------------------
//						1.5.Параметры диагностические
//-------------------------------------------------------------------------------------------------
uint8_t  freshCustom=0;					//--Флаг изменения настроек custom(0,1,2);
uint8_t  freshStatus=0;					//--Флаг изменения статуса;
uint8_t  freshConnect=0; 				//--Флаг установки соединения;
uint8_t  freshDisConnect=0;				//--Флаг разрыва   соединения;
uint8_t  freshError=0;					//--Флаг изменения кода ошибки;
uint8_t  head=0;						//--Флаг вывода заголовка о работе Ethernet;
//-------------------------------------------------------------------------------------------------
uint8_t  cntError=0;					//--Счетчик ошибок  Ethernet;
uint8_t  cntMess=0; 					//--Счетчик выведенных сообщений;		
uint8_t  cntLoopMess=0;					//--Счетчик периодичности выполнения вывода сообщений в циклах loop();
uint8_t  isNeedSendConnectMessage   =1; //--Флаг "Требуется установить   связь с Ethernet";
uint8_t  isNeedSendDisconnectMessage=1; //--Флаг "Требуется рассоединить связь с Ethernet";
uint8_t  bf;							//--Рабочий регистр;

//=================================================================================================
//                            2.1.Функция: Расширение функции pool библиотеки "flprogEthernet.h"
//=================================================================================================
void directExpEth(FLProgWiznetInterface &id){
//-------------------------------------------------------------------------------------------------
//				1.250 Статическая задержка в ms
//-------------------------------------------------------------------------------------------------
if(dir==250) {if(RT_HW_Base.checkDelayMS(checkDIR)) {return;} dir=checkDIR.pointTime; return;}	//--Задержка в ms;
//-------------------------------------------------------------------------------------------------
//				1.000.Настройка параметров
//-------------------------------------------------------------------------------------------------
if(dir==0){
  if(custom==0)	{return;}															//--Ожидание настройки параметров;										
  codeError=0;	head=0;																//--Очистка параметров; 	
  if(!RT_HW_Base.spiCheckBus(id.spiBus())) {		       bitSet(stateError,15);} //--Проверка номера шины;
  bf=(uint8_t)id.pinCs();															//--Преобразование pinCs в формат uint8_t;
  if(!RT_HW_Base.checkPinPGM(RT_HW_PGM_PIN_DOT_ID,bf))    {bitSet(stateError,14);}	//--Проверка номера пина cs;
  if( RT_HW_Base.checkPinPGM(RT_HW_PGM_PIN_DOT_ID,pinRST)){permitPinRST=1;}			//--Проверка номера пина cs;
  if( RT_HW_Base.checkPinPGM(RT_HW_PGM_PIN_DOT_ID,pinINT)){permitPinINT=1;}			//--Проверка номера пина cs;  
  freshCustom=1;																	//--Флаг изменения настройки
  if(stateError)  {custom=2;  dir=210; return;}										//--При фатальных ошибках переход на заглушку;
  if(permitPinRST){digitalWrite(pinRST,1); pinMode(pinRST,OUTPUT);}					//--Настройка пина RST(аппратный сброс чипа) на вывод;
  if(permitPinINT){digitalWrite(pinINT,0); pinMode(pinINT,INPUT_PULLUP);}			//--Настройка пина INT(прерывания  от  чипа) на ввод с подтяжкой к Vcc;
  custom=1; 																		//--Установка успешной настройки;
  checkDIR.pointTime=10; checkDIR.sizeDelay=10; dir=250; return;} 					//--После задержки 10ms переход на продолжение;	
//-------------------------------------------------------------------------------------------------
//				1.010.Сброс чипа
//-------------------------------------------------------------------------------------------------
if(dir==10){
  if(permitPinRST){digitalWrite(pinRST,0); delayMicroseconds(5); digitalWrite(pinRST,1);}//--Аппаратный  сброс чипа;
  else            {; //id.softReset();		//--Выдает ошибку компиляции-> private: FLProgWiznetClass _hardware;
                  }																	//--Программный сброс чипа;
  checkDIR.pointTime=20; checkDIR.sizeDelay=50; dir=250; return;} 					//--После задержки 50ms переход на продолжение;	
//-------------------------------------------------------------------------------------------------
//				1.020.Периодический опрос 
//-------------------------------------------------------------------------------------------------
if(dir==20){
  id.pool();
  ip=id.localIP();  
  bf=id.getStatus(); if(status   !=bf){status   =bf; freshStatus=1; ip=id.localIP();}
  bf=id.getError();  if(codeError!=bf){codeError=bf; freshError=1;}
  bf=id.isReady();   if(isReady  !=bf){isReady  =bf;
                     if(isReady){if( isNeedSendConnectMessage){freshConnect   =1; isNeedSendConnectMessage=0; isNeedSendDisconnectMessage=1;}}
                     else       {if(!isNeedSendConnectMessage){freshDisConnect=1; isNeedSendConnectMessage=1; isNeedSendDisconnectMessage=0;}}}
}					 
//-------------------------------------------------------------------------------------------------
//				1.210.Обработка ошибок 
//-------------------------------------------------------------------------------------------------
if(dir==210){;}
//-------------------------------------------------------------------------------------------------
};
//=================================================================================================
//                            2.2.Функция: Вывод номера текущего этапа(для тестирования программного обеспечения)
//=================================================================================================
void checkDirExpEth(){if(agoDir!=dir){agoDir=dir; RT_HW_Base.consoleTest(String(F("ETH->dir")),agoDir,'E','U'); }};
//=================================================================================================
//                            2.3.1.Функция(вспомогательная)): Вывод сообщений функции directEth()
//=================================================================================================
void  messHeadExpEth(FLProgWiznetInterface &id){
  RT_HW_Base.consoleTest(String(F("Eth")),            ++cntMess,  '~','U');
  RT_HW_Base.consoleTest(String(F(" cs")),     (uint8_t)id.pinCs(), ';','P');
  RT_HW_Base.consoleTest(String(F(" bus")),    (uint8_t)id.spiBus(),';','U');};
//=================================================================================================
//                            2.3.2.Вывод диагностических сообщений (для тестирования оборудования);
//=================================================================================================
void messExpEth(FLProgWiznetInterface &id, uint8_t vPeriodMessLoop=0){
(void) id;
if(++cntLoopMess<vPeriodMessLoop){return;} cntLoopMess=0;
if(!RT_HW_Base.console.ok)       {return;}
//-------------------------------------------------------------------------------------------------
//                   	1.Одноразовый вывод заголовка
//-------------------------------------------------------------------------------------------------
if(freshCustom){freshCustom=0;
if(head==0)  {head=1; RT_HW_Base.consoleHead(String(F("ETHERNET")),'=');  messHeadExpEth(id);}
if(custom==1){RT_HW_Base.consoleVar (String(F(" custom->1:  Успешная инициализация параметров(пины,шина).")));}
if(custom==2){RT_HW_Base.consoleTest(String(F(" custom->2:  Ошибка инициализации параметров->statusError.")),statusError,':','H');
  if(bitRead(statusError,15)){RT_HW_Base.consoleVar(String(F(" Недопустимый номер шины.")));}
  if(bitRead(statusError,14)){RT_HW_Base.consoleVar(String(F(" Недопустимый пин CS.")));}}
RT_HW_Base.consoleCR();}
//-------------------------------------------------------------------------------------------------
//                 		2.Вывод при изменении статуса, соединения
//-------------------------------------------------------------------------------------------------
if(freshStatus){freshStatus=0;
  messHeadExpEth(id);		//--Вывод заголовка сообщения;
  RT_HW_Base.consoleVar(String(F(" status->"))); 
  RT_HW_Base.consoleVar(status,':',0,'U');
  RT_HW_Base.consoleBlank(2);
if(status== 0){RT_HW_Base.consoleVar(String(F("Нет готовности чипа")));}
if(status== 1){RT_HW_Base.consoleVar(String(F("Чип готов к работе")));}
if(status== 2){RT_HW_Base.consoleVar(String(F("Ожидание инициализации")));}
if(status== 3){RT_HW_Base.consoleVar(String(F("Ожидание DHCP")));}
if(status== 4){RT_HW_Base.consoleVar(String(F("Ожидание DNS")));}
if(status== 5){RT_HW_Base.consoleVar(String(F("Ожидание UDP")));}
if(status== 6){RT_HW_Base.consoleVar(String(F("Ожидание соединения с клиентом через Ethernet")));}
if(status== 7){RT_HW_Base.consoleVar(String(F("Связь установлена")));}
if(status== 8){RT_HW_Base.consoleVar(String(F("Чип Ethernet инициализирован")));}
if(status== 9){RT_HW_Base.consoleVar(String(F("Ожидание подключения Ethernet")));}
if(status==10){RT_HW_Base.consoleVar(String(F("Ожидание соединения с клиентом через Wi-Fi")));}
if(status==11){RT_HW_Base.consoleVar(String(F("Ожидание начала соединения с клиентом через Ethernet")));}
if(status==12){RT_HW_Base.consoleVar(String(F("Ожидание ответа  от Web-сервера")));}
if(status==13){RT_HW_Base.consoleVar(String(F("Ожидание запроса на Web-сервер")));}
if(status==14){RT_HW_Base.consoleVar(String(F("Ожидание отправки пакета на UDP-сервер")));}
RT_HW_Base.consoleChar('.');
RT_HW_Base.consoleCR();
}
//-------------------------------------------------------------------------------------------------
//            			3.Вывод при изменении кода ошибки
//-------------------------------------------------------------------------------------------------
if(freshError){freshError=0; 
  messHeadExpEth(id);		//--Вывод заголовка сообщения;
  RT_HW_Base.consoleVar(String(F(" error->"))); 
  RT_HW_Base.consoleVar(codeError,':',0,'U');
  RT_HW_Base.consoleBlank(2);
if(codeError== 0){RT_HW_Base.consoleVar(String(F("Ошибки сброшены, нет ошибок")));}
if(codeError==10){RT_HW_Base.consoleVar(String(F("Ошибка по готовности Ethernet")));}
if(codeError==11){RT_HW_Base.consoleVar(String(F("Ошибка инициализации Ethernet")));}
RT_HW_Base.consoleCR();
}
//-------------------------------------------------------------------------------------------------
//              		4.Вывод при подключении Ethernet
//-------------------------------------------------------------------------------------------------
if(freshConnect){freshConnect=0;  
  messHeadExpEth(id);		//--Вывод заголовка сообщения;
  RT_HW_Base.consoleVar(String(F(" connect=1:  ETHERNET ПОДКЛЮЧЕН! ")),'~');
//RT_HW_Base.consoleTest(String(F(" chip")),            id.getChip(),';','U'); //--Функция не реализована(ошибка компиляции);
  RT_HW_Base.consoleCR();  
  for(uint8_t i=0; i<6; i++){mac[i]=id.mac()[i];}
  RT_HW_Base.ethMacAdrToString(mac);		RT_HW_Base.consoleTest(String(F("MAC")), 	RT_HW_Base.mess.str,';'); RT_HW_Base.consoleBlank(1);
  RT_HW_Base.ethIpToString(id.localIP());  	RT_HW_Base.consoleTest(String(F("IP")), 	RT_HW_Base.mess.str,'E'); 
  RT_HW_Base.ethIpToString(id.dns());		RT_HW_Base.consoleTest(String(F("DNS")), 	RT_HW_Base.mess.str,';'); RT_HW_Base.consoleBlank(2);
  RT_HW_Base.ethIpToString(id.subnet());	RT_HW_Base.consoleTest(String(F("Subnet")), RT_HW_Base.mess.str,';'); RT_HW_Base.consoleBlank(2);   
  RT_HW_Base.ethIpToString(id.gateway());  	RT_HW_Base.consoleTest(String(F("Gateway")),RT_HW_Base.mess.str,'E');   	
}
//-------------------------------------------------------------------------------------------------
//                		5.Вывод при отключении Ethernet
//-------------------------------------------------------------------------------------------------
if(freshDisConnect){freshDisConnect=0;
  messHeadExpEth(id);		//--Вывод заголовка сообщения;
  RT_HW_Base.consoleVar (String(F(" connect=0:  ETHERNET ОТКЛЮЧЕН!!! "))); 
  RT_HW_Base.consoleCR(2);
}
//-------------------------------------------------------------------------------------------------
}  		//---END printEthMess()
//=================================================================================================
};		//---END class RT_HW_ETHERNET
//=================================================================================================
#endif 	//---RT_HW_ETHERNET_h
//=================================================================================================
