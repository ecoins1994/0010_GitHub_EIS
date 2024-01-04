//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
//                                  BASIC TEST №10 
//                  (compatible with FLProg - visual programming system)
//    1.1.Setting parameters, incl. test pins from controller parameters. Can be changed.
//    1.2.In each loop() loop, the "  Task Manager" is executed.
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
//          for button=0:  Line 1:Button,ADC,Press(BMP280),Speed/1000.
//                         Line 2:Ok CombiSensor,Temp,Hum(AHTxx).  
//          for button=0:  Line 1:Button,DS1820.ok,DS1280.Temp,HC-SR04.ok,HC-SR04.Len;Press(BMP280),
//                         Line 2:Ok DHT22,DHT22.Temp,DHT22.Hum.  
//-------------------------------------------------------------------------------------------------
//    To configure the IDE to work with supported boards, instructions to the Readme.hpp.
//-------------------------------------------------------------------------------------------------
// ecoins@mail.ru 07.05.23
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//#include "flprogUtilites.h"   //--Connect SDK FLProg;
#include "RT_HW_BASE.h"         //--Connection of the base library;
#include "RT_HW_LCD44780.h"     //--Connecting the HD44780 type LCD support library;
#include "RT_HW_SENSORS.h"      //--Connecting the sensor   support library;
#include "RT_HW_EXPANDERS.h"    //--Connecting the expander support library;
#include "RT_HW_NEXT.h"         //--Connecting the Nextion  support library;
//============================Connecting Internal Functions========================================
#include "Asystem.hpp"          //--System data and functions;
#include "Bconsole.hpp"         //--Console;
#include "Csensor.hpp"          //--Sensor Polling Functions;
#include "Expander.hpp"         //--Expander Functions
#include "Lcd1.hpp"             //--Display functions Lcd1(i2c);       
#include "Lcd2.hpp"             //--Display functions Lcd2(i2c);
#include "Lcd3_SPI.hpp"         //--Display functions Lcd3(SPI); 
#include "Lcd4_SPN.hpp"         //--Display functions Lcd4(SPN);   
#include "Lcd5_Nxt.hpp"         //--Display functions Lcd4(Nextion);   
//============================================SETUP()==============================================
void setup(){}
//=============================================LOOP()==============================================
void loop(){
//============================1.System functions=================================================== 
initProject();                                  //--Settings;
RT_HW_Base.sheduler(shed);                          //--Sheduler tasks;
if(shed.eventSec){                   //--Call 1 time per second;
vSpeedMCU=shed.cycle;                //--Get speed MCU;
vSpeedMCUF=filterSpeed.filtered(vSpeedMCU);     //--Performance calculation with filtering; 
vSpeedSmall=round(((float)vSpeedMCUF)/1000);}   //--Performance calculation with filtering/1000;
//============================2.INITIALIZING THE CONSOLE AND DISPLAYING HEADERS====================
//RT_HW_Base.consoleBegin();                      //--Console initialization;
if(RT_HW_Base.consoleHead()){consoleHead();}    //--Single output to the console of the project header;
//============================3.OUTPUT TO CONTROL PIN AND PIN LED=========== ======================
RT_HW_Base.pinDigitalWrite(idPinControl,pinControl,shed.control);    //--loop() output to control pin; 
RT_HW_Base.pinDigitalWrite(idPinLed,    pinLed,    shed.blink500);   //--Meander 500ms to Led; 
//-------------------------------------------------------------------------------------------------
if(RT_HW_Base.shed.frdm.num==1){vDebug=1;} else{vDebug=0;}                      //--Setting vDebug;
RT_HW_Base.pinDigitalWrite(idPinDebug,  pinDebug,  vDebug);   //--Meander 500ms to Led; 
//============================4.Test function======================================================
if(shed.frdm.num==1) {genRun(); genDAC(); genMCP23x17();}
if(shed.frdm.num==2) {setFlagSystem(); setFlagDevice();}     //--Settiing vectors of flags;
//============================5.I/O Pins===========================================================
if(shed.fast.num==1) {fncADC();}          //--Read  ADC; 
if(shed.fast.num==1) {fncPWM();}          //--Write PWM; 
if(shed.quick.num==1){fncButton();}       //--Anti-bounce button reading;
//====================================6.SENSORS====================================================
//==================================6.1.Sensors via pins===========================================  
if(shed.frdm.num==5) {snsDS1820();}       //--DS1820 sensor control; 
if(shed.frdm.num==6) {snsDHT22();}        //--DHT22 sensor control;  
if(shed.frdm.num==7) {snsSR04();}         //--HC-SR04 sensor control (by interrupts);   
//==================================6.2.Sensors via i2c============================================ 
if(shed.frdm.num==10){snsAHTxx();}        //--AHTxx;
if(shed.frdm.num==11){snsBMP180();}       //--BMP180;
//if(shed.frdm.num==16){snsBME280();}     //--BME280;
if(shed.frdm.num==12){snsSHT3x();}        //--Sensor SHT3x;
if(shed.frdm.num==13){snsHTU21();}        //--Sensor HTU21;
if(shed.frdm.num==14){snsBH1750();}       //--Sensor BH1750
//==================================6.3.Sensors,Extenders via SPI,SPN==============================
//if(shed.frdm.num==15){snsMAX6675();}      //--Sensor NAX6675;
//if(shed.frdm.num==15){snsMAX6675N();}   //--MAX6675N
//==================================7.1.Extenders via i2c==========================================
if(shed.frdm.num==30){extMCP4725();}      //--Direct MCP4725(DAC);
if(shed.frdm.num==31){extMCP23x17_i2c();} //--Direct MCP23x17 (I/O i2c);
if(shed.frdm.num==32){extPCF8575();}      //--Direct MCP23x17 (I/O i2c);
if(shed.frdm.num==33){extADS1115();}      //--Direct MCP23x17 (I/O i2c);
//==================================7.2.Sensors,Extenders via SPI,SPN=============================
//if(shed.frdm.num==34){direct595();}       //--"Running 1" is output to 74HC595;
//if(shed.frdm.num==35){direct165();}       //--Input for 74HC165;
//if(shed.frdm.num==36){direct595N();}    //--"Running 1" is output to 74HC595N;
//if(shed.frdm.num==37){direct165N();}    //--Input for 74HC165;
//=================================================================================================
//                                  8.Displaies
//=================================================================================================
if(shed.frdm.num==40){Lcd1();}            //--Output Lcd1(16x2,i2c,0x27);
if(shed.frdm.num==41){Lcd2();}            //--Output Lcd2(20x4,i2c,0x3E);
//if(shed.frdm.num==42){Lcd3_SPI();}        //--Output Lcd3(cs1, SPI);
//if(shed.frdm.num==43){Lcd4_SPN();}        //--Output Lcd4(SPN);
//if(shed.frdm.num==45){genNextion(); Nextion();}  //--Output Lcd4 Nextion(UART);
//-------------------------------------------------------------------------------------------------
//#################################################################################################
//                                  II.CORE 1(for RP2040 and other)
//#################################################################################################
#if defined(RT_HW_PERMIT_CORE1)
} 
void loop1() {vCr1Ok=1;
#endif
//=================================================================================================
if(vCr1Ok){RT_HW_Base.sheduler(shed1);}   //--Sheduler tasks;
RT_HW_Base.sheduler(shed1);
if(shed1.eventSec){                       //--Call 1 time per second;
vCr1SpeedMCU=shed1.cycle;                 //--Get speed MCU;
vCr1SpeedMCUF=cr1FilterSpeed.filtered(vCr1SpeedMCU);  //--Performance calculation with filtering; 
vCr1SpeedSmall=round(((float)vCr1SpeedMCUF)/1000);}      //--Performance calculation with filtering/1000;
//=================================================================================================
if(shed1.frdm.num==10){cr1GenCnt();}            //--
}; //++++END loop() or loop1======================================================================
  
