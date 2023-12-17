//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
//                                  ModBus TEST №10 
//                  (совместимо с визуальной системой программирования FLProg)
// 1.1.Установка параметров установки, в т.ч. тестовые пиновиз параметров контроллера. Может быть изменено.
// 1.2.В каждом цикле loop() выполняется «Диспетчер задач».
// 1.3.Каждую секунду рассчитывается производительность проекта.
// 2.1.Консоль инициализируется (после инициализации время на выполнение не тратится).
// 2.2.После готовности консоли один раз отображается заголовок с параметрами контроллера,
//     включая сканирование шины i2c. Если на шине i2c к Vcc нет подтягивающих резисторов
//     или устройства i2c, возможно, зависшие из-за функции CORE.
// 3.1.Изменение в каждом такте цикла выводится на вывод Control (для логического анализатора).
// 3.2.Выводится на меандр 500 ms на пин Led.
// 4.1.Чтение АЦП (период 100мс).
// 4.3.Чтение кнопки с защитой от дребезга 50 мс.
//-------------------------------------------------------------------------------------------------
// ecoins@mail.ru 07.05.23
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//#include "flprogUtilites.h"   //--Connect SDK FLProg;
#include "RT_HW_BASE.h"         //--Connection of the base library;
#include "RT_HW_LCD44780.h"     //--Connecting the HD44780 type LCD support library;
#include "RT_HW_SENSORS.h"      //--Connecting the sensor   support library;
#include "RT_HW_EXPANDERS.h"    //--Connecting the expander support library;
//#include "RT_HW_NEXT.h"       //--Connecting the Nextion  support library;
//============================Подключение библиотек ModBUS=========================================
#include "flprogModbusRTU.h"    //--ModBus RTU;
//============================Connecting Internal Functions========================================
#include "Asystem.hpp"          //--Системные данные и функции ;
#include "Bconsole.hpp"         //--Функции вывода на консоль параметров системы;
#include "Lcd1.hpp"             //--Display functions Lcd1(i2c);       
#include "Lcd2.hpp"             //--Display functions Lcd2(i2c);
//#include "Lcd3_SPI.hpp"       //--Display functions Lcd3(SPI);    
//#include "Lcd5_Nxt.hpp"       //--Display functions Lcd4(Nextion);   
//=================================================================================================
#include "ModBusTable.hpp"      //--Создание объектов Modbus;
#include "ModBusFunc.hpp"       //--Функции Modbus;
uint8_t mbCustom=0; 
uint16_t  mbCnt1=0, mbCnt2=0, mbCnt3=0, mbCnt4=0x23;
//============================================SETUP()==============================================
void setup(){}
//=============================================LOOP()==============================================
void loop(){
//================================================================================================= 
//                                    1.Системные функции
//=================================================================================================
initProject();                                  //--Вызов функции настройки системных параметров;
RT_HW_Base.sheduler(shed);                      //--Диспетчер задач (CORE 0);
//================================================================================================= 
//                                    2.ModBus
//    Доступные функции:
//      void    saveLong(int slave, long value, byte table, int startAddres);
//      void    saveUnsignedLong(int slave, unsigned long value, byte table, int startAddres);
//      void    saveFloat(int slave, float value, byte table, int startAddres);
//      void    saveInteger(int slave, int value, byte table, int startAddres);
//      void    saveByte(int slave, byte value, byte table, int startAddres);
//      void    saveBool(int slave, bool value, byte table, int startAddres);
//      byte    readByte(int slave, byte table, int startAddres);
//      int     readInteger(int slave, byte table, int startAddres);
//      float   readFloat(int slave, byte table, int startAddres);
//      long    readLong(int slave, byte table, int startAddres);
//      unsigned long readUnsignedLong(int slave, byte table, int startAddres);
//      bool    readBool(int slave, byte table, int startAddres);
//=================================================================================================
if((mbCustom==0) & (RT_HW_Base.console.all)){
mbCustom=1;
RT_HW_Base.consoleTest(String(F("Настройка параметров numModBus")),mbCustom);
int16_t arr[10]={23,24,25,-26,27,28,-23475,32145};
int16_t x;
for(uint8_t i=0; i<8; i++){Holder1.writeRegister(i,arr[i]);}
RT_HW_Base.consoleTestArr(String(F("1.arr")),arr,'E','I',10);
//for(uint8_t i=0; i<8; i++){arr[i]=Holder1.writeRegister(i,arr[i]);}
x=Holder1.readWorldRegister(3);
RT_HW_Base.consoleTest(String(F("Holder1.adr[3]")),x);


mbUartInit(1,9600,1);               //--Настройка коммуникационного канала: номер ModBus, скорость UART, номер UART); 
//mbSlaveInit(1, 8, 1000, 100);       //--Настройка параметров внешнего SLAVE для Master MCU: номер ModBus, ID(адрес) Slave, период опроса, тайм-аут опроса;
//mbMasterInit(1);                    //--Настройка ModBus как Master; 
}   //==END if(mbCustom==0);
//--------------------------------------------------------------------------------------------------
//Master1.pool();                     //--Цикл работы MASTER;
if(shed.slow.num==1){if(++mbCnt1>50){mbCnt1=5;} if(++mbCnt2>20){mbCnt2=4;} if(++mbCnt1>=100){mbCnt1=0;}}
if(shed.frdm.num==5){
//  Master1.saveInteger(0, mbCnt1, HOLDING_REGISTR, 1);
//  Master1.saveInteger(0, mbCnt2, HOLDING_REGISTR, 2);
//  Master1.saveInteger(0, mbCnt3, HOLDING_REGISTR, 3);
//  Master1.saveInteger(0, mbCnt4, HOLDING_REGISTR, 4);
//  Master1.saveInteger(0, 0x55,   HOLDING_REGISTR, 6);
}

//================================================================================================= 
//                                    3.Обработка секундных событий
//=================================================================================================
if(shed.eventSec){                              //--Обработка секундных параметров:
vSpeedMCU=shed.cycle;                           //--Кол-во циклов в сек;
vSpeedMCUF=FilterSpeed.filtered(vSpeedMCU);     //--Кол-во циклов в сек после фильтра; 
vSpeedSmall=round(((float)vSpeedMCUF)/1000);    //--Кол-во циклов в сек после фильтра/1000;
}
//================================================================================================= 
//                                    2.Управление консолью
//=================================================================================================
RT_HW_Base.consoleBegin();                      //--Console initialization;
if(RT_HW_Base.consoleHead()){consoleHead();}    //--Single output to the console of the project header;
//================================================================================================= 
//                                    3.Работа системными пинами
//=================================================================================================
RT_HW_Base.pinDigitalWrite(idPinControl,pinControl,shed.control);   //--Ввывод цикла loop() на контрольный пин; 
RT_HW_Base.pinDigitalWrite(idPinLed,    pinLed,    shed.blink500);  //--Вывод меандра 500 ms на светодиод; 
RT_HW_Base.pinDigitalWrite(idPinDebug,  pinDebug,  vDebug);         //--Вывод значения vDebug на пин Debug; 
if(shed.quick.num==1){fncButton();}                                 //--Чтение кнопки с защитой от дребезга;
if(shed.quick.num==2) {fncADC();}                                   //--Чтение ADC; 
if(shed.quick.num==2) {fncPWM();}                                   //--Запись PWM; 
//================================================================================================= 
//                                    4.Системные устройства через пины
//================================================================================================= 
if(shed.frdm.num==5) {snsDS1820();}             //--DS1820. При опросе задержка 4-6 ms; 
if(shed.frdm.num==6) {snsDHT22();}              //--DHT22.  При опросе задержка 6 ms;   
if(shed.frdm.num==7) {snsSR04();}               //--HC-SR04(по прерываниям);   
//================================================================================================= 
//                                    5.Системные устройства через i2c
//================================================================================================= 
if(shed.frdm.num==10){snsAHTxx();}              //--AHTxx;
//================================================================================================= 
//                                    6.Системные устройства через SPI
//================================================================================================= 
if(shed.frdm.num==34){exp74HC595();}            //--Вывод на 74HC595;
if(shed.frdm.num==35){expMCP4725();}            //--Вывод на MCP4725;
//=================================================================================================
//                                    7.Вывод на дисплеи
//=================================================================================================
if(shed.frdm.num==40){Lcd1();}                  //--Output Lcd1(16x2,i2c,0x27);
if(shed.frdm.num==41){Lcd2();}                  //--Output Lcd2(20x4,i2c,0x3E);
//if(shed.frdm.num==42){Lcd3_SPI();}            //--Output Lcd3(cs1, SPI);
//if(shed.frdm.num==45){genNextion();Nextion();}//--Output Lcd5 Nextion(UART);
//-------------------------------------------------------------------------------------------------
//#################################################################################################
//                                  II. Переключение на ядро CORE 1 для  RP2040
//#################################################################################################
#if defined(RT_HW_PERMIT_CORE1)
} 
void loop1() {vCr1Ok=1;
#endif
//=================================================================================================
//if(vCr1Ok){RT_HW_Base.sheduler(shed1);}   
RT_HW_Base.sheduler(shed1);                     //--Диспетчер задач для CORE 1;
//-------------------------------------------------------------------------------------------------
if(shed1.eventSec){                             //--Обработка секундных параметров:
vspeedMCU=shed1.cycle;                          //--Кол-во циклов в сек;
vspeedMCUF=filterSpeed.filtered(vspeedMCU);     //--Кол-во циклов в сек после фильтра; 
vspeedSmall=round(((float)vspeedMCUF)/1000);    //--Кол-во циклов в сек после фильтра/1000;
}
//=================================================================================================
if(shed1.frdm.num==10){coreGenCnt();}           //--Тестовый счетчик;
}; //++++END loop() or loop1======================================================================
  
