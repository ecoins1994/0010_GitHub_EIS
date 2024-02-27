//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// 								1. API Console - Сканирование устройств
// 							         
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//									1. Сканирование 2c c 
//=================================================================================================
uint8_t i2cScanBus(RT_HW_STRUCT_I2C_DEV &id, uint8_t bus=0, uint8_t channel=0, uint32_t speed=0)
{							
#if defined(RT_HW_LINK_I2C)
if(!i2cCheckBus(bus)){return 0;}	//--Выход, если шина недоступна;
id.custom=0; i2cSetParam(id,255,bus,speed); id.channel=channel; id.agoChannel=255;
i2cInitDevice(id); if(!id.link){return 1;}
//-------------------------------------------------------------------------------------------------         
consoleBegin(); //if(!console.ok){return 1;}	//--Setting up the console with default options and waiting for it to be ready;
mess.alig='R'; mess.blank=' ';  mess.modePin='T'; 
consoleVar(String(F("I2C")));           consoleVar(bus,'~');
consoleVar(String(F(" bus=")));         consoleVar(bus,'~'); 
if((id.expander) && (id.channel>0) && (id.channel<=8)){consoleVar(String(F(" channel="))); consoleVar(id.channel,'~');}
consoleVar(String(F(": scan->")));
if(id.status==0) {consoleVar(String(F("No init")),'E'); 	return 1;} 
if(id.status==2) {consoleVar(String(F(" Slave")),'E');  	return 1;} 
if(id.status!=1) {consoleVar(String(F(" No Master")),'E');  return 1;}
id.idx=1; id.codeErr=0; id.cnt=0;
//-------------------------------------------------------------------------------------------------
do{if(id.idx>127){break;}
id.adr=id.idx; i2cFindAdr(id); 
if((id.codeErr==0) && (id.adr!=id.expander)){if(id.cnt>0){if((mess.modeAdr=='A') && (id.cnt==10)){consoleCR();}
					            else if((mess.modeAdr=='H') && (id.cnt==14)){consoleCR();}
					            else if((mess.modeAdr=='D') && (id.cnt==16)){consoleCR();}
						        else                                        {consoleChar(',');}}                                   
id.cnt++; consoleVar(id.idx,'~',0,'A'); }
id.idx++;}while(1);
if(id.cnt>0){consoleChar(';');} 
consoleTest(String(F(" qnt")),id.cnt,'E'); 	
//-------------------------------------------------------------------------------------------------
#endif
return 1;
};
//=================================================================================================
//							5.3x. Сканирование i2c
//=================================================================================================
uint8_t i2cScanBus(uint8_t bus=0, uint32_t speed=0){							
#if defined(RT_HW_LINK_I2C)
  RT_HW_STRUCT_I2C_DEV dvi2c;
//------------------------------------------------------------------------------------------------
//							
//------------------------------------------------------------------------------------------------
  consoleBegin(); 
  if(!console.ok){return 1;}	//--Setting up the console with default options and waiting for it to be ready;
//-------------------------------------------------------
  if(!i2cCheckBus(bus)){consoleVar(String(F("I2C"))); consoleVar(bus,'~'); consoleVar(String(F(" No Bus")),'E'); return 0;}	//--Выход, если шина недоступна;
  dvi2c.custom=0;
  if(dvi2c.custom==0){i2cSetParam(dvi2c,255,bus,speed);} 
  i2cInitDevice(dvi2c);
//-------------------------------------------------------------------------------------------------         

  mess.alig='R'; mess.blank=' ';  mess.modePin='T'; 
consoleVar(String(F("I2C")));           consoleVar(bus,'~');
consoleVar(String(F(" bus=")));         consoleVar(bus,':'); 
consoleVar(String(F(" scan->")));
if(dvi2c.status==0) {consoleVar(String(F("No init")),'E'); return 1;} 
if(dvi2c.status==2) {consoleVar(String(F(" Slave")),'E');  return 1;} 
if(dvi2c.status!=1) {consoleVar(String(F(" No Master")),'E');   return 1;}
dvi2c.idx=1;   dvi2c.codeErr=0; dvi2c.cnt=0;
//-------------------------------------------------------------------------------------------------
do{if(dvi2c.idx>127){break;}
dvi2c.adr=dvi2c.idx; i2cFindAdr(dvi2c); 
if(dvi2c.codeErr==0){if(dvi2c.cnt>0){if((mess.modeAdr=='A') && (dvi2c.cnt==10)){consoleCR();}
					            else if((mess.modeAdr=='H') && (dvi2c.cnt==14)){consoleCR();}
					            else if((mess.modeAdr=='D') && (dvi2c.cnt==16)){consoleCR();}
						        else                                           {consoleChar(',');}}                                   
dvi2c.cnt++; consoleVar(dvi2c.idx,'~',0,'A'); }
dvi2c.idx++;}while(1);
if(dvi2c.cnt>0){consoleChar(';');} 
consoleTest(String(F(" qnt")),dvi2c.cnt,'E'); 	
//-------------------------------------------------------------------------------------------------
#endif
return 1;
};
