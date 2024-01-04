//=================================================================================================
//                        1. Настройка коммуникационного канала
//=================================================================================================
void mbUartInit(uint8_t numModBus, uint32_t speed, uint8_t num){
RT_HW_Base.uartSetSpeed(speed,num); //--Установка скорости;
RT_HW_Base.uartBegin(num);          //--Настройка UART;
Master1.setUart(&RtuDevice);     //--Настройка UART в ModBus (выглядит избыточно....);
};
//=================================================================================================
//                        2. Настройка Modbus1
//=================================================================================================
void mbSlaveInit(uint8_t numModBus, uint8_t slaveID, uint16_t period=1000, uint16_t timeOut=1000){
Master1SlavesTable[0].setSlaveAddress(1);     //--Установка адреса(ID) SLAVE 1;
Master1SlavesTable[0].setPollingPeriod(1000); //--Установка периода опроса в ms(можно менять в любой момент времени);
Master1SlavesTable[0].setTimeOutTime(1000);   //--Установка тайм-аута SLAVE[default=1000ms](можно менять в любой момент времени);
};
//=================================================================================================
//                        3. Настройка порта (default 9600 8N1)
//   Параметры порта можно менять во время исполнения программы ???
//   FLPROG_SPEED_300,   FLPROG_SPEED_600,   FLPROG_SPEED_1200,  FLPROG_SPEED_2400,  FLPROG_SPEED_4800
//   FLPROG_SPEED_9600,  FLPROG_SPEED_14400, FLPROG_SPEED_19200, FLPROG_SPEED_28800, FLPROG_SPEED_38400
//   FLPROG_SPEED_57600, FLPROG_SPEED_115200
//=================================================================================================
void mbMasterInit(uint8_t numModBus=1){
//  Master1.setPortSpeed(FLPROG_SPEED_14400);
//  Master1.setPortSpeed(FLPROG_SPEED_9600);      //--
//  Master1.setPortDataBits(8);                   //--Задаем количество дата бит
//  Master1.setPortStopBits(2);                   //--Задаем количество стоп бит
//  Master1.setPortParity(2);                     //-Задаем четность - Значения 0 (NONE), 1 (EVEN), 2 (ODD)
  Master1.begin();                              //Инициализируем мастер
};
