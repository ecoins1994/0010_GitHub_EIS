//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
//                                  BASIC TEST №04 ver.2.0 14.10.2023  
//                              ТЕСТИРОВАНИЕ УСТРОЙСТВ С ВЫВОДОМ НА ДИСПЛЕИ
//                        (совместим с визуальной системой программирования FLProg)
//    1.1.Настройка параметров в т.ч. тестовые пины, которые могут быть изменены.
//    1.2.В каждом цикле loop() вызывается "Диспетчер задач".
//    1.3.Каждую секунду обрабатываюся секундные параметры - быстродействие проекта, время наработки).
//    2.1.Инициализируется консоль (в терминах Arduino IDE - монитор порта). 
//    2.2.После готовности консоли (проверка консоли особо критична для контроллеров с USB на кристалле - STM32,Raspberry Pi,ESP32-C3,S2,S3),
//        в монитор порта однократно выводяся отчет о проекте (пины, наличие коммуникаций и др.),
//        сканируется шина i2c (SDA,SCL необходимо подтянуть к Vcc резисторами 10-47к).
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
//    для ESP32 дополнительная инструкция для достижения большего удобства.
//-------------------------------------------------------------------------------------------------
// ecoins@mail.ru 14.10.23
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//#define RT_HW_TEST_PERMIT_PLC_01      //--Разрешение перенастройки системных параметров под старую конфигурацию;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                    Разрешения использования системных устройств [Asystem.hpp]
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
  #define RT_HW_TEST_PERMIT_DS1820      //--(pin)Разрешение использования сенсора DS1820;
  #define RT_HW_TEST_PERMIT_SR04        //--(pin)Разрешение использования сенсора HC-SR04;
//-------------------------------------------------------------------------------------------------
  #define RT_HW_TEST_PERMIT_AHTx        //--(i2c)Разрешение использования сенсора SHT3x;
  #define RT_HW_TEST_PERMIT_SHT3x       //--(i2c)Разрешение использования сенсора SHT3x;
//-------------------------------------------------------------------------------------------------
  #define RT_HW_TEST_PERMIT_MCP4725     //--(i2c)Разрешение использования расширителя MCP4725;
//#define RT_HW_TEST_PERMIT_MCP23017    //--(i2c)Разрешение использования расширителя MCP23017(i2c);
//-------------------------------------------------------------------------------------------------
  #define RT_HW_TEST_PERMIT_LCD1_i2c    //--(i2c)Разрешение подключения дисплея Lcd1.i2c  16x2;
//#define RT_HW_TEST_PERMIT_LCD2_i2c    //--(i2c)Разрешение подключения дисплея Lcd2.i2c  20x4; 
//-------------------------------------------------------------------------------------------------
  #define RT_HW_TEST_PERMIT_74HC595     //--(SPI)Разрешение использования расширителя 74HC595 (SPI);  
//#define RT_HW_TEST_PERMIT_74HC165     //--(SPI)Разрешение использования расширителя 74HC165; 
//#define RT_HW_TEST_PERMIT_DM13C       //--(SPI)Разрешение использования расширителя DM13C(SPI);
//#define RT_HW_TEST_PERMIT_MCP23S17    //--(SPI)Разрешение использования расширителя MCP23S17(SPI);
//=================================================================================================
//                    Подключение библиотек
//=================================================================================================
  #include "RT_HW_BASE.h"               //--Connection of the base library;
  #include "RT_HW_LCD44780.h"           //--Connecting the HD44780 type LCD support library;
  #include "RT_HW_SENSORS.h"            //--Connecting the sensor   support library;
  #include "RT_HW_EXPANDERS.h"          //--Connecting the expander support library;
//=================================================================================================
//                    Подключение внутренних вкладок
//=================================================================================================
  #include "Asystem.hpp"                //--Системные параметры и функции (ADC,PWM,Кнопка,DHT22,DS1820,HC-SR04,AHTxx);
  #include "Bconsole.hpp"               //--Функции вывода на консоль;
  #include "Csensor.hpp"                //--Сенсоры;
  #include "Expander.hpp"               //--Расширители;
  #include "Lcd1.hpp"                   //--Дисплей Lcd1(i2c) 16x2; 
  #include "Lcd2.hpp"                   //--Дисплей Lcd2(i2c) 20x4;
//=================================================================================================
//                                    Секция SETUP()
//=================================================================================================
void setup(){}
//=================================================================================================
//                                    Секция SETUP()
//=================================================================================================
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
vMotorSec=shed.cntSec;                          //  кол-во секунд с начала работы программы;
}
//================================================================================================= 
//                                    1.3.Управление консолью
//=================================================================================================
//RT_HW_Base.consoleBegin();                    //--Инициализация консоли;
if(RT_HW_Base.consoleHead()){consoleHead();}    //--Однократный вывод отчета по MC;
//================================================================================================= 
//                                    1.4.Работа системными пинами
//=================================================================================================
RT_HW_Base.pinDigitalWrite(idPinControl,pinControl,shed.control);   //--Ввывод цикла loop() на контрольный пин; 
RT_HW_Base.pinDigitalWrite(idPinLed,    pinLed,    shed.blink500);  //--Вывод меандра 500 ms на светодиод; 
RT_HW_Base.pinDigitalWrite(idPinDebug,  pinDebug,  vDebug);         //--Вывод значения vDebug на пин Debug; 
  if(shed.quick.num==1){fncButton();}                                 //--Чтение кнопки с защитой от дребезга;
  if(shed.quick.num==2) {fncADC();}                                   //--Чтение ADC; 
  if(shed.quick.num==2) {fncPWM();}                                   //--Запись PWM; 
//================================================================================================= 
//                                    1.7.Системные устройства через пины
//================================================================================================= 
  if(shed.frdm.num==5) {snsDS1820();}             //--DS1820. При опросе задержка 4-6 ms;   
  if(shed.frdm.num==7) {snsSR04();}               //--HC-SR04(по прерываниям); 
//================================================================================================= 
//                                    1.8.1.Системные сенсоры через i2c
//================================================================================================= 
  if(shed.frdm.num==10){snsAHTxx();}              //--AHTxx;
//================================================================================================= 
//                                    1.8.Системные устройства через SPI
//================================================================================================= 
  if(shed.frdm.num==30){exp74HC595();}            //--Вывод на 74HC595;
  if(shed.frdm.num==31){exp74HC165();}            //--Ввод  с  74HC165;
  if(shed.frdm.num==32){expMCP4725();}            //--Вывод на MCP4725 (0x60);
//================================================================================================= 
//                                    1.9.Дополнительные устройства через i2c
//================================================================================================= 
  if(shed.frdm.num==35){snsSHT3x();}              //--Сенсор SHT3x;
  if(shed.frdm.num==36){expMCP23017();}           //--Расширитель MCP23017 (i2c);
//================================================================================================= 
//                                    1.10.Дополнительные устройства через SPI
//=================================================================================================
  if(shed.frdm.num==38){expMCP23S17();}           //--Расширитель MCP23S17 (SPI);
  if(shed.frdm.num==37){expDM13C();}              //--Расширитель DM13C;
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
}; //++++END loop() or loop1=======================================================================
