//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                    1.Системные параметры
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                                   1.1.Параметры для работы с диспетчером задач
//=================================================================================================
uint8_t isInit=0;                                                                 //--Состояние инициализации параметров;
//------------------------------------------------------------------------------------------------
RT_HW_STRUCT_SHED shed;  uint32_t vSpeedMCU=0;      uint16_t vSpeedSmall=0;       //--Диспетчер для ядра CORE 0;
RT_HW_FILTER_RING_AVERAGE<uint32_t,5> FilterSpeed;  uint32_t vSpeedMCUF;          //--Фильтр для быстройдествия CORE 0;
uint32_t vMotorSec=0;                                                             //--Мотосекунды;
//-------------------------------------------------------------------------------------------------
RT_HW_STRUCT_SHED shed1;  uint32_t vspeedMCU=0;     uint16_t vspeedSmall=0;       //--Диспетчер для ядра CORE 1 (RP2040);
RT_HW_FILTER_RING_AVERAGE<uint32_t,5> filterSpeed;  uint32_t vspeedMCUF;          //--Фильтр для быстройдествия CORE 1;
RT_HW_GENERATOR_EVENT_ID coreGen;  RT_HW_COUNTER_ID coreCnt; uint8_t vcoreOk=0; uint8_t  vcoreCnt;    //--Параметры для тестирования CORE 1;
//------------------------------------------------------------------------------------------------
uint16_t  flagSystem=0, flagDevice=0;                                                                  //--Флаги системные и устройств;
uint8_t   agoDir=255, agoStep=255, agoCodeErr=255; char sign; bool  blink;                             //--Рабочие регистры для отладки;
uint32_t  timeUNIX=0,timeUNIX_Ago=0;
uint8_t   timeHour,timeMin,timeSec,timeZone=3;
IPAddress ethIP{0,0,0,0};   //--IP адрес Ethernet;
uint8_t   ethServerCnt=0;   //--Кол-во соединений с WEB-сервером;
uint8_t   ethNtpCntTo=0,ettNtpCntFrom=0;   //--Кол-во соединений с NTP-сервером;
//-------------------------------------------------------------------------------------------------
RT_HW_GENERATOR_EVENT_ID genDAC;  RT_HW_COUNTER_ID cntDAC; uint16_t vDAC;
//=================================================================================================
//                                   1.2.Системные пины
//=================================================================================================
RT_HW_PIN_DIR_ID   idPinControl;  uint8_t pinControl=255;                   //--Пин контроль loop()[для логического анализатора];
RT_HW_PIN_DIR_ID   idPinDebug;    uint8_t pinDebug=255;   uint8_t vDebug;   //--Пин для отладки(Debug), значение для вывода на пин Debug;
RT_HW_PIN_DIR_ID   idPinLed;      uint8_t pinLed=255;                       //--Пин Led на плате;                    
//-------------------------------------------------------------------------------------------------
RT_HW_PIN_DIR_ID   idPinButton;   uint8_t pinButton=255;  uint8_t vButton;  //--Пин Кнопка, значение с кнопки;
RT_HW_CHATTER_DIN  idChatBut;     uint8_t vChatBut;                         //--Параметры для защиты кнопки от дребезга;
//-------------------------------------------------------------------------------------------------
RT_HW_PIN_ADC_ID   idPinADC;      uint8_t pinADC=255;     uint16_t vADC,agoADC,vADCF,vADCPrc; //--Пин ADC,значения с пина ADC и обработки;   
RT_HW_FILTER_RING_AVERAGE<uint32_t,5>  filterADC;         //--Параметры фильтра ADC (скользящее среднее 5-го порядка);
//-------------------------------------------------------------------------------------------------
RT_HW_PIN_PWM_ID   idPinPWM;      uint8_t pinPWM=255;     uint32_t vPWM;   //--Пин PWM, значение для вывода на PWM;
RT_HW_PIN_PWM_ID   idPinFRQ;      uint8_t pinFRQ=255;     uint32_t vFRQ;   //--Пин для вывода частоты FRQ;
//=================================================================================================
//                                   1.3.Параметры тестовых устройств через пины
//=================================================================================================
uint8_t pinDHT22=255;         uint8_t vDHT22ok;   float    vDHT22Temp,   vDHT22Hum;         
uint8_t pinDS1820=255;        uint8_t vDS1820ok;  float    vDS1820Temp; 
uint8_t pinSR04=255;          uint8_t vSR04ok;    uint16_t vSR04Len; 
//=================================================================================================
//                                   1.4.Параметры тестовых устройств через i2c
//=================================================================================================
uint8_t i2cAdrAHTxx=0x38;     uint8_t vAHTxx_ok;  float    vAHTxx_Temp,  vAHTxx_Hum; //--Сенсор AHTxx;
uint8_t i2cAdrMCP4725=0x60, i2cAdrMCP4725x=0x61; 
uint8_t i2cAdrMCP23017=0x21;  
uint8_t i2cAdrPCF8575=0x20;  
uint8_t i2cAdrADS1115=0x48;   uint8_t vADS1115_ok; float vADS1115_A0f,vADS1115_A1f,vADS1115_A2f,vADS1115_A3f;
//-------------------------------------------------------------------------------------------------
uint8_t i2cAdrSHT3x=0x44;     uint8_t vSHT3x_ok;  float    vSHT3x_Temp,  vSHT3x_Hum; 
uint8_t i2cAdrHTU21=0x40;     uint8_t vHTU21_ok;  float    vHTU21_Temp,  vHTU21_Hum;
uint8_t i2cAdrBME280=0x77;    uint8_t vBME280_ok; float    vBME280_Temp, vBME280_Hum, vBME280_Press;
uint8_t i2cAdrBMP180=0x77;    uint8_t vBMP180_ok; float    vBMP180_Temp, vBMP180_Press;
                              uint8_t vBMP_ok;    float    vBMP_Temp,    vBMP_Hum, vBMP_Press;
