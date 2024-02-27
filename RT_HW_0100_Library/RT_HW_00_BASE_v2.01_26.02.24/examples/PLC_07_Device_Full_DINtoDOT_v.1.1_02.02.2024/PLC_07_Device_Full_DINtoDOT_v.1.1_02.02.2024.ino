//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
//                                 Тест PLC_07 ver.1.1 30.01.2024  
//                              ТЕСТИРОВАНИЕ УСТРОЙСТВ С ВЫВОДОМ НА ДИСПЛЕИ Lcd
//                            (совместим с визуальной системой программирования FLProg)
//    1.1.Инициализация параметров в т.ч. тестовые пины, которые могут быть изменены.
//    1.2.В каждом цикле loop() вызывается "Диспетчер задач";
//    1.3.Инициализируется консоль (в терминах Arduino IDE - монитор порта). 
//        После готовности консоли  в монитор порта однократно выводится отчет о проекте (пины, наличие коммуникаций и др.).
//        сканируется шина i2c (SDA,SCL необходимо подтянуть к Vcc резисторами 10-47к).
//    1.4.Каждую секунду обрабатываются секундные параметры - быстродействие проекта, время наработки).
//    2.1.Сенсоры через i2c: AHTxx(T,H),SHT3x(T,H),BH1750,BMPx80(Press);
//    2.2.Расширители через i2c: MCP4725(DAC),ADS1115(ADC);
//    3.1.Дискретный вывод: 4 пина+ 74HC595;
//    3.2.Дискретный ввод:  4 пина+ 74HC165;  
//    4.1.Вывод на Lcd1.i2c 16x2(0x27):
//                     строка 1:Blink(*),74HC165(HEX.2), быстродействие CORE0/1000, флаг CORE1(+), быстродействие CORE1/1000;
//                     строка 2:AHTxx.ok,AHTxx.Temp,AHTxx.Hum;   
//    4.2.Вывод на Lcd2.i2c 20x4 (0x3E):
//    4.3.Вывод на Lcd3.i2c 20x4 (0x26):
//    4.4.Панель Nextion;  
//=================================================================================================
//    Подключение к выполнению различных устройств выполняется через снятие символов комментариев(//) 
//    с соответствующего макроса.
//-------------------------------------------------------------------------------------------------
// ecoins@mail.ru 27.01.2024
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                    0.Секция DECLARE
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                          1.Разрешения использования пинов и устройств
//================================================================================================= 
  #define RT_HW_TEST_PERMIT_AHTx            //--i2c.Разрешение использования сенсора     AHTx; 
  #define RT_HW_TEST_PERMIT_SHT3x           //--i2c.Разрешение использования сенсора     SHT3x;
  #define RT_HW_TEST_PERMIT_BH1750          //--i2c.Разрешение использования сенсора     BH1750;
  #define RT_HW_TEST_PERMIT_BMP180          //--i2c.Разрешение использования сенсора     BMP180;
//#define RT_HW_TEST_PERMIT_BME280          //--i2c.Разрешение использования сенсора     BME280;    
  #define RT_HW_TEST_PERMIT_MCP4725         //--i2c.Разрешение использования расширителя MCP4725;
  #define RT_HW_TEST_PERMIT_ADS1115         //--i2c.Разрешение использования расширителя ADS1115;    
  #define RT_HW_TEST_PERMIT_LCD1            //--i2c.Разрешение использования дисплея Lcd1;
  #define RT_HW_TEST_PERMIT_LCD2            //--i2c.Разрешение использования дисплея Lcd2;
  #define RT_HW_TEST_PERMIT_LCD3            //--i2c.Разрешение использования дисплея Lcd3;
  #define RT_HW_TEST_PERMIT_NEXTION         //--UART.Разрешение использования панели Nextion; 
  #define RT_HW_TEST_PERMIT_PLC_DOT         //--pin.Вывод на 12 дискретных выходов: pinx4 + 74HC595; 
  #define RT_HW_TEST_PERMIT_PLC_DIN         //--pin.Ввод   c 12 дискретных входов:  pinx4 + 74HC165;  
//-------------------------------------------------------------------------------------------------
  #define RT_HW_TEST_PERMIT_ETHERNET        //--Разрешение тестов работы с Ethernet;
  #define RT_HW_TEST_PERMIT_ETHERNET_NTP    //--Разрешение тестов работы c NTP-cерверами(серверы точного времени);
  #define RT_HW_TEST_PERMIT_ETHERNET_SERVER //--Разрешение тестов работы c cервером;
  #define RT_HW_TEST_PERMIT_MB_MASTER_RTU   //--Разрешение использования MasterRTU;
  #define RT_HW_TEST_PERMIT_MB_SLAVE_RTU    //--Разрешение использования SlaveRTU;  
