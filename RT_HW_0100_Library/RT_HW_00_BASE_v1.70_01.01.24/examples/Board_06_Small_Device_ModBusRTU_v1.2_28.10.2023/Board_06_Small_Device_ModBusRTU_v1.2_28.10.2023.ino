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
  #define RT_HW_TEST_PERMIT_DS1820      //--Разрешение использования сенсора DS1820;
  #define RT_HW_TEST_PERMIT_SR04        //--Разрешение использования сенсора HC-SR04;
  #define RT_HW_TEST_PERMIT_AHTx        //--Разрешение использования сенсора SHT3x;
  #define RT_HW_TEST_PERMIT_74HC595     //--Разрешение использования расширителя 74HC595;  
  #define RT_HW_TEST_PERMIT_74HC165     //--Разрешение использования расширителя 74HC165; 
  #define RT_HW_TEST_PERMIT_MCP4725     //--Разрешение использования расширителя MCP4725;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                    Разрешения использования дополнительных сенсоров [Csensor.hpp]
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++   
  #define RT_HW_TEST_PERMIT_SHT3x       //--Разрешение использования сенсора SHT3x;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                    Разрешения использования дополнительных расширителей [Expander.hpp]
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++;
//#define RT_HW_TEST_PERMIT_DM13C       //--Разрешение использования расширителя DM13C(SPI);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                    Разрешения использования дополнительных дисплeeв [Lcd.hpp]
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  #define RT_HW_TEST_PERMIT_LCD1_i2c    //--Разрешение подключения дисплея Lcd1.i2c  16x2;
  #define RT_HW_TEST_PERMIT_LCD2_i2c    //--Разрешение подключения дисплея Lcd2.i2c  20x4;  
//=================================================================================================
//                    Подключение библиотек
//=================================================================================================
  #include "RT_HW_BASE.h"               //--Подключение библиотеки базовой  RT_HW_BASE.h;
  #include "RT_HW_LCD44780.h"           //--Подключение библиотеки дисплеев LCD HD74780;
  #include "RT_HW_SENSORS.h"            //--Подключение библиотеки Sensors   (сенсоры);
  #include "RT_HW_EXPANDERS.h"          //--Подключение библиотеки Expanders (расширители);
  #include "flprogModbusRTU.h"          //--Подключение библиотеки ModBusRTU;
//=================================================================================================
//                    Подключение внутренних вкладок
//=================================================================================================
  #include "Asystem.hpp"                //--Системные параметры и функции (ADC,PWM,Кнопка,DHT22,DS1820,HC-SR04,AHTxx);
  #include "Bconsole.hpp"               //--Функции вывода на консоль;
  #include "Csensor.hpp"                //--Сенсоры;
  #include "Expander.hpp"               //--Расширители;
  #include "ModBusRTU.hpp"              //--ModbusRTU;
