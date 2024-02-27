//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#if defined(RT_HW_TEST_PERMIT_MB_SLAVE_RTU)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
//                              Modbus Slave RTU1
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

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
//
//                                Modbus Slave RTU1
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//================================================================================================= 
//                      1.Настройка и управление Modbus Slave RTU1
//=================================================================================================
if(RT_HW_Base.shed.frdm.num==11){
if(MbSlaveRTU1_custom==0){    //--Однократные действия
   MbSlaveRTU1_custom=1;
//------------------------------------------------------------------------------------------------- 
//                                1.1.Настройка UART
//-------------------------------------------------------------------------------------------------
  MbSlaveRTU1_numUART=RT_HW_Base.device.uart.modbus2; //--Определение     номера UART RTU Slave Master из описания контроллера;
//MbSlaveRTU1_numUART=3;                              //--Переопределения номера UART RTU Slave Master (при необходимости);
  SlaveRTU1.setUart(MbSlaveRTU1_numUART);             //--Установка       номера UART RTU Slave Master;
  SlaveRTU1.setSpeedUart(FLPROG_SPEED_115200);        //--Установка скорости                   [default=9600];
  SlaveRTU1.setDataBitUart(8);                        //--Установка кол-ва бит данных (5,7,8)  [default=8];
  SlaveRTU1.setStopBitUart(1);                        //--Установка количество стоп-бит(0,1,2) [default=1];
  SlaveRTU1.setParityUart(0);                         //--Устан.четности:0=NONE, 1=EVEN, 2=ODD [default=0];
  SlaveRTU1.setSlaveAddress(MbSlaveRTU1_ID);          //--Определение адреса(ID) Slave(ID=1);
//-------------------------------------------------------------------------------------------------
//                               1.2.Задание областей памяти ModBus
//-------------------------------------------------------------------------------------------------
  SlaveRTU1.configDataTable(FLPROG_HOLDING_REGISTR,50);     //--10 регистров типа HOLDING REGISTER, стартовый адрес=0 (адреса 0-39);
  SlaveRTU1.configDataTable(FLPROG_INPUT_REGISTR,  10);     //--10 регистров типа INPUT   REGISTER, стартовый адрес=0 (адреса 0-9);
  SlaveRTU1.configDataTable(FLPROG_COIL,           15, 5);  //--15 регистров типа COIL,             стартовый адрес=5 (адреса 5-14);
  SlaveRTU1.setDataTable   (FLPROG_DISCRETE_INPUT, 10,MbSlaveRTU1_DI_Adr); //--10 регистров типа DISCRETE INPUT, с адресами в соответствии с таблицей;  
//-------------------------------------------------------------------------------------------------  
} //--END if(MbSlaveRTU1_custom==0)  
//-------------------------------------------------------------------------------------------------
//                               1.3.Управление ModBus Slave RTU1
//-------------------------------------------------------------------------------------------------
  SlaveRTU1.pool();
}
//================================================================================================= 
//                2.Запись в таблицу битовых значений COIL (кол-во COIL=16, начальный адрес=5)
//=================================================================================================
if(RT_HW_Base.shed.quick.num==1){
  SlaveRTU1.saveBool(saveBlink,                 FLPROG_COIL, 5);    //--Blink 1 сек;
  SlaveRTU1.saveBool(RT_HW_Base.shed.blink250,  FLPROG_COIL, 6);    //--Меандр 250ms;
  SlaveRTU1.saveBool(RT_HW_Base.shed.blink500,  FLPROG_COIL, 7);    //--Меандр 500ms;
  SlaveRTU1.saveBool(bitRead(pinDIN,0),         FLPROG_COIL, 8);    //--DIN.0;   
};
//=================================================================================================
//                3.Запись в таблицу Holding Registers быстрых int16
//=================================================================================================
if(RT_HW_Base.shed.quick.num==2){
  SlaveRTU1.saveInteger(saveInt16,     FLPROG_HOLDING_REGISTR, 0);
  SlaveRTU1.saveInteger(2012,          FLPROG_HOLDING_REGISTR, 1);  //--ADC
  SlaveRTU1.saveInteger(123,           FLPROG_HOLDING_REGISTR, 2);  //--SR04;
  SlaveRTU1.saveInteger(vBH1750_Lux,   FLPROG_HOLDING_REGISTR, 3);
  SlaveRTU1.saveInteger(pinDIN,         FLPROG_HOLDING_REGISTR, 4);
  SlaveRTU1.saveInteger(flagSystem,    FLPROG_HOLDING_REGISTR, 5); 
  SlaveRTU1.saveInteger(flagDevice,    FLPROG_HOLDING_REGISTR, 6);   
};
//=================================================================================================
//                4.Запись в таблицу Holding Registers медленных int32
//=================================================================================================
if(RT_HW_Base.shed.slow.num==1){
  SlaveRTU1.saveInteger     (RT_HW_Base.unixID.hours,   FLPROG_HOLDING_REGISTR, 7); //--Часы;
  SlaveRTU1.saveInteger     (RT_HW_Base.unixID.minutes, FLPROG_HOLDING_REGISTR, 8); //--Минуты;
  SlaveRTU1.saveInteger     (RT_HW_Base.unixID.seconds, FLPROG_HOLDING_REGISTR, 9); //--Секунды;  
  SlaveRTU1.saveUnsignedLong(RT_HW_Base.shed.cntSec,    FLPROG_HOLDING_REGISTR,10); //--Мотосекунды;
  SlaveRTU1.saveUnsignedLong(RT_HW_Base.unixID.timeUNIX,FLPROG_HOLDING_REGISTR,12); //--UNIX время;  
};
//=================================================================================================
//                5.Запись в таблицу Holding Registers медленных float
//=================================================================================================
if(RT_HW_Base.shed.quick.num==2){
  SlaveRTU1.saveFloat(vADS1115_A0f, FLPROG_HOLDING_REGISTR, 30);
  SlaveRTU1.saveFloat(vADS1115_A1f, FLPROG_HOLDING_REGISTR, 32);
  SlaveRTU1.saveFloat(vADS1115_A2f, FLPROG_HOLDING_REGISTR, 34);
  SlaveRTU1.saveFloat(vADS1115_A3f, FLPROG_HOLDING_REGISTR, 36);   
};
//=================================================================================================
//                6.Запись в таблицу Holding Registers медленных float
//=================================================================================================
if(RT_HW_Base.shed.slow.num==2){
  SlaveRTU1.saveFloat(vAHTxx_Temp, FLPROG_HOLDING_REGISTR, 20);
  SlaveRTU1.saveFloat(vAHTxx_Hum,  FLPROG_HOLDING_REGISTR, 22);
  SlaveRTU1.saveFloat(vSHT3x_Temp, FLPROG_HOLDING_REGISTR, 24);
  SlaveRTU1.saveFloat(vSHT3x_Hum,  FLPROG_HOLDING_REGISTR, 26);
  SlaveRTU1.saveFloat(18.23,       FLPROG_HOLDING_REGISTR, 28);  //--DS1820;     
};
//=================================================================================================
//                7.Чтение из таблицу Holding Registers медленных int16
//=================================================================================================
if(RT_HW_Base.shed.slow.num==2){
  rg0=SlaveRTU1.readInteger(FLPROG_HOLDING_REGISTR, 40);    
};
//=================================================================================================
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#endif
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