//=================================================================================================
//                                  2.Подключение библиотек
//=================================================================================================
  #include "IPAddress.h"
  #include "flprogModbusRTU.h"          //--Подключение библиотеки ModBus RTU (Включает #include RT_HW_BASE.h");  
  #include "RT_HW_BASE.h"               //--Подключение базовой библиотеки;
  #include "RT_HW_LCD44780.h"           //--Подключение библиотеки дисплеев типа HD44780;
  #include "RT_HW_SENSORS.h"            //--Подключение библиотек базовых сенсоров    (DS1820, HC-SR04,AHTx,   SHT3x,  BH1750,  BME/BMP,etc);
  #include "RT_HW_EXPANDERS.h"          //--Подключение библиотек базовых расширителей(MCP4725,ADS1115,74HC595,74HC165,MCP23x17,PCF8575,etc);
  #include "RT_HW_NEXT.h"               //--Подключение библиотеки панелей типа Nextion; 
//------------------------------------------------------------------------------------------------

//=================================================================================================
//                            4.Подключение внутренних вкладок
//=================================================================================================
  #include "Asystem.hpp"                //--Параметры и объекты;
  #include "Device.hpp"                 //--Пины,cенсоры,расширители; 
  #include "Lcd1.hpp"                   //--Дисплей Lcd1(i2c) 16x4;       
  #include "Lcd2.hpp"                   //--Дисплей Lcd2(i2c) 20x4;
  #include "Lcd3.hpp"                   //--Дисплей Lcd3(i2c) 20x4;
  #include "Nextion.hpp"                //--Панель Nextion;    
  #include "Tethernet.hpp"              //--Ethernet;  
