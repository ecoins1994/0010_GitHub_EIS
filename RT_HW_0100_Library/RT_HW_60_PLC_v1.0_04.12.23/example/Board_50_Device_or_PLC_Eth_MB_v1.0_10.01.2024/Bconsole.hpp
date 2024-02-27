//=================================================================================================
//                                  2.Heading console output
//=================================================================================================
void consoleHead(){
RT_HW_Base.consoleCR(3); 
RT_HW_Base.consoleHead(String(F("BASIC TEST №50(Расширенные устройства или ПЛК v.1.0 10.01.2023)")),'='); 
RT_HW_Base.consoleHead(String(F("Main parameters")),'-');  RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleBoardGeneral();   
RT_HW_Base.consoleHead(String(F("Add parameters")));       RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleBoardAdd(); 
RT_HW_Base.consoleHead(String(F("Task parameters")));      RT_HW_Base.consoleShedulerParameters();
//RT_HW_Base.consoleHead(String(F("PGM array")));            RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleFromPGM();
//RT_HW_Base.consoleHead(String(F("Available pins")));       RT_HW_Base.mess.modePin='A'; RT_HW_Base.consolePinsAll();        
RT_HW_Base.consoleHead(String(F("Interface")));            RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleInterface(); 
RT_HW_Base.consoleHead(String(F("System,test,cs pins")));  RT_HW_Base.mess.modePin='T'; RT_HW_Base.consolePinsSystem(); RT_HW_Base.consolePinsTest(); RT_HW_Base.consolePinsCS(); 
RT_HW_Base.consoleVar (String(F("SPI cs-->")));  RT_HW_Base.mess.modePin='T';
RT_HW_Base.consoleHead(String(F("Test num UART")));        RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleNumUART(); 
//------------------------------------------------------------------------------------------------
RT_HW_Base.consoleHead(String(F("ПАРАМЕТРЫ ИСПОЛЬЗУЕМЫЕ В ТЕСТЕ"))); 
#if defined(RT_HW_TEST_PERMIT_PLC_RP_55)
RT_HW_Base.consoleHead(String(F("     PLC Raspberry Pi Pico v.5.5     ")),'+'); 
#endif
if(cs74HC595 !=255){RT_HW_Base.consoleTest(String(F(" 74HC595")), cs74HC595, ';','P');}
if(cs595PLC  !=255){RT_HW_Base.consoleTest(String(F(" 595PLC")),  cs595PLC,  ';','P');}
if(cs74HC165 !=255){RT_HW_Base.consoleTest(String(F(" 74HC165")), cs74HC165, ';','P');}
if(csEthernet!=255){RT_HW_Base.consoleTest(String(F(" Ethernet")),csEthernet,';','P');}
if(csCAN     !=255){RT_HW_Base.consoleTest(String(F(" CAN")),     csCAN,     ';','P');}
if(csTFT     !=255){RT_HW_Base.consoleTest(String(F(" TFT")),     csTFT,     ';','P');}
if(csDM13C   !=255){RT_HW_Base.consoleTest(String(F(" DM13C")),   csDM13C,   ';','P');}
if(csMAX6675 !=255){RT_HW_Base.consoleTest(String(F(" MAX6675")), csMAX6675, ';','P');}  
if(uartModbusMaster !=255){RT_HW_Base.consoleTest(String(F(" UART ModBus Master")),uartModbusMaster, 'E','U');}
if(uartModbusSlave  !=255){RT_HW_Base.consoleTest(String(F(" UART ModBus Slave")), uartModbusSlave,  'E','U');} 
if(uartNextion      !=255){RT_HW_Base.consoleTest(String(F(" UART Nextion")),      uartNextion,      'E','U');}  
if(uartWiFi         !=255){RT_HW_Base.consoleTest(String(F(" UART Wi=Fi")),        uartWiFi,         'E','U');}
RT_HW_Base.consoleCR();                      
//------------------------------------------------------------------------------------------------
RT_HW_Base.consoleHead(String(F("Scan i2c")));             RT_HW_Base.mess.modePin='T'; RT_HW_Base.i2cScanBus(0);   
RT_HW_Base.consoleLine('+'); 
};
