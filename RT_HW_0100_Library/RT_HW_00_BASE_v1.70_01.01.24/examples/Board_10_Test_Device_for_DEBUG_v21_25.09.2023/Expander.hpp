//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                   1.Data EXPANDERS
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                                   1.2.Expander via i2c
//=================================================================================================
RT_HW_MCP4725_DEV  dvMCP4725;   RT_HW_STRUCT_SHED_TASK shMCP4725; 
RT_HW_MCP23x17_DEV dvMCP23x17;  RT_HW_STRUCT_SHED_TASK shMCP23x17in, shMCP23x17out;  uint8_t mcp23x17inA,mcp23x17inB;
RT_HW_PCF8575_DEV  dvPCF8575;   RT_HW_STRUCT_SHED_TASK shPCF8575in,  shPCF8575out;   uint8_t PCF8575inA, PCF8575inB;
RT_HW_ADS1115_DEV  dvADS1115;   RT_HW_STRUCT_SHED_TASK shADS1115;
//=================================================================================================
//                                   1.3.Expander via SPI,SPN
//=================================================================================================
RT_HW_74HC595_DEV dv74HC595;    RT_HW_STRUCT_SHED_TASK sh74HC595;  uint32_t vGenRun;
RT_HW_74HC595_DEV dv74HC595N;   RT_HW_STRUCT_SHED_TASK sh74HC595N; uint32_t vGenRunN;
RT_HW_74HC165_DEV dv74HC165;    RT_HW_STRUCT_SHED_TASK sh74HC165;  uint32_t v74HC165,  ago74HC165;
RT_HW_74HC165_DEV dv74HC165N;   RT_HW_STRUCT_SHED_TASK sh74HC165N; uint32_t v74HC165N, ago74HC165N;
//=================================================================================================

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                   0.3.Generators, counter
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
RT_HW_GENERATOR_EVENT_ID idGenRun;      RT_HW_COUNTER_ID idCntRun8;     uint8_t  vGenRun8=0;  //--For generator running "1" 0-8;
                                        RT_HW_COUNTER_ID idCntRun16;    uint16_t vGenRun16=0; //--For generator running "1" 0-16;
                                        RT_HW_COUNTER_ID idCntRun24;    uint32_t vGenRun24=0; //--For generator running "1" 0-24;
                                        RT_HW_COUNTER_ID idCntRun32;    uint32_t vGenRun32=0; //--For generator running "1" 0-32;
