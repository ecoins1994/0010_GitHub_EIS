//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                    1.Data SYSTEM
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                                   1.1.Параметры для работы с диспетчером задач
//=================================================================================================
uint8_t vInit=0;                                                                                      //--Состояние инициализации параметров;
//------------------------------------------------------------------------------------------------
RT_HW_STRUCT_SHED shed;  uint32_t vSpeedMCU=0;      uint16_t vSpeedSmall=0;     uint32_t vSpeedFltr;  //--Диспетчер для ядоа CORE 0;
RT_HW_FILTER_RING_AVERAGE<uint32_t,5> FilterSpeed;  uint32_t vSpeedMCUF;                              //--Фильтр для быстройдествия CORE 0;
uint32_t vMotorSec=0;                                                                                 //--Мотосекунды;
//-------------------------------------------------------------------------------------------------
RT_HW_STRUCT_SHED shed1; uint32_t vspeedMCU=0;      uint16_t vspeedSmall=0;     uint32_t vspeedFltr;  //--Диспетчер для ядра CORE 1 (RP2040);
RT_HW_FILTER_RING_AVERAGE<uint32_t,5> filterSpeed;  uint32_t vspeedMCUF;                              //--Фильтр для быстройдествия CORE 1;
RT_HW_GENERATOR_EVENT_ID coreGen;  RT_HW_COUNTER_ID coreCnt; uint8_t vcoreOk=0; uint8_t  vcoreCnt;    //--Параметры для тестирования CORE 1;
//------------------------------------------------------------------------------------------------
uint16_t flagSystem=0, flagDevice=0;                                                                  //--Флаги системные и устройств;
uint8_t  agoDir=255, agoStep=255, agoCodeErr=255; char sign; bool  blink;                             //--Рабочие регистры для отладки;
uint32_t timeUNIX=0,timeUNIX_Ago=0;
uint8_t  timeHour,timeMin,timeSec,timeZone=3;
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
uint8_t csTFT=255;          //--[cs4]  || [cs3];
uint8_t csDEV=255;          //--[cs5];

uint8_t csDM13C=255;        //--[cs0]  || [cs1]  || [cs5];
uint8_t csMAX6675=255;  uint8_t vMAX6675ok; float vMAX6675Temp; //--[cs3] || [cs5]       
uint8_t csMAX6675N=255; uint8_t sckMAX6675N=255,misoMAX6675N=255,mosiMAX6675N=255,vMAX6675Nok;  float vMAX6675NTemp;
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
//                            1.9.СТРУКТУРА ДЛЯ РАБОТЫ С ETHERNET
// status: FLPROG_ETHERNET_STATUS_NOTREADY   =0 - устройство не готово (default);
//         FLPROG_ETHERNET_STATUS_READY      =1 - устройство готово;
//         FLPROG_ETHERNET_STATUS_WHITE_DHCP =2 - устройство готово и имеет "белый" DHCP; 
// link:   FLPROG_ETHERNET_LINK_UNKNOWN      =0 - нет связи с устройством(устр-во не иницировано, также возвращает для W5100 !!!?);
//         FLPROG_ETHERNET_LINK_ON           =1 - устройство    отвечает на запросы;
//         FLPROG_ETHERNET_LINK_OFF          =2 - устройство не отвечает на запросы;
// chip:   FLPROG_ETHERNET_NO_HARDWARE       =0 - устройство не обнаружено;
//         FLPROG_ETHERNET_W5100             =1 - W5100;
//         FLPROG_ETHERNET_W5200             =2 - W5200;                                                  
//         FLPROG_ETHERNET_W5500             =3 - W5500;
//=================================================================================================
struct RT_HW_ETHERNET_DEV{
uint8_t  custom=0, customFresh=0;                 //--Параметр настройки: custom=1 - параметры настроены;
uint8_t  printFirst=0;                            //--Флаг первого вывода;
uint8_t  status=0, statusAgo=255, statusFresh=0;  //--Состояние устройства;
uint8_t  link=0,   linkAgo=255,   linkFresh=0;    //--Состояние связи;   
uint8_t  chip=0;                                  //--Тип устрйоства;
uint8_t  busy=0;                                  //--Занятость устройства (1/0);  
uint16_t busyWD=100;                              //--Период сторожевого таймера занятости шины; 
uint8_t  cs=255;  uint8_t bus=0;                  //--SPI.cs W5x00 - cs устройства; SPI.bus - номер шины SPI;
IPAddress ip;                                     //--IP адрес;
//------------------------------------------------------------------------------------------------                       
};
RT_HW_ETHERNET_DEV  ethID;                        //--Объект с данными для работы с Ethernet;

