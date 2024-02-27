//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  #if defined(RT_HW_TEST_PERMIT_MB_MASTER_RTU)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
//                              Modbus MASTER RTU1
//================================================================================================= 
//                                1.Настройка и управление Modbus Master RTU1
//=================================================================================================
if(RT_HW_Base.shed.frdm.num==10){
if(MbMasterRTU1_custom==0){                       //--Однократные действия
   MbMasterRTU1_custom=1;
   MasterRTU1.setUart(MbMasterRTU1_numUART);      //--Установка номера UART=1; 
 //MasterRTU1.setUart(1);                         //--Установка       номера UART RTU Slave Master;
   MasterRTU1.setSpeedUart(FLPROG_SPEED_115200);  //--Установка скорости                   [default=9600];
   MasterRTU1.setDataBitUart(8);                  //--Установка кол-ва бит данных (5,7,8)  [default=8];
   MasterRTU1.setStopBitUart(1);                  //--Установка количество стоп-бит(0,1,2) [default=1];
   MasterRTU1.setParityUart(0);                   //--Устан.четности:0=NONE, 1=EVEN, 2=ODD [default=0]; 
//-------------------------------------------------------------------------------------------------
//        1.2.Настройка параметров Slave 1  с устанавливаемым адресом на шине Modbus ID=2
//------------------------------------------------------------------------------------------------  
   MasterRTU1.setSlaveAddress(0, 1);              //--Установка Slave(индекс слейва в мастере, задаваемый адрес).
   MasterRTU1.setPollingPeriod(1, 1000);          //--Slave ID=1, период=1000ms;
   MasterRTU1.setTimeOutTime  (1, 1000);          //--Slave ID=1, период=1000ms;
   MasterRTU1.configDataTable( 1, FLPROG_HOLDING_REGISTR, 50);  //--Описание таблицы Slave;
//-------------------------------------------------------------------------------------------------
//        1.2.Настройка параметров Slave 1  с устанавливаемым адресом на шине Modbus ID=2
//------------------------------------------------------------------------------------------------
   MasterRTU1.setSlaveAddress (1, 2);      //--Для Slave с индексом  0  устанавливатся адрес(ID)=2. 
                                            //  Далее все работы со слейвом ведутся по адресу слейва; 
   MasterRTU1.setPollingPeriod(2, 1000);   //--Период опроса; 
   MasterRTU1.setTimeOutTime  (2, 1000);   //--Тайм-аут ответа; 
   MasterRTU1.configDataTable (2, FLPROG_HOLDING_REGISTR,20); //--Таблица на 20 Holding регистра;
//-------------------------------------------------------------------------------------------------  
} //--END if(MbMasterRTU1_custom==0)  
//------------------------------------------------------------------------------------------------
    MasterRTU1.pool();
} 
//================================================================================================= 
//                2.Запись в Slave c ID=1 в регистры HOLDING 1000ms
//=================================================================================================
if(RT_HW_Base.shed.slow.num==2){
  MasterRTU1.saveInteger(1,counter,     FLPROG_HOLDING_REGISTR, 0); //--Счетчик;
  MasterRTU1.saveInteger(1,vADCF,       FLPROG_HOLDING_REGISTR, 1); //--ADC;
  MasterRTU1.saveInteger(1,vSR04_Len,   FLPROG_HOLDING_REGISTR, 2); //--HC-SR04;
  MasterRTU1.saveInteger(1,vBH1750_Lux, FLPROG_HOLDING_REGISTR, 3);
  MasterRTU1.saveInteger(1,pinDIN,      FLPROG_HOLDING_REGISTR, 4);
  MasterRTU1.saveInteger(1,flagSystem,  FLPROG_HOLDING_REGISTR, 5); 
  MasterRTU1.saveInteger(1,flagDevice,  FLPROG_HOLDING_REGISTR, 6);
  MasterRTU1.saveInteger(1,RT_HW_Base.unixID.hours,   FLPROG_HOLDING_REGISTR, 7);   
  MasterRTU1.saveInteger(1,RT_HW_Base.unixID.minutes, FLPROG_HOLDING_REGISTR, 8); 
  MasterRTU1.saveInteger(1,RT_HW_Base.unixID.seconds, FLPROG_HOLDING_REGISTR, 9); 
}
//================================================================================================= 
//                2.Запись в Slave c ID=2 в регистры HOLDING 1000ms
//=================================================================================================
if(RT_HW_Base.shed.slow.num==3){
  MasterRTU1.saveFloat  (2,vAHTxx_Temp, FLPROG_HOLDING_REGISTR, 0); //--;
  MasterRTU1.saveFloat  (2,vAHTxx_Hum,  FLPROG_HOLDING_REGISTR, 2); //--;
  MasterRTU1.saveFloat  (2,vSHT3x_Temp, FLPROG_HOLDING_REGISTR, 4); //--;
  MasterRTU1.saveFloat  (2,vSHT3x_Hum,  FLPROG_HOLDING_REGISTR, 6);
  MasterRTU1.saveFloat  (2,vDS1820_Temp, FLPROG_HOLDING_REGISTR, 8);
}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 #endif
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