//-------------------------------------------------------------------------------------------------
RT_HW_GENERATOR_EVENT_ID idGenDAC;      RT_HW_COUNTER_ID idCntDAC;      uint16_t vGenDAC=0;                //--For generator 0-4095 DAC;
RT_HW_GENERATOR_EVENT_ID idGenA,idGenB; RT_HW_COUNTER_ID idCntA,idCntB; uint8_t  vCntA,vCntB,vGenA,vGenB;  //--For generator MCP23x17;
//=================================================================================================
void  genRun(void){
if(idCntRun8.reset) {RT_HW_Base.counterReset(idCntRun8,  8,0,1,1);}  //--init counter: Upper limit=8,   Down limit=0, Change step=1,   Initial value=0;
if(idCntRun16.reset){RT_HW_Base.counterReset(idCntRun16,16,0,1,1);}  //--init counter: Upper limit=16,  Down limit=0, Change step=1,   Initial value=0;
if(idCntRun24.reset){RT_HW_Base.counterReset(idCntRun24,24,0,1,1);}  //--init counter: Upper limit=24,  Down limit=0, Change step=1,   Initial value=0;
if(idCntRun32.reset){RT_HW_Base.counterReset(idCntRun32,32,0,1,1);}  //--init counter: Upper limit=32,  Down limit=0, Change step=1,   Initial value=0;
if(RT_HW_Base.generatorEvent(idGenRun,20)){
  vGenRun8= RT_HW_Base.dc8(RT_HW_Base.counterS(idCntRun8));
  vGenRun16=RT_HW_Base.dc16(RT_HW_Base.counterS(idCntRun16));
  vGenRun24=RT_HW_Base.dc24(RT_HW_Base.counterS(idCntRun24));
  vGenRun32=RT_HW_Base.dc32(RT_HW_Base.counterS(idCntRun32));
  }                                            
} //--Saw generator 100 ms;
//=================================================================================================
void genDAC(){         
if(idCntDAC.reset){RT_HW_Base.counterReset(idCntDAC,4095,0,10,0);}  //--init counter: Upper limit=4095, Down limit=0, Change step=10, Initial value=0;
if(RT_HW_Base.generatorEvent(idGenDAC,10)) {vGenDAC=RT_HW_Base.counterT(idCntDAC);}; //--Triangle generator 0-4095 for DAC,100 ms;
};
//=================================================================================================
void genMCP23x17(){         
if(idCntA.reset){RT_HW_Base.counterReset(idCntA,8,0,1,1);}   //--init counter: Upper limit=8,   Down limit=0, Change step=1,   Initial value=0;
if(idCntB.reset){RT_HW_Base.counterReset(idCntB,8,0,1,1);}   //--init counter: Upper limit=8,   Down limit=0, Change step=1,   Initial value=0;
if(RT_HW_Base.generatorEvent(idGenA,50)) {vCntA=RT_HW_Base.counterT(idCntA); vGenA=RT_HW_Base.dc8(vCntA);
                                          vCntB=RT_HW_Base.counterS(idCntB); vGenB=RT_HW_Base.dc8(vCntB);}
//------------------------------------------------------------------------------------------------
};
//=================================================================================================
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     1. I/O EXPANDERS via i2c
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                                     1.1.MCP4725.i2c;
//=================================================================================================
void extMCP4725(){ 
if(dvMCP4725.custom==0){dvMCP4725.custom=RT_HW_Base.i2cSetParam(dvMCP4725.dvI,i2cAdrMCP4725,0,800000);
                        dvMCP4725.mi='I'; RT_HW_Base.setTaskID(shMCP4725,'Q'); shMCP4725.period=0;}
//------------------------------------------------------------------------------------------------
RT_HW_Base.directTask(shMCP4725);                         //--Launching task; 
RT_HW_mcp4725.direct(dvMCP4725,vGenDAC,shMCP4725.run );   //--Direct MCP4725;
};
//=================================================================================================
//                                     1.2.MCP23017.i2c;
//=================================================================================================
void extMCP23x17_i2c(){ 
if(dvMCP23x17.custom==0){dvMCP23x17.custom=RT_HW_Base.i2cSetParam(dvMCP23x17.dvI,i2cAdrMCP23x17,0,0);
                         dvMCP23x17.mi='I';
                         dvMCP23x17.cnfgA=0x00; dvMCP23x17.cnfgIPOLA=0xFF; dvMCP23x17.cnfgGPPUA=0xFF;
                         dvMCP23x17.cnfgB=0x00; dvMCP23x17.cnfgIPOLB=0xFF; dvMCP23x17.cnfgGPPUB=0xFF;                        
                         RT_HW_Base.setTaskID(shMCP23x17in, 'P',500);  
                         RT_HW_Base.setTaskID(shMCP23x17out,'Q',100); 
                        }
RT_HW_Base.directTask(shMCP23x17in);
RT_HW_Base.directTask(shMCP23x17out);
if(shMCP23x17out.run){dvMCP23x17.extA=vGenA; dvMCP23x17.extB=vGenB;}
RT_HW_mcp23x17.direct(dvMCP23x17,shMCP23x17in.run,shMCP23x17out.run);
};
//=================================================================================================
//                                     1.3.PCF8575.i2c;
//=================================================================================================
void extPCF8575(){ 
if(dvPCF8575.custom==0){dvPCF8575.custom=RT_HW_Base.i2cSetParam(dvPCF8575.dvI,i2cAdrPCF8575,0,0);
                         dvPCF8575.mi='I';
                         dvPCF8575.cnfgA=0x00; dvPCF8575.invOutA=0xFF;  dvPCF8575.invInA=0xFF;
                         dvPCF8575.cnfgB=0x00; dvPCF8575.invOutB=0xFF;  dvPCF8575.invInB=0xFF;                     
                         RT_HW_Base.setTaskID(shPCF8575in, 'P',100);  
                         RT_HW_Base.setTaskID(shPCF8575out,'Q',100); 
                        }
RT_HW_Base.directTask(shPCF8575in);
RT_HW_Base.directTask(shPCF8575out);
if(shPCF8575out.run){dvPCF8575.extA=vGenA; dvPCF8575.extB=vGenB;}
RT_HW_pcf8575.direct(dvPCF8575,shPCF8575in.run,shPCF8575out.run);
if(dvPCF8575.fresh){};
};
//=================================================================================================
//                                     1.3.ADS1115.i2c;
//=================================================================================================
void extADS1115(){ 
if(dvADS1115.custom==0){dvADS1115.custom=RT_HW_Base.i2cSetParam(dvADS1115.dvI,i2cAdrADS1115,0,800000);
                        dvADS1115.mi='I';RT_HW_Base.setTaskID(shADS1115,'P',200);}
//------------------------------------------------------------------------------------------------
RT_HW_Base.directTask(shADS1115);                         //--Launching task; 
RT_HW_ads1115.direct(dvADS1115,shADS1115.run );           //--Direct ADS1115;
//-------------------------------------------------------------------------------------------------
if(dvADS1115.fresh){dvADS1115.fresh=0;                  vADS1115_ok=dvADS1115.ok; 
vADS1115_A0f=RT_HW_ads1115.getVar_V(dvADS1115,dvADS1115.vA0);  
vADS1115_A1f=RT_HW_ads1115.getVar_V(dvADS1115,dvADS1115.vA1); 
vADS1115_A2f=RT_HW_ads1115.getVar_V(dvADS1115,dvADS1115.vA2);  
vADS1115_A3f=RT_HW_ads1115.getVar_V(dvADS1115,dvADS1115.vA3);
}};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                     2. I/O EXPANDERS via SPI
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=================================================================================================
//                                     2.1. 74HC595.SPI
//=================================================================================================
void direct595(){   
if(dv74HC595.custom==0){dv74HC595.custom=RT_HW_Base.spiSetParam(dv74HC595.dvS,cs74HC595,0,4000000);
                        dv74HC595.mi='S'; dv74HC595.qnt=4; dv74HC595.bitOrder=1;  //--qnt=Number of registers 74HC595(1-4);
                        RT_HW_Base.setTaskID(sh74HC595,'Q');}  //--Setting task: 'Q'-on change output in every  default=5th cycle; 
//-------------------------------------------------------------------------------------------------
if(sh74HC595.custom==0){RT_HW_Base.setTaskID(sh74HC595,'Q');} //  Setting task: 'Q'-on change output in every  default=5th cycle;
//-------------------------------------------------------------------------------------------------
RT_HW_Base.directTask(sh74HC595); 
if(sh74HC595.run){
if(dv74HC595.qnt==1){vGenRun=vGenRun8;}
if(dv74HC595.qnt==2){vGenRun=vGenRun16;}
if(dv74HC595.qnt==3){vGenRun=vGenRun24;}
if(dv74HC595.qnt==4){vGenRun=vGenRun32;}
}
//-------------------------------------------------------------------------------------------------
RT_HW_74hc595.direct(dv74HC595,vGenRun,sh74HC595.run);
};
//=================================================================================================
//                                     2.2. 74HC595.SPN
//=================================================================================================
void direct595N(){   
if(dv74HC595N.custom==0){dv74HC595N.custom=RT_HW_Base.spnSetParam(dv74HC595N.dvN,sck74HC595N,255,mosi74HC595N,cs74HC595N,0);
                         dv74HC595N.mi='N'; dv74HC595N.qnt=4; dv74HC595N.bitOrder=1;  //--qnt=Number of registers 74HC595(1-4);
                         RT_HW_Base.setTaskID(sh74HC595N,'Q');}  //--Setting task: 'Q'-on change output in every  default=5th cycle; 
//-------------------------------------------------------------------------------------------------
RT_HW_Base.directTask(sh74HC595N); 
if(sh74HC595N.run){
if(dv74HC595N.qnt==1){vGenRunN=vGenRun8;}
if(dv74HC595N.qnt==2){vGenRunN=vGenRun16;}
if(dv74HC595N.qnt==3){vGenRunN=vGenRun24;}
if(dv74HC595N.qnt==4){vGenRunN=vGenRun32;}
}
//-------------------------------------------------------------------------------------------------
RT_HW_74hc595.direct(dv74HC595N,vGenRunN,sh74HC595N.run);
};
//=================================================================================================
//                                     2.3. 74HC165.SPI
//=================================================================================================
void direct165(){   
if(dv74HC165.custom==0){dv74HC165.custom=RT_HW_Base.spiSetParam(dv74HC165.dvS,cs74HC165,0,4000000);
                        dv74HC165.mi='S'; dv74HC165.qnt=2; dv74HC165.bitOrder=1;  //--qnt=Number of registers 74HC595(1-4);
                        RT_HW_Base.setTaskID(sh74HC165,'P',50);}                  //  Setting task: 'P';
//-------------------------------------------------------------------------------------------------
RT_HW_Base.directTask(sh74HC165); 
//-------------------------------------------------------------------------------------------------
RT_HW_74hc165.direct(dv74HC165,sh74HC165.run); 
if(dv74HC165.fresh){dv74HC165.fresh=0;  v74HC165=dv74HC165.var;};
};
//=================================================================================================
//                                     2.4. 74HC165.SPN
//=================================================================================================
void direct165N(){   
if(dv74HC165N.custom==0){dv74HC165N.custom=RT_HW_Base.spnSetParam(dv74HC165N.dvN,sck74HC165N,miso74HC165N,255,cs74HC165N,0);
                        dv74HC165N.mi='N'; dv74HC165N.qnt=4; dv74HC165N.bitOrder=1;  //--qnt=Number of registers 74HC595N(1-4);
                        RT_HW_Base.setTaskID(sh74HC165N,'P',50);}   //  Setting task: 'P';
//-------------------------------------------------------------------------------------------------
RT_HW_Base.directTask(sh74HC165N); 
//-------------------------------------------------------------------------------------------------
RT_HW_74hc165.direct(dv74HC165N,sh74HC165.run); 
if(dv74HC165N.fresh){if(ago74HC165N!=v74HC165N){ago74HC165N=v74HC165N; RT_HW_Base.consoleTest(String(F("74HC165N  v")),v74HC165N,'E','H');}}
if(dv74HC165N.fresh){dv74HC165N.fresh=0; v74HC165N=dv74HC165N.var;};
};
//=================================================================================================
