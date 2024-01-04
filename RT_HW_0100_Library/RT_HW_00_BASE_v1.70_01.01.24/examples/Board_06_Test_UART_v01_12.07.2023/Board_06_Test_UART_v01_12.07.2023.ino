//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                  BASIC TEST №3 
//                  (compatible with FLProg - visual programming system)
//    2.1.The console is initialized (after initialization, no time is spent on execution).
//    2.2.After the console is ready, the header with the controller parameters is displayed once,
//        including scanning the i2c bus. If there are no pull-up resistors on the i2c bus to Vcc
//        or i2c devices, possibly hanging due to the CORE feature.
//    3.1.The change in each cycle of the loop is output on the Control pin (for a logic analyzer).
//    3.2.Meander=500ms is output on the Led pin.
//-------------------------------------------------------------------------------------------------
//    To configure the IDE to work with supported boards, instructions to the Readme.hpp.
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
uint32_t codeCustomBrd=0;       //--Custom board ID (Raspberry Pi Pico DNS.01);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//#include "flprogUtilites.h"   //--Connect SDK FLProg;
#include "RT_HW_BASE.h"         //--Connection of the base library;
//=================================OBJECTS AND VARIABLES===========================================
RT_HW_STRUCT_SHED shed;  uint32_t vSpeedMCU=0;    uint16_t vSpeedSmall=0;    uint32_t vSpeedFltr;       //--Created sheduler 0;
RT_HW_PIN_DIR_ID   idPinControl;    uint8_t pinControl; //--Control;
RT_HW_PIN_DIR_ID   idPinLed;        uint8_t pinLed;     //--Led on Board;
RT_HW_GENERATOR_EVENT_ID idGenLed;                      //--Generator for Led;
RT_HW_GENERATOR_EVENT_ID idGenUART,idGenUART0,idGenUART1,idGenUART2,idGenUART3,idGenUART4,idGenUART5,idGenUART6; //--Generator for scan UART;
RT_HW_STRUCT_UART_DEV dv;
uint8_t vr=0;
//=================================================================================================
uint8_t vInit=0;                                        //--Parameter initialization flag;
uint8_t bus=0;                                          //--var fo num bus;
uint8_t idx=0;
//======================================SETUP()====================================================
void setup(){}
//=======================================LOOP()====================================================
void loop(){
//======================================1.Init parameters==========================================
if(vInit==0){vInit=1;
pinControl=RT_HW_Base.device.pin.control; 
pinLed=RT_HW_Base.device.pin.led;}
//======================================2.Heading console output===================================
RT_HW_Base.consoleBegin();        //--Console initialization;
if(RT_HW_Base.console.head==1){   //--Single output to the console of the project header;
  RT_HW_Base.consoleHead(String(F("BASIC TEST №3(scan i2c)")),'=');
  RT_HW_Base.consoleHead(String(F("Main parameters")));     RT_HW_Base.mess.modePin='T';   RT_HW_Base.consoleBoardGeneral();           
  RT_HW_Base.consoleHead(String(F("Interface")));           RT_HW_Base.mess.modePin='T';   RT_HW_Base.consoleInterface(); 
  RT_HW_Base.consoleHead(String(F("System pins")));         RT_HW_Base.mess.modePin='T';   RT_HW_Base.consolePinsSystem();  
  RT_HW_Base.consoleLine('-');
}
//===================================2.Output meander on Led=======================================
RT_HW_Base.sheduler(shed);                          //--Sheduler tasks;
RT_HW_Base.pinDigitalWrite(idPinControl,pinControl,shed.control);   //--loop() output to control pin; 
RT_HW_Base.pinDigitalWrite(idPinLed,    pinLed,    shed.blink500);  //--Meander 500ms to Led; 
//===================================3.Write UART==================================================
if(RT_HW_Base.generatorEvent(idGenUART,250)){
for(idx=1; idx<10; idx++){if(RT_HW_Base.uartCheckNum(idx)){
dv.custom=0;  RT_HW_Base.uartSetParam(dv,idx,115000); RT_HW_Base.uartInitDevice(dv);
if(dv.status==1){vr=0x60+idx; RT_HW_Base.uartWrite(dv,vr);
RT_HW_Base.consoleVar(String(" UART"),'~'); RT_HW_Base.consoleVar(idx,'~'); RT_HW_Base.consoleVar(String("->")); RT_HW_Base.consoleVar(vr,';',0,'H');  
}}}
RT_HW_Base.consoleCR(1);}
}; //++++END loop()================================================================================
   
