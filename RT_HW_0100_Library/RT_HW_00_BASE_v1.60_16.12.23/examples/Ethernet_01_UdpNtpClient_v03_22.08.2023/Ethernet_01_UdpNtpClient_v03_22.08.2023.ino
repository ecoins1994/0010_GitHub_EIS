//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
//                                  BASIC TEST №10 
//                  (совместим с визуальной системой программирования FLProg  вер.8.2.3)
//    1.1.Настройка параметров в т.ч. тестовые пины, которые могут быть изменены.
//    1.2.В каждом цикле loop() вызывается "Диспетчер задач".
//    1.3.Каждую секунду обрабатываюся секундные параметры - быстродействие проекта, время наработки).
//    2.1.Инициализируется консоль (в терминах Arduino IDE - монитор порта). 
//    2.2.После готовности консоли (проверка консоли особо критична для контроллеров с USB на кристалле - STM32,Raspberry Pi,ESP32-C3,S2,S3),
//        в монитор порта однократно выводяся отчет о проекте (пины, наличие коммуникаций и др.),
//        сканируется шина i2c (SDA,SCL необходимо подтянуть к Vcc резисторами 10-47к).
//        or i2c devices, possibly hanging due to the CORE feature.
//    3.1.В каждом цикле loop() меняется значение на пине Control (для логического анализатора).
//    3.2.На пин Led выводится меандр 500ms.
//    4.1.Периодически читается пин ADC(period 100ms). Отфильтрованное значение ADC выводится на пин PWM.
//    4.2.Читается значение пина "Кнопка" с защитой от дребезга 50ms.
//    5.  Сенсоры чере пины: DHT22,DS1820,HC-SR04;
//    6.  Sensors via i2c:  AHTxx(T,H),BMP280(P),SHT3x(T,H),HTU21(T,H); 
//    8.  Extenders via i2c: MCP4725(DAC);
//    9.  Extenders via SPI: 74HC595 "Running 1" ;
//    10. Вывод на Lcd1.i2c(0x27)
//          Кнопка=0:  строка 1:Button,ADC,Press(BMP280),Speed/1000.
//                     строка 2:Ok CombiSensor,Temp,Hum(AHTxx).  
//          Кнопка=1:  строка 1:Button,DS1820.ok,DS1280.Temp,HC-SR04.ok,HC-SR04.Len;Press(BMP280),
//                     строка 2:Ok DHT22,DHT22.Temp,DHT22.Hum.  
//    Подключение к выполнению различных устройств выполняется через снятие символов комментариев(//) 
//    с соответствующего макроса.
//-------------------------------------------------------------------------------------------------
//    Перечень поддерживаемых плат размещен во вкладке Readme.hpp.
//    Там же размещены инструкции по настройке Arduino IDE, 
//    для ESP32 дополнительная инструкция для лостижения большего удобства  и поод
//    To configure the IDE to work with supported boards, instructions to the Readme.hpp.
//-------------------------------------------------------------------------------------------------
// ecoins@mail.ru 07.05.23
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//#define RT_HW_TEST_PERMIT_SHT3x       //--Разрешение использования сенсора SHT3x;
//#define RT_HW_TEST_PERMIT_BMP180      //--Разрешение использования сенсора BMP180;
//#define RT_HW_TEST_PERMIT_BH1750      //--Разрешение использования сенсора BH1750;
//#define RT_HW_TEST_PERMIT_MAX6675     //--Разрешение использования сенсора MAX6675;
//------------------------------------------------------------------------------------------------
  #define RT_HW_TEST_PERMIT_PCF8575     //--Разрешение использования расширителя PCF8575 (i2c); 
  #define RT_HW_TEST_PERMIT_DM13C       //--Разрешение использования расширителя DM13C(SPI);
  #define RT_HW_TEST_PERMIT_ADS1115     //--Разрешение использования расширителя ADS1115(i2c);
//------------------------------------------------------------------------------------------------
  #define RT_HW_TEST_PERMIT_LCD2_i2c    //--Разрешение подключения дисплея Lcd2.i2c  20x4;  
//------------------------------------------------------------------------------------------------
  #define RT_HW_TEST_PERMIT_ETHERNET    //--Разрешение Ethernet;
  #define RT_HW_TEST_PERMIT_NTP         //--Разрешение запросов в NTP-cервер;
//================================================================================================
  #include "RT_HW_BASE.h"               //--Connection of the base library;
  #include "RT_HW_LCD44780.h"           //--Connecting the HD44780 type LCD support library;
  #include "RT_HW_SENSORS.h"            //--Connecting the sensor   support library;
  #include "RT_HW_EXPANDERS.h"          //--Connecting the expander support library;
