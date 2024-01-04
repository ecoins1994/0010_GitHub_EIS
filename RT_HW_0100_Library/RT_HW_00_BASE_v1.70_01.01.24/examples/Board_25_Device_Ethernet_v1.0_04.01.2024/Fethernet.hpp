//=================================================================================================
//                                ФУНКЦИИ И ОБЪЕКТЫ ETHERNET 
//=================================================================================================
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                    1.ETHERNET
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//-------------------------------------------------------------------------------------------------
#if defined (RT_HW_TEST_PERMIT_ETHERNET) 
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  #include "RT_HW_ETHERNET_EXP.h"                   //++Подключение библиотеки  Ethernet(включает подключение flprogEthernet.h);  
  FLProgWiznetInterface   eth;                      //++Создание объекта                 класса Ethernet;
  RT_HW_ETHERNET_EXP      ethExp;                   //++Создание объекта дополнительного класса Ethernet (временно); 
//-------------------------------------------------------------------------------------------------
  void setParamExpEth(){if(ethExp.custom==0){       //==1.1.Установка параметров Ethernet                       
                     //eth.setPinCs(21);            //--Здесь можно изменить номер пина CS (default=RT_HW_Base.device.spi.csETH); 
                     //eth.setSpiBus(0);            //--Здесь можно изменить номер шины SPI(default=RT_HW_Base.device.spi.busETH);    
                       ethExp.custom=1; }}          //--Установка "Настройка выполнена";
//-------------------------------------------------------------------------------------------------
  void directExpEth()  {ethExp.directExpEth(eth);   //==1.2.Управление Ethernet;
     if(ethExp.freshStatus){ethIP=eth.localIP();}}; //      Сохранение IP адреса.
  void checkDirExpEth(){ethExp.checkDirExpEth();}   //==1.3.Вывод номера текущего этапа(для тестирования программного обеспечения);
  void messExpEth(uint8_t vPeriod=0){               //==1.4.Вывод диагностических сообщений (для тестирования оборудования);
            ethExp.messExpEth(eth,vPeriod);}        //      Вывод на консоль;
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#else
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  void setParamExpEth() {;};                       //==1.1.Установка параметров Ethernet 
  void directExpEth()  {;};                        //==1.2.Управление Ethernet;
  void checkDirExpEth() {;};                       //==1.3.Вывод номера текущего этапа(для тестирования программного обеспечения);
  void messExpEth(){;};                            //==1.4.Вывод диагностических сообщений (для тестирования оборудования);
#endif


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                2.NTP-сервер (через Ethernet)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if defined(RT_HW_TEST_PERMIT_ETHERNET) &&  defined(RT_HW_TEST_PERMIT_ETHERNET_NTP)
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  
  #include "RT_HW_ETHERNET_NTP.h"               //++Подключение библиотеки  NTP (включает подключение flprogEthernet.h,RT_HW_ETHERNET.h);
  FLProgUdpClient         ethUDP(&eth);         //++Создание объекта класса Ethernet UDP для использования сервером точного времени;
  RT_HW_ETHERNET_NTP      ethNTP;               //++Создание объекта данных NTP (со временем возможно уйдет в библиотеку flprogEthernet.h);
  RT_HW_STRUCT_SHED_TASK  shNTP;                //++Создание объекта управления вызовом NTP;
//-------------------------------------------------------------------------------------------------
  void setParamNtpEth(){if(ethNTP.custom==0){       //==2.1.Установка параметров NTP;
    ethUDP.setDnsCacheStorageTime(600000);          //--Установка для клиента время хранения DNS кэша=10 минут (default=60000);
    RT_HW_Base.setTaskID(shNTP,'P',60000);           //--Настройка периодического вызова с период 60000ms(60сек)(default=5000);      
    ethNTP.custom=1;}}
//-------------------------------------------------------------------------------------------------
  void directNtpEth(){                              //==2.2.Управление NTP сервером
    RT_HW_Base.directTask(shNTP);                   //--Установка флага запуска задачи "Запрос времени от NTP";      
    ethNTP.directNtpEth(eth,ethUDP,shNTP.run);      //--Вызов                   задачи "Запрос времени от NTP";   
    if(ethNTP.fresh){ethNTP.fresh=0; RT_HW_Base.unixID.timeUNIX=ethNTP.timeUNIX;}}  //--Обновление времени от NTP сервера;
//-------------------------------------------------------------------------------------------------
  void checkDirNtpEth(){ethNTP.checkDirNtpEth();};  //==2.3.Вывод номера текущего этапа(для тестирования программного обеспечения);
  void messNtpEth()    {ethNTP.messNtpEth();};      //==2.4.Вывод диагностических сообщений (для тестирования оборудования);             
  uint32_t getTimeUnixNTP(){return ethNTP.timeUNIX;}//==2.5.Получение времени timeUNIX;
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#else
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  void setParamNTP() {;};                           //==2.1.Установка параметров NTP;
  void directNTP()   {;};                           //==2.2.Управление NTP сервером;
  void checkDirNTP() {;};                           //==2.3.Вывод номера текущего этапа(для тестирования программного обеспечения);
  void printMessNTP(){;};                           //==2.4.Вывод диагностических сообщений (для тестирования оборудования);
  uint32_t getTimeUnixNTP(){return 0;}              //==2.5.Получение времени timeUNIX;
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                3.Web-сервер (через Ethernet)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#if defined (RT_HW_TEST_PERMIT_ETHERNET) &&  defined(RT_HW_TEST_PERMIT_ETHERNET_SERVER)
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  FLProgEthernetServer    ethServer(&eth,80); //--Создание объекта класса Ethernet Server;
  uint8_t  ethServerStatus = 255;
  uint8_t  ethServerError  = 255;
  uint8_t  ethServerfirst  = 0;
  bool     ethServerCurrentLineIsBlank;
  uint32_t ethServerTimeBegin;
  uint32_t ethServerTimePacket;
  char     ethServerChar;
  uint8_t  ethServerCntConnect=0, ethServerCntDisConnect=0; 
  uint8_t  ethServerFirst=0;
  uint8_t  ethServerIdx;
  IPAddress ethServerIP;
