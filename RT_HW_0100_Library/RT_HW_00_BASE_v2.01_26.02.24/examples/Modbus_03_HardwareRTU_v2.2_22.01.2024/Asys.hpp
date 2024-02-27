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
//------------------------------------------------------------------------------------------------
uint32_t  flagSystem=0, flagDevice=0;                                                                  //--Флаги системные и устройств;
//------------------------------------------------------------------------------------------------
uint8_t   agoDir=255, agoStep=255, agoCodeErr=255; char sign; bool  blink;                             //--Рабочие регистры для отладки;
uint32_t  timeUNIX=0,timeUNIX_Ago=0;
uint8_t   timeHour,timeMin,timeSec,timeZone=3;
//-------------------------------------------------------------------------------------------------
RT_HW_GENERATOR_EVENT_ID genDAC;     RT_HW_COUNTER_ID cntDAC;        uint16_t vDAC;         //--Для генератора DAC
RT_HW_GENERATOR_EVENT_ID idGenDAC;   RT_HW_COUNTER_ID idCntDAC;      uint16_t vGenDAC=0;    //--Для генератора кругового индикатора Nextion;
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
RT_HW_PIN_ADC_ID   idPinADC;      uint8_t pinADC=255;     uint16_t vADC,agoADC,vADCF; //--Пин ADC,значения с пина ADC и обработки;   
RT_HW_FILTER_RING_AVERAGE<uint32_t,5>  filterADC;         //--Параметры фильтра ADC (скользящее среднее 5-го порядка);
//=================================================================================================
//                                   1.3.Параметры тестовых устройств 
//=================================================================================================      
uint8_t pinDS1820=255;        uint8_t vDS1820ok;   float    vDS1820Temp; 
uint8_t pinSR04=255;          uint8_t vSR04ok;     uint16_t vSR04Len;  
uint8_t i2cAdrAHTxx=0x38;     uint8_t vAHTxx_ok;   float    vAHTxx_Temp,  vAHTxx_Hum; //--Сенсор AHTxx;
uint8_t i2cAdrSHT3x=0x44;     uint8_t vSHT3x_ok;   float    vSHT3x_Temp,  vSHT3x_Hum; ;
uint8_t i2cAdrBH1750=0x23;    uint8_t vBH1750ok;   uint16_t vBH1750Lux; 
uint8_t i2cAdrADS1115=0x48;   uint8_t vADS1115_ok; float vADS1115_A0f,vADS1115_A1f,vADS1115_A2f,vADS1115_A3f;
uint8_t cs74HC165=255;      //--Выходной сдвиговый регистр;
uint8_t cs74HC595=255;      //--Входной  сдвиговый регистр;
uint8_t i2cAdrLcd1=0x27;    //--Дисплей;
//=================================================================================================
int16_t counter = -10;                //--Тестовый счетчик;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                   1.4.Объекты и параметры UART для Modbus RTU
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  uint16_t rg0=0,rg1=0,rg2=0,rg3=0,rg4=0,rg5=0,rg6=0,rg7=0; //--Регистры для записи внешним Mастером;
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_TEST_PERMIT_MB_MASTER_RTU)
  ModbusMasterRTU   MasterRTU1(1, 2);   //--Создание Master: номер UART=1; кол-во Slave=2 (Slave 0,1);
  uint8_t  MbMasterRTU1_numUART=1;      //--Номер UART Master;
  uint8_t  MbMasterRTU1_custom=0;       //--Флаг настройки Modbus Slave RTU1;
  int tempInt;
  bool tempBool;
  int value, oldValue;
  unsigned long startTime; 
#endif
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_TEST_PERMIT_MB_SLAVE_RTU)
  ModbusSlaveRTU   SlaveRTU1(1);        //--Создание объекта Мodbus Slave на UART=1;
  int      MbSlaveRTU1_DI_Adr[]={8,9,10,11,12,14,15,16,17,18}; //--Таблица доступных адресов для 10-ти регистров;
  uint8_t  MbSlaveRTU1_numUART=2;       //--Номер UART     Modbus Slave RTU1;   
  uint8_t  MbSlaveRTU1_ID=1;            //--ID(адрес)      Modbus Slave RTU1;
  uint8_t  MbSlaveRTU1_custom=0;        //--Флаг настройки Modbus Slave RTU1;
  int16_t saveInt16=-23567;             //--Рабочая переменная int16_t;
  int32_t saveInt32=123456;             //--Рабочая переменная int32_t;
  float   saveFloat1=12.5;              //--Рабочая переменная float; 
  float   saveFloat2=23.4;              //--Рабочая переменная float;
  bool    saveBlink=0;                  //--Рабочая переменная bool;
#endif
//-------------------------------------------------------------------------------------------------
int16_t  lastError;
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
  shed.quick.qnt =5; shed.fast.qnt =4; shed.slow.qnt =4; shed.back.qnt=5;  shed.frdm.qnt =50;
  RT_HW_Base.unixID.zone=3;                  //--Установка часового пояса(default=3);
//-------------------------------------------------------------------------------------------------
  pinControl=RT_HW_Base.device.pin.control; //--Установка пина Control;
  pinLed    =RT_HW_Base.device.pin.led;     //--Установка пина Led;
  pinButton =RT_HW_Base.device.pin.button;  //--Установка пина Кнопки;
  pinADC    =RT_HW_Base.device.pin.adc;     //--Установка пина ADC; 
//-------------------------------------------------------------------------------------------------
  pinDS1820 =RT_HW_Base.device.dev.oneWire; //--Установка пина 1-Wire;
  pinSR04   =RT_HW_Base.device.dev.sr04;    //--Установка пина HC-SR04.trig;
  cs74HC595 =RT_HW_Base.device.spi.cs0;     //--Установка пина cs 74HC595; 
  cs74HC165 =RT_HW_Base.device.spi.cs1;     //--Установка пина cs 74HC165;
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_TEST_PERMIT_MB_MASTER_RTU)
  MbMasterRTU1_numUART=RT_HW_Base.device.uart.modbus1;
