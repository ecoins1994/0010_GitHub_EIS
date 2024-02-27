//=================================================================================================
//                                  1.Объекты и параметры,функции 
//=================================================================================================
RT_HW_FILTER_RING_AVERAGE<uint32_t,5> FilterSpeed0; uint32_t vSpeedMCUF0;  uint16_t vspeedMCUF0;    //--Фильтр, быстродействие, быстродействие/1000 CORE 0;
RT_HW_FILTER_RING_AVERAGE<uint32_t,5> FilterSpeed1; uint32_t vSpeedMCUF1;  uint16_t vspeedMCUF1;    //--Фильтр, быстродействие, быстродействие/1000 CORE 1;
uint32_t  flagSystem=0, flagDevice=0;                                         //--Флаги системные и устройств;
int16_t counter = -10;                //--Тестовый счетчик;
//-------------------------------------------------------------------------------------------------
//                    Параметры PLC RP2040 v.5.5
//-------------------------------------------------------------------------------------------------
  RT_HW_PIN_DIR_ID    idDotPLC[4];  uint8_t pinDotPLC[4]={2,3,22,28};   uint16_t plcDOT_vr=0; uint8_t cs595PLC=17; //--12 дискретных выходов;
  RT_HW_PIN_DIR_ID    idDinPLC[4];  uint8_t pinDinPLC[4]={10,11,23,29}; uint16_t plcDIN_vr=0; uint8_t cs165PLC=20; //--12 дискретных входов;  
  uint16_t pinDOT=0,pinDIN=0;
  uint8_t  plcIdx;                            //--Рабочий индекс;
  IPAddress ethIP{0,0,0,0};                   //--IP адрес Ethernet;
  uint8_t   ethServerCnt=0;                   //--Кол-во соединений с WEB-сервером;
//-------------------------------------------------------------------------------------------------
//                                   Параметры UART для Modbus Master RTU 
//-------------------------------------------------------------------------------------------------
uint8_t uartModbusMaster=255; 
uint8_t uartModbusSlave=255;   
uint8_t  MbMasterRTU1_numUART=1;      //--Номер UART Master;
uint8_t  MbSlaveRTU1_numUART=2;       //--Номер UART     Modbus Slave RTU1; 
uint16_t rg0=0,rg1=0,rg2=0,rg3=0,rg4=0,rg5=0,rg6=0,rg7=0;
uint16_t wg0=0,wg1=0,wg2=0,wg3=0,wg4=0,wg5=0,wg6=0,wg7=0;
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_TEST_PERMIT_MB_MASTER_RTU)
  ModbusMasterRTU   MasterRTU1(1, 2);   //--Создание Master: номер UART=1; кол-во Slave=2 (Slave 0,1);
  uint8_t  MbMasterRTU1_custom=0;       //--Флаг настройки Modbus Slave RTU1;
  int tempInt;
  bool tempBool;
  int value, oldValue;
  unsigned long startTime; 
#endif
//-------------------------------------------------------------------------------------------------
//                                   Параметры UART для Modbus Slave RTU 
//-------------------------------------------------------------------------------------------------
#if defined(RT_HW_TEST_PERMIT_MB_SLAVE_RTU)
  ModbusSlaveRTU   SlaveRTU1(1);        //--Создание объекта Мodbus Slave на UART=1;
  int      MbSlaveRTU1_DI_Adr[]={8,9,10,11,12,14,15,16,17,18}; //--Таблица доступных адресов для 10-ти регистров;  
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
//                                   1.10.Параметры UART для моста WiFi
//=================================================================================================
uint8_t uartWiFi=255;

//-------------------------------------------------------------------------------------------------
uint8_t cnsCnt=0, cnsADC=0, first=0, vAgoButton=0;                            //--Рабочие параметры;
//-------------------------------------------------------------------------------------------------
uint8_t i2cAdrAHTxx=0x38;     uint8_t  vAHTxx_ok;   float    vAHTxx_Temp, vAHTxx_Hum; //--i2c.Сенсор AHTxx;
uint8_t i2cAdrSHT3x=0x44;     uint8_t  vSHT3x_ok;   float    vSHT3x_Temp, vSHT3x_Hum; //--i2c.Сенсор SHT3x; 
uint8_t i2cAdrBME280=0x77;    uint8_t  vBMPx80_ok;  float    vBMPx80_Press;           //--i2c.Сенсор BMEx80/BMPx80;
uint8_t i2cAdrBMP180=0x77;                                                            //--i2c.Сенсор BMP180;
uint8_t i2cAdrBH1750=0x23;    uint8_t  vBH1750_ok;  uint16_t vBH1750_Lux;             //--i2c.Сенсор BH1750;
uint8_t i2cAdrMCP4725=0x60;   uint8_t  vMCP4725_ok; uint16_t vMCP4725_vr;             //--i2c.Расширитель DAC;
uint8_t i2cAdrADS1115=0x48;   uint8_t  vADS1115_ok; float    vADS1115_A0f,            //--i2c.Расширитель ADC
                                       vADS1115_A1f,vADS1115_A2f,vADS1115_A3f;        //                  ADS1115;
uint8_t i2cAdrLcd1=0x27;                                                              //--i2c.Дисплей Lcd1 HD44780 (16x2);
uint8_t i2cAdrLcd2=0x3E;                                                              //--i2c.Дисплей Lcd2 HD44780 (20x4);
uint8_t i2cAdrLcd3=0x26;                                                              //--i2c.Дисплей Lcd3 HD44780 (20x4);
uint8_t uartNextion=255;     uint8_t nxtPage=0; uint8_t nxtVr1,nxtVr2,nxtVr3,nxtVr4;  //--UART.Панель Nextion;
