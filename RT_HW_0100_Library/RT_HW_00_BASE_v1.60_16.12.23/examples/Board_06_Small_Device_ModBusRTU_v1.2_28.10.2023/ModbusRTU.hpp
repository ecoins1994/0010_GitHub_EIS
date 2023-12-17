//=================================================================================================
//      Доступные функции:
//         void saveLong(long value, byte table, int startAddres);
//         void saveUnsignedLong(unsigned long value, byte table, int startAddres);
//         void saveFloat(float value, byte table, int startAddres);
//         void saveInteger(int value, byte table, int startAddres);
//         void saveByte(byte value, byte table, int startAddres);
//         void saveBool(bool value, byte table, int startAddres);
//         byte readByte(byte table, int startAddres);
//         int readInteger(byte table, int startAddres);
//         float readFloat(byte table, int startAddres);
//         long readLong(byte table, int startAddres);
//         unsigned long readUnsignedLong(byte table, int startAddres);
//         bool readBool(byte table, int startAddres);
//================================================================================================= 
  uint8_t initMbRTU=0;
  ModbusSlaveRTU SlaveRTU0(0);    //--Создание объекта ModbusSlaveRTU на нулевом UART;
  int TableAddrRegDI[] = { 8,  9, 10, 11, 12, 14, 15, 16, 
                          17, 18, 19, 20, 21, 22, 23, 24, 
                          25, 26, 27, 28, 29, 30, 31, 32};          //--Таблица адресов регистров DI;
  int lastError;
//=================================================================================================
//
//=================================================================================================
void createMbRTU0(){
  if(initMbRTU){return;} initMbRTU=1;                                     //--Проверка для одноразовой настройки параметров;
  SlaveRTU0.configDataTable(FLPROG_HOLDING_REGISTR, 24);                  //--
  SlaveRTU0.configDataTable(FLPROG_INPUT_REGISTR,   24);                  //--
  SlaveRTU0.configDataTable(FLPROG_COIL,            24, 5);               //--
  SlaveRTU0.setDataTable   (FLPROG_DISCRETE_INPUT,  24, TableAddrRegDI);  //--Настройка таблицы адресов;
  SlaveRTU0.setSlaveAddress(10); //--Установка адреса Slave=10;   
 }