//-------------------------------------------------------------------------------------------------
  #include "Lcd1.hpp"                   //--Подключение вкладки Lcd1(i2c) 16x2; 
  #include "Lcd2.hpp"                   //--Подключение вкладки Lcd2(i2c) 20x4;
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
//================================================================================================= 
createMbRTU0();
//================================================================================================= 
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
//                                    1.2.Modbus
//=================================================================================================
//      Доступные функции:
//         void saveLong(long value, byte table, int startAddres);
//         void saveUnsignedLong(unsigned long value, byte table, int startAddres);
//         void saveFloat(float value, byte table, int startAddres);
//         void saveInteger(int value, byte table, int startAddres);
//         void saveByte(byte value, byte table, int startAddres);
//         void saveBool(bool value, byte table, int startAddres);
//         byte readByte(byte table, int startAddres);
//         int readInteger(byte table, int startAddres);
//         float readFloat(byte table, int startAddres);
//         long readLong(byte table, int startAddres);
//         unsigned long readUnsignedLong(byte table, int startAddres);
//         bool readBool(byte table, int startAddres);
//================================================================================================= 
//================================================================================================= 
createMbRTU0();                               //--Одноразовая инициализация;
SlaveRTU0.pool();                             //--Цикл работы Modbus RTU Slave 0;
//-------------------------------------------------------------------------------------------------  
  if(shed.frdm.num==2) {      
    SlaveRTU0.saveInteger     (tst0.blink,   FLPROG_HOLDING_REGISTR, 0); //--
    SlaveRTU0.saveInteger     (vADCF,        FLPROG_HOLDING_REGISTR, 1); //--
    SlaveRTU0.saveInteger     (vSpeedSmall,  FLPROG_HOLDING_REGISTR, 2); //--
    SlaveRTU0.saveInteger     (vspeedSmall,  FLPROG_HOLDING_REGISTR, 3); //--
    SlaveRTU0.saveInteger     (vMotorSec,    FLPROG_HOLDING_REGISTR, 4); //-- 
    SlaveRTU0.saveFloat       (vAHTxx_Temp,  FLPROG_HOLDING_REGISTR, 5); //-- 
    SlaveRTU0.saveFloat       (vAHTxx_Hum,   FLPROG_HOLDING_REGISTR, 7); //-- 
    SlaveRTU0.saveFloat       (vDS1820Temp,  FLPROG_HOLDING_REGISTR, 9); //-- 
    SlaveRTU0.saveInteger     (vSR04Len,     FLPROG_HOLDING_REGISTR, 11); //-- 
    SlaveRTU0.saveInteger     (vSR04Len,     FLPROG_HOLDING_REGISTR, 12); //--  
    SlaveRTU0.saveInteger     (vSR04Len,     FLPROG_HOLDING_REGISTR, 13); //--         
  lastError = SlaveRTU0.getLastError();  
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
  if(shed.quick.num==1) {fncButton();}                              //--Чтение кнопки с защитой от дребезга;
  if(shed.quick.num==2) {fncADC();}                                 //--Чтение ADC; 
  if(shed.quick.num==2) {fncPWM();}                                 //--Запись PWM; 
//================================================================================================= 
//                                    1.5.Тестовые параметры
//================================================================================================= 
  if(shed.frdm.num==1){
    if(RT_HW_Base.generatorEvent(tst0.gen,1000)){     //--Генератор событий (период 1 сек;
      if(tst0.cnt.reset){RT_HW_Base.counterReset(tst0.cnt,15,-15,1,0);}  //--Инициализация счетчика: Top=10, Bottow =0, Step=1, Begin=0;
      tst0.vr=RT_HW_Base.counterS(tst0.cnt);                             //--Счетчик "Пила";
      tst0.blink=!tst0.blink;                                            //--Мерцание;
      }
  }
//================================================================================================= 
//                                    1.7.Системные устройства через пины
//================================================================================================= 
  if(shed.frdm.num==5) {snsDS1820();}             //--DS1820. При опросе задержка 4-6 ms;   
  if(shed.frdm.num==7) {snsSR04();}               //--HC-SR04(по прерываниям); 
//================================================================================================= 
//                                    1.8.Системные устройства через i2c
//================================================================================================= 
  if(shed.frdm.num==10){snsAHTxx();}              //--AHTxx;
//================================================================================================= 
//                                    1.8.Системные устройства через SPI
//================================================================================================= 
  if(shed.frdm.num==34){exp74HC595();}            //--Вывод на 74HC595;
  if(shed.frdm.num==35){exp74HC165();}            //--Вывод на 74HC165;
  if(shed.frdm.num==36){expMCP4725();}            //--Вывод на MCP4725 (0x60);
//================================================================================================= 
//                                    1.9.Дополнительные устройства через i2c
//================================================================================================= 
  if(shed.frdm.num==12){snsSHT3x();}              //--Sensor SHT3x;
//================================================================================================= 
//                                    1.10.Дополнительные устройства через SPI
//=================================================================================================
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
if(shed1.frdm.num==5){if(vcoreOk){coreGenCnt();}}  //--Тестовый счетчик;
//=================================================================================================           
}; //++++END loop() or loop1=======================================================================