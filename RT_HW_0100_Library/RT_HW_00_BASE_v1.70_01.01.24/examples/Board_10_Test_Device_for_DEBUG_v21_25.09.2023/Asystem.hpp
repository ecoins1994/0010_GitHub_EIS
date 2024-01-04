//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                    1.Data SYSTEM
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                                   1.1.Pins,cs,adr
//=================================================================================================
uint8_t pinControl=255;       uint8_t pinLed=255;          uint8_t pinButton=255;   uint8_t pinADC=255; uint8_t pinPWM=255; 
uint8_t pinDebug=255;         uint8_t pinFRQ=255;
uint8_t pinDHT22=255;         uint8_t vDHT22ok;   float    vDHT22Temp,   vDHT22Hum;         
uint8_t pinDS1820=255;        uint8_t vDS1820ok;  float    vDS1820Temp; 
uint8_t pinSR04=255;          uint8_t vSR04ok;    uint16_t vSR04Len; 
uint8_t i2cAdrAHTxx=0x38;     uint8_t vAHTxx_ok;  float    vAHTxx_Temp,  vAHTxx_Hum; 
uint8_t i2cAdrSHT3x=0x44;     uint8_t vSHT3x_ok;  float    vSHT3x_Temp,  vSHT3x_Hum; 
uint8_t i2cAdrHTU21=0x40;     uint8_t vHTU21_ok;  float    vHTU21_Temp,  vHTU21_Hum;
uint8_t i2cAdrBME280=0x77;    uint8_t vBME280_ok; float    vBME280_Temp, vBME280_Hum, vBME280_Press;
uint8_t i2cAdrBMP180=0x77;    uint8_t vBMP180_ok; float    vBMP180_Temp, vBMP180_Press;
                              uint8_t vBMP_ok;    float    vBMP_Temp,    vBMP_Hum, vBMP_Press;
uint8_t i2cAdrBH1750=0x23;    uint8_t vBH1750ok;  uint16_t vBH1750Lux;
uint8_t csMAX6675=255;        uint8_t vMAX6675ok; float    vMAX6675Temp; 
uint8_t csMAX6675N=255;       uint8_t sckMAX6675N=255; uint8_t misoMAX6675N=255;  uint8_t mosiMAX6675N=255; uint8_t vMAX6675Nok;  float vMAX6675NTemp;
//-------------------------------------------------------------------------------------------------
uint8_t i2cAdrMCP4725=0x60; 
uint8_t i2cAdrMCP23x17=0x21;  
uint8_t i2cAdrPCF8575=0x20;  
uint8_t i2cAdrADS1115=0x48;   uint8_t vADS1115_ok; float vADS1115_A0f,vADS1115_A1f,vADS1115_A2f,vADS1115_A3f;
uint8_t cs74HC595=255;              
uint8_t cs74HC165=255;
uint8_t cs74HC595N=255;       uint8_t sck74HC595N=255; uint8_t miso74HC595N=255;  uint8_t mosi74HC595N=255;
uint8_t cs74HC165N=255;       uint8_t sck74HC165N=255; uint8_t miso74HC165N=255;  uint8_t mosi74HC165N=255;
//-------------------------------------------------------------------------------------------------
uint8_t i2cAdrLcd1=0x27;    
uint8_t i2cAdrLcd2=0x3E; 
uint8_t csLcdSPI=255;
uint8_t csLcdSPN=255;       uint8_t sckLcdSPN=255;    uint8_t misoLcdSPN=255;    uint8_t mosiLcdSPN=255;         
//------------------------------------------------------------------------------------------------- 
uint8_t uartModbusMaster=255; 
uint8_t uartModbusSlave=255;  
//-------------------------------------------------------------------------------------------------
uint8_t uartNextion=255; 
uint8_t nxtPage=0;
uint8_t nxtVr1,nxtVr2,nxtVr3,nxtVr4; 
//=================================================================================================
//                                   1.2.Project Performance Options
//=================================================================================================
RT_HW_STRUCT_SHED shed;  uint32_t vSpeedMCU=0;    uint16_t vSpeedSmall=0;    uint32_t vSpeedFltr;       //--Created sheduler 0;
RT_HW_STRUCT_SHED shed1; uint32_t vCr1SpeedMCU=0; uint16_t vCr1SpeedSmall=0; uint32_t vCr1SpeedFltr;    //--Created sheduler 1;
RT_HW_GENERATOR_EVENT_ID cr1Gen;  RT_HW_COUNTER_ID cr1Cnt; uint8_t vCr1Ok=0; uint8_t  vCr1Cnt;          //--For generator counter CORE1;
//-------------------------------------------------------------------------------------------------
uint8_t  vInit=0;                                                         //--Parameter initialization flag;
uint16_t flagSystem=0; uint16_t flagDevice=0;                             //--System & device flags;
uint8_t  agoDir=255, agoStep=255, agoCodeErr=255; char sign; bool  blink; //--Working registeres;
//-------------------------------------------------------------------------------------------------
RT_HW_FILTER_RING_AVERAGE<uint32_t,10> filterSpeed; uint32_t vSpeedMCUF;  //--Filter options (10th order moving average);
RT_HW_FILTER_RING_AVERAGE<uint32_t,10> cr1FilterSpeed; uint32_t vCr1SpeedMCUF;  //--Filter options (10th order moving average);
RT_HW_FILTER_RING_AVERAGE<uint32_t,5>  filterADC;   //--Filter parameters ADC(5th order moving average);
RT_HW_CHATTER_DIN  idChatBut;    uint8_t vChatBut;  //--Anti-bounce;
//=================================================================================================
//                                   1.3.Control pin, Led on board, PWM
//=================================================================================================
RT_HW_PIN_DIR_ID   idPinControl;                    //--Pin control;
RT_HW_PIN_DIR_ID   idPinDebug;   uint8_t vDebug;    //--Pin debug;
RT_HW_PIN_DIR_ID   idPinLed;                        //--Pin Led on Board;                    
RT_HW_PIN_PWM_ID   idPinPWM;     uint32_t vPWM;     //--Pin PWM;
RT_HW_PIN_PWM_ID   idPinFRQ;     uint32_t vFRQ;     //--Pin FRQ;
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
shed.quick.qnt =5; shed.fast.qnt =4; shed.slow.qnt =4; shed.back.qnt=5; shed.frdm.qnt =50;
shed1.quick.qnt=5; shed1.fast.qnt=4; shed1.slow.qnt=4; shed1.back.qnt=5; shed1.frdm.qnt=50;
//=================================================================================================
//--------------------------------------------------------------------------------------------------
//                                    2.1.1. UART
//-------------------------------------------------------------------------------------------------
 uartNextion=RT_HW_Base.readArrPGM(RT_HW_PGM_TST_URT_ID,0); //--UART number for Nextion;
