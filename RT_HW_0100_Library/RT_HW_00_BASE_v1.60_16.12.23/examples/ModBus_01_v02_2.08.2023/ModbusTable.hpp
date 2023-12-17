//#################################################################################################
//                              Создание объектов для MODBUS
//  Секция: Declare
//################################################################################################
//=================================================================================================
//                                  1.Таблицы доступа Master->SLAVE 1
//=================================================================================================
//-------------------------------------------------------------------------------------------------
//                          1.1.HOLDING REGISTERS, 8 регистров;
//-------------------------------------------------------------------------------------------------
int  tableA_4_1[8] = {0, 1, 2, 3, 4, 5, 6, 7};   //--Адреса;
int  table_4_1[8];                               //--Данные;
bool tableS_4_1[8] = {0, 0, 0, 0, 0, 0, 0, 0};   //--Флаги запуска;
ModbusWorldTable Holder1(HOLDING_REGISTR, table_4_1, tableA_4_1, tableS_4_1, 8);
//-------------------------------------------------------------------------------------------------
//                          1.2.INPUT REGISTERS, 8 регистров;
//-------------------------------------------------------------------------------------------------
int tableA_3_1[8] = {0, 1, 2, 3, 4, 5, 6, 7};
int table_3_1[8];
ModbusWorldTable InputRegistr1(INPUT_REGISTR, table_3_1, tableA_3_1, 8);
//-------------------------------------------------------------------------------------------------
//                          1.3.COIL, 2 регистра;
//-------------------------------------------------------------------------------------------------
bool table_0_1[2];
int tableA_0_1[2] = {0, 1};
bool tableS_0_1[2] = {0, 0};
ModbusBoolTable Coil1(COIL, table_0_1, tableA_0_1, tableS_0_1, 2);
//-------------------------------------------------------------------------------------------------
//                          1.4.DISCRETE INPUT, 2 регистра;
//-------------------------------------------------------------------------------------------------
bool table_1_1[2];
int tableA_1_1[2] = {0, 1};
ModbusBoolTable DiscreteInput1(DISCRETE_INPUT, table_1_1, tableA_1_1, 2);

//=================================================================================================
//                                  2.Таблицы доступа Master->SLAVE 2
//=================================================================================================
//-------------------------------------------------------------------------------------------------
//                          2.1.HOLDING REGISTERS, 8 регистров;
//-------------------------------------------------------------------------------------------------
int  table_4_2[8];
int  tableA_4_2[8] = {0, 1, 2, 3, 4, 5, 6, 7};
bool tableS_4_2[8] = {0, 0, 0, 0, 0, 0, 0, 0};
ModbusWorldTable Holder2(HOLDING_REGISTR, table_4_2, tableA_4_2, tableS_4_2, 8);
//-------------------------------------------------------------------------------------------------
//                          2.2.INPUT REGISTERS, 8 регистров;
//-------------------------------------------------------------------------------------------------
int table_3_2[8];
int tableA_3_2[8] = {0, 1, 2, 3, 4, 5, 6, 7};
ModbusWorldTable InputRegistr2(INPUT_REGISTR, table_3_2, tableA_3_2, 8);
//-------------------------------------------------------------------------------------------------
//                          2.3.COIL, 2 регистра;
//-------------------------------------------------------------------------------------------------
bool table_0_2[2];
int tableA_0_2[2] = {0, 1};
bool tableS_0_2[2] = {0, 0};
ModbusBoolTable Coil2(COIL, table_0_2, tableA_0_2, tableS_0_2, 2);
//-------------------------------------------------------------------------------------------------
//                          2.4.DISCRETE INPUT, 2 регистра;
//-------------------------------------------------------------------------------------------------
bool table_1_2[2];
int tableA_1_2[2] = {0, 1};
ModbusBoolTable DiscreteInput2(DISCRETE_INPUT, table_1_2, tableA_1_2, 2);

//=================================================================================================
//                        3. Создание массива SLAVE для MASTER
//=================================================================================================
ModbusSlaveInMaster Master1SlavesTable[2];
//=================================================================================================
//                        4. Создание объект Master (2 Slave)
//=================================================================================================
ModbusMasterRTU Master1(Master1SlavesTable, 1);
//=================================================================================================
//                        5. Создание коммуникационного канала
//=================================================================================================
//FLProgUart RtuDevice(0);
  FLProgUart RtuDevice(1);
//FLProgUart RtuDevice(2);

//================================================================================================