//-------------------------------------------------------------------------------------------------
void blankServerEth(FLProgEthernetServer &id,char sign=' ',uint8_t qnt=5){
  for(ethServerIdx=0; ethServerIdx<qnt; ethServerIdx++){id.print(sign);}} 
//=================================================================================================
// mode: =0 Нет вывода на консоль; =1-Только подключение/отключение; >=2 Все сообщения;
//=================================================================================================
void directServerEth(FLProgEthernetServer &id, uint8_t mode=0){
if(!id.connected())       {return;}
if(!id.available())       {return;}
  ethServerIP=eth.localIP();
  ethServerCurrentLineIsBlank = true;
  ethServerTimeBegin=micros();
  while(id.connected()){
      if(id.available()){
          ethServerChar=id.read(); 
          if(mode>=2){Serial.write(ethServerChar);}
          if (ethServerChar=='\n' && ethServerCurrentLineIsBlank){
              //--Отправка стандартного HTTP заголовка ответа
              id.println("HTTP/1.1 200 OK");
              id.println("Content-Type: text/html");
              id.println("Connection: close");
              id.println("Refresh: 5");
              id.println();
              id.println("<!DOCTYPE HTML>");
              id.println("<html>");
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
           id.print("Core0=");        id.print(vSpeedMCUF);   blankServerEth(id,'_',10);
           id.print("Core1=");        id.print(vspeedMCUF);   blankServerEth(id,'_',10);   
           id.print("MotorSec=");     id.print(vMotorSec);    id.println("<br />");
//-------------------------------------------------------------------------------------------------
           id.print("A0=");           id.print(vADCF);        blankServerEth(id,'_',10);
           id.print("DAC=");          id.print(vDAC);         id.println("<br />");
//-------------------------------------------------------------------------------------------------
           if(vAHTxx_ok){id.print("+");} else{id.print("-");}
           id.print("AHTx Temp=");    id.print(vAHTxx_Temp);  blankServerEth(id,'_',10); 
           id.print("Hum=");          id.print(vAHTxx_Hum);   id.println("<br />");
//-------------------------------------------------------------------------------------------------
           if(vSHT3x_ok){id.print("+");} else{id.print("-");}
           id.print("SHTx Temp=");    id.print(vSHT3x_Temp);  blankServerEth(id,' ',20);  
           id.print("  Hum=");        id.print(vSHT3x_Hum);   id.println("<br />");
//-------------------------------------------------------------------------------------------------          
        id.println("</html>");
        break;
      }
           if(ethServerChar=='\n'){ethServerCurrentLineIsBlank = true;}  // you're starting a new line
      else if(ethServerChar!='\r'){ethServerCurrentLineIsBlank = false;}
    }
  }
  id.stopConnection();
  ethServerCnt=ethServerCntDisConnect;
  ethServerTimePacket=RT_HW_Base.getPastMcs(ethServerTimeBegin);   
   if(mode>=1){RT_HW_Base.consoleBlank('-',9); RT_HW_Base.consoleCurrentTime(); 
               RT_HW_Base.consoleVar(String(F(" Клиент cnt="))); ethServerCntDisConnect++;
               RT_HW_Base.consoleVar(ethServerCntDisConnect,'~',3,'U');
               RT_HW_Base.consoleTest(String(F(" time(mcs)")),ethServerTimePacket,'.','U'); 
               RT_HW_Base.consoleBlank(3);
               RT_HW_Base.consoleVar(String(F("IP: ")));
               RT_HW_Base.consoleVar(ethIP[0],'.',0,'U');
               RT_HW_Base.consoleVar(ethIP[1],'.',0,'U');
               RT_HW_Base.consoleVar(ethIP[2],'.',0,'U');
               RT_HW_Base.consoleVar(ethIP[3],'~',0,'U');
              RT_HW_Base.consoleCR();
              }           
}

//=================================================================================================
//
//=================================================================================================
void messServerEth(FLProgEthernetServer &id){
(void)id;
if(ethServerFirst==0){if(RT_HW_Base.console.ok){ethServerFirst=1; RT_HW_Base.consoleHead(String(F("Ethernet->WEB-сервер")),'=');}}
//------------------------------------------------------------------------------------------------
  if(ethServerStatus!=id.getStatus()){
     ethServerStatus =id.getStatus(); 
     RT_HW_Base.consoleTest(String(F("Server status")),ethServerStatus);}
//------------------------------------------------------------------------------------------------
  if(ethServerError!=id.getError()){
     ethServerError =id.getError();
     if(ethServerError!=0){
     RT_HW_Base.consoleTest(String(F("Server error")),ethServerError);
     RT_HW_Base.consoleCR();
     }}
//------------------------------------------------------------------------------------------------
}; //--END messServerEth();
//================================================================================================
void directServerEth(uint8_t mode){directServerEth(ethServer,mode);}
void messServerEth()  {messServerEth(ethServer);}
//-------------------------------------------------------------------------------------------------
#else
void directServerEth(){;};
void messServerEth()  {;};
#endif
//=================================================================================================
