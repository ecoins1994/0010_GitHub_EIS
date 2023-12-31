//##################################################################################################
//                                      I.ETHERNET
//##################################################################################################
#ifdef RT_HW_TEST_PERMIT_ETHERNET
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//=================================================================================================
//                            1.1.СОЗДАНИЕ ОБЪЕКТА ETHERNET
//=================================================================================================
//         Вариант с  шиной (SPI0) и пином(10) по умолчаниюю. Пин потом можно поменять.
//         Но если на этой шине висит ещё какое то устройство лучше применять второй вариант
//-------------------------------------------------------------------------------------------------
FLProgWiznetInterface WiznetInterface;
//-------------------------------------------------------------------------------------------------
//        Второй вариант с непосредственной привязкой к шине и пину.
//        Cсылку на шину(spiBus) можно так же передавать на другие устройства на этой шине
//-------------------------------------------------------------------------------------------------
//FLProgSPI spiBus(0);                                //--Создание объекта для привязки к требуемой шине SPI;
//FLProgWiznetInterface WiznetInterface(&spiBus, 29); //--Создание интерфейса для работы с чипом W5100(W5200,W5500); STM32;
//-------------------------------------------------------------------------------------------------
FLProgEthernetUDP Udp(&WiznetInterface);              //--Создание UDP клиента;
  uint16_t qntPrintMess=0; 
//=================================================================================================
//                            1.2.ФУНКЦИИ ДЛЯ ETHERNET
//=================================================================================================
//-------------------------------------------------------------------------------------------------
//                           1.2.1. Инициализация параметров Ethernet
//-------------------------------------------------------------------------------------------------
void  customEthernet(RT_HW_ETHERNET_DEV &id){
if(id.custom==1){return;}                                 //--Выход, если параметры инициализированы;   
if(id.cs==255)  {return;}                                 //--Определение cs;
WiznetInterface.setSsPin(id.cs);                          //--Настройка номера пина cs W5x00;  
WiznetInterface.mac(0x78, 0xAC, 0xC0, 0x2C, 0x3E, 0x28);  //--Установка MAC-адрес контроллера (лучше адрес прошитый производителем);
id.busy=id.statusFresh=id.linkFresh=0;                    //--Настройка рабочих параметров;
id.busyWD=5000;                                           //--Период watch-dog занятости шины =6000ms;
id.custom=1;                                              //--Установка флагов настройки параметров;
id.statusFresh=1;
};
//-------------------------------------------------------------------------------------------------
//                           1.2.2. Управление Ethernet
//-------------------------------------------------------------------------------------------------
void  directEthernet(RT_HW_ETHERNET_DEV &id){
//---------------------------------------------------------------------------------------
WiznetInterface.pool();                             //--Цикл работы интерфейса
//---------------------------------------------------------------------------------------
id.status=WiznetInterface.isReady();                //--Чтение текущего состояния         устройства  Ethernet;
id.link  =WiznetInterface.linkStatus();             //--Чтение текущего состояния связи с устройством Ethernet; 
//-------------------------------------------------------------------------------------------------
if(id.statusAgo!=id.status){                        //--ПРОВЕРКА ИЗМЕНЕНИЯ dvLineStatus:
   id.statusAgo =id.status; id.statusFresh=1;       //--Фиксация изменения параметра lineStatus (лучше это делать непосредственно в функции pool);
   id.chip      =WiznetInterface.hardwareStatus();  //--Обновление типа используемого чипа      (лучше это делать непосредственно в функции pool);                                                                            
   id.ip        =WiznetInterface.localIP();         //--Сохранение IP адреса;
}
//-------------------------------------------------------------------------------------------------
if(id.linkAgo !=id.link){                           //--ПРОВЕРКА ИЗМЕНЕНИЯ dvLinkStatus:
   id.linkAgo  =id.link;     id.linkFresh=1;        //--Фиксация изменения параметра lineStatus (лучше это делать непосредственно в функции pool);
   id.chip     =WiznetInterface.hardwareStatus();   //--Обновление типа используемого чипа      (лучше это делать непосредственно в функции pool);   
}
//-------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------
//                           1.2.3. Вывод на консоль состояние Ethernet
//-------------------------------------------------------------------------------------------------
void printEthernet(RT_HW_ETHERNET_DEV &id){
if(!RT_HW_Base.console.ok)                                        {return;} //--Выход, если консоль не готова;
if((id.statusFresh==0) && (id.linkFresh==0) && (id.printFirst==1)){return;} //--Ожидание изменения системных флагов;
  id.printFirst=1; id.statusFresh=id.linkFresh=0;  qntPrintMess++;          //--Установка/очистка флагов, инкремент счетчика;
//------------------------------------------------------------------------------------------------  
  RT_HW_Base.consoleVar(qntPrintMess, '.',4,'U');
  RT_HW_Base.consoleVar(String(F(" time=")));; RT_HW_Base.consoleVar(vMotorSec, ';',6,'U');
//------------------------------------------------------------------------------------------------  
  RT_HW_Base.consoleVar(String(F(" Ethernet: ")));
  RT_HW_Base.consoleVar(String(F(" Status=")));  
  if(id.status==1){RT_HW_Base.consoleVar(String(F("Включен; ")));} 
  else             {RT_HW_Base.consoleVar(String(F("Выключен;")));} 
//------------------------------------------------------------------------------------------------  
  RT_HW_Base.mess.alig='L';
  RT_HW_Base.consoleVar(String(F(" Link=")));
       if(id.link==FLPROG_ETHERNET_LINK_UNKNOWN){RT_HW_Base.consoleVar(String(F("Нет инициализации")),   ';',20);} 
  else if(id.link==FLPROG_ETHERNET_LINK_ON)     {RT_HW_Base.consoleVar(String(F("Связь установлена")),   ';',20);} 
  else if(id.link==FLPROG_ETHERNET_LINK_OFF)    {RT_HW_Base.consoleVar(String(F("Нет ответа на запрос")),';',20);}    
  else                                          {RT_HW_Base.consoleVar(String(F("Неизвестная ошибка")),  ';',20);} 
//------------------------------------------------------------------------------------------------   
  RT_HW_Base.consoleVar(String(F(" chip="))); RT_HW_Base.mess.modePin='A';
       if(id.chip==FLPROG_ETHERNET_NO_HARDWARE){RT_HW_Base.consoleVar(String(F("Wxxxx")),';');}
  else if(id.chip==FLPROG_ETHERNET_W5100)      {RT_HW_Base.consoleVar(String(F("W5100")),';');}
  else if(id.chip==FLPROG_ETHERNET_W5200)      {RT_HW_Base.consoleVar(String(F("W5200")),';');}
  else if(id.chip==FLPROG_ETHERNET_W5500)      {RT_HW_Base.consoleVar(String(F("W5500")),';');}
  else                                         {RT_HW_Base.consoleVar(String(F("xxxxx")),';');}
//------------------------------------------------------------------------------------------------    
  RT_HW_Base.mess.modePin='A';  
  RT_HW_Base.consoleTest(String(F(" cs")),id.cs,',','P'); 
  RT_HW_Base.consoleVar(String(F(" IP="))); Serial.print(id.ip);   Serial.print(';'); 
  RT_HW_Base.consoleCR();
};
//=================================================================================================
#else
void  customEthernet(RT_HW_ETHERNET_DEV &id){(void)id;};
void  directEthernet(RT_HW_ETHERNET_DEV &id){(void)id;};
void  printEthernet (RT_HW_ETHERNET_DEV &id){(void)id;};
#endif
//=================================================================================================
