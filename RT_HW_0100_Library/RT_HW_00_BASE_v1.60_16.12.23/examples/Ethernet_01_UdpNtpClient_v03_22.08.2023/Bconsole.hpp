//=================================================================================================
//                                  2.Heading console output
//=================================================================================================
void consoleHead(){
  RT_HW_Base.consoleCR(3);
  RT_HW_Base.consoleHead(String(F("BASIC TEST №5(Median Device v.05 06.07.2023)")),'='); 
  RT_HW_Base.consoleHead(String(F("Main parameters")),'-'); RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleBoardGeneral();   
//RT_HW_Base.consoleHead(String(F("Add parameters")));      RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleBoardAdd(); 
//RT_HW_Base.consoleHead(String(F("Task parameters")));     RT_HW_Base.consoleShedulerParameters();
//RT_HW_Base.consoleHead(String(F("PGM array")));           RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleFromPGM();
//RT_HW_Base.consoleHead(String(F("Available pins")));      RT_HW_Base.mess.modePin='A'; RT_HW_Base.consolePinsAll();        
  RT_HW_Base.consoleHead(String(F("Interface")));           RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleInterface(); 
  RT_HW_Base.consoleHead(String(F("System,test,cs pins"))); RT_HW_Base.mess.modePin='T'; RT_HW_Base.consolePinsSystem(); 
                                                            RT_HW_Base.consolePinsTest(); RT_HW_Base.consolePinsCS(); 
  RT_HW_Base.consoleHead(String(F("Test num UART")));       RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleNumUART();   
  RT_HW_Base.consoleHead(String(F("Scan i2c")));            RT_HW_Base.mess.modePin='T'; RT_HW_Base.i2cScanBus(0);   
  RT_HW_Base.consoleHead(String(F("Параметры сенсоров и расширителей")));  RT_HW_Base.mess.modePin='A';   
  RT_HW_Base.consoleTest(String(F("cs 74HC595")),cs74HC595,';','P');  
  RT_HW_Base.consoleTest(String(F(" cs DM13C")),  csDM13C,';','P');
  RT_HW_Base.consoleTest(String(F(" cs MAX6675")),csMAX6675,';','P');
  RT_HW_Base.consoleCR();
  RT_HW_Base.consoleTest(String(F("adr ADS1115")),i2cAdrADS1115,';','A');  
  RT_HW_Base.consoleTest(String(F(" adr PCF8575")),i2cAdrPCF8575,';','A'); 
  RT_HW_Base.consoleCR();
  RT_HW_Base.consoleHead(String(F("Параметры Ethernet")));  RT_HW_Base.mess.modePin='A'; 
  RT_HW_Base.consoleTest(String(F("cs Ethernet")),csEthernet,';','P');
  RT_HW_Base.consoleTest(String(F(" Имя host")),String(host),';');  RT_HW_Base.consoleTest(String(F(" port")), port,'E'); 
  RT_HW_Base.consoleLine('+'); 
};