uint8_t i2cAdrBH1750=0x23;    uint8_t vBH1750ok;  uint16_t vBH1750Lux;
//=================================================================================================
//                                   1.5.Параметры тестовых устройств через SPI
//=================================================================================================
uint8_t cs74HC165=255;      //--[cs0];
uint8_t cs74HC595=255;      //--[cs1];
uint8_t csEthernet=255;     //--[cs2];
uint8_t csCAN=255;          //--[cs3];
uint8_t csTFT=255;          //--[cs4];
uint8_t csDM13C=255;        //--[cs5];
uint8_t csMAX6675=255;  uint8_t vMAX6675ok; float vMAX6675Temp; //--[cs5]       
uint8_t csDEV=255;          //--[cs5];
//================================================================================================
//                                   1.6.Параметры тестовых дисплеев
//=================================================================================================
uint8_t i2cAdrLcd1=0x27;      uint8_t i2cAdrLcd2=0x3E;  uint8_t csLcdSPI=255;
uint8_t i2cAdrLcd6=0x26;
//=================================================================================================
//                                   1.7.Параметры тестовых UART
//=================================================================================================
uint8_t uartModbusMaster=255; uint8_t uartModbusSlave=255;   
//-------------------------------------------------------------------------------------------------
uint8_t uartNextion=255; 
uint8_t nxtPage=0; uint8_t nxtVr1,nxtVr2,nxtVr3,nxtVr4;

