//=================================================================================================
//                                  1.Вывод на консоль параметров контроллера
//=================================================================================================
uint8_t bus=0;                                          //--рабочая переменная;
//-------------------------------------------------------------------------------------------------
void consoleHead(){
  RT_HW_Base.consoleHead(String(F("BASIC TEST №3(scan i2c)")),'=');
  RT_HW_Base.consoleHead(String(F("Main parameters")));      RT_HW_Base.mess.modePin='T';  RT_HW_Base.consoleBoardGeneral();           
  RT_HW_Base.consoleHead(String(F("Add parameters")));       RT_HW_Base.mess.modePin='T';  RT_HW_Base.consoleBoardAdd(); 
  RT_HW_Base.consoleHead(String(F("Task parameters")));      RT_HW_Base.consoleShedulerParameters();
  RT_HW_Base.consoleHead(String(F("Available pins")));       RT_HW_Base.mess.modePin='A';  RT_HW_Base.consolePinsAll();    
  RT_HW_Base.consoleHead(String(F("Interface")));            RT_HW_Base.mess.modePin='T';  RT_HW_Base.consoleInterface(); 
  RT_HW_Base.consoleHead(String(F("System,test,cs pins")));  RT_HW_Base.mess.modePin='T';  RT_HW_Base.consolePinsSystem(); 
                                                             RT_HW_Base.consolePinsTest(); RT_HW_Base.consolePinsCS();   
  RT_HW_Base.consoleLine('-');
  for(bus=0; bus<3; bus++){
  if(RT_HW_Base.i2cCheckBus(bus)){RT_HW_Base.consoleTest(String(F("i2c ok bus")),bus);}
  RT_HW_Base.i2cHeadInterface(bus);
  RT_HW_Base.consoleLine('+');
  }
  RT_HW_Base.consoleHead(String(F("Scan i2c")));             RT_HW_Base.mess.modePin='T';  RT_HW_Base.i2cScanBus(0);   
  RT_HW_Base.consoleLine('+');  
};
//=================================================================================================
