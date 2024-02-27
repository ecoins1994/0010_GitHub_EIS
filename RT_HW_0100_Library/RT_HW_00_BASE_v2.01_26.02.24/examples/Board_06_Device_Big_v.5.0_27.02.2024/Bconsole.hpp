//=================================================================================================
//                                  1. Вывод на консоль параметров контроллера
//=================================================================================================
void consoleHead(){
  RT_HW_Base.consoleHead(String(F("Тест Board_05_Device_Average_v1.1")),'=');
  RT_HW_Base.consoleVar(String(F("Проект->")));                     RT_HW_Base.consoleVar(String(F(__FILE__)),'E');
  RT_HW_Base.consoleHead(String(F("Основные параметры")));          RT_HW_Base.mess.modePin='T';  RT_HW_Base.consoleBoardGeneral();           
//RT_HW_Base.consoleHead(String(F("Дополнительные параметры")));    RT_HW_Base.mess.modePin='T';  RT_HW_Base.consoleBoardAdd(); 
//RT_HW_Base.consoleHead(String(F("Параметры диспетчера задач")));  RT_HW_Base.consoleShedulerParameters();
//RT_HW_Base.consoleHead(String(F("Доступные пины")));              RT_HW_Base.mess.modePin='A';  RT_HW_Base.consolePinsAll();    
  RT_HW_Base.consoleHead(String(F("Интерфейсы")));                  RT_HW_Base.mess.modePin='T';  RT_HW_Base.consoleInterface(); 
  RT_HW_Base.consoleHead(String(F("Системные,тестовые,cs пины")));  RT_HW_Base.mess.modePin='T';  
  RT_HW_Base.consolePinsSystem(); RT_HW_Base.consolePinsTest();     RT_HW_Base.consolePinsCS(); 
  RT_HW_Base.consoleHead(String(F("Устройства на UART")));          RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleNumUART();    
//-------------------------------------------------------------------------------------------------
  RT_HW_Base.consoleHead(String(F("Ethernet")));
  RT_HW_Base.ethMacAdrToString(macAddr0); RT_HW_Base.consoleTest(String(F("MAC0")),RT_HW_Base.mess.str,';'); RT_HW_Base.consoleBlank(5); 
  RT_HW_Base.ethIpToString    (ethIP0);   RT_HW_Base.consoleTest(String(F("IP0")), RT_HW_Base.mess.str,'E'); 
  RT_HW_Base.ethMacAdrToString(macAddr1); RT_HW_Base.consoleTest(String(F("MAC1")),RT_HW_Base.mess.str,';'); RT_HW_Base.consoleBlank(5); 
  RT_HW_Base.ethIpToString    (ethIP1);   RT_HW_Base.consoleTest(String(F("IP1")), RT_HW_Base.mess.str,'E'); 
//-------------------------------------------------------------------------------------------------
  RT_HW_Base.consoleHead(String(F("Сканирование i2c(bus=0)")));     RT_HW_Base.mess.modeAdr='A';  
                                                                    RT_HW_Base.i2cScanBus(0);     
//-------------------------------------------------------------------------------------------------   
  RT_HW_Base.consoleLine('+');  
};
//=================================================================================================
