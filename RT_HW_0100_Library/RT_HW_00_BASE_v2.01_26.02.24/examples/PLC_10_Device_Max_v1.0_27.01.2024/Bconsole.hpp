//=================================================================================================
//                                  1.Вывод на консоль заголовка
//=================================================================================================
void consoleHead(){
RT_HW_Base.consoleCR(3); 
//-------------------------------------------------------------------------------------------------
RT_HW_Base.consoleHead(String(F("Board_70_Device_Max_v1.0_26.01.2024: ТЕСТИРОВАНИЕ УСТРОЙСТВ)")),'='); 
RT_HW_Base.consoleHead(String(F("Основные параметры")),'-');    RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleBoardGeneral();   
RT_HW_Base.consoleHead(String(F("Дополнительные параметры")));  RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleBoardAdd(); 
RT_HW_Base.consoleHead(String(F("Параметры диспетчера задач")));RT_HW_Base.consoleShedulerParameters();
//RT_HW_Base.consoleHead(String(F("PGM массивы")));             RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleFromPGM();
//RT_HW_Base.consoleHead(String(F(Доступные пины")));           RT_HW_Base.mess.modePin='A'; RT_HW_Base.consolePinsAll();        
RT_HW_Base.consoleHead(String(F("Интерфейсы")));                RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleInterface(); 
RT_HW_Base.consoleHead(String(F("Системные и тестовые пины. Пины cs")));  
                                                                RT_HW_Base.mess.modePin='T'; RT_HW_Base.consolePinsSystem(); 
                                                                RT_HW_Base.consolePinsTest(); RT_HW_Base.consolePinsCS(); 
RT_HW_Base.consoleHead(String(F("Устройства на UART")));        RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleNumUART(); 
//------------------------------------------------------------------------------------------------ 
#if defined(RT_HW_TEST_PERMIT_PLC_RP_55)
RT_HW_Base.consoleHead(String(F("ПАРАМЕТРЫ ИСПОЛЬЗУЕМЫЕ В ТЕСТЕ ПЛК RP2040_5.5")));
RT_HW_Base.consoleVar(String(F("SPI0->cs")));}
RT_HW_Base.consoleTest(String(F(" 595PLC")),  cs595PLC,  ';','P');}
RT_HW_Base.consoleTest(String(F(" 74HC165")), cs165PLC, ';','P');}
RT_HW_Base.consoleTest(String(F(" Ethernet")),csEthernet,';','P');}
RT_HW_Base.consoleTest(String(F(" CAN")),     csCAN,     ';','P');}
RT_HW_Base.consoleTest(String(F(" TFT")),     csTFT,     ';','P');}
RT_HW_Base.consoleCR(); 
RT_HW_Base.consoleTest(String(F("TFT->cs,DC,Led")),     csTFT,     ';','P');} 
if(uartModbusMaster !=255){RT_HW_Base.consoleTest(String(F(" UART ModBus Master")),uartModbusMaster, 'E','U');}
if(uartModbusSlave  !=255){RT_HW_Base.consoleTest(String(F(" UART ModBus Slave")), uartModbusSlave,  'E','U');} 
if(uartNextion      !=255){RT_HW_Base.consoleTest(String(F(" UART Nextion")),      uartNextion,      'E','U');}  
if(uartWiFi         !=255){RT_HW_Base.consoleTest(String(F(" UART Wi=Fi")),        uartWiFi,         'E','U');}
RT_HW_Base.consoleCR();  
#endif                    
//------------------------------------------------------------------------------------------------
RT_HW_Base.consoleHead(String(F("Scan i2c")));             RT_HW_Base.mess.modePin='T'; RT_HW_Base.i2cScanBus(0);   
RT_HW_Base.consoleLine('+'); 
};