uint8_t vPCF8575inA=0, vPCF8575inB=0; uint8_t mcp23x17inA,mcp23x17inB;
//=================================================================================================
//                                   1.8.Параметры тестовые для ModBus
//=================================================================================================
uint16_t rg0=0,rg1=0,rg2=0,rg3=0,rg4=0,rg5=0,rg6=0,rg7=0;
uint16_t wg0=0,wg1=0,wg2=0,wg3=0,wg4=0,wg5=0,wg6=0,wg7=0;
//=================================================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     2.СИСТЕМНЫЕ ФУНКЦИИ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                                    2.1.Инициализация параметров
//=================================================================================================
void initProject(){
if(isInit==1){return;} isInit=1;
//-------------------------------------------------------------------------------------------------
shed.quick.qnt =5; shed.fast.qnt =4; shed.slow.qnt =4; shed.back.qnt=5; shed.frdm.qnt =50;
shed1.quick.qnt=5; shed1.fast.qnt=4; shed1.slow.qnt=4; shed1.back.qnt=5; shed1.frdm.qnt=50;
RT_HW_Base.unixID.zone=3;                     //--Установка часового пояса(default=3);
//-------------------------------------------------------------------------------------------------
//                                    2.1.1. UART
//-------------------------------------------------------------------------------------------------
 uartNextion=RT_HW_Base.device.uart.nextion;
//-------------------------------------------------------------------------------------------------
pinControl  =RT_HW_Base.device.pin.control;  //--Установка пина Control;
pinLed      =RT_HW_Base.device.pin.led;      //--Установка пина Led;
pinButton   =RT_HW_Base.device.pin.button;   //--Установка пина Кнопки;
pinPWM      =RT_HW_Base.device.pin.pwm;      //--Установка пина PWM;
pinADC      =RT_HW_Base.device.pin.adc;      //--Установка пина ADC; 
//-------------------------------------------------------------------------------------------------
pinDS1820  =RT_HW_Base.device.dev.oneWire;  //--Установка пина 1-Wire;
pinDHT22   =RT_HW_Base.device.dev.dht22;    //--Установка пина DHT22;
pinSR04    =RT_HW_Base.device.dev.sr04;     //--Установка пина HC-SR04.trig;
//-------------------------------------------------------------------------------------------------
i2cAdrLcd1    =0x27;                        //--Adress Lcd1;
i2cAdrLcd2    =0x3E;                        //--Adress Lcd2;
i2cAdrLcd6    =0x26;                        //--Adress Lcd6 ;
i2cAdrAHTxx   =0x38;                        //--Adress AHTXX;       
i2cAdrMCP4725 =0x60;                        //--Adress MCP4725;  
i2cAdrMCP4725x=0x61;                        //--Adress MCP4725; 
i2cAdrMCP23017=0x21;                        //--Adress MCP23017; 
i2cAdrPCF8575 =0x20;                        //--Adress PCF8575;   
i2cAdrADS1115 =0x48;                        //--Adress ADS1115; 
//-------------------------------------------------------------------------------------------------
cs74HC595   =RT_HW_Base.device.spi.cs0;     //--cs 74HC595; 
cs74HC165   =RT_HW_Base.device.spi.cs1;     //--cs 74HC165;
csEthernet  =RT_HW_Base.device.spi.cs2;     //--cs Ethernet W5x00;
csCAN       =RT_HW_Base.device.spi.cs3;     //--cs CAN;
csTFT       =RT_HW_Base.device.spi.cs4;     //--cs TFT;
csMAX6675   =RT_HW_Base.device.spi.cs5;     //--cs MAX6675;
};
//=====================================================================================================
//                                    2.2.Чтение кнопки с защитой от дребезга 50 ms
//=====================================================================================================
void fncButton(){
vButton=!RT_HW_Base.pinDigitalRead(idPinButton,pinButton,'U');  //--Чтение кнопки с подтяжкой пина к Vcc;
vChatBut=RT_HW_Base.chatterDIN(idChatBut,vButton,50);           //--Защита от дребезга;
};
//=====================================================================================================
//                                    2.3.Чтение ADC
//=====================================================================================================
void fncADC(){
RT_HW_Base.pinAnalogRead(idPinADC,pinADC);    //--Read ADC;
vADCF=filterADC.filtered(idPinADC.vNorm);     //--Fltered ADC;
vADCPrc=(uint32_t)vADCF*100/4095;             //--Convert ADC 0-4095 to %(0-100);
};
//=====================================================================================================
//                                    2.4.Запись PWM
//=====================================================================================================
void fncPWM(){
if(idPinPWM.dir==0){idPinPWM.channel=0; idPinPWM.freq=1000; idPinPWM.depth=16;} //--Init PWM, freq=1000Hz, mode output='N'(normal); depth bit=16;
RT_HW_Base.pinPWM(idPinPWM,pinPWM,vADCF);  vPWM=idPinPWM.var;                   //--Write to PWM;
};
//=====================================================================================================
//                                    2.5.Запись частоты(ESP32)
//=====================================================================================================
void fncFRQ(){
if(idPinPWM.dir==0){idPinPWM.channel=0; idPinPWM.freq=1000; idPinPWM.depth=16;} //--Init PWM, freq=1000Hz, mode output='N'(normal); depth bit=16;
RT_HW_Base.pinPWM(idPinPWM,pinPWM,vADCF);  vPWM=idPinPWM.var;                   //--Write to PWM;
};
//=================================================================================================
//                                    2.6.Счетчик для тестирования DAC
//=================================================================================================
void fncDAC(){         
if(cntDAC.reset)                          {RT_HW_Base.counterReset (cntDAC,4095,0,20,0);} //--Инициализация счетчика: верхний предел, нижний предел, шаг изменения, начальное значение;
if(RT_HW_Base.generatorEvent(genDAC,100)) {vDAC=RT_HW_Base.counterT(cntDAC);};            //--Генератор "Треугольник",100 ms;
};
//=================================================================================================
//                                    2.7.Формирование вектора состояний устройств
//=================================================================================================
void fncSetStatus(){
//------------------------------------------------------------------------------------------------
bitWrite(flagSystem,0,RT_HW_Base.shed.blink500);
bitWrite(flagSystem,1,vChatBut);
//------------------------------------------------------------------------------------------------
bitWrite(flagDevice,1,vAHTxx_ok);
bitWrite(flagDevice,2,vDS1820ok);
bitWrite(flagDevice,3,vSR04ok);
bitWrite(flagDevice,4,vMAX6675ok);
bitWrite(flagDevice,5,vBH1750ok);
bitWrite(flagDevice,7,vSHT3x_ok);
bitWrite(flagDevice,8,vDHT22ok);
};
//=================================================================================================
//                                  2.8.Счетчик для тестирования CORE1
//=================================================================================================
void coreGenCnt(){         
if(coreCnt.reset){RT_HW_Base.counterReset(coreCnt,99,0,1,0);}  //--init counter: Upper limit, Down limit, Change step, Initial value;
if(RT_HW_Base.generatorEvent(coreGen,100)) {vcoreCnt=RT_HW_Base.counterS(coreCnt);}; //--Генератор "Треугольник",100 ms;
};
//=================================================================================================