//-------------------------------------------------------------------------------------------------
//                                    2.1.2. Pins
//-------------------------------------------------------------------------------------------------
pinControl =RT_HW_Base.device.pin.control;//--Pin number Control;
pinLed     =RT_HW_Base.device.pin.led;    //--Pin number Led;
pinButton  =RT_HW_Base.device.pin.button; //--Pin number Кнопки;
pinPWM     =RT_HW_Base.device.pin.pwm;    //--Pin number PWM;
pinADC     =RT_HW_Base.device.pin.adc;    //--Pin number ADC;
//pinFRQ     =14;                         //--Pin number FREQ(ESP32);   
//-------------------------------------------------------------------------------------------------
pinDS1820  =RT_HW_Base.device.dev.oneWire; //--Pin number 1-Wire;
pinDHT22   =RT_HW_Base.device.dev.dht22;   //--Pin number DHT22;
pinSR04    =RT_HW_Base.device.dev.sr04;    //--Pin number HC-SR04.trig;
//-------------------------------------------------------------------------------------------------
//                                    2.1.3. i2c
//-------------------------------------------------------------------------------------------------
i2cAdrLcd1    =0x27;                        //--Adress Lcd1;
i2cAdrLcd2    =0x3E;                        //--Adress Lcd2;
i2cAdrAHTxx   =0x38;                        //--Adress AHTXX;       
i2cAdrSHT3x   =0x44;                        //--Adress SHT3x; 
i2cAdrHTU21   =0x40;                        //--Adress HTU21; 
i2cAdrBME280  =0x77;                        //--Adress BME280; 
i2cAdrBMP180  =0x77;                        //--Adress BMP180; 
i2cAdrBH1750  =0x23;                        //--Adress BH1750; 
//------------------------------------------------------------------------------------------------
i2cAdrMCP4725 =0x60;                        //--Adress MCP4725;  
i2cAdrMCP23x17=0x21;                        //--Adress MCP23017; 
i2cAdrPCF8575 =0x20;                        //--Adress PCF8575;   
i2cAdrADS1115 =0x48;                        //--Adress ADS1115; 
//-------------------------------------------------------------------------------------------------
//                                    2.1.4. SPI
//-------------------------------------------------------------------------------------------------
cs74HC595   =RT_HW_Base.device.spi.cs0;     //--cs 74HC595;
csLcdSPI    =RT_HW_Base.device.spi.cs1;     //--cs MAX6675;
cs74HC165   =RT_HW_Base.device.spi.cs2;     //--cs 74HC165;
csMAX6675   =RT_HW_Base.device.spi.cs3;     //--cs MAX6675; 
//-------------------------------------------------------------------------------------------------
//                                   2.1.5.SPN
//-------------------------------------------------------------------------------------------------     
sckLcdSPN   =RT_HW_Base.readArrPGM(RT_HW_PGM_PIN_SPN_ID,0);   //--sck  Lcd.SPN;    
misoLcdSPN  =RT_HW_Base.readArrPGM(RT_HW_PGM_PIN_SPN_ID,1);   //--miso Lcd.SPN;  
mosiLcdSPN  =RT_HW_Base.readArrPGM(RT_HW_PGM_PIN_SPN_ID,2);   //--mosi Lcd.SPN;  
csLcdSPN    =RT_HW_Base.readArrPGM(RT_HW_PGM_PIN_SPN_ID,3);   //--cs   Lcd.SPN;  
//-------------------------------------------------------------------------------------------------
sckMAX6675N =RT_HW_Base.readArrPGM(RT_HW_PGM_PIN_SPN_ID,0);   //--sck  MAX6675.SPN;    
misoMAX6675N=RT_HW_Base.readArrPGM(RT_HW_PGM_PIN_SPN_ID,1);   //--miso MAXX6675.SPN;  
mosiMAX6675N=RT_HW_Base.readArrPGM(RT_HW_PGM_PIN_SPN_ID,2);   //--mosi MAX6675.SPN;  
csMAX6675N  =RT_HW_Base.readArrPGM(RT_HW_PGM_PIN_SPN_ID,3);   //--cs   MAX6675.SPN;  
//------------------------------------------------------------------------------------------------- 
sck74HC595N =RT_HW_Base.readArrPGM(RT_HW_PGM_PIN_SPN_ID,0);   //--sck  74HC595.SPN;  
miso74HC595N=RT_HW_Base.readArrPGM(RT_HW_PGM_PIN_SPN_ID,1);   //--miso 74HC595.SPN;
mosi74HC595N=RT_HW_Base.readArrPGM(RT_HW_PGM_PIN_SPN_ID,2);   //--mosi 74HC595.SPN;
cs74HC595N  =RT_HW_Base.readArrPGM(RT_HW_PGM_PIN_SPN_ID,3);   //--cs   74HC595.SPN;  
//-------------------------------------------------------------------------------------------------
sck74HC165N =RT_HW_Base.readArrPGM(RT_HW_PGM_PIN_SPN_ID,0);   //--sck  74HC165.SPN;  
miso74HC165N=RT_HW_Base.readArrPGM(RT_HW_PGM_PIN_SPN_ID,1);   //--miso 74HC165.SPN;
mosi74HC165N=RT_HW_Base.readArrPGM(RT_HW_PGM_PIN_SPN_ID,2);   //--mosi 74HC165.SPN;
cs74HC165N  =RT_HW_Base.readArrPGM(RT_HW_PGM_PIN_SPN_ID,3);   //--cs   74HC165.SPN;  
//-------------------------------------------------------------------------------------------------
};
//=================================================================================================
//                              Counter for DEBUG ORE1
//=================================================================================================
void cr1GenCnt(){         
if(cr1Cnt.reset){RT_HW_Base.counterReset(cr1Cnt,99,0,1,0);}  //--init counter: Upper limit, Down limit, Change step, Initial value;
if(RT_HW_Base.generatorEvent(cr1Gen,100)) {vCr1Cnt=RT_HW_Base.counterS(cr1Cnt);}; //--Triangle generator ,100 ms;
};
//=================================================================================================
//                              FORMING REGISTERS WITH FLAGS
//=================================================================================================
void setFlagSystem(){
bitWrite(flagSystem,0,RT_HW_Base.shed.blink500);
bitWrite(flagSystem,1,vChatBut);
};
//------------------------------------------------------------------------------------------------
void setFlagDevice(){
bitWrite(flagDevice,1,vAHTxx_ok);
bitWrite(flagDevice,2,vDS1820ok);
bitWrite(flagDevice,3,vSR04ok);
bitWrite(flagDevice,4,vMAX6675ok);
bitWrite(flagDevice,5,vBH1750ok);
bitWrite(flagDevice,7,vSHT3x_ok);
bitWrite(flagDevice,8,vDHT22ok);
};
//=====================================================================================================
//                                      3.Read ADC
//=====================================================================================================
void fncADC(){
RT_HW_Base.pinAnalogRead(idPinADC,pinADC);    //--Read ADC;
vADCF=filterADC.filtered(idPinADC.vNorm);     //--Fltered ADC;
vADCPrc=(uint32_t)vADCF*100/4095;             //--Convert ADC 0-4095 to %(0-100);
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