//=================================================================================================
//                            1.10.СТРУКТУРА ДЛЯ РАБОТЫ С NTP сервером
//=================================================================================================
struct  RT_HW_TIME_NTP_DEV{
//-------------------------------------------------------------------------------------------------
char     mi='W';          //--0.Тип интерфейса;
uint8_t  custom=0;        //--1.Флаг настройки параметров; 
//--------------------------------------------------------------------------------------------------
uint8_t  dir=0,dirAgo=255;//--5.Этапы управляющей задачи;;
uint8_t  run=1;           //--7.1.Флаг для старта запуска запроса;
uint8_t  ok;              //--7.3.Device ok;
uint8_t  fresh;           //--7.4.Fresh data;
//-------------------------------------------------------------------------------------------------
uint8_t  timeZone=3;                    //--Номер часового пояса
uint32_t time1900,timeUNIX,vr;
uint8_t  timeHour,timeMin,timeSec; 
uint16_t cntRequest=0, cntResponse=0;   //--Счетчики запросов и ответов;
uint8_t  cntWD;                         //--Счетчик для сторожевого таймера;
//-------------------------------------------------------------------------------------------------
uint8_t  workDelay=0;     //--10.Working register; 
uint8_t  pointDelay;      //--11.Return point from a function;
uint16_t sizeDelay;       //--12.Size delay;  
uint32_t startDelay;     //--13.Working register;
//------------------------------------------------------------------------------------------------  
uint16_t  periodNTP=10000;
uint16_t  periodWD=5000;
uint8_t   codeMess=0;
uint16_t  getDataQnt=0;                                 //--Кол-во принятых байт;
//------------------------------------------------------------------------------------------------
uint32_t  localPort = 8888;                             //--Определение порта для UDP пакетов (используется стандартный номер);
uint8_t   packetSize=48;                                //--Неизменный размер буфера; 
uint8_t   packetBuffer[48];                             //--Создание буфера для хранения входящих и исходящих пакетов;
char      timeServer[20] = "time.nist.gov";             //--Имя NTP сервера - сервер точного времени;
};
RT_HW_TIME_NTP_DEV  ntpID;                              //--Объект с данными для работы с NTP-сервером; 
RT_HW_STRUCT_SHED_TASK shNTP;                           //--Объект для управления задачей;


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     2.СИСТЕМНЫЕ ФУНКЦИИ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                                    2.1.Инициализация параметров
//=================================================================================================
void initProject(){
if(vInit==1){return;} vInit=1;
shed.quick.qnt =5; shed.fast.qnt =4; shed.slow.qnt =4; shed.back.qnt=5; shed.frdm.qnt =50;
shed1.quick.qnt=5; shed1.fast.qnt=4; shed1.slow.qnt=4; shed1.back.qnt=5; shed1.frdm.qnt=50;
//--------------------------------------------------------------------------------------------------
//                                    2.1.1. UART
//-------------------------------------------------------------------------------------------------
 uartNextion=RT_HW_Base.device.uart.nextion;
//--------------------------------------------------------------------------------------------------
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
csLcdSPI    =RT_HW_Base.device.spi.cs1;     //--cs LcdSPI(with 74HC595);
csDM13C     =RT_HW_Base.device.spi.cs1;     //--cs DM13C;
csEthernet  =RT_HW_Base.device.spi.cs2;     //--cs Ethernet W5x00;
csCAN       =RT_HW_Base.device.spi.cs3;     //--cs CAN;
csMAX6675   =RT_HW_Base.device.spi.cs3;     //--cs MAX6675;
};
//=================================================================================================
//                                    2.2.Счетчик для тестирования CORE1
//=================================================================================================
void coreGenCnt(){         
if(coreCnt.reset){RT_HW_Base.counterReset(coreCnt,99,0,1,0);}  //--init counter: Upper limit, Down limit, Change step, Initial value;
if(RT_HW_Base.generatorEvent(coreGen,100)) {vcoreCnt=RT_HW_Base.counterS(coreCnt);}; //--Генератор "Треугольник",100 ms;
};
//=====================================================================================================
//                                    2.3.Чтение кнопки с защитой от дребезга 50 ms
//=====================================================================================================
void fncButton(){
vButton=!RT_HW_Base.pinDigitalRead(idPinButton,pinButton,'U');  //--Чтение кнопки с подтяжкой пина к Vcc;
vChatBut=RT_HW_Base.chatterDIN(idChatBut,vButton,50);           //--Защита от дребезга;
};
//=====================================================================================================
//                                    2.4.Чтение ADC
//=====================================================================================================
void fncADC(){
RT_HW_Base.pinAnalogRead(idPinADC,pinADC);    //--Read ADC;
vADCF=filterADC.filtered(idPinADC.vNorm);     //--Fltered ADC;
vADCPrc=(uint32_t)vADCF*100/4095;             //--Convert ADC 0-4095 to %(0-100);
};
//=====================================================================================================
//                                    2.5.Запись PWM
//=====================================================================================================
void fncPWM(){
if(idPinPWM.dir==0){idPinPWM.channel=0; idPinPWM.freq=1000; idPinPWM.depth=16;} //--Init PWM, freq=1000Hz, mode output='N'(normal); depth bit=16;
RT_HW_Base.pinPWM(idPinPWM,pinPWM,vADCF);  vPWM=idPinPWM.var;                   //--Write to PWM;
};
//=====================================================================================================
//                                    2.6.Запись частоты(ESP32)
//=====================================================================================================
void fncFRQ(){
if(idPinPWM.dir==0){idPinPWM.channel=0; idPinPWM.freq=1000; idPinPWM.depth=16;} //--Init PWM, freq=1000Hz, mode output='N'(normal); depth bit=16;
RT_HW_Base.pinPWM(idPinPWM,pinPWM,vADCF);  vPWM=idPinPWM.var;                   //--Write to PWM;
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     3.СИСТЕМНЫЕ УСТРОЙСТВА
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                                      3.1.DS1820 через 1-Wire
//=================================================================================================
RT_HW_STRUCT_DS1820_ID  dvDS1820; RT_HW_STRUCT_SHED_TASK shDS1820;  RT_HW_ONEWIRE dvNW;
//-------------------------------------------------------------------------------------------------
#ifdef RT_HW_TEST_PERMIT_DS1820
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void snsDS1820(){
if(shDS1820.custom==0){RT_HW_Base.setTaskID(shDS1820,'P',2200); shDS1820.periodLimit=50;} //--Периодический вызов 2.2сек;
if(dvDS1820.custom==0){RT_HW_ds1820.setParam(dvDS1820,pinDS1820);}                        //--Настройка параметров;
dvDS1820.run=RT_HW_Base.directTask(shDS1820);                                             //--Управление задачей;
RT_HW_ds1820.direct(dvNW,dvDS1820);                                                       //--Управление устройством; 
if(dvDS1820.fresh){dvDS1820.fresh=0; vDS1820Temp=dvDS1820.vTemp; vDS1820ok=dvDS1820.ok;}  //--Обновление данных;
};
#else
void snsDS1820(){;};
#endif
//=================================================================================================
//                                      3.2.DHT22
//=================================================================================================
RT_HW_DHT22   dvDHT22;            RT_HW_STRUCT_SHED_TASK shDHT22; 
//-------------------------------------------------------------------------------------------------
#ifdef RT_HW_TEST_PERMIT_DHT22
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void snsDHT22(){
if(shDHT22.custom==0){RT_HW_Base.setTaskID(shDHT22,'P',2200); shDHT22.periodLimit=50;}    //--Периодический вызов 2.2сек;
if(dvDHT22.custom==0){dvDHT22.setParam(RT_HW_Base.device.dev.dht22);}                     //--Настройка параметров;
dvDHT22.run=RT_HW_Base.directTask(shDHT22);                                               //--Управление задачей;
dvDHT22.direct();                                                                         //--Управление устройством; 
if(dvDHT22.fresh){dvDHT22.fresh=0; vDHT22Temp=dvDHT22.vTemp; vDHT22Hum=dvDHT22.vHum; vDHT22ok=dvDHT22.ok;} //--Обновление данных;
};
#else
void snsDHT22(){;};
#endif
//=================================================================================================
//                                      3.3.HC-SR04 через пин Trig (соединить с Echo чере R=470ом) по прерываниям;
//=================================================================================================
RT_HW_STRUCT_SR04_ID  dvSR04;     RT_HW_STRUCT_SHED_TASK shSR04;
RT_HW_FILTER_MEDIAN_3 <uint16_t> ftrSR04;     uint16_t vSR04LenF;   //--Parameters for the HC-SR04 filter (3rd order median);
//------------------------------------------------------------------------------------------------
RT_HW_IRAM_ATTR void RT_HW_IRQ_SR04_handler_dvSR04(){
  if(dvSR04.state==2) {if( RT_HW_PIN_DIR_READ(dvSR04.ddPin)){dvSR04.timeBegin=micros(); dvSR04.state=3;}}
  if(dvSR04.state==3) {if(!RT_HW_PIN_DIR_READ(dvSR04.ddPin)){dvSR04.timeEnd  =micros(); dvSR04.state=4;}}}
//------------------------------------------------------------------------------------------------
#ifdef RT_HW_TEST_PERMIT_SR04
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void snsSR04(){
if(shSR04.custom==0){RT_HW_Base.setTaskID(shSR04,'P',75);}                              //--Периодический вызов 75ms;
if(dvSR04.custom==0){dvSR04.custom=1; dvSR04.extPinTrig=pinSR04; dvSR04.maxLen=400;}    //--Настройка параметров;
dvSR04.run=RT_HW_Base.directTask(shSR04);                                               //--Управление задачей; 
RT_HW_sr04.direct(dvSR04);                                                              //--Управление устройством;
if(dvSR04.state==1){dvSR04.state++;  attachInterrupt(dvSR04.numIRQ, RT_HW_IRQ_SR04_handler_dvSR04,CHANGE);}
if(dvSR04.fresh)   {dvSR04.fresh=0;  dvSR04.LenMcs=ftrSR04.filtered(dvSR04.echoMcs);    //--Обновление данных;
                    dvSR04.Len=round(dvSR04.LenMcs * dvSR04.speedSoundAir/10.0) ;  
                 if(dvSR04.Len>dvSR04.maxLen){dvSR04.Len=dvSR04.maxLen;}
                    vSR04Len=dvSR04.Len;  vSR04ok=dvSR04.ok;}         
};
#else
void snsSR04(){;};
#endif
//=================================================================================================
//                                    3.4.AHTxx.i2c (T,H)      
//=================================================================================================
RT_HW_AHTxx_DEV   dvAHTxx;      RT_HW_STRUCT_SHED_TASK shAHTxx; 
#ifdef RT_HW_TEST_PERMIT_AHTx
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void snsAHTxx(){
//-------------------------------------------------------------------------------------------------
if(dvAHTxx.custom==0) {dvAHTxx.mi='I';          
                 dvAHTxx.custom=RT_HW_Base.i2cSetParam(dvAHTxx.dvI,i2cAdrAHTxx,0,0);  //--Настройка параметров (адрес i2c, номер шины, скорость);
                 shAHTxx.periodLimit=50;  RT_HW_Base.setTaskID  (shAHTxx,'P',1200);}  //--Периодический вызов 75ms;
//-------------------------------------------------------------------------------------------------
RT_HW_Base.directTask(shAHTxx);                                                       //--Управление задачей;  
RT_HW_ahtxx.direct(dvAHTxx,shAHTxx.run);                                              //--Управление устройством;
//-------------------------------------------------------------------------------------------------
if(dvAHTxx.fresh){
//-------------------------------------------------------------------------------------------------
//if(RT_HW_Base.consoleOk()){  
//sign='-'; if(dvAHTxx.ok){sign='+';} RT_HW_Base.consoleVar(sign);    //--Вывод а консоль;
//RT_HW_Base.consoleTest(String(F("AHTxx  T")),dvAHTxx.vTemp,';'); 
//RT_HW_Base.consoleTest(String(F(" H")),      dvAHTxx.vHum),'E';
//}
//-------------------------------------------------------------------------------------------------
}
if(dvAHTxx.fresh){dvAHTxx.fresh=0; vAHTxx_ok=dvAHTxx.ok; vAHTxx_Temp=dvAHTxx.vTemp; vAHTxx_Hum=dvAHTxx.vHum;}  //--Обновление данных;
};
#else
void snsAHTxx(){;};
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     4. РАСШИРИТЕЛИ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                                     4.1. 74HC595.SPI Ввывод бегущей '1'
//=================================================================================================
RT_HW_74HC595_DEV       dv74HC595;
RT_HW_GENERATOR_RUN_ID  idRun;  
//-------------------------------------------------------------------------------------------------
#ifdef RT_HW_TEST_PERMIT_74HC595
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void exp74HC595(){   
//------------------------------------------------------------------------------------------------
if(dv74HC595.custom==0){dv74HC595.custom=RT_HW_Base.spiSetParam(dv74HC595.dvS,cs74HC595,0,4000000);
                        dv74HC595.mi='S'; dv74HC595.qnt=1;  //--Кол-во регистров 74HC595(1-4);
                        dv74HC595.bitOrder=0;               //--Последовательность вывода: =1 - впереди старший бит;
                        //-----------------------------------------------------------------------
                        idRun.top=8;                                              //--Кол-во бит=8,16,24,32;
                        idRun.modeGen='S';}                                       //--Тип генератора: S-пила, T-треугольник; 
//-------------------------------------------------------------------------------------------------
RT_HW_Base.generatorRun(idRun,100);
RT_HW_74hc595.direct(dv74HC595,idRun.dc,idRun.event);};
#else
void exp74HC595(){;};
#endif

//=================================================================================================
//                                     2.2. 74HC165.SPI
//=================================================================================================
RT_HW_74HC165_DEV dv74HC165;    RT_HW_STRUCT_SHED_TASK sh74HC165;  uint32_t v74HC165,  ago74HC165;
//-------------------------------------------------------------------------------------------------
#ifdef RT_HW_TEST_PERMIT_74HC165
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void exp74HC165(){   
if(dv74HC165.custom==0){dv74HC165.custom=RT_HW_Base.spiSetParam(dv74HC165.dvS,cs74HC165,0,4000000);
                        dv74HC165.mi='S'; dv74HC165.qnt=2; dv74HC165.bitOrder=1;  //--qnt=Number of registers 74HC595(1-4);
                        RT_HW_Base.setTaskID(sh74HC165,'P',50);}                  //  Setting task: 'P';
//-------------------------------------------------------------------------------------------------
RT_HW_Base.directTask(sh74HC165); 
//-------------------------------------------------------------------------------------------------
RT_HW_74hc165.direct(dv74HC165,sh74HC165.run); 
if(dv74HC165.fresh){dv74HC165.fresh=0;  v74HC165=dv74HC165.var;};
};
#else
void exp74HC165(){;};
#endif

//=================================================================================================
//                                     4.4.MCP4725.i2c;
//=================================================================================================
RT_HW_MCP4725_DEV        dvMCP4725;   RT_HW_STRUCT_SHED_TASK shMCP4725;
RT_HW_GENERATOR_EVENT_ID idGenDAC;    RT_HW_COUNTER_ID idCntDAC;      uint16_t vGenDAC=0;                //--For generator 0-4095 DAC;
//-------------------------------------------------------------------------------------------------
#ifdef RT_HW_TEST_PERMIT_MCP4725
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void expMCP4725(){ 
//------------------------------------------------------------------------------------------------
if(idCntDAC.reset){RT_HW_Base.counterReset(idCntDAC,4095,0,10,0);}  //--init counter: Upper limit=4095, Down limit=0, Change step=10, Initial value=0;
if(RT_HW_Base.generatorEvent(idGenDAC,10)) {vGenDAC=RT_HW_Base.counterT(idCntDAC);}; //--Triangle generator 0-4095 for DAC,100 ms;
//-------------------------------------------------------------------------------------------------
if(dvMCP4725.custom==0){dvMCP4725.custom=RT_HW_Base.i2cSetParam(dvMCP4725.dvI,i2cAdrMCP4725,0,800000); //--800 кГц;
                        dvMCP4725.mi='I'; RT_HW_Base.setTaskID(shMCP4725,'Q'); shMCP4725.period=0;}
//------------------------------------------------------------------------------------------------
RT_HW_Base.directTask(shMCP4725);                         //--Launching task; 
RT_HW_mcp4725.direct(dvMCP4725,vGenDAC,shMCP4725.run );   //--Direct MCP4725;
};
#else
void expMCP4725(){;};
#endif
//=================================================================================================
//                                     4.5.MCP4725x.i2c;
//=================================================================================================
RT_HW_MCP4725_DEV        dvMCP4725x;   RT_HW_STRUCT_SHED_TASK shMCP4725x;
RT_HW_GENERATOR_EVENT_ID idGenDACx;    RT_HW_COUNTER_ID idCntDACx;      uint16_t vGenDACx=0;                //--For generator 0-4095 DAC;
#ifdef RT_HW_TEST_PERMIT_MCP4725x
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//-------------------------------------------------------------------------------------------------
void expMCP4725x(){ 
//------------------------------------------------------------------------------------------------
if(idCntDACx.reset){RT_HW_Base.counterReset(idCntDACx,4095,0,10,0);}  //--init counter: Upper limit=4095, Down limit=0, Change step=10, Initial value=0;
if(RT_HW_Base.generatorEvent(idGenDACx,10)) {vGenDACx=RT_HW_Base.counterT(idCntDACx);}; //--Triangle generator 0-4095 for DAC,100 ms;
//-------------------------------------------------------------------------------------------------
if(dvMCP4725x.custom==0){dvMCP4725x.custom=RT_HW_Base.i2cSetParam(dvMCP4725x.dvI,i2cAdrMCP4725x,0,800000); //--800 кГц;
                        dvMCP4725x.mi='I'; RT_HW_Base.setTaskID(shMCP4725x,'Q'); shMCP4725x.period=0;}
//------------------------------------------------------------------------------------------------
RT_HW_Base.directTask(shMCP4725x);                          //--Launching task; 
RT_HW_mcp4725.direct(dvMCP4725x,vGenDACx,shMCP4725x.run );   //--Direct MCP4725;
};
#else
void expMCP4725x(){;};
#endif
//=================================================================================================
//                              5.Формирование вектора состояний устройств
//=================================================================================================
void setFlagStatus(){
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
//=====================================================================================================
