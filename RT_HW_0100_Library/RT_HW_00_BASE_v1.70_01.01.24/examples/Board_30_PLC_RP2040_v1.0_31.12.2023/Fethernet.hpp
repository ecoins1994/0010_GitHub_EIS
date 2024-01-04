//##################################################################################################
//                                      I.ETHERNET
//##################################################################################################

//=================================================================================================
#ifdef RT_HW_TEST_ETH_SERVER 
void workEthServer(FLProgEthernetServer &id){
if(!id.connected())       {return;}
if(!id.available())       {return;}
if(!RT_HW_Base.console.ok){return;}
  Serial.println("=====================================================================");
  Serial.println("Клиент подключился");
  Serial.println("=====================================================================");
  bool currentLineIsBlank = true;
  while (id.connected()){
    if (id.available()){
      char c = id.read();
      Serial.write(c);
      if (c == '\n' && currentLineIsBlank)
      {
        // send a standard http response header
        id.println("HTTP/1.1 200 OK");
        id.println("Content-Type: text/html");
        id.println("Connection: close");
        id.println("Refresh: 5");
        id.println();
        id.println("<!DOCTYPE HTML>");
        id.println("<html>");
        // output the value of each analog input pin
        for (int analogChannel = 0; analogChannel < 6; analogChannel++)
        {
          int sensorReading = analogRead(analogChannel);
          id.print("analog input ");
          id.print(analogChannel);
          id.print(" is ");
          id.print(sensorReading);
          id.println("<br />");
        }
        id.println("</html>");
        break;
      }
      if (c == '\n')
      {
        // you're starting a new line
        currentLineIsBlank = true;
      }
      else if (c != '\r')
      {
        currentLineIsBlank = false;
      }
    }
  }
  id.stopConnection();
  Serial.println("=====================================================================");
  Serial.println("Клиент отключён");
  Serial.println("=====================================================================");
}
//-------------------------------------------------------------------------------------------------
#else
void workEthServer(FLProgEthernetServer &id){(void)id;}
#endif


#ifdef RT_HW_TEST_ETH_SERVER 
void printStatusMessages(FLProgEthernetServer &id)
{
/*
  if (id.getStatus() != ethernetStatus)
  {
    ethernetStatus = WiznetInterface.getStatus();
    Serial.println();
    Serial.print("Статус интерфейса - ");
    Serial.println(flprog::flprogStatusCodeName(ethernetStatus));
  }
 */ 
/* 
  if (WiznetInterface.getError() != ethernetError)
  {
    ethernetError = WiznetInterface.getError();
    if (ethernetError != FLPROG_NOT_ERROR)
    {
      Serial.println();
      Serial.print("Ошибка интерфейса - ");
      Serial.println(flprog::flprogErrorCodeName(ethernetError));
    }
  }
 */ 
//-------------------------------------------------------------------------------------------------
if(id.getStatus()!=ethServerStatus){
   ethServerStatus=id.getStatus();
    Serial.println();
    Serial.print("Статус сервера - ");
    Serial.println(flprog::flprogStatusCodeName(ethServerStatus));
  }
//-------------------------------------------------------------------------------------------------  
if(ethServer.getError() != ethServerError){
ethServerError = id.getError();
if(ethServerError!=FLPROG_NOT_ERROR){
      Serial.println();
      Serial.print("Ошибка сервера - ");
      Serial.println(flprog::flprogErrorCodeName(ethServerError));
    }
  }

//=================================================================================================
//               1.15.Генератор случайных чисел.
//================================================================================================= 
 // printConnectMessages();
 // printDisconnectMessages();
}

#else
void printStatusMessages(FLProgEthernetServer &id){(void)id;}
#endif  


/*
void printConnectMessages()
{
  if (!WiznetInterface.isReady())
  {
    return;
  }
  if (!isNeedSendConnectMessage)
  {
    return;
  }
  Serial.println("Ethernet подключён!");
  Serial.print("Ip - ");
  Serial.println(WiznetInterface.localIP());
  Serial.print("DNS - ");
  Serial.println(WiznetInterface.dns());
  Serial.print("Subnet - ");
  Serial.println(WiznetInterface.subnet());
  Serial.print("Gateway - ");
  Serial.println(WiznetInterface.gateway());
  isNeedSendConnectMessage = false;
  isNeedSendDisconnectMessage = true;
}

void printDisconnectMessages()
{
  if (WiznetInterface.isReady())
  {
    return;
  }
  if (isNeedSendConnectMessage)
  {
    return;
  }
  if (!isNeedSendDisconnectMessage)
  {
    return;
  }
  Serial.println("Ethernet отключён!");
  isNeedSendConnectMessage = true;
  isNeedSendDisconnectMessage = false;
}
*/