//#include "RT_HW_NEXT.h"               //--Connecting the Nextion  support library;
  #include "flprogEthernet.h"           //--Подключение библиотеки Ehernet; 
//-------------------------------------------------------------------------------------------------
  FlprogW5100Interface W5100_Interface;         //--Создание объекта для привязки шине SPI(0) и пину cs=10(можно переназначить);
  FlprogEthernetUDP Udp(&W5100_Interface);      //--Создание UDP клиента;
//-------------------------------------------------------------------------------------------------
  const char  timeServer[] = "time.nist.gov";   //--Имя NTP сервера - сервер точного времени;
  //const int   NTP_PACKET_SIZE = 48;           //--Размер буфера NTP (отметка времени NTP находится в первых 48 байтах сообщения);
//-------------------------------------------------------------------------------------------------
  const char *host = "djxmmx.net";                      //--Домен DJXMMX.net. Серверы веб-сайта размещены в Олмстед-Фолс, США и др.
  const uint16_t port = 17;                             //--Номер порта;
//============================Connecting Internal Functions========================================
  #include "Asystem.hpp"                //--Системные параметры и функции (ADC,PWM,Кнопка,DHT22,DS1820,HC-SR04,AHTxx);
  #include "Bconsole.hpp"               //--Функции вывода на консоль;
  #include "Csensor.hpp"                //--Сенсоры;
  #include "Expander.hpp"               //--Расширители;
  #include "Fethernet.hpp"              //--Ethernet;
//-------------------------------------------------------------------------------------------------
  #include "Lcd1.hpp"                   //--Подключение вкладки Lcd1(i2c) 16x4;       
  #include "Lcd2.hpp"                   //--Подключение вкладки Lcd2(i2c) 20x4;  
//-------------------------------------------------------------------------------------------------

