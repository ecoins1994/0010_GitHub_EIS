//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
//                                  BASIC TEST №10 
//                  (compatible with FLProg - visual programming system)
//    1.1.Setting parameters, incl. test pins from controller parameters. Can be changed.
//    1.2.In each loop() loop, the "Task Manager" is executed.
//    1.3.Every second the project performance is calculated.
//    2.1.The console is initialized (after initialization, no time is spent on execution).
//    2.2.After the console is ready, the header with the controller parameters is displayed once,
//        including scanning the i2c bus. If there are no pull-up resistors on the i2c bus to Vcc
//        or i2c devices, possibly hanging due to the CORE feature.
//    3.1.The change in each cycle of the loop is output on the Control pin (for a logic analyzer).
//    3.2.Meander=500ms is output on the Led pin.
//    4.1.Test value generators.
//    4.2.Reading from the ADC pin (period 100ms).
//    4.2.Write to the PWM pin values from ADC (period 100ms).
//    4.3.Reading a button with 50ms bounce protection.
//    5.  Sensors via pins: DHT22,DS1820,HC-SR04;
//    6.  Sensors via i2c:  AHTxx(T,H),BMP280(P),SHT3x(T,H),HTU21(T,H); 
//    8.  Extenders via i2c: MCP4725(DAC);
//    9.  Extenders via SPI: 74HC595 "Running 1" ;
//    10. To Lcd1.i2c(0x27)
//          for button=0:  Line 1:Button,ADC,Press(BMP180),Speed/1000.
//                         Line 2:Ok CombiSensor,Temp,Hum(AHTxx).  
//          for button=0:  Line 1:Button,DS1820.ok,DS1280.Temp,HC-SR04.ok,HC-SR04.Len;Press(BMP180),
//                         Line 2:Ok DHT22,DHT22.Temp,DHT22.Hum.  
//-------------------------------------------------------------------------------------------------
//    To configure the IDE to work with supported boards, instructions to the Readme.hpp.
//-------------------------------------------------------------------------------------------------
// ecoins@mail.ru 15.07.23
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "RT_HW_BASE.h"         //--Connection of the base library;
#include "RT_HW_LCD44780.h"     //--Connecting the HD44780 type LCD support library;
#include "RT_HW_SENSORS.h"      //--Connecting the sensor   support library;
#include "RT_HW_EXPANDERS.h"    //--Connecting the sensor   support library;
//============================Connecting Internal Functions========================================
#include "Asystem.hpp"          //--System data and functions;
#include "Csensor.hpp"          //--Sensor Polling Functions;
#include "Expander.hpp"         //--Sensor Polling Functions;
#include "Lcd1.hpp"             //--Display functions Lcd1(i2c);         
//============================================SETUP()==============================================
void setup(){}
//=============================================LOOP()==============================================
void loop(){
//============================1.System functions=================================================== 
initProject();                                  //--Settings;
RT_HW_Base.sheduler(shed);                      //--Sheduler tasks;
//if(RT_HW_Base.console.ok){RT_HW_Base.sheduler(shed);}  //--Sheduler tasks for debug;
if(shed.eventSec){                              //--Call 1 time per second;
vSpeedMCU=shed.cycle;                           //--Get speed MCU;
vSpeedMCUF=filterSpeed.filtered(vSpeedMCU);     //--Performance calculation with filtering; 
vSpeedSmall=round(((float)vSpeedMCUF)/1000);}   //--Performance calculation with filtering/1000;
//============================2.INITIALIZING THE CONSOLE AND DISPLAYING HEADERS====================
RT_HW_Base.consoleBegin();                      //--Console initialization;
if(RT_HW_Base.console.head){consoleHead();}     //--Single output to the console of the project header;
//============================3.OUTPUT TO CONTROL PIN AND PIN LED=========== ======================
RT_HW_Base.pinDigitalWrite(idPinControl,pinControl,shed.control);    //--loop() output to control pin; 
RT_HW_Base.pinDigitalWrite(idPinLed,    pinLed,    shed.blink500);   //--Meander 500ms to Led;  
//============================5.I/O Pins===========================================================
if(shed.fast.num==1) {fncADC();}     //--Read  ADC; 
if(shed.fast.num==1) {fncPWM();}     //--Write PWM; 
if(shed.quick.num==1){fncButton();}  //--Anti-bounce button reading;
//-------------------------------------------------------------------------------------------------
//                                  6.Sensors
//==================================6.1.Sensors via pins===========================================  
if(shed.frdm.num==14){snsDS1820();}  //--DS1820 sensor control; 
if(shed.frdm.num==15){snsDHT22();}   //--DHT22 sensor control;  
if(shed.frdm.num==16){snsSR04();}    //--HC-SR04 sensor control (by interrupts);   
//==================================6.2.Sensors via i2c============================================ 
if(shed.frdm.num==18){snsAHTxx();}   //--AHTxx;
//if(shed.frdm.num==22){snsBMP180();}  //--BMP180;
if(shed.frdm.num==22){snsBME280();}  //--BME280/BMP280;
//=================================================================================================
if(shed.frdm.num==30){genRun();}  
if(shed.frdm.num==35){extDM13C();}  
//=================================================================================================
//                                  8.Display
//=================================================================================================
if(shed.frdm.num==40){Lcd1();}       //--Output Lcd1(16x2,i2c,0x27);
//-------------------------------------------------------------------------------------------------
}; //++++END loop()================================================================================
  
