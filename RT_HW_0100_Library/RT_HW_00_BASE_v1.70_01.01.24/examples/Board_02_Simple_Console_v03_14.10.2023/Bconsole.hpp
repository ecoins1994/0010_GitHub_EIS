//=================================================================================================
//                                  1.Вывод на консоль параметров контроллера
//=================================================================================================
void consoleHead(){
  RT_HW_Base.consoleCR(3);
  RT_HW_Base.consoleHead(String(F("BASIC TEST №2(Вывод на консоль)")),'='); 
  RT_HW_Base.consoleHead(String(F("Main parameters")),'-'); RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleBoardGeneral();   
//RT_HW_Base.consoleTest(String(F("FLPROG->Code CORE")),(uint8_t)FLPROG_CORE_CODE,';');
//RT_HW_Base.consoleTest(String(F(" Name CORE")),(String)FLPROG_CORE_NAME);
  RT_HW_Base.consoleHead(String(F("Add parameters")));      RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleBoardAdd(); 
  RT_HW_Base.consoleHead(String(F("Task parameters")));     RT_HW_Base.consoleShedulerParameters();
//RT_HW_Base.consoleHead(String(F("PGM array")));           RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleFromPGM();
  RT_HW_Base.consoleHead(String(F("Available pins")));      RT_HW_Base.mess.modePin='A'; RT_HW_Base.consolePinsAll();        
  RT_HW_Base.consoleHead(String(F("Interface")));           RT_HW_Base.mess.modePin='T'; RT_HW_Base.consoleInterface(); 
  RT_HW_Base.consoleHead(String(F("System & test pins")));  RT_HW_Base.mess.modePin='T'; RT_HW_Base.consolePinsSystem(); RT_HW_Base.consolePinsTest();  
//RT_HW_Base.consoleHead(String(F("Scan i2c")));            RT_HW_Base.mess.modePin='T'; RT_HW_Base.i2cScanBus(0);   
  RT_HW_Base.consoleLine('+'); 
};
//=================================================================================================
//                                  2.Периодический вывод на консоль ADC,"Кнопки" 
//                                    + Быстродействие и Время работы  
//=================================================================================================
uint8_t cnsCnt=0, cnsADC=0, first=0, vAgoButton=0;
uint16_t vAgoADC=0;
//-------------------------------------------------------------------------------------------------
void consoleVar(){
if(cnsCnt++>30)           {cnsCnt=1;}
if(vAgoButton!=vButton)   {cnsCnt=1;}
if(++cnsADC>5){cnsADC=0; if(vAgoADC!=vADCF) {cnsCnt=1;}}
if(first==0)  {if(vSpeedMCU>0)     {first=1; cnsCnt=1;}}
if(cnsCnt==1){vAgoButton=vButton; vAgoADC=vADCF; cnsADC=0;
           RT_HW_Base.consoleTest(String(F("Button")),(uint8_t)vButton,';');
           RT_HW_Base.consoleVar (String(F(" ADC=")));     RT_HW_Base.consoleVar(vADCF,';',5,'U');
           RT_HW_Base.consoleVar (String(F(" Speed/1000->")));           
           RT_HW_Base.consoleVar (String(F(" CORE0=")));   RT_HW_Base.consoleVar(vSpeedSmall,';',5,'U');     
           RT_HW_Base.consoleVar (String(F(" CORE1=")));   RT_HW_Base.consoleVar(vspeedSmall,';',5,'U'); 
           RT_HW_Base.consoleTest(String(F(" motoSec")),vMotorSec,'E');}                      
};
//=================================================================================================
