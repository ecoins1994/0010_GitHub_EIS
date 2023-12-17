//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                    1.Data SYSTEM
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                                   1.1.Pins,cs,adr
//=================================================================================================
uint8_t pinControl=255;       uint8_t pinLed=255;          uint8_t pinButton=255;   uint8_t pinADC=255; uint8_t pinPWM=255; 
uint8_t pinDHT22=255;         uint8_t vDHT22ok;   float    vDHT22Temp,   vDHT22Hum;         
uint8_t pinDS1820=255;        uint8_t vDS1820ok;  float    vDS1820Temp; 
uint8_t pinSR04=255;          uint8_t vSR04ok;    uint16_t vSR04Len; 
uint8_t i2cAdrAHTxx=0x38;     uint8_t vAHTxx_ok;  float    vAHTxx_Temp,  vAHTxx_Hum; 
uint8_t i2cAdrBME280=0x77;    uint8_t vBME280_ok; float    vBME280_Temp, vBME280_Hum, vBME280_Press;
uint8_t i2cAdrBMP180=0x77;    uint8_t vBMP180_ok; float    vBMP180_Temp, vBMP180_Press;
                              uint8_t vBMP_ok;    float    vBMP_Temp,    vBMP_Hum, vBMP_Press;
//-------------------------------------------------------------------------------------------------
uint8_t cs74HC595=255;              
//-------------------------------------------------------------------------------------------------
uint8_t i2cAdrLcd1=0x27;            
//=================================================================================================
//                                   1.2.Project Performance Options
//=================================================================================================
RT_HW_STRUCT_SHED shed;                                                   //--Created sheduler;
uint8_t  vInit=0;                                                         //--Parameter initialization flag;
uint32_t vSpeedMCU=0; uint16_t vSpeedSmall=0; uint32_t vSpeedFltr;        //--Project performance in loop() (speedMCU=SpeedMCU/1000);
//------------------------------------------------------------------------------------------------=
char sign='+';
uint8_t agoDir=255,agoStep=255,agoErr=255;
//-------------------------------------------------------------------------------------------------
RT_HW_FILTER_RING_AVERAGE<uint32_t,10> filterSpeed; uint32_t vSpeedMCUF;  //--Filter options (10th order moving average);
RT_HW_FILTER_RING_AVERAGE<uint32_t,5>  filterADC;   //--Filter parameters ADC(5th order moving average);
RT_HW_CHATTER_DIN  idChatBut;    uint8_t vChatBut;  //--Anti-bounce;
//=================================================================================================
//                                   1.3.Control pin, Led on board, PWM
//=================================================================================================
RT_HW_PIN_DIR_ID   idPinControl;                    //--Pin control;
RT_HW_PIN_DIR_ID   idPinDebug;   uint8_t vDebug;    //--Pin debug;
RT_HW_PIN_DIR_ID   idPinLed;                        //--Pin Led on Board;                    
RT_HW_PIN_PWM_ID   idPinPWM;     uint32_t vPWM;     //--Pin PWM;
RT_HW_PIN_DIR_ID   idPinButton;  uint8_t vButton;   //--Pin Button on board;  
RT_HW_PIN_ADC_ID   idPinADC;     uint16_t vADC,agoADC,vADCF,vADCPrc;  
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     2.Systen FUNCTIONS
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                                    2.1.Parameter initialization
//=================================================================================================
void initProject(){
if(vInit==1){return;} vInit=1;
shed.quick.qnt=5; shed.fast.qnt=4; shed.slow.qnt=4; shed.back.qnt=5; shed.frdm.qnt=50;
//=================================================================================================
//-------------------------------------------------------------------------------------------------
//                                    2.1.2. Pins
//-------------------------------------------------------------------------------------------------
pinControl =RT_HW_Base.device.pin.control;//--Pin number Control;
pinLed     =RT_HW_Base.device.pin.led;    //--Pin number Led;
pinButton  =RT_HW_Base.device.pin.button; //--Pin number Кнопки;
pinPWM     =RT_HW_Base.device.pin.pwm;    //--Pin number PWM;
pinADC     =RT_HW_Base.device.pin.adc;    //--Pin number ADC;  
//-------------------------------------------------------------------------------------------------
pinDS1820  =RT_HW_Base.device.dev.oneWire; //--Pin number 1-Wire;
pinDHT22   =RT_HW_Base.device.dev.dht22;   //--Pin number DHT22;
pinSR04    =RT_HW_Base.device.dev.sr04;    //--Pin number HC-SR04.trig;
//-------------------------------------------------------------------------------------------------
//                                    2.1.3. i2c
//-------------------------------------------------------------------------------------------------
i2cAdrLcd1    =0x27;                        //--Adress Lcd1;
i2cAdrAHTxx   =0x38;                        //--Adress AHTXX;        
i2cAdrBMP180  =0x77;                        //--Adress BMP180; 
//-------------------------------------------------------------------------------------------------
};
//=================================================================================================
//                                  2.Heading console output
//=================================================================================================
void consoleHead(){
RT_HW_Base.consoleCR(3);
RT_HW_Base.consoleHead(String(F("Sensor TEST №1(Basic set v.01 15.07.2023)")),'='); 
RT_HW_Base.consoleHead(String(F("Main parameters")),'-'); RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleBoardGeneral();   
//RT_HW_Base.consoleTest(String(F("FLPROG->Code CORE")),(uint8_t)FLPROG_CORE_CODE,';');
//RT_HW_Base.consoleTest(String(F(" Name CORE")),(String)FLPROG_CORE_NAME);
RT_HW_Base.consoleHead(String(F("Add parameters")));      RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleBoardAdd(); 
RT_HW_Base.consoleHead(String(F("Task parameters")));     RT_HW_Base.consoleShedulerParameters();
//RT_HW_Base.consoleHead(String(F("PGM array")));           RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleFromPGM();
RT_HW_Base.consoleHead(String(F("Available pins")));      RT_HW_Base.mess.modePin='A'; RT_HW_Base.consolePinsAll();        
RT_HW_Base.consoleHead(String(F("Interface")));           RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleInterface(); 
RT_HW_Base.consoleHead(String(F("System & test pins")));  RT_HW_Base.mess.modePin='T'; RT_HW_Base.consolePinsSystem(); RT_HW_Base.consolePinsTest();  
RT_HW_Base.consoleHead(String(F("Scan i2c")));            RT_HW_Base.mess.modePin='T'; RT_HW_Base.i2cScanBus(0);   
RT_HW_Base.consoleLine('+'); 
};
//=====================================================================================================
//                                      3.Read ADC
//=====================================================================================================
void fncADC(){
RT_HW_Base.pinAnalogRead(idPinADC,pinADC);    //--Read ADC;
vADCF=idPinADC.vNorm;     //--Fltered ADC;
};
//=====================================================================================================
//                                      4.Write PWM
//=====================================================================================================
void fncPWM(){
if(idPinPWM.dir==0){idPinPWM.channel=0; idPinPWM.freq=1000; idPinPWM.depth=16;} //--Init PWM, freq=1000Hz, mode output='N'(normal); depth bit=16;
RT_HW_Base.pinPWM(idPinPWM,pinPWM,vADCF);  vPWM=idPinPWM.var;                   //--Write to PWM;
};
//=====================================================================================================
//                                      4.Write Freq(ESP32)
//=====================================================================================================
void fncFRQ(){
if(idPinPWM.dir==0){idPinPWM.channel=0; idPinPWM.freq=1000; idPinPWM.depth=16;} //--Init PWM, freq=1000Hz, mode output='N'(normal); depth bit=16;
RT_HW_Base.pinPWM(idPinPWM,pinPWM,vADCF);  vPWM=idPinPWM.var;                   //--Write to PWM;
};
//=====================================================================================================
//                                     5.Read Bitton
//=====================================================================================================
void fncButton(){
vButton=!RT_HW_Base.pinDigitalRead(idPinButton,pinButton,'U');  //--Reading a button with a tightened pin to Vcc;
vChatBut=RT_HW_Base.chatterDIN(idChatBut,vButton,50);           //--Anti-bounce value from the button;
};
//=====================================================================================================