#endif
#if defined(RT_HW_TEST_PERMIT_MB_SLAVE_RTU)  
  MbSlaveRTU1_numUART=RT_HW_Base.device.uart.modbus2;
#endif  
};    //--END initProject()
//=====================================================================================================
//                                    2.2.Чтение кнопки с защитой от дребезга 50 ms
//=====================================================================================================
void fncButton(){
if(pinButton!=255){vButton=!RT_HW_Base.pinDigitalRead(idPinButton,pinButton,'U');}  //--Чтение кнопки с подтяжкой пина к Vcc;
else              {vButton=0;}
vChatBut=RT_HW_Base.chatterDIN(idChatBut,vButton,50);           //--Защита от дребезга;
};
//=====================================================================================================
//                                    2.3.Чтение ADC
//=====================================================================================================
void fncADC(){
RT_HW_Base.pinAnalogRead(idPinADC,pinADC);    //--Read ADC;
vADCF=filterADC.filtered(idPinADC.vNorm);     //--Fltered ADC;
};
//=================================================================================================
//                                    2.6.Счетчик для тестирования
//=================================================================================================
void fncCounter(){ 
    if(++counter > 10){counter = -10;}
#if defined(RT_HW_TEST_PERMIT_MB_SLAVE_RTU)
    saveBlink = !saveBlink;
    saveInt16=counter;
    saveInt32=counter*1000;
    saveFloat1=counter / 10.0;
    saveFloat2=counter / 100.0;
#endif     
};
//=================================================================================================
//                                    2.7.Формирование вектора состояний устройств
//=================================================================================================
void fncSetStatus(){
//------------------------------------------------------------------------------------------------
bitWrite(flagSystem,1,shed.blink500);
bitWrite(flagSystem,2,vChatBut);
//------------------------------------------------------------------------------------------------
bitWrite(flagDevice,0,vAHTxx_ok);
bitWrite(flagDevice,1,vSHT3x_ok);
bitWrite(flagDevice,7,vBH1750ok);
bitWrite(flagDevice,8,vDS1820ok);
bitWrite(flagDevice,9,vSR04ok);
bitWrite(flagDevice,30,vADS1115_ok);
};

//=================================================================================================
//                                  3.Вывод на консоль заголовка
//=================================================================================================
void consoleHead(){
  RT_HW_Base.consoleCR(3); 
//-------------------------------------------------------------------------------------------------
  RT_HW_Base.consoleHead(String(F("Тест Modbus 02:RTU Master Hardware v.1.0 21.01.2023)")),'='); 
  RT_HW_Base.consoleHead(String(F("Основные параметры")),'-');    RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleBoardGeneral();   
  RT_HW_Base.consoleHead(String(F("Дополнительные параметры")));  RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleBoardAdd(); 
  RT_HW_Base.consoleHead(String(F("Параметры диспетчера задач")));RT_HW_Base.consoleShedulerParameters();
//RT_HW_Base.consoleHead(String(F("PGM массивы")));               RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleFromPGM();
//RT_HW_Base.consoleHead(String(F(Доступные пины")));             RT_HW_Base.mess.modePin='A'; RT_HW_Base.consolePinsAll();        
  RT_HW_Base.consoleHead(String(F("Интерфейсы")));                RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleInterface(); 
  RT_HW_Base.consoleHead(String(F("Системные и тестовые пины. Пины cs")));  
                                                                  RT_HW_Base.mess.modePin='T'; RT_HW_Base.consolePinsSystem(); 
                                                                  RT_HW_Base.consolePinsTest(); RT_HW_Base.consolePinsCS(); 
//------------------------------------------------------------------------------------------------
  RT_HW_Base.consoleHead(String(F("Расширители SPI"))); 
  RT_HW_Base.consoleTest(String(F("cs 74HC595")),cs74HC595, 'E','U');
  RT_HW_Base.consoleTest(String(F("cs 74HC165")),cs74HC165, 'E','U');
//-----------------------------------------------------------------------------------------------
#if defined(RT_HW_TEST_PERMIT_MB_MASTER_RTU)
  RT_HW_Base.consoleHead(String(F("Параметры Modbus Master #1"))); 
  RT_HW_Base.consoleTest(String(F("Modbus Master RTU->Uart: num")),  MbMasterRTU1_numUART, ',','U');
  RT_HW_Base.consoleTest(String(F(" speed")),RT_HW_Base.uartGetSpeed(MbMasterRTU1_numUART),';','U');
  RT_HW_Base.consoleCR();
#endif
//------------------------------------------------------------------------------------------------
#if defined(RT_HW_TEST_PERMIT_MB_SLAVE_RTU)
  RT_HW_Base.consoleHead(String(F("Параметры Modbus Slave #1"))); 
  RT_HW_Base.consoleTest(String(F("Modbus  Slave RTU->Uart: num")), MbSlaveRTU1_numUART, ',','U');
  RT_HW_Base.consoleTest(String(F(" speed")),RT_HW_Base.uartGetSpeed(MbSlaveRTU1_numUART),';','U');
  RT_HW_Base.consoleTest(String(F(" ID(addres)")),                  MbSlaveRTU1_ID,      ';','U');
  RT_HW_Base.consoleCR();
#endif
//------------------------------------------------------------------------------------------------
RT_HW_Base.consoleHead(String(F("Scan i2c")));                  RT_HW_Base.mess.modePin='T'; RT_HW_Base.i2cScanBus(0);   
RT_HW_Base.consoleLine('+'); 
};
