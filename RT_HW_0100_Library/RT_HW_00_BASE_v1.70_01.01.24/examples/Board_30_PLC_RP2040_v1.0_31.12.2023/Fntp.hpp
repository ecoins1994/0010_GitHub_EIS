 // const char  timeServer[] = "time.nist.gov"; //--Имя NTP сервера - сервер точного времени;
  //const int   NTP_PACKET_SIZE = 48;         //--Размер буфера NTP (отметка времени NTP находится в первых 48 байтах сообщения);
//-------------------------------------------------------------------------------------------------
 // const char *host = "djxmmx.net";            //--Домен DJXMMX.net. Серверы веб-сайта размещены в Олмстед-Фолс, США и др.
 // const uint16_t port = 17;                   //--Номер порта;
//##################################################################################################
//                                      III.РАБОТА С NTP сервером
//##################################################################################################
//uint32_t localPort = 8888;                            //--Определение порта для UDP пакетов (используется стандартный номер);
const char timeServer[] = "time.nist.gov";            //--Имя NTP сервера - сервер точного времени;
//-------------------------------------------------------------------------------------------------
//                           3.1.Инициализация параметров NTP-сервера
//-------------------------------------------------------------------------------------------------
void  customNTP(RT_HW_TIME_NTP_DEV &id){
  if(id.custom==1){return;}                                //--Выход, если параметры инициализированы;   
  id.periodNTP=10000;                                      //--Установка периода    опроса NTP сервера =10000ms;
  id.periodWD=5000;                                       //--Установка периода    сторожевого таймера ответа NTP сервера =5000ms;
  id.timeZone=3;                                          //--Установка часового пояса +3;
  id.custom=1;                             //--Установка флагов настройки параметров;
};
//=================================================================================================
//                           3.2.Управления обменом c NTP-сервером
//=================================================================================================
#ifdef RT_HW_TEST_PERMIT_NTP
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void  directNTP(RT_HW_TIME_NTP_DEV &id, uint8_t run){
//-------------------------------------------------------------------------------------------------
if(run>0)  {id.run=1;}
//-------------------------------------------------------------------------------------------------
//                  3.00. Инициализация параметров. Продолжение через 500ms.
//-------------------------------------------------------------------------------------------------
if(id.dir==0) { 
id.workDelay=0; id.ok=0;  
if(id.custom==0){return;} 
id.dir=200; id.sizeDelay=500; id.pointDelay=10; return;} 
//-------------------------------------------------------------------------------------------------
//                  3.10.Ожидание сигнала запуска. Переход через 200ms;
//-------------------------------------------------------------------------------------------------
if(id.dir==10){
if(!id.run)        {return;}    //--                                     
if(ethID.status!=1){return;}    //--Выход при не готовности Ethernet;
id.run=0;
id.dir=200; id.sizeDelay=500; id.pointDelay=20; return;} 
//-------------------------------------------------------------------------------------------------
//                  3.20.Отправка запроса
//-------------------------------------------------------------------------------------------------
if(id.dir==20){
Udp.begin(id.localPort);                      //--Инициализация UDP (это надо делать всегда? ... надо проверить!!!);
memset(id.packetBuffer, 0, id.packetSize);    //--Очистка буфера
id.packetBuffer[0]  = 0b11100011;             // LI, Version, Mode
id.packetBuffer[1]  = 0;                      // Stratum, or type of clock
id.packetBuffer[2]  = 6;                      // Polling Interval
id.packetBuffer[12] = 49;
id.packetBuffer[13] = 0x4E;
id.packetBuffer[14] = 49;
id.packetBuffer[15] = 52;
Udp.beginPacket(timeServer, 123);             //--Инициализация NTP запроса к порту 123;
Udp.write(id.packetBuffer, id.packetSize);    //--Отправка запроса;
Udp.endPacket();                              //--Завершение запроса;
id.cntRequest++;                              //--Увеличение кол-ва отправленных запросов;
id.codeMess=2;                                //--Код выводмиого сообщения;
id.cntWD=0; 
id.dir=200; id.sizeDelay=100; id.pointDelay=30; 
return;} 
//-------------------------------------------------------------------------------------------------
//                  3.30.Проверка ответа каждые 100ms до значения сторожевого таймера;
//-------------------------------------------------------------------------------------------------
if(id.dir==30){
id.getDataQnt=Udp.parsePacket();                          //--Получение кол-ва принятых байт в последнем запросе;
if(id.getDataQnt>0)      {id.dir=40; return;} //--Переход на обработку ответа(dir=50) при наличии данных (сколько принятых данных должно быть???);
//-------------------------------------------------------------------------------------------------
if(++id.cntWD>(id.periodWD/100)){
id.codeMess=3;  id.run=1; 
id.dir=200; id.sizeDelay=100; id.pointDelay=10; return;} 
//--------------------------------------------------------------------------------------------------
id.dir=200; id.sizeDelay=100; id.pointDelay=30; return;}
//-------------------------------------------------------------------------------------------------
//                  3.40.Чтение ответа;
//-------------------------------------------------------------------------------------------------
if(id.dir==40){ 
Udp.read(id.packetBuffer,id.packetSize);                  //--Чтение пакета. В байтах 40-43 находятся сведения о времени;
id.cntResponse++;                                         //--Увеличение счетчика прочитанных пакетов;            
id.time1900=((uint32_t)id.packetBuffer[40]<<24) | ((uint32_t)id.packetBuffer[41]<<16) | ((uint16_t)id.packetBuffer[42]<<8) | id.packetBuffer[43];                  
id.timeUNIX=id.time1900-2208988800UL;                     //--Unix-time время в сек от 01.01.1970, что соответствует 2208988800;
id.timeHour=((id.timeUNIX+(id.timeZone*3600UL)) % 86400L)/3600;   //--Часы (86400 сек в сутках);
id.timeMin =((id.timeUNIX+(id.timeZone*3600UL)) % 3600)  /60;     //--Минуты (3600 сек в минуте);
id.timeSec =( id.timeUNIX+(id.timeZone*3600UL))  % 60;            //--Секунды;  
id.fresh=1;                                                       //--Установка флага принятых обновленных данных;
//                 dev.busy=0;                                    //--Освобождении шины;
id.codeMess=4;                                                    //--Код выводимого сообщения;
id.dir=90; return;}                                               //--Возврат на новый запрос к серверу NTP;
//-------------------------------------------------------------------------------------------------
//                  3.90.Successful exit
//-------------------------------------------------------------------------------------------------
if(id.dir==90){
id.timeUNIX=id.time1900-2208988800UL;                     //--Unix-time время в сек от 01.01.1970, что соответствует 2208988800;
id.fresh=1;                                                //--Установка флага принятых обновленных данных;
id.dir=10; return;}
//-------------------------------------------------------------------------------------------------
//                  3.200.Fixed Delay.
//-------------------------------------------------------------------------------------------------
if(id.dir==200){
if(!RT_HW_Base.timeDelay(id.startDelay,id.workDelay,id.sizeDelay)){return;} id.dir=id.pointDelay;}  
//-------------------------------------------------------------------------------------------------
};
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#else
void directNTP(RT_HW_TIME_NTP_DEV &id, uint8_t run){(void)id; if(run){return;}};
#endif
//=================================================================================================
//                                3.2.Вывод сообщений теста UdpNtpClient(); 
//=================================================================================================
#ifdef RT_HW_TEST_PERMIT_NTP
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void printTestNTP(RT_HW_TIME_NTP_DEV &id){
if(!RT_HW_Base.console.ok)                    {return;} //--Выход, если консоль не готова;
if(id.codeMess==0)                            {return;} //--Ожидание номера сообщения;
  qntPrintMess++;                                       //--Увеличение номера выводимого сообщения;
//-------------------------------------------------------------------------------------------------
  RT_HW_Base.consoleVar(qntPrintMess,'.',4,'U');
  RT_HW_Base.consoleVar(String(F(" time=")));; RT_HW_Base.consoleVar(vMotorSec, ';',6,'U');
  RT_HW_Base.consoleVar(String(F(" UDP->NTP: ")));
//-------------------------------------------------------------------------------------------------
if(id.codeMess==1){ RT_HW_Base.consoleVar (String(F(" Начало теста v.01 19.08.23г."))); 
                    RT_HW_Base.consoleTest(String(F(" Период запросов(сек)")),  (uint16_t)(id.periodNTP/10), ';');
                    RT_HW_Base.consoleTest(String(F(" Watch-dog ответов(сек)")),(uint16_t)(id.periodWD/10),';'); 
                    RT_HW_Base.consoleCR();
                    id.codeMess=0; return;}  
//-------------------------------------------------------------------------------------------------
if(id.codeMess==2){ RT_HW_Base.consoleVar(String(F(" Запрос в NTP сервер."))); 
                    RT_HW_Base.consoleCR(); 
                    id.codeMess=0; return;}  
//-------------------------------------------------------------------------------------------------
if(id.codeMess==3){ RT_HW_Base.consoleVar(String(F(" Завершение по тайм-ауту ответа от NTP сервера."))); 
                    RT_HW_Base.consoleCR(); 
                    id.codeMess=0; return;}   
//-------------------------------------------------------------------------------------------------
if(id.codeMess==4){ RT_HW_Base.consoleVar(String(F(" Greenwich +0:")));       RT_HW_Base.consoleVar(char(' '));                //--Вывод заголовка;
                    id.vr=(id.timeUNIX % 86400L)/3600;                        RT_HW_Base.consoleVar((uint8_t)id.vr,':',0,'T'); //--Вывод часов (86400 сек в сутках);
                    id.vr=(id.timeUNIX % 3600)  /60;                          RT_HW_Base.consoleVar((uint8_t)id.vr,':',0,'T'); //--Вывод минут (3600 сек в минуте);
                    id.vr= id.timeUNIX % 60;                                  RT_HW_Base.consoleVar((uint8_t)id.vr,';',0,'T'); //--Вывод сек;                   
                    RT_HW_Base.consoleVar(String(F(" +")));                   RT_HW_Base.consoleVar(id.timeZone,':');          //--Вывод заголовка;
                                                                              RT_HW_Base.consoleVar(char(' '));             
                    id.vr=id.timeHour;                                        RT_HW_Base.consoleVar((uint8_t)id.vr,':',0,'T'); //--Вывод часов (86400 сек в сутках);
                    id.vr=id.timeMin;                                         RT_HW_Base.consoleVar((uint8_t)id.vr,':',0,'T'); //--Вывод минут (3600 сек в минуте);
                    id.vr=id.timeSec;                                         RT_HW_Base.consoleVar((uint8_t)id.vr,';',0,'T'); //--Вывод сек;   
                    RT_HW_Base.consoleTest(String(F(" Packet")),id.cntResponse,  '/'); RT_HW_Base.consoleVar(id.cntRequest,';');                        
                    //RT_HW_Base.consoleTest(String(F(" 01.01.1900")),id.time1900, ';');   //--Вывод абсолютного времени в сек(с 01.01.1990);
                    RT_HW_Base.consoleTest(String(F(" Unix")),     id.timeUNIX, ';');   //--Вывод UNIX времени (с 01.01.1970)
                    RT_HW_Base.consoleCR();
                    id.codeMess=0; return;}                                
//------------------------------------------------------------------------------------------------
                    RT_HW_Base.consoleTest(String(F(" Неизвестное тестовое сообщение")),id.codeMess,'E');  
                    RT_HW_Base.consoleCR(); 
                    id.codeMess=0; return;                  
};
#else
void printTestNTP(RT_HW_TIME_NTP_DEV &id){(void)id;};
#endif
//=================================================================================================
//                                3.3.Вывод диагностических сообщений теста UdpNtpClient(); 
//=================================================================================================
#ifdef RT_HW_TEST_PERMIT_NTP
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void printDebugNTP(RT_HW_TIME_NTP_DEV &id){
if(!RT_HW_Base.console.ok)                    {return;} //--Выход, если консоль не готова;
  if(id.dirAgo!=id.dir){id.dirAgo=id.dir; RT_HW_Base.consoleTest(String(F("dir")),id.dir,'E','U');}
};
#else
void printDebugNTP(RT_HW_TIME_NTP_DEV &id){(void)id;};
#endif
//=================================================================================================
//##################################################################################################
