//=================================================================================================
//                                ФУНКЦИИ И ОБЪЕКТЫ MODBUS
//=================================================================================================
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                    1.Modbus MasterRTU
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//-------------------------------------------------------------------------------------------------
#if defined (RT_HW_TEST_PERMIT_ModbusMasterRTU) 
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  #include "flprogModbusRTU.h"      //++Подключение библиотеки  ModbusRTU(включает подключение RT_HW_BASE.h); 
  ModbusMasterRTU Master1(1, 2);    //--Создание Master: номер UART=1; кол-во Slave=2 (Slave 0,1);
  uint8_t customMbMaster=0; 
//=================================================================================================
//                            1.Настройка Master и Slave 0,1
//=================================================================================================
  void setParamMbMaster(){if(customMbMaster==0){    //==1.1.Установка параметров Ethernet                                   
//-------------------------------------------------------------------------------------------------
//                            1.1.Настройка параметров
//-------------------------------------------------------------------------------------------------     
      //Master1(1);                                 //--Здесь можно изменить номер UART; 
        
//-------------------------------------------------------------------------------------------------
//        Настройка параметров Slave 0  с устанавливаемым адресом на шине Modbus ID=4
//-------------------------------------------------------------------------------------------------
  Master1.setSlaveAddress (0, 4);                         //--Для Slave 0 адрес на шине ID=4;
  Master1.setPollingPeriod(1, 1000);                      //--Период опроса; 
  Master1.setTimeOutTime  (1, 1000);                      //--Тайм-аут ответа; 
  Master1.configDataTable (1, FLPROG_HOLDING_REGISTR,10); //--Таблица на 10 Holding регистра;
//-------------------------------------------------------------------------------------------------
//        Настройка параметров Slave 1  с устанавливаемым адресом на шине Modbus ID=8
//------------------------------------------------------------------------------------------------
  Master1.setSlaveAddress (1, 8);                         //--Для Slave 0 адрес на шине ID=1;
  Master1.setPollingPeriod(8, 1000);                      //--Период опроса; 
  Master1.setTimeOutTime  (8, 1000);                      //--Тайм-аут ответа; 
  Master1.configDataTable (8, FLPROG_HOLDING_REGISTR, 8); //--Таблица на 8 Holding регистра;         
//-------------------------------------------------------------------------------------------------
        customMbMaster=1; }}                        //--Установка "Настройка выполнена";
//-------------------------------------------------------------------------------------------------
  void  poolMbMaster(){Master1.pool();}

//  void directExpEth()  {ethExp.directExpEth(eth);   //==1.2.Управление Ethernet;
//     if(ethExp.freshStatus){ethIP=eth.localIP();}}; //      Сохранение IP адреса.
//  void checkDirExpEth(){ethExp.checkDirExpEth();}   //==1.3.Вывод номера текущего этапа(для тестирования программного обеспечения);
//  void messExpEth(uint8_t vPeriod=0){               //==1.4.Вывод диагностических сообщений (для тестирования оборудования);
//            ethExp.messExpEth(eth,vPeriod);}        //      Вывод на консоль;
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#else
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  void setParamMbMaster {;};                        //==1.1.Установка параметров ModbusMaster
  void poolMbMaster() {Master1.pool();}
//  void directExpEth()  {;};                        //==1.2.Управление Ethernet;
//  void checkDirExpEth() {;};                       //==1.3.Вывод номера текущего этапа(для тестирования программного обеспечения);
//  void messExpEth(){;};                            //==1.4.Вывод диагностических сообщений (для тестирования оборудования);
#endif
