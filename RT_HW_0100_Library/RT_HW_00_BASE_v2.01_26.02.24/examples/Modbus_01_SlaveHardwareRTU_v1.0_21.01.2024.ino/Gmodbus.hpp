//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
//                                  TEST Modbus Slave RTU (HardWare)
//-------------------------------------------------------------------------------------------------
// 1.Последовательность байтов для хранения различных типов данных
//  1.1.Возможные значения:
//      Для Integer:
//      FLPROG_AB_ORDER
//      FLPROG_BA_ORDER
//  1.2.Для остальных типов:
//      FLPROG_ABCD_ORDER
//      FLPROG_CDAB_ORDER
//      FLPROG_BADC_ORDER
//      FLPROG_DCBA_ORDER
// 1.3.По умолчанию заданы значения  FLPROG_AB_ORDER  и FLPROG_ABCD_ORDER
// 1.4.В любое время эти значения могут быть изменены следующими функциями
//     SlaveRTU1.setLongOrder(FLPROG_DCBA_ORDER);
//     SlaveRTU1.setFloatOrder(FLPROG_BADC_ORDER);
//     SlaveRTU1.setUnsignedlongOrder(FLPROG_CDAB_ORDER);
//     SlaveRTU1.setIntOrder(FLPROG_AB_ORDER);
//-------------------------------------------------------------------------------------------------
// 2.По умолчанию пин управления потоком приёма/передачи не используется.
//     При необходимости он задается функцией:
//     SlaveRTU1.setPinPeDe(pin);
//-------------------------------------------------------------------------------------------------
// 3.По умолчанию UART настраивается с параметрами 9600 8N1
// Параметры порта можно менять во время исполнения программы с использованием констант
//    FLPROG_SPEED_300,  FLPROG_SPEED_600,   FLPROG_SPEED_1200,   FLPROG_SPEED_2400,  FLPROG_SPEED_4800
//    FLPROG_SPEED_9600, FLPROG_SPEED_14400, FLPROG_SPEED_19200,  FLPROG_SPEED_28800, FLPROG_SPEED_38400
//    FLPROG_PEED_57600, FLPROG_SPEED_115200
//    и функциями;
// SlaveRTU1.setPortSpeed(FLPROG_SPEED_115200);//--Установка скорости                  [default=9600];
// SlaveRTU1.setPortDataBits(8);               //--Установка кол-ва бит данных (5,7,8) [default=8];
// SlaveRTU1.setPortStopBits(1);               //--Установка количество стоп-бит(0,1,2)[default=1];
// SlaveRTU1.setPortParity(0);                 //--Устан.четности:0=NONE, 1=EVEN, 2=ODD[default=0];
//-------------------------------------------------------------------------------------------------
// 4.Функции для работы с регистрами
//      void saveLong(long value, byte table, int startAddres);
//      void saveUnsignedLong(unsigned long value, byte table, int startAddres);
//      void saveFloat(float value, byte table, int startAddres);
//      void saveInteger(int value, byte table, int startAddres);
//      void saveByte(byte value, byte table, int startAddres);
//      void saveBool(bool value, byte table, int startAddres);
//      byte readByte(byte table, int startAddres);
//      int readInteger(byte table, int startAddres);
//      float readFloat(byte table, int startAddres);
//      long readLong(byte table, int startAddres)
//      unsigned long readUnsignedLong(byte table, int startAddres);
//      bool readBool(byte table, int startAddres);
//-------------------------------------------------------------------------------------------------
// ecoins@mail.ru 20.01.2024
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                                   1.Объекты и параметры UART для Modbus RTU
//=================================================================================================
/*
  ModbusSlaveRTU SlaveRTU1(1);      //--Создание объекта Мodbus Slave на UART=1;
  int     MbSlaveRTU1_DI_Adr[]={8, 9, 10, 11, 12, 14, 15, 16, 17, 18};  //--Таблица доступных адресов для 10-ти входных дискретных регистров; 
  uint8_t MbSlaveRTU1_custom=0;     //--Флаг настройки Modbus Slave RTU1;
  uint8_t MbSlaveRTU1_numUART=1;    //--Номер UART     Modbus Slave RTU1;   
  uint8_t MbSlaveRTU1_ID=1;         //--ID(адрес)      Modbus Slave RTU1;
  uint16_t rg0=0,rg1=0,rg2=0,rg3=0,rg4=0,rg5=0,rg6=0,rg7=0;
  uint16_t wg0=0,wg1=0,wg2=0,wg3=0,wg4=0,wg5=0,wg6=0,wg7=0;
//=================================================================================================
//                                  2.Рабочие переменные
//=================================================================================================
  int16_t counter = -10;
  int16_t saveInt16=-23567; 
  int32_t saveInt32=123456;
  float   saveFloat1=12.5; 
  float   saveFloat2=23.4;
  bool    saveBlink=0;
  int     lastError;
*/  
//=================================================================================================
//                                3.Настройка UART для Modbus Slave RTU 1
//=================================================================================================
void setParamModbusRtuSlave(){ 
//------------------------------------------------------------------------------------------------- 
//                                3.1.Настройка UART
//-------------------------------------------------------------------------------------------------
  MbSlaveRTU1_numUART=RT_HW_Base.device.uart.modbus2; //--Определение     номера UART RTU Slave Master из описания контроллера;
//MbSlaveRTU1_numUART=1;                              //--Переопределения номера UART RTU Slave Master (при необходимости);
  SlaveRTU1.setUart(MbSlaveRTU1_numUART);             //--Установка       номера UART RTU Slave Master;
  SlaveRTU1.setSpeedUart(FLPROG_SPEED_115200);        //--Установка скорости                   [default=9600];
  SlaveRTU1.setDataBitUart(8);                        //--Установка кол-ва бит данных (5,7,8)  [default=8];
  SlaveRTU1.setStopBitUart(1);                        //--Установка количество стоп-бит(0,1,2) [default=1];
  SlaveRTU1.setParityUart(0);                         //--Устан.четности:0=NONE, 1=EVEN, 2=ODD [default=0];
  SlaveRTU1.setSlaveAddress(MbSlaveRTU1_ID);          //--Определение адреса(ID) Slave(ID=1);
//-------------------------------------------------------------------------------------------------
//                               3.2.Задание областей памяти ModBus
//-------------------------------------------------------------------------------------------------
  SlaveRTU1.configDataTable(FLPROG_HOLDING_REGISTR,50);     //--10 регистров типа HOLDING REGISTER, стартовый адрес=0 (адреса 0-39);
  SlaveRTU1.configDataTable(FLPROG_INPUT_REGISTR,  10);     //--10 регистров типа INPUT   REGISTER, стартовый адрес=0 (адреса 0-9);
  SlaveRTU1.configDataTable(FLPROG_COIL,           15, 5);  //--15 регистров типа COIL,             стартовый адрес=5 (адреса 5-14);
  SlaveRTU1.setDataTable   (FLPROG_DISCRETE_INPUT, 10,MbSlaveRTU1_DI_Adr); //--10 регистров типа DISCRETE INPUT, с адресами в соответствии с таблицей;
};
