//=================================================================================================
//                                  2.Heading console output
//=================================================================================================
void consoleHead(){
  RT_HW_Base.consoleCR(3);
  RT_HW_Base.consoleHead(String(F("Test Board №4(Small Device v.1.2 21.09.2023)")),'='); 
  RT_HW_Base.consoleHead(String(F("Main parameters")),'-');  RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleBoardGeneral();   
  RT_HW_Base.consoleHead(String(F("Add parameters")));       RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleBoardAdd(); 
  RT_HW_Base.consoleHead(String(F("Task parameters")));      RT_HW_Base.consoleShedulerParameters();
//RT_HW_Base.consoleHead(String(F("PGM array")));            RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleFromPGM();
  RT_HW_Base.consoleHead(String(F("Available pins")));       RT_HW_Base.mess.modePin='A'; RT_HW_Base.consolePinsAll();        
  RT_HW_Base.consoleHead(String(F("Interface")));            RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleInterface(); 
  RT_HW_Base.consoleHead(String(F("System,test,cs pins")));  RT_HW_Base.mess.modePin='T'; RT_HW_Base.consolePinsSystem(); RT_HW_Base.consolePinsTest(); RT_HW_Base.consolePinsCS(); 
  RT_HW_Base.consoleVar (String(F("SPI cs-->")));            RT_HW_Base.mess.modePin='T';
  RT_HW_Base.consoleTest(String(F(" cs 74HC595")), cs74HC595, ';','P');
  RT_HW_Base.consoleTest(String(F(" cs 74HC165")), cs74HC165, ';','P');
  RT_HW_Base.consoleTest(String(F(" cs DM13C")),   csDM13C,   ';','P');
  RT_HW_Base.consoleTest(String(F(" cs MCP23S17")),csMCP23S17,';','P');
  RT_HW_Base.consoleCR();
  RT_HW_Base.consoleHead(String(F("Scan i2c")));             RT_HW_Base.mess.modePin='T'; RT_HW_Base.i2cScanBus(0);   
  RT_HW_Base.consoleLine('+'); 
};