/*
//=================================================================================================
//                            1.3.Вывод на консоль контрольных сообщений Ethernet
//=================================================================================================
void printEthMess(FLProgWiznetInterface &id){
(void) id;
if(!RT_HW_Base.console.ok) {return;}
//-------------------------------------------------------------------------------------------------
//                          1.3.1.Одноразовый вывод заголовка
//-------------------------------------------------------------------------------------------------
if(ethCustom==1){ethCustom=2;
RT_HW_Base.consoleHead(String(F("Тест проверки соединения Ethernet на модуле WizNet->")),'='); 
RT_HW_Base.consoleTest(String(F("Eth.")),           ++ethCntMess,  '~','U');
RT_HW_Base.consoleTest(String(F(" cs")),     (uint8_t)eth.pinCs(), ';','P');
RT_HW_Base.consoleTest(String(F(" SPI bus")),(uint8_t)eth.spiBus(),';','U');
//RT_HW_Base.consoleTest(String(F(" chip")),           eth.getChip(),';','U');
RT_HW_Base.consoleCR();
}
//-------------------------------------------------------------------------------------------------
//                          1.3.1.Контроль изменения и вывод статуса
//-------------------------------------------------------------------------------------------------
if(ethStatus==id.getStatus()) {ethStatus =id.getStatus();
RT_HW_Base.consoleTest(String(F("Eth")),      ++ethCntMess,  '~','U');
RT_HW_Base.consoleTest(String(F(" cs")),(uint8_t)eth.pinCs(),';','P');
RT_HW_Base.consoleTest(String(F(" Статус")),     ethStatus,  ';','U');
RT_HW_Base.consoleCR();
}
//-------------------------------------------------------------------------------------------------
//                          1.3.2.Контроль изменения и вывод ошибки
//-------------------------------------------------------------------------------------------------
if(ethError==id.getError()){ethError=id.getError(); 
if(ethError){
RT_HW_Base.consoleTest(String(F("Eth")),      ++ethCntMess,  '~','U');
RT_HW_Base.consoleTest(String(F(" cs")),(uint8_t)eth.pinCs(),';','P');
RT_HW_Base.consoleTest(String(F(" код ошибки")), ethError,   'E','U');
}}
//-------------------------------------------------------------------------------------------------
//                          1.2.2.Контроль подключения
//-------------------------------------------------------------------------------------------------
if((id.isReady()) &&  (isNeedSendConnectMessage)){    
RT_HW_Base.consoleTest(String(F("Eth")),      ++ethCntMess,  '~','U');
RT_HW_Base.consoleTest(String(F(" cs")),(uint8_t)eth.pinCs(),';','P');
RT_HW_Base.consoleVar(String(F(" ETHERNET ПОДКЛЮЧЕН! ")));   
    Serial.print(" Ip=");      Serial.print(id.localIP());
    Serial.print(" DNS=");     Serial.print(id.dns());
    Serial.print(" Subnet=");  Serial.print(id.subnet());
    Serial.print(" Gateway="); Serial.print(id.gateway());
RT_HW_Base.consoleCR();
isNeedSendConnectMessage    = false;
isNeedSendDisconnectMessage = true;
}
//-------------------------------------------------------------------------------------------------
if((!id.isReady()) && (!isNeedSendConnectMessage) && (isNeedSendDisconnectMessage)){
RT_HW_Base.consoleTest(String(F("Eth")),      ++ethCntMess,  '~','U');
RT_HW_Base.consoleTest(String(F(" cs")),(uint8_t)eth.pinCs(),';','P');
RT_HW_Base.consoleVar (String(F(" ETHERNET ОТКЛЮЧЕН!!! "))); 
RT_HW_Base.consoleCR(2);
    isNeedSendConnectMessage = true;
    isNeedSendDisconnectMessage = false;
}
//-------------------------------------------------------------------------------------------------
}
//=================================================================================================

//=================================================================================================
//                            1.2.ФУНКЦИИ ДЛЯ ETHERNET
//=================================================================================================
//-------------------------------------------------------------------------------------------------
//                           1.2.1. Инициализация параметров Ethernet
//-------------------------------------------------------------------------------------------------
//void  customEthernet(FLProgWiznetInterface &id){
//if(RT_HW_Base.customETH){return;}                         //--Выход, если параметры инициализированы;   
//eth.mac(0x78, 0xAC, 0xC0, 0x2C, 0x3E, 0x28);              //--Установка MAC-адрес контроллера (лучше адрес прошитый производителем);
//RT_HW_Base.customETH=1;
//};
//-------------------------------------------------------------------------------------------------
//                           1.2.1. Инициализация параметров Ethernet
//-------------------------------------------------------------------------------------------------
//void ethPool(FLProgWiznetInterface &id){eth.pool;}

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
void  customEthernet(FLProgWiznetInterface &id){(void)id;};
void  poolEthernet  (FLProgWiznetInterface &id){(void)id;}
//void  directEthernet(RT_HW_ETHERNET_DEV &id){(void)id;};
//void  printEthernet (RT_HW_ETHERNET_DEV &id){(void)id;};
#endif
*/
//=================================================================================================