//============================================SETUP()==============================================
void setup(){}
//=============================================LOOP()==============================================
void loop(){
//================================================================================================= 
//                                    1.1.Инициализация параметров и диспетчер
//================================================================================================= 
initProject();                                  //--Инициализация параметров;
RT_HW_Base.sheduler(shed);                      //--Диспетчер задач(CORE0);
//================================================================================================= 
//                                    1.2.Обработка секундных событий
//=================================================================================================
if(shed.eventSec){                              //--Обработка секундных событий:
vSpeedMCU=shed.cycle;                           //  кол-во циклов в сек;
vSpeedMCUF=filterSpeed.filtered(vSpeedMCU);     //  кол-во циклов в сек с фильтром; 
vSpeedSmall=round(((float)vSpeedMCUF)/1000);    //  кол-во циклов в сек с фильтром/1000;
vMotorSec=shed.cntSec;                          //  кол-во секунд с начала запуска программы;
if(timeUNIX!=ntpID.timeUNIX){timeUNIX=ntpID.timeUNIX;}  //--Обработка времени 
else                        {timeUNIX++;}               //        в формате UNIX;
timeHour=getTimeHour(timeUNIX,timeZone);        //--Получение значения часов;
timeMin =getTimeMin (timeUNIX,timeZone);        //--Получение значения мин;
timeSec =getTimeSec (timeUNIX,timeZone);        //--Получение значения сек;
}
//================================================================================================= 
//                                    1.3.Управление консолью
//=================================================================================================
RT_HW_Base.consoleBegin();                      //--Инициализация консоли;
if(RT_HW_Base.consoleHead()){consoleHead();}    //--Однократный вывод отчета по MC;
//================================================================================================= 
//                                    1.4.Работа системными пинами
//=================================================================================================
RT_HW_Base.pinDigitalWrite(idPinControl,pinControl,shed.control);   //--Вывод цикла loop() на контрольный пин; 
RT_HW_Base.pinDigitalWrite(idPinLed,    pinLed,    shed.blink500);  //--Вывод меандра 500 ms на светодиод; 
RT_HW_Base.pinDigitalWrite(idPinDebug,  pinDebug,  vDebug);         //--Вывод значения vDebug на пин Debug; 
//------------------------------------------------------------------------------------------------  
  if(shed.quick.num==1) {fncButton();}                              //--Чтение кнопки с защитой от дребезга;
  if(shed.quick.num==2) {fncADC();}                                 //--Чтение ADC; 
  if(shed.quick.num==2) {fncPWM();}                                 //--Запись PWM; 
//================================================================================================= 
//                                    1.5.ModBus
//=================================================================================================

//================================================================================================= 
//                                    1.6.Ethernet UdpNtp
//================================================================================================= 
if(shed.frdm.num==1){
//-------------------------------------------------------------------------------------------------
//                                    1.6.1.Управление Ethernet
//-------------------------------------------------------------------------------------------------
  if(ethID.custom==0) {customEthernet(ethID);     //==НАСТРОЙКА параметров Ethernet(default).  
                                          }       //--Здесь можно уточнить параметры;                                    
  directEthernet(ethID);                          //==Управление Ethernet (настройка, контроль и восстановление связи);
  printEthernet(ethID);                           //==Вывод на консоль сообщений от Ethernet;
//-------------------------------------------------------------------------------------------------
//                                    1.6.2.Управление UDP запросами к NTP серверу (получение точного времени);
//-------------------------------------------------------------------------------------------------
  if(ntpID.custom==0){customNTP(ntpID);           //==НАСТРОЙКА параметров управления запросов к NTP серверу.
    ntpID.periodNTP=10000; ntpID.periodWD=5000;}  //--Здесь можно уточнить параметры;  
  if(shNTP.custom==0){                            //==Настройка задачи управления запросами в NTP сервер;
    shNTP.custom=ntpID.custom;                    //--Установка готовности при настройки ntpID;     
  RT_HW_Base.setTaskID(shNTP,'P',ntpID.periodNTP);} //-Настройка на периодический вызов;
  RT_HW_Base.directTask(shNTP);                   //==Вызов задачи управления запросами в NTP сервер;
  directNTP(ntpID, shNTP.run);                    //==Управление запросами в NTP сервер;
  printTestNTP(ntpID);                            //==Вывод на консоль сообщений от NTP сервера;
//printDebugNTP(ntpID);                           //==Отладочные сообщения теста NTP;
//-------------------------------------------------------------------------------------------------
}   //----END if(shed.frdm.num==1);
//================================================================================================= 
//                                    1.6.Системные устройства через пины
//================================================================================================= 
  if(shed.frdm.num==5) {snsDS1820();}             //--DS1820. При опросе задержка 4-6 ms; 
  if(shed.frdm.num==6) {snsDHT22();}              //--DHT22.  При опросе задержка 6 ms;   
  if(shed.frdm.num==7) {snsSR04();}               //--HC-SR04(по прерываниям); 
//================================================================================================= 
//                                    1.7.Системные устройства через i2c
//================================================================================================= 
  if(shed.frdm.num==10){snsAHTxx();}              //--AHTxx;
  if(shed.frdm.num==11){snsBMP180();}             //--BMP180;
  if(shed.frdm.num==12){snsSHT3x();}              //--Sensor SHT3x;
  if(shed.frdm.num==14){snsBH1750();}             //--Sensor BH1750
//================================================================================================= 
//                                    1.8.Системные устройства через SPI
//================================================================================================= 
  if(shed.frdm.num==34){exp74HC595();}            //--Вывод на 74HC595;
  if(shed.frdm.num==35){expMCP4725();}            //--Вывод на MCP4725 (0x60);
//==================================7.1.Extenders via i2c==========================================
  if(shed.frdm.num==32){expPCF8575();}            //--Direct PCF8575  (I/O i2c);
  if(shed.frdm.num==33){expADS1115();}            //--Direct ADS1115  (I/O i2c);
//==================================7.2.Sensors,Extenders via SPI,SPN=============================
  if(shed.frdm.num==37){expDM13C();}              //--DM13C;
//=================================================================================================
//                                  8.ДИСПЛЕИ
//=================================================================================================
  if(shed.frdm.num==40){Lcd1();}            //--Output Lcd1(16x2,i2c,0x27);
  if(shed.frdm.num==41){Lcd2();}            //--Output Lcd2(20x4,i2c,0x3E);
//-------------------------------------------------------------------------------------------------
//#################################################################################################
//                       II. Переключение на ядро CORE 1 для  RP2040
//#################################################################################################
#if defined(RT_HW_PERMIT_CORE1)
} 
void loop1() {vcoreOk=1;
#endif
//=================================================================================================
//if(vcoreOk){RT_HW_Base.sheduler(shed1);}   
RT_HW_Base.sheduler(shed1);                         //--Диспетчер задач для CORE 1;
//-------------------------------------------------------------------------------------------------
if(shed1.eventSec){                                 //--Обработка секундных параметров:
vspeedMCU=shed1.cycle;                              //--Кол-во циклов в сек;
vspeedMCUF=filterSpeed.filtered(vspeedMCU);         //--Кол-во циклов в сек после фильтра; 
vspeedSmall=round(((float)vspeedMCUF)/1000);        //--Кол-во циклов в сек после фильтра/1000;
}
//=================================================================================================
if(shed1.frdm.num==10){if(vcoreOk){coreGenCnt();}}  //--Тестовый счетчик;
}; //++++END loop() or loop1======================================================================
