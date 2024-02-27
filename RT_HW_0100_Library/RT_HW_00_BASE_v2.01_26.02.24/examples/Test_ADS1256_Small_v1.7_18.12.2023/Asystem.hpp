//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                    1.Data SYSTEM
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                                   1.1.Параметры для работы с диспетчером задач
//=================================================================================================
uint8_t vInit=0;                                                                                      //--Состояние инициализации параметров;
//------------------------------------------------------------------------------------------------
RT_HW_STRUCT_SHED shed;  uint32_t vSpeedMCU=0;      uint16_t vSpeedSmall=0;     uint32_t vSpeedFltr;  //--Диспетчер для ядра CORE 0;
RT_HW_FILTER_RING_AVERAGE<uint32_t,5> FilterSpeed;  uint32_t vSpeedMCUF;                              //--Фильтр для быстройдествия CORE 0;
uint32_t vMotorSec=0;                                                                                 //--Мотосекунды;
//------------------------------------------------------------------------------------------------
//char sign; bool  blink;                        //--Рабочие регистры для отладки;
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
//=================================================================================================
//                                   1.4.Параметры тестовых устройств через i2c
//=================================================================================================
uint8_t i2cAdrAHTxx=0x38;     uint8_t vAHTxx_ok;  float    vAHTxx_Temp,  vAHTxx_Hum; //--Сенсор AHTxx;
uint8_t i2cAdrLcd1=0x27;      uint8_t i2cAdrLcd2=0x3E; 
//=================================================================================================
//                                   1.5.Параметры тестовых устройств
//=================================================================================================
uint8_t  cs74HC595=255;      //--[cs0];
uint8_t  csADS1256=255;      //--[cs2];
uint8_t  vAdcOk;
uint32_t vAdc0,vAdc1,vAdc2,vAdc3,vAdc4,vAdc5,vAdc6,vAdc7,vAdc01,vAdc23,vAdc45,vAdc67;
float    vADC0,vADC1,vADC2,vADC3,vADC4,vADC5,vADC6,vADC7,vADC01,vADC23,vADC45,vADC67;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     2.СИСТЕМНЫЕ ФУНКЦИИ
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                                    2.1.Инициализация параметров
//=================================================================================================
void initProject(){
if(vInit==1){return;} vInit=1;
shed.quick.qnt =5; shed.fast.qnt =4; shed.slow.qnt =4; shed.back.qnt=5; 
shed.frdm.qnt =10;
//--------------------------------------------------------------------------------------------------
pinControl  =RT_HW_Base.device.pin.control;  //--Установка пина Control;
pinLed      =RT_HW_Base.device.pin.led;      //--Установка пина Led;
pinButton   =RT_HW_Base.device.pin.button;   //--Установка пина Кнопки;
pinADC      =RT_HW_Base.device.pin.adc;      //--Установка пина ADC; 
pinDebug=4;
//-------------------------------------------------------------------------------------------------
i2cAdrLcd1    =0x27;                        //--Adress Lcd1;
i2cAdrAHTxx   =0x38;                        //--Adress AHTXX;         
//-------------------------------------------------------------------------------------------------
cs74HC595   =RT_HW_Base.device.spi.cs0;     //--cs 74HC595; 
csADS1256   =RT_HW_Base.device.spi.cs2;     //--cs ADS1256;
//if(RT_HW_Base.device.spi.cs0!=255){digitalWrite(RT_HW_Base.device.spi.cs0,1); pinMode(RT_HW_Base.device.spi.cs0,OUTPUT);}
//if(RT_HW_Base.device.spi.cs1!=255){digitalWrite(RT_HW_Base.device.spi.cs1,1); pinMode(RT_HW_Base.device.spi.cs1,OUTPUT);}
//if(RT_HW_Base.device.spi.cs2!=255){digitalWrite(RT_HW_Base.device.spi.cs2,1); pinMode(RT_HW_Base.device.spi.cs2,OUTPUT);}
//if(RT_HW_Base.device.spi.cs3!=255){digitalWrite(RT_HW_Base.device.spi.cs3,1); pinMode(RT_HW_Base.device.spi.cs3,OUTPUT);}
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
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     3.СИСТЕМНЫЕ УСТРОЙСТВА
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
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
                 shAHTxx.periodLimit=50;  RT_HW_Base.setTaskID  (shAHTxx,'P',1200);}  //--Периодический вызов 1200ms;