//-------------------------------------------------------------------------------------------------
  void consoleHead();                   //--Предопределение функции;  
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                    I.Секция SETUP()
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void setup(){}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                    II.Секция LOOP()
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void loop(){
//================================================================================================= 
//                                    1.1.Инициализация параметров
//=================================================================================================
if(RT_HW_Base.isInit==0){
  RT_HW_Base.isInit=1;
  uartNextion=RT_HW_Base.device.uart.nextion; //--UART Nextion; 
}
//================================================================================================= 
//                                    1.2.Диспетчер задач
//=================================================================================================
  RT_HW_Base.sheduler();                      //--Диспетчер;
//================================================================================================= 
//                                    1.3.Однократный вывод на консоль параметров проекта;
//=================================================================================================
if(RT_HW_Base.shed.frdm.num==1){
   RT_HW_Base.consoleBegin();                                     //--Инициализация консоли;
   if(RT_HW_Base.console.head){consoleHead();}}                   //--Однократный вывод отчета по MCU;
//================================================================================================= 
//                                    1.4.Обработка секундных событий
//=================================================================================================
if(RT_HW_Base.shed.eventSec){                                     //--Обработка секундных событий:
  vSpeedMCUF0=FilterSpeed0.filtered(RT_HW_Base.shed.cycle);       //  кол-во циклов в сек      с фильтром CORE0; 
  vSpeedMCUF1=FilterSpeed1.filtered(RT_HW_Base.shed.cycle1);      //  кол-во циклов в сек      с фильтром CORE1; 
  vspeedMCUF0=round(((float)vSpeedMCUF0)/1000);                   //  кол-во циклов в сек/1000 с фильтром CORE0;
  vspeedMCUF1=round(((float)vSpeedMCUF1)/1000);                   //  кол-во циклов в сек/1000 с фильтром CORE1;  
  RT_HW_Base.unixID.timeUNIX++;                                   //--Инкремент UNIX времени;
  RT_HW_Base.unixGetTotal();                                      //--Получение времени,даты,дня недели;
  if(RT_HW_Base.unixID.timeUNIX!=0){RT_HW_Base.unixID.delta=RT_HW_Base.unixID.timeUNIX-RT_HW_Base.unixID.timeUNIX_NTP;} //--Разрыв с временем NTP сервера;
}
//=================================================================================================
//                                    2.1.Управление через Ethernet
//================================================================================================= 
if(RT_HW_Base.shed.frdm.num==2){
  setParamExpEth();                             //--Настройка параметров Ethernet;             
  directExpEth();                               //--Управление модулем   Ethternet;
  messExpEth();                                 //--Вывод диагностических сообщений Ethernet(период в циклах loop);
}
//=================================================================================================
//                                    2.2.Управление NTP-сервером через Ethernet
//================================================================================================= 
if(RT_HW_Base.shed.frdm.num==3){
  setParamNtpEth();                             //--Настройка параметров NTP-сервера;
  directNtpEth();                               //--Управление работой с NTP-сервера;
  messNtpEth();                                 //--Вывод диагностических сообщений NTP-сервер;
}
//=================================================================================================
//                                    2.3 Управление сервером через Ethernet
//================================================================================================= 
if(RT_HW_Base.shed.frdm.num==4){
  directServerEth(1);                           //--Консоль: =0 Нет вывода; =1-Подключение/отключение; >=2 Все сообщения;
  messServerEth(); 
}
//================================================================================================= 
//                                    3.2.СЕНСОРЫ через i2c
//=================================================================================================
  if(RT_HW_Base.shed.frdm.num==12) {snsAHTxx();}    //--i2c.AHTxx;
  if(RT_HW_Base.shed.frdm.num==13) {snsSHT3x();}    //--i2c.SHT3x;   
  if(RT_HW_Base.shed.frdm.num==14) {snsBH1750();}   //--i2c.BH1750;
  if(RT_HW_Base.shed.frdm.num==15) {snsBME280();}   //--i2c.BME280(Press);  
  if(RT_HW_Base.shed.frdm.num==16) {snsBMP180();}   //--i2c.BMP180(Press);  
//================================================================================================= 
//                                   4.1.РАСШИРИТЕЛИ через i2cfrdm.n
//=================================================================================================
  if(RT_HW_Base.shed.frdm.num==20) {genMCP4725(); expMCP4725();}   //--i2c.MCP4725;
  if(RT_HW_Base.shed.frdm.num==21) {              expADS1115();}   //--i2c.ADS1115;
//================================================================================================= 
//                                   4.2.РАСШИРИТЕЛИ через SPI
//================================================================================================= 
  if(RT_HW_Base.shed.frdm.num==21) {                  expDinPLC();}   //--Дискретный ввод; 
//if(RT_HW_Base.shed.frdm.num==22) {genDotPLC();      expDotPLC();}   //--Дискретный выход;    
  if(RT_HW_Base.shed.frdm.num==22) {plcDOT_vr=pinDIN; expDotPLC();}   //--Дискретный выход; 
//=================================================================================================
//                                   5.ДИСПЛЕИ
//=================================================================================================
  if(RT_HW_Base.shed.frdm.num==40) {Lcd1();}          //--Вывод на дисплей Lcd1(16x2,i2c,0x27);
  if(RT_HW_Base.shed.frdm.num==41) {Lcd2();}          //--Вывод на дисплей Lcd2(20x4,i2c,0x3E);
  if(RT_HW_Base.shed.frdm.num==42) {Lcd3();}          //--Вывод на дисплей Lcd3(20x4,i2c,0x26); 
  if(RT_HW_Base.shed.frdm.num==43) {Nextion();}       //--Обмен с панелью  Nextion; 
//=================================================================================================
//                                   6.ДОПОЛНИТЕЛЬНЫЕ ФУНКЦИИ
//=================================================================================================
  if(RT_HW_Base.shed.frdm.num==49){fncSetStatus();}   //--Флаги системные и готовности устройств;
  if(RT_HW_Base.shed.slow.num==1) {fncCounter();}     //--Тестовый счетчик;
//-------------------------------------------------------------------------------------------------

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
//                            3.Modbus
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  #include "mbMasterRTU.hpp"    //==Modbus Master RTU1;
  #include "mbSlaveRTU.hpp"     //==Modbus Slave  RTU1;


//#################################################################################################
//                       II. Переключение на ядро CORE 1 для  RP2040
//#################################################################################################
#if defined(RT_HW_PERMIT_CORE1)
} 
void loop1() {RT_HW_Base.shed.isLoop1=1;
#endif
  if(RT_HW_Base.shed.freshSec1) {RT_HW_Base.shed.cntCycle1=1; RT_HW_Base.shed.freshSec1=0;}    //--Увеличение числа циклов loop1() (для вычисления быстродействия CORE1);
  else                          {RT_HW_Base.shed.cntCycle1++;}
}; //++++END loop() or loop1=======================================================================


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                    ВНЕШНИЕ ФУНКЦИИ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                                  1.Функция: Вывод на консоль параметров контроллера
//=================================================================================================
void consoleHead(){
  RT_HW_Base.consoleHead(String(F("Тест Board_06_Device_Full_v1.1")),'=');
  RT_HW_Base.consoleVar(String(F("Проект->")));                     RT_HW_Base.consoleVar(String(F(__FILE__)),'E');
  RT_HW_Base.consoleHead(String(F("Основные параметры")));          RT_HW_Base.mess.modePin='T';  RT_HW_Base.consoleBoardGeneral();           
//RT_HW_Base.consoleHead(String(F("Дополнительные параметры")));    RT_HW_Base.mess.modePin='T';  RT_HW_Base.consoleBoardAdd(); 
//RT_HW_Base.consoleHead(String(F("Параметры диспетчера задач")));  RT_HW_Base.consoleShedulerParameters();
//RT_HW_Base.consoleHead(String(F("Доступные пины")));              RT_HW_Base.mess.modePin='A';  RT_HW_Base.consolePinsAll();    
  RT_HW_Base.consoleHead(String(F("Интерфейсы")));                  RT_HW_Base.mess.modePin='T';  RT_HW_Base.consoleInterface(); 
  RT_HW_Base.consoleHead(String(F("Системные,тестовые,cs пины")));  RT_HW_Base.mess.modePin='T';  
  RT_HW_Base.consolePinsSystem(); RT_HW_Base.consolePinsTest();     RT_HW_Base.consolePinsCS(); 
  RT_HW_Base.consoleHead(String(F("Устройства на UART")));          RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleNumUART();    
//-------------------------------------------------------------------------------------------------
  RT_HW_Base.consoleHead(String(F("Сканирование i2c(bus=0)")));     RT_HW_Base.mess.modeAdr='A';  
                                                                    RT_HW_Base.i2cScanBus(0);     
//-------------------------------------------------------------------------------------------------   
  RT_HW_Base.consoleLine('+');  
};
//=================================================================================================