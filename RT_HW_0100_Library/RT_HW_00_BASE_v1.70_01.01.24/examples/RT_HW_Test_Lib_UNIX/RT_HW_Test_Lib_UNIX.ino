#include "RT_HW_BASE.h"               //--Подключение базовой библиотеки;
#include <UnixTime.h>
RT_HW_GENERATOR_EVENT_ID gen,genLed; 
UnixTime stamp(3);  // указать GMT (3 для Москвы)
uint32_t unixStamp;
uint32_t t1,t2,t3,t4;
uint8_t  vInit=0;
bool blink;
//-------------------------------
#if defined(ARDUINO_ARCH_RP2040)
  RT_HW_PIN_DIR_ID   idPinControl;  uint8_t pinControl=28;  //--Пин контроль loop()[для логического анализатора];
  RT_HW_PIN_DIR_ID   idPinDebug;    uint8_t pinDebug=29;    //--Пин для отладки(Debug), значение для вывода на пин Debug;
  RT_HW_PIN_DIR_ID   idPinLed;      uint8_t pinLed=25;      //--Пин Led на плате; 
#else
  RT_HW_PIN_DIR_ID   idPinControl;  uint8_t pinControl=8;  //--Пин контроль loop()[для логического анализатора];
  RT_HW_PIN_DIR_ID   idPinDebug;    uint8_t pinDebug=9;    //--Пин для отладки(Debug), значение для вывода на пин Debug;
  RT_HW_PIN_DIR_ID   idPinLed;      uint8_t pinLed=13;     //--Пин Led на плате; 
#endif
//------------------------------
void setup() {};
void loop() {
//------------------------------
if(!vInit){vInit=1;
//-------------------------------------------------------------------------------------------------------------------------------------------
  RT_HW_Base.unixSetTimeDate(22,30,15,25,12,2023);  //--unixID: Установка произвольного времени;
  RT_HW_Base.unixSetSystemTimeDate();               //--unixID: Получение системного времени;
//-------------------------------------------------------------------------------------------------------------------------------------------
  stamp.setDateTime(RT_HW_Base.unixID.year,  RT_HW_Base.unixID.month, RT_HW_Base.unixID.day, RT_HW_Base.unixID.hours, RT_HW_Base.unixID.minutes, RT_HW_Base.unixID.seconds);  //--Установка времени stamp;
  RT_HW_Base.unixGetTimeDate();                     //--unixID: Получение времени, даты, дня недели;
  unixStamp=stamp.getUnix();                      //--stamp:  Получение времени, даты, дня недели;  
}
//------------------------------------------------------------------------------------------------
RT_HW_Base.consoleBegin();                    //--Инициализация консоли;
//-------------------------------------------------------------------------------------------------
blink=!blink;                             RT_HW_Base.pinDigitalWrite(idPinControl,pinControl,blink);            //--Вывод цикла loop() на контрольный пин; 
if(RT_HW_Base.generatorEvent(genLed,500)){RT_HW_Base.pinDigitalWrite(idPinLed,    pinLed,    genLed.meander);}  //--Вывод меандра 500 мс пин Led;
//-------------------------------------------------------------------------------------------------
if(RT_HW_Base.generatorEvent(gen,1000))     //--Периодический запуск функций работы со временем;
{
RT_HW_Base.unixID.timeUNIX++;               //--unitID:  увеличение времени на 1 сек;
            unixStamp++;               //--stamp:  увеличение времени на 1 сек;

//-------------------------------------------------------------------------------------------------
RT_HW_Base.pinDigitalWrite(idPinDebug,  pinDebug,  1);         //--Вывод значения vDebug на пин Debug; 
t1=micros(); unixStamp=stamp.getUnix();         t2=micros();
RT_HW_Base.pinDigitalWrite(idPinDebug,  pinDebug,  0);         //--Вывод значения vDebug на пин Debug;
delayMicroseconds(100);
//-------------------------------------------------------------------------------------------------
RT_HW_Base.pinDigitalWrite(idPinDebug,  pinDebug,  1);         //--Вывод значения vDebug на пин Debug; 
t3=micros(); RT_HW_Base.unixGetTimeDate();           t4=micros();
RT_HW_Base.pinDigitalWrite(idPinDebug,  pinDebug,  0);         //--Вывод значения vDebug на пин Debug; 
delayMicroseconds(100);
 
//----------------------------------------------
RT_HW_Base.consoleTest(String(F("stamp-->time")),             unixStamp,';'); RT_HW_Base.consoleTest(String(F(" mcs")),(t2-t1),'E');
RT_HW_Base.consoleTest(String(F("uinxID->time")),RT_HW_Base.unixID.timeUNIX,';'); RT_HW_Base.consoleTest(String(F(" mcs")),(t4-t3),'E');
RT_HW_Base.consoleCR();
//=================================================================================================
} //--END Generator
}; //--END loop();