//-------------------------------------------------------------------------------------------------
RT_HW_Base.directTask(shAHTxx);                                                       //--Управление задачей;  
RT_HW_ahtxx.direct(dvAHTxx,shAHTxx.run);                                              //--Управление устройством;
//-------------------------------------------------------------------------------------------------
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
RT_HW_74HC595_DEV       dv74HC595; RT_HW_STRUCT_SHED_TASK sh74HC595;
RT_HW_GENERATOR_EVENT_ID idGen74HC595;    RT_HW_COUNTER_ID idCnt74HC595;      uint32_t vCnt74HC595,vGen74HC595=0; 
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#ifdef RT_HW_TEST_PERMIT_74HC595
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//=================================================================================================
//                                     2.1. 74HC595.SPI
//=================================================================================================
void exp74HC595(){   
if(idCnt74HC595.reset){RT_HW_Base.counterReset(idCnt74HC595,8,0,1,0);}   //--Инициализация счетчика: Верх=8, Низ=0, Шаг=1, Нач.значение=0;
if(RT_HW_Base.generatorEvent(idGen74HC595,100)) {vCnt74HC595=RT_HW_Base.counterS(idCnt74HC595); vGen74HC595=RT_HW_Base.dc8(vCnt74HC595);}
//-----------------------------------------------------------------------------------------------
if(dv74HC595.custom==0){dv74HC595.custom=RT_HW_Base.spiSetParam(dv74HC595.dvS,cs74HC595,0,4000000);
                        dv74HC595.mi='S'; dv74HC595.qnt=1; dv74HC595.bitOrder=1;}  //--qnt=Кол-во регистров 74HC595(1-4);
//-------------------------------------------------------------------------------------------------
if(sh74HC595.custom==0){RT_HW_Base.setTaskID(sh74HC595,'Q');} //-Параметры задачи: 'Q'-по изменению через каждые 5 цикло loop() (default=5);
//-------------------------------------------------------------------------------------------------
RT_HW_Base.directTask(sh74HC595); 
//-------------------------------------------------------------------------------------------------
RT_HW_74hc595.direct(dv74HC595,vGen74HC595,sh74HC595.run);
};
#else
void exp74HC595(){;};
#endif
//=====================================================================================================

//=================================================================================================
//                                  5.Heading console output
//=================================================================================================
void consoleHead(){
  RT_HW_Base.consoleCR(3);
  RT_HW_Base.consoleHead(String(F("Test Board_12_Small_Device_v0.1 22.11.2023)")),'='); 
  RT_HW_Base.consoleHead(String(F("24-битный 8-канальный скоростной АЦП типа ADS1256)")),'+');   
  RT_HW_Base.consoleHead(String(F("Main parameters")),'-');  RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleBoardGeneral();   
  RT_HW_Base.consoleHead(String(F("Add parameters")));       RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleBoardAdd(); 
  RT_HW_Base.consoleHead(String(F("Task parameters")));      RT_HW_Base.consoleShedulerParameters();
//RT_HW_Base.consoleHead(String(F("PGM array")));            RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleFromPGM();
  RT_HW_Base.consoleHead(String(F("Available pins")));       RT_HW_Base.mess.modePin='A'; RT_HW_Base.consolePinsAll();        
  RT_HW_Base.consoleHead(String(F("Interface")));            RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleInterface(); 
  RT_HW_Base.consoleHead(String(F("System,test,cs pins")));  RT_HW_Base.mess.modePin='T'; RT_HW_Base.consolePinsSystem(); RT_HW_Base.consolePinsTest(); RT_HW_Base.consolePinsCS(); 
  RT_HW_Base.consoleVar (String(F("SPI cs-->")));            RT_HW_Base.mess.modePin='T';
  RT_HW_Base.consoleTest(String(F(" cs 74HC595")),   cs74HC595, ';','P');
  RT_HW_Base.consoleTest(String(F(" cs ADS1256")),   csADS1256, ';','P');
  RT_HW_Base.consoleCR();
  RT_HW_Base.consoleHead(String(F("Scan i2c")));             RT_HW_Base.mess.modePin='T'; RT_HW_Base.i2cScanBus(0);   
  RT_HW_Base.consoleLine('+'); 
};
